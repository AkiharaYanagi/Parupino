using System.Windows.Forms;

namespace ScriptEditor
{
	//==================================================================================
	//	サブフォーム関連
	//==================================================================================
	public partial class FormMain : Form
	{
		//==================================================================================
		//	初期化
		//==================================================================================
		private void LoadSubForm ()
		{
			FormAction.Inst.FormMain = this;
			Form_ScriptList.Inst.FormMain = this;
			FormScript.Inst.FormMain = this;
			FormImage.Inst.FormMain = this;
			FormRoute.Inst.FormMain = this;
			FormRect2.Inst.FormMain = this;
			FormEfGnrt.Inst.FormMain = this;
			FormRoute.Inst.FormMain = this;
		}

		//==================================================================================
		//	環境設定
		//==================================================================================
		private void SetEnvironmentSubForms ()
		{
			//ビヘイビア(:コンペンド)の指定
			EditBehavior eb = EditChara.Inst.EditBehavior;
			DispBehavior db = DispChara.Inst.DispBehavior;

			FormAction.Inst.SetCtrl ( eb.EditAction, db.DispAction, db );	//フォーム：アクション
			Form_ScriptList.Inst.SetEnvironment ( eb, chara );
			FormImage.Inst.SetEnviron ( eb, db );			//フォーム：イメージ
			FormRect2.Inst.SetEnvironment ( eb );			//フォーム：レクト
			FormPreview.Inst.SetEnviron ( this, eb );	//フォーム：プレビュー
			FormRoute.Inst.SetEnvironment ( eb );
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
//			FormRect.Inst.Show ();
//			FormBranch.Inst.Show ();
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
