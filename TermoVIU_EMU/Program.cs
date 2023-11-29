using System;
using System.Threading;
using TermoVIUserver;

namespace TermoVIU_EMU 
{
    public class Program
    {
        static void Main(string[] args)
        {

            Console.WriteLine("TermoVIU Corp Emulator V0.1 - By Pacman Jan-2021");
            Console.WriteLine("======================================================");
            Console.WriteLine("");

            Thread t = new Thread(delegate ()
            {
                // replace the IP with your system IP Address...
                Server myserver = new Server("127.0.0.1", 8001);
            });
            t.Start();
            
            Console.WriteLine("Server Started ...");
        }
    }
}