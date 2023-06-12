namespace ILSTS_Sample
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.OpenFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.btnsaveRawdata = new System.Windows.Forms.Button();
            this.SaveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.btnsaveref_rawdata = new System.Windows.Forms.Button();
            this.btnmeas = new System.Windows.Forms.Button();
            this.btnget_reference = new System.Windows.Forms.Button();
            this.btnset = new System.Windows.Forms.Button();
            this.Label7 = new System.Windows.Forms.Label();
            this.Label6 = new System.Windows.Forms.Label();
            this.chklst_range = new System.Windows.Forms.CheckedListBox();
            this.chklst_ch = new System.Windows.Forms.CheckedListBox();
            this.Button1 = new System.Windows.Forms.Button();
            this.GroupBox2 = new System.Windows.Forms.GroupBox();
            this.Label5 = new System.Windows.Forms.Label();
            this.Label4 = new System.Windows.Forms.Label();
            this.Label3 = new System.Windows.Forms.Label();
            this.Label2 = new System.Windows.Forms.Label();
            this.Label1 = new System.Windows.Forms.Label();
            this.txtpower = new System.Windows.Forms.TextBox();
            this.cmbspeed = new System.Windows.Forms.ComboBox();
            this.txtstepwave = new System.Windows.Forms.TextBox();
            this.txtstopwave = new System.Windows.Forms.TextBox();
            this.txtstartwave = new System.Windows.Forms.TextBox();
            this.GroupBox1 = new System.Windows.Forms.GroupBox();
            this.chkeach_ch = new System.Windows.Forms.CheckBox();
            this.GroupBox2.SuspendLayout();
            this.GroupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // OpenFileDialog1
            // 
            this.OpenFileDialog1.FileName = "OpenFileDialog1";
            // 
            // btnsaveRawdata
            // 
            this.btnsaveRawdata.Location = new System.Drawing.Point(188, 261);
            this.btnsaveRawdata.Name = "btnsaveRawdata";
            this.btnsaveRawdata.Size = new System.Drawing.Size(132, 35);
            this.btnsaveRawdata.TabIndex = 14;
            this.btnsaveRawdata.Text = "Save Rawdata";
            this.btnsaveRawdata.UseVisualStyleBackColor = true;
            this.btnsaveRawdata.Click += new System.EventHandler(this.btnsaveRawdata_Click);
            // 
            // btnsaveref_rawdata
            // 
            this.btnsaveref_rawdata.Location = new System.Drawing.Point(37, 261);
            this.btnsaveref_rawdata.Name = "btnsaveref_rawdata";
            this.btnsaveref_rawdata.Size = new System.Drawing.Size(132, 35);
            this.btnsaveref_rawdata.TabIndex = 13;
            this.btnsaveref_rawdata.Text = "Save Reference Rawdata";
            this.btnsaveref_rawdata.UseVisualStyleBackColor = true;
            this.btnsaveref_rawdata.Click += new System.EventHandler(this.btnsaveref_rawdata_Click);
            // 
            // btnmeas
            // 
            this.btnmeas.Location = new System.Drawing.Point(609, 150);
            this.btnmeas.Name = "btnmeas";
            this.btnmeas.Size = new System.Drawing.Size(106, 35);
            this.btnmeas.TabIndex = 12;
            this.btnmeas.Text = "Measurement";
            this.btnmeas.UseVisualStyleBackColor = true;
            this.btnmeas.Click += new System.EventHandler(this.btnmeas_Click);
            // 
            // btnget_reference
            // 
            this.btnget_reference.Location = new System.Drawing.Point(485, 150);
            this.btnget_reference.Name = "btnget_reference";
            this.btnget_reference.Size = new System.Drawing.Size(102, 35);
            this.btnget_reference.TabIndex = 11;
            this.btnget_reference.Text = "Reference";
            this.btnget_reference.UseVisualStyleBackColor = true;
            this.btnget_reference.Click += new System.EventHandler(this.btnget_reference_Click);
            // 
            // btnset
            // 
            this.btnset.Location = new System.Drawing.Point(384, 150);
            this.btnset.Name = "btnset";
            this.btnset.Size = new System.Drawing.Size(83, 35);
            this.btnset.TabIndex = 10;
            this.btnset.Text = "SET";
            this.btnset.UseVisualStyleBackColor = true;
            this.btnset.Click += new System.EventHandler(this.btnset_Click);
            // 
            // Label7
            // 
            this.Label7.AutoSize = true;
            this.Label7.Location = new System.Drawing.Point(176, 21);
            this.Label7.Name = "Label7";
            this.Label7.Size = new System.Drawing.Size(106, 13);
            this.Label7.TabIndex = 3;
            this.Label7.Text = "Measurement Range";
            // 
            // Label6
            // 
            this.Label6.AutoSize = true;
            this.Label6.Location = new System.Drawing.Point(10, 21);
            this.Label6.Name = "Label6";
            this.Label6.Size = new System.Drawing.Size(86, 13);
            this.Label6.TabIndex = 2;
            this.Label6.Text = "Measurement ch";
            // 
            // chklst_range
            // 
            this.chklst_range.FormattingEnabled = true;
            this.chklst_range.Location = new System.Drawing.Point(177, 37);
            this.chklst_range.Name = "chklst_range";
            this.chklst_range.Size = new System.Drawing.Size(118, 34);
            this.chklst_range.TabIndex = 1;
            // 
            // chklst_ch
            // 
            this.chklst_ch.FormattingEnabled = true;
            this.chklst_ch.Location = new System.Drawing.Point(12, 37);
            this.chklst_ch.Name = "chklst_ch";
            this.chklst_ch.Size = new System.Drawing.Size(135, 34);
            this.chklst_ch.TabIndex = 0;
            // 
            // Button1
            // 
            this.Button1.Location = new System.Drawing.Point(384, 261);
            this.Button1.Name = "Button1";
            this.Button1.Size = new System.Drawing.Size(132, 35);
            this.Button1.TabIndex = 15;
            this.Button1.Text = "Read Reference Data";
            this.Button1.UseVisualStyleBackColor = true;
            this.Button1.Click += new System.EventHandler(this.Button1_Click);
            // 
            // GroupBox2
            // 
            this.GroupBox2.Controls.Add(this.Label7);
            this.GroupBox2.Controls.Add(this.Label6);
            this.GroupBox2.Controls.Add(this.chklst_range);
            this.GroupBox2.Controls.Add(this.chklst_ch);
            this.GroupBox2.Location = new System.Drawing.Point(25, 140);
            this.GroupBox2.Name = "GroupBox2";
            this.GroupBox2.Size = new System.Drawing.Size(332, 89);
            this.GroupBox2.TabIndex = 9;
            this.GroupBox2.TabStop = false;
            this.GroupBox2.Text = "Measurement ch And Range";
            // 
            // Label5
            // 
            this.Label5.AutoSize = true;
            this.Label5.Location = new System.Drawing.Point(560, 37);
            this.Label5.Name = "Label5";
            this.Label5.Size = new System.Drawing.Size(87, 13);
            this.Label5.TabIndex = 9;
            this.Label5.Text = "TSL Power(dBm)";
            // 
            // Label4
            // 
            this.Label4.AutoSize = true;
            this.Label4.Location = new System.Drawing.Point(435, 37);
            this.Label4.Name = "Label4";
            this.Label4.Size = new System.Drawing.Size(113, 13);
            this.Label4.TabIndex = 8;
            this.Label4.Text = "SweepSpeed(nm/sec)";
            // 
            // Label3
            // 
            this.Label3.AutoSize = true;
            this.Label3.Location = new System.Drawing.Point(312, 38);
            this.Label3.Name = "Label3";
            this.Label3.Size = new System.Drawing.Size(107, 13);
            this.Label3.TabIndex = 7;
            this.Label3.Text = "WavelengthStep(nm)";
            // 
            // Label2
            // 
            this.Label2.AutoSize = true;
            this.Label2.Location = new System.Drawing.Point(176, 38);
            this.Label2.Name = "Label2";
            this.Label2.Size = new System.Drawing.Size(107, 13);
            this.Label2.TabIndex = 6;
            this.Label2.Text = "StopWavelength(nm)";
            // 
            // Label1
            // 
            this.Label1.AutoSize = true;
            this.Label1.Location = new System.Drawing.Point(25, 37);
            this.Label1.Name = "Label1";
            this.Label1.Size = new System.Drawing.Size(107, 13);
            this.Label1.TabIndex = 5;
            this.Label1.Text = "StartWavelength(nm)";
            // 
            // txtpower
            // 
            this.txtpower.Location = new System.Drawing.Point(562, 53);
            this.txtpower.Name = "txtpower";
            this.txtpower.Size = new System.Drawing.Size(117, 20);
            this.txtpower.TabIndex = 4;
            this.txtpower.Text = "0";
            // 
            // cmbspeed
            // 
            this.cmbspeed.FormattingEnabled = true;
            this.cmbspeed.Location = new System.Drawing.Point(437, 53);
            this.cmbspeed.Name = "cmbspeed";
            this.cmbspeed.Size = new System.Drawing.Size(102, 21);
            this.cmbspeed.TabIndex = 3;
            // 
            // txtstepwave
            // 
            this.txtstepwave.Location = new System.Drawing.Point(314, 54);
            this.txtstepwave.Name = "txtstepwave";
            this.txtstepwave.Size = new System.Drawing.Size(100, 20);
            this.txtstepwave.TabIndex = 2;
            this.txtstepwave.Text = "0.01";
            // 
            // txtstopwave
            // 
            this.txtstopwave.Location = new System.Drawing.Point(178, 54);
            this.txtstopwave.Name = "txtstopwave";
            this.txtstopwave.Size = new System.Drawing.Size(117, 20);
            this.txtstopwave.TabIndex = 1;
            this.txtstopwave.Text = "1600";
            // 
            // txtstartwave
            // 
            this.txtstartwave.Location = new System.Drawing.Point(27, 54);
            this.txtstartwave.Name = "txtstartwave";
            this.txtstartwave.Size = new System.Drawing.Size(117, 20);
            this.txtstartwave.TabIndex = 0;
            this.txtstartwave.Text = "1500";
            // 
            // GroupBox1
            // 
            this.GroupBox1.Controls.Add(this.Label5);
            this.GroupBox1.Controls.Add(this.Label4);
            this.GroupBox1.Controls.Add(this.Label3);
            this.GroupBox1.Controls.Add(this.Label2);
            this.GroupBox1.Controls.Add(this.Label1);
            this.GroupBox1.Controls.Add(this.txtpower);
            this.GroupBox1.Controls.Add(this.cmbspeed);
            this.GroupBox1.Controls.Add(this.txtstepwave);
            this.GroupBox1.Controls.Add(this.txtstopwave);
            this.GroupBox1.Controls.Add(this.txtstartwave);
            this.GroupBox1.Location = new System.Drawing.Point(25, 22);
            this.GroupBox1.Name = "GroupBox1";
            this.GroupBox1.Size = new System.Drawing.Size(709, 101);
            this.GroupBox1.TabIndex = 8;
            this.GroupBox1.TabStop = false;
            this.GroupBox1.Text = "Sweep Setting";
            // 
            // chkeach_ch
            // 
            this.chkeach_ch.AutoSize = true;
            this.chkeach_ch.Location = new System.Drawing.Point(384, 194);
            this.chkeach_ch.Name = "chkeach_ch";
            this.chkeach_ch.Size = new System.Drawing.Size(145, 17);
            this.chkeach_ch.TabIndex = 16;
            this.chkeach_ch.Text = "each channel individually";
            this.chkeach_ch.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(758, 348);
            this.Controls.Add(this.chkeach_ch);
            this.Controls.Add(this.btnsaveRawdata);
            this.Controls.Add(this.btnsaveref_rawdata);
            this.Controls.Add(this.btnmeas);
            this.Controls.Add(this.btnget_reference);
            this.Controls.Add(this.btnset);
            this.Controls.Add(this.Button1);
            this.Controls.Add(this.GroupBox2);
            this.Controls.Add(this.GroupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "STS IL sample software";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.GroupBox2.ResumeLayout(false);
            this.GroupBox2.PerformLayout();
            this.GroupBox1.ResumeLayout(false);
            this.GroupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        internal System.Windows.Forms.OpenFileDialog OpenFileDialog1;
        internal System.Windows.Forms.Button btnsaveRawdata;
        internal System.Windows.Forms.SaveFileDialog SaveFileDialog1;
        internal System.Windows.Forms.Button btnsaveref_rawdata;
        internal System.Windows.Forms.Button btnmeas;
        internal System.Windows.Forms.Button btnget_reference;
        internal System.Windows.Forms.Button btnset;
        internal System.Windows.Forms.Label Label7;
        internal System.Windows.Forms.Label Label6;
        internal System.Windows.Forms.CheckedListBox chklst_range;
        internal System.Windows.Forms.CheckedListBox chklst_ch;
        internal System.Windows.Forms.Button Button1;
        internal System.Windows.Forms.GroupBox GroupBox2;
        internal System.Windows.Forms.Label Label5;
        internal System.Windows.Forms.Label Label4;
        internal System.Windows.Forms.Label Label3;
        internal System.Windows.Forms.Label Label2;
        internal System.Windows.Forms.Label Label1;
        internal System.Windows.Forms.TextBox txtpower;
        internal System.Windows.Forms.ComboBox cmbspeed;
        internal System.Windows.Forms.TextBox txtstepwave;
        internal System.Windows.Forms.TextBox txtstopwave;
        internal System.Windows.Forms.TextBox txtstartwave;
        internal System.Windows.Forms.GroupBox GroupBox1;
        internal System.Windows.Forms.CheckBox chkeach_ch;
    }
}

