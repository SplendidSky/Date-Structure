using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HTTPTest1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string url = "http://soj.sysu.edu.cn";
            var request = (HttpWebRequest)WebRequest.Create(url);
            var respone = (HttpWebResponse)request.GetResponse();
            Stream stream = respone.GetResponseStream();
            StreamReader sr = new StreamReader(stream);
            string content = sr.ReadToEnd();
            webBrowser1.DocumentText = content;
        }

        private void webBrowser1_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            var url = "http://soj.sysu.edu.cn/action.php?act=Login";
            string prev = string.Empty;
            for (int i = 0; i < 100; i++)
            {
                var username = "spendidsky";
                var password = "CHENweichen";
                
            }
        }
    }
}
