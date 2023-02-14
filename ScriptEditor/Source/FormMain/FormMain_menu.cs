using System;
using System.IO;
using System.Windows.Forms;


namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//	メインメニュー
		//==================================================================================

		//コマンドラインから現在位置でエクスプローラを開く
		private void フォルダToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			FormUtility.OpenCurrentDir ();
		}

		private void 上書保存ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			_SaveChara ( stgs.LastFilepath );
			STS_TXT.Trace ( "上書保存" );
		}

		private void 別名保存ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//基本拡張子
			saveFileDialog1.DefaultExt = "dat";

			//初期ファイル名
			saveFileDialog1.FileName = stgs.LastFilepath;

			saveFileDialog1.OverwritePrompt = false;

			//ダイアログ開始
			if ( saveFileDialog1.ShowDialog () == DialogResult.OK )
			{
				_SaveChara ( saveFileDialog1.FileName );

				//パスの保存
				stgs.LastFilepath = saveFileDialog1.FileName;
				stgs.LastDirectory = Path.GetDirectoryName ( saveFileDialog1.FileName );
				XML_IO.Save ( stgs );

				STS_TXT.Trace ( "別名保存" );
			}
		}

		private void 基準保存TToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			SaveChara saveChara = new SaveChara ();
			saveChara.Do ( "testChara.dat", chara );
			STS_TXT.Trace ( "基準保存" );
		}

		private void 読込ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//ダイアログ中の初期ファイル名
			openFileDialog1.FileName = stgs.LastFilepath;

			//ダイアログ開始
			if ( openFileDialog1.ShowDialog () == DialogResult.OK )
			{
				_LoadChara ( openFileDialog1.FileName );

				//パスの保存
				stgs.LastFilepath = openFileDialog1.FileName;
				stgs.LastDirectory = Path.GetDirectoryName ( openFileDialog1.FileName );
				SetFormText ( stgs.LastFilepath );

				STS_TXT.Trace ( "読込" );
			}
		}

		private void テキストから読込ToolStripMenuItem_Click ( object sender, System.EventArgs e )
		{
			//ダイアログ中の初期ファイル名
			openFileDialog1.FileName = stgs.LastFilepath;

			//ダイアログ開始
			if ( openFileDialog1.ShowDialog () == DialogResult.OK )
			{
				LoadTextChara loadChara = new LoadTextChara ( openFileDialog1.FileName, chara );
				LoadCharaData ();
			}
		}

		private void バイナリから読込BToolStripMenuItem_Click ( object sender, System.EventArgs e )
		{
			//ダイアログ中の初期ファイル名
			openFileDialog1.FileName = stgs.LastFilepath;

			//ダイアログ開始
			if ( openFileDialog1.ShowDialog () == DialogResult.OK )
			{
				LoadCharaBin loadCharaBin = new LoadCharaBin ();
				loadCharaBin.Do ( openFileDialog1.FileName, chara );
				LoadCharaData ();
			}
		}

		//タイトルバーテキスト更新
		private void ReloadTitleBarText ()
		{
			this.Text = Directory.GetCurrentDirectory() + "\\" + stgs.LastFilepath + " - " + formText;
		}
	}

}

