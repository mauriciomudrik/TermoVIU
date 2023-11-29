using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using TermoVIUservice;

namespace TermoVIUserver 
{

    public class Server
    {

        TcpListener server = null;
        public int port;
        private string recBuffer;

        public Server(string ip, int port)
        {
            this.port = port;
            IPAddress localAddr = IPAddress.Parse(ip);
            server = new TcpListener(localAddr, port);
            server.Start();
            StartListener();
        }

        public void StartListener()
        {
            try
            {
                while (true)
                {
                    Console.WriteLine("Waiting for a connection at {0}...", port.ToString());
                    TcpClient client = server.AcceptTcpClient();
                    Console.WriteLine("Connected!");

                    Thread t = new Thread(new ParameterizedThreadStart(HandleDevice));
                    t.Start(client);
                }
            }
            catch (SocketException e)
            {
                Console.WriteLine("SocketException: {0}", e);
                server.Stop();
            }
        }

        public void HandleDevice(Object obj)
        {
            TVservice tvs = new TVservice();

            TcpClient client = (TcpClient)obj;
            var stream = client.GetStream();
            string imei = String.Empty;

            string data = null;
            Byte[] bytes = new Byte[256];
            int i;
            recBuffer = "";
            try
            {
                while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
                {
                    string hex = BitConverter.ToString(bytes);
                    data = Encoding.ASCII.GetString(bytes, 0, i);
                    recBuffer += data;
                    if(recBuffer.Contains("\n")) {
                        Console.WriteLine("{1}: Received: {0}", recBuffer, Thread.CurrentThread.ManagedThreadId); 
                        string myResponse = null;
                        if((myResponse = tvs.processCall(recBuffer))!=null) {
                            Console.WriteLine("Response has sent ..."); 
                            string str = myResponse;
                            Byte[] reply = System.Text.Encoding.ASCII.GetBytes(str);   
                            stream.Write(reply, 0, reply.Length);
                            Console.WriteLine("{1}: Sent: {0}", str, Thread.CurrentThread.ManagedThreadId);
                        }    
                        recBuffer = "";
                    }
                    
                }
            }
            catch(Exception e)
            {
                Console.WriteLine("Exception: {0}", e.ToString());
                client.Close();
            }
        }
    }
}