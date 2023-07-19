using System.Windows.Forms;
using System.IO;


namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//コントロール統合処理
		private Ctrl_All ctrl_all = new Ctrl_All ();

		//シークエンスリスト・アクション
		Ctrl_SqcList ctrl_SqcList_Act = new Ctrl_SqcList ();

		//コントロール・ビヘイビア
		_Ctrl_Compend ctrl_cmpd_bhv = new _Ctrl_Compend ();

		//シークエンスリスト・エフェクト
		Ctrl_SqcList ctrl_SqcList_Efc = new Ctrl_SqcList ();

		//コントロール・ガーニッシュ
		_Ctrl_Compend ctrl_cmpd_gns = new _Ctrl_Compend ();


		//==================================================================================
		//	環境初期化
		//==================================================================================
		private void LoadEnvironment ()
		{
			//コントロール初期化
			ctrl_all.SetCtrl ( ctrl_SqcList_Act, ctrl_cmpd_bhv, ctrl_SqcList_Ef, ctrl_cmpd_gns );

			LoadSetting ();		//設定ファイル初期化
			LoadSubForm ();		//サブフォーム初期化
			LoadTab ();			//タブ初期化
		}

		//---------------------------------------------------------------------
		//	設定ファイル初期化
		//---------------------------------------------------------------------
		private void LoadSetting ()
		{
			//設定ファイル読込
			XML_IO.SettingFilepath = Directory.GetCurrentDirectory () + "\\setting.xml";
			stgs = (Ctrl_Settings) XML_IO.Load ( stgs.GetType () );
			SetFormText ( stgs.LastFilepath );
		}

		//---------------------------------------------------------------------
		//	タブ初期化関連
		//---------------------------------------------------------------------

		//各タブの初期化
		private void LoadTab ()
		{
			TabAction_Load ();
			TabScript_A_Load ();
			TabEffect_Load ();
			TabScript_E_Load ();
			TabCommand_Load ();
			TabBranch_Load ();
			TabRoute_Load ();
		}
		//--------------------------------------------------------------------------

		//タブ_アクションの初期化
		private void TabAction_Load ()
		{
			tabControl1.TabPages[0].Controls.Add ( ctrl_SqcList_Act );

			Ctrl_SqcList.CTRL_SQC act = Ctrl_SqcList.CTRL_SQC.ACTION;
			ctrl_SqcList_Act.SetEnviroment ( act, ()=>new Action(), stgs );
			ctrl_SqcList_Act.SetCharaData ( chara.behavior );
			ctrl_SqcList_Act.LoadCtrl ();
		}

		//タブ_スクリプト(Act)の初期化
		private void TabScript_A_Load ()
		{
			//ビヘイビア(:コンペンド)の指定
			EditBehavior eb = EditChara.Inst.EditBehavior;
			DispBehavior db = DispChara.Inst.DispBehavior;

//			db.SetCtrl ( eb, ctrl_cmpd_bhv );    //表示

//			cpd_Behavior.SetEnviron ( eb, db );	//ビヘイビア(:コンペンド)初期化
//			cpd_Behavior.SetBehavior ();
			ctrl_cmpd_bhv.SetEnviron ( eb );

			//サブフォームにおける環境設定
			SetEnvironmentSubForms ( eb, db );

			//アクションのみ
			FormAction.Inst.SetCtrl ( eb.EditAction, db.DispAction, db );
		}

		//タブ_エフェクトの初期化
		private void TabEffect_Load ()
		{
			Ctrl_SqcList.CTRL_SQC ef = Ctrl_SqcList.CTRL_SQC.EFFECT;
			ctrl_SqcList_Ef.SetEnviroment ( ef, ()=>new Effect(), stgs );
			ctrl_SqcList_Ef.SetCharaData ( chara.garnish );
			ctrl_SqcList_Ef.LoadCtrl ();
		}

		//タブ_スクリプト(Ef)の初期化
		private void TabScript_E_Load ()
		{
			//ガーニッシュ(:コンペンド)の指定
			EditGarnish eg = EditChara.Inst.EditGarnish;
			DispGarnish dg = DispChara.Inst.DispGarnish;

//			dg.SetCtrl ( eg, cpd_Garnish );	//表示

//			cpd_Garnish.SetEnviron ( eg, dg );	//ガーニッシュ(:コンペンド)初期化
//			cpd_Garnish.SetGarnish ();
	
			//サブフォームの初期化
			Form_ScriptList.Inst.SetEnvironment ( eg, chara );
			FormImage.Inst.SetEnviron ( eg, dg );
			FormRect2.Inst.SetEnvironment ( eg, dg );
		}

		//タブ_コマンドの初期化
		private void TabCommand_Load ()
		{
			ctrl_CmdList1.SetEnvironment ( stgs );
		}

		//タブ_ブランチの初期化
		private void TabBranch_Load ()
		{
			ctrl_Branch1.SetEnvironment ( stgs );
			ctrl_Branch1.SetCharaData ( chara );
		}

		//タブ_ルートの初期化
		private void TabRoute_Load ()
		{
			ctrl_Route1.SetEnvironment ( stgs );
		}
	}
}
