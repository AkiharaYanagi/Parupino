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
			//上書保存
			SaveChara saveChara = new SaveChara ();
			saveChara.Do ( filepath, chara );

			//タイトルバー編集中ファイル名更新(非保存表示を消去)
			SetFormText ( filepath );
		}

		//------------------------------------------
		//	キャラ読込総合
		//------------------------------------------
		private void _LoadChara ( string filepath )
		{
			//読込
			LoadChara loadChara = new LoadChara ();
			loadChara.Do ( filepath, chara );
			LoadCharaData ();

			//タイトルバー更新
			SetFormText ( stgs.LastFilepath );
		}

		//キャラロード時に更新
		private void LoadCharaData ()
		{
			//名前参照のチェック
			TestChara testChara = new TestChara ();
			try { testChara._TestNameAssign ( chara ); }
			catch
			{
				STS_TXT.Tssl.BackColor = Color.Red;
				STS_TXT.Trace( "Name Refference Error." );
//				return;
			}
			STS_TXT.Tssl.BackColor = SystemColors.Control;

			//各コントロールにデータを設定
			SetCharaData ( chara );

			//設定ファイルにファイル位置を記録
			stgs.LastDirectory = Path.GetDirectoryName ( openFileDialog1.FileName );
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

			//タブアクションを選択
			tabAction_Selected ();

			//表示の更新
			//DispChara.Inst.Disp ();
			Ctrl_All.Inst.AllDisp ();
		}

	}
}

