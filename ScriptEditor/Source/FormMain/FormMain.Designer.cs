namespace ScriptEditor
{
	partial class FormMain
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

		#region Windows フォーム デザイナーで生成されたコード

		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent ()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.フォルダToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.上書保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.別名保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.基準保存TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.読込ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.テキストから読込ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabAction = new System.Windows.Forms.TabPage();
			this.cpd_Behavior = new ScriptEditor.Ctrl_Compend();
			this.tabEffect = new System.Windows.Forms.TabPage();
			this.cpd_Garnish = new ScriptEditor.Ctrl_Compend();
			this.tabCommand = new System.Windows.Forms.TabPage();
			this.listCommand1 = new ScriptEditor.ListCommand();
			this.ctrl_Command1 = new ScriptEditor.Ctrl_Command();
			this.tabBranch = new System.Windows.Forms.TabPage();
			this.tabChara = new System.Windows.Forms.TabPage();
			this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
			this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
			this.menuStrip1.SuspendLayout();
			this.statusStrip1.SuspendLayout();
			this.tabControl1.SuspendLayout();
			this.tabAction.SuspendLayout();
			this.tabEffect.SuspendLayout();
			this.tabCommand.SuspendLayout();
			this.tabBranch.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.フォルダToolStripMenuItem,
            this.上書保存ToolStripMenuItem,
            this.別名保存ToolStripMenuItem,
            this.基準保存TToolStripMenuItem,
            this.読込ToolStripMenuItem,
            this.テキストから読込ToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(984, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// フォルダToolStripMenuItem
			// 
			this.フォルダToolStripMenuItem.Name = "フォルダToolStripMenuItem";
			this.フォルダToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
			this.フォルダToolStripMenuItem.Size = new System.Drawing.Size(68, 20);
			this.フォルダToolStripMenuItem.Text = "フォルダ(&F)";
			this.フォルダToolStripMenuItem.Click += new System.EventHandler(this.フォルダToolStripMenuItem_Click);
			// 
			// 上書保存ToolStripMenuItem
			// 
			this.上書保存ToolStripMenuItem.Name = "上書保存ToolStripMenuItem";
			this.上書保存ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
			this.上書保存ToolStripMenuItem.Size = new System.Drawing.Size(81, 20);
			this.上書保存ToolStripMenuItem.Text = "上書保存(&S)";
			this.上書保存ToolStripMenuItem.Click += new System.EventHandler(this.上書保存ToolStripMenuItem_Click);
			// 
			// 別名保存ToolStripMenuItem
			// 
			this.別名保存ToolStripMenuItem.Name = "別名保存ToolStripMenuItem";
			this.別名保存ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
			this.別名保存ToolStripMenuItem.Size = new System.Drawing.Size(83, 20);
			this.別名保存ToolStripMenuItem.Text = "別名保存(&A)";
			this.別名保存ToolStripMenuItem.Click += new System.EventHandler(this.別名保存ToolStripMenuItem_Click);
			// 
			// 基準保存TToolStripMenuItem
			// 
			this.基準保存TToolStripMenuItem.Name = "基準保存TToolStripMenuItem";
			this.基準保存TToolStripMenuItem.Size = new System.Drawing.Size(81, 20);
			this.基準保存TToolStripMenuItem.Text = "基準保存(&T)";
			this.基準保存TToolStripMenuItem.Click += new System.EventHandler(this.基準保存TToolStripMenuItem_Click);
			// 
			// 読込ToolStripMenuItem
			// 
			this.読込ToolStripMenuItem.Name = "読込ToolStripMenuItem";
			this.読込ToolStripMenuItem.Size = new System.Drawing.Size(60, 20);
			this.読込ToolStripMenuItem.Text = "読込(&O)";
			this.読込ToolStripMenuItem.Click += new System.EventHandler(this.読込ToolStripMenuItem_Click);
			// 
			// テキストから読込ToolStripMenuItem
			// 
			this.テキストから読込ToolStripMenuItem.Name = "テキストから読込ToolStripMenuItem";
			this.テキストから読込ToolStripMenuItem.Size = new System.Drawing.Size(97, 20);
			this.テキストから読込ToolStripMenuItem.Text = "テキストから読込";
			this.テキストから読込ToolStripMenuItem.Click += new System.EventHandler(this.テキストから読込ToolStripMenuItem_Click);
			// 
			// statusStrip1
			// 
			this.statusStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
			this.statusStrip1.Location = new System.Drawing.Point(0, 739);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(984, 22);
			this.statusStrip1.TabIndex = 1;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
			this.toolStripStatusLabel1.Size = new System.Drawing.Size(26, 17);
			this.toolStripStatusLabel1.Text = "test";
			// 
			// tabControl1
			// 
			this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.tabControl1.Controls.Add(this.tabAction);
			this.tabControl1.Controls.Add(this.tabEffect);
			this.tabControl1.Controls.Add(this.tabCommand);
			this.tabControl1.Controls.Add(this.tabBranch);
			this.tabControl1.Controls.Add(this.tabChara);
			this.tabControl1.Location = new System.Drawing.Point(0, 24);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(984, 712);
			this.tabControl1.TabIndex = 3;
			this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
			this.tabControl1.Deselected += new System.Windows.Forms.TabControlEventHandler(this.tabControl1_Deselected);
			// 
			// tabAction
			// 
			this.tabAction.AutoScroll = true;
			this.tabAction.Controls.Add(this.cpd_Behavior);
			this.tabAction.Location = new System.Drawing.Point(4, 22);
			this.tabAction.Name = "tabAction";
			this.tabAction.Padding = new System.Windows.Forms.Padding(3);
			this.tabAction.Size = new System.Drawing.Size(976, 686);
			this.tabAction.TabIndex = 0;
			this.tabAction.Text = "アクション";
			this.tabAction.UseVisualStyleBackColor = true;
			// 
			// cpd_Behavior
			// 
			this.cpd_Behavior.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.cpd_Behavior.AutoScroll = true;
			this.cpd_Behavior.BoolAction = false;
			this.cpd_Behavior.EditCompend = null;
			this.cpd_Behavior.Location = new System.Drawing.Point(0, 0);
			this.cpd_Behavior.Name = "cpd_Behavior";
			this.cpd_Behavior.Size = new System.Drawing.Size(977, 712);
			this.cpd_Behavior.TabIndex = 0;
			// 
			// tabEffect
			// 
			this.tabEffect.Controls.Add(this.cpd_Garnish);
			this.tabEffect.Location = new System.Drawing.Point(4, 22);
			this.tabEffect.Name = "tabEffect";
			this.tabEffect.Padding = new System.Windows.Forms.Padding(3);
			this.tabEffect.Size = new System.Drawing.Size(976, 686);
			this.tabEffect.TabIndex = 1;
			this.tabEffect.Text = "エフェクト";
			this.tabEffect.UseVisualStyleBackColor = true;
			// 
			// cpd_Garnish
			// 
			this.cpd_Garnish.BoolAction = false;
			this.cpd_Garnish.EditCompend = null;
			this.cpd_Garnish.Location = new System.Drawing.Point(0, 0);
			this.cpd_Garnish.Name = "cpd_Garnish";
			this.cpd_Garnish.Size = new System.Drawing.Size(977, 711);
			this.cpd_Garnish.TabIndex = 0;
			// 
			// tabCommand
			// 
			this.tabCommand.Controls.Add(this.listCommand1);
			this.tabCommand.Controls.Add(this.ctrl_Command1);
			this.tabCommand.Location = new System.Drawing.Point(4, 22);
			this.tabCommand.Name = "tabCommand";
			this.tabCommand.Size = new System.Drawing.Size(976, 686);
			this.tabCommand.TabIndex = 2;
			this.tabCommand.Text = "コマンド";
			this.tabCommand.UseVisualStyleBackColor = true;
			// 
			// listCommand1
			// 
			this.listCommand1.Location = new System.Drawing.Point(8, 3);
			this.listCommand1.Name = "listCommand1";
			this.listCommand1.Size = new System.Drawing.Size(179, 489);
			this.listCommand1.TabIndex = 1;
			// 
			// ctrl_Command1
			// 
			this.ctrl_Command1.Location = new System.Drawing.Point(181, 3);
			this.ctrl_Command1.Name = "ctrl_Command1";
			this.ctrl_Command1.Size = new System.Drawing.Size(688, 462);
			this.ctrl_Command1.TabIndex = 0;
			// 
			// tabBranch
			// 
			this.tabBranch.Location = new System.Drawing.Point(4, 22);
			this.tabBranch.Name = "tabBranch";
			this.tabBranch.Size = new System.Drawing.Size(976, 686);
			this.tabBranch.TabIndex = 4;
			this.tabBranch.Text = "ブランチ";
			this.tabBranch.UseVisualStyleBackColor = true;
			// 
			// tabChara
			// 
			this.tabChara.Location = new System.Drawing.Point(4, 22);
			this.tabChara.Name = "tabChara";
			this.tabChara.Size = new System.Drawing.Size(976, 686);
			this.tabChara.TabIndex = 3;
			this.tabChara.Text = "キャラ";
			this.tabChara.UseVisualStyleBackColor = true;
			// 
			// openFileDialog1
			// 
			this.openFileDialog1.FileName = "openFileDialog1";
			// 
			// FormMain
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(984, 761);
			this.Controls.Add(this.statusStrip1);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.tabControl1);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "FormMain";
			this.Text = "ScriptEditor";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.FormMain_Paint);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.tabControl1.ResumeLayout(false);
			this.tabAction.ResumeLayout(false);
			this.tabEffect.ResumeLayout(false);
			this.tabCommand.ResumeLayout(false);
			this.tabBranch.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.ToolStripMenuItem 上書保存ToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem 読込ToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem フォルダToolStripMenuItem;
		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabAction;
		private System.Windows.Forms.TabPage tabCommand;
		private System.Windows.Forms.TabPage tabChara;
		private System.Windows.Forms.ToolStripMenuItem 別名保存ToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem 基準保存TToolStripMenuItem;
		private System.Windows.Forms.TabPage tabEffect;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
		private System.Windows.Forms.SaveFileDialog saveFileDialog1;
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		private Ctrl_Compend cpd_Behavior;
		private Ctrl_Compend cpd_Garnish;
		private System.Windows.Forms.ToolStripMenuItem テキストから読込ToolStripMenuItem;
		private ListCommand listCommand1;
		private Ctrl_Command ctrl_Command1;
		private System.Windows.Forms.TabPage tabBranch;
	}
}

