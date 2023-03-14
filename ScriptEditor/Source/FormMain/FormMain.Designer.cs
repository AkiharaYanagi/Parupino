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
			ScriptEditor.BindingDictionary<ScriptEditor.Branch> bindingDictionary_11 = new ScriptEditor.BindingDictionary<ScriptEditor.Branch>();
			ScriptEditor.BindingDictionary<ScriptEditor.Command> bindingDictionary_12 = new ScriptEditor.BindingDictionary<ScriptEditor.Command>();
			ScriptEditor.BindingDictionary<ScriptEditor.Sequence> bindingDictionary_13 = new ScriptEditor.BindingDictionary<ScriptEditor.Sequence>();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.フォルダToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.上書保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.別名保存ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.基準保存TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.読込ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.テキストから読込ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.バイナリから読込BToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabAction = new System.Windows.Forms.TabPage();
			this.ctrl_SqcList_Act = new ScriptEditor.Ctrl_SqcList();
			this.tabScriptA = new System.Windows.Forms.TabPage();
			this.cpd_Behavior = new ScriptEditor.Ctrl_Compend();
			this.tabEffect = new System.Windows.Forms.TabPage();
			this.ctrl_SqcList_Ef = new ScriptEditor.Ctrl_SqcList();
			this.tabScriptE = new System.Windows.Forms.TabPage();
			this.cpd_Garnish = new ScriptEditor.Ctrl_Compend();
			this.tabCommand = new System.Windows.Forms.TabPage();
			this.ctrl_CmdList1 = new ScriptEditor.Ctrl_CmdList();
			this.tabBranch = new System.Windows.Forms.TabPage();
			this.ctrl_Branch1 = new ScriptEditor.Ctrl_Branch();
			this.tabRoute = new System.Windows.Forms.TabPage();
			this.ctrl_Route1 = new ScriptEditor.Ctrl_Route();
			this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
			this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
			this.menuStrip1.SuspendLayout();
			this.statusStrip1.SuspendLayout();
			this.tabControl1.SuspendLayout();
			this.tabAction.SuspendLayout();
			this.tabScriptA.SuspendLayout();
			this.tabEffect.SuspendLayout();
			this.tabScriptE.SuspendLayout();
			this.tabCommand.SuspendLayout();
			this.tabBranch.SuspendLayout();
			this.tabRoute.SuspendLayout();
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
            this.テキストから読込ToolStripMenuItem,
            this.バイナリから読込BToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(972, 24);
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
			this.テキストから読込ToolStripMenuItem.Size = new System.Drawing.Size(111, 20);
			this.テキストから読込ToolStripMenuItem.Text = "テキストから読込(&T)";
			this.テキストから読込ToolStripMenuItem.Click += new System.EventHandler(this.テキストから読込ToolStripMenuItem_Click);
			// 
			// バイナリから読込BToolStripMenuItem
			// 
			this.バイナリから読込BToolStripMenuItem.Name = "バイナリから読込BToolStripMenuItem";
			this.バイナリから読込BToolStripMenuItem.Size = new System.Drawing.Size(113, 20);
			this.バイナリから読込BToolStripMenuItem.Text = "バイナリから読込(&B)";
			this.バイナリから読込BToolStripMenuItem.Click += new System.EventHandler(this.バイナリから読込BToolStripMenuItem_Click);
			// 
			// statusStrip1
			// 
			this.statusStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
			this.statusStrip1.Location = new System.Drawing.Point(0, 762);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(972, 22);
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
			this.tabControl1.Controls.Add(this.tabScriptA);
			this.tabControl1.Controls.Add(this.tabEffect);
			this.tabControl1.Controls.Add(this.tabScriptE);
			this.tabControl1.Controls.Add(this.tabCommand);
			this.tabControl1.Controls.Add(this.tabBranch);
			this.tabControl1.Controls.Add(this.tabRoute);
			this.tabControl1.Location = new System.Drawing.Point(0, 24);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(972, 735);
			this.tabControl1.TabIndex = 3;
			this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
			this.tabControl1.Deselected += new System.Windows.Forms.TabControlEventHandler(this.tabControl1_Deselected);
			// 
			// tabAction
			// 
			this.tabAction.Controls.Add(this.ctrl_SqcList_Act);
			this.tabAction.Location = new System.Drawing.Point(4, 22);
			this.tabAction.Name = "tabAction";
			this.tabAction.Size = new System.Drawing.Size(964, 709);
			this.tabAction.TabIndex = 6;
			this.tabAction.Text = "アクション ->";
			this.tabAction.UseVisualStyleBackColor = true;
			// 
			// ctrl_SqcList_Act
			// 
			this.ctrl_SqcList_Act.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.ctrl_SqcList_Act.AutoSize = true;
			this.ctrl_SqcList_Act.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.ctrl_SqcList_Act.Location = new System.Drawing.Point(0, 0);
			this.ctrl_SqcList_Act.Name = "ctrl_SqcList_Act";
			this.ctrl_SqcList_Act.Size = new System.Drawing.Size(1786, 1531);
			this.ctrl_SqcList_Act.TabIndex = 0;
			// 
			// tabScriptA
			// 
			this.tabScriptA.AutoScroll = true;
			this.tabScriptA.Controls.Add(this.cpd_Behavior);
			this.tabScriptA.Location = new System.Drawing.Point(4, 22);
			this.tabScriptA.Name = "tabScriptA";
			this.tabScriptA.Padding = new System.Windows.Forms.Padding(3);
			this.tabScriptA.Size = new System.Drawing.Size(964, 709);
			this.tabScriptA.TabIndex = 0;
			this.tabScriptA.Text = "スクリプト(A)";
			this.tabScriptA.UseVisualStyleBackColor = true;
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
			this.cpd_Behavior.Size = new System.Drawing.Size(977, 742);
			this.cpd_Behavior.TabIndex = 0;
			// 
			// tabEffect
			// 
			this.tabEffect.Controls.Add(this.ctrl_SqcList_Ef);
			this.tabEffect.Location = new System.Drawing.Point(4, 22);
			this.tabEffect.Name = "tabEffect";
			this.tabEffect.Size = new System.Drawing.Size(964, 709);
			this.tabEffect.TabIndex = 7;
			this.tabEffect.Text = "エフェクト ->";
			this.tabEffect.UseVisualStyleBackColor = true;
			// 
			// ctrl_SqcList_Ef
			// 
			this.ctrl_SqcList_Ef.AutoSize = true;
			this.ctrl_SqcList_Ef.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.ctrl_SqcList_Ef.Dock = System.Windows.Forms.DockStyle.Fill;
			this.ctrl_SqcList_Ef.Location = new System.Drawing.Point(0, 0);
			this.ctrl_SqcList_Ef.Name = "ctrl_SqcList_Ef";
			this.ctrl_SqcList_Ef.Size = new System.Drawing.Size(964, 709);
			this.ctrl_SqcList_Ef.TabIndex = 1;
			// 
			// tabScriptE
			// 
			this.tabScriptE.Controls.Add(this.cpd_Garnish);
			this.tabScriptE.Location = new System.Drawing.Point(4, 22);
			this.tabScriptE.Name = "tabScriptE";
			this.tabScriptE.Padding = new System.Windows.Forms.Padding(3);
			this.tabScriptE.Size = new System.Drawing.Size(964, 709);
			this.tabScriptE.TabIndex = 1;
			this.tabScriptE.Text = "スクリプト(E)";
			this.tabScriptE.UseVisualStyleBackColor = true;
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
			this.tabCommand.Controls.Add(this.ctrl_CmdList1);
			this.tabCommand.Location = new System.Drawing.Point(4, 22);
			this.tabCommand.Name = "tabCommand";
			this.tabCommand.Size = new System.Drawing.Size(964, 709);
			this.tabCommand.TabIndex = 2;
			this.tabCommand.Text = "コマンド";
			this.tabCommand.UseVisualStyleBackColor = true;
			// 
			// ctrl_CmdList1
			// 
			this.ctrl_CmdList1.Location = new System.Drawing.Point(0, 0);
			this.ctrl_CmdList1.Name = "ctrl_CmdList1";
			this.ctrl_CmdList1.Size = new System.Drawing.Size(880, 573);
			this.ctrl_CmdList1.TabIndex = 0;
			// 
			// tabBranch
			// 
			this.tabBranch.Controls.Add(this.ctrl_Branch1);
			this.tabBranch.Location = new System.Drawing.Point(4, 22);
			this.tabBranch.Name = "tabBranch";
			this.tabBranch.Size = new System.Drawing.Size(964, 709);
			this.tabBranch.TabIndex = 4;
			this.tabBranch.Text = "ブランチ";
			this.tabBranch.UseVisualStyleBackColor = true;
			// 
			// ctrl_Branch1
			// 
			this.ctrl_Branch1.BD_Branch = bindingDictionary_11;
			this.ctrl_Branch1.BD_Command = bindingDictionary_12;
			this.ctrl_Branch1.BD_Sequence = bindingDictionary_13;
			this.ctrl_Branch1.Location = new System.Drawing.Point(0, 0);
			this.ctrl_Branch1.Name = "ctrl_Branch1";
			this.ctrl_Branch1.Size = new System.Drawing.Size(766, 568);
			this.ctrl_Branch1.TabIndex = 0;
			// 
			// tabRoute
			// 
			this.tabRoute.Controls.Add(this.ctrl_Route1);
			this.tabRoute.Location = new System.Drawing.Point(4, 22);
			this.tabRoute.Name = "tabRoute";
			this.tabRoute.Size = new System.Drawing.Size(964, 709);
			this.tabRoute.TabIndex = 5;
			this.tabRoute.Text = "ルート";
			this.tabRoute.UseVisualStyleBackColor = true;
			// 
			// ctrl_Route1
			// 
			this.ctrl_Route1.Location = new System.Drawing.Point(12, 0);
			this.ctrl_Route1.Name = "ctrl_Route1";
			this.ctrl_Route1.Size = new System.Drawing.Size(809, 611);
			this.ctrl_Route1.TabIndex = 0;
			// 
			// openFileDialog1
			// 
			this.openFileDialog1.FileName = "openFileDialog1";
			// 
			// FormMain
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(972, 784);
			this.Controls.Add(this.statusStrip1);
			this.Controls.Add(this.menuStrip1);
			this.Controls.Add(this.tabControl1);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "FormMain";
			this.Text = "ScriptEditor";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
			this.Shown += new System.EventHandler(this.FormMain_Shown);
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.FormMain_Paint);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.tabControl1.ResumeLayout(false);
			this.tabAction.ResumeLayout(false);
			this.tabAction.PerformLayout();
			this.tabScriptA.ResumeLayout(false);
			this.tabEffect.ResumeLayout(false);
			this.tabEffect.PerformLayout();
			this.tabScriptE.ResumeLayout(false);
			this.tabCommand.ResumeLayout(false);
			this.tabBranch.ResumeLayout(false);
			this.tabRoute.ResumeLayout(false);
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
		private System.Windows.Forms.TabPage tabScriptA;
		private System.Windows.Forms.TabPage tabCommand;
		private System.Windows.Forms.ToolStripMenuItem 別名保存ToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem 基準保存TToolStripMenuItem;
		private System.Windows.Forms.TabPage tabScriptE;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
		private System.Windows.Forms.SaveFileDialog saveFileDialog1;
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		private Ctrl_Compend cpd_Behavior;
		private Ctrl_Compend cpd_Garnish;
		private System.Windows.Forms.ToolStripMenuItem テキストから読込ToolStripMenuItem;
		private System.Windows.Forms.TabPage tabBranch;
		private Ctrl_CmdList ctrl_CmdList1;
		private Ctrl_Branch ctrl_Branch1;
		private System.Windows.Forms.TabPage tabRoute;
		private Ctrl_Route ctrl_Route1;
		private System.Windows.Forms.TabPage tabAction;
		private Ctrl_SqcList ctrl_SqcList_Act;
		private System.Windows.Forms.TabPage tabEffect;
		private Ctrl_SqcList ctrl_SqcList_Ef;
		private System.Windows.Forms.ToolStripMenuItem バイナリから読込BToolStripMenuItem;
	}
}

