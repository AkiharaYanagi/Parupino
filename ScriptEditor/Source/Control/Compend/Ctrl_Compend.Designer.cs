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
			this.panel1 = new System.Windows.Forms.Panel();
			this.sqcBoard1 = new ScriptEditor.SqcBoard();
			this.Btn_Sqc = new System.Windows.Forms.Button();
			this.Btn_Scp = new System.Windows.Forms.Button();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.Ctrl_Img = new ScriptEditor.Ctrl_Image();
			this.Btn_Branch = new System.Windows.Forms.Button();
			this.Btn_EfGnrt = new System.Windows.Forms.Button();
			this.Btn_Rect = new System.Windows.Forms.Button();
			this.Btn_Image = new System.Windows.Forms.Button();
			this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.シークエンスToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.スクリプトToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.シークエンスToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
			this.スクリプトPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.sequenceTree1 = new ScriptEditor.SequenceTree();
			this.Btn_Preview = new System.Windows.Forms.Button();
			this.panel1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.contextMenuStrip1.SuspendLayout();
			this.menuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// panel1
			// 
			this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.panel1.AutoScroll = true;
			this.panel1.Controls.Add(this.sqcBoard1);
			this.panel1.Location = new System.Drawing.Point(140, 3);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(612, 157);
			this.panel1.TabIndex = 2;
			// 
			// sqcBoard1
			// 
			this.sqcBoard1.AutoScroll = true;
			this.sqcBoard1.BackColor = System.Drawing.SystemColors.Control;
			this.sqcBoard1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.sqcBoard1.Ctrl_Script = null;
			this.sqcBoard1.DispCompend = null;
			this.sqcBoard1.EditCompend = null;
			this.sqcBoard1.Location = new System.Drawing.Point(0, 0);
			this.sqcBoard1.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
			this.sqcBoard1.Name = "sqcBoard1";
			this.sqcBoard1.Size = new System.Drawing.Size(500, 140);
			this.sqcBoard1.TabIndex = 0;
			// 
			// Btn_Sqc
			// 
			this.Btn_Sqc.Location = new System.Drawing.Point(1, 3);
			this.Btn_Sqc.Name = "Btn_Sqc";
			this.Btn_Sqc.Size = new System.Drawing.Size(111, 29);
			this.Btn_Sqc.TabIndex = 3;
			this.Btn_Sqc.Text = "シークエンス";
			this.Btn_Sqc.UseVisualStyleBackColor = true;
			this.Btn_Sqc.Click += new System.EventHandler(this.Btn_Sqc_Click);
			// 
			// Btn_Scp
			// 
			this.Btn_Scp.Location = new System.Drawing.Point(1, 38);
			this.Btn_Scp.Name = "Btn_Scp";
			this.Btn_Scp.Size = new System.Drawing.Size(113, 29);
			this.Btn_Scp.TabIndex = 3;
			this.Btn_Scp.Text = "スクリプト";
			this.Btn_Scp.UseVisualStyleBackColor = true;
			this.Btn_Scp.Click += new System.EventHandler(this.Btn_Scp_Click);
			// 
			// splitContainer1
			// 
			this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.splitContainer1.Location = new System.Drawing.Point(140, 166);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.Ctrl_Img);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Preview);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Branch);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_EfGnrt);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Rect);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Image);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Sqc);
			this.splitContainer1.Panel2.Controls.Add(this.Btn_Scp);
			this.splitContainer1.Size = new System.Drawing.Size(612, 342);
			this.splitContainer1.SplitterDistance = 488;
			this.splitContainer1.TabIndex = 6;
			// 
			// Ctrl_Img
			// 
			this.Ctrl_Img.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.Ctrl_Img.DispCompend = null;
			this.Ctrl_Img.EditCompend = null;
			this.Ctrl_Img.Location = new System.Drawing.Point(0, 0);
			this.Ctrl_Img.Margin = new System.Windows.Forms.Padding(5, 4, 5, 4);
			this.Ctrl_Img.Name = "Ctrl_Img";
			toolImg_Main1.EditCompend = null;
			toolImg_Main1.RbTl = null;
			this.Ctrl_Img.SelectingTool = toolImg_Main1;
			this.Ctrl_Img.Size = new System.Drawing.Size(490, 342);
			this.Ctrl_Img.TabIndex = 0;
			// 
			// Btn_Branch
			// 
			this.Btn_Branch.Location = new System.Drawing.Point(1, 178);
			this.Btn_Branch.Name = "Btn_Branch";
			this.Btn_Branch.Size = new System.Drawing.Size(113, 30);
			this.Btn_Branch.TabIndex = 10;
			this.Btn_Branch.Text = "ブランチ";
			this.Btn_Branch.UseVisualStyleBackColor = true;
			this.Btn_Branch.Click += new System.EventHandler(this.Btn_Branch_Click);
			// 
			// Btn_EfGnrt
			// 
			this.Btn_EfGnrt.Location = new System.Drawing.Point(1, 143);
			this.Btn_EfGnrt.Name = "Btn_EfGnrt";
			this.Btn_EfGnrt.Size = new System.Drawing.Size(113, 29);
			this.Btn_EfGnrt.TabIndex = 7;
			this.Btn_EfGnrt.Text = "Ef生成";
			this.Btn_EfGnrt.UseVisualStyleBackColor = true;
			this.Btn_EfGnrt.Click += new System.EventHandler(this.Btn_EfGnrt_Click);
			// 
			// Btn_Rect
			// 
			this.Btn_Rect.Location = new System.Drawing.Point(1, 108);
			this.Btn_Rect.Name = "Btn_Rect";
			this.Btn_Rect.Size = new System.Drawing.Size(113, 29);
			this.Btn_Rect.TabIndex = 7;
			this.Btn_Rect.Text = "判定枠";
			this.Btn_Rect.UseVisualStyleBackColor = true;
			this.Btn_Rect.Click += new System.EventHandler(this.Btn_Rect_Click);
			// 
			// Btn_Image
			// 
			this.Btn_Image.Location = new System.Drawing.Point(1, 73);
			this.Btn_Image.Name = "Btn_Image";
			this.Btn_Image.Size = new System.Drawing.Size(113, 29);
			this.Btn_Image.TabIndex = 7;
			this.Btn_Image.Text = "イメージ";
			this.Btn_Image.UseVisualStyleBackColor = true;
			this.Btn_Image.Click += new System.EventHandler(this.Btn_Image_Click);
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
			// sequenceTree1
			// 
			this.sequenceTree1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
			this.sequenceTree1.AutoScroll = true;
			this.sequenceTree1.BD_sq = null;
			this.sequenceTree1.CtrlCompend = null;
			this.sequenceTree1.DispCompend = null;
			this.sequenceTree1.EditCompend = null;
			this.sequenceTree1.Location = new System.Drawing.Point(0, 0);
			this.sequenceTree1.Name = "sequenceTree1";
			this.sequenceTree1.Size = new System.Drawing.Size(132, 508);
			this.sequenceTree1.TabIndex = 9;
			// 
			// Btn_Preview
			// 
			this.Btn_Preview.Location = new System.Drawing.Point(3, 290);
			this.Btn_Preview.Name = "Btn_Preview";
			this.Btn_Preview.Size = new System.Drawing.Size(57, 52);
			this.Btn_Preview.TabIndex = 11;
			this.Btn_Preview.Text = "プレビュー";
			this.Btn_Preview.UseVisualStyleBackColor = true;
			this.Btn_Preview.Click += new System.EventHandler(this.Btn_Preview_Click);
			// 
			// Ctrl_Compend
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.sequenceTree1);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.splitContainer1);
			this.Controls.Add(this.panel1);
			this.Name = "Ctrl_Compend";
			this.Size = new System.Drawing.Size(779, 520);
			this.panel1.ResumeLayout(false);
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
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
		public SqcBoard sqcBoard1;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Button Btn_Sqc;
		private System.Windows.Forms.Button Btn_Scp;
		private System.Windows.Forms.SplitContainer splitContainer1;
		private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
		private System.Windows.Forms.ToolStripMenuItem シークエンスToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem スクリプトToolStripMenuItem;
		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem シークエンスToolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem スクリプトPToolStripMenuItem;
		private System.Windows.Forms.Button Btn_Image;
		private System.Windows.Forms.Button Btn_Rect;
		private System.Windows.Forms.Button Btn_EfGnrt;
		private System.Windows.Forms.Button Btn_Branch;
		private SequenceTree sequenceTree1;
		private System.Windows.Forms.Button Btn_Preview;
	}
}
