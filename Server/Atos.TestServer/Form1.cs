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
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Atos.BLL;
using Atos.Classes;
using SimpleTCP;
using Utility;

namespace Atos.TestServer
{
    public partial class Form1 : Form
    {
        static List<TestMessage> msgList = new List<TestMessage>();

        private static SimpleTcpServer server;

        private IPAddress ip;
        private int port;

        public delegate void UpdateTextCallback(string text);
        public delegate void UpdateChkCallback(EndPoint ep);

        private Thread sThread;

        private Storage netstatus;

        public Form1()
        {
            InitializeComponent();
            btnSend.Enabled = false;
            timer1.Enabled = true;

            Console.SetOut(new TextBoxWriter(txtOutput));

            //gridMsg.DataSource = typeof(List<TestMessage>);
           
            GridDataBind();

            ddlError.SelectedIndex = 0;
        }

        private void GridDataBind()
        {
            gridMsg.DataSource = msgList.Where(x => x.Sent == false).Select(x => new { x.Error, x.Payload }).ToList(); ;
            
            foreach (DataGridViewRow rw in gridMsg.Rows)
            {
                if (Convert.ToInt32(rw.Cells[0].Value) == 4)
                {
                    rw.DefaultCellStyle.BackColor = Color.Red;
                }
                else if (Convert.ToInt32(rw.Cells[0].Value) == 3)
                {
                    rw.DefaultCellStyle.BackColor = Color.Yellow;
                }
                else if (Convert.ToInt32(rw.Cells[0].Value) == 2)
                {
                    rw.DefaultCellStyle.BackColor = Color.Yellow;
                }
                else if (Convert.ToInt32(rw.Cells[0].Value) == 1)
                {
                    rw.DefaultCellStyle.BackColor = Color.Yellow;
                }
                else if (Convert.ToInt32(rw.Cells[0].Value) == 0)
                {
                    rw.DefaultCellStyle.BackColor = Color.Lime;
                }
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            ip = IPAddress.Parse(txtIp.Text);
            port = Convert.ToInt32(txtPort.Text);

            sThread = new Thread(StartServer);
            sThread.Start();

            btnStart.Enabled = false;
        }

        public void StartServer()
        {
            Server.StartServer(ip, port);
        }

        private void AddClients()
        {
            foreach (var c in Server.AtosClients)
            {
                AddNewClient(c.Client.Client.RemoteEndPoint);
            }
        }

        private void AddNewClient(EndPoint ep)
        {
            foreach (var c in chkClients.Items)
            {
                if (ep.ToString() == c.ToString())
                {
                    return;
                }
            }
            chkClients.Items.Add(ep);
        }

        private void chkClients_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (chkClients.SelectedItems.Count == 0)
            {
                btnSend.Enabled = false;
            }
            else
            {
                if (chkClients.SelectedItems.Count > 0)
                {
                    btnSend.Enabled = true;
                }
            }
        }

        private void btnClrMsg_Click(object sender, EventArgs e)
        {
            msgList.Clear();
            GridDataBind();
        }

        private void btnAddJsonMsg_Click(object sender, EventArgs e)
        {
            AddMessage(false);
        }

        private void AddMessage(bool random)
        {
            bool miss = false;

            Random rnd = new Random();
            int newRan = rnd.Next(1, 254);
            byte newByte = Convert.ToByte(newRan);

            // create payload json string
            string replyPayload = Json.CreateReplyJson(
                (int) numSeq.Value,
                (int) numTsk.Value,
                (int) numArg0.Value,
                (int) numArg1.Value,
                (int) numArg2.Value,
                (int) numArg3.Value
            );

            if (random)
            {
                replyPayload = Json.CreateReplyJson(
                    (int) numSeq.Value,
                    rnd.Next(0, 256),
                    rnd.Next(0, 65535),
                    rnd.Next(0, 65535),
                    rnd.Next(0, 65535),
                    rnd.Next(0, 65535)
                );
            }

            numSeq.Value++;

            // create hash
            uint hash = Hash.HashTo(replyPayload + "\xFF");
            byte[] hashBytes = BitConverter.GetBytes(hash);
            var hashBytes4 = new byte[4];
            var startAt = hashBytes4.Length - hashBytes.Length;
            Buffer.BlockCopy(hashBytes, 0, hashBytes4, startAt, hashBytes.Length);

            // create reply bytes
            byte[][] replyByteArray = new[]
            {
                new byte[] {0xFF},
                hashBytes4,
                Encoding.ASCII.GetBytes(replyPayload),
                new byte[] {0xFF},
            };
            byte[] replyBytes = CombineByteArray(replyByteArray);

            int errorCode = rnd.Next(0, 5);
            if (!random)
            {
                errorCode = ddlError.SelectedIndex;
            }

            if (errorCode > 0)
            {
                if (errorCode == 1)
                {
                    var newList = replyBytes.ToList();
                    newList.RemoveAt(newList.Count - 1);
                    newList.Add(newByte);
                    newList.Add(0xFF);
                    replyBytes = newList.ToArray();
                }
                else if (errorCode == 2)
                {
                    var newList = replyBytes.ToList();
                    newList.RemoveAt(rnd.Next(1, 10));
                    replyBytes = newList.ToArray();
                }
                else if (errorCode == 3)
                {
                    newRan = rnd.Next(1, 254);
                    replyBytes[4] = Convert.ToByte(newRan);
                }
                else if (errorCode == 4)
                {
                    miss = true;
                }
            }


            TestMessage newMsg = new TestMessage()
            {
                Error = errorCode,
                Data = replyBytes,
                Payload = replyPayload,
                Missing = miss,
                Sent = false
            };

            msgList.Add(newMsg);

            lblPendingData.Text = "Total: " + msgList.Count(v => v.Sent == false && v.Missing == false) +
                                  " Good: " + msgList.Count(v => v.Sent == false && v.Error == 0) +
                                  " Bad: " + msgList.Count(v => v.Sent == false && v.Error > 0 && v.Error < 4) +
                                  " Missed: " + msgList.Count(v => v.Sent == false && v.Error == 4);

            //gridMsg.DataSource = typeof(List<TestMessage>);
            GridDataBind();
        }

