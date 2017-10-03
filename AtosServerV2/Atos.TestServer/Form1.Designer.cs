﻿namespace Atos.TestServer
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.chkClients = new System.Windows.Forms.CheckedListBox();
            this.numTimer = new System.Windows.Forms.NumericUpDown();
            this.btnStart = new System.Windows.Forms.Button();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.lblPort = new System.Windows.Forms.Label();
            this.lblIp = new System.Windows.Forms.Label();
            this.txtIp = new System.Windows.Forms.TextBox();
            this.lblPerSec = new System.Windows.Forms.Label();
            this.btnSend = new System.Windows.Forms.Button();
            this.numArg3 = new System.Windows.Forms.NumericUpDown();
            this.numArg2 = new System.Windows.Forms.NumericUpDown();
            this.numArg1 = new System.Windows.Forms.NumericUpDown();
            this.numArg0 = new System.Windows.Forms.NumericUpDown();
            this.numTsk = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.numSeq = new System.Windows.Forms.NumericUpDown();
            this.lblSeq = new System.Windows.Forms.Label();
            this.ddlError = new System.Windows.Forms.ComboBox();
            this.lblErrorType = new System.Windows.Forms.Label();
            this.btnAddJsonMsg = new System.Windows.Forms.Button();
            this.gridMsg = new System.Windows.Forms.DataGridView();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btnAddRandom = new System.Windows.Forms.Button();
            this.btnClrMsg = new System.Windows.Forms.Button();
            this.lblClientReport = new System.Windows.Forms.Label();
            this.lblServerSent = new System.Windows.Forms.Label();
            this.lblClientData = new System.Windows.Forms.Label();
            this.lblServerData = new System.Windows.Forms.Label();
            this.lblPendingData = new System.Windows.Forms.Label();
            this.lblPending = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numTimer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg0)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTsk)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numSeq)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridMsg)).BeginInit();
            this.SuspendLayout();
            // 
            // chkClients
            // 
            this.chkClients.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.chkClients.FormattingEnabled = true;
            this.chkClients.Location = new System.Drawing.Point(15, 632);
            this.chkClients.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.chkClients.Name = "chkClients";
            this.chkClients.Size = new System.Drawing.Size(200, 106);
            this.chkClients.TabIndex = 5;
            this.chkClients.SelectedIndexChanged += new System.EventHandler(this.chkClients_SelectedIndexChanged);
            // 
            // numTimer
            // 
            this.numTimer.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numTimer.Location = new System.Drawing.Point(546, 687);
            this.numTimer.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.numTimer.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.numTimer.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numTimer.Name = "numTimer";
            this.numTimer.Size = new System.Drawing.Size(100, 22);
            this.numTimer.TabIndex = 10;
            this.numTimer.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            // 
            // btnStart
            // 
            this.btnStart.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnStart.Location = new System.Drawing.Point(451, 673);
            this.btnStart.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(80, 50);
            this.btnStart.TabIndex = 20;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // txtPort
            // 
            this.txtPort.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.txtPort.Location = new System.Drawing.Point(405, 686);
            this.txtPort.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.txtPort.MaxLength = 10;
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(40, 22);
            this.txtPort.TabIndex = 19;
            this.txtPort.Text = "2000";
            // 
            // lblPort
            // 
            this.lblPort.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblPort.AutoSize = true;
            this.lblPort.Location = new System.Drawing.Point(361, 690);
            this.lblPort.Name = "lblPort";
            this.lblPort.Size = new System.Drawing.Size(38, 17);
            this.lblPort.TabIndex = 18;
            this.lblPort.Text = "Port:";
            // 
            // lblIp
            // 
            this.lblIp.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblIp.AutoSize = true;
            this.lblIp.Location = new System.Drawing.Point(225, 690);
            this.lblIp.Name = "lblIp";
            this.lblIp.Size = new System.Drawing.Size(24, 17);
            this.lblIp.TabIndex = 17;
            this.lblIp.Text = "IP:";
            // 
            // txtIp
            // 
            this.txtIp.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.txtIp.Location = new System.Drawing.Point(255, 686);
            this.txtIp.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.txtIp.MaxLength = 20;
            this.txtIp.Name = "txtIp";
            this.txtIp.Size = new System.Drawing.Size(100, 22);
            this.txtIp.TabIndex = 16;
            this.txtIp.Text = "192.168.137.1";
            // 
            // lblPerSec
            // 
            this.lblPerSec.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblPerSec.AutoSize = true;
            this.lblPerSec.Location = new System.Drawing.Point(651, 690);
            this.lblPerSec.Name = "lblPerSec";
            this.lblPerSec.Size = new System.Drawing.Size(54, 17);
            this.lblPerSec.TabIndex = 21;
            this.lblPerSec.Text = "Interval";
            // 
            // btnSend
            // 
            this.btnSend.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnSend.Location = new System.Drawing.Point(709, 673);
            this.btnSend.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(80, 50);
            this.btnSend.TabIndex = 22;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // numArg3
            // 
            this.numArg3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numArg3.Location = new System.Drawing.Point(777, 630);
            this.numArg3.Margin = new System.Windows.Forms.Padding(4);
            this.numArg3.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg3.Name = "numArg3";
            this.numArg3.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.numArg3.Size = new System.Drawing.Size(111, 22);
            this.numArg3.TabIndex = 37;
            this.numArg3.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numArg2
            // 
            this.numArg2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numArg2.Location = new System.Drawing.Point(659, 630);
            this.numArg2.Margin = new System.Windows.Forms.Padding(4);
            this.numArg2.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg2.Name = "numArg2";
            this.numArg2.Size = new System.Drawing.Size(111, 22);
            this.numArg2.TabIndex = 36;
            this.numArg2.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numArg1
            // 
            this.numArg1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numArg1.Location = new System.Drawing.Point(540, 630);
            this.numArg1.Margin = new System.Windows.Forms.Padding(4);
            this.numArg1.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg1.Name = "numArg1";
            this.numArg1.Size = new System.Drawing.Size(111, 22);
            this.numArg1.TabIndex = 35;
            this.numArg1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numArg0
            // 
            this.numArg0.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numArg0.Location = new System.Drawing.Point(421, 630);
            this.numArg0.Margin = new System.Windows.Forms.Padding(4);
            this.numArg0.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg0.Name = "numArg0";
            this.numArg0.Size = new System.Drawing.Size(111, 22);
            this.numArg0.TabIndex = 34;
            this.numArg0.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numTsk
            // 
            this.numTsk.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numTsk.Location = new System.Drawing.Point(344, 630);
            this.numTsk.Margin = new System.Windows.Forms.Padding(4);
            this.numTsk.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numTsk.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numTsk.Name = "numTsk";
            this.numTsk.Size = new System.Drawing.Size(48, 22);
            this.numTsk.TabIndex = 33;
            this.numTsk.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(311, 632);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 17);
            this.label2.TabIndex = 32;
            this.label2.Text = "tsk:";
            // 
            // numSeq
            // 
            this.numSeq.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numSeq.Location = new System.Drawing.Point(255, 630);
            this.numSeq.Margin = new System.Windows.Forms.Padding(4);
            this.numSeq.Maximum = new decimal(new int[] {
            99999,
            0,
            0,
            0});
            this.numSeq.Name = "numSeq";
            this.numSeq.Size = new System.Drawing.Size(48, 22);
            this.numSeq.TabIndex = 27;
            this.numSeq.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // lblSeq
            // 
            this.lblSeq.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblSeq.AutoSize = true;
            this.lblSeq.Location = new System.Drawing.Point(222, 632);
            this.lblSeq.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSeq.Name = "lblSeq";
            this.lblSeq.Size = new System.Drawing.Size(35, 17);
            this.lblSeq.TabIndex = 26;
            this.lblSeq.Text = "seq:";
            // 
            // ddlError
            // 
            this.ddlError.FormattingEnabled = true;
            this.ddlError.Items.AddRange(new object[] {
            "None",
            "Extra Byte(s)",
            "Incomplete",
            "Flip Byte(s)",
            "Missing"});
            this.ddlError.Location = new System.Drawing.Point(1019, 632);
            this.ddlError.Margin = new System.Windows.Forms.Padding(4);
            this.ddlError.Name = "ddlError";
            this.ddlError.Size = new System.Drawing.Size(132, 24);
            this.ddlError.TabIndex = 39;
            // 
            // lblErrorType
            // 
            this.lblErrorType.AutoSize = true;
            this.lblErrorType.Location = new System.Drawing.Point(931, 635);
            this.lblErrorType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblErrorType.Name = "lblErrorType";
            this.lblErrorType.Size = new System.Drawing.Size(80, 17);
            this.lblErrorType.TabIndex = 38;
            this.lblErrorType.Text = "Error Type:";
            // 
            // btnAddJsonMsg
            // 
            this.btnAddJsonMsg.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnAddJsonMsg.Location = new System.Drawing.Point(973, 672);
            this.btnAddJsonMsg.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnAddJsonMsg.Name = "btnAddJsonMsg";
            this.btnAddJsonMsg.Size = new System.Drawing.Size(100, 50);
            this.btnAddJsonMsg.TabIndex = 40;
            this.btnAddJsonMsg.Text = "Add  Message";
            this.btnAddJsonMsg.UseVisualStyleBackColor = true;
            this.btnAddJsonMsg.Click += new System.EventHandler(this.btnAddJsonMsg_Click);
            // 
            // gridMsg
            // 
            this.gridMsg.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridMsg.Location = new System.Drawing.Point(11, 379);
            this.gridMsg.Margin = new System.Windows.Forms.Padding(4);
            this.gridMsg.Name = "gridMsg";
            this.gridMsg.Size = new System.Drawing.Size(1147, 246);
            this.gridMsg.TabIndex = 41;
            // 
            // txtOutput
            // 
            this.txtOutput.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtOutput.Location = new System.Drawing.Point(11, 14);
            this.txtOutput.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.txtOutput.Multiline = true;
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.ReadOnly = true;
            this.txtOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtOutput.Size = new System.Drawing.Size(1145, 205);
            this.txtOutput.TabIndex = 42;
            this.txtOutput.TextChanged += new System.EventHandler(this.txtOutput_TextChanged);
            // 
            // timer1
            // 
            this.timer1.Interval = 500;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btnAddRandom
            // 
            this.btnAddRandom.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnAddRandom.Location = new System.Drawing.Point(840, 672);
            this.btnAddRandom.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnAddRandom.Name = "btnAddRandom";
            this.btnAddRandom.Size = new System.Drawing.Size(128, 50);
            this.btnAddRandom.TabIndex = 44;
            this.btnAddRandom.Text = "Add  Random Message";
            this.btnAddRandom.UseVisualStyleBackColor = true;
            this.btnAddRandom.Click += new System.EventHandler(this.btnAddRandom_Click);
            // 
            // btnClrMsg
            // 
            this.btnClrMsg.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnClrMsg.Location = new System.Drawing.Point(1079, 672);
            this.btnClrMsg.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnClrMsg.Name = "btnClrMsg";
            this.btnClrMsg.Size = new System.Drawing.Size(67, 50);
            this.btnClrMsg.TabIndex = 45;
            this.btnClrMsg.Text = "Clear";
            this.btnClrMsg.UseVisualStyleBackColor = true;
            this.btnClrMsg.Click += new System.EventHandler(this.btnClrMsg_Click);
            // 
            // lblClientReport
            // 
            this.lblClientReport.AutoSize = true;
            this.lblClientReport.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblClientReport.Location = new System.Drawing.Point(12, 235);
            this.lblClientReport.Name = "lblClientReport";
            this.lblClientReport.Size = new System.Drawing.Size(181, 29);
            this.lblClientReport.TabIndex = 46;
            this.lblClientReport.Text = "Client Report:";
            // 
            // lblServerSent
            // 
            this.lblServerSent.AutoSize = true;
            this.lblServerSent.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblServerSent.Location = new System.Drawing.Point(12, 276);
            this.lblServerSent.Name = "lblServerSent";
            this.lblServerSent.Size = new System.Drawing.Size(165, 29);
            this.lblServerSent.TabIndex = 47;
            this.lblServerSent.Text = "Server Sent:";
            // 
            // lblClientData
            // 
            this.lblClientData.AutoSize = true;
            this.lblClientData.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblClientData.Location = new System.Drawing.Point(208, 235);
            this.lblClientData.Name = "lblClientData";
            this.lblClientData.Size = new System.Drawing.Size(90, 29);
            this.lblClientData.TabIndex = 48;
            this.lblClientData.Text = "<N/A>";
            // 
            // lblServerData
            // 
            this.lblServerData.AutoSize = true;
            this.lblServerData.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblServerData.Location = new System.Drawing.Point(208, 276);
            this.lblServerData.Name = "lblServerData";
            this.lblServerData.Size = new System.Drawing.Size(90, 29);
            this.lblServerData.TabIndex = 49;
            this.lblServerData.Text = "<N/A>";
            // 
            // lblPendingData
            // 
            this.lblPendingData.AutoSize = true;
            this.lblPendingData.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblPendingData.Location = new System.Drawing.Point(208, 317);
            this.lblPendingData.Name = "lblPendingData";
            this.lblPendingData.Size = new System.Drawing.Size(90, 29);
            this.lblPendingData.TabIndex = 51;
            this.lblPendingData.Text = "<N/A>";
            // 
            // lblPending
            // 
            this.lblPending.AutoSize = true;
            this.lblPending.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblPending.Location = new System.Drawing.Point(12, 317);
            this.lblPending.Name = "lblPending";
            this.lblPending.Size = new System.Drawing.Size(129, 29);
            this.lblPending.TabIndex = 50;
            this.lblPending.Text = "Pending: ";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1163, 747);
            this.Controls.Add(this.lblPendingData);
            this.Controls.Add(this.lblPending);
            this.Controls.Add(this.lblServerData);
            this.Controls.Add(this.lblClientData);
            this.Controls.Add(this.lblServerSent);
            this.Controls.Add(this.lblClientReport);
            this.Controls.Add(this.btnClrMsg);
            this.Controls.Add(this.btnAddRandom);
            this.Controls.Add(this.txtOutput);
            this.Controls.Add(this.gridMsg);
            this.Controls.Add(this.btnAddJsonMsg);
            this.Controls.Add(this.ddlError);
            this.Controls.Add(this.lblErrorType);
            this.Controls.Add(this.numArg3);
            this.Controls.Add(this.numArg2);
            this.Controls.Add(this.numArg1);
            this.Controls.Add(this.numArg0);
            this.Controls.Add(this.numTsk);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.numSeq);
            this.Controls.Add(this.lblSeq);
            this.Controls.Add(this.btnSend);
            this.Controls.Add(this.lblPerSec);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.txtPort);
            this.Controls.Add(this.lblPort);
            this.Controls.Add(this.lblIp);
            this.Controls.Add(this.txtIp);
            this.Controls.Add(this.numTimer);
            this.Controls.Add(this.chkClients);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.numTimer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg0)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTsk)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numSeq)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridMsg)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckedListBox chkClients;
        private System.Windows.Forms.NumericUpDown numTimer;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.Label lblPort;
        private System.Windows.Forms.Label lblIp;
        private System.Windows.Forms.TextBox txtIp;
        private System.Windows.Forms.Label lblPerSec;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.NumericUpDown numArg3;
        private System.Windows.Forms.NumericUpDown numArg2;
        private System.Windows.Forms.NumericUpDown numArg1;
        private System.Windows.Forms.NumericUpDown numArg0;
        private System.Windows.Forms.NumericUpDown numTsk;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numSeq;
        private System.Windows.Forms.Label lblSeq;
        private System.Windows.Forms.ComboBox ddlError;
        private System.Windows.Forms.Label lblErrorType;
        private System.Windows.Forms.Button btnAddJsonMsg;
        private System.Windows.Forms.DataGridView gridMsg;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btnAddRandom;
        private System.Windows.Forms.Button btnClrMsg;
        private System.Windows.Forms.Label lblClientReport;
        private System.Windows.Forms.Label lblServerSent;
        private System.Windows.Forms.Label lblClientData;
        private System.Windows.Forms.Label lblServerData;
        private System.Windows.Forms.Label lblPendingData;
        private System.Windows.Forms.Label lblPending;
    }
}

