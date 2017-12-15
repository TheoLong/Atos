namespace Atos.DBViewer
{
    partial class DBViewer
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.ddlType = new System.Windows.Forms.ComboBox();
            this.listClient = new System.Windows.Forms.ListView();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.gridData = new System.Windows.Forms.DataGridView();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.lblType = new System.Windows.Forms.Label();
            this.lblSourceId = new System.Windows.Forms.Label();
            this.ddlSourceId = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.chkAuto = new System.Windows.Forms.CheckBox();
            this.lblTimeElapsed = new System.Windows.Forms.Label();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.label5 = new System.Windows.Forms.Label();
            this.lblTsk = new System.Windows.Forms.Label();
            this.numTsk = new System.Windows.Forms.NumericUpDown();
            this.lblArg = new System.Windows.Forms.Label();
            this.ddlArg = new System.Windows.Forms.ComboBox();
            this.btnPlot = new System.Windows.Forms.Button();
            this.chtPlot = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.numTgt = new System.Windows.Forms.NumericUpDown();
            this.lblTgt = new System.Windows.Forms.Label();
            this.lblLeftError = new System.Windows.Forms.Label();
            this.lblRightError = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.gridData)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTsk)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chtPlot)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTgt)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlType
            // 
            this.ddlType.FormattingEnabled = true;
            this.ddlType.Location = new System.Drawing.Point(69, 15);
            this.ddlType.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ddlType.Name = "ddlType";
            this.ddlType.Size = new System.Drawing.Size(121, 24);
            this.ddlType.TabIndex = 0;
            this.ddlType.SelectedIndexChanged += new System.EventHandler(this.ddlType_SelectedIndexChanged);
            // 
            // listClient
            // 
            this.listClient.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listClient.Location = new System.Drawing.Point(13, 561);
            this.listClient.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.listClient.Name = "listClient";
            this.listClient.Size = new System.Drawing.Size(768, 111);
            this.listClient.TabIndex = 2;
            this.listClient.UseCompatibleStateImageBehavior = false;
            this.listClient.View = System.Windows.Forms.View.List;
            // 
            // btnRefresh
            // 
            this.btnRefresh.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnRefresh.Location = new System.Drawing.Point(788, 561);
            this.btnRefresh.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(100, 50);
            this.btnRefresh.TabIndex = 3;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // btnClear
            // 
            this.btnClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnClear.Location = new System.Drawing.Point(893, 561);
            this.btnClear.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(100, 50);
            this.btnClear.TabIndex = 4;
            this.btnClear.Text = "Delete All";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // gridData
            // 
            this.gridData.AllowUserToOrderColumns = true;
            this.gridData.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gridData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridData.Location = new System.Drawing.Point(13, 89);
            this.gridData.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.gridData.Name = "gridData";
            this.gridData.ReadOnly = true;
            this.gridData.RowTemplate.Height = 24;
            this.gridData.ShowCellErrors = false;
            this.gridData.Size = new System.Drawing.Size(981, 466);
            this.gridData.TabIndex = 5;
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // lblType
            // 
            this.lblType.AutoSize = true;
            this.lblType.Location = new System.Drawing.Point(16, 18);
            this.lblType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblType.Name = "lblType";
            this.lblType.Size = new System.Drawing.Size(44, 17);
            this.lblType.TabIndex = 6;
            this.lblType.Text = "Type:";
            // 
            // lblSourceId
            // 
            this.lblSourceId.AutoSize = true;
            this.lblSourceId.Location = new System.Drawing.Point(203, 17);
            this.lblSourceId.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSourceId.Name = "lblSourceId";
            this.lblSourceId.Size = new System.Drawing.Size(68, 17);
            this.lblSourceId.TabIndex = 8;
            this.lblSourceId.Text = "SourceId:";
            // 
            // ddlSourceId
            // 
            this.ddlSourceId.FormattingEnabled = true;
            this.ddlSourceId.Location = new System.Drawing.Point(280, 14);
            this.ddlSourceId.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ddlSourceId.Name = "ddlSourceId";
            this.ddlSourceId.Size = new System.Drawing.Size(121, 24);
            this.ddlSourceId.TabIndex = 7;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Lime;
            this.label1.Location = new System.Drawing.Point(433, 17);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 17);
            this.label1.TabIndex = 9;
            this.label1.Text = "Server Sent";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.label2.Location = new System.Drawing.Point(525, 17);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 17);
            this.label2.TabIndex = 10;
            this.label2.Text = "Client Get";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Yellow;
            this.label3.Location = new System.Drawing.Point(604, 17);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(75, 17);
            this.label3.TabIndex = 11;
            this.label3.Text = "Client Post";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Red;
            this.label4.Location = new System.Drawing.Point(688, 17);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(94, 17);
            this.label4.TabIndex = 12;
            this.label4.Text = "Bad Message";
            // 
            // chkAuto
            // 
            this.chkAuto.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.chkAuto.AutoSize = true;
            this.chkAuto.Location = new System.Drawing.Point(845, 616);
            this.chkAuto.Name = "chkAuto";
            this.chkAuto.Size = new System.Drawing.Size(113, 21);
            this.chkAuto.TabIndex = 13;
            this.chkAuto.Text = "Auto Refresh";
            this.chkAuto.UseVisualStyleBackColor = true;
            this.chkAuto.CheckedChanged += new System.EventHandler(this.chkAuto_CheckedChanged);
            // 
            // lblTimeElapsed
            // 
            this.lblTimeElapsed.AutoSize = true;
            this.lblTimeElapsed.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblTimeElapsed.Location = new System.Drawing.Point(856, 640);
            this.lblTimeElapsed.Name = "lblTimeElapsed";
            this.lblTimeElapsed.Size = new System.Drawing.Size(81, 20);
            this.lblTimeElapsed.TabIndex = 14;
            this.lblTimeElapsed.Text = "00:00:00";
            // 
            // timer2
            // 
            this.timer2.Interval = 1000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.MediumPurple;
            this.label5.Location = new System.Drawing.Point(794, 17);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(101, 17);
            this.label5.TabIndex = 15;
            this.label5.Text = "Message Stats";
            // 
            // lblTsk
            // 
            this.lblTsk.AutoSize = true;
            this.lblTsk.Location = new System.Drawing.Point(228, 52);
            this.lblTsk.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTsk.Name = "lblTsk";
            this.lblTsk.Size = new System.Drawing.Size(43, 17);
            this.lblTsk.TabIndex = 17;
            this.lblTsk.Text = "Task:";
            // 
            // numTsk
            // 
            this.numTsk.Location = new System.Drawing.Point(281, 53);
            this.numTsk.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numTsk.Name = "numTsk";
            this.numTsk.Size = new System.Drawing.Size(120, 22);
            this.numTsk.TabIndex = 18;
            // 
            // lblArg
            // 
            this.lblArg.AutoSize = true;
            this.lblArg.Location = new System.Drawing.Point(416, 55);
            this.lblArg.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblArg.Name = "lblArg";
            this.lblArg.Size = new System.Drawing.Size(73, 17);
            this.lblArg.TabIndex = 19;
            this.lblArg.Text = "Argument:";
            // 
            // ddlArg
            // 
            this.ddlArg.FormattingEnabled = true;
            this.ddlArg.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3"});
            this.ddlArg.Location = new System.Drawing.Point(496, 52);
            this.ddlArg.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ddlArg.Name = "ddlArg";
            this.ddlArg.Size = new System.Drawing.Size(121, 24);
            this.ddlArg.TabIndex = 20;
            this.ddlArg.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // btnPlot
            // 
            this.btnPlot.Enabled = false;
            this.btnPlot.Location = new System.Drawing.Point(638, 53);
            this.btnPlot.Name = "btnPlot";
            this.btnPlot.Size = new System.Drawing.Size(75, 23);
            this.btnPlot.TabIndex = 21;
            this.btnPlot.Text = "Plot";
            this.btnPlot.UseVisualStyleBackColor = true;
            this.btnPlot.Click += new System.EventHandler(this.btnPlot_Click);
            // 
            // chtPlot
            // 
            chartArea1.Name = "ChartArea1";
            this.chtPlot.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.chtPlot.Legends.Add(legend1);
            this.chtPlot.Location = new System.Drawing.Point(59, 123);
            this.chtPlot.Name = "chtPlot";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Color = System.Drawing.Color.Blue;
            series1.Legend = "Legend1";
            series1.Name = "leftPid";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series2.Color = System.Drawing.Color.Red;
            series2.Legend = "Legend1";
            series2.Name = "rightPid";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.StepLine;
            series3.Color = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            series3.Legend = "Legend1";
            series3.Name = "leftSpeed";
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.StepLine;
            series4.Color = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            series4.Legend = "Legend1";
            series4.Name = "rightSpeed";
            this.chtPlot.Series.Add(series1);
            this.chtPlot.Series.Add(series2);
            this.chtPlot.Series.Add(series3);
            this.chtPlot.Series.Add(series4);
            this.chtPlot.Size = new System.Drawing.Size(899, 408);
            this.chtPlot.TabIndex = 22;
            this.chtPlot.Text = "chart1";
            this.chtPlot.Visible = false;
            // 
            // numTgt
            // 
            this.numTgt.Location = new System.Drawing.Point(101, 52);
            this.numTgt.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.numTgt.Name = "numTgt";
            this.numTgt.Size = new System.Drawing.Size(120, 22);
            this.numTgt.TabIndex = 24;
            // 
            // lblTgt
            // 
            this.lblTgt.AutoSize = true;
            this.lblTgt.Location = new System.Drawing.Point(29, 54);
            this.lblTgt.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTgt.Name = "lblTgt";
            this.lblTgt.Size = new System.Drawing.Size(65, 17);
            this.lblTgt.TabIndex = 23;
            this.lblTgt.Text = "TargetId:";
            // 
            // lblLeftError
            // 
            this.lblLeftError.AutoSize = true;
            this.lblLeftError.Location = new System.Drawing.Point(811, 235);
            this.lblLeftError.Name = "lblLeftError";
            this.lblLeftError.Size = new System.Drawing.Size(128, 17);
            this.lblLeftError.TabIndex = 25;
            this.lblLeftError.Text = "Left Total Error: 35";
            this.lblLeftError.Visible = false;
            // 
            // lblRightError
            // 
            this.lblRightError.AutoSize = true;
            this.lblRightError.Location = new System.Drawing.Point(811, 252);
            this.lblRightError.Name = "lblRightError";
            this.lblRightError.Size = new System.Drawing.Size(137, 17);
            this.lblRightError.TabIndex = 26;
            this.lblRightError.Text = "Right Total Error: 35";
            this.lblRightError.Visible = false;
            // 
            // DBViewer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1005, 721);
            this.Controls.Add(this.lblRightError);
            this.Controls.Add(this.lblLeftError);
            this.Controls.Add(this.numTgt);
            this.Controls.Add(this.lblTgt);
            this.Controls.Add(this.chtPlot);
            this.Controls.Add(this.btnPlot);
            this.Controls.Add(this.ddlArg);
            this.Controls.Add(this.lblArg);
            this.Controls.Add(this.numTsk);
            this.Controls.Add(this.lblTsk);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.lblTimeElapsed);
            this.Controls.Add(this.chkAuto);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblSourceId);
            this.Controls.Add(this.ddlSourceId);
            this.Controls.Add(this.lblType);
            this.Controls.Add(this.gridData);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.listClient);
            this.Controls.Add(this.ddlType);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "DBViewer";
            this.Text = "DBViewer";
            ((System.ComponentModel.ISupportInitialize)(this.gridData)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTsk)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chtPlot)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTgt)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox ddlType;
        private System.Windows.Forms.ListView listClient;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.DataGridView gridData;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lblType;
        private System.Windows.Forms.Label lblSourceId;
        private System.Windows.Forms.ComboBox ddlSourceId;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox chkAuto;
        private System.Windows.Forms.Label lblTimeElapsed;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lblTsk;
        private System.Windows.Forms.NumericUpDown numTsk;
        private System.Windows.Forms.Label lblArg;
        private System.Windows.Forms.ComboBox ddlArg;
        private System.Windows.Forms.Button btnPlot;
        private System.Windows.Forms.DataVisualization.Charting.Chart chtPlot;
        private System.Windows.Forms.NumericUpDown numTgt;
        private System.Windows.Forms.Label lblTgt;
        private System.Windows.Forms.Label lblLeftError;
        private System.Windows.Forms.Label lblRightError;
    }
}