        private void btnAddRandom_Click(object sender, EventArgs e)
        {
            AddMessage(true);
        }

        private void txtOutput_TextChanged(object sender, EventArgs e)
        {
            AddClients();
        }

        public static byte[] CombineByteArray(params byte[][] arrays)
        {
            byte[] rv = new byte[arrays.Sum(a => a.Length)];
            int offset = 0;
            foreach (byte[] array in arrays)
            {
                System.Buffer.BlockCopy(array, 0, rv, offset, array.Length);
                offset += array.Length;
            }
            return rv;
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            //timer1.Enabled = !timer1.Enabled;;
            //if (timer1.Enabled)
            //{
            //    btnSend.Text = "Stop";
            //}
            //else
            //{
            //    btnSend.Text = "Send";
            //}

            Thread t1 = new Thread(SendMessage);
            t1.Start();
        }

        private void SendMessage()
        {
            foreach (var c in chkClients.CheckedItems)
            {
                foreach (var a in Server.AtosClients)
                {
                    foreach (var m in msgList)
                    {
                        if (c.ToString() == a.Client.Client.RemoteEndPoint.ToString())
                        {
                            if (!m.Missing && !m.Sent)
                            {
                                Server.QueueB.Enqueue(new AtosMsgQ { Client = a.Client, Data = m.Data });
                            }
                            m.Sent = true;

                            lblServerData.Invoke(
                                new MethodInvoker(() => lblServerData.Text =
                                    "Total: " + msgList.Count(v => v.Sent == true && v.Missing == false) +
                                    " Good: " + msgList.Count(v => v.Sent == true && v.Error == 0) +
                                    " Bad: " + msgList.Count(v => v.Sent == true && v.Error > 0 && v.Error < 4) +
                                    " Missed: " + msgList.Count(v => v.Sent == true && v.Error == 4)));

                            lblPendingData.Invoke(
                                new MethodInvoker(() => lblPendingData.Text =
                                    "Total: " + msgList.Count(v => v.Sent == false && v.Missing == false) +
                                    " Good: " + msgList.Count(v => v.Sent == false && v.Error == 0) +
                                    " Bad: " + msgList.Count(v => v.Sent == false && v.Error > 0 && v.Error < 4) +
                                    " Missed: " + msgList.Count(v => v.Sent == false && v.Error == 4)));
                        }

                        //GridDataBind();

                        Thread.Sleep((int)numTimer.Value);
                    }
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            AddClients();
            netstatus = Cache.RetrieveStorage(4, 11);

            lblClientData.Text = "Total: " + netstatus.Arg0 + " Good: " + netstatus.Arg1 + " Bad: " + netstatus.Arg2 +
                                 " Missed: " + netstatus.Arg3;

            GridDataBind();
        }
    }

    public class TextBoxWriter : TextWriter
    {
        TextBox _output = null;

        public TextBoxWriter(TextBox output)
        {
            _output = output;
        }

        public override void Write(char value)
        {
            _output.Invoke(new MethodInvoker(() => _output.AppendText(value.ToString())));
        }

        public override Encoding Encoding
        {
            get { return System.Text.Encoding.UTF8; }
        }
    }

    public class TestMessage
    {
        public int Error { get; set; }
        public byte[] Data { get; set; }
        public string Payload { get; set; }
        public bool Missing { get; set; }
        public bool Sent { get; set; }
    }

    public class Client
    {
        public TcpClient Endpoint { get; set; }
        public int Id { get; set; }
        public int Total { get; set; }
        public int Good { get; set; }
        public int Corrupted { get; set; }
        public int Missing { get; set; }
    }
}
