using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Collections.ObjectModel;
using Windows.UI.Popups;
using Windows.Storage;
using Newtonsoft.Json;
using Todos.ViewModels;
using Windows.Data.Xml.Dom;
using Windows.UI.Notifications;
using NotificationsExtensions.Tiles;
using NotificationsExtensions.Badges;
using Windows.ApplicationModel.DataTransfer;
using Windows.ApplicationModel;
using Windows.Storage.Streams;
using System.Collections;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace Todos
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            var viewTitleBar = Windows.UI.ViewManagement.ApplicationView.GetForCurrentView().TitleBar;
            viewTitleBar.BackgroundColor = Windows.UI.Colors.CornflowerBlue;
            viewTitleBar.ButtonBackgroundColor = Windows.UI.Colors.CornflowerBlue;
            dtm.DataRequested += DataTransferManager_DataRequested;

        }

        ~MainPage()
        {
            dtm.DataRequested -= DataTransferManager_DataRequested;
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            //if (e.Parameter.GetType() == typeof(TodoItemViewModels.TodoItemTodoItemViewModel))
            //{
            //    this.TodoItemViewModel = (TodoItemViewModels.TodoItemTodoItemViewModel)(e.Parameter);
            //}
            Update_Tile();
        }

        ObservableCollection<Models.TodoItem> AllItems = TodoItemViewModel.AllItems;
        DataTransferManager dtm = DataTransferManager.GetForCurrentView();
        Models.TodoItem SharedItem;

        void Update_Tile()
        {
            TileContent content = new TileContent()
            {
                Visual = new TileVisual()
                {
                    Branding = TileBranding.Name,
                    TileSmall = new TileBinding()
                    {
                        Content = new TileBindingContentAdaptive()
                        {
                            Children =
                            {
                                new TileText()
                                {
                                    Text = AllItems.Count > 0 ? AllItems[AllItems.Count - 1].title : "BY SplendidSky",
                                    Style = TileTextStyle.Subtitle
                                },
                                new TileText()
                                {
                                    Text = AllItems.Count > 0 ? AllItems[AllItems.Count - 1].description : "",
                                    Style = TileTextStyle.CaptionSubtle
                                },
                            },
                            BackgroundImage = new TileBackgroundImage()
                            {
                                Source = new TileImageSource(AllItems.Count > 0 ? Models.TodoItem.ImagePath + AllItems[AllItems.Count - 1].ImageName : Models.TodoItem.ImagePath + "background.jpg"),
                                Overlay = 20
                            },
                        }
                    },
                    TileMedium = new TileBinding()
                    {
                        Content = new TileBindingContentAdaptive()
                        {
                            Children =
                            {
                                new TileText()
                                {
                                    Text = AllItems.Count > 0 ? AllItems[AllItems.Count - 1].title : "BY SplendidSky",
                                    Style = TileTextStyle.Subtitle
                                },
                                new TileText()
                                {
                                    Text = AllItems.Count > 0 ? AllItems[AllItems.Count - 1].description : "",
                                    Style = TileTextStyle.CaptionSubtle
                                },
                            },
                            BackgroundImage = new TileBackgroundImage()
                            {
                                Source = new TileImageSource(AllItems.Count > 0 ? Models.TodoItem.ImagePath + AllItems[AllItems.Count - 1].ImageName : Models.TodoItem.ImagePath + "background.jpg"),
                                Overlay = 40
                            },
                        }
                    },
                    TileWide = new TileBinding()
                    {
                        Content = new TileBindingContentAdaptive()
                        {
                            Children =
                            {
                                new TileText()
                                {
                                    Text = AllItems.Count > 0 ? AllItems[AllItems.Count - 1].title : "BY SplendidSky",
                                    Style = TileTextStyle.Subtitle
                                },
                                new TileText()
                                {
                                    Text = AllItems.Count > 0 ? AllItems[AllItems.Count - 1].description : "",
                                    Style = TileTextStyle.CaptionSubtle
                                }
                            },
                            BackgroundImage = new TileBackgroundImage()
                            {
                                Source = new TileImageSource(AllItems.Count > 0 ? Models.TodoItem.ImagePath + AllItems[AllItems.Count - 1].ImageName : Models.TodoItem.ImagePath + "background.jpg"),
                                Overlay = 60
                            },
                        }
                    }
                }
            };
            var notifi = new TileNotification(content.GetXml());
            var updater = TileUpdateManager.CreateTileUpdaterForApplication();
            updater.Update(notifi);
        }

        private void TodosListView_ItemClicked(object sender, ItemClickEventArgs e)
        {
            TodoItemViewModel.SelectedItem = (Models.TodoItem)(e.ClickedItem);
            Frame.Navigate(typeof(NewPage));
        }

        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            TodoItemViewModel.SelectedItem = null;
            Frame.Navigate(typeof(NewPage));
        }

        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            var i = new MessageDialog("");

            if (Title.Text == "")
            {
                i.Content = "请填写标题！";
                i.ShowAsync();
            }

            else if (Details.Text == "")
            {
                i.Content = "请填写计划细节！";
                i.ShowAsync();
            }

            else if (Date.Date < DateTime.Now.Date)
            {
                i.Content = "时间设置不正确！";
                i.ShowAsync();
            }

            else {
                TodoItemViewModel.AddTodoItem(Title.Text, Details.Text, Date.Date.Date, Image.Source, "background.jpg");
                Title.Text = "";
                Details.Text = "";
                Date.Date = DateTime.Now.Date;
                TodoItemViewModel.SelectedItem = null;
                Update_Tile();
            }
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            Title.Text = "";
            Details.Text = "";
            Date.Date = DateTime.Now.Date;
        }

        private void Update_Click(object sender, RoutedEventArgs e)
        {
            Update_Tile();
        }

        private void Share_Click(object sender, RoutedEventArgs e)
        {
            dynamic d = e.OriginalSource;
            SharedItem = (Models.TodoItem)d.DataContext;
            DataTransferManager.ShowShareUI();
        }

        async private void DataTransferManager_DataRequested(DataTransferManager sender, DataRequestedEventArgs args)
        {
            DataPackage data = args.Request.Data;
            data.Properties.Title = SharedItem.title;
            data.Properties.Description = SharedItem.description;
            DataRequestDeferral GetFiles = args.Request.GetDeferral();
            try
            {
                Windows.Storage.StorageFolder imageFolder = await StorageFolder.GetFolderFromPathAsync(Models.TodoItem.ImagePath);
                Windows.Storage.StorageFile imageFile = await imageFolder.GetFileAsync(SharedItem.ImageName);
                data.Properties.Thumbnail = RandomAccessStreamReference.CreateFromFile(imageFile);
                data.SetBitmap(RandomAccessStreamReference.CreateFromFile(imageFile));
            }
            finally
            {
                GetFiles.Complete();
            }
        }

        private void Query_Click(object sender, RoutedEventArgs e)
        {
            var QueryString = QueryTextBox.Text;
            ArrayList items = new ArrayList();
            items = TodoItemViewModel.getTodoItemsByKeywords(QueryString);
            var msg = new MessageDialog("");
            string content = "";
            foreach (var item in items)
            {
                var it = (Models.TodoItem)item;
                content += "Title: " + it.title + "; Description: " + it.description + "; Date: " + it.date.Date;
                content += "\n";
            }
            msg.Content = content == "" ? "未查询到相关信息！" : content;
            msg.ShowAsync();
        }
    }
}
