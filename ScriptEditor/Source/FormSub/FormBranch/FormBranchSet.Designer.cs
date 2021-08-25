namespace ScriptEditor
{
	partial class FormBranchSet
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
			this.LB_BranchSet = new System.Windows.Forms.ListBox();
			this.Tb_Name = new System.Windows.Forms.TextBox();
			this.Tb_Remark = new System.Windows.Forms.TextBox();
			this.Lb_Branch = new System.Windows.Forms.ListBox();
			this.SuspendLayout();
			// 
			// LB_BranchSet
			// 
			this.LB_BranchSet.FormattingEnabled = true;
			this.LB_BranchSet.ItemHeight = 12;
			this.LB_BranchSet.Location = new System.Drawing.Point(19, 25);
			this.LB_BranchSet.Name = "LB_BranchSet";
			this.LB_BranchSet.Size = new System.Drawing.Size(113, 388);
			this.LB_BranchSet.TabIndex = 0;
			// 
			// Tb_Name
			// 
			this.Tb_Name.Location = new System.Drawing.Point(173, 25);
			this.Tb_Name.Name = "Tb_Name";
			this.Tb_Name.Size = new System.Drawing.Size(136, 19);
			this.Tb_Name.TabIndex = 1;
			this.Tb_Name.Text = "Name";
			// 
			// Tb_Remark
			// 
			this.Tb_Remark.Location = new System.Drawing.Point(173, 67);
			this.Tb_Remark.Name = "Tb_Remark";
			this.Tb_Remark.Size = new System.Drawing.Size(513, 19);
			this.Tb_Remark.TabIndex = 2;
			this.Tb_Remark.Text = "Remark";
			// 
			// Lb_Branch
			// 
			this.Lb_Branch.FormattingEnabled = true;
			this.Lb_Branch.ItemHeight = 12;
			this.Lb_Branch.Location = new System.Drawing.Point(173, 113);
			this.Lb_Branch.Name = "Lb_Branch";
			this.Lb_Branch.Size = new System.Drawing.Size(401, 292);
			this.Lb_Branch.TabIndex = 3;
			// 
			// FormBranchSet
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.Lb_Branch);
			this.Controls.Add(this.Tb_Remark);
			this.Controls.Add(this.Tb_Name);
			this.Controls.Add(this.LB_BranchSet);
			this.Name = "FormBranchSet";
			this.Text = "FormBranchSet";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ListBox LB_BranchSet;
		private System.Windows.Forms.TextBox Tb_Name;
		private System.Windows.Forms.TextBox Tb_Remark;
		private System.Windows.Forms.ListBox Lb_Branch;
	}
}