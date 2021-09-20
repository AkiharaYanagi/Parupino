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
			this.Cb_Route = new System.Windows.Forms.ComboBox();
			this.SuspendLayout();
			// 
			// Cb_Route
			// 
			this.Cb_Route.FormattingEnabled = true;
			this.Cb_Route.Location = new System.Drawing.Point(270, 59);
			this.Cb_Route.Name = "Cb_Route";
			this.Cb_Route.Size = new System.Drawing.Size(202, 20);
			this.Cb_Route.TabIndex = 0;
			this.Cb_Route.SelectionChangeCommitted += new System.EventHandler(this.Cb_Route_SelectionChangeCommitted);
			// 
			// FormRoute
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(522, 528);
			this.Controls.Add(this.Cb_Route);
			this.Name = "FormRoute";
			this.Text = "FormRoute";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ComboBox Cb_Route;
	}
}