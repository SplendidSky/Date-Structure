﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Data;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Popups;
using Windows.Storage;
using System.Collections.ObjectModel;
using Newtonsoft.Json;
using Todos.ViewModels;
using Windows.ApplicationModel;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上提供

namespace Todos
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class NewPage : Page
    {

        public NewPage()
        {
            this.InitializeComponent();
            var viewTitleBar = Windows.UI.ViewManagement.ApplicationView.GetForCurrentView().TitleBar;
            viewTitleBar.BackgroundColor = Windows.UI.Colors.CornflowerBlue;
            viewTitleBar.ButtonBackgroundColor = Windows.UI.Colors.CornflowerBlue;
            //PreviousItem = TodoItemViewModel.Load();
            SelectedItem = TodoItemViewModel.SelectedItem;
        }

        Models.TodoItem SelectedItem;
        Models.TodoItem Item;
        //Models.TodoItem PreviousItem;
        string ImageName = "background.jpg";
        string ImagePath = Models.TodoItem.ImagePath;

        //async void CopyImage()
        //{
        //    string sourece = ImagePath;
        //    string target = Models.TodoItem.ImagePath + ImageName;
        //    Windows.Storage.StorageFolder sourceFolder = await StorageFolder.GetFolderFromPathAsync(ImagePath);
        //    Windows.Storage.StorageFolder targetFolder = await StorageFolder.GetFolderFromPathAsync(Models.TodoItem.ImagePath);
        //    Windows.Storage.StorageFile file = await sourceFolder.GetFileAsync(ImageName);
        //    await file.CopyAsync(targetFolder);
        //    System.IO.File.Copy(sourece, target);
        //}

        protected async override void OnNavigatedTo(NavigationEventArgs e)
        {
            if (Window.Current.Content != null)
            {
                Frame rootFrame = Window.Current.Content as Frame;
                if (rootFrame.CanGoBack)
                {
                    // Show UI in title bar if opted-in and in-app backstack is not empty.
                    SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                        AppViewBackButtonVisibility.Visible;
                    ((App)App.Current).BackRequest += NewPageBackRequested;
                    ((App)App.Current).Suspending += NewPageSuspending;
                }
                else
                {
                    // Remove the UI from the title bar if in-app back stack is empty.
                    SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                        AppViewBackButtonVisibility.Collapsed;
                }
            }

            if (true)
            {
                CreateOrUpdateButton.Content = "Create";
                SelectedItem.title = Title.Text;
                SelectedItem = new Models.TodoItem();
                await SelectedItem.LoadImageAsync();
                Image.Source = SelectedItem.image;
            }
            else
                CreateOrUpdateButton.Content = "Update";
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            //TodoItemViewModel.Save(SelectedItem.id, Title.Text, Details.Text, Date.Date.Date);
            ((App)App.Current).BackRequest -= NewPageBackRequested;
            ((App)App.Current).Suspending -= NewPageSuspending;
            Item = new Models.TodoItem(SelectedItem.title, SelectedItem.description, SelectedItem.date, SelectedItem.image, SelectedItem.ImageName);
            SelectedItem = null;
            //base.OnNavigatedFrom(e);
        }

        private void NewPageBackRequested(object sender, BackRequestedEventArgs e)
        {
            //TodoItemViewModel.Save(Title.Text, Details.Text, Date.Date.Date, Image.Source, ImageName, Item);
        }

        private void NewPageSuspending(object sender, SuspendingEventArgs e)
        {
            //TodoItemViewModel.Save(Title.Text, Details.Text, Date.Date.Date, Image.Source, ImageName, Item);
        }

        private void CreateOrUpdateButton_Click(object sender, RoutedEventArgs e)
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


            else
            {
                if ((string)CreateOrUpdateButton.Content == "Create")
                {
                    TodoItemViewModel.AddTodoItem(Title.Text, Details.Text, Date.Date.Date, Image.Source, ImageName);
                }
                else
                    TodoItemViewModel.UpdateTodoItem(TodoItemViewModel.SelectedItem.id, Title.Text, Details.Text, Date.Date.Date, Image.Source, ImageName);
                Frame.Navigate(typeof(MainPage));
            }

        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            if ((string)CreateOrUpdateButton.Content == "Create")
            {
                Title.Text = "";
                Details.Text = "";
                Date.Date = DateTime.Now.Date;
            }
            Frame.Navigate(typeof(MainPage));

        }

        private async void SelectPictureButton_Click(object sender, RoutedEventArgs e)
        {
            Windows.Storage.Pickers.FileOpenPicker filePicker = new Windows.Storage.Pickers.FileOpenPicker();
            filePicker.ViewMode = Windows.Storage.Pickers.PickerViewMode.Thumbnail;
            filePicker.FileTypeFilter.Add(".jpg");
            filePicker.FileTypeFilter.Add(".jpeg");
            filePicker.FileTypeFilter.Add(".png");
            filePicker.FileTypeFilter.Add(".bmp");
            filePicker.SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.PicturesLibrary;

            StorageFile file = await filePicker.PickSingleFileAsync();
            if (file != null)
            {
                using (Windows.Storage.Streams.IRandomAccessStream fileStream =
                     await file.OpenAsync(Windows.Storage.FileAccessMode.Read))
                {
                    // Set the image source to the selected bitmap.
                    Windows.UI.Xaml.Media.Imaging.BitmapImage bitmapImage =
                        new Windows.UI.Xaml.Media.Imaging.BitmapImage();
                    bitmapImage.SetSource(fileStream);
                    Image.Source = bitmapImage;
                    ImageName = file.Name;
                    ImagePath = file.Path;
                    Windows.Storage.StorageFolder targetFolder = await StorageFolder.GetFolderFromPathAsync(Models.TodoItem.ImagePath);
                    await file.CopyAsync(targetFolder, ImageName, NameCollisionOption.ReplaceExisting);
                }
            }
        }

        private void AppBarButton_Click(object sender, RoutedEventArgs e)
        {
            TodoItemViewModel.RemoveTodoItem(TodoItemViewModel.SelectedItem.id);
            TodoItemViewModel.SelectedItem = null;
            Frame.Navigate(typeof(MainPage));
        }

    }
}
