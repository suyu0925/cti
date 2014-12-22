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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DemoForm));
            this.axDJAcsAPI = new AxDJACSAPILib.AxDJAcsAPI();
            this.buttonInitSystem = new System.Windows.Forms.Button();
            this.buttonExitSystem = new System.Windows.Forms.Button();
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
            this.listBox_OptAndEvtInfo = new System.Windows.Forms.ListBox();
            ((System.ComponentModel.ISupportInitialize)(this.axDJAcsAPI)).BeginInit();
            this.SuspendLayout();
            // 
            // axDJAcsAPI
            // 
            this.axDJAcsAPI.Enabled = true;
            this.axDJAcsAPI.Location = new System.Drawing.Point(749, 1);
            this.axDJAcsAPI.Name = "axDJAcsAPI";
            this.axDJAcsAPI.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axDJAcsAPI.OcxState")));
            this.axDJAcsAPI.Size = new System.Drawing.Size(25, 24);
            this.axDJAcsAPI.TabIndex = 0;
            this.axDJAcsAPI.Visible = false;
            // 
            // buttonInitSystem
            // 
            this.buttonInitSystem.Location = new System.Drawing.Point(12, 12);
            this.buttonInitSystem.Name = "buttonInitSystem";
            this.buttonInitSystem.Size = new System.Drawing.Size(75, 23);
            this.buttonInitSystem.TabIndex = 1;
            this.buttonInitSystem.Text = "InitSystem";
            this.buttonInitSystem.UseVisualStyleBackColor = true;
            this.buttonInitSystem.Click += new System.EventHandler(this.buttonInitSystem_Click);
            // 
            // buttonExitSystem
            // 
            this.buttonExitSystem.Location = new System.Drawing.Point(93, 12);
            this.buttonExitSystem.Name = "buttonExitSystem";
            this.buttonExitSystem.Size = new System.Drawing.Size(75, 23);
            this.buttonExitSystem.TabIndex = 2;
            this.buttonExitSystem.Text = "ExitSystem";
            this.buttonExitSystem.UseVisualStyleBackColor = true;
            this.buttonExitSystem.Click += new System.EventHandler(this.buttonExitSystem_Click);
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
            this.listView_InterfInfo.Location = new System.Drawing.Point(12, 41);
            this.listView_InterfInfo.MultiSelect = false;
            this.listView_InterfInfo.Name = "listView_InterfInfo";
            this.listView_InterfInfo.Size = new System.Drawing.Size(862, 409);
            this.listView_InterfInfo.TabIndex = 3;
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
            // listBox_OptAndEvtInfo
            // 
            this.listBox_OptAndEvtInfo.FormattingEnabled = true;
            this.listBox_OptAndEvtInfo.ItemHeight = 12;
            this.listBox_OptAndEvtInfo.Location = new System.Drawing.Point(12, 456);
            this.listBox_OptAndEvtInfo.Name = "listBox_OptAndEvtInfo";
            this.listBox_OptAndEvtInfo.Size = new System.Drawing.Size(862, 76);
            this.listBox_OptAndEvtInfo.TabIndex = 4;
            // 
            // DemoForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(886, 545);
            this.Controls.Add(this.listBox_OptAndEvtInfo);
            this.Controls.Add(this.listView_InterfInfo);
            this.Controls.Add(this.buttonExitSystem);
            this.Controls.Add(this.buttonInitSystem);
            this.Controls.Add(this.axDJAcsAPI);
            this.MaximizeBox = false;
            this.Name = "DemoForm";
            this.Text = "DemoForm";
            ((System.ComponentModel.ISupportInitialize)(this.axDJAcsAPI)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private AxDJACSAPILib.AxDJAcsAPI axDJAcsAPI;
        private System.Windows.Forms.Button buttonInitSystem;
        private System.Windows.Forms.Button buttonExitSystem;
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
        private System.Windows.Forms.ListBox listBox_OptAndEvtInfo;
    }
}

