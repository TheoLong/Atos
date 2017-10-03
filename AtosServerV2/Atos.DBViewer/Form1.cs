using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.Entity;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Message = Atos.DBContext.Message;

namespace Atos.DBViewer
{
    public partial class DBViewer : Form
    {
        private static bool refresh = false;

        private int startsecond = 0;

        static IQueryable<Message> msgList = DBAccess.DBAccess.GetAllMessages();

        public DBViewer()
        {
            InitializeComponent();

            ddlType.Items.Add("All");
            ddlType.Items.Add("Store Request");
            ddlType.Items.Add("Retrieve Request");
            ddlType.Items.Add("Sent");
            ddlType.Items.Add("Report");
            ddlType.Items.Add("Test");

            ddlSourceId.Items.Add("All");

            ddlType.SelectedIndex = 0;
            ddlSourceId.SelectedIndex = 0;

            timer1.Enabled = false;
            timer2.Enabled = true;

            this.gridData.DataError += this.DataGridView_DataError;

            DBAccess.DBAccess.UpdateLegacy();
        }

        public object Select(IQueryable<Message> m)
        {
            return m.Select(x => new
            {
                x.SourceId,
                x.TargetId,
                x.SequenceNumber,
                x.Hex,
                x.Hash,
                x.PayloadRaw,
                x.PayloadType,
                x.PayloadTaskNumber,
                x.PayloadArg0,
                x.PayloadArg1,
                x.PayloadArg2,
                x.PayloadArg3,
                x.BadMessage,
                x.DateTime
            }).ToList();
        }

        private void DataGridView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            return;
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            //try
            //{
            GetMessages();
            //}
            //catch (Exception exception)
            //{
            //}

            //timer1.Enabled = !timer1.Enabled;

            //if (timer1.Enabled)
            //{
            //    btnRefresh.Text = "Stop";
            //    btnClear.Enabled = false;
            //}
            //else
            //{
            //    btnRefresh.Text = "Refresh";
            //    btnClear.Enabled = true;
            //}
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            DBAccess.DBAccess.DeleteAllMessages();
            ddlType.SelectedIndex = 0;

            msgList = DBAccess.DBAccess.GetAllMessages();

            gridData.DataSource = msgList.ToList();
        }

        public static List<int> GetDistinctClientIds()
        {
            return msgList.Where(s => s.Legacy == false && s.SourceId > 0)
                .Select(m => m.SourceId).Distinct().ToList();
        }

        public static int GetPostCountByClientId(int id)
        {
            return msgList.Count(m => m.Legacy == false && m.SourceId == id && m.PayloadType == "s");
        }

        public static int GetGetCountByClientId(int id)
        {

            return msgList.Count(m => m.Legacy == false && m.SourceId == id && m.PayloadType == "r");

        }

        public static int GetSentCountByClientId(int id)
        {

            return msgList.Count(m => m.Legacy == false && m.TargetId == id && m.PayloadType == "a");

        }

        public static List<int> GetSequenceListById(int id)
        {

            return msgList.Where(m => m.Legacy == false && m.SourceId == id).OrderByDescending(m => m.DateTime).Select(m => m.SequenceNumber).ToList();

        }

        public static int GetIntervalBySourceId(int srcId)
        {
            int msgCount10sec =
                msgList.Where(m => m.Legacy == false)
                    .Count(m => m.SourceId == srcId && m.DateTime > DbFunctions.AddSeconds(DateTime.UtcNow, -10));
            if (msgCount10sec > 0)
            {
                return 10000 / msgCount10sec;
            }
            return 0;
        }

        private void RefreshClient()
        {
            List<int> idList = GetDistinctClientIds();
            listClient.Clear();

            if (ddlSourceId.SelectedIndex < 1)
            {
                ddlSourceId.Items.Clear();
                ddlSourceId.Items.Add("All");
                ddlSourceId.SelectedIndex = 0;
            }

            foreach (var id in idList)
            {
                Client newClient = new Client()
                {
                    Id = id,
                    Post = GetPostCountByClientId(id),
                    Get = GetGetCountByClientId(id),
                    Sent = GetSentCountByClientId(id),
                    Interval = GetIntervalBySourceId(id),
                    MissingSequence = GetMissingSequenceById(id)
                };

                if (ddlSourceId.SelectedIndex < 1)
                {
                    ddlSourceId.Items.Add(id);
                }

                listClient.Items.Add(GetClientText(newClient));

            }
        }

