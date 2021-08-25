namespace ScriptEditor.Source.FormSub.FormBranch
{
	partial class FormBranch0
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
			this.Lb_Branch = new System.Windows.Forms.ListBox();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.Cb_Action = new System.Windows.Forms.ComboBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.Cb_Command = new System.Windows.Forms.ComboBox();
			this.SuspendLayout();
			// 
			// Lb_Branch
			// 
			this.Lb_Branch.FormattingEnabled = true;
			this.Lb_Branch.ItemHeight = 12;
			this.Lb_Branch.Location = new System.Drawing.Point(12, 12);
			this.Lb_Branch.Name = "Lb_Branch";
			this.Lb_Branch.Size = new System.Drawing.Size(154, 160);
			this.Lb_Branch.TabIndex = 0;
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(183, 12);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(199, 19);
			this.textBox1.TabIndex = 1;
			this.textBox1.Text = "Name";
			// 
			// Cb_Action
			// 
			this.Cb_Action.FormattingEnabled = true;
			this.Cb_Action.Location = new System.Drawing.Point(394, 65);
			this.Cb_Action.Name = "Cb_Action";
			this.Cb_Action.Size = new System.Drawing.Size(199, 20);
			this.Cb_Action.TabIndex = 3;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(181, 48);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(55, 12);
			this.label1.TabIndex = 4;
			this.label1.Text = "Command";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(392, 48);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(38, 12);
			this.label2.TabIndex = 5;
			this.label2.Text = "Action";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(371, 68);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(17, 12);
			this.label3.TabIndex = 6;
			this.label3.Text = "→";
			// 
			// Cb_Command
			// 
			this.Cb_Command.FormattingEnabled = true;
			this.Cb_Command.Location = new System.Drawing.Point(183, 65);
			this.Cb_Command.Name = "Cb_Command";
			this.Cb_Command.Size = new System.Drawing.Size(182, 20);
			this.Cb_Command.TabIndex = 2;
			// 
			// FormBranch0
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(611, 183);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.Cb_Action);
			this.Controls.Add(this.Cb_Command);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.Lb_Branch);
			this.Name = "FormBranch0";
			this.Text = "FormBranch0";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ListBox Lb_Branch;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.ComboBox Cb_Action;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.ComboBox Cb_Command;
	}
}