using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class Ctrl_Compend : UserControl
	{
		public Ctrl_Compend ()
		{
			InitializeComponent ();
		}

		public void Set ( Sequence sqc )
		{
			listBox1.Items.Add ( sqc );
			listBox1.SelectedIndex = ( listBox1.Items.Count - 1 );

			sqcBoard1.Set ( sqc );
		}


#if false

		private void pictureBox1_Paint ( object sender, PaintEventArgs e )
		{
			Graphics g = e.Graphics;
			Rectangle r0 = new Rectangle ( 0, 0, 200, 40 );
			Rectangle r1 = new Rectangle ( 0, 50, 200, 40 );

			LinearGradientBrush lgBrush = new LinearGradientBrush ( r0, Color.Red, Color.Green, LinearGradientMode.Horizontal );
			g.FillRectangle ( lgBrush, r0 );
			lgBrush.GammaCorrection = true;
			g.FillRectangle ( lgBrush, r1 );
		}
#endif
	}
}
