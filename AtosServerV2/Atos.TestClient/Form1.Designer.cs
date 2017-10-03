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
            this.lblIP.Location = new System.Drawing.Point(13, 13);
            this.lblIP.Name = "lblIP";
            this.lblIP.Size = new System.Drawing.Size(20, 13);
            this.lblIP.TabIndex = 0;
            this.lblIP.Text = "IP:";
            // 
            // txtIP
            // 
            this.txtIP.Location = new System.Drawing.Point(39, 10);
            this.txtIP.Name = "txtIP";
            this.txtIP.Size = new System.Drawing.Size(100, 20);
            this.txtIP.TabIndex = 1;
            this.txtIP.Text = "192.168.137.1";
            // 
            // lblPort
            // 
            this.lblPort.AutoSize = true;
            this.lblPort.Location = new System.Drawing.Point(146, 13);
            this.lblPort.Name = "lblPort";
            this.lblPort.Size = new System.Drawing.Size(29, 13);
            this.lblPort.TabIndex = 2;
            this.lblPort.Text = "Port:";
            // 
            // txtPort
            // 
            this.txtPort.Location = new System.Drawing.Point(178, 10);
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(100, 20);
            this.txtPort.TabIndex = 3;
            this.txtPort.Text = "2000";
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(284, 8);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(75, 23);
            this.btnConnect.TabIndex = 4;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // txtOutput
            // 
            this.txtOutput.Location = new System.Drawing.Point(16, 46);
            this.txtOutput.Multiline = true;
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.Size = new System.Drawing.Size(745, 249);
            this.txtOutput.TabIndex = 5;
            // 
            // txtMsg
            // 
            this.txtMsg.Location = new System.Drawing.Point(16, 302);
            this.txtMsg.Name = "txtMsg";
            this.txtMsg.Size = new System.Drawing.Size(544, 20);
            this.txtMsg.TabIndex = 6;
            // 
            // btnSendRaw
            // 
            this.btnSendRaw.Location = new System.Drawing.Point(578, 301);
            this.btnSendRaw.Name = "btnSendRaw";
            this.btnSendRaw.Size = new System.Drawing.Size(75, 23);
            this.btnSendRaw.TabIndex = 7;
            this.btnSendRaw.Text = "Send Raw";
            this.btnSendRaw.UseVisualStyleBackColor = true;
            this.btnSendRaw.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // btnSendPayload
            // 
            this.btnSendPayload.Location = new System.Drawing.Point(667, 302);
            this.btnSendPayload.Name = "btnSendPayload";
            this.btnSendPayload.Size = new System.Drawing.Size(84, 23);
            this.btnSendPayload.TabIndex = 8;
            this.btnSendPayload.Text = "Send Payload";
            this.btnSendPayload.UseVisualStyleBackColor = true;
            this.btnSendPayload.Click += new System.EventHandler(this.btnSendPayload_Click);
            // 
            // lblId
            // 
            this.lblId.AutoSize = true;
            this.lblId.Location = new System.Drawing.Point(17, 337);
            this.lblId.Name = "lblId";
            this.lblId.Size = new System.Drawing.Size(18, 13);
            this.lblId.TabIndex = 9;
            this.lblId.Text = "id:";
            // 
            // numId
            // 
            this.numId.Location = new System.Drawing.Point(42, 335);
            this.numId.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            0});
            this.numId.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numId.Name = "numId";
            this.numId.Size = new System.Drawing.Size(36, 20);
            this.numId.TabIndex = 10;
            this.numId.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numSeq
            // 
            this.numSeq.Location = new System.Drawing.Point(118, 335);
            this.numSeq.Maximum = new decimal(new int[] {
            99999,
            0,
            0,
            0});
            this.numSeq.Name = "numSeq";
            this.numSeq.Size = new System.Drawing.Size(36, 20);
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
            this.lblSeq.Location = new System.Drawing.Point(93, 337);
            this.lblSeq.Name = "lblSeq";
            this.lblSeq.Size = new System.Drawing.Size(27, 13);
            this.lblSeq.TabIndex = 11;
            this.lblSeq.Text = "seq:";
            // 
            // numTgt
            // 
            this.numTgt.Location = new System.Drawing.Point(266, 335);
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
            this.numTgt.Size = new System.Drawing.Size(36, 20);
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
            this.lblTgt.Location = new System.Drawing.Point(241, 337);
            this.lblTgt.Name = "lblTgt";
            this.lblTgt.Size = new System.Drawing.Size(22, 13);
            this.lblTgt.TabIndex = 15;
            this.lblTgt.Text = "tgt:";
            // 
            // lblTp
            // 
            this.lblTp.AutoSize = true;
            this.lblTp.Location = new System.Drawing.Point(165, 337);
            this.lblTp.Name = "lblTp";
            this.lblTp.Size = new System.Drawing.Size(19, 13);
            this.lblTp.TabIndex = 13;
            this.lblTp.Text = "tp:";
            // 
            // ddlTp
            // 
            this.ddlTp.FormattingEnabled = true;
            this.ddlTp.Items.AddRange(new object[] {
            "r",
            "s"});
            this.ddlTp.Location = new System.Drawing.Point(190, 334);
            this.ddlTp.Name = "ddlTp";
            this.ddlTp.Size = new System.Drawing.Size(45, 21);
            this.ddlTp.TabIndex = 17;
            // 
            // numArg0
            // 
            this.numArg0.Location = new System.Drawing.Point(401, 335);
            this.numArg0.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg0.Name = "numArg0";
            this.numArg0.Size = new System.Drawing.Size(83, 20);
            this.numArg0.TabIndex = 21;
            this.numArg0.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numTsk
            // 
            this.numTsk.Location = new System.Drawing.Point(343, 335);
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
            this.numTsk.Size = new System.Drawing.Size(36, 20);
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
            this.label2.Location = new System.Drawing.Point(318, 337);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(24, 13);
            this.label2.TabIndex = 18;
            this.label2.Text = "tsk:";
            // 
            // numArg1
            // 
            this.numArg1.Location = new System.Drawing.Point(490, 335);
            this.numArg1.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg1.Name = "numArg1";
            this.numArg1.Size = new System.Drawing.Size(83, 20);
            this.numArg1.TabIndex = 23;
            this.numArg1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numArg3
            // 
            this.numArg3.Location = new System.Drawing.Point(668, 335);
            this.numArg3.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg3.Name = "numArg3";
            this.numArg3.Size = new System.Drawing.Size(83, 20);
            this.numArg3.TabIndex = 25;
            this.numArg3.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numArg2
            // 
            this.numArg2.Location = new System.Drawing.Point(579, 335);
            this.numArg2.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numArg2.Name = "numArg2";
            this.numArg2.Size = new System.Drawing.Size(83, 20);
            this.numArg2.TabIndex = 24;
            this.numArg2.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(773, 367);
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
    }
}

