using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace HTTPTest2
{
    class Program
    {
        public static CountdownEvent cde = new CountdownEvent(0);
        public static ConcurrentDictionary<long, byte[]> dic = new ConcurrentDictionary<long, byte[]>();
        public static string url = "http://www.pncity.net/bbs/data/attachment/forum/201107/30/1901108yyd8gnrs2isadrr.jpg";

        static void Main(string[] args)
        {
            Console.WriteLine("\n********\n第1次比较\n*********");
            RunMultiTask();
            Console.WriteLine("\n********\n第2次比较\n*********");
            RunSingle();
            Console.Read();
        }

        static void RunMultiTask()
        {
            Stopwatch watch = Stopwatch.StartNew();

            int threadCount = 5;
            long start = 0;
            long end = 0;
            var total = GetSourceHead();

            if (total == 0)
                return;
            var pageSize = (int)Math.Ceiling((double)total / threadCount);

            cde.Reset(threadCount);

            Task[] tasks = new Task[threadCount];

            for (int i = 0; i < threadCount; i++)
            {
                start = i * pageSize;
                end = (i + 1) * pageSize - 1;
                if (end > total)
                    end = total;
                var obj = start + "|" + end;
                tasks[i] = Task.Run(() => new DownFile().DownTaskMulti(obj));
            }
            Task.WaitAll(tasks);
            var targetFile = @"C:\Users\Administrator\Desktop\大二下\" + url.Substring(url.LastIndexOf('/') + 1);
            FileStream fs = new FileStream(targetFile, FileMode.Create);
            var result = dic.Keys.OrderBy(i => i).ToList();
            foreach (var item in result)
            {
                fs.Write(dic[item], 0, dic[item].Length);
            }
            fs.Close();
            watch.Stop();
            Console.WriteLine("多线程：下载耗费时间：{0}", watch.Elapsed);
        }

        static void RunSingle()
        {
            Stopwatch watch = Stopwatch.StartNew();

            if (GetSourceHead() == 0)
                return;

            var request = (HttpWebRequest)HttpWebRequest.Create(url);
            var respone = (HttpWebResponse)request.GetResponse();
            var stream = respone.GetResponseStream();
            var outStream = new MemoryStream();
            var bytes = new byte[10240];
            int count = 0;
            while ((count = stream.Read(bytes, 0, bytes.Length)) != 0)
            {
                outStream.Write(bytes, 0, count);
            }

            var targetFile = @"C: \Users\Administrator\Desktop\大二下\" + url.Substring(url.LastIndexOf('/') + 1);
            FileStream fs = new FileStream(targetFile, FileMode.Create);
            fs.Write(outStream.ToArray(), 0, (int)outStream.Length);
            outStream.Close();
            respone.Close();
            fs.Close();
            watch.Stop();
            Console.WriteLine("不用线程，下载耗费时间：{0}", watch.Elapsed);
        }

        public static long GetSourceHead()
        {
            var request = (HttpWebRequest)HttpWebRequest.Create(url);
            request.Method = "Head";
            request.Timeout = 3000;

            var respone = (HttpWebResponse)request.GetResponse();
            var code = respone.StatusCode;

            if (code != HttpStatusCode.OK)
            {
                Console.WriteLine("下载资源无效!");
                return 0;
            }

            var total = respone.ContentLength;
            Console.WriteLine("当前资源大小为：" + total);
            respone.Close();
            return total;
        }
    }

    public class DownFile
    {
        public void DownTaskMulti(object obj)
        {
            var single = obj.ToString().Split('|');
            long start = Convert.ToInt64(single.FirstOrDefault());
            long end = Convert.ToInt64(single.LastOrDefault());
            var request = (HttpWebRequest)HttpWebRequest.Create(Program.url);
            request.AddRange(start, end);
            var response = (HttpWebResponse)request.GetResponse();
            var stream = response.GetResponseStream();
            var outStream = new MemoryStream();
            var bytes = new byte[10240];
            int count = 0;
            while ((count = stream.Read(bytes, 0, bytes.Length)) != 0)
            {
                outStream.Write(bytes, 0, count);
            }
            outStream.Close();
            response.Close();
            Program.dic.TryAdd(start, outStream.ToArray());
            Program.cde.Signal();
        }
    }
}
