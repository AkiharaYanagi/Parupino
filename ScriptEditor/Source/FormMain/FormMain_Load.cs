using System.Windows.Forms;
using System.IO;


namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//	環境初期化
		//==================================================================================
		private void LoadEnvironment ()
		{
			LoadSetting ();		//設定ファイル初期化
			LoadCtrl ();		//コントロール初期化
			LoadTab ();			//タブ初期化
			LoadSubForm ();		//サブフォーム初期化
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
			//タブページに手動追加
			TabPage tp = tabControl1.TabPages [ (int)TAB_NAME.TAB_ACTION ];
			tp.Controls.Add ( ctrl_SqcList_Act );
		}

		//タブ_スクリプト(Act)の初期化
		private void TabScript_A_Load ()
		{
#if false
			//ビヘイビア(:コンペンド)の指定
			EditBehavior eb = EditChara.Inst.EditBehavior;

			//タブページに手動追加
			TabPage tp = tabControl1.TabPages[1];
			tp.SuspendLayout ();

			tp.Controls.Add ( ctrl_cmpd_bhv );
			ctrl_cmpd_bhv.SetEnviron ( eb );
			ctrl_cmpd_bhv.Location = new Point ( 0, 0 );
			ctrl_cmpd_bhv.Size = new Size ( tp.Size.Width - ctrl_fmBtn_gns.Width, tp.Size.Height );

			tp.Controls.Add ( ctrl_fmBtn_bhv );
			ctrl_fmBtn_bhv.Location = new Point ( ctrl_cmpd_bhv.Width, 0 );

			tp.ResumeLayout ( false );

			//サブフォームにおける環境設定
			SetEnvironment_SubForms ( eb );

			//アクションのみ
//			FormAction.Inst.SetCtrl ( eb.EditAction, db.DispAction, db );
#endif
		}

		//タブ_エフェクトの初期化
		private void TabEffect_Load ()
		{
#if false
			//タブページに手動追加
			Ctrl_SqcList.CTRL_SQC ef = Ctrl_SqcList.CTRL_SQC.EFFECT;
			ctrl_SqcList_Ef.SetEnviroment ( ef, ()=>new Effect(), stgs );
			ctrl_SqcList_Ef.SetCharaData ( chara.garnish );
			//ctrl_SqcList_Ef.LoadCtrl ();
#endif
		}

		//タブ_スクリプト(Ef)の初期化
		private void TabScript_E_Load ()
		{
#if false
			//ガーニッシュ(:コンペンド)の指定
			EditGarnish eg = EditChara.Inst.EditGarnish;
			DispGarnish dg = DispChara.Inst.DispGarnish;

			//タブページに手動追加
			TabPage tp = tabControl1.TabPages[3];
			tp.SuspendLayout ();

			tp.Controls.Add ( ctrl_cmpd_gns );
			ctrl_cmpd_gns.SetEnviron ( eg );
			ctrl_cmpd_gns.Location = new Point ( 0, 0 ); 
			ctrl_cmpd_gns.Size = new Size ( tp.Size.Width - ctrl_fmBtn_gns.Width, tp.Size.Height );
			
			tp.Controls.Add ( ctrl_fmBtn_gns );
			ctrl_fmBtn_gns.Location = new Point ( ctrl_cmpd_gns.Width, 0 );

			tp.ResumeLayout ();

	
			//サブフォームの初期化
			SetEnvironment_SubForms ( eg );
//			Form_ScriptList.Inst.SetEnvironment ( eg );
//			FormImage.Inst.SetEnviron ( eg );
//			FormRect2.Inst.SetEnvironment ( eg );
#endif
		}

		//タブ_コマンドの初期化
		private void TabCommand_Load ()
		{
			//タブページに手動追加
			TabPage tp = tabControl1.TabPages [ (int)TAB_NAME.TAB_COMMAND ];
			tp.Controls.Add ( ctrl_Cmd );
		}

		//タブ_ブランチの初期化
		private void TabBranch_Load ()
		{
			//タブページに手動追加
			TabPage tp = tabControl1.TabPages [ (int)TAB_NAME.TAB_BRANCH ];
			tp.Controls.Add ( ctrl_Brc );
		}

		//タブ_ルートの初期化
		private void TabRoute_Load ()
		{
			//タブページに手動追加
			TabPage tp = tabControl1.TabPages [ (int)TAB_NAME.TAB_ROUTE ];
			tp.Controls.Add ( ctrl_Rut );
		}
	}
}
