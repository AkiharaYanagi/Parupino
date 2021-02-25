namespace ScriptEditor
{
	partial class Ctrl_Compend
	{
		/// <summary> 
		/// 必要なデザイナー変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary> 
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
		protected override void Dispose ( bool disposing )
		{
			if ( disposing && ( components != null ) )
			{
				components.Dispose ();
			}
			base.Dispose ( disposing );
		}

		#region コンポーネント デザイナーで生成されたコード

		/// <summary> 
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を 
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent ()
		{
			this.components = new System.ComponentModel.Container();
			ScriptEditor.ToolImg_Main toolImg_Main1 = new ScriptEditor.ToolImg_Main();
			this.Lb_SqcName = new System.Windows.Forms.ListBox();
			this.panel1 = new System.Windows.Forms.Panel();
			this.sqcBoard1 = new ScriptEditor.SqcBoard();
			this.Btn_Sqc = new System.Windows.Forms.Button();
			this.Btn_Scp = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.Ctrl_Img = new ScriptEditor.Ctrl_Image();
			this.Tb_ImageName = new System.Windows.Forms.TextBox();
			this.Btn_EfGnrt = new System.Windows.Forms.Button();
			this.Btn_Rect = new System.Windows.Forms.Button();
			this.Btn_Image = new System.Windows.Forms.Button();
			this.Tbn_Y = new ScriptEditor.TB_Number();
			this.Tbn_X = new ScriptEditor.TB_Number();
			this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.シークエンスToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.スクリプトToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.シークエンスToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
			this.スクリプトPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.Btn_Branch = new System.Windows.Forms.Button();
			this.panel1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.contextMenuStrip1.SuspendLayout();
			this.menuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// Lb_SqcName
			// 
			this.Lb_SqcName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
			this.Lb_SqcName.FormattingEnabled = true;
			this.Lb_SqcName.ItemHeight = 12;
			this.Lb_SqcName.Location = new System.Drawing.Point(0, 0);
			this.Lb_SqcName.Name = "Lb_SqcName";
			this.Lb_SqcName.Size = new System.Drawing.Size(108, 508);
			this.Lb_SqcName.TabIndex = 1;
			this.Lb_SqcName.SelectedIndexChanged += new System.EventHandler(this.Lb_SqcName_SelectedIndexChanged);
			// 
			// panel1
			// 
			this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.panel1.AutoScroll = true;
			this.panel1.Controls.Add(this.sqcBoard1);
			this.panel1.Location = new System.Drawing.Point(114, 3);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(638, 157);
			this.panel1.TabIndex = 2;
			// 
			// sqcBoard1
			// 
			this.sqcBoard1.AutoScroll = true;
			this.sqcBoard1.BackColor = System.Drawing.SystemColors.Control;
			this.sqcBoard1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.sqcBoard1.EditCompend = null;
			this.sqcBoard1.Location = new System.Drawing.Point(0, 0);
			this.sqcBoard1.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
			this.sqcBoard1.Name = "sqcBoard1";
			this.sqcBoard1.Size = new System.Drawing.Size(500, 140);
			this.sqcBoard1.TabIndex = 0;
			// 
			// Btn_Sqc
			// 
			this.Btn_Sqc.Location = new System.Drawing.Point(3, 3);
			this.Btn_Sqc.Name = "Btn_Sqc";
			this.Btn_Sqc.Size = new System.Drawing.Size(111, 29);
			this.Btn_Sqc.TabIndex = 3;
			this.Btn_Sqc.Text = "シークエンス";
			this.Btn_Sqc.UseVisualStyleBackColor = true;
			this.Btn_Sqc.Click += new System.EventHandler(this.Btn_Sqc_Click);
			// 
			// Btn_Scp
			// 
			this.Btn_Scp.Location = new System.Drawing.Point(3, 38);
			this.Btn_Scp.Name = "Btn_Scp";
			this.Btn_Scp.Size = new System.Drawing.Size(113, 29);
			this.Btn_Scp.TabIndex = 3;
			this.Btn_Scp.Text = "スクリプト";
			this.Btn_Scp.UseVisualStyleBackColor = true;
			this.Btn_Scp.Click += new System.EventHandler(this.Btn_Scp_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 151);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(11, 12);
			this.label1.TabIndex = 5;
			this.label1.Text = "x";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 176);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(11, 12);
			this.label2.TabIndex = 5;
			this.label2.Text = "y";
			// 
			// splitContainer1
			// 
			this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainer1.Location = new System.Drawing.Point(114, 166);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.Ctrl_Img);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Branch);
			this.splitContainer1.Panel2.Controls.Add(this.Tb_ImageName);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_EfGnrt);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Rect);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Image);
			this.splitContainer1.Panel2.Controls.Add(this.Tbn_Y);
			this.splitContainer1.Panel2.Controls.Add(this.Tbn_X);
			this.splitContainer1.Panel2.Controls.Add(this.label2);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Sqc);
			this.splitContainer1.Panel2.Controls.Add(this.label1);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Scp);
			this.splitContainer1.Size = new System.Drawing.Size(638, 342);
			this.splitContainer1.SplitterDistance = 510;
			this.splitContainer1.TabIndex = 6;
			// 
			// Ctrl_Img
			// 
			this.Ctrl_Img.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.Ctrl_Img.EditCompend = null;
			this.Ctrl_Img.Location = new System.Drawing.Point(0, 0);
			this.Ctrl_Img.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
			this.Ctrl_Img.Name = "Ctrl_Img";
			toolImg_Main1.EditCompend = null;
			toolImg_Main1.RbTl = null;
			this.Ctrl_Img.SelectingTool = toolImg_Main1;
			this.Ctrl_Img.Size = new System.Drawing.Size(507, 342);
			this.Ctrl_Img.TabIndex = 0;
			// 
			// Tb_ImageName
			// 
			this.Tb_ImageName.Location = new System.Drawing.Point(3, 108);
			this.Tb_ImageName.Name = "Tb_ImageName";
			this.Tb_ImageName.Size = new System.Drawing.Size(111, 19);
			this.Tb_ImageName.TabIndex = 9;
			// 
			// Btn_EfGnrt
			// 
			this.Btn_EfGnrt.Location = new System.Drawing.Point(1, 250);
			this.Btn_EfGnrt.Name = "Btn_EfGnrt";
			this.Btn_EfGnrt.Size = new System.Drawing.Size(113, 29);
			this.Btn_EfGnrt.TabIndex = 7;
			this.Btn_EfGnrt.Text = "Ef生成";
			this.Btn_EfGnrt.UseVisualStyleBackColor = true;
			this.Btn_EfGnrt.Click += new System.EventHandler(this.Btn_EfGnrt_Click);
			// 
			// Btn_Rect
			// 
			this.Btn_Rect.Location = new System.Drawing.Point(1, 215);
			this.Btn_Rect.Name = "Btn_Rect";
			this.Btn_Rect.Size = new System.Drawing.Size(113, 29);
			this.Btn_Rect.TabIndex = 7;
			this.Btn_Rect.Text = "判定枠";
			this.Btn_Rect.UseVisualStyleBackColor = true;
			this.Btn_Rect.Click += new System.EventHandler(this.Btn_Rect_Click);
			// 
			// Btn_Image
			// 
			this.Btn_Image.Location = new System.Drawing.Point(3, 73);
			this.Btn_Image.Name = "Btn_Image";
			this.Btn_Image.Size = new System.Drawing.Size(113, 29);
			this.Btn_Image.TabIndex = 7;
			this.Btn_Image.Text = "イメージ";
			this.Btn_Image.UseVisualStyleBackColor = true;
			this.Btn_Image.Click += new System.EventHandler(this.Btn_Image_Click);
			// 
			// Tbn_Y
			// 
			this.Tbn_Y.GroupSetter = null;
			this.Tbn_Y.Location = new System.Drawing.Point(23, 173);
			this.Tbn_Y.Name = "Tbn_Y";
			this.Tbn_Y.Size = new System.Drawing.Size(78, 19);
			this.Tbn_Y.TabIndex = 6;
			this.Tbn_Y.Text = "0";
			// 
			// Tbn_X
			// 
			this.Tbn_X.GroupSetter = null;
			this.Tbn_X.Location = new System.Drawing.Point(23, 148);
			this.Tbn_X.Name = "Tbn_X";
			this.Tbn_X.Size = new System.Drawing.Size(78, 19);
			this.Tbn_X.TabIndex = 6;
			this.Tbn_X.Text = "0";
			// 
			// contextMenuStrip1
			// 
			this.contextMenuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
			this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.シークエンスToolStripMenuItem,
            this.スクリプトToolStripMenuItem});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new System.Drawing.Size(146, 48);
			// 
			// シークエンスToolStripMenuItem
			// 
			this.シークエンスToolStripMenuItem.Name = "シークエンスToolStripMenuItem";
			this.シークエンスToolStripMenuItem.Size = new System.Drawing.Size(145, 22);
			this.シークエンスToolStripMenuItem.Text = "シークエンス(Q)";
			this.シークエンスToolStripMenuItem.Click += new System.EventHandler(this.シークエンスToolStripMenuItem_Click);
			// 
			// スクリプトToolStripMenuItem
			// 
			this.スクリプトToolStripMenuItem.Name = "スクリプトToolStripMenuItem";
			this.スクリプトToolStripMenuItem.Size = new System.Drawing.Size(145, 22);
			this.スクリプトToolStripMenuItem.Text = "スクリプト(&P)";
			// 
			// menuStrip1
			// 
			this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.シークエンスToolStripMenuItem1,
            this.スクリプトPToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Padding = new System.Windows.Forms.Padding(4, 1, 0, 1);
			this.menuStrip1.Size = new System.Drawing.Size(779, 24);
			this.menuStrip1.TabIndex = 8;
			this.menuStrip1.Text = "menuStrip1";
			this.menuStrip1.Visible = false;
			// 
			// シークエンスToolStripMenuItem1
			// 
			this.シークエンスToolStripMenuItem1.Name = "シークエンスToolStripMenuItem1";
			this.シークエンスToolStripMenuItem1.ShortcutKeyDisplayString = "Ctrl+Q";
			this.シークエンスToolStripMenuItem1.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
			this.シークエンスToolStripMenuItem1.Size = new System.Drawing.Size(90, 22);
			this.シークエンスToolStripMenuItem1.Text = "シークエンス(&Q)";
			this.シークエンスToolStripMenuItem1.Click += new System.EventHandler(this.シークエンスToolStripMenuItem_Click);
			// 
			// スクリプトPToolStripMenuItem
			// 
			this.スクリプトPToolStripMenuItem.Name = "スクリプトPToolStripMenuItem";
			this.スクリプトPToolStripMenuItem.ShortcutKeyDisplayString = "Ctrl+P";
			this.スクリプトPToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
			this.スクリプトPToolStripMenuItem.Size = new System.Drawing.Size(77, 22);
			this.スクリプトPToolStripMenuItem.Text = "スクリプト(&P)";
			this.スクリプトPToolStripMenuItem.Click += new System.EventHandler(this.スクリプトPToolStripMenuItem_Click);
			// 
			// Btn_Branch
			// 
			this.Btn_Branch.Location = new System.Drawing.Point(1, 285);
			this.Btn_Branch.Name = "Btn_Branch";
			this.Btn_Branch.Size = new System.Drawing.Size(113, 30);
			this.Btn_Branch.TabIndex = 10;
			this.Btn_Branch.Text = "ブランチ";
			this.Btn_Branch.UseVisualStyleBackColor = true;
			this.Btn_Branch.Click += new System.EventHandler(this.Btn_Branch_Click);
			// 
			// Ctrl_Compend
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.splitContainer1);
			this.Controls.Add(this.panel1);
			this.Controls.Add(this.Lb_SqcName);
			this.Name = "Ctrl_Compend";
			this.Size = new System.Drawing.Size(779, 520);
			this.panel1.ResumeLayout(false);
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			this.splitContainer1.Panel2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
			this.splitContainer1.ResumeLayout(false);
			this.contextMenuStrip1.ResumeLayout(false);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		public Ctrl_Image Ctrl_Img;
		private System.Windows.Forms.ListBox Lb_SqcName;
		public SqcBoard sqcBoard1;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Button Btn_Sqc;
		private System.Windows.Forms.Button Btn_Scp;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.SplitContainer splitContainer1;
		private TB_Number Tbn_Y;
		private TB_Number Tbn_X;
		private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
		private System.Windows.Forms.ToolStripMenuItem シークエンスToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem スクリプトToolStripMenuItem;
		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem シークエンスToolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem スクリプトPToolStripMenuItem;
		private System.Windows.Forms.Button Btn_Image;
		private System.Windows.Forms.Button Btn_Rect;
		private System.Windows.Forms.TextBox Tb_ImageName;
		private System.Windows.Forms.Button Btn_EfGnrt;
		private System.Windows.Forms.Button Btn_Branch;
	}
}
