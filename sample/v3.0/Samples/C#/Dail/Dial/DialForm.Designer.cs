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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DialForm));
            this.button_initsystem = new System.Windows.Forms.Button();
            this.button_exitsystem = new System.Windows.Forms.Button();
            this.listBox_OptAndEvtInfo = new System.Windows.Forms.ListBox();
            this.button_simulate = new System.Windows.Forms.Button();
            this.textBox_Callee = new System.Windows.Forms.TextBox();
            this.checkBox_IsLoop = new System.Windows.Forms.CheckBox();
            this.timer_loopCallOut = new System.Windows.Forms.Timer(this.components);
            this.axDJAcsAPI = new AxDJACSAPILib.AxDJAcsAPI();
            this.listView_InterfInfo = new System.Windows.Forms.ListView();
            this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader3 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader4 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader5 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader6 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader7 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader8 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader9 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader10 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader11 = new System.Windows.Forms.ColumnHeader();
            ((System.ComponentModel.ISupportInitialize)(this.axDJAcsAPI)).BeginInit();
            this.SuspendLayout();
            // 
            // button_initsystem
            // 
            this.button_initsystem.Location = new System.Drawing.Point(12, 21);
            this.button_initsystem.Name = "button_initsystem";
            this.button_initsystem.Size = new System.Drawing.Size(75, 23);
            this.button_initsystem.TabIndex = 1;
            this.button_initsystem.Text = "InitSystem";
            this.button_initsystem.UseVisualStyleBackColor = true;
            this.button_initsystem.Click += new System.EventHandler(this.button_initsystem_Click);
            // 
            // button_exitsystem
            // 
            this.button_exitsystem.Location = new System.Drawing.Point(112, 21);
            this.button_exitsystem.Name = "button_exitsystem";
            this.button_exitsystem.Size = new System.Drawing.Size(75, 23);
            this.button_exitsystem.TabIndex = 2;
            this.button_exitsystem.Text = "ExitSystem";
            this.button_exitsystem.UseVisualStyleBackColor = true;
            this.button_exitsystem.Click += new System.EventHandler(this.button_exitsystem_Click);
            // 
            // listBox_OptAndEvtInfo
            // 
            this.listBox_OptAndEvtInfo.FormattingEnabled = true;
            this.listBox_OptAndEvtInfo.ItemHeight = 12;
            this.listBox_OptAndEvtInfo.Location = new System.Drawing.Point(12, 471);
            this.listBox_OptAndEvtInfo.Name = "listBox_OptAndEvtInfo";
            this.listBox_OptAndEvtInfo.Size = new System.Drawing.Size(862, 100);
            this.listBox_OptAndEvtInfo.TabIndex = 4;
            // 
            // button_simulate
            // 
            this.button_simulate.Location = new System.Drawing.Point(203, 21);
            this.button_simulate.Name = "button_simulate";
            this.button_simulate.Size = new System.Drawing.Size(152, 23);
            this.button_simulate.TabIndex = 5;
            this.button_simulate.Text = "Start Simulate Callout";
            this.button_simulate.UseVisualStyleBackColor = true;
            this.button_simulate.Click += new System.EventHandler(this.button_simulate_Click);
            // 
            // textBox_Callee
            // 
            this.textBox_Callee.Location = new System.Drawing.Point(375, 23);
            this.textBox_Callee.Name = "textBox_Callee";
            this.textBox_Callee.Size = new System.Drawing.Size(100, 21);
            this.textBox_Callee.TabIndex = 6;
            this.textBox_Callee.Text = "12345";
            // 
            // checkBox_IsLoop
            // 
            this.checkBox_IsLoop.AutoSize = true;
            this.checkBox_IsLoop.Location = new System.Drawing.Point(532, 23);
            this.checkBox_IsLoop.Name = "checkBox_IsLoop";
            this.checkBox_IsLoop.Size = new System.Drawing.Size(48, 16);
            this.checkBox_IsLoop.TabIndex = 7;
            this.checkBox_IsLoop.Text = "Loop";
            this.checkBox_IsLoop.UseVisualStyleBackColor = true;
            // 
            // timer_loopCallOut
            // 
            this.timer_loopCallOut.Interval = 500;
            this.timer_loopCallOut.Tick += new System.EventHandler(this.timer_loopCallOut_Tick);
            // 
            // axDJAcsAPI
            // 
            this.axDJAcsAPI.Enabled = true;
            this.axDJAcsAPI.Location = new System.Drawing.Point(723, 1);
            this.axDJAcsAPI.Name = "axDJAcsAPI";
            this.axDJAcsAPI.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axDJAcsAPI.OcxState")));
            this.axDJAcsAPI.Size = new System.Drawing.Size(16, 18);
            this.axDJAcsAPI.TabIndex = 8;
            this.axDJAcsAPI.Visible = false;
            // 
            // listView_InterfInfo
            // 
            this.listView_InterfInfo.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6,
            this.columnHeader7,
            this.columnHeader8,
            this.columnHeader9,
            this.columnHeader10,
            this.columnHeader11});
            this.listView_InterfInfo.FullRowSelect = true;
            this.listView_InterfInfo.Location = new System.Drawing.Point(12, 50);
            this.listView_InterfInfo.MultiSelect = false;
            this.listView_InterfInfo.Name = "listView_InterfInfo";
            this.listView_InterfInfo.Size = new System.Drawing.Size(862, 409);
            this.listView_InterfInfo.TabIndex = 9;
            this.listView_InterfInfo.UseCompatibleStateImageBehavior = false;
            this.listView_InterfInfo.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Tag = "Index";
            this.columnHeader1.Text = "Index";
            // 
            // columnHeader2
            // 
            this.columnHeader2.Tag = "DSP ID";
            this.columnHeader2.Text = "DSP ID";
            // 
            // columnHeader3
            // 
            this.columnHeader3.Tag = "Channel ID";
            this.columnHeader3.Text = "Channel ID";
            this.columnHeader3.Width = 80;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Tag = "Device Type";
            this.columnHeader4.Text = "Device Type";
            this.columnHeader4.Width = 90;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Tag = "State";
            this.columnHeader5.Text = "State";
            // 
            // columnHeader6
            // 
            this.columnHeader6.Tag = "Device State";
            this.columnHeader6.Text = "Device State";
            this.columnHeader6.Width = 100;
            // 
            // columnHeader7
            // 
            this.columnHeader7.Tag = "Caller";
            this.columnHeader7.Text = "Caller";
            this.columnHeader7.Width = 100;
            // 
            // columnHeader8
            // 
            this.columnHeader8.Tag = "Callee";
            this.columnHeader8.Text = "Callee";
            this.columnHeader8.Width = 100;
            // 
            // columnHeader9
            // 
            this.columnHeader9.Tag = "DTMF";
            this.columnHeader9.Text = "DTMF";
            // 
            // columnHeader10
            // 
            this.columnHeader10.Tag = "Link ID";
            this.columnHeader10.Text = "Link ID";
            // 
            // columnHeader11
            // 
            this.columnHeader11.Tag = "Voc ID";
            this.columnHeader11.Text = "Voc ID";
            // 
            // DialForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(886, 585);
            this.Controls.Add(this.listView_InterfInfo);
            this.Controls.Add(this.axDJAcsAPI);
            this.Controls.Add(this.checkBox_IsLoop);
            this.Controls.Add(this.textBox_Callee);
            this.Controls.Add(this.button_simulate);
            this.Controls.Add(this.listBox_OptAndEvtInfo);
            this.Controls.Add(this.button_exitsystem);
            this.Controls.Add(this.button_initsystem);
            this.MaximizeBox = false;
            this.Name = "DialForm";
            this.Text = "DialForm";
            this.Load += new System.EventHandler(this.DialForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axDJAcsAPI)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_initsystem;
        private System.Windows.Forms.Button button_exitsystem;
        private System.Windows.Forms.ListBox listBox_OptAndEvtInfo;
        private System.Windows.Forms.Button button_simulate;
        private System.Windows.Forms.TextBox textBox_Callee;
        private System.Windows.Forms.CheckBox checkBox_IsLoop;
        private System.Windows.Forms.Timer timer_loopCallOut;
        private AxDJACSAPILib.AxDJAcsAPI axDJAcsAPI;
        private System.Windows.Forms.ListView listView_InterfInfo;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.ColumnHeader columnHeader7;
        private System.Windows.Forms.ColumnHeader columnHeader8;
        private System.Windows.Forms.ColumnHeader columnHeader9;
        private System.Windows.Forms.ColumnHeader columnHeader10;
        private System.Windows.Forms.ColumnHeader columnHeader11;
    }
}

