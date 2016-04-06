using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Http;
using System.Text;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using ViewModel;
using System.Collections.ObjectModel;
using Windows.UI.Popups;
using Models;
using Windows.Networking;
using Windows.Networking.Sockets;
using Windows.Networking.Connectivity;
using System.Threading.Tasks;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace Turing
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            SocketListener();
        }

        private ObservableCollection<Message> Messages = ViewModel.MessageViewModel.Messages;
        private bool ChatMode = false;
        private StreamSocket client;

        public async void Turing(string info)
        {
            Messages.Add(new Message("You", DateTime.Now, info, true));
            info = System.Net.WebUtility.UrlEncode(info);

            //构造请求的url
            string url = "http://apis.baidu.com/turing/turing/turing";
            string param = "key=879a6cb3afb84dbf4fc84a1df2ab7319&info=";
            param += info;
            param += "&userid=eb2edb736";
            string strURL = url + '?' + param;

            try
            {
                HttpClient httpClient = new HttpClient();

                //添加头部信息
                var headers = httpClient.DefaultRequestHeaders;
                string header = "ie Mozilla/5.0 (Windows NT 6.2; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0";
                if (!headers.UserAgent.TryParseAdd(header))
                {
                    throw new Exception("Invalid header value: " + header);
                }
                headers.Add("apikey", "6a3ae60bad55e2b4248128250fa253a5");

                //处理服务器的答复
                HttpResponseMessage response = await httpClient.GetAsync(strURL);
                response.EnsureSuccessStatusCode();

                Byte[] getByte = await response.Content.ReadAsByteArrayAsync();

                Encoding code = Encoding.GetEncoding("UTF-8");
                string result = code.GetString(getByte, 0, getByte.Length);

                JsonReader json = new JsonTextReader(new StringReader(result));
                string jsonVal = "";

                while (json.Read())
                {
                    jsonVal += json.Value;
                    if (jsonVal.Equals("text"))
                    {
                        json.Read();
                        Messages.Add(new Message("Turing", DateTime.Now, (string)json.Value, false));
                        break;
                    }
                    jsonVal = "";
                }
            }
            catch (Exception e)
            {
                MessageDialog i = new MessageDialog("请检查网络设置！\n" + e.Message);
                await i.ShowAsync();
                //如果无法连接到网络，退出程序
                Application.Current.Exit();
            }
        }

        public async Task<StreamSocket> BeginToChat(HostName RemoteHost)
        {
            var HostNames = NetworkInformation.GetHostNames();
            var LocalHost = HostNames.FirstOrDefault(h =>
            {
                bool isIpaddr = h.Type == Windows.Networking.HostNameType.Ipv4;
                // 如果不是IP地址表示的名称，则忽略
                if (isIpaddr == false)
                {
                    return false;
                }
                IPInformation ipinfo = h.IPInformation;
                // 71表示无线，6表示以太网
                if (ipinfo.NetworkAdapter.IanaInterfaceType == 71 || ipinfo.NetworkAdapter.IanaInterfaceType == 6)
                {
                    return true;
                }
                return false;
            });
            EndpointPair EndPoint = new EndpointPair(LocalHost, "", RemoteHost, "ChatWithMe");
            StreamSocket client = new StreamSocket();
            await client.ConnectAsync(EndPoint);
            return client;
        }

        public async void SocketListener()
        {
            StreamSocketListener listener = new StreamSocketListener();
            await listener.BindServiceNameAsync("ChatWithMe");
            listener.ConnectionReceived += Listener_ConnectionReceived;
        }

        private void Listener_ConnectionReceived(StreamSocketListener sender, StreamSocketListenerConnectionReceivedEventArgs args)
        {
            client = args.Socket;
        }

        public void Chat()
        {
            var DataWriter = new Windows.Storage.Streams.DataWriter(client.OutputStream);
            DataWriter.WriteString("test\n");
            Messages.Add(new Message("test", DateTime.Now, textBox.Text, true));
            var DataReader = new Windows.Storage.Streams.DataReader(client.InputStream);
            byte[] getByte = new byte[5000];
            DataReader.ReadBytes(getByte);
            Encoding code = Encoding.GetEncoding("UTF-8");
            string RemoteData = code.GetString(getByte, 0, getByte.Length);
        }

        private async void TextBox_KeyUp(object sender, KeyRoutedEventArgs e)
        {
            if (e.OriginalKey == Windows.System.VirtualKey.Enter)
            {
                if (textBox.Text == "")
                {
                    MessageDialog i = new MessageDialog("发送内容不能为空！");
                    await i.ShowAsync();
                }
                else if (textBox.Text == "Chat")
                {
                    ChatMode = true;
                    HostName RemoteHost = new HostName("172.18.70.124");
                    client = await InitialNetwork(RemoteHost);
                }
                else if (textBox.Text == "Turing")
                {
                    ChatMode = false;
                }
                else if (ChatMode)
                {
                    Chat(client);
                }
                else
                {
                    Turing(textBox.Text);
                    //发送完消息后，清空消息框
                }
                textBox.Text = "";
            }
        }

        private async void Button_Click(object sender, RoutedEventArgs e)
        {
            if (textBox.Text == "")
            {
                MessageDialog i = new MessageDialog("发送内容不能为空！");
                await i.ShowAsync();
            }
            else
            {
                Turing(textBox.Text);
                //发送完消息后，清空消息框
                textBox.Text = "";
            }
        }
    }
}
