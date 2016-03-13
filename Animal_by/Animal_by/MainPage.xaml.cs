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

namespace Animal_by
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private delegate string AnimalSaying(object sender, myEventArgs e);//声明一个委托
        private event AnimalSaying Say;//委托声明一个事件
        private int times = 0;

        public MainPage()
        {
            this.InitializeComponent();
        }

        interface Animal
        {
            //方法
            string saying(object sender, myEventArgs e);
            //属性
            int A { get; set; }
        }

        class cat : Animal
        {
            TextBlock word;
            private int a;

            public cat(TextBlock w)
            {
                this.word = w;
            }
            public string saying(object sender, myEventArgs e)
            {
                this.word.Text += "cat : I am a Cat" + "\n";
                return "";
            }
            public int A
            {
                get { return a; }
                set { this.a = value; }
            }
        }

        class dog : Animal
        {
            TextBlock word;
            private int a;

            public dog(TextBlock w)
            {
                this.word = w;
            }
            public string saying(object sender, myEventArgs e)
            {
                this.word.Text += "dog : I am a Dog\n";
                return "";
            }
            public int A
            {
                get { return a; }
                set { this.a = value; }
            }
        }

        class pig : Animal
        {
            TextBlock word;
            private int a;

            public pig(TextBlock w)
            {
                this.word = w;
            }
            public string saying(object sender, myEventArgs e)
            {
                this.word.Text +=  "pig : I am a Pig" + "\n";
                return "";
            }
            public int A
            {
                get { return a; }
                set { this.a = value; }
            }
        }

        private cat c;
        private dog d;
        private pig p;

        public string GetRandom(string[] arr)
        {
            Random ran = new Random();
            int n = ran.Next(arr.Length);
            return arr[n];
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            
            string[] arr = {"Pig", "Cat", "Dog" };
            string astring = GetRandom(arr);
            words.Text += astring + " : " + "I am a " +astring + "\n";
            times++;
        }

        private void Button_Click_(object sender, RoutedEventArgs e)
        {
            c = new cat(words);
            d = new dog(words);
            p = new pig(words);
            if (textBox.Text  == "cat" || textBox.Text == "Cat") {
                Say += c.saying;
                Say(this, new myEventArgs(times++));
                Say -= c.saying;
            } else if (textBox.Text == "dog" || textBox.Text == "Dog")
            {
                Say += d.saying;
                Say(this, new myEventArgs(times++));
                Say -= d.saying;
            }
            else if (textBox.Text == "pig" || textBox.Text == "Pig")
            {
                Say += p.saying;
                Say(this, new myEventArgs(times++));
                Say -= p.saying;
            }
            else { }
            textBox.Text = "";
        }

        //自定义一个Eventargs传递事件参数
        class myEventArgs : EventArgs
        {
            public int t = 0;
            public myEventArgs(int tt)
            {
                this.t = tt;
            }
        }
    }
}
