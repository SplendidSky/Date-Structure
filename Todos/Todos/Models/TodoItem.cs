using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Windows.UI.Xaml.Media;
using System.IO;
using Windows.Storage;
using System.Threading.Tasks;

namespace Todos.Models
{
    class TodoItem : INotifyPropertyChanged
    {
        private string _id;
        public string id
        {
            get
            {
                return _id;
            }
            set
            {
                _id = value;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void NotifyPropertyChanged([CallerMemberName] String propertyName = "")
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        private string _title;
        public string title
        {
            get
            {
                return _title;
            }
            set
            {
                _title = value;
            }
        }

        private string _description;
        public string description
        {
            get
            {
                return _description;
            }
            set
            {
                _description = value;
                NotifyPropertyChanged();
            }
        }

        private bool? _completed;
        public bool? completed
        {
            get
            {
                return this._completed;
            }
            set
            {
                this._completed = value;
                NotifyPropertyChanged();
            }
        }

        private DateTime _date;
        public DateTime date
        {
            get
            {
                return _date;
            }
            set
            {
                _date = value;
                NotifyPropertyChanged();
            }
        }

        private ImageSource _image;
        public ImageSource image
        {
            get
            {
                return _image;
            }
            set
            {
                _image = value;
                NotifyPropertyChanged();
            }
        }


        public static string ImagePath = Directory.GetCurrentDirectory() + "\\Assets\\";
        public string ImageName;

        public async Task LoadImageAsync()
        {
            StorageFolder folder = await StorageFolder.GetFolderFromPathAsync(ImagePath);
            StorageFile file = await folder.GetFileAsync(ImageName);
            using (Windows.Storage.Streams.IRandomAccessStream fileStream =
                    await file.OpenAsync(FileAccessMode.Read))
            {
                // Set the image source to the selected bitmap.
                Windows.UI.Xaml.Media.Imaging.BitmapImage bitmapImage =
                    new Windows.UI.Xaml.Media.Imaging.BitmapImage();
                bitmapImage.SetSource(fileStream);
                _image = bitmapImage;
            }
        }

        public TodoItem(string title, string description, DateTime date, ImageSource imageSource, string ImageName)
        {
            if (imageSource != null)
                image = imageSource;
            this._id = Guid.NewGuid().ToString();
            this._title = title;
            this._description = description;
            this._date = date;
            this._completed = false;
            this.ImageName = ImageName;
        }

        public TodoItem(string title, string description, DateTime date)
        {
            this._id = Guid.NewGuid().ToString();
            this._title = title;
            this._description = description;
            this._date = date;
            this._completed = false;
            this.ImageName = "background.jpg";

        }

        public TodoItem(string id, string title, string description, bool? completed, DateTime date, string ImageName)
        {
            this._id = id;
            this._title = title;
            this._description = description;
            this._completed = completed;
            this._date = date;
            this._completed = false;
            this.ImageName = ImageName;
        }

        public TodoItem()
        {
            this._id = Guid.NewGuid().ToString();
            this._title = "";
            this._description = "";
            this._date = DateTime.Today;
            this._completed = false;
            this.ImageName = "background.jpg";
        }
    }
}

