namespace Atos.ControlPanel
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
            this.btnEnd = new System.Windows.Forms.Button();
            this.btnEStop = new System.Windows.Forms.Button();
            this.lblLori = new System.Windows.Forms.Label();
            this.lblCipango = new System.Windows.Forms.Label();
            this.lblCrane = new System.Windows.Forms.Label();
            this.lblFactory = new System.Windows.Forms.Label();
            this.lblLoriStats = new System.Windows.Forms.Label();
            this.lblCipangoStats = new System.Windows.Forms.Label();
            this.lblCraneStats = new System.Windows.Forms.Label();
            this.lblFactoryStats = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // btnStart
            // 
            this.btnStart.BackColor = System.Drawing.Color.Lime;
            this.btnStart.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnStart.Location = new System.Drawing.Point(460, 12);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(150, 50);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = false;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // btnEnd
            // 
            this.btnEnd.BackColor = System.Drawing.Color.Yellow;
            this.btnEnd.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnEnd.Location = new System.Drawing.Point(460, 68);
            this.btnEnd.Name = "btnEnd";
            this.btnEnd.Size = new System.Drawing.Size(150, 50);
            this.btnEnd.TabIndex = 1;
            this.btnEnd.Text = "End";
            this.btnEnd.UseVisualStyleBackColor = false;
            this.btnEnd.Click += new System.EventHandler(this.btnEnd_Click);
            // 
            // btnEStop
            // 
            this.btnEStop.BackColor = System.Drawing.Color.Red;
            this.btnEStop.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnEStop.Location = new System.Drawing.Point(460, 124);
            this.btnEStop.Name = "btnEStop";
            this.btnEStop.Size = new System.Drawing.Size(150, 150);
            this.btnEStop.TabIndex = 2;
            this.btnEStop.Text = "E-Stop";
            this.btnEStop.UseVisualStyleBackColor = false;
            this.btnEStop.Click += new System.EventHandler(this.btnEStop_Click);
            // 
            // lblLori
            // 
            this.lblLori.AutoSize = true;
            this.lblLori.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblLori.Location = new System.Drawing.Point(13, 12);
            this.lblLori.Name = "lblLori";
            this.lblLori.Size = new System.Drawing.Size(61, 25);
            this.lblLori.TabIndex = 3;
            this.lblLori.Text = "Lori: ";
            // 
            // lblCipango
            // 
            this.lblCipango.AutoSize = true;
            this.lblCipango.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblCipango.Location = new System.Drawing.Point(12, 68);
            this.lblCipango.Name = "lblCipango";
            this.lblCipango.Size = new System.Drawing.Size(100, 25);
            this.lblCipango.TabIndex = 4;
            this.lblCipango.Text = "Cipango:";
            // 
            // lblCrane
            // 
            this.lblCrane.AutoSize = true;
            this.lblCrane.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblCrane.Location = new System.Drawing.Point(13, 124);
            this.lblCrane.Name = "lblCrane";
            this.lblCrane.Size = new System.Drawing.Size(78, 25);
            this.lblCrane.TabIndex = 5;
            this.lblCrane.Text = "Crane:";
            // 
            // lblFactory
            // 
            this.lblFactory.AutoSize = true;
            this.lblFactory.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblFactory.Location = new System.Drawing.Point(12, 187);
            this.lblFactory.Name = "lblFactory";
            this.lblFactory.Size = new System.Drawing.Size(91, 25);
            this.lblFactory.TabIndex = 6;
            this.lblFactory.Text = "Factory:";
            // 
            // lblLoriStats
            // 
            this.lblLoriStats.AutoSize = true;
            this.lblLoriStats.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblLoriStats.Location = new System.Drawing.Point(126, 12);
            this.lblLoriStats.Name = "lblLoriStats";
            this.lblLoriStats.Size = new System.Drawing.Size(127, 25);
            this.lblLoriStats.TabIndex = 7;
            this.lblLoriStats.Text = "<Unknown>";
            // 
            // lblCipangoStats
            // 
            this.lblCipangoStats.AutoSize = true;
            this.lblCipangoStats.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblCipangoStats.Location = new System.Drawing.Point(126, 68);
            this.lblCipangoStats.Name = "lblCipangoStats";
            this.lblCipangoStats.Size = new System.Drawing.Size(127, 25);
            this.lblCipangoStats.TabIndex = 8;
            this.lblCipangoStats.Text = "<Unknown>";
            // 
            // lblCraneStats
            // 
            this.lblCraneStats.AutoSize = true;
            this.lblCraneStats.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblCraneStats.Location = new System.Drawing.Point(126, 124);
            this.lblCraneStats.Name = "lblCraneStats";
            this.lblCraneStats.Size = new System.Drawing.Size(127, 25);
            this.lblCraneStats.TabIndex = 9;
            this.lblCraneStats.Text = "<Unknown>";
            // 
            // lblFactoryStats
            // 
            this.lblFactoryStats.AutoSize = true;
            this.lblFactoryStats.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblFactoryStats.Location = new System.Drawing.Point(126, 187);
            this.lblFactoryStats.Name = "lblFactoryStats";
            this.lblFactoryStats.Size = new System.Drawing.Size(127, 25);
            this.lblFactoryStats.TabIndex = 10;
            this.lblFactoryStats.Text = "<Unknown>";
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(622, 313);
            this.Controls.Add(this.lblFactoryStats);
            this.Controls.Add(this.lblCraneStats);
            this.Controls.Add(this.lblCipangoStats);
            this.Controls.Add(this.lblLoriStats);
            this.Controls.Add(this.lblFactory);
            this.Controls.Add(this.lblCrane);
            this.Controls.Add(this.lblCipango);
            this.Controls.Add(this.lblLori);
            this.Controls.Add(this.btnEStop);
            this.Controls.Add(this.btnEnd);
            this.Controls.Add(this.btnStart);
            this.Name = "Form1";
            this.Text = "Control Panel";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnEnd;
        private System.Windows.Forms.Button btnEStop;
        private System.Windows.Forms.Label lblLori;
        private System.Windows.Forms.Label lblCipango;
        private System.Windows.Forms.Label lblCrane;
        private System.Windows.Forms.Label lblFactory;
        private System.Windows.Forms.Label lblLoriStats;
        private System.Windows.Forms.Label lblCipangoStats;
        private System.Windows.Forms.Label lblCraneStats;
        private System.Windows.Forms.Label lblFactoryStats;
        private System.Windows.Forms.Timer timer1;
    }
}

