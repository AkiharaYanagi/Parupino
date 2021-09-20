namespace ScriptEditor
{
	partial class Ctrl_Script
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
			this.cB_ClcSt = new System.Windows.Forms.ComboBox();
			this.tB_Frame = new System.Windows.Forms.TextBox();
			this.lbl_clc = new System.Windows.Forms.Label();
			this.lbl_VelX = new System.Windows.Forms.Label();
			this.lbl_Frame = new System.Windows.Forms.Label();
			this.lbl_AP = new System.Windows.Forms.Label();
			this.lbl_PosX = new System.Windows.Forms.Label();
			this.lbl_PosY = new System.Windows.Forms.Label();
			this.lbl_VelY = new System.Windows.Forms.Label();
			this.lbl_AccX = new System.Windows.Forms.Label();
			this.lbl_AccY = new System.Windows.Forms.Label();
			this.tBN_AccY = new ScriptEditor.TB_Number();
			this.tBN_AccX = new ScriptEditor.TB_Number();
			this.tBN_VelY = new ScriptEditor.TB_Number();
			this.tBN_VelX = new ScriptEditor.TB_Number();
			this.tBN_PosY = new ScriptEditor.TB_Number();
			this.tBN_PosX = new ScriptEditor.TB_Number();
			this.tBN_Power = new ScriptEditor.TB_Number();
			this.Lbl_Img = new System.Windows.Forms.Label();
			this.Tb_Img = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// cB_ClcSt
			// 
			this.cB_ClcSt.FormattingEnabled = true;
			this.cB_ClcSt.Location = new System.Drawing.Point(249, 62);
			this.cB_ClcSt.Margin = new System.Windows.Forms.Padding(2);
			this.cB_ClcSt.Name = "cB_ClcSt";
			this.cB_ClcSt.Size = new System.Drawing.Size(74, 20);
			this.cB_ClcSt.TabIndex = 15;
			this.cB_ClcSt.SelectedIndexChanged += new System.EventHandler(this.cB_ClcSt_SelectedIndexChanged);
			this.cB_ClcSt.SelectionChangeCommitted += new System.EventHandler(this.cB_ClcSt_SelectionChangeCommitted);
			// 
			// tB_Frame
			// 
			this.tB_Frame.BackColor = System.Drawing.SystemColors.Control;
			this.tB_Frame.Cursor = System.Windows.Forms.Cursors.Default;
			this.tB_Frame.Location = new System.Drawing.Point(64, 21);
			this.tB_Frame.Margin = new System.Windows.Forms.Padding(2);
			this.tB_Frame.Name = "tB_Frame";
			this.tB_Frame.ReadOnly = true;
			this.tB_Frame.Size = new System.Drawing.Size(62, 19);
			this.tB_Frame.TabIndex = 14;
			// 
			// lbl_clc
			// 
			this.lbl_clc.AutoSize = true;
			this.lbl_clc.Location = new System.Drawing.Point(212, 67);
			this.lbl_clc.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_clc.Name = "lbl_clc";
			this.lbl_clc.Size = new System.Drawing.Size(33, 12);
			this.lbl_clc.TabIndex = 7;
			this.lbl_clc.Text = "ClcSt";
			// 
			// lbl_VelX
			// 
			this.lbl_VelX.AutoSize = true;
			this.lbl_VelX.Location = new System.Drawing.Point(20, 102);
			this.lbl_VelX.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_VelX.Name = "lbl_VelX";
			this.lbl_VelX.Size = new System.Drawing.Size(29, 12);
			this.lbl_VelX.TabIndex = 8;
			this.lbl_VelX.Text = "VelX";
			// 
			// lbl_Frame
			// 
			this.lbl_Frame.AutoSize = true;
			this.lbl_Frame.Location = new System.Drawing.Point(20, 23);
			this.lbl_Frame.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_Frame.Name = "lbl_Frame";
			this.lbl_Frame.Size = new System.Drawing.Size(37, 12);
			this.lbl_Frame.TabIndex = 9;
			this.lbl_Frame.Text = "Frame";
			// 
			// lbl_AP
			// 
			this.lbl_AP.AutoSize = true;
			this.lbl_AP.Location = new System.Drawing.Point(187, 102);
			this.lbl_AP.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_AP.Name = "lbl_AP";
			this.lbl_AP.Size = new System.Drawing.Size(70, 12);
			this.lbl_AP.TabIndex = 10;
			this.lbl_AP.Text = "AttackPower";
			// 
			// lbl_PosX
			// 
			this.lbl_PosX.AutoSize = true;
			this.lbl_PosX.Location = new System.Drawing.Point(20, 66);
			this.lbl_PosX.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_PosX.Name = "lbl_PosX";
			this.lbl_PosX.Size = new System.Drawing.Size(31, 12);
			this.lbl_PosX.TabIndex = 8;
			this.lbl_PosX.Text = "PosX";
			// 
			// lbl_PosY
			// 
			this.lbl_PosY.AutoSize = true;
			this.lbl_PosY.Location = new System.Drawing.Point(106, 66);
			this.lbl_PosY.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_PosY.Name = "lbl_PosY";
			this.lbl_PosY.Size = new System.Drawing.Size(31, 12);
			this.lbl_PosY.TabIndex = 8;
			this.lbl_PosY.Text = "PosY";
			// 
			// lbl_VelY
			// 
			this.lbl_VelY.AutoSize = true;
			this.lbl_VelY.Location = new System.Drawing.Point(106, 102);
			this.lbl_VelY.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_VelY.Name = "lbl_VelY";
			this.lbl_VelY.Size = new System.Drawing.Size(29, 12);
			this.lbl_VelY.TabIndex = 8;
			this.lbl_VelY.Text = "VelY";
			// 
			// lbl_AccX
			// 
			this.lbl_AccX.AutoSize = true;
			this.lbl_AccX.Location = new System.Drawing.Point(20, 139);
			this.lbl_AccX.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_AccX.Name = "lbl_AccX";
			this.lbl_AccX.Size = new System.Drawing.Size(32, 12);
			this.lbl_AccX.TabIndex = 8;
			this.lbl_AccX.Text = "AccX";
			// 
			// lbl_AccY
			// 
			this.lbl_AccY.AutoSize = true;
			this.lbl_AccY.Location = new System.Drawing.Point(106, 139);
			this.lbl_AccY.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_AccY.Name = "lbl_AccY";
			this.lbl_AccY.Size = new System.Drawing.Size(32, 12);
			this.lbl_AccY.TabIndex = 8;
			this.lbl_AccY.Text = "AccY";
			// 
			// tBN_AccY
			// 
			this.tBN_AccY.GetFunc = null;
			this.tBN_AccY.GroupSetter = null;
			this.tBN_AccY.Location = new System.Drawing.Point(146, 137);
			this.tBN_AccY.Name = "tBN_AccY";
			this.tBN_AccY.SetFunc = null;
			this.tBN_AccY.Size = new System.Drawing.Size(30, 19);
			this.tBN_AccY.TabIndex = 20;
			this.tBN_AccY.Text = "0";
			// 
			// tBN_AccX
			// 
			this.tBN_AccX.GetFunc = null;
			this.tBN_AccX.GroupSetter = null;
			this.tBN_AccX.Location = new System.Drawing.Point(64, 136);
			this.tBN_AccX.Name = "tBN_AccX";
			this.tBN_AccX.SetFunc = null;
			this.tBN_AccX.Size = new System.Drawing.Size(30, 19);
			this.tBN_AccX.TabIndex = 20;
			this.tBN_AccX.Text = "0";
			// 
			// tBN_VelY
			// 
			this.tBN_VelY.GetFunc = null;
			this.tBN_VelY.GroupSetter = null;
			this.tBN_VelY.Location = new System.Drawing.Point(146, 100);
			this.tBN_VelY.Name = "tBN_VelY";
			this.tBN_VelY.SetFunc = null;
			this.tBN_VelY.Size = new System.Drawing.Size(30, 19);
			this.tBN_VelY.TabIndex = 20;
			this.tBN_VelY.Text = "0";
			// 
			// tBN_VelX
			// 
			this.tBN_VelX.GetFunc = null;
			this.tBN_VelX.GroupSetter = null;
			this.tBN_VelX.Location = new System.Drawing.Point(64, 99);
			this.tBN_VelX.Name = "tBN_VelX";
			this.tBN_VelX.SetFunc = null;
			this.tBN_VelX.Size = new System.Drawing.Size(30, 19);
			this.tBN_VelX.TabIndex = 20;
			this.tBN_VelX.Text = "0";
			// 
			// tBN_PosY
			// 
			this.tBN_PosY.GetFunc = null;
			this.tBN_PosY.GroupSetter = null;
			this.tBN_PosY.Location = new System.Drawing.Point(146, 63);
			this.tBN_PosY.Name = "tBN_PosY";
			this.tBN_PosY.SetFunc = null;
			this.tBN_PosY.Size = new System.Drawing.Size(30, 19);
			this.tBN_PosY.TabIndex = 20;
			this.tBN_PosY.Text = "0";
			// 
			// tBN_PosX
			// 
			this.tBN_PosX.GetFunc = null;
			this.tBN_PosX.GroupSetter = null;
			this.tBN_PosX.Location = new System.Drawing.Point(64, 62);
			this.tBN_PosX.Name = "tBN_PosX";
			this.tBN_PosX.SetFunc = null;
			this.tBN_PosX.Size = new System.Drawing.Size(30, 19);
			this.tBN_PosX.TabIndex = 20;
			this.tBN_PosX.Text = "0";
			// 
			// tBN_Power
			// 
			this.tBN_Power.GetFunc = null;
			this.tBN_Power.GroupSetter = null;
			this.tBN_Power.Location = new System.Drawing.Point(269, 99);
			this.tBN_Power.Margin = new System.Windows.Forms.Padding(2);
			this.tBN_Power.Name = "tBN_Power";
			this.tBN_Power.SetFunc = null;
			this.tBN_Power.Size = new System.Drawing.Size(74, 19);
			this.tBN_Power.TabIndex = 18;
			this.tBN_Power.Text = "0";
			// 
			// Lbl_Img
			// 
			this.Lbl_Img.AutoSize = true;
			this.Lbl_Img.Location = new System.Drawing.Point(153, 24);
			this.Lbl_Img.Name = "Lbl_Img";
			this.Lbl_Img.Size = new System.Drawing.Size(23, 12);
			this.Lbl_Img.TabIndex = 21;
			this.Lbl_Img.Text = "Img";
			// 
			// Tb_Img
			// 
			this.Tb_Img.Location = new System.Drawing.Point(182, 21);
			this.Tb_Img.Name = "Tb_Img";
			this.Tb_Img.ReadOnly = true;
			this.Tb_Img.Size = new System.Drawing.Size(141, 19);
			this.Tb_Img.TabIndex = 22;
			// 
			// Ctrl_Script
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.Tb_Img);
			this.Controls.Add(this.Lbl_Img);
			this.Controls.Add(this.tBN_AccY);
			this.Controls.Add(this.tBN_AccX);
			this.Controls.Add(this.tBN_VelY);
			this.Controls.Add(this.tBN_VelX);
			this.Controls.Add(this.tBN_PosY);
			this.Controls.Add(this.tBN_PosX);
			this.Controls.Add(this.tBN_Power);
			this.Controls.Add(this.cB_ClcSt);
			this.Controls.Add(this.tB_Frame);
			this.Controls.Add(this.lbl_clc);
			this.Controls.Add(this.lbl_PosY);
			this.Controls.Add(this.lbl_AccY);
			this.Controls.Add(this.lbl_PosX);
			this.Controls.Add(this.lbl_AccX);
			this.Controls.Add(this.lbl_VelY);
			this.Controls.Add(this.lbl_VelX);
			this.Controls.Add(this.lbl_Frame);
			this.Controls.Add(this.lbl_AP);
			this.Margin = new System.Windows.Forms.Padding(2);
			this.Name = "Ctrl_Script";
			this.Size = new System.Drawing.Size(368, 171);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		public TB_Number tBN_Power;
		public System.Windows.Forms.ComboBox cB_ClcSt;
		public System.Windows.Forms.TextBox tB_Frame;
		private System.Windows.Forms.Label lbl_clc;
		private System.Windows.Forms.Label lbl_VelX;
		private System.Windows.Forms.Label lbl_Frame;
		private System.Windows.Forms.Label lbl_AP;
		private System.Windows.Forms.Label lbl_PosX;
		private System.Windows.Forms.Label lbl_PosY;
		private System.Windows.Forms.Label lbl_VelY;
		private System.Windows.Forms.Label lbl_AccX;
		private System.Windows.Forms.Label lbl_AccY;
		private TB_Number tBN_PosX;
		private TB_Number tBN_VelX;
		private TB_Number tBN_AccX;
		private TB_Number tBN_PosY;
		private TB_Number tBN_VelY;
		private TB_Number tBN_AccY;
		private System.Windows.Forms.Label Lbl_Img;
		private System.Windows.Forms.TextBox Tb_Img;
	}
}
