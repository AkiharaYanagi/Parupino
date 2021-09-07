namespace ScriptEditor
{
	partial class FormScript
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
			this.ctrl_Script1 = new ScriptEditor.Ctrl_Script();
			this.SuspendLayout();
			// 
			// ctrl_Script1
			// 
			this.ctrl_Script1.Location = new System.Drawing.Point(1, 0);
			this.ctrl_Script1.Margin = new System.Windows.Forms.Padding(1);
			this.ctrl_Script1.Name = "ctrl_Script1";
			this.ctrl_Script1.Size = new System.Drawing.Size(345, 348);
			this.ctrl_Script1.TabIndex = 0;
			// 
			// FormScript
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(344, 358);
			this.Controls.Add(this.ctrl_Script1);
			this.Name = "FormScript";
			this.Text = "Script";
			this.ResumeLayout(false);

		}

		#endregion

		public Ctrl_Script ctrl_Script1;
	}
}