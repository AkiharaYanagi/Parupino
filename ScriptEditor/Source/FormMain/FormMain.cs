using System.Windows.Forms;

namespace ScriptEditor
{
	//@todo アクション指定に名前から検索する機能を付ける
	//@todo ブランチにセットを作り、名前から検索する機能を付ける

	//#################################################################################
	//##
	//##	メインフォーム
	//##
	//#################################################################################
	public partial class FormMain : Form
	{
		//==================================================================================
		//	メンバ変数
		//==================================================================================
		//編集対象キャラクタ
		private Chara chara = new Chara ();

		private string edittingFilename = "chara.dat";	//編集中のファイル名
		private Settings settings = new Settings();		//スクリプトエディタ自身の設定ファイル

		//==================================================================================
		//	コンストラクタ
		//==================================================================================
		public FormMain ()
		{
			//フォーム開始位置をマウス位置にする
			InitPosition ();

			//コンポーネントの初期化
			InitializeComponent ();

			//サブフォーム初期化
			LoadSubForm ();

			//ステータスバーテキストを登録
			STS_TXT.Tssl = 	toolStripStatusLabel1;
			STS_TXT.Trace ( "Init." );

			//タブ初期化
			TabAction_Load ();
			TabEffect_Load ();
			TabCommand_Load ();
			TabChara_Load ();

			//キャラデータのテスト
			TestCharaData ();

			//開始
			Init ();

			//表示
			Disp ();
		}

		//==================================================================================
		//	終了時
		//==================================================================================
		private void FormMain_FormClosing ( object sender, FormClosingEventArgs e )
		{
			//メインフォームを閉じるため、
			//モーダルフォームで開いた子フォームの関連を切る
			FormAction.Inst.Owner = null;
			FormScript.Inst.Owner = null;
		}

	}
}
