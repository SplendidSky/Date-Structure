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

namespace _2048
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void Game_Click(object sender, RoutedEventArgs e)
        {
            //转到游戏开始界面
            Frame.Navigate(typeof(GamePage), "");
        }

        private void Rule_Click(object sender, RoutedEventArgs e)
        {
            //转到游戏说明界面
            Frame.Navigate(typeof(RulePage), "");
        }

        private void Grade_Click(object sender, RoutedEventArgs e)
        {
            //转到排行榜界面（测试游戏结束界面）
            Frame.Navigate(typeof(RankPage), "");
            //Frame.Navigate(typeof(GradePage), "");
        }
    }
}
