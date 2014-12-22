namespace Demo
{
    partial class DemoForm
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
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.listView_Main = new System.Windows.Forms.ListView();
            this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader3 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader4 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader5 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader6 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader7 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader8 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader9 = new System.Windows.Forms.ColumnHeader();
            this.listBox_OptAndEvtInfo = new System.Windows.Forms.ListBox();
            this.listView_Count = new System.Windows.Forms.ListView();
            this.columnHeader10 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader11 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader12 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader13 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader14 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader15 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader16 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader17 = new System.Windows.Forms.ColumnHeader();
            this.BtnForRemove = new System.Windows.Forms.Button();
            this.listView_pcm = new System.Windows.Forms.ListView();
            this.columnHeader18 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader19 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader20 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader21 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader22 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader23 = new System.Windows.Forms.ColumnHeader();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.checkBox_WorkMode = new System.Windows.Forms.CheckBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.radioButton_VocSameMode = new System.Windows.Forms.RadioButton();
            this.radioButton_VocMost = new System.Windows.Forms.RadioButton();
            this.radioButton_VocFix = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.radioButton_Disp30 = new System.Windows.Forms.RadioButton();
            this.radioButton_Disp31 = new System.Windows.Forms.RadioButton();
            this.radioButton_Disp32 = new System.Windows.Forms.RadioButton();
            this.textBox_ModID = new System.Windows.Forms.TextBox();
            this.textBox_VocPath = new System.Windows.Forms.TextBox();
            this.textBox_Port = new System.Windows.Forms.TextBox();
            this.textBox_ServerIP = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBox_ModID = new System.Windows.Forms.CheckBox();
            this.checkBox_Debug = new System.Windows.Forms.CheckBox();
            this.Btn_ReOpen = new System.Windows.Forms.Button();
            this.Btn_Exit = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // listView_Main
            // 
            this.listView_Main.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6,
            this.columnHeader7,
            this.columnHeader8,
            this.columnHeader9});
            this.listView_Main.FullRowSelect = true;
            this.listView_Main.Location = new System.Drawing.Point(2, 130);
            this.listView_Main.MultiSelect = false;
            this.listView_Main.Name = "listView_Main";
            this.listView_Main.Size = new System.Drawing.Size(584, 459);
            this.listView_Main.TabIndex = 3;
            this.listView_Main.UseCompatibleStateImageBehavior = false;
            this.listView_Main.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Tag = "ID";
            this.columnHeader1.Text = "ID";
            this.columnHeader1.Width = 35;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Tag = "Mod,Ch";
            this.columnHeader2.Text = "Mod,Ch";
            this.columnHeader2.Width = 50;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Tag = "Type";
            this.columnHeader3.Text = "Type";
            this.columnHeader3.Width = 65;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Tag = "Line State";
            this.columnHeader4.Text = "Line State";
            this.columnHeader4.Width = 81;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Tag = "State";
            this.columnHeader5.Text = "State";
            this.columnHeader5.Width = 64;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Tag = "Called";
            this.columnHeader6.Text = "Called";
            this.columnHeader6.Width = 68;
            // 
            // columnHeader7
            // 
            this.columnHeader7.Tag = "Calling";
            this.columnHeader7.Text = "Calling";
            this.columnHeader7.Width = 66;
            // 
            // columnHeader8
            // 
            this.columnHeader8.Tag = "DTMF";
            this.columnHeader8.Text = "DTMF";
            this.columnHeader8.Width = 67;
            // 
            // columnHeader9
            // 
            this.columnHeader9.Tag = "Voc Info";
            this.columnHeader9.Text = "Voc Info";
            this.columnHeader9.Width = 68;
            // 
            // listBox_OptAndEvtInfo
            // 
            this.listBox_OptAndEvtInfo.FormattingEnabled = true;
            this.listBox_OptAndEvtInfo.HorizontalScrollbar = true;
            this.listBox_OptAndEvtInfo.ItemHeight = 12;
            this.listBox_OptAndEvtInfo.Location = new System.Drawing.Point(590, 1);
            this.listBox_OptAndEvtInfo.Name = "listBox_OptAndEvtInfo";
            this.listBox_OptAndEvtInfo.Size = new System.Drawing.Size(271, 436);
            this.listBox_OptAndEvtInfo.TabIndex = 4;
            // 
            // listView_Count
            // 
            this.listView_Count.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader10,
            this.columnHeader11,
            this.columnHeader12,
            this.columnHeader13,
            this.columnHeader14,
            this.columnHeader15,
            this.columnHeader16,
            this.columnHeader17});
            this.listView_Count.FullRowSelect = true;
            this.listView_Count.Location = new System.Drawing.Point(0, 1);
            this.listView_Count.MultiSelect = false;
            this.listView_Count.Name = "listView_Count";
            this.listView_Count.Size = new System.Drawing.Size(584, 103);
            this.listView_Count.TabIndex = 5;
            this.listView_Count.UseCompatibleStateImageBehavior = false;
            this.listView_Count.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader10
            // 
            this.columnHeader10.Tag = "ID";
            this.columnHeader10.Text = "ID";
            this.columnHeader10.Width = 35;
            // 
            // columnHeader11
            // 
            this.columnHeader11.Tag = "Mod ID";
            this.columnHeader11.Text = "Mod ID";
            this.columnHeader11.Width = 50;
            // 
            // columnHeader12
            // 
            this.columnHeader12.Tag = "Pcm/Open";
            this.columnHeader12.Text = "Pcm/Open";
            this.columnHeader12.Width = 67;
            // 
            // columnHeader13
            // 
            this.columnHeader13.Tag = "Trk/Open";
            this.columnHeader13.Text = "Trk/Open";
            this.columnHeader13.Width = 68;
            // 
            // columnHeader14
            // 
            this.columnHeader14.Tag = "Voc/Open";
            this.columnHeader14.Text = "Voc/Open";
            this.columnHeader14.Width = 65;
            // 
            // columnHeader15
            // 
            this.columnHeader15.Tag = "Voc Free";
            this.columnHeader15.Text = "Voc Free";
            this.columnHeader15.Width = 66;
            // 
            // columnHeader16
            // 
            this.columnHeader16.Tag = "Err Flag";
            this.columnHeader16.Text = "Err Flag";
            this.columnHeader16.Width = 67;
            // 
            // columnHeader17
            // 
            this.columnHeader17.Tag = "Remove State";
            this.columnHeader17.Text = "Remove State";
            this.columnHeader17.Width = 93;
            // 
            // BtnForRemove
            // 
            this.BtnForRemove.Location = new System.Drawing.Point(442, 106);
            this.BtnForRemove.Name = "BtnForRemove";
            this.BtnForRemove.Size = new System.Drawing.Size(130, 23);
            this.BtnForRemove.TabIndex = 6;
            this.BtnForRemove.Text = "Prepare For Remove";
            this.BtnForRemove.UseVisualStyleBackColor = true;
            this.BtnForRemove.Click += new System.EventHandler(this.BtnForRemove_Click);
            // 
            // listView_pcm
            // 
            this.listView_pcm.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader18,
            this.columnHeader19,
            this.columnHeader20,
            this.columnHeader21,
            this.columnHeader22,
            this.columnHeader23});
            this.listView_pcm.FullRowSelect = true;
            this.listView_pcm.Location = new System.Drawing.Point(0, 592);
            this.listView_pcm.Name = "listView_pcm";
            this.listView_pcm.Size = new System.Drawing.Size(584, 120);
            this.listView_pcm.TabIndex = 7;
            this.listView_pcm.UseCompatibleStateImageBehavior = false;
            this.listView_pcm.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader18
            // 
            this.columnHeader18.Tag = "Pcm ID";
            this.columnHeader18.Text = "Pcm ID";
            this.columnHeader18.Width = 50;
            // 
            // columnHeader19
            // 
            this.columnHeader19.Tag = "Type";
            this.columnHeader19.Text = "Type";
            this.columnHeader19.Width = 64;
            // 
            // columnHeader20
            // 
            this.columnHeader20.Tag = "Alarm Value";
            this.columnHeader20.Text = "Alarm Value";
            this.columnHeader20.Width = 82;
            // 
            // columnHeader21
            // 
            this.columnHeader21.Tag = "Sig Detect";
            this.columnHeader21.Text = "Sig Detect";
            this.columnHeader21.Width = 88;
            // 
            // columnHeader22
            // 
            this.columnHeader22.Tag = "Frame Sync";
            this.columnHeader22.Text = "Frame Sync";
            this.columnHeader22.Width = 89;
            // 
            // columnHeader23
            // 
            this.columnHeader23.Tag = "Remote Alarm";
            this.columnHeader23.Text = "Remote Alarm";
            this.columnHeader23.Width = 96;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.checkBox_WorkMode);
            this.groupBox1.Controls.Add(this.groupBox3);
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Controls.Add(this.textBox_ModID);
            this.groupBox1.Controls.Add(this.textBox_VocPath);
            this.groupBox1.Controls.Add(this.textBox_Port);
            this.groupBox1.Controls.Add(this.textBox_ServerIP);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.checkBox_ModID);
            this.groupBox1.Controls.Add(this.checkBox_Debug);
            this.groupBox1.Location = new System.Drawing.Point(592, 444);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(269, 238);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Config";
            // 
            // checkBox_WorkMode
            // 
            this.checkBox_WorkMode.AutoSize = true;
            this.checkBox_WorkMode.Location = new System.Drawing.Point(133, 20);
            this.checkBox_WorkMode.Name = "checkBox_WorkMode";
            this.checkBox_WorkMode.Size = new System.Drawing.Size(114, 16);
            this.checkBox_WorkMode.TabIndex = 19;
            this.checkBox_WorkMode.Text = "work in windows";
            this.checkBox_WorkMode.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.radioButton_VocSameMode);
            this.groupBox3.Controls.Add(this.radioButton_VocMost);
            this.groupBox3.Controls.Add(this.radioButton_VocFix);
            this.groupBox3.Location = new System.Drawing.Point(15, 165);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(250, 43);
            this.groupBox3.TabIndex = 18;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Voice Search Rule:";
            // 
            // radioButton_VocSameMode
            // 
            this.radioButton_VocSameMode.AutoSize = true;
            this.radioButton_VocSameMode.Location = new System.Drawing.Point(71, 20);
            this.radioButton_VocSameMode.Name = "radioButton_VocSameMode";
            this.radioButton_VocSameMode.Size = new System.Drawing.Size(71, 16);
            this.radioButton_VocSameMode.TabIndex = 15;
            this.radioButton_VocSameMode.TabStop = true;
            this.radioButton_VocSameMode.Text = "Same Mod";
            this.radioButton_VocSameMode.UseVisualStyleBackColor = true;
            // 
            // radioButton_VocMost
            // 
            this.radioButton_VocMost.AutoSize = true;
            this.radioButton_VocMost.Location = new System.Drawing.Point(161, 20);
            this.radioButton_VocMost.Name = "radioButton_VocMost";
            this.radioButton_VocMost.Size = new System.Drawing.Size(83, 16);
            this.radioButton_VocMost.TabIndex = 16;
            this.radioButton_VocMost.TabStop = true;
            this.radioButton_VocMost.Text = "Most First";
            this.radioButton_VocMost.UseVisualStyleBackColor = true;
            // 
            // radioButton_VocFix
            // 
            this.radioButton_VocFix.AutoSize = true;
            this.radioButton_VocFix.Location = new System.Drawing.Point(6, 20);
            this.radioButton_VocFix.Name = "radioButton_VocFix";
            this.radioButton_VocFix.Size = new System.Drawing.Size(41, 16);
            this.radioButton_VocFix.TabIndex = 14;
            this.radioButton_VocFix.TabStop = true;
            this.radioButton_VocFix.Text = "Fix";
            this.radioButton_VocFix.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.radioButton_Disp30);
            this.groupBox2.Controls.Add(this.radioButton_Disp31);
            this.groupBox2.Controls.Add(this.radioButton_Disp32);
            this.groupBox2.Location = new System.Drawing.Point(15, 118);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(250, 43);
            this.groupBox2.TabIndex = 17;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Disp Channel Per Pcm:";
            // 
            // radioButton_Disp30
            // 
            this.radioButton_Disp30.AutoSize = true;
            this.radioButton_Disp30.Location = new System.Drawing.Point(7, 20);
            this.radioButton_Disp30.Name = "radioButton_Disp30";
            this.radioButton_Disp30.Size = new System.Drawing.Size(35, 16);
            this.radioButton_Disp30.TabIndex = 11;
            this.radioButton_Disp30.TabStop = true;
            this.radioButton_Disp30.Text = "30";
            this.radioButton_Disp30.UseVisualStyleBackColor = true;
            // 
            // radioButton_Disp31
            // 
            this.radioButton_Disp31.AutoSize = true;
            this.radioButton_Disp31.Location = new System.Drawing.Point(93, 20);
            this.radioButton_Disp31.Name = "radioButton_Disp31";
            this.radioButton_Disp31.Size = new System.Drawing.Size(35, 16);
            this.radioButton_Disp31.TabIndex = 12;
            this.radioButton_Disp31.TabStop = true;
            this.radioButton_Disp31.Text = "31";
            this.radioButton_Disp31.UseVisualStyleBackColor = true;
            // 
            // radioButton_Disp32
            // 
            this.radioButton_Disp32.AutoSize = true;
            this.radioButton_Disp32.Location = new System.Drawing.Point(179, 20);
            this.radioButton_Disp32.Name = "radioButton_Disp32";
            this.radioButton_Disp32.Size = new System.Drawing.Size(35, 16);
            this.radioButton_Disp32.TabIndex = 13;
            this.radioButton_Disp32.TabStop = true;
            this.radioButton_Disp32.Text = "32";
            this.radioButton_Disp32.UseVisualStyleBackColor = true;
            // 
            // textBox_ModID
            // 
            this.textBox_ModID.Location = new System.Drawing.Point(159, 211);
            this.textBox_ModID.Name = "textBox_ModID";
            this.textBox_ModID.Size = new System.Drawing.Size(106, 21);
            this.textBox_ModID.TabIndex = 10;
            // 
            // textBox_VocPath
            // 
            this.textBox_VocPath.Location = new System.Drawing.Point(159, 91);
            this.textBox_VocPath.Name = "textBox_VocPath";
            this.textBox_VocPath.Size = new System.Drawing.Size(106, 21);
            this.textBox_VocPath.TabIndex = 9;
            // 
            // textBox_Port
            // 
            this.textBox_Port.Location = new System.Drawing.Point(159, 64);
            this.textBox_Port.Name = "textBox_Port";
            this.textBox_Port.Size = new System.Drawing.Size(106, 21);
            this.textBox_Port.TabIndex = 8;
            // 
            // textBox_ServerIP
            // 
            this.textBox_ServerIP.Location = new System.Drawing.Point(159, 37);
            this.textBox_ServerIP.Name = "textBox_ServerIP";
            this.textBox_ServerIP.Size = new System.Drawing.Size(106, 21);
            this.textBox_ServerIP.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(84, 94);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "Voc Path:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(108, 67);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "Port:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(48, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "Server IP Addr:";
            // 
            // checkBox_ModID
            // 
            this.checkBox_ModID.AutoSize = true;
            this.checkBox_ModID.Location = new System.Drawing.Point(8, 216);
            this.checkBox_ModID.Name = "checkBox_ModID";
            this.checkBox_ModID.Size = new System.Drawing.Size(144, 16);
            this.checkBox_ModID.TabIndex = 1;
            this.checkBox_ModID.Text = "Part Work,Module ID:";
            this.checkBox_ModID.UseVisualStyleBackColor = true;
            // 
            // checkBox_Debug
            // 
            this.checkBox_Debug.AutoSize = true;
            this.checkBox_Debug.Location = new System.Drawing.Point(22, 20);
            this.checkBox_Debug.Name = "checkBox_Debug";
            this.checkBox_Debug.Size = new System.Drawing.Size(96, 16);
            this.checkBox_Debug.TabIndex = 0;
            this.checkBox_Debug.Text = "Debug Mod On";
            this.checkBox_Debug.UseVisualStyleBackColor = true;
            // 
            // Btn_ReOpen
            // 
            this.Btn_ReOpen.Location = new System.Drawing.Point(592, 688);
            this.Btn_ReOpen.Name = "Btn_ReOpen";
            this.Btn_ReOpen.Size = new System.Drawing.Size(72, 24);
            this.Btn_ReOpen.TabIndex = 9;
            this.Btn_ReOpen.Text = "ReOpen";
            this.Btn_ReOpen.UseVisualStyleBackColor = true;
            this.Btn_ReOpen.Click += new System.EventHandler(this.Btn_ReOpen_Click);
            // 
            // Btn_Exit
            // 
            this.Btn_Exit.Location = new System.Drawing.Point(786, 688);
            this.Btn_Exit.Name = "Btn_Exit";
            this.Btn_Exit.Size = new System.Drawing.Size(75, 24);
            this.Btn_Exit.TabIndex = 10;
            this.Btn_Exit.Text = "Exit";
            this.Btn_Exit.UseVisualStyleBackColor = true;
            this.Btn_Exit.Click += new System.EventHandler(this.Btn_Exit_Click);
            // 
            // DemoForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(861, 711);
            this.Controls.Add(this.Btn_Exit);
            this.Controls.Add(this.Btn_ReOpen);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.listView_pcm);
            this.Controls.Add(this.BtnForRemove);
            this.Controls.Add(this.listView_Count);
            this.Controls.Add(this.listBox_OptAndEvtInfo);
            this.Controls.Add(this.listView_Main);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "DemoForm";
            this.Text = "Donjin XMS Bank Demo System";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listView_Main;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.ColumnHeader columnHeader7;
        private System.Windows.Forms.ColumnHeader columnHeader8;
        private System.Windows.Forms.ColumnHeader columnHeader9;
        private System.Windows.Forms.ListBox listBox_OptAndEvtInfo;
        private System.Windows.Forms.ListView listView_Count;
        private System.Windows.Forms.Button BtnForRemove;
        private System.Windows.Forms.ListView listView_pcm;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button Btn_ReOpen;
        private System.Windows.Forms.Button Btn_Exit;
        private System.Windows.Forms.ColumnHeader columnHeader10;
        private System.Windows.Forms.ColumnHeader columnHeader11;
        private System.Windows.Forms.ColumnHeader columnHeader12;
        private System.Windows.Forms.ColumnHeader columnHeader13;
        private System.Windows.Forms.ColumnHeader columnHeader14;
        private System.Windows.Forms.ColumnHeader columnHeader15;
        private System.Windows.Forms.ColumnHeader columnHeader16;
        private System.Windows.Forms.ColumnHeader columnHeader17;
        private System.Windows.Forms.ColumnHeader columnHeader18;
        private System.Windows.Forms.ColumnHeader columnHeader19;
        private System.Windows.Forms.ColumnHeader columnHeader20;
        private System.Windows.Forms.ColumnHeader columnHeader21;
        private System.Windows.Forms.ColumnHeader columnHeader22;
        private System.Windows.Forms.ColumnHeader columnHeader23;
        private System.Windows.Forms.TextBox textBox_ModID;
        private System.Windows.Forms.TextBox textBox_VocPath;
        private System.Windows.Forms.TextBox textBox_Port;
        private System.Windows.Forms.TextBox textBox_ServerIP;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBox_ModID;
        private System.Windows.Forms.CheckBox checkBox_Debug;
        private System.Windows.Forms.RadioButton radioButton_VocMost;
        private System.Windows.Forms.RadioButton radioButton_VocSameMode;
        private System.Windows.Forms.RadioButton radioButton_VocFix;
        private System.Windows.Forms.RadioButton radioButton_Disp32;
        private System.Windows.Forms.RadioButton radioButton_Disp31;
        private System.Windows.Forms.RadioButton radioButton_Disp30;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox checkBox_WorkMode;
    }
}

