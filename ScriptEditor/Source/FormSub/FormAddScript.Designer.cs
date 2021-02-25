namespace ScriptEditor.FormSub
{
	partial class FormAddScript
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
			this.label1 = new System.Windows.Forms.Label();
			this.tB_Number1 = new ScriptEditor.TB_Number();
			this.button1 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(9, 12);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(72, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "追加する個数";
			// 
			// tB_Number1
			// 
			this.tB_Number1.dispCompend = null;
			this.tB_Number1.editCompend = null;
			this.tB_Number1.Location = new System.Drawing.Point(96, 8);
			this.tB_Number1.Name = "tB_Number1";
			this.tB_Number1.refInt = null;
			this.tB_Number1.scriptAddress = null;
			this.tB_Number1.SetFunc = null;
			this.tB_Number1.Size = new System.Drawing.Size(121, 19);
			this.tB_Number1.TabIndex = 1;
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(12, 36);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(204, 23);
			this.button1.TabIndex = 2;
			this.button1.Text = "OK";
			this.button1.UseVisualStyleBackColor = true;
			// 
			// FormAddScript
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(228, 65);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.tB_Number1);
			this.Controls.Add(this.label1);
			this.Name = "FormAddScript";
			this.Text = "スクリプトの追加";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private TB_Number tB_Number1;
		private System.Windows.Forms.Button button1;
	}
}