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

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace Animal
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private delegate void AnimalSaying(object sender, myEventArgs e);
        private event AnimalSaying Say;
        private int times = 0;

        public MainPage()
        {
            this.InitializeComponent();
        }

        interface Animal
        {
            void saying(object sender, myEventArgs e);
        }

        class Pig : Animal
        {
            TextBlock text;

            public Pig(TextBlock t)
            {
                this.text = t;
            }

            public void saying(object sender, myEventArgs e)
            {
                if (e.choice == 1)
                    this.text.Text += "pig : I'm a pig\n";
            }
        }

        class Dog : Animal
        {
            TextBlock text;

            public Dog(ref TextBlock t)
            {
                this.text = t;
            }

            public void saying(object sender, myEventArgs e)
            {
                if (e.choice == 2)
                    this.text.Text += "dog : I'm a dog\n";
            }
        }

        class Cat : Animal
        {
            TextBlock text;

            public Cat(TextBlock t)
            {
                this.text = t;
            }

            public void saying(object sender, myEventArgs e)
            {
                if (e.choice == 3)
                    this.text.Text += "cat : I'm a cat\n";
            }
        }

        private Pig p;
        private Dog d;
        private Cat c;

        private void speakClick(object sender, RoutedEventArgs e)
        {
            if (times == 0)
            {
                p = new Pig(textBlock);
                d = new Dog(ref textBlock);
                c = new Cat(textBlock);
                Say += p.saying;
                Say += d.saying;
                Say += c.saying;
            }

            Random ran = new Random();

            Say(this, new myEventArgs(ran.Next(1, 4)));

            times++;
        }

        private void sureClick(object sender, RoutedEventArgs e)
        {
            if (times == 0)
            {
                Say += p.saying;
                Say += d.saying;
                Say += c.saying;
            }


            if (textBox.Text == "Pig" || textBox.Text == "pig")
            {
                Animal a = new Pig(textBlock);
                a.saying(sender, new myEventArgs(1));
            }
            if (textBox.Text == "Dog" || textBox.Text == "dog")
            {
                Animal a = new Dog(ref textBlock);
                a.saying(sender, new myEventArgs(2));
            }
            if (textBox.Text == "Cat" || textBox.Text == "cat")
            {
                Animal a = new Cat(textBlock);
                a.saying(sender, new myEventArgs(3));
            }

            textBox.Text = "";

            times++;
        }

        class myEventArgs : EventArgs
        {
            public int choice;
            public myEventArgs(int c)
            {
                this.choice = c;
            }
        }

        private void textBox_KeyUp(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == Windows.System.VirtualKey.Enter)
                sureClick(this, new RoutedEventArgs());
        }
    }
}
