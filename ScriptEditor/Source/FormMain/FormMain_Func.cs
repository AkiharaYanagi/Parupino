using System.Windows.Forms;
using System.IO;

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

		//タイトルバーテキスト更新
		private void ReloadTitleBarText ()
		{
			this.Text = Directory.GetCurrentDirectory() + "\\" + stgs.LastFilepath + " - " + formText;
		}
	}
}
