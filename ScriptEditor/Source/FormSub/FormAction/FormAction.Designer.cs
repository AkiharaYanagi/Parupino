namespace ScriptEditor
{
	partial class FormAction
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose ( bool disposing )
		{
			if ( disposing && ( components != null ) )
			{
				components.Dispose ();
			}
			base.Dispose ( disposing );
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent ()
		{
			this.lbl_Name = new System.Windows.Forms.Label();
			this.lbl_Next = new System.Windows.Forms.Label();
			this.lbl_Category = new System.Windows.Forms.Label();
			this.lbl_Balance = new System.Windows.Forms.Label();
			this.lbl_Posture = new System.Windows.Forms.Label();
			this.TB_Name = new System.Windows.Forms.TextBox();
			this.CB_Category = new System.Windows.Forms.ComboBox();
			this.CB_Posture = new System.Windows.Forms.ComboBox();
			this.CBSL_Next = new ScriptEditor.CB_SequenceList();
			this.TBN_Balance = new ScriptEditor.TB_Number();
			this.SuspendLayout();
			// 
			// lbl_Name
			// 
			this.lbl_Name.AutoSize = true;
			this.lbl_Name.Location = new System.Drawing.Point(12, 12);
			this.lbl_Name.Name = "lbl_Name";
			this.lbl_Name.Size = new System.Drawing.Size(34, 12);
			this.lbl_Name.TabIndex = 1;
			this.lbl_Name.Text = "Name";
			// 
			// lbl_Next
			// 
			this.lbl_Next.AutoSize = true;
			this.lbl_Next.Location = new System.Drawing.Point(12, 49);
			this.lbl_Next.Name = "lbl_Next";
			this.lbl_Next.Size = new System.Drawing.Size(29, 12);
			this.lbl_Next.TabIndex = 2;
			this.lbl_Next.Text = "Next";
			// 
			// lbl_Category
			// 
			this.lbl_Category.AutoSize = true;
			this.lbl_Category.Location = new System.Drawing.Point(12, 86);
			this.lbl_Category.Name = "lbl_Category";
			this.lbl_Category.Size = new System.Drawing.Size(51, 12);
			this.lbl_Category.TabIndex = 3;
			this.lbl_Category.Text = "Category";
			// 
			// lbl_Balance
			// 
			this.lbl_Balance.AutoSize = true;
			this.lbl_Balance.Location = new System.Drawing.Point(12, 160);
			this.lbl_Balance.Name = "lbl_Balance";
			this.lbl_Balance.Size = new System.Drawing.Size(46, 12);
			this.lbl_Balance.TabIndex = 4;
			this.lbl_Balance.Text = "Balance";
			// 
			// lbl_Posture
			// 
			this.lbl_Posture.AutoSize = true;
			this.lbl_Posture.Location = new System.Drawing.Point(12, 123);
			this.lbl_Posture.Name = "lbl_Posture";
			this.lbl_Posture.Size = new System.Drawing.Size(44, 12);
			this.lbl_Posture.TabIndex = 5;
			this.lbl_Posture.Text = "Posture";
			// 
			// TB_Name
			// 
			this.TB_Name.Location = new System.Drawing.Point(69, 9);
			this.TB_Name.Name = "TB_Name";
			this.TB_Name.Size = new System.Drawing.Size(219, 19);
			this.TB_Name.TabIndex = 6;
			this.TB_Name.TextChanged += new System.EventHandler(this.TB_Name_TextChanged);
			// 
			// CB_Category
			// 
			this.CB_Category.FormattingEnabled = true;
			this.CB_Category.Location = new System.Drawing.Point(69, 83);
			this.CB_Category.Name = "CB_Category";
			this.CB_Category.Size = new System.Drawing.Size(220, 20);
			this.CB_Category.TabIndex = 8;
			this.CB_Category.SelectedIndexChanged += new System.EventHandler(this.CB_Category_SelectedIndexChanged);
			// 
			// CB_Posture
			// 
			this.CB_Posture.FormattingEnabled = true;
			this.CB_Posture.Location = new System.Drawing.Point(69, 120);
			this.CB_Posture.Name = "CB_Posture";
			this.CB_Posture.Size = new System.Drawing.Size(219, 20);
			this.CB_Posture.TabIndex = 9;
			this.CB_Posture.SelectedIndexChanged += new System.EventHandler(this.CB_Posture_SelectedIndexChanged);
			// 
			// CBSL_Next
			// 
			this.CBSL_Next.DispCompend = null;
			this.CBSL_Next.FormattingEnabled = true;
			this.CBSL_Next.Location = new System.Drawing.Point(69, 44);
			this.CBSL_Next.Name = "CBSL_Next";
			this.CBSL_Next.Set = null;
			this.CBSL_Next.Size = new System.Drawing.Size(218, 20);
			this.CBSL_Next.TabIndex = 10;
			// 
			// TBN_Balance
			// 
			this.TBN_Balance.Location = new System.Drawing.Point(69, 157);
			this.TBN_Balance.Name = "TBN_Balance";
			this.TBN_Balance.Size = new System.Drawing.Size(100, 19);
			this.TBN_Balance.TabIndex = 11;
			// 
			// FormAction
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(314, 199);
			this.Controls.Add(this.TBN_Balance);
			this.Controls.Add(this.CBSL_Next);
			this.Controls.Add(this.CB_Posture);
			this.Controls.Add(this.CB_Category);
			this.Controls.Add(this.TB_Name);
			this.Controls.Add(this.lbl_Posture);
			this.Controls.Add(this.lbl_Balance);
			this.Controls.Add(this.lbl_Category);
			this.Controls.Add(this.lbl_Next);
			this.Controls.Add(this.lbl_Name);
			this.Name = "FormAction";
			this.Text = "Action";
			this.VisibleChanged += new System.EventHandler(this.FormAction_VisibleChanged);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion
		private System.Windows.Forms.Label lbl_Name;
		private System.Windows.Forms.Label lbl_Next;
		private System.Windows.Forms.Label lbl_Category;
		private System.Windows.Forms.Label lbl_Balance;
		private System.Windows.Forms.Label lbl_Posture;
		public System.Windows.Forms.TextBox TB_Name;
		public System.Windows.Forms.ComboBox CB_Category;
		public System.Windows.Forms.ComboBox CB_Posture;
		public CB_SequenceList CBSL_Next;
		private TB_Number TBN_Balance;
	}
}