﻿using System.Windows.Forms;
using System.Collections.Generic;


namespace ScriptEditor
{
	//==================================================================================
	//	サブフォーム関連
	//==================================================================================
	public partial class FormMain : Form
	{
		//サブフォーム共通設定
		private List < EditorForm > L_EditorForm = new List<EditorForm> ();

		//==================================================================================
		//	初期化
		//==================================================================================
		private void LoadSubForm ()
		{
			//サブフォーム一覧に登録
			L_EditorForm.Add ( FormAction.Inst );
			L_EditorForm.Add ( Form_ScriptList.Inst );
			L_EditorForm.Add ( FormScript.Inst );
			L_EditorForm.Add ( FormImage.Inst );
			L_EditorForm.Add ( FormRoute.Inst );
			L_EditorForm.Add ( FormRect2.Inst );
			L_EditorForm.Add ( FormEfGnrt.Inst );
			L_EditorForm.Add ( FormPreview.Inst );

			//親を記録
			foreach ( EditorForm ef in L_EditorForm )
			{
				ef.FormMain = this;
			}
		}

		//==================================================================================
		//	環境設定
		//==================================================================================
		private void SetEnvironment_SubForms ( EditCompend ec )
		{
#if false
			//コンペンド(ビヘイビア、ガーニッシュ)の指定
			Form_ScriptList.Inst.SetEnvironment ( ec, chara );
			FormScript.Inst.SetEnvironment ( ec );
			FormImage.Inst.SetEnviron ( ec );			//フォーム：イメージ
			FormRect2.Inst.SetEnvironment ( ec );			//フォーム：レクト
			FormRoute.Inst.SetEnvironment ( ec );
			FormPreview.Inst.SetEnviron ( ec );	//フォーム：プレビュー
#endif
			foreach ( SubForm_Compend subform in L_EditorForm )
			{
				subform.SetEditCompend ( ec );
			}
		}

		//==================================================================================
		//各フォームにおける関連付け (読込時、変更時)
		//==================================================================================
		public void Assosiate ( Sequence sqc, Script scp )
		{
			FormRect2.Inst.Assosiate ( scp );
			FormScript.Inst.Assosiate ( scp, sqc );
			FormEfGnrt.Inst.Assosiate ( scp );
			FormRoute.Inst.Assosiate ( scp );
			Disp ();
		}

		//==================================================================================
		//	サブフォームの明示的表示
		//==================================================================================
		public void ShowSubForms ()
		{
//			FormAction.Inst.Show ();
//			Form_ScriptList.Inst.Show ();
//			FormScript.Inst.Show ();
//			FormEfGnrt.Inst.Show ();
//			FormRect2.Inst.Show ();
//			FormRoute.Inst.Show ();
		}

		public void HideSubForms ()
		{
			FormAction.Inst.Hide ();
			Form_ScriptList.Inst.Hide ();
			FormScript.Inst.Hide ();
			FormEfGnrt.Inst.Hide ();
			FormRect2.Inst.Hide ();
			FormRoute.Inst.Hide ();
			FormPreview.Inst.Hide ();
		}

		//==================================================================================
		//各フォーム終了時
		//==================================================================================
		public void CloseSubForms ()
		{
			//モーダルフォームで開いた子フォームの関連を切る
			FormAction.Inst.Owner = null;
			FormScript.Inst.Owner = null;
		}

	}
}
