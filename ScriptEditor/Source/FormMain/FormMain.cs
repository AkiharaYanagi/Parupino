﻿using System.Windows.Forms;

namespace ScriptEditor
{
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
		private Chara chara = new Chara ();		//編集対象キャラクタ
		private Ctrl_Settings stgs = new Ctrl_Settings();		//スクリプトエディタ自身の設定ファイル

		//==================================================================================
		//	コンストラクタ
		//==================================================================================
		public FormMain ()
		{
			//フォーム開始位置をマウス位置にする
			FormUtility.InitPosition ( this );

			//コンポーネントの初期化
			InitializeComponent ();

			//環境初期化
			LoadEnvironment ();

			//開始設定
			Init ();

			//データ読込
			LoadData ();

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
