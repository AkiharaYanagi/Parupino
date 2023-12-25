using System.Windows.Forms;
using System.Collections.Generic;


namespace ScriptEditor
{
	//==================================================================================
	//	サブフォーム関連
	//==================================================================================
	public partial class FormMain : Form
	{
		//サブフォーム共通設定
		private List < EditorSubForm > L_EditorForm = new List < EditorSubForm > ();

		//==================================================================================
		//	初期化
		//==================================================================================
		private void LoadSubForm ()
		{
			//サブフォーム一覧に登録
//			L_EditorForm.Add ( FormAction.Inst );
			L_EditorForm.Add ( Form_ScriptList.Inst );
			L_EditorForm.Add ( FormScript.Inst );
			L_EditorForm.Add ( FormImage.Inst );
			L_EditorForm.Add ( FormRoute.Inst );
			L_EditorForm.Add ( FormRect2.Inst );
//			L_EditorForm.Add ( FormEfGnrt.Inst );
			L_EditorForm.Add ( _FormEfGnrt.Inst );
			L_EditorForm.Add ( FormPreview.Inst );

			//親を記録
			foreach ( EditorSubForm ef in L_EditorForm )
			{
				ef.FormMain = this;
			}
		}

		//==================================================================================
		//	環境設定
		//==================================================================================
		//コンペンドの指定
		//	タブ切替(ビヘイビア、ガーニッシュ)時に毎回指定する
		private void SetEnvironment_SubForms ( EditCompend ec )
		{
			foreach ( SubForm_Compend subform in L_EditorForm )
			{
				subform.SetEditCompend ( ec );
			}
		}

		//==================================================================================
		//各フォームにおける関連付け (読込時、変更時)
		//==================================================================================
		// -> All_ctrlに統合
#if false

		public void Assosiate ( Sequence sqc, Script scp )
		{
			FormRect2.Inst.Assosiate ( scp );
			FormScript.Inst.Assosiate ( scp, sqc );
			FormEfGnrt.Inst.Assosiate ( scp );
			FormRoute.Inst.Assosiate ( scp );
			Disp ();
		}
#endif

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
//			FormAction.Inst.Hide ();
			Form_ScriptList.Inst.Hide ();
			FormScript.Inst.Hide ();
			FormRect2.Inst.Hide ();
			FormRoute.Inst.Hide ();
			_FormEfGnrt.Inst.Hide ();
			FormPreview.Inst.Hide ();
		}

		//==================================================================================
		//各フォーム終了時
		//==================================================================================
		public void CloseSubForms ()
		{
			//モーダルフォームで開いた子フォームの関連を切る
//			FormAction.Inst.Owner = null;
//			FormScript.Inst.Owner = null;
		}

	}
}
