using System;
using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//	環境初期化
		//==================================================================================
		private void LoadEnvironment ()
		{
			//サブフォーム初期化
			LoadSubForm ();

			//タブ初期化
			LoadTab ();
		}

		//==================================================================================
		//	タブ初期化関連
		//==================================================================================

		//--------------------------------------------------------------------------
		//各タブの初期化
		private void LoadTab ()
		{
			TabAction_Load ();
			TabScript_Load ();
			TabEffect_Load ();
			TabCommand_Load ();
			TabBranch_Load ();
			TabChara_Load ();
		}

		//タブ_アクションの初期化
		private void TabAction_Load ()
		{
			ctrl_SqcList1.LoadCtrl ();
			ctrl_SqcList1.SetEnviroment ( ()=>new Action() );
			ctrl_SqcList1.SetData ( chara.behavior );
		}

		//タブ_スクリプトの初期化
		private void TabScript_Load ()
		{
			//ビヘイビア(:コンペンド)の指定
			EditBehavior eb = EditChara.Inst.EditBehavior;
			DispBehavior db = DispChara.Inst.DispBehavior;

			db.SetCtrl ( eb, cpd_Behavior );    //表示

			cpd_Behavior.SetEnviron ( eb, db );	//ビヘイビア(:コンペンド)初期化
			cpd_Behavior.SetBehavior ();

			//サブフォームの初期化
			FormImage.Inst.SetEnviron ( this, eb, db );			//フォーム：イメージ
			FormAction.Inst.SetCtrl ( eb.EditAction, db.DispAction, db );	//フォーム：アクション
			FormScript.Inst.SetCtrl ( eb.EditScript, db.DispScript );	//フォーム：スクリプト
			FormRect.Inst.SetCtrl ( eb.EditScript );			//フォーム：レクト
			FormPreview.Inst.SetEnviron ( this, eb );	//フォーム：プレビュー
		}

		//タブ_エフェクトの初期化
		private void TabEffect_Load ()
		{
			//ガーニッシュ(:コンペンド)の指定
			EditGarnish eg = EditChara.Inst.EditGarnish;
			DispGarnish dg = DispChara.Inst.DispGarnish;

			dg.SetCtrl ( eg, cpd_Garnish );	//表示

			cpd_Garnish.SetEnviron ( eg, dg );	//ビヘイビア(:コンペンド)初期化
			cpd_Garnish.SetGarnish ();
	
			//サブフォームの初期化
			FormImage.Inst.SetEnviron ( this, eg, dg );
			FormScript.Inst.SetCtrl ( eg.EditScript, dg.DispScript );
			FormRect.Inst.SetCtrl ( eg.EditScript );
		}

		//タブ_コマンドの初期化
		private void TabCommand_Load ()
		{
		}

		//タブ_ブランチの初期化
		private void TabBranch_Load ()
		{
		}

		//タブ_キャラの初期化
		private void TabChara_Load ()
		{
		}

		//--------------------------------------------------------------------------
		//サブフォーム関連
		private void LoadSubForm ()
		{
			FormImage.Inst.FormMain = this;
			FormAction.Inst.FormMain = this;
			FormScript.Inst.FormMain = this;
			FormRect.Inst.FormMain = this;
			FormEfGnrt.Inst.FormMain = this;
			FormRoute.Inst.FormMain = this;
		}

	}
}
