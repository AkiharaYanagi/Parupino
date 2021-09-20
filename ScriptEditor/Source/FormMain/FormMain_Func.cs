using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//各コントロールのデータソースにキャラデータを設定する (読込時に１回のみ)
		//==================================================================================
		public void SetCharaData ( Chara ch )
		{
			//編集
			EditChara.Inst.SetCharaDara ( ch );
			//表示
			DispChara.Inst.SetCharaData ( ch );

			//コントロール
			cpd_Behavior.SetCharaData ( ch );
			cpd_Garnish.SetCharaData ( ch );

			//----------------------------------------------
			//コマンド
			ctrl_CmdList1.SetCharaData ( ch );

			//ブランチ
			ctrl_Branch1.SetCharaData ( ch );

			//ルート
			ctrl_Route1.SetCharaData ( ch );

			//----------------------------------------------
			// [エフェクトジェネレートフォーム]
			FormEfGnrt.Inst.SetCharaData ( ch );

			//フォーム ルート
			FormRoute.Inst.SetCharaData ( ch );
			
			//----------------------------------------------
			// [メインフォーム] キャラ内容表示
			UpdateData ();
		}

		//==================================================================================
		//各フォームに更新を伝える (読込時、変更時)
		//==================================================================================
		public void Assosiate ( Script scp )
		{
			FormRect.Inst.Assosiate ( scp );
			FormScript.Inst.Assosiate ( scp );
			FormEfGnrt.Inst.Assosiate ( scp );
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
