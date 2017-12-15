using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Atos.BLL;
using Atos.Classes;
using Atos.DBAccess;
using Newtonsoft.Json.Linq;
using Utility;

namespace AtosServerV2
{
    class Program
    {
        

        static void Main(string[] args)
        {
            Console.WriteLine("Simple TCP test server");

            IPAddress ip = IPAddress.Parse(ConfigurationManager.AppSettings["IP"]);
            int port = Convert.ToInt32(ConfigurationManager.AppSettings["Port"]);

            Console.WriteLine(" >> " + "Server Started");
            Console.WriteLine(" >> " + "IP: " + ip);
            Console.WriteLine(" >> " + "Port: " + port);

            Server.OutToConsole = true;
            Server.OutToDb = true;
            Server.StartServer(ip, port);
        }
    }
}
