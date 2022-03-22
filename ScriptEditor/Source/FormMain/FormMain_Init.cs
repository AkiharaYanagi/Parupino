using System;
using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//	初期化関連
		//==================================================================================

		private void Init ()
		{
			//キャラデータ設定
			InitChara ();

			//ステータスバーテキストを登録
			STS_TXT.Tssl = 	toolStripStatusLabel1;
			STS_TXT.Trace ( "Init." );

			//タブの選択
			tabAction_Selected ();

			tabControl1.SelectedIndex = ( int ) TAB_NAME.TAB_ACTION;

			//サブフォームの初期表示
//			FormAction.Inst.Show ();
//			FormScript.Inst.Show ();
//			FormEfGnrt.Inst.Show ();
//			FormRect.Inst.Show ();
//			FormBranch.Inst.Show ();
		}
	}
}
