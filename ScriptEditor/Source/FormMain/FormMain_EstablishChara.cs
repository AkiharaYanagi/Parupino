using System;
using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//	キャラ初期設定(の選択)
		//==================================================================================
		private void EstablishChara ()
		{
			//-------------------------------
			//@info 下記いずれかを環境で選ぶ
			//-------------------------------

#if false
			//キャラ：空データ
			SetCharaData ( chara );

			//キャラ：テストデータ
			TestCharaData ();

			//個別データから作成
			LoadPreData ();
#endif

			//自動で既存のキャラデータを読込
			_LoadChara ( stgs.LastFilepath );
		}

		//プレデータテキストファイルから既存データの読込
		public void LoadPreData ()
		{
			ctrl_SqcList_Act.LoadData ();
			ctrl_SqcList_Ef.LoadData ();
			ctrl_CmdList1.LoadData ();
			ctrl_Branch1.LoadData ();
			ctrl_Route1.LoadData ();
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