        private string GetClientText(Client client)
        {
            return "Id: " + client.Id
                   + " Post: " + client.Post
                   + " Get: " + client.Get
                   + " Sent: " + client.Sent
                   + " Average Interval: " + client.Interval
                   + " Missing Sequences: {" + string.Join(", ", client.MissingSequence) + "}"
                   + "\n";
        }

        private List<int> GetMissingSequenceById(int id)
        {
            List<int> seqList = GetSequenceListById(id);
            return Enumerable.Range(seqList.Last(), seqList.Count).Except(seqList).ToList();
        }

        public static object GetMessagesBySourceId(int sourceId)
        {

            return msgList.Where(s => s.Legacy == false && s.SourceId == sourceId)
                .OrderByDescending(m => m.DateTime)
                .Select(x => new
                {
                    x.SourceId,
                    x.TargetId,
                    x.SequenceNumber,
                    x.Hex,
                    x.Hash,
                    x.PayloadRaw,
                    x.PayloadType,
                    x.PayloadTaskNumber,
                    x.PayloadArg0,
                    x.PayloadArg1,
                    x.PayloadArg2,
                    x.PayloadArg3,
                    x.BadMessage,
                    x.DateTime
                }).Take(1000).ToList();

        }

        public static object GetMessagesByType(string type)
        {
            var a = msgList.Where(m => m.Legacy == false && m.PayloadType.Equals(type))
                .OrderByDescending(m => m.DateTime);
            var b = a.Select(x => new
            {
                x.SourceId,
                x.TargetId,
                x.SequenceNumber,
                x.Hex,
                x.Hash,
                x.PayloadRaw,
                x.PayloadType,
                x.PayloadTaskNumber,
                x.PayloadArg0,
                x.PayloadArg1,
                x.PayloadArg2,
                x.PayloadArg3,
                x.BadMessage,
                x.DateTime
            }).Take(1000);
                
            var c = b.ToList();

            return c;
        }

        public static object GetTestMsgs()
        {
            return msgList.Where(m => m.Legacy == false && m.PayloadType == "s" && m.PayloadTaskNumber == 32)
                .OrderByDescending(m => m.DateTime)
                .Select(x => new
                {
                    x.SourceId,
                    x.TargetId,
                    x.SequenceNumber,
                    x.Hex,
                    x.Hash,
                    x.PayloadRaw,
                    x.PayloadType,
                    x.PayloadTaskNumber,
                    x.PayloadArg0,
                    x.PayloadArg1,
                    x.PayloadArg2,
                    x.PayloadArg3,
                    x.BadMessage,
                    x.DateTime
                }).Take(1000).ToList();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            GetMessages();
        }

