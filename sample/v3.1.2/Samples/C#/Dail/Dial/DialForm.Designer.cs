namespace Dial
{
    partial class DialForm
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
            this.components = new System.ComponentModel.Container();
            this.listBox_OptAndEvtInfo = new System.Windows.Forms.ListBox();
            this.timer_loopCallOut = new System.Windows.Forms.Timer(this.components);
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
            this.listView_count = new System.Windows.Forms.ListView();
            this.columnHeader10 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader11 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader12 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader13 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader14 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader15 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader16 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader17 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader18 = new System.Windows.Forms.ColumnHeader();
            this.Btn_PreForRemove = new System.Windows.Forms.Button();
            this.listView_user = new System.Windows.Forms.ListView();
            this.columnHeader19 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader20 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader21 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader22 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader23 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader24 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader25 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader26 = new System.Windows.Forms.ColumnHeader();
            this.listView_pcm = new System.Windows.Forms.ListView();
            this.columnHeader27 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader28 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader29 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader30 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader31 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader32 = new System.Windows.Forms.ColumnHeader();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.Btn_Simulate = new System.Windows.Forms.Button();
            this.radioButton_Dtmf = new System.Windows.Forms.RadioButton();
            this.radioButton_Loop = new System.Windows.Forms.RadioButton();
            this.radioButton_Seq = new System.Windows.Forms.RadioButton();
            this.textBox_ModID = new System.Windows.Forms.TextBox();
            this.textBox_CalledNum = new System.Windows.Forms.TextBox();
            this.textBox_CallingNum = new System.Windows.Forms.TextBox();
            this.textBox_CalledLen = new System.Windows.Forms.TextBox();
            this.textBox_Port = new System.Windows.Forms.TextBox();
            this.textBox_ServerIP = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBox_ModID = new System.Windows.Forms.CheckBox();
            this.checkBox_Debug = new System.Windows.Forms.CheckBox();
            this.Btn_ReOpen = new System.Windows.Forms.Button();
            this.Btn_Exit = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // listBox_OptAndEvtInfo
            // 
            this.listBox_OptAndEvtInfo.FormattingEnabled = true;
            this.listBox_OptAndEvtInfo.HorizontalScrollbar = true;
            this.listBox_OptAndEvtInfo.ItemHeight = 12;
            this.listBox_OptAndEvtInfo.Location = new System.Drawing.Point(582, 1);
            this.listBox_OptAndEvtInfo.Name = "listBox_OptAndEvtInfo";
            this.listBox_OptAndEvtInfo.Size = new System.Drawing.Size(280, 304);
            this.listBox_OptAndEvtInfo.TabIndex = 4;
            // 
            // timer_loopCallOut
            // 
            /*this.timer_loopCallOut.Interval = 500;
            this.timer_loopCallOut.Tick += new System.EventHandler(this.timer_loopCallOut_Tick);*/
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
            this.listView_Main.Location = new System.Drawing.Point(0, 127);
            this.listView_Main.MultiSelect = false;
            this.listView_Main.Name = "listView_Main";
            this.listView_Main.Size = new System.Drawing.Size(580, 436);
            this.listView_Main.TabIndex = 9;
            this.listView_Main.UseCompatibleStateImageBehavior = false;
            this.listView_Main.View = System.Windows.Forms.View.Details;
            this.listView_Main.SelectedIndexChanged += new System.EventHandler(this.listView_Main_SelectedIndexChanged);
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
            // 
            // columnHeader4
            // 
            this.columnHeader4.Tag = "Line State";
            this.columnHeader4.Text = "Line State";
            this.columnHeader4.Width = 80;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Tag = "State";
            this.columnHeader5.Text = "State";
            this.columnHeader5.Width = 70;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Tag = "Called";
            this.columnHeader6.Text = "Called";
            // 
            // columnHeader7
            // 
            this.columnHeader7.Tag = "Calling";
            this.columnHeader7.Text = "Calling";
            // 
            // columnHeader8
            // 
            this.columnHeader8.Tag = "Line Dev";
            this.columnHeader8.Text = "Line Dev";
            // 
            // columnHeader9
            // 
            this.columnHeader9.Tag = "Fail Reason";
            this.columnHeader9.Text = "Fail Reason";
            this.columnHeader9.Width = 81;
            // 
            // listView_count
            // 
            this.listView_count.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader10,
            this.columnHeader11,
            this.columnHeader12,
            this.columnHeader13,
            this.columnHeader14,
            this.columnHeader15,
            this.columnHeader16,
            this.columnHeader17,
            this.columnHeader18});
            this.listView_count.FullRowSelect = true;
            this.listView_count.Location = new System.Drawing.Point(0, 1);
            this.listView_count.MultiSelect = false;
            this.listView_count.Name = "listView_count";
            this.listView_count.Size = new System.Drawing.Size(580, 97);
            this.listView_count.TabIndex = 10;
            this.listView_count.UseCompatibleStateImageBehavior = false;
            this.listView_count.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader10
            // 
            this.columnHeader10.Tag = "ID";
            this.columnHeader10.Text = "ID";
            this.columnHeader10.Width = 48;
            // 
            // columnHeader11
            // 
            this.columnHeader11.Tag = "Mod ID";
            this.columnHeader11.Text = "Mod ID";
            // 
            // columnHeader12
            // 
            this.columnHeader12.Tag = "Pcm/Open";
            this.columnHeader12.Text = "Pcm/Open";
            // 
            // columnHeader13
            // 
            this.columnHeader13.Tag = "Trk/Open";
            this.columnHeader13.Text = "Trk/Open";
            // 
            // columnHeader14
            // 
            this.columnHeader14.Tag = "Voc/Open";
            this.columnHeader14.Text = "Voc/Open";
            // 
            // columnHeader15
            // 
            this.columnHeader15.Tag = "Voc Free";
            this.columnHeader15.Text = "Voc Free";
            // 
            // columnHeader16
            // 
            this.columnHeader16.Tag = "User/Open";
            this.columnHeader16.Text = "User/Open";
            this.columnHeader16.Width = 70;
            // 
            // columnHeader17
            // 
            this.columnHeader17.Tag = "Err Flag";
            this.columnHeader17.Text = "Err Flag";
            // 
            // columnHeader18
            // 
            this.columnHeader18.Tag = "Remove Sate";
            this.columnHeader18.Text = "Remove Sate";
            this.columnHeader18.Width = 80;
            // 
            // Btn_PreForRemove
            // 
            this.Btn_PreForRemove.Location = new System.Drawing.Point(403, 101);
            this.Btn_PreForRemove.Name = "Btn_PreForRemove";
            this.Btn_PreForRemove.Size = new System.Drawing.Size(123, 23);
            this.Btn_PreForRemove.TabIndex = 11;
            this.Btn_PreForRemove.Text = "Prepare For Remove";
            this.Btn_PreForRemove.UseVisualStyleBackColor = true;
            this.Btn_PreForRemove.Click += new System.EventHandler(this.Btn_PreForRemove_Click);
            // 
            // listView_user
            // 
            this.listView_user.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader19,
            this.columnHeader20,
            this.columnHeader21,
            this.columnHeader22,
            this.columnHeader23,
            this.columnHeader24,
            this.columnHeader25,
            this.columnHeader26});
            this.listView_user.Location = new System.Drawing.Point(0, 566);
            this.listView_user.Name = "listView_user";
            this.listView_user.Size = new System.Drawing.Size(580, 121);
            this.listView_user.TabIndex = 12;
            this.listView_user.UseCompatibleStateImageBehavior = false;
            this.listView_user.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader19
            // 
            this.columnHeader19.Tag = "ID";
            this.columnHeader19.Text = "ID";
            this.columnHeader19.Width = 30;
            // 
            // columnHeader20
            // 
            this.columnHeader20.Tag = "Mod,Ch";
            this.columnHeader20.Text = "Mod,Ch";
            this.columnHeader20.Width = 50;
            // 
            // columnHeader21
            // 
            this.columnHeader21.Tag = "Type";
            this.columnHeader21.Text = "Type";
            // 
            // columnHeader22
            // 
            this.columnHeader22.Tag = "Line State";
            this.columnHeader22.Text = "Line State";
            this.columnHeader22.Width = 75;
            // 
            // columnHeader23
            // 
            this.columnHeader23.Tag = "State";
            this.columnHeader23.Text = "State";
            // 
            // columnHeader24
            // 
            this.columnHeader24.Tag = "DTMF";
            this.columnHeader24.Text = "DTMF";
            // 
            // columnHeader25
            // 
            this.columnHeader25.Tag = "Voc Info";
            this.columnHeader25.Text = "Voc Info";
            this.columnHeader25.Width = 79;
            // 
            // columnHeader26
            // 
            this.columnHeader26.Tag = "Link Dev";
            this.columnHeader26.Text = "Link Dev";
            this.columnHeader26.Width = 84;
            // 
            // listView_pcm
            // 
            this.listView_pcm.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader27,
            this.columnHeader28,
            this.columnHeader29,
            this.columnHeader30,
            this.columnHeader31,
            this.columnHeader32});
            this.listView_pcm.Location = new System.Drawing.Point(582, 309);
            this.listView_pcm.Name = "listView_pcm";
            this.listView_pcm.Size = new System.Drawing.Size(280, 129);
            this.listView_pcm.TabIndex = 13;
            this.listView_pcm.UseCompatibleStateImageBehavior = false;
            this.listView_pcm.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader27
            // 
            this.columnHeader27.Tag = "PcmID";
            this.columnHeader27.Text = "PcmID";
            this.columnHeader27.Width = 45;
            // 
            // columnHeader28
            // 
            this.columnHeader28.Tag = "Type";
            this.columnHeader28.Text = "Type";
            // 
            // columnHeader29
            // 
            this.columnHeader29.Tag = "Alarm Value";
            this.columnHeader29.Text = "Alarm Value";
            this.columnHeader29.Width = 80;
            // 
            // columnHeader30
            // 
            this.columnHeader30.Tag = "Sig Detect";
            this.columnHeader30.Text = "Sig Detect";
            this.columnHeader30.Width = 80;
            // 
            // columnHeader31
            // 
            this.columnHeader31.Tag = "Frame Sync";
            this.columnHeader31.Text = "Frame Sync";
            this.columnHeader31.Width = 80;
            // 
            // columnHeader32
            // 
            this.columnHeader32.Tag = "Remote Alarm";
            this.columnHeader32.Text = "Remote Alarm";
            this.columnHeader32.Width = 85;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Btn_Simulate);
            this.groupBox1.Controls.Add(this.radioButton_Dtmf);
            this.groupBox1.Controls.Add(this.radioButton_Loop);
            this.groupBox1.Controls.Add(this.radioButton_Seq);
            this.groupBox1.Controls.Add(this.textBox_ModID);
            this.groupBox1.Controls.Add(this.textBox_CalledNum);
            this.groupBox1.Controls.Add(this.textBox_CallingNum);
            this.groupBox1.Controls.Add(this.textBox_CalledLen);
            this.groupBox1.Controls.Add(this.textBox_Port);
            this.groupBox1.Controls.Add(this.textBox_ServerIP);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.checkBox_ModID);
            this.groupBox1.Controls.Add(this.checkBox_Debug);
            this.groupBox1.Location = new System.Drawing.Point(582, 444);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(280, 229);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Config";
            // 
            // Btn_Simulate
            // 
            this.Btn_Simulate.Location = new System.Drawing.Point(28, 169);
            this.Btn_Simulate.Name = "Btn_Simulate";
            this.Btn_Simulate.Size = new System.Drawing.Size(78, 23);
            this.Btn_Simulate.TabIndex = 25;
            this.Btn_Simulate.Text = "Simulate";
            this.Btn_Simulate.UseVisualStyleBackColor = true;
            this.Btn_Simulate.Click += new System.EventHandler(this.Btn_Simulate_Click);
            // 
            // radioButton_Dtmf
            // 
            this.radioButton_Dtmf.AutoSize = true;
            this.radioButton_Dtmf.Location = new System.Drawing.Point(164, 144);
            this.radioButton_Dtmf.Name = "radioButton_Dtmf";
            this.radioButton_Dtmf.Size = new System.Drawing.Size(89, 16);
            this.radioButton_Dtmf.TabIndex = 18;
            this.radioButton_Dtmf.TabStop = true;
            this.radioButton_Dtmf.Text = "Dtmf Tail 3";
            this.radioButton_Dtmf.UseVisualStyleBackColor = true;
            // 
            // radioButton_Loop
            // 
            this.radioButton_Loop.AutoSize = true;
            this.radioButton_Loop.Location = new System.Drawing.Point(99, 144);
            this.radioButton_Loop.Name = "radioButton_Loop";
            this.radioButton_Loop.Size = new System.Drawing.Size(47, 16);
            this.radioButton_Loop.TabIndex = 16;
            this.radioButton_Loop.TabStop = true;
            this.radioButton_Loop.Text = "Loop";
            this.radioButton_Loop.UseVisualStyleBackColor = true;
            // 
            // radioButton_Seq
            // 
            this.radioButton_Seq.AutoSize = true;
            this.radioButton_Seq.Location = new System.Drawing.Point(11, 144);
            this.radioButton_Seq.Name = "radioButton_Seq";
            this.radioButton_Seq.Size = new System.Drawing.Size(71, 16);
            this.radioButton_Seq.TabIndex = 14;
            this.radioButton_Seq.TabStop = true;
            this.radioButton_Seq.Text = "Sequence";
            this.radioButton_Seq.UseVisualStyleBackColor = true;
            // 
            // textBox_ModID
            // 
            this.textBox_ModID.Location = new System.Drawing.Point(159, 203);
            this.textBox_ModID.Name = "textBox_ModID";
            this.textBox_ModID.Size = new System.Drawing.Size(115, 21);
            this.textBox_ModID.TabIndex = 13;
            // 
            // textBox_CalledNum
            // 
            this.textBox_CalledNum.Location = new System.Drawing.Point(159, 171);
            this.textBox_CalledNum.Name = "textBox_CalledNum";
            this.textBox_CalledNum.Size = new System.Drawing.Size(115, 21);
            this.textBox_CalledNum.TabIndex = 12;
            // 
            // textBox_CallingNum
            // 
            this.textBox_CallingNum.Location = new System.Drawing.Point(159, 101);
            this.textBox_CallingNum.Name = "textBox_CallingNum";
            this.textBox_CallingNum.Size = new System.Drawing.Size(115, 21);
            this.textBox_CallingNum.TabIndex = 11;
            // 
            // textBox_CalledLen
            // 
            this.textBox_CalledLen.Location = new System.Drawing.Point(159, 78);
            this.textBox_CalledLen.Name = "textBox_CalledLen";
            this.textBox_CalledLen.Size = new System.Drawing.Size(115, 21);
            this.textBox_CalledLen.TabIndex = 10;
            // 
            // textBox_Port
            // 
            this.textBox_Port.Location = new System.Drawing.Point(159, 55);
            this.textBox_Port.Name = "textBox_Port";
            this.textBox_Port.Size = new System.Drawing.Size(115, 21);
            this.textBox_Port.TabIndex = 9;
            // 
            // textBox_ServerIP
            // 
            this.textBox_ServerIP.Location = new System.Drawing.Point(159, 33);
            this.textBox_ServerIP.Name = "textBox_ServerIP";
            this.textBox_ServerIP.Size = new System.Drawing.Size(115, 21);
            this.textBox_ServerIP.TabIndex = 8;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 129);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 12);
            this.label5.TabIndex = 6;
            this.label5.Text = "CallOutRule:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(76, 104);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 12);
            this.label4.TabIndex = 5;
            this.label4.Text = "Calling Num:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(82, 81);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "Called Len:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(118, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "Port:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(58, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "Server IP Addr:";
            // 
            // checkBox_ModID
            // 
            this.checkBox_ModID.AutoSize = true;
            this.checkBox_ModID.Location = new System.Drawing.Point(27, 208);
            this.checkBox_ModID.Name = "checkBox_ModID";
            this.checkBox_ModID.Size = new System.Drawing.Size(126, 16);
            this.checkBox_ModID.TabIndex = 1;
            this.checkBox_ModID.Text = "Part Work,Mod ID:";
            this.checkBox_ModID.UseVisualStyleBackColor = true;
            // 
            // checkBox_Debug
            // 
            this.checkBox_Debug.AutoSize = true;
            this.checkBox_Debug.Location = new System.Drawing.Point(28, 17);
            this.checkBox_Debug.Name = "checkBox_Debug";
            this.checkBox_Debug.Size = new System.Drawing.Size(96, 16);
            this.checkBox_Debug.TabIndex = 0;
            this.checkBox_Debug.Text = "Debug Mod On";
            this.checkBox_Debug.UseVisualStyleBackColor = true;
            // 
            // Btn_ReOpen
            // 
            this.Btn_ReOpen.Location = new System.Drawing.Point(613, 679);
            this.Btn_ReOpen.Name = "Btn_ReOpen";
            this.Btn_ReOpen.Size = new System.Drawing.Size(75, 23);
            this.Btn_ReOpen.TabIndex = 15;
            this.Btn_ReOpen.Text = "ReOpen";
            this.Btn_ReOpen.UseVisualStyleBackColor = true;
            this.Btn_ReOpen.Click += new System.EventHandler(this.Btn_ReOpen_Click);
            // 
            // Btn_Exit
            // 
            this.Btn_Exit.Location = new System.Drawing.Point(787, 679);
            this.Btn_Exit.Name = "Btn_Exit";
            this.Btn_Exit.Size = new System.Drawing.Size(75, 23);
            this.Btn_Exit.TabIndex = 16;
            this.Btn_Exit.Text = "Exit";
            this.Btn_Exit.UseVisualStyleBackColor = true;
            this.Btn_Exit.Click += new System.EventHandler(this.Btn_Exit_Click);
            // 
            // DialForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(861, 702);
            this.Controls.Add(this.Btn_Exit);
            this.Controls.Add(this.Btn_ReOpen);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.listView_pcm);
            this.Controls.Add(this.listView_user);
            this.Controls.Add(this.Btn_PreForRemove);
            this.Controls.Add(this.listView_count);
            this.Controls.Add(this.listView_Main);
            this.Controls.Add(this.listBox_OptAndEvtInfo);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "DialForm";
            this.Text = "Donjin XMS Dial System";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox listBox_OptAndEvtInfo;
        private System.Windows.Forms.Timer timer_loopCallOut;
        
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
        private System.Windows.Forms.ListView listView_count;
        private System.Windows.Forms.ColumnHeader columnHeader10;
        private System.Windows.Forms.ColumnHeader columnHeader11;
        private System.Windows.Forms.ColumnHeader columnHeader12;
        private System.Windows.Forms.ColumnHeader columnHeader13;
        private System.Windows.Forms.ColumnHeader columnHeader14;
        private System.Windows.Forms.ColumnHeader columnHeader15;
        private System.Windows.Forms.ColumnHeader columnHeader16;
        private System.Windows.Forms.ColumnHeader columnHeader17;
        private System.Windows.Forms.ColumnHeader columnHeader18;
        private System.Windows.Forms.Button Btn_PreForRemove;
        private System.Windows.Forms.ListView listView_user;
        private System.Windows.Forms.ColumnHeader columnHeader19;
        private System.Windows.Forms.ColumnHeader columnHeader20;
        private System.Windows.Forms.ColumnHeader columnHeader21;
        private System.Windows.Forms.ColumnHeader columnHeader22;
        private System.Windows.Forms.ColumnHeader columnHeader23;
        private System.Windows.Forms.ColumnHeader columnHeader24;
        private System.Windows.Forms.ColumnHeader columnHeader25;
        private System.Windows.Forms.ColumnHeader columnHeader26;
        private System.Windows.Forms.ListView listView_pcm;
        private System.Windows.Forms.ColumnHeader columnHeader27;
        private System.Windows.Forms.ColumnHeader columnHeader28;
        private System.Windows.Forms.ColumnHeader columnHeader29;
        private System.Windows.Forms.ColumnHeader columnHeader30;
        private System.Windows.Forms.ColumnHeader columnHeader31;
        private System.Windows.Forms.ColumnHeader columnHeader32;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radioButton_Dtmf;
        private System.Windows.Forms.RadioButton radioButton_Loop;
        private System.Windows.Forms.RadioButton radioButton_Seq;
        private System.Windows.Forms.TextBox textBox_ModID;
        private System.Windows.Forms.TextBox textBox_CalledNum;
        private System.Windows.Forms.TextBox textBox_CallingNum;
        private System.Windows.Forms.TextBox textBox_CalledLen;
        private System.Windows.Forms.TextBox textBox_Port;
        private System.Windows.Forms.TextBox textBox_ServerIP;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBox_ModID;
        private System.Windows.Forms.CheckBox checkBox_Debug;
        private System.Windows.Forms.Button Btn_Simulate;
        private System.Windows.Forms.Button Btn_ReOpen;
        private System.Windows.Forms.Button Btn_Exit;
    }
}

