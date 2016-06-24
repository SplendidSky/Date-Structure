using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 进程与线程
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                ProcessHelper.MainProcess();
            }
        }
    }

    public class ProcessHelper
    {
        public static void MainProcess()
        {
            ProcessHelper helper = new ProcessHelper();
            var result = helper.GetProcesses();
            helper.ShowProcess(result.ToArray());
            Console.Write("\n请输入您要查看的进程: ");
            helper.ShowProcessSingle(Console.ReadLine());
            Console.Write("\n请输入您要开启的程序:");
            var name = helper.StartProcess(Console.ReadLine());
        }

        public Process[] GetProcesses(string ip = "")
        {
            if (string.IsNullOrEmpty(ip))
                return Process.GetProcesses();

            return Process.GetProcesses(ip);
        }

        public void ShowProcess(Process[] process)
        {
            Console.WriteLine("进程ID\t进程名称\t物理内存\t启动时间\t文件名");

            foreach (var p in process)
            {
                try
                {
                    Console.WriteLine("{0}\t{1}\t{2}M\t{3}\t{4}", p.Id, p.ProcessName.Trim(), p.WorkingSet64 / 1024.0f / 1024.0f, p.StartTime, p.MainModule.FileName);
                }
                catch (Exception ex)
                {
                    //Console.WriteLine(ex.Message);
                }
            }
        }

        public void ShowProcessSingle(string processID)
        {
            Process process = Process.GetProcessById(Convert.ToInt32(processID));

            Console.WriteLine("\n\n您要查看的进程详细信息如下:\n");

            try
            {
                var module = process.MainModule;

                Console.WriteLine("文件名:{0}\n版本{1}\n描述{2}\n语言:{3}", module.FileName, module.FileVersionInfo.FileVersion, module.FileVersionInfo.FileDescription, module.FileVersionInfo.Language);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public string StartProcess(string fileName)
        {
            Process process = new Process();
            process.StartInfo = new ProcessStartInfo(fileName);
            process.Start();
            return process.ProcessName;
        }

        public void StopProcess(string processID)
        {
            var process = Process.GetProcessById(Convert.ToInt32(processID));

            try
            {
                process.CloseMainWindow();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }


}
