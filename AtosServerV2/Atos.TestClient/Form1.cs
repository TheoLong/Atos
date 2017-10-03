using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlTypes;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Atos.BLL;
using Atos.Classes;
using SimpleTCP;
using Utility;

namespace Atos.TestClient
{
    public partial class Form1 : Form
    {
        private string temp = string.Empty;

        private static SimpleTcpClient client;

        public delegate void UpdateTextCallback(string text);

        public Form1()
        {
            InitializeComponent();
            btnSendRaw.Enabled = false;
            btnSendPayload.Enabled = false;

            ddlTp.SelectedIndex = 0;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            client = new SimpleTcpClient(); //Instantiate the client
            client.StringEncoder = Encoding.UTF8; //Config
            client.DataReceived += Client_DataReceived; //Subscribe to the DataRecieved event.
            client.Connect(txtIP.Text, Convert.ToInt32(txtPort.Text)); //Connect to the server
            btnConnect.Enabled = false;

            btnSendRaw.Enabled = true;
            btnSendPayload.Enabled = true;
        }

        private void UpdateText(string text)
        {
            // Set the textbox text.
            txtOutput.Text += text + "\r\n";
        }

        private void Client_DataReceived(object sender, SimpleTCP.Message m)
        {
            //if (InvokeRequired)
            //{
            //    txtOutput.Text += "\nReceived(raw): " + m.MessageString + "\nReceived(hex): " + BitConverter.ToString(m.Data);
            //}

            txtOutput.Invoke(new UpdateTextCallback(this.UpdateText),
            new object[] { "\r\nReceived(raw): " + m.MessageString + "\r\nReceived(hex): " + BitConverter.ToString(m.Data) });

            //MessageBox.Show("\nReceived(raw): " + m.MessageString + "\nReceived(hex): " + BitConverter.ToString(m.Data));
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            client.Write(Encoding.ASCII.GetBytes(txtMsg.Text));
        }

        private void btnSendPayload_Click(object sender, EventArgs e)
        {
            //while (true)
            //{
                string payloadString = Json.CreateSendJson((int) numId.Value, (int) numSeq.Value,
                    ddlTp.SelectedItem.ToString(), (int) numTgt.Value,
                    (int) numTsk.Value, (int) numArg0.Value, (int) numArg1.Value, (int) numArg2.Value,
                    (int) numArg3.Value);

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
            //}
        }
    }
}
