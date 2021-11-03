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
			this.Lbl_BlackOut = new System.Windows.Forms.Label();
			this.tBN_BlackOut = new ScriptEditor.TB_Number();
			this.Lbl_Vibration = new System.Windows.Forms.Label();
			this.tBN_Vibration = new ScriptEditor.TB_Number();
			this.Lbl_Stop = new System.Windows.Forms.Label();
			this.tBN_Stop = new ScriptEditor.TB_Number();
			this.RB_TRG_ALL = new System.Windows.Forms.RadioButton();
			this.RB_TRG_GRP = new System.Windows.Forms.RadioButton();
			this.RB_TRG_SGL = new System.Windows.Forms.RadioButton();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.TBSN_posx = new ScriptEditor.TB_ScpNumber();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// cB_ClcSt
			// 
			this.cB_ClcSt.FormattingEnabled = true;
			this.cB_ClcSt.Location = new System.Drawing.Point(244, 116);
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
			this.tB_Frame.Location = new System.Drawing.Point(59, 75);
			this.tB_Frame.Margin = new System.Windows.Forms.Padding(2);
			this.tB_Frame.Name = "tB_Frame";
			this.tB_Frame.ReadOnly = true;
			this.tB_Frame.Size = new System.Drawing.Size(62, 19);
			this.tB_Frame.TabIndex = 14;
			// 
			// lbl_clc
			// 
			this.lbl_clc.AutoSize = true;
			this.lbl_clc.Location = new System.Drawing.Point(207, 121);
			this.lbl_clc.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_clc.Name = "lbl_clc";
			this.lbl_clc.Size = new System.Drawing.Size(33, 12);
			this.lbl_clc.TabIndex = 7;
			this.lbl_clc.Text = "ClcSt";
			// 
			// lbl_VelX
			// 
			this.lbl_VelX.AutoSize = true;
			this.lbl_VelX.Location = new System.Drawing.Point(15, 156);
			this.lbl_VelX.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_VelX.Name = "lbl_VelX";
			this.lbl_VelX.Size = new System.Drawing.Size(29, 12);
			this.lbl_VelX.TabIndex = 8;
			this.lbl_VelX.Text = "VelX";
			// 
			// lbl_Frame
			// 
			this.lbl_Frame.AutoSize = true;
			this.lbl_Frame.Location = new System.Drawing.Point(15, 77);
			this.lbl_Frame.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_Frame.Name = "lbl_Frame";
			this.lbl_Frame.Size = new System.Drawing.Size(37, 12);
			this.lbl_Frame.TabIndex = 9;
			this.lbl_Frame.Text = "Frame";
			// 
			// lbl_AP
			// 
			this.lbl_AP.AutoSize = true;
			this.lbl_AP.Location = new System.Drawing.Point(182, 156);
			this.lbl_AP.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_AP.Name = "lbl_AP";
			this.lbl_AP.Size = new System.Drawing.Size(70, 12);
			this.lbl_AP.TabIndex = 10;
			this.lbl_AP.Text = "AttackPower";
			// 
			// lbl_PosX
			// 
			this.lbl_PosX.AutoSize = true;
			this.lbl_PosX.Location = new System.Drawing.Point(15, 120);
			this.lbl_PosX.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_PosX.Name = "lbl_PosX";
			this.lbl_PosX.Size = new System.Drawing.Size(31, 12);
			this.lbl_PosX.TabIndex = 8;
			this.lbl_PosX.Text = "PosX";
			// 
			// lbl_PosY
			// 
			this.lbl_PosY.AutoSize = true;
			this.lbl_PosY.Location = new System.Drawing.Point(101, 120);
			this.lbl_PosY.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_PosY.Name = "lbl_PosY";
			this.lbl_PosY.Size = new System.Drawing.Size(31, 12);
			this.lbl_PosY.TabIndex = 8;
			this.lbl_PosY.Text = "PosY";
			// 
			// lbl_VelY
			// 
			this.lbl_VelY.AutoSize = true;
			this.lbl_VelY.Location = new System.Drawing.Point(101, 156);
			this.lbl_VelY.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_VelY.Name = "lbl_VelY";
			this.lbl_VelY.Size = new System.Drawing.Size(29, 12);
			this.lbl_VelY.TabIndex = 8;
			this.lbl_VelY.Text = "VelY";
			// 
			// lbl_AccX
			// 
			this.lbl_AccX.AutoSize = true;
			this.lbl_AccX.Location = new System.Drawing.Point(15, 193);
			this.lbl_AccX.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_AccX.Name = "lbl_AccX";
			this.lbl_AccX.Size = new System.Drawing.Size(32, 12);
			this.lbl_AccX.TabIndex = 8;
			this.lbl_AccX.Text = "AccX";
			// 
			// lbl_AccY
			// 
			this.lbl_AccY.AutoSize = true;
			this.lbl_AccY.Location = new System.Drawing.Point(101, 193);
			this.lbl_AccY.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.lbl_AccY.Name = "lbl_AccY";
			this.lbl_AccY.Size = new System.Drawing.Size(32, 12);
			this.lbl_AccY.TabIndex = 8;
			this.lbl_AccY.Text = "AccY";
			// 
			// tBN_AccY
			// 
			this.tBN_AccY.GetFunc = null;
			this.tBN_AccY.Location = new System.Drawing.Point(141, 191);
			this.tBN_AccY.Name = "tBN_AccY";
			this.tBN_AccY.SetFunc = null;
			this.tBN_AccY.Size = new System.Drawing.Size(30, 19);
			this.tBN_AccY.TabIndex = 20;
			this.tBN_AccY.Text = "0";
			// 
			// tBN_AccX
			// 
			this.tBN_AccX.GetFunc = null;
			this.tBN_AccX.Location = new System.Drawing.Point(59, 190);
			this.tBN_AccX.Name = "tBN_AccX";
			this.tBN_AccX.SetFunc = null;
			this.tBN_AccX.Size = new System.Drawing.Size(30, 19);
			this.tBN_AccX.TabIndex = 20;
			this.tBN_AccX.Text = "0";
			// 
			// tBN_VelY
			// 
			this.tBN_VelY.GetFunc = null;
			this.tBN_VelY.Location = new System.Drawing.Point(141, 154);
			this.tBN_VelY.Name = "tBN_VelY";
			this.tBN_VelY.SetFunc = null;
			this.tBN_VelY.Size = new System.Drawing.Size(30, 19);
			this.tBN_VelY.TabIndex = 20;
			this.tBN_VelY.Text = "0";
			// 
			// tBN_VelX
			// 
			this.tBN_VelX.GetFunc = null;
			this.tBN_VelX.Location = new System.Drawing.Point(59, 153);
			this.tBN_VelX.Name = "tBN_VelX";
			this.tBN_VelX.SetFunc = null;
			this.tBN_VelX.Size = new System.Drawing.Size(30, 19);
			this.tBN_VelX.TabIndex = 20;
			this.tBN_VelX.Text = "0";
			// 
			// tBN_PosY
			// 
			this.tBN_PosY.GetFunc = null;
			this.tBN_PosY.Location = new System.Drawing.Point(141, 117);
			this.tBN_PosY.Name = "tBN_PosY";
			this.tBN_PosY.SetFunc = null;
			this.tBN_PosY.Size = new System.Drawing.Size(30, 19);
			this.tBN_PosY.TabIndex = 20;
			this.tBN_PosY.Text = "0";
			// 
			// tBN_PosX
			// 
			this.tBN_PosX.GetFunc = null;
			this.tBN_PosX.Location = new System.Drawing.Point(59, 116);
			this.tBN_PosX.Name = "tBN_PosX";
			this.tBN_PosX.SetFunc = null;
			this.tBN_PosX.Size = new System.Drawing.Size(30, 19);
			this.tBN_PosX.TabIndex = 20;
			this.tBN_PosX.Text = "0";
			// 
			// tBN_Power
			// 
			this.tBN_Power.GetFunc = null;
			this.tBN_Power.Location = new System.Drawing.Point(264, 153);
			this.tBN_Power.Margin = new System.Windows.Forms.Padding(2);
			this.tBN_Power.Name = "tBN_Power";
			this.tBN_Power.SetFunc = null;
			this.tBN_Power.Size = new System.Drawing.Size(54, 19);
			this.tBN_Power.TabIndex = 18;
			this.tBN_Power.Text = "0";
			// 
			// Lbl_Img
			// 
			this.Lbl_Img.AutoSize = true;
			this.Lbl_Img.Location = new System.Drawing.Point(148, 78);
			this.Lbl_Img.Name = "Lbl_Img";
			this.Lbl_Img.Size = new System.Drawing.Size(23, 12);
			this.Lbl_Img.TabIndex = 21;
			this.Lbl_Img.Text = "Img";
			// 
			// Tb_Img
			// 
			this.Tb_Img.Location = new System.Drawing.Point(177, 75);
			this.Tb_Img.Name = "Tb_Img";
			this.Tb_Img.ReadOnly = true;
			this.Tb_Img.Size = new System.Drawing.Size(141, 19);
			this.Tb_Img.TabIndex = 22;
			// 
			// Lbl_BlackOut
			// 
			this.Lbl_BlackOut.AutoSize = true;
			this.Lbl_BlackOut.Location = new System.Drawing.Point(15, 238);
			this.Lbl_BlackOut.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.Lbl_BlackOut.Name = "Lbl_BlackOut";
			this.Lbl_BlackOut.Size = new System.Drawing.Size(52, 12);
			this.Lbl_BlackOut.TabIndex = 10;
			this.Lbl_BlackOut.Text = "BlackOut";
			// 
			// tBN_BlackOut
			// 
			this.tBN_BlackOut.GetFunc = null;
			this.tBN_BlackOut.Location = new System.Drawing.Point(97, 235);
			this.tBN_BlackOut.Margin = new System.Windows.Forms.Padding(2);
			this.tBN_BlackOut.Name = "tBN_BlackOut";
			this.tBN_BlackOut.SetFunc = null;
			this.tBN_BlackOut.Size = new System.Drawing.Size(74, 19);
			this.tBN_BlackOut.TabIndex = 18;
			this.tBN_BlackOut.Text = "0";
			// 
			// Lbl_Vibration
			// 
			this.Lbl_Vibration.AutoSize = true;
			this.Lbl_Vibration.Location = new System.Drawing.Point(15, 261);
			this.Lbl_Vibration.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.Lbl_Vibration.Name = "Lbl_Vibration";
			this.Lbl_Vibration.Size = new System.Drawing.Size(51, 12);
			this.Lbl_Vibration.TabIndex = 10;
			this.Lbl_Vibration.Text = "Vibration";
			// 
			// tBN_Vibration
			// 
			this.tBN_Vibration.GetFunc = null;
			this.tBN_Vibration.Location = new System.Drawing.Point(97, 258);
			this.tBN_Vibration.Margin = new System.Windows.Forms.Padding(2);
			this.tBN_Vibration.Name = "tBN_Vibration";
			this.tBN_Vibration.SetFunc = null;
			this.tBN_Vibration.Size = new System.Drawing.Size(74, 19);
			this.tBN_Vibration.TabIndex = 18;
			this.tBN_Vibration.Text = "0";
			// 
			// Lbl_Stop
			// 
			this.Lbl_Stop.AutoSize = true;
			this.Lbl_Stop.Location = new System.Drawing.Point(15, 284);
			this.Lbl_Stop.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.Lbl_Stop.Name = "Lbl_Stop";
			this.Lbl_Stop.Size = new System.Drawing.Size(28, 12);
			this.Lbl_Stop.TabIndex = 10;
			this.Lbl_Stop.Text = "Stop";
			// 
			// tBN_Stop
			// 
			this.tBN_Stop.GetFunc = null;
			this.tBN_Stop.Location = new System.Drawing.Point(97, 281);
			this.tBN_Stop.Margin = new System.Windows.Forms.Padding(2);
			this.tBN_Stop.Name = "tBN_Stop";
			this.tBN_Stop.SetFunc = null;
			this.tBN_Stop.Size = new System.Drawing.Size(74, 19);
			this.tBN_Stop.TabIndex = 18;
			this.tBN_Stop.Text = "0";
			// 
			// RB_TRG_ALL
			// 
			this.RB_TRG_ALL.AutoSize = true;
			this.RB_TRG_ALL.Font = new System.Drawing.Font("MS UI Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.RB_TRG_ALL.Location = new System.Drawing.Point(26, 13);
			this.RB_TRG_ALL.Name = "RB_TRG_ALL";
			this.RB_TRG_ALL.Size = new System.Drawing.Size(42, 20);
			this.RB_TRG_ALL.TabIndex = 23;
			this.RB_TRG_ALL.Text = "All";
			this.RB_TRG_ALL.UseVisualStyleBackColor = true;
			this.RB_TRG_ALL.CheckedChanged += new System.EventHandler(this.RB_TRG_ALL_CheckedChanged);
			// 
			// RB_TRG_GRP
			// 
			this.RB_TRG_GRP.AutoSize = true;
			this.RB_TRG_GRP.Font = new System.Drawing.Font("MS UI Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.RB_TRG_GRP.Location = new System.Drawing.Point(87, 13);
			this.RB_TRG_GRP.Name = "RB_TRG_GRP";
			this.RB_TRG_GRP.Size = new System.Drawing.Size(67, 20);
			this.RB_TRG_GRP.TabIndex = 24;
			this.RB_TRG_GRP.Text = "Group";
			this.RB_TRG_GRP.UseVisualStyleBackColor = true;
			this.RB_TRG_GRP.CheckedChanged += new System.EventHandler(this.RB_TRG_GRP_CheckedChanged);
			// 
			// RB_TRG_SGL
			// 
			this.RB_TRG_SGL.AutoSize = true;
			this.RB_TRG_SGL.Checked = true;
			this.RB_TRG_SGL.Font = new System.Drawing.Font("MS UI Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.RB_TRG_SGL.Location = new System.Drawing.Point(170, 13);
			this.RB_TRG_SGL.Name = "RB_TRG_SGL";
			this.RB_TRG_SGL.Size = new System.Drawing.Size(65, 20);
			this.RB_TRG_SGL.TabIndex = 25;
			this.RB_TRG_SGL.TabStop = true;
			this.RB_TRG_SGL.Text = "Single";
			this.RB_TRG_SGL.UseVisualStyleBackColor = true;
			this.RB_TRG_SGL.CheckedChanged += new System.EventHandler(this.RB_TRG_SGL_CheckedChanged);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.RB_TRG_SGL);
			this.groupBox1.Controls.Add(this.RB_TRG_GRP);
			this.groupBox1.Controls.Add(this.RB_TRG_ALL);
			this.groupBox1.Location = new System.Drawing.Point(8, 7);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(310, 43);
			this.groupBox1.TabIndex = 26;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Target";
			// 
			// TBSN_posx
			// 
			this.TBSN_posx.Location = new System.Drawing.Point(264, 214);
			this.TBSN_posx.Name = "TBSN_posx";
			this.TBSN_posx.PrmInt = null;
			this.TBSN_posx.Scp = null;
			this.TBSN_posx.Size = new System.Drawing.Size(45, 19);
			this.TBSN_posx.TabIndex = 27;
			// 
			// Ctrl_Script
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.TBSN_posx);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.Tb_Img);
			this.Controls.Add(this.Lbl_Img);
			this.Controls.Add(this.tBN_AccY);
			this.Controls.Add(this.tBN_AccX);
			this.Controls.Add(this.tBN_VelY);
			this.Controls.Add(this.tBN_VelX);
			this.Controls.Add(this.tBN_PosY);
			this.Controls.Add(this.tBN_PosX);
			this.Controls.Add(this.tBN_Stop);
			this.Controls.Add(this.tBN_Vibration);
			this.Controls.Add(this.tBN_BlackOut);
			this.Controls.Add(this.tBN_Power);
			this.Controls.Add(this.cB_ClcSt);
			this.Controls.Add(this.tB_Frame);
			this.Controls.Add(this.lbl_clc);
			this.Controls.Add(this.lbl_PosY);
			this.Controls.Add(this.lbl_AccY);
			this.Controls.Add(this.lbl_PosX);
			this.Controls.Add(this.lbl_AccX);
			this.Controls.Add(this.Lbl_Stop);
			this.Controls.Add(this.lbl_VelY);
			this.Controls.Add(this.Lbl_Vibration);
			this.Controls.Add(this.lbl_VelX);
			this.Controls.Add(this.Lbl_BlackOut);
			this.Controls.Add(this.lbl_Frame);
			this.Controls.Add(this.lbl_AP);
			this.Margin = new System.Windows.Forms.Padding(2);
			this.Name = "Ctrl_Script";
			this.Size = new System.Drawing.Size(337, 319);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
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
		private System.Windows.Forms.Label Lbl_BlackOut;
		public TB_Number tBN_BlackOut;
		private System.Windows.Forms.Label Lbl_Vibration;
		public TB_Number tBN_Vibration;
		private System.Windows.Forms.Label Lbl_Stop;
		public TB_Number tBN_Stop;
		private System.Windows.Forms.RadioButton RB_TRG_ALL;
		private System.Windows.Forms.RadioButton RB_TRG_GRP;
		private System.Windows.Forms.RadioButton RB_TRG_SGL;
		private System.Windows.Forms.GroupBox groupBox1;
		private TB_ScpNumber TBSN_posx;
	}
}
