using System;
using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//	キャラ読込
		//==================================================================================
		private void InitChara ()
		{
			//キャラ：空データ
			SetCharaData ( chara );

			//キャラ：テストデータ
//			TestCharaData ();

			//キャラ：既存データ自動読込
//			CharaLoad ();
		}


		//既存のキャラデータ読込
		private void CharaLoad ()
		{
			//読込
			LoadChara loadChara = new LoadChara ( stgs.LastFilename, chara );

			//保存先
			SetFormText ( stgs.LastFilename );

			//キャラデータの適用
			SetCharaData ( chara );
		}

		//==================================================================================
		//各コントロールのデータソースにキャラデータを設定する (読込時に１回のみ)
		//==================================================================================
		public void SetCharaData ( Chara ch )
		{
			//----------------------------------------------
			EditChara.Inst.SetCharaDara ( ch );			//編集
			DispChara.Inst.SetCharaData ( ch );			//表示

			//----------------------------------------------
			ctrl_SqcList_Act.SetCharaData ( ch.behavior );			//シークエンス
			ctrl_SqcList_Ef.SetCharaData ( ch.garnish );			//シークエンス

			//----------------------------------------------
			cpd_Behavior.SetCharaData ( ch );			//コンペンド
			cpd_Garnish.SetCharaData ( ch );

			//----------------------------------------------
			ctrl_CmdList1.SetCharaData ( ch );			//コマンド
			ctrl_Branch1.SetCharaData ( ch );			//ブランチ
			ctrl_Route1.SetCharaData ( ch );			//ルート

			//----------------------------------------------
			FormEfGnrt.Inst.SetCharaData ( ch );			// [エフェクトジェネレートフォーム]
			FormRoute.Inst.SetCharaData ( ch );			//フォーム ルート

			//----------------------------------------------
			UpdateData ();			// [メインフォーム] キャラ内容表示
		}

	}
}
