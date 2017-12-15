using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Atos.BLL;
using SimpleTCP;
using Utility;

namespace Atos.ControlPanel
{
    public partial class Form1 : Form
    {
        private static SimpleTcpClient client;

        public Form1()
        {
            InitializeComponent();

            client = new SimpleTcpClient(); //Instantiate the client
            client.StringEncoder = Encoding.UTF8; //Config
            client.Connect("192.168.1.1", 2000); //Connect to the server

            DBAccess.DBAccess.DeleteAllMessages();

            timer1.Enabled = true;
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            string payloadString = Json.CreateSendJson(0, 0, "s", 0, 79, -1, -1, -1, 21);
            SendPayload(payloadString);
            Thread.Sleep(500);
            payloadString = Json.CreateSendJson(0, 0, "s", 0, 89, -1, -1, -1, 21);
            SendPayload(payloadString);
        }

        private void btnEnd_Click(object sender, EventArgs e)
        {
            string payloadString = Json.CreateSendJson(0, 0, "s", 0, 79, -1, -1, -1, 50);
            SendPayload(payloadString);
            Thread.Sleep(500);
            payloadString = Json.CreateSendJson(0, 0, "s", 0, 89, -1, -1, -1, 50);
            SendPayload(payloadString);
            payloadString = Json.CreateSendJson(0, 0, "s", 0, 80, 50, 0, 0, 0);
            SendPayload(payloadString);
        }

        private void btnEStop_Click(object sender, EventArgs e)
        {
            string payloadString = Json.CreateSendJson(0, 0, "s", 0, 79, -1, -1, -1, 99);
            SendPayload(payloadString);
            Thread.Sleep(250);
            payloadString = Json.CreateSendJson(0, 0, "s", 0, 89, -1, -1, -1, 99);
            SendPayload(payloadString);
            Thread.Sleep(1000);
            payloadString = Json.CreateSendJson(0, 0, "s", 0, 255, 256, 256, 256, 256);
            SendPayload(payloadString);
        }

        private static void SendPayload(string payloadString)
        {
            uint hash = Hash.HashTo(payloadString + "\xFF");
            byte[] hashBytes = BitConverter.GetBytes(hash);

            // create reply bytes
            byte[][] replyByteArray = new[]
            {
                new byte[] {0xFF},
                hashBytes,
                Encoding.ASCII.GetBytes(payloadString),
                new byte[] {0xFF}
            };
            byte[] replyBytes = Server.CombineByteArray(replyByteArray);

            client.Write(replyBytes);
            Thread.Sleep(20);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            lblLoriStats.Text = Client.GetStatusByClientId(1, 63);
            lblCipangoStats.Text = Client.GetStatusByClientId(2, 73);
            lblCraneStats.Text = Client.GetStatusByClientId(3, 83);
            lblFactoryStats.Text = Client.GetStatusByClientId(4, 93);
        }
    }
}
