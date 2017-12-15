using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Atos.BLL;
using Atos.Classes;
using Utility;

namespace Atos.TestServerM3
{
    public partial class Form1 : Form
    {
        private IPAddress _ip;
        private int _port;

        private Thread _sThread;

        List<string> msgs = Server.Output.Reverse().Take(300).ToList();

        public Form1()
        {
            InitializeComponent();
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            try
            {
                _ip = IPAddress.Parse(txtIp.Text);
                _port = Convert.ToInt32(txtPort.Text);

                _sThread = new Thread(StartServer);
                _sThread.IsBackground = true;
                _sThread.Start();

                btnStart.Enabled = false;
                btnAddStorage.Enabled = true;

                listMsg.DataSource = msgs;

                timer1.Enabled = true;
            }
            catch (Exception ex)
            {
                _sThread.Abort();

                btnStart.Enabled = true;
                btnAddStorage.Enabled = false;

                timer1.Enabled = false;

                Server.OutToDb = true;
                Server.OutToList = false;

                MessageBox.Show(ex.Message);
                Environment.Exit(0);
            }
        }

        public void StartServer()
        {
            try
            {
                Server.OutToDb = false;
                Server.OutToList = true;
                Server.OutToConsole = false;
                Server.StartServer(_ip, _port);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                Environment.Exit(0);
            }

        }

        private void btnAddStorage_Click(object sender, EventArgs e)
        {
            Storage newStorage = new Storage()
            {
                Id = (int) numId.Value,
                Task = (int) numTsk.Value,
                Arg0 = (int) numArg0.Value,
                Arg1 = (int) numArg1.Value,
                Arg2 = (int) numArg2.Value,
                Arg3 = (int) numArg3.Value
            };
            Cache.UpdateStorage(newStorage);
            BindingList<Storage> storages = new BindingList<Storage>(Cache.CachedData);
            gridStorage.DataSource = storages;
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            Cache.CachedData.Clear();

            BindingList<Storage> storages = new BindingList<Storage>(Cache.CachedData);
            gridStorage.DataSource = storages;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //string firstBefore = msgs.FirstOrDefault();

            msgs = Server.Output.Take(300).Reverse().ToList();

            //string firstAfter = msgs.FirstOrDefault();

            //if (firstBefore != null && firstBefore != firstAfter)
            //{
            //    listMsg.DataSource = msgs;
            //}
            //else if (firstBefore == null && firstAfter != null)
            //{
            //    listMsg.DataSource = msgs;
            //}

            listMsg.DataSource = msgs;

            BindingList<Storage> storages = new BindingList<Storage>(Cache.CachedData);
            gridStorage.DataSource = storages;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Server.CloseServer();
            _sThread?.Abort();
            Environment.Exit(0);
        }
    }
}
