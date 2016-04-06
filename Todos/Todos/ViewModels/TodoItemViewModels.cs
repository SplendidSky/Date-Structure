using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using Windows.Storage;
using System.Runtime.Serialization.Json;
using System.IO;
using Newtonsoft.Json;
using Windows.UI.Xaml.Media;
using System.Collections;
using SQLitePCL;

namespace Todos.ViewModels
{
    class TodoItemViewModel
    {
        static private ObservableCollection<Models.TodoItem> allItems = new ObservableCollection<Models.TodoItem>()
        {
        };
        static public ObservableCollection<Models.TodoItem> AllItems { get { return allItems; } }

        static public Models.TodoItem SelectedItem { get; set; }

        static public void AddTodoItem(string title, string description, DateTime date, ImageSource imageSource, string ImageName)
        {
            allItems.Add(new Models.TodoItem(title, description, date, imageSource, ImageName));
        }

        static public void RemoveTodoItem(string id)
        {
            // DIY
            allItems.Remove(SelectedItem);
            // set selectedItem to null after remove
            SelectedItem = null;
            var db = App.db;
            using (var statement = db.Prepare("DELETE FROM Todoitems WHERE ID = ?"))
            {
                statement.Bind(1, id);
                statement.Step();
            }
        }

        static public void UpdateTodoItem(string id, string title, string description, DateTime date, ImageSource image_source, string ImageName)
        {
            SelectedItem.title = title;
            SelectedItem.description = description;
            SelectedItem.date = date;
            SelectedItem.image = image_source;
            SelectedItem.ImageName = ImageName;
        }

        static public Models.TodoItem getTodoItemByID(string ID)
        {
            foreach (var item in allItems)
            {
                if (item.id == ID)
                    return item;
            }
            return null;
        }

        static public ArrayList getTodoItemsByKeywords(params string[] keywords)
        {
            var db = App.db;
            ArrayList items = new ArrayList();
            foreach (var keyword in keywords)
            {
                using (var statement = db.Prepare("SELECT * FROM Todoitems WHERE Title = ? OR Description = ?"))
                {
                    statement.Bind(1, keyword);
                    statement.Bind(2, keyword);
                    while (statement.Step() == SQLiteResult.ROW)
                    {
                        string id = (string)statement["ID"];
                        string title = (string)statement["Title"];
                        string description = (string)statement["Description"];
                        bool? completed = (Int64)statement["Completed"] == 0 ? false : true;
                        DateTime date = (DateTime.Parse((string)statement["Date"]));
                        string ImageName = (string)statement["ImageName"];
                        Models.TodoItem item = new Models.TodoItem(id, title, description, completed, date, ImageName);
                        items.Add(item);
                    }
                }
                //using (var statement = db.Prepare("SELECT * FROM Todoitems WHERE Description = ?"))
                //{
                //    statement.Bind(1, keyword);
                //    while (statement.Step() == SQLiteResult.ROW)
                //    {
                //        string id = (string)statement["ID"];
                //        string title = (string)statement["Title"];
                //        string description = (string)statement["Description"];
                //        bool? completed = (Int64)statement["Completed"] == 0 ? false : true;
                //        DateTime date = (DateTime.Parse((string)statement["Date"]));
                //        string ImageName = (string)statement["ImageName"];
                //        Models.TodoItem item = new Models.TodoItem(id, title, description, completed, date, ImageName);
                //        items.Add(item);
                //    }
                //}
            }
            return items;
        }

        static public void SaveAll()
        {
            foreach (var item in allItems)
            {
                var db = App.db;
                using (var statement = db.Prepare("BEGIN TRANSACTION"))
                {
                    statement.Step();
                }
                using (var statement = db.Prepare("SELECT * FROM TodoItems WHERE ID = ?"))
                {
                    statement.Bind(1, item.id);
                    if (statement.Step() != SQLiteResult.ROW)
                    {
                        using (var custstmt = db.Prepare("INSERT INTO TodoItems(ID, Title, Description, Completed, Date, ImageName) VALUES(?, ?, ?, ?, ?, ?)"))
                        {
                            custstmt.Bind(1, item.id);
                            custstmt.Bind(2, item.title);
                            custstmt.Bind(3, item.description);
                            int c = item.completed == true ? 1 : 0;
                            custstmt.Bind(4, c);
                            custstmt.Bind(5, item.date.ToString());
                            custstmt.Bind(6, item.ImageName);
                            custstmt.Step();
                        }
                    }
                    else
                    {
                        using (var custstmt = db.Prepare("UPDATE TodoItems SET Title = ?, Description = ?, Completed = ?, Date = ?, ImageName = ? WHERE ID = ?"))
                        {
                            custstmt.Bind(1, item.title);
                            custstmt.Bind(2, item.description);
                            int c = item.completed == true ? 1 : 0;
                            custstmt.Bind(3, c);
                            custstmt.Bind(4, item.date.ToString());
                            custstmt.Bind(5, item.ImageName);
                            custstmt.Bind(6, item.id);
                            custstmt.Step();
                        }
                    }
                }

                using (var statement = db.Prepare("COMMIT TRANSACTION"))
                {
                    statement.Step();
                }
            }
        }

        static async public void LoadAll()
        {
            var db = App.db;
            using (var statement = db.Prepare("SELECT * FROM TodoItems"))
            {
                while (statement.Step() == SQLitePCL.SQLiteResult.ROW)
                {
                    string id = (string)statement["ID"];
                    string title = (string)statement["Title"];
                    string description = (string)statement["Description"];
                    bool? completed = (Int64)statement["Completed"] == 0 ? false : true;
                    DateTime date = (DateTime.Parse((string)statement["Date"]));
                    string ImageName = (string)statement["ImageName"];
                    Models.TodoItem item = new Models.TodoItem(id, title, description, completed, date, ImageName);
                    await item.LoadImageAsync();
                    allItems.Add(item);
                }
            }
        }

        //static public Todos.Models.TodoItem Load()
        //{
        //    if (SelectedItem == null)
        //    {
        //        Todos.Models.TodoItem Item = new Models.TodoItem();
        //        SelectedItem = new Todos.Models.TodoItem();
        //        if (ApplicationData.Current.RoamingSettings.Values.ContainsKey("TheData"))
        //        {
        //            Todos.Models.TodoItem data = JsonConvert.DeserializeObject<Todos.Models.TodoItem>(
        //                (string)ApplicationData.Current.RoamingSettings.Values["TheData"]);
        //            string title = (string)ApplicationData.Current.RoamingSettings.Values["title"];
        //            SelectedItem = getTodoItemByID(SelectedItem.id);
        //            Item.title = SelectedItem.title;
        //            Item.description = SelectedItem.description;
        //            Item.date = SelectedItem.date;
        //            SelectedItem.title = data.title;
        //            SelectedItem.description = data.description;
        //            SelectedItem.date = data.date;
        //        }
        //        return Item;
        //    }
        //    return null;
        //}

        //static public void Save(string title, string description, DateTime date, ImageSource image_source, string ImageName, Todos.Models.TodoItem Item)
        //{
        //    Todos.Models.TodoItem data = new Todos.Models.TodoItem(title, description, date, image_source, ImageName);
        //    ApplicationData.Current.RoamingSettings.Values["TheData"] = JsonConvert.SerializeObject(data);
        //    ApplicationData.Current.RoamingSettings.Values["title"] = Item.title;
        //}
    }
}
