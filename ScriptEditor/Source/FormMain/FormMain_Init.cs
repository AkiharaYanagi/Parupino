using System;
using System.Windows.Forms;
using System.Drawing;
using System.IO;

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
			FormBranch.Inst.FormMain = this;
		}

		//--------------------------------------------------------------------------
		//タイトルバー
		private string formText = "ScriptEditor";		//フォームテキスト(タイトル)

		private void InitFormText ()
		{
			this.Text = formText;
		}
		private void SetFormText ( string fileName )
		{
			this.Text = fileName + " - " + formText;
		}
		private void NoSaveFormText ( string fileName )
		{
			this.Text = fileName + "*" + " - " + formText;
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

				//既存のとき書出しない
				if ( ! File.Exists ( edittingFilename ) )
				{
					//書出
					SaveChara saveChara = new SaveChara ( edittingFilename, testCharaData );
				}

				//読込
				LoadChara loadChara = new LoadChara ( edittingFilename, chara );

				//フォームテキストの更新
				SetFormText ( edittingFilename );

				//@todo ImageNameが"0"になる問題を修正
		
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
		//	各タブの初期化
		//==================================================================================
		//タブ_アクションの初期化
		private void TabAction_Load ()
		{
			//ビヘイビア(:コンペンド)の指定
			EditBehavior eb = EditChara.Inst.EditBehavior;
			DispBehavior db = DispChara.Inst.DispBehavior;

//			eb.SetCtrl ( cpd_Behavior );		//編集
			db.SetCtrl ( eb, cpd_Behavior );    //表示

			cpd_Behavior.SetCtrl ( eb );	//ビヘイビア(:コンペンド)初期化
			cpd_Behavior.SetBehavior ();

			//フォーム：イメージの初期化
//			FormImage.Inst.SetTarget ( eb.Compend.ListImage.GetBindingList () );

			//フォーム：アクションの初期化
			FormAction.Inst.SetCtrl ( eb.EditAction, db.DispAction, db );

			//フォーム：スクリプトの初期化
			FormScript.Inst.SetCtrl ( eb.EditScript, db.DispScript );

			//フォーム：レクトの初期化
			FormRect.Inst.SetCtrl ( eb.EditScript );
		}

		//タブ_エフェクトの初期化
		private void TabEffect_Load ()
		{
			//ガーニッシュ(:コンペンド)の指定
			EditGarnish eg = EditChara.Inst.EditGarnish;
			DispGarnish dg = DispChara.Inst.DispGarnish;

//			eg.SetCtrl ( cpd_Garnish );		//編集
			dg.SetCtrl ( eg, cpd_Garnish );	//表示

			cpd_Garnish.SetCtrl ( eg );	//ビヘイビア(:コンペンド)初期化
			cpd_Garnish.SetGarnish ();
	
			//フォーム：スクリプトの初期化
			FormScript.Inst.SetCtrl ( eg.EditScript, dg.DispScript );

			//フォーム：レクトの初期化
			FormRect.Inst.SetCtrl ( eg.EditScript );
		}

		//タブ_コマンドの初期化
		private void TabCommand_Load ()
		{
			listCommand1.SetData ( chara.ListCommand, ctrl_Command1 );
			Command c = listCommand1.GetSelected ();
			if ( null == c ) { return; }
			ctrl_Command1.Set ( c );
		}

		//タブ_キャラの初期化
		private void TabChara_Load ()
		{
			Ctrl_ListBox < Sequence > ctrl_testlistbox = new Ctrl_ListBox < Sequence > ();
			this.tabChara.Controls.Add ( ctrl_testlistbox );
		}

		//==================================================================================
		//	開始
		//==================================================================================
		private void Init ()
		{
			//キャラデータの適用
			SetCharaData ( chara );

			//タブの選択
			tabAction_Selected ();
			FormAction.Inst.Show ();
			FormScript.Inst.Show ();
			FormEfGnrt.Inst.Show ();
			FormRect.Inst.Show ();
			FormBranch.Inst.Show ();
		}
	}
}
