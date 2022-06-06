using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		public void UpdateData ()
		{
			Disp ();
		}

		//==================================================================================
		//表示
		//==================================================================================
		//手動
		private void Disp ()
		{
			DispChara.Inst.Disp ();
		}
		//イベント
		private void FormMain_Paint ( object sender, PaintEventArgs e )
		{
//			DispChara.Inst.Disp ();
		}
	}
}
