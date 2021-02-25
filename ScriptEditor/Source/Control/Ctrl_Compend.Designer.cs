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
			this.colorDialog1 = new System.Windows.Forms.ColorDialog();
			this.listBox1 = new System.Windows.Forms.ListBox();
			this.pictureBox2 = new System.Windows.Forms.PictureBox();
			this.panel1 = new System.Windows.Forms.Panel();
			this.sqcBoard1 = new ScriptEditor.SqcBoard();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
			this.panel1.SuspendLayout();
			this.SuspendLayout();
			// 
			// listBox1
			// 
			this.listBox1.FormattingEnabled = true;
			this.listBox1.ItemHeight = 12;
			this.listBox1.Location = new System.Drawing.Point(0, 0);
			this.listBox1.Name = "listBox1";
			this.listBox1.Size = new System.Drawing.Size(119, 496);
			this.listBox1.TabIndex = 1;
			// 
			// pictureBox2
			// 
			this.pictureBox2.BackColor = System.Drawing.Color.DarkGray;
			this.pictureBox2.Location = new System.Drawing.Point(137, 148);
			this.pictureBox2.Name = "pictureBox2";
			this.pictureBox2.Size = new System.Drawing.Size(404, 348);
			this.pictureBox2.TabIndex = 2;
			this.pictureBox2.TabStop = false;
			// 
			// panel1
			// 
			this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.panel1.AutoScroll = true;
			this.panel1.Controls.Add(this.sqcBoard1);
			this.panel1.Location = new System.Drawing.Point(137, 3);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(636, 493);
			this.panel1.TabIndex = 4;
			// 
			// sqcBoard1
			// 
			this.sqcBoard1.BackColor = System.Drawing.Color.White;
			this.sqcBoard1.Location = new System.Drawing.Point(0, 0);
			this.sqcBoard1.Name = "sqcBoard1";
			this.sqcBoard1.Size = new System.Drawing.Size(500, 100);
			this.sqcBoard1.TabIndex = 3;
			// 
			// Ctrl_Compend
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.pictureBox2);
			this.Controls.Add(this.listBox1);
			this.Controls.Add(this.panel1);
			this.Name = "Ctrl_Compend";
			this.Size = new System.Drawing.Size(776, 499);
			((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
			this.panel1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion
		private System.Windows.Forms.ColorDialog colorDialog1;
		private System.Windows.Forms.ListBox listBox1;
		private System.Windows.Forms.PictureBox pictureBox2;
		private SqcBoard sqcBoard1;
		private System.Windows.Forms.Panel panel1;
	}
}
