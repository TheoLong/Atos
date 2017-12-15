namespace Atos.TestServerM3
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
            this.btnStart = new System.Windows.Forms.Button();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.lblPort = new System.Windows.Forms.Label();
            this.lblIp = new System.Windows.Forms.Label();
            this.txtIp = new System.Windows.Forms.TextBox();
            this.numArg3 = new System.Windows.Forms.NumericUpDown();
            this.numArg2 = new System.Windows.Forms.NumericUpDown();
            this.numArg1 = new System.Windows.Forms.NumericUpDown();
            this.numArg0 = new System.Windows.Forms.NumericUpDown();
            this.numTsk = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.numId = new System.Windows.Forms.NumericUpDown();
            this.lblId = new System.Windows.Forms.Label();
            this.gridStorage = new System.Windows.Forms.DataGridView();
            this.btnAddStorage = new System.Windows.Forms.Button();
            this.lblStorage = new System.Windows.Forms.Label();
            this.btnClear = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.listMsg = new System.Windows.Forms.ListBox();
            ((System.ComponentModel.ISupportInitialize)(this.numArg3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg0)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTsk)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numId)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridStorage)).BeginInit();
            this.SuspendLayout();
            // 
            // btnStart
            // 
            this.btnStart.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnStart.Location = new System.Drawing.Point(848, 422);
            this.btnStart.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(80, 50);
            this.btnStart.TabIndex = 48;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // txtPort
            // 
            this.txtPort.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.txtPort.Location = new System.Drawing.Point(803, 434);
            this.txtPort.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.txtPort.MaxLength = 10;
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(40, 22);
            this.txtPort.TabIndex = 47;
            this.txtPort.Text = "2000";
            // 
            // lblPort
            // 
            this.lblPort.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblPort.AutoSize = true;
            this.lblPort.Location = new System.Drawing.Point(759, 439);
            this.lblPort.Name = "lblPort";
            this.lblPort.Size = new System.Drawing.Size(38, 17);
            this.lblPort.TabIndex = 46;
            this.lblPort.Text = "Port:";
            // 
            // lblIp
            // 
            this.lblIp.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblIp.AutoSize = true;
            this.lblIp.Location = new System.Drawing.Point(623, 439);
            this.lblIp.Name = "lblIp";
            this.lblIp.Size = new System.Drawing.Size(24, 17);
            this.lblIp.TabIndex = 45;
            this.lblIp.Text = "IP:";
            // 
            // txtIp
            // 
            this.txtIp.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.txtIp.Location = new System.Drawing.Point(652, 434);
            this.txtIp.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.txtIp.MaxLength = 20;
            this.txtIp.Name = "txtIp";
            this.txtIp.Size = new System.Drawing.Size(100, 22);
            this.txtIp.TabIndex = 44;
            this.txtIp.Text = "192.168.1.1";
            // 
            // numArg3
            // 
            this.numArg3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numArg3.Location = new System.Drawing.Point(919, 542);
            this.numArg3.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.numArg3.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.numArg3.Size = new System.Drawing.Size(111, 22);
            this.numArg3.TabIndex = 56;
            this.numArg3.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numArg2
            // 
            this.numArg2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numArg2.Location = new System.Drawing.Point(800, 542);
            this.numArg2.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.numArg2.TabIndex = 55;
            this.numArg2.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numArg1
            // 
            this.numArg1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numArg1.Location = new System.Drawing.Point(681, 542);
            this.numArg1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.numArg1.TabIndex = 54;
            this.numArg1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numArg0
            // 
            this.numArg0.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numArg0.Location = new System.Drawing.Point(563, 542);
            this.numArg0.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.numArg0.TabIndex = 53;
            this.numArg0.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numTsk
            // 
            this.numTsk.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numTsk.Location = new System.Drawing.Point(848, 510);
            this.numTsk.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.numTsk.TabIndex = 52;
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
            this.label2.Location = new System.Drawing.Point(815, 512);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 17);
            this.label2.TabIndex = 51;
            this.label2.Text = "tsk:";
            // 
            // numId
            // 
            this.numId.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.numId.Location = new System.Drawing.Point(669, 510);
            this.numId.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.numId.Maximum = new decimal(new int[] {
            99999,
            0,
            0,
            0});
            this.numId.Name = "numId";
            this.numId.Size = new System.Drawing.Size(48, 22);
            this.numId.TabIndex = 58;
            this.numId.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // lblId
            // 
            this.lblId.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblId.AutoSize = true;
            this.lblId.Location = new System.Drawing.Point(636, 512);
            this.lblId.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblId.Name = "lblId";
            this.lblId.Size = new System.Drawing.Size(23, 17);
            this.lblId.TabIndex = 57;
            this.lblId.Text = "id:";
            // 
            // gridStorage
            // 
            this.gridStorage.AllowUserToAddRows = false;
            this.gridStorage.AllowUserToDeleteRows = false;
            this.gridStorage.AllowUserToResizeRows = false;
            this.gridStorage.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.ColumnHeader;
            this.gridStorage.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridStorage.Location = new System.Drawing.Point(16, 422);
            this.gridStorage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gridStorage.Name = "gridStorage";
            this.gridStorage.Size = new System.Drawing.Size(533, 235);
            this.gridStorage.TabIndex = 59;
            // 
            // btnAddStorage
            // 
            this.btnAddStorage.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnAddStorage.Enabled = false;
            this.btnAddStorage.Location = new System.Drawing.Point(744, 583);
            this.btnAddStorage.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnAddStorage.Name = "btnAddStorage";
            this.btnAddStorage.Size = new System.Drawing.Size(100, 50);
            this.btnAddStorage.TabIndex = 60;
            this.btnAddStorage.Text = "Store Task";
            this.btnAddStorage.UseVisualStyleBackColor = true;
            this.btnAddStorage.Click += new System.EventHandler(this.btnAddStorage_Click);
            // 
            // lblStorage
            // 
            this.lblStorage.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblStorage.AutoSize = true;
            this.lblStorage.Location = new System.Drawing.Point(15, 402);
            this.lblStorage.Name = "lblStorage";
            this.lblStorage.Size = new System.Drawing.Size(96, 17);
            this.lblStorage.TabIndex = 61;
            this.lblStorage.Text = "Stored Tasks:";
            // 
            // btnClear
            // 
            this.btnClear.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnClear.Location = new System.Drawing.Point(563, 583);
            this.btnClear.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(100, 50);
            this.btnClear.TabIndex = 62;
            this.btnClear.Text = "Clear Stored Tasks";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // listMsg
            // 
            this.listMsg.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listMsg.Font = new System.Drawing.Font("Courier New", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.listMsg.FormattingEnabled = true;
            this.listMsg.HorizontalScrollbar = true;
            this.listMsg.ItemHeight = 17;
            this.listMsg.Location = new System.Drawing.Point(19, 16);
            this.listMsg.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.listMsg.Name = "listMsg";
            this.listMsg.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.listMsg.Size = new System.Drawing.Size(1009, 361);
            this.listMsg.TabIndex = 63;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1045, 672);
            this.Controls.Add(this.listMsg);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.lblStorage);
            this.Controls.Add(this.btnAddStorage);
            this.Controls.Add(this.gridStorage);
            this.Controls.Add(this.numId);
            this.Controls.Add(this.lblId);
            this.Controls.Add(this.numArg3);
            this.Controls.Add(this.numArg2);
            this.Controls.Add(this.numArg1);
            this.Controls.Add(this.numArg0);
            this.Controls.Add(this.numTsk);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.txtPort);
            this.Controls.Add(this.lblPort);
            this.Controls.Add(this.lblIp);
            this.Controls.Add(this.txtIp);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.numArg3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numArg0)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTsk)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numId)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridStorage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.Label lblPort;
        private System.Windows.Forms.Label lblIp;
        private System.Windows.Forms.TextBox txtIp;
        private System.Windows.Forms.NumericUpDown numArg3;
        private System.Windows.Forms.NumericUpDown numArg2;
        private System.Windows.Forms.NumericUpDown numArg1;
        private System.Windows.Forms.NumericUpDown numArg0;
        private System.Windows.Forms.NumericUpDown numTsk;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numId;
        private System.Windows.Forms.Label lblId;
        private System.Windows.Forms.DataGridView gridStorage;
        private System.Windows.Forms.Button btnAddStorage;
        private System.Windows.Forms.Label lblStorage;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ListBox listMsg;
    }
}