        private void GetMessages()
        {
            msgList = DBAccess.DBAccess.GetAllMessages();

            switch (ddlType.SelectedItem.ToString())
            {
                case "All":
                    switch (ddlSourceId.SelectedIndex)
                    {
                        case 0:

                            gridData.DataSource = Select(msgList);
                            break;
                        default:
                            gridData.DataSource =
                                GetMessagesBySourceId(
                                    Convert.ToInt32(ddlSourceId.SelectedItem));
                            break;
                    }

                    break;
                case "Store Request":
                    gridData.DataSource = GetMessagesByType("s");
                    break;
                case "Retrieve Request":
                    gridData.DataSource = GetMessagesByType("r");
                    break;
                case "Sent":
                    gridData.DataSource = GetMessagesByType("a");
                    break;
                case "Report":
                    gridData.DataSource = GetMessagesByType("m");
                    break;
                case "Test":
                    gridData.DataSource = GetTestMsgs();
                    break;
                default:
                    gridData.DataSource = msgList;
                    break;
            }

            gridData.Columns["SourceId"].Width = 30;
            gridData.Columns["SourceId"].HeaderText = "src";

            gridData.Columns["TargetId"].Width = 30;
            gridData.Columns["TargetId"].HeaderText = "tgt";

            gridData.Columns["SequenceNumber"].Width = 50;
            gridData.Columns["SequenceNumber"].HeaderText = "seq";

            gridData.Columns["Hex"].Width = 80;
            gridData.Columns["Hex"].HeaderText = "hex";

            gridData.Columns["Hash"].Width = 80;
            gridData.Columns["Hash"].HeaderText = "hash";

            gridData.Columns["PayloadRaw"].Width = 80;
            gridData.Columns["PayloadRaw"].HeaderText = "json";

            gridData.Columns["PayloadType"].Width = 30;
            gridData.Columns["PayloadType"].HeaderText = "type";

            gridData.Columns["PayloadTaskNumber"].Width = 30;
            gridData.Columns["PayloadTaskNumber"].HeaderText = "tsk";

            gridData.Columns["PayloadArg0"].Width = 75;
            gridData.Columns["PayloadArg0"].HeaderText = "0";

            gridData.Columns["PayloadArg1"].Width = 75;
            gridData.Columns["PayloadArg1"].HeaderText = "1";

            gridData.Columns["PayloadArg2"].Width = 75;
            gridData.Columns["PayloadArg2"].HeaderText = "2";

            gridData.Columns["PayloadArg3"].Width = 75;
            gridData.Columns["PayloadArg3"].HeaderText = "3";

            gridData.Columns["BadMessage"].Width = 30;
            gridData.Columns["BadMessage"].HeaderText = "bad";

            gridData.Columns["DateTime"].DefaultCellStyle.Format = "yyyy-MM-dd hh:mm:ss.fff";
            gridData.Columns["DateTime"].Width = 150;

            foreach (DataGridViewRow rw in gridData.Rows)
            {
                if (rw.Cells[6].Value != null)
                {
                    if (rw.Cells[6].Value.Equals("r"))
                    {
                        rw.DefaultCellStyle.BackColor = Color.DeepSkyBlue;
                    }
                    else if (rw.Cells[6].Value.Equals("s"))
                    {
                        rw.DefaultCellStyle.BackColor = Color.Yellow;
                    }
                    else if (rw.Cells[6].Value.Equals("a"))
                    {
                        rw.DefaultCellStyle.BackColor = Color.Lime;
                    }
                    else if (rw.Cells[6].Value.Equals("m"))
                    {
                        rw.DefaultCellStyle.BackColor = Color.MediumPurple;
                    }
                }

                if (rw.Cells[7].Value != null)
                {
                    if (Convert.ToInt32(rw.Cells[7].Value) == 32)
                    {
                        if (Convert.ToInt32(rw.Cells[8].Value) == 112)
                        {
                            rw.DefaultCellStyle.BackColor = Color.Aqua;
                        }
                        else
                        {
                            rw.DefaultCellStyle.BackColor = Color.Crimson;
                        }
                    }
                }

                if (Convert.ToInt32(rw.Cells[0].Value) >= 1)
                {
                    rw.Cells[0].Style.BackColor = Color.FromArgb(255 / Convert.ToInt32(rw.Cells[0].Value), 128,
                        Convert.ToInt32(rw.Cells[0].Value) * 255 % 255);
                }
                else
                {
                    rw.Cells[0].Style.BackColor = Color.White;
                }

                if (Convert.ToInt32(rw.Cells[1].Value) >= 1)
                {
                    rw.Cells[1].Style.BackColor = Color.FromArgb(255 / Convert.ToInt32(rw.Cells[1].Value), 128,
                        Convert.ToInt32(rw.Cells[0].Value) * 255 % 255);
                }
                else
                {
                    rw.Cells[1].Style.BackColor = Color.White;
                }

                if (Convert.ToInt32(rw.Cells[12].Value) >= 1)
                {
                    rw.DefaultCellStyle.BackColor = Color.Red;
                }
            }

            RefreshClient();
        }

        private void ddlType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ddlType.SelectedIndex == 0)
            {
                ddlSourceId.Enabled = true;
            }
            else
            {
                ddlSourceId.Enabled = false;
            }
        }

        private void chkAuto_CheckedChanged(object sender, EventArgs e)
        {
            timer1.Enabled = chkAuto.Checked;
            btnRefresh.Enabled = !chkAuto.Checked;

            ddlSourceId.Enabled = !chkAuto.Checked;
            ddlType.Enabled = !chkAuto.Checked;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            UpdateTime();
        }

        private void UpdateTime()
        {
            startsecond++;
            TimeSpan t = TimeSpan.FromSeconds(startsecond);

            string answer = $"{t.Hours:D2}:{t.Minutes:D2}:{t.Seconds:D2}";
            lblTimeElapsed.Text = answer;
        }
    }

    class Client
    {
        public int Id { get; set; }
        public int Post { get; set; }
        public int Get { get; set; }
        public int Sent { get; set; }
        public int Interval { get; set; }
        public List<int> MissingSequence { get; set; }
    }
}
