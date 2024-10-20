using System;
using System.Windows.Forms;
using System.IO;
using System.Drawing;


namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//------------------------------------------
		//	キャラ書出総合
		//------------------------------------------
		private void _SaveChara ( string filepath )
		{
			//強制描画
			SetFormText ( "上書保存 - 開始 " + filepath );
			STS_TXT.Trace ( "上書保存 - 開始" );
			this.Refresh ();


			//タブがリスト編集のとき
			//アクションリスト、エフェクトリストを反映

			//上書保存
#if false
			SaveChara saveChara = new SaveChara ();
			saveChara.Do ( filepath, chara );
#endif
			SaveCharaBin saveCharaBin = new SaveCharaBin ();
			saveCharaBin.Do ( filepath, chara );


			//タイトルバー編集中ファイル名更新(非保存表示を消去)
			SetFormText ( "◆ 完了 ◆ 上書保存 - " + filepath );
			STS_TXT.Trace ( "上書保存 - ◆ 完了 ◆" );
		}

		//------------------------------------------
		//	キャラ読込総合
		//------------------------------------------
		private void _LoadChara ( string filepath )
		{
#if false
			//ドキュメント読込
			LoadChara loadChara = new LoadChara ();
			loadChara.Do ( filepath, chara );
			LoadCharaData ();
#endif
			//バイナリ読込
			LoadCharaBin loadCharaBin = new LoadCharaBin ();
			loadCharaBin.Do ( filepath, chara );
			LoadCharaData ();

			//===============================================================
			//1回限りの更新(スクリプト定義の仕様変更など)
			//　データのバックアップを取り、コピーで行うこと
			// ◆◆◆ 旧ロードで読込、新セーブで書出、新ロードで読込


#if true
#endif
			//===============================================================
		}

		//キャラロード時に更新
		private void LoadCharaData ()
		{
			string path = Path.GetDirectoryName ( stgs.LastFilepath );

			//名前参照のチェック
			TestChara testChara = new TestChara ();
			testChara.SOUND_DIR = path;

			try { testChara._TestNameAssign ( chara ); }
			catch ( Exception e )
			{
				STS_TXT.Trace_Err ( "Name Refference Error. " + e.Message );
				//return;
				//エラー表示をして続行
			}

			//設定ファイルにファイルパスを記録
			stgs.LastDirectory = path;
			XML_IO.Save ( stgs );

			//カレントディレクトリも変更する
			if ( stgs.LastDirectory == "" )
			{
				stgs.LastDirectory = Directory.GetCurrentDirectory ();
			}
			else
			{ 
				Directory.SetCurrentDirectory ( stgs.LastDirectory );
			}

			//タイトルバー更新
			SetFormText ( stgs.LastFilepath );

			//------------------------------------------
			//各コントロールにデータを設定
			SetCharaData ( chara );

			//タブアクションを選択
			tabAction_Selected ();

			//表示の更新
			//DispChara.Inst.Disp ();
			//Ctrl_All.Inst.AllDisp ();
			All_Ctrl.Inst.Disp ();
		}

	}
}

