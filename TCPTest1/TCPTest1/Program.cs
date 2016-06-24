using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace TCPTest1
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                Task.Run(() =>
                {
                    while (true)
                    {
                        try
                        {
                            Socket ClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Raw, ProtocolType.IP);

                            ClientSocket.Blocking = false;
                            ClientSocket.Bind(new IPEndPoint(IPAddress.Parse("10.101.194.195 "), 2000));
                            try
                            {
                                ClientSocket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.HeaderIncluded, 1);
                                byte[] IN = new byte[4] { 1, 0, 0, 0 };
                                byte[] OUT = new byte[4];

                                //低级别操作模式,接受所有的数据包，这一步是关键，必须把socket设成raw和IP   Level才可用SIO_RCVALL 
                                int ret_code = ClientSocket.IOControl(IOControlCode.ReceiveAll, IN, OUT);
                                ret_code = OUT[0] + OUT[1] + OUT[2] + OUT[3];//把4个8位字节合成一个32位整数 
                                                                             //if(ret_code   !=   0)   ret_value   =   false; 
                            }
                            catch (SocketException)
                            {
                                //ret_value   =   false; 
                                MessageBox.Show("sdfsf ");
                            }

                            // IPEndPoint   ff   =   new   IPEndPoint(IPAddress.Parse( "10.101.64.174 "),2000); 
                            // EndPoint   rr   =   (EndPoint)ff; 
                            // ClientSocket.Bind(rr); 
                            //填充tcp_header 
                            ip_header iph = new ip_header();
                            tcp_header tcph = new tcp_header();
                            iph.Version = 4;
                            iph.comput_internet_header_length = false;
                            iph.type_service = 0;
                            iph.comput_internet_header_length = false;
                            iph.Identification = 149;
                            iph.Flags = 2;
                            iph.FragmentOffset = 0;
                            iph.TTL = 255;
                            iph.Protocol = 6;
                            iph.comput_header_checksum = true;
                            iph.HeaderChecksum = 25895;
                            iph.str_Destination_address = "64.233.161.99 ";
                            iph.str_Source_address = "10.101.64.174 ";

                            tcph.SourcePort = 2000;
                            tcph.DestinationPort = 80;
                            tcph.SequenceNumber = 2758944060;
                            tcph.AcknowledgmentNumber = 101;
                            tcph.Reserved = 0;
                            tcph.URG = false;
                            tcph.ACK = false;
                            tcph.PSH = false;
                            tcph.RST = false;
                            tcph.SYN = true;
                            tcph.FIN = false;
                            tcph.Window = 19200;
                            tcph.Checksum = 54523;
                            tcph.UrgentPointer = 0;

                            uint aa = BitConverter.ToUInt32(IPAddress.Parse("10.101.64.174 ").GetAddressBytes(), 0);
                            uint bb = BitConverter.ToUInt32(IPAddress.Parse(Dns.Resolve("www.google.com ").AddressList[0].ToString()).GetAddressBytes(), 0);

                            byte[] tt = tcph.encode(aa, bb);

                            iph.Data = tt;
                            byte[] qq = iph.encode();
                            // IPEndPoint   yy   =   new   IPEndPoint(IPAddress.Parse( "64.233.161.99 "),80); 
                            // 
                            // EndPoint   ww   =   (EndPoint)yy; 
                            IPEndPoint yy = new IPEndPoint(IPAddress.Parse("64.233.161.99 "), 80);

                            EndPoint ww = (EndPoint)yy;
                            //ClientSocket.Blocking   =   false; 
                            //ClientSocket.Bind( 
                            ClientSocket.SendTo(qq, ww);
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine(e.Data);
                        }
                    }
                });
            }
            Task.WaitAll();
        }
    }
}
