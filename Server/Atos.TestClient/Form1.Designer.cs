namespace Atos.TestClient
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
            this.lblIP = new System.Windows.Forms.Label();
            this.txtIP = new System.Windows.Forms.TextBox();
            this.lblPort = new System.Windows.Forms.Label();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.txtMsg = new System.Windows.Forms.TextBox();
            this.btnSendRaw = new System.Windows.Forms.Button();
            this.btnSendPayload = new System.Windows.Forms.Button();
            this.lblId = new System.Windows.Forms.Label();
            this.numId = new System.Windows.Forms.NumericUpDown();
            this.numSeq = new System.Windows.Forms.NumericUpDown();
            this.lblSeq = new System.Windows.Forms.Label();
            this.numTgt = new System.Windows.Forms.NumericUpDown();
            this.lblTgt = new System.Windows.Forms.Label();
            this.lblTp = new System.Windows.Forms.Label();
            this.ddlTp = new System.Windows.Forms.ComboBox();
            this.numArg0 = new System.Windows.Forms.NumericUpDown();
            this.numTsk = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.numArg1 = new System.Windows.Forms.NumericUpDown();
            this.numArg3 = new System.Windows.Forms.NumericUpDown();
            this.numArg2 = new System.Windows.Forms.NumericUpDown();
            this.btnForward = new System.Windows.Forms.Button();
            this.btnBack = new System.Windows.Forms.Button();
            this.btnPause = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numId)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numSeq)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTgt)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg0)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTsk)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg2)).BeginInit();
            this.SuspendLayout();
            // 
            // lblIP
            // 
            this.lblIP.AutoSize = true;
            this.lblIP.Location = new System.Drawing.Point(17, 16);
            this.lblIP.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblIP.Name = "lblIP";
            this.lblIP.Size = new System.Drawing.Size(24, 17);
            this.lblIP.TabIndex = 0;
            this.lblIP.Text = "IP:";
            // 
            // txtIP
            // 
            this.txtIP.Location = new System.Drawing.Point(52, 12);
            this.txtIP.Margin = new System.Windows.Forms.Padding(4);
            this.txtIP.Name = "txtIP";
            this.txtIP.Size = new System.Drawing.Size(132, 22);
            this.txtIP.TabIndex = 1;
            this.txtIP.Text = "192.168.1.1";
            // 
            // lblPort
            // 
            this.lblPort.AutoSize = true;
            this.lblPort.Location = new System.Drawing.Point(195, 16);
            this.lblPort.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblPort.Name = "lblPort";
            this.lblPort.Size = new System.Drawing.Size(38, 17);
            this.lblPort.TabIndex = 2;
            this.lblPort.Text = "Port:";
            // 
            // txtPort
            // 
            this.txtPort.Location = new System.Drawing.Point(237, 12);
            this.txtPort.Margin = new System.Windows.Forms.Padding(4);
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(132, 22);
            this.txtPort.TabIndex = 3;
            this.txtPort.Text = "2000";
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(379, 10);
            this.btnConnect.Margin = new System.Windows.Forms.Padding(4);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(100, 28);
            this.btnConnect.TabIndex = 4;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // txtOutput
            // 
            this.txtOutput.Location = new System.Drawing.Point(21, 57);
            this.txtOutput.Margin = new System.Windows.Forms.Padding(4);
            this.txtOutput.Multiline = true;
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.Size = new System.Drawing.Size(992, 306);
            this.txtOutput.TabIndex = 5;
            // 
            // txtMsg
            // 
            this.txtMsg.Location = new System.Drawing.Point(21, 372);
            this.txtMsg.Margin = new System.Windows.Forms.Padding(4);
            this.txtMsg.Name = "txtMsg";
            this.txtMsg.Size = new System.Drawing.Size(724, 22);
            this.txtMsg.TabIndex = 6;
            // 
            // btnSendRaw
            // 
            this.btnSendRaw.Location = new System.Drawing.Point(771, 370);
            this.btnSendRaw.Margin = new System.Windows.Forms.Padding(4);
            this.btnSendRaw.Name = "btnSendRaw";
            this.btnSendRaw.Size = new System.Drawing.Size(100, 28);
            this.btnSendRaw.TabIndex = 7;
            this.btnSendRaw.Text = "Send Raw";
            this.btnSendRaw.UseVisualStyleBackColor = true;
            this.btnSendRaw.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // btnSendPayload
            // 
            this.btnSendPayload.Location = new System.Drawing.Point(889, 372);
            this.btnSendPayload.Margin = new System.Windows.Forms.Padding(4);
            this.btnSendPayload.Name = "btnSendPayload";
            this.btnSendPayload.Size = new System.Drawing.Size(112, 28);
            this.btnSendPayload.TabIndex = 8;
            this.btnSendPayload.Text = "Send Payload";
            this.btnSendPayload.UseVisualStyleBackColor = true;
            this.btnSendPayload.Click += new System.EventHandler(this.btnSendPayload_Click);
            // 
            // lblId
            // 
            this.lblId.AutoSize = true;
            this.lblId.Location = new System.Drawing.Point(23, 415);
            this.lblId.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblId.Name = "lblId";
            this.lblId.Size = new System.Drawing.Size(23, 17);
            this.lblId.TabIndex = 9;
            this.lblId.Text = "id:";
            // 
            // numId
            // 
            this.numId.Location = new System.Drawing.Point(56, 412);
            this.numId.Margin = new System.Windows.Forms.Padding(4);
            this.numId.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.numId.Name = "numId";
            this.numId.Size = new System.Drawing.Size(48, 22);
            this.numId.TabIndex = 10;
            // 
            // numSeq
            // 
            this.numSeq.Location = new System.Drawing.Point(157, 412);
            this.numSeq.Margin = new System.Windows.Forms.Padding(4);
            this.numSeq.Maximum = new decimal(new int[] {
            99999,
            0,
            0,
            0});
            this.numSeq.Name = "numSeq";
            this.numSeq.Size = new System.Drawing.Size(48, 22);
            this.numSeq.TabIndex = 12;
            this.numSeq.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // lblSeq
            // 
            this.lblSeq.AutoSize = true;
            this.lblSeq.Location = new System.Drawing.Point(124, 415);
            this.lblSeq.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSeq.Name = "lblSeq";
            this.lblSeq.Size = new System.Drawing.Size(35, 17);
            this.lblSeq.TabIndex = 11;
            this.lblSeq.Text = "seq:";
            // 
            // numTgt
            // 
            this.numTgt.Location = new System.Drawing.Point(355, 412);
            this.numTgt.Margin = new System.Windows.Forms.Padding(4);
            this.numTgt.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.numTgt.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numTgt.Name = "numTgt";
            this.numTgt.Size = new System.Drawing.Size(48, 22);
            this.numTgt.TabIndex = 16;
            this.numTgt.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // lblTgt
            // 
            this.lblTgt.AutoSize = true;
            this.lblTgt.Location = new System.Drawing.Point(321, 415);
            this.lblTgt.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTgt.Name = "lblTgt";
            this.lblTgt.Size = new System.Drawing.Size(28, 17);
            this.lblTgt.TabIndex = 15;
            this.lblTgt.Text = "tgt:";
            // 
            // lblTp
            // 
            this.lblTp.AutoSize = true;
            this.lblTp.Location = new System.Drawing.Point(220, 415);
            this.lblTp.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTp.Name = "lblTp";
            this.lblTp.Size = new System.Drawing.Size(24, 17);
            this.lblTp.TabIndex = 13;
            this.lblTp.Text = "tp:";
            // 
            // ddlTp
            // 
            this.ddlTp.FormattingEnabled = true;
            this.ddlTp.Items.AddRange(new object[] {
            "r",
            "s"});
            this.ddlTp.Location = new System.Drawing.Point(253, 411);
            this.ddlTp.Margin = new System.Windows.Forms.Padding(4);
            this.ddlTp.Name = "ddlTp";
            this.ddlTp.Size = new System.Drawing.Size(59, 24);
            this.ddlTp.TabIndex = 17;
            // 
            // numArg0
            // 
            this.numArg0.Location = new System.Drawing.Point(535, 412);
            this.numArg0.Margin = new System.Windows.Forms.Padding(4);
            this.numArg0.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg0.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numArg0.Name = "numArg0";
            this.numArg0.Size = new System.Drawing.Size(111, 22);
            this.numArg0.TabIndex = 21;
            this.numArg0.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // numTsk
            // 
            this.numTsk.Location = new System.Drawing.Point(457, 412);
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
            this.numTsk.TabIndex = 19;
            this.numTsk.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(424, 415);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 17);
            this.label2.TabIndex = 18;
            this.label2.Text = "tsk:";
            // 
            // numArg1
            // 
            this.numArg1.Location = new System.Drawing.Point(653, 412);
            this.numArg1.Margin = new System.Windows.Forms.Padding(4);
            this.numArg1.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numArg1.Name = "numArg1";
            this.numArg1.Size = new System.Drawing.Size(111, 22);
            this.numArg1.TabIndex = 23;
            this.numArg1.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // numArg3
            // 
            this.numArg3.Location = new System.Drawing.Point(891, 412);
            this.numArg3.Margin = new System.Windows.Forms.Padding(4);
            this.numArg3.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg3.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numArg3.Name = "numArg3";
            this.numArg3.Size = new System.Drawing.Size(111, 22);
            this.numArg3.TabIndex = 25;
            this.numArg3.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // numArg2
            // 
            this.numArg2.Location = new System.Drawing.Point(772, 412);
            this.numArg2.Margin = new System.Windows.Forms.Padding(4);
            this.numArg2.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg2.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numArg2.Name = "numArg2";
            this.numArg2.Size = new System.Drawing.Size(111, 22);
            this.numArg2.TabIndex = 24;
            this.numArg2.Value = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            // 
            // btnForward
            // 
            this.btnForward.Location = new System.Drawing.Point(21, 447);
            this.btnForward.Name = "btnForward";
            this.btnForward.Size = new System.Drawing.Size(75, 23);
            this.btnForward.TabIndex = 26;
            this.btnForward.Text = "Lori";
            this.btnForward.UseVisualStyleBackColor = true;
            this.btnForward.Click += new System.EventHandler(this.btnForward_Click);
            // 
            // btnBack
            // 
            this.btnBack.Location = new System.Drawing.Point(102, 447);
            this.btnBack.Name = "btnBack";
            this.btnBack.Size = new System.Drawing.Size(75, 23);
            this.btnBack.TabIndex = 27;
            this.btnBack.Text = "Crane";
            this.btnBack.UseVisualStyleBackColor = true;
            this.btnBack.Click += new System.EventHandler(this.btnBack_Click);
            // 
            // btnPause
            // 
            this.btnPause.Location = new System.Drawing.Point(183, 447);
            this.btnPause.Name = "btnPause";
            this.btnPause.Size = new System.Drawing.Size(75, 23);
            this.btnPause.TabIndex = 28;
            this.btnPause.Text = "Pause";
            this.btnPause.UseVisualStyleBackColor = true;
            this.btnPause.Click += new System.EventHandler(this.btnPause_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1031, 482);
            this.Controls.Add(this.btnPause);
            this.Controls.Add(this.btnBack);
            this.Controls.Add(this.btnForward);
            this.Controls.Add(this.numArg3);
            this.Controls.Add(this.numArg2);
            this.Controls.Add(this.numArg1);
            this.Controls.Add(this.numArg0);
            this.Controls.Add(this.numTsk);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ddlTp);
            this.Controls.Add(this.numTgt);
            this.Controls.Add(this.lblTgt);
            this.Controls.Add(this.lblTp);
            this.Controls.Add(this.numSeq);
            this.Controls.Add(this.lblSeq);
            this.Controls.Add(this.numId);
            this.Controls.Add(this.lblId);
            this.Controls.Add(this.btnSendPayload);
            this.Controls.Add(this.btnSendRaw);
            this.Controls.Add(this.txtMsg);
            this.Controls.Add(this.txtOutput);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.txtPort);
            this.Controls.Add(this.lblPort);
            this.Controls.Add(this.txtIP);
            this.Controls.Add(this.lblIP);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "TestClient";
            ((System.ComponentModel.ISupportInitialize)(this.numId)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numSeq)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTgt)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg0)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTsk)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblIP;
        private System.Windows.Forms.TextBox txtIP;
        private System.Windows.Forms.Label lblPort;
        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.TextBox txtMsg;
        private System.Windows.Forms.Button btnSendRaw;
        private System.Windows.Forms.Button btnSendPayload;
        private System.Windows.Forms.Label lblId;
        private System.Windows.Forms.NumericUpDown numId;
        private System.Windows.Forms.NumericUpDown numSeq;
        private System.Windows.Forms.Label lblSeq;
        private System.Windows.Forms.NumericUpDown numTgt;
        private System.Windows.Forms.Label lblTgt;
        private System.Windows.Forms.Label lblTp;
        private System.Windows.Forms.ComboBox ddlTp;
        private System.Windows.Forms.NumericUpDown numArg0;
        private System.Windows.Forms.NumericUpDown numTsk;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numArg1;
        private System.Windows.Forms.NumericUpDown numArg3;
        private System.Windows.Forms.NumericUpDown numArg2;
        private System.Windows.Forms.Button btnForward;
        private System.Windows.Forms.Button btnBack;
        private System.Windows.Forms.Button btnPause;
    }
}

