﻿using System;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;
using System.Drawing;


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
			//"@"はコマンドラインに文字列が表示されないようにする構文
			// Explorer.exe . (ピリオドで現在ディレクトリ)
			Process.Start ( "Explorer.exe", @"." );
		}

		private void 上書保存ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//上書保存
			SaveChara saveChara = new SaveChara ( stgs.LastFilename, chara );

			//編集中ファイル名更新(非保存表示を消去)
			SetFormText ( stgs.LastFilename );

			STS_TXT.Trace ( "上書保存" );
		}

		private void 別名保存ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//基本拡張子
			saveFileDialog1.DefaultExt = "dat";

			//初期ファイル名
			saveFileDialog1.FileName = stgs.LastFilename;

			//ダイアログ開始
			if ( saveFileDialog1.ShowDialog () == DialogResult.OK )
			{
				SaveChara saveChara = new SaveChara ( saveFileDialog1.FileName, chara );

				//編集中ファイル名更新(非保存表示を消去)
				stgs.LastFilename = saveFileDialog1.FileName;
				SetFormText ( stgs.LastFilename );

				stgs.LastDirectory = Path.GetDirectoryName ( saveFileDialog1.FileName );

				XML_IO.Save ( stgs );
			}
			STS_TXT.Trace ( "別名保存" );
		}

		private void 基準保存TToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			SaveChara saveChara = new SaveChara ( "testChara.dat", chara );
			STS_TXT.Trace ( "基準保存" );
		}

		private void 読込ToolStripMenuItem_Click ( object sender, EventArgs e )
		{
			//ダイアログ中の初期ファイル名
			openFileDialog1.FileName = stgs.LastFilename;

			//ダイアログ開始
			if ( openFileDialog1.ShowDialog () == DialogResult.OK )
			{
				LoadChara loadChara = new LoadChara ( openFileDialog1.FileName, chara );
				LoadCharaData ();
			}
			//ファイル名更新
			stgs.LastFilename = Path.GetFileName ( openFileDialog1.FileName );

			STS_TXT.Trace ( "読込" );
		}

		//キャラロード時に更新
		private void LoadCharaData ()
		{
			//各コントロールにデータを設定
			SetCharaData ( chara );

			//設定ファイルにファイル位置を記録
			stgs.LastDirectory = Path.GetDirectoryName ( openFileDialog1.FileName );
			XML_IO.Save ( stgs );

			//カレントディレクトリも変更する
			Directory.SetCurrentDirectory ( stgs.LastDirectory );
			SetFormText ( stgs.LastFilename );

			//タブアクションを選択
			tabAction_Selected ();


			//名前参照のチェック
			TestChara testChara = new TestChara ();
			try { testChara._TestNameAssign ( chara ); }
			catch
			{
				STS_TXT.Tssl.BackColor = Color.Red;
				STS_TXT.Trace( "Name Refference Error." );
			}
			STS_TXT.Tssl.BackColor = SystemColors.Control;

			//表示の更新
			DispChara.Inst.Disp ();
		}

		private void テキストから読込ToolStripMenuItem_Click ( object sender, System.EventArgs e )
		{
			//ダイアログ中の初期ファイル名
			openFileDialog1.FileName = stgs.LastFilename;

			//ダイアログ開始
			if ( openFileDialog1.ShowDialog () == DialogResult.OK )
			{
				LoadTextChara loadChara = new LoadTextChara ( openFileDialog1.FileName, chara );
				LoadCharaData ();
			}
		}

		//タイトルバーテキスト更新
		private void ReloadTitleBarText ()
		{
			this.Text = Directory.GetCurrentDirectory() + "\\" + stgs.LastFilename + " - " + formText;
		}
	}

}

