namespace ScriptEditor
{
	partial class SqcBoard
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

				//内部定数
				PEN_BAR.Dispose ();
				PEN_BASE_BAR.Dispose ();
				PEN_SELECTED.Dispose ();
				BRUSH_0.Dispose ();
				STR_FMT.Dispose ();
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
			this.Btn_GrpMake = new System.Windows.Forms.Button();
			this.Btn_GrpRel = new System.Windows.Forms.Button();
			this.Btn_GrpPaste = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.Btn_MulDel = new System.Windows.Forms.Button();
			this.Btn_ScpDel = new System.Windows.Forms.Button();
			this.Btn_MulAdd = new System.Windows.Forms.Button();
			this.Btn_ScpAdd = new System.Windows.Forms.Button();
			this.panel1 = new System.Windows.Forms.Panel();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.panel1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.SuspendLayout();
			// 
			// Btn_GrpMake
			// 
			this.Btn_GrpMake.Location = new System.Drawing.Point(6, 16);
			this.Btn_GrpMake.Name = "Btn_GrpMake";
			this.Btn_GrpMake.Size = new System.Drawing.Size(43, 27);
			this.Btn_GrpMake.TabIndex = 0;
			this.Btn_GrpMake.Text = "作成";
			this.Btn_GrpMake.UseVisualStyleBackColor = true;
			this.Btn_GrpMake.Click += new System.EventHandler(this.button1_Click);
			// 
			// Btn_GrpRel
			// 
			this.Btn_GrpRel.Location = new System.Drawing.Point(55, 16);
			this.Btn_GrpRel.Name = "Btn_GrpRel";
			this.Btn_GrpRel.Size = new System.Drawing.Size(42, 27);
			this.Btn_GrpRel.TabIndex = 1;
			this.Btn_GrpRel.Text = "解除";
			this.Btn_GrpRel.UseVisualStyleBackColor = true;
			this.Btn_GrpRel.Click += new System.EventHandler(this.button2_Click);
			// 
			// Btn_GrpPaste
			// 
			this.Btn_GrpPaste.Location = new System.Drawing.Point(103, 16);
			this.Btn_GrpPaste.Name = "Btn_GrpPaste";
			this.Btn_GrpPaste.Size = new System.Drawing.Size(50, 27);
			this.Btn_GrpPaste.TabIndex = 4;
			this.Btn_GrpPaste.Text = "同一化";
			this.Btn_GrpPaste.UseVisualStyleBackColor = true;
			this.Btn_GrpPaste.Click += new System.EventHandler(this.Btn_Paste_Click);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.Btn_GrpMake);
			this.groupBox1.Controls.Add(this.Btn_GrpPaste);
			this.groupBox1.Controls.Add(this.Btn_GrpRel);
			this.groupBox1.Location = new System.Drawing.Point(316, 3);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(156, 53);
			this.groupBox1.TabIndex = 5;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "グループ";
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.Btn_MulDel);
			this.groupBox2.Controls.Add(this.Btn_ScpDel);
			this.groupBox2.Controls.Add(this.Btn_MulAdd);
			this.groupBox2.Controls.Add(this.Btn_ScpAdd);
			this.groupBox2.Location = new System.Drawing.Point(19, 3);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(271, 53);
			this.groupBox2.TabIndex = 7;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "スクリプト";
			// 
			// Btn_MulDel
			// 
			this.Btn_MulDel.Location = new System.Drawing.Point(184, 16);
			this.Btn_MulDel.Name = "Btn_MulDel";
			this.Btn_MulDel.Size = new System.Drawing.Size(68, 26);
			this.Btn_MulDel.TabIndex = 8;
			this.Btn_MulDel.Text = "複数削除";
			this.Btn_MulDel.UseVisualStyleBackColor = true;
			// 
			// Btn_ScpDel
			// 
			this.Btn_ScpDel.Location = new System.Drawing.Point(62, 16);
			this.Btn_ScpDel.Name = "Btn_ScpDel";
			this.Btn_ScpDel.Size = new System.Drawing.Size(41, 26);
			this.Btn_ScpDel.TabIndex = 8;
			this.Btn_ScpDel.Text = "削除";
			this.Btn_ScpDel.UseVisualStyleBackColor = true;
			// 
			// Btn_MulAdd
			// 
			this.Btn_MulAdd.Location = new System.Drawing.Point(109, 16);
			this.Btn_MulAdd.Name = "Btn_MulAdd";
			this.Btn_MulAdd.Size = new System.Drawing.Size(69, 26);
			this.Btn_MulAdd.TabIndex = 8;
			this.Btn_MulAdd.Text = "複数追加";
			this.Btn_MulAdd.UseVisualStyleBackColor = true;
			// 
			// Btn_ScpAdd
			// 
			this.Btn_ScpAdd.Location = new System.Drawing.Point(15, 16);
			this.Btn_ScpAdd.Name = "Btn_ScpAdd";
			this.Btn_ScpAdd.Size = new System.Drawing.Size(41, 26);
			this.Btn_ScpAdd.TabIndex = 8;
			this.Btn_ScpAdd.Text = "追加";
			this.Btn_ScpAdd.UseVisualStyleBackColor = true;
			// 
			// panel1
			// 
			this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.panel1.AutoScroll = true;
			this.panel1.Controls.Add(this.pictureBox1);
			this.panel1.Location = new System.Drawing.Point(10, 62);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(492, 105);
			this.panel1.TabIndex = 8;
			// 
			// pictureBox1
			// 
			this.pictureBox1.BackColor = System.Drawing.Color.White;
			this.pictureBox1.Location = new System.Drawing.Point(0, 0);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(477, 105);
			this.pictureBox1.TabIndex = 2;
			this.pictureBox1.TabStop = false;
			this.pictureBox1.Paint += new System.Windows.Forms.PaintEventHandler(this.pictureBox1_Paint);
			this.pictureBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
			this.pictureBox1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
			this.pictureBox1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
			// 
			// SqcBoard
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.Control;
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.panel1);
			this.Name = "SqcBoard";
			this.Size = new System.Drawing.Size(517, 170);
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.SqcBoard_Paint);
			this.groupBox1.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			this.panel1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button Btn_GrpMake;
		private System.Windows.Forms.Button Btn_GrpRel;
		private System.Windows.Forms.Button Btn_GrpPaste;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Button Btn_ScpAdd;
		private System.Windows.Forms.Button Btn_MulDel;
		private System.Windows.Forms.Button Btn_ScpDel;
		private System.Windows.Forms.Button Btn_MulAdd;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.Panel panel1;
	}
}
