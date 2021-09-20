using System;
using System.Windows.Forms;
using System.IO;
using System.Drawing;


namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//	初期化関連
		//==================================================================================

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

		//==================================================================================
		//	テスト：キャラデータ
		//==================================================================================
		public void TestCharaData ()
		{
			//ファイル名指定
			edittingFilename = "testChara.dat";

			//キャラのテストデータの作成・書出・読込の動作確認
			try
			{
				//テスト用キャラの作成
				Chara testCharaData = new Chara ();

				//テストオブジェクトによる機能のテスト
				TestChara testChara = new TestChara ();
				testChara.Test ( testCharaData );

				//イメージファイル読込のテスト
#if true
				testCharaData.behavior.BD_Image.Clear ();
				string tsetImageDir = "TestImage";
				string[] files = Directory.GetFiles ( tsetImageDir );
				foreach ( string filename in files )
				{
					string f = Path.GetFileName ( filename );
					string fn = f.Substring ( 4 );	//先頭のインデックス("ddd_")を除く

					//画像からImageData型を作成
					ImageData imageData = new ImageData ( fn, Image.FromFile ( filename ) );

					//追加
					testCharaData.behavior.BD_Image.Add ( imageData );
				}
#endif

#if true
				//書出
				SaveChara saveChara = new SaveChara ( edittingFilename, testCharaData );
#else
				//既存のとき書出しない
				if ( ! File.Exists ( edittingFilename ) )
				{
					//書出
					SaveChara saveChara = new SaveChara ( edittingFilename, testCharaData );
				}

#endif
				//読込
				LoadChara loadChara = new LoadChara ( edittingFilename, chara );

				//フォームテキストの更新
				SetFormText ( edittingFilename );
		
				//テストデータからキャラ作成ソースファイルを作成
//				MakeTestCharaData mtcd = new MakeTestCharaData ( chara );

				//キャラデータの適用
				SetCharaData ( chara );
			}
			catch ( ArgumentException e )
			{
				MessageBox.Show ( "TestCharaData\n" + e.Message );
			}
		}

		//==================================================================================
		//	タブ初期化関連
		//==================================================================================

		//--------------------------------------------------------------------------
		//各タブの初期化
		private void LoadTab ()
		{
			TabAction_Load ();
			TabEffect_Load ();
			TabCommand_Load ();
			TabBranch_Load ();
			TabChara_Load ();
		}

		//タブ_アクションの初期化
		private void TabAction_Load ()
		{
			//ビヘイビア(:コンペンド)の指定
			EditBehavior eb = EditChara.Inst.EditBehavior;
			DispBehavior db = DispChara.Inst.DispBehavior;

			db.SetCtrl ( eb, cpd_Behavior );    //表示

			cpd_Behavior.SetEnviron ( eb, db );	//ビヘイビア(:コンペンド)初期化
			cpd_Behavior.SetBehavior ();

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
	
			//フォーム：スクリプトの初期化
			FormScript.Inst.SetCtrl ( eg.EditScript, dg.DispScript );

			//フォーム：レクトの初期化
			FormRect.Inst.SetCtrl ( eg.EditScript );
		}

		//タブ_コマンドの初期化
		private void TabCommand_Load ()
		{
#if false
			listCommand1.SetData ( chara.BD_Command.GetBindingList (), ctrl_Command1 );
			Command c = listCommand1.GetSelected ();
			if ( null == c ) { return; }
			ctrl_Command1.Set ( c );
#endif
		}

		//タブ_ブランチの初期化
		private void TabBranch_Load ()
		{

		}

		//タブ_キャラの初期化
		private void TabChara_Load ()
		{
		}

		//==================================================================================
		//	開始
		//==================================================================================
		private void Init ()
		{
			//ステータスバーテキストを登録
			STS_TXT.Tssl = 	toolStripStatusLabel1;
			STS_TXT.Trace ( "Init." );

			//キャラデータの適用
			SetCharaData ( chara );

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
