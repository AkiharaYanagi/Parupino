using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//各フォームに更新を伝える (読込時、変更時)
		//==================================================================================
		public void Assosiate ( Sequence sqc, Script scp )
		{
//			FormRect.Inst.Assosiate ( scp );
			FormRect2.Inst.Assosiate ( scp );
			FormScript.Inst.Assosiate ( scp, sqc );
			FormEfGnrt.Inst.Assosiate ( scp );
			FormRoute.Inst.Assosiate ( scp );
			Disp ();
		}

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
