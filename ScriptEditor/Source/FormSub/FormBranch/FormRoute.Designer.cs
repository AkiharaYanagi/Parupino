namespace ScriptEditor
{
	partial class FormRoute
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
			this.ctrl_Route1 = new ScriptEditor.Ctrl_Route();
			this.SuspendLayout();
			// 
			// ctrl_Route1
			// 
			this.ctrl_Route1.Location = new System.Drawing.Point(9, 5);
			this.ctrl_Route1.Name = "ctrl_Route1";
			this.ctrl_Route1.Size = new System.Drawing.Size(893, 553);
			this.ctrl_Route1.TabIndex = 0;
			// 
			// FormRoute
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 548);
			this.Controls.Add(this.ctrl_Route1);
			this.Name = "FormRoute";
			this.Text = "FormRoute";
			this.ResumeLayout(false);

		}

		#endregion

		private Ctrl_Route ctrl_Route1;
	}
}