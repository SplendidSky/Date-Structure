using System;
using System.Collections.ObjectModel;
using Models;

namespace ViewModel
{
    public class MessageViewModel
    {
        static public ObservableCollection<Message> Messages = new ObservableCollection<Message>();
    }
}