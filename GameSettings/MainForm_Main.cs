using System;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace GameSettings
{
	public partial class MainForm : Form
	{
		//ロード
		protected override void OnLoad ( EventArgs e )
		{
			//ファイル読込
			LoadFile ();

			//読込終了かつコンポーネント初期化終了後で表示に反映する
	
			//フルスクリーン
			cb_fullscreen.Checked = apStg.fullscreen;
			
			//解像度コンボボックス初期化
			cmb_resolution.Items.Add ( apStg.v_resolution [ 0 ] );
			cmb_resolution.Items.Add ( apStg.v_resolution [ 1 ] );

			//解像度 読み込んだ値から選択する
			int index = -1;
			bool hit = false;
			foreach ( Resolution res in apStg.v_resolution )
			{
				if ( res.x == apStg.window_x && res.y == apStg.window_y )
				{
					hit = true;
					++index;
					break;
				}
				++index;
			}
			cmb_resolution.SelectedIndex = hit ? index : -1;
			
			//デモ
			CH_Demo.Checked = gmStg.demo;

			//バトルから開始
			CH_StartBattle.Checked = gmStg.startBattle;

			//バトルから開始
			CH_Training.Checked = gmStg.training;

			//操作1p
			if ( gmStg.inputPlayer1p )
			{
				rb_input1pPlayer.Checked = true;
			}
			else
			{
				rb_input1pCPU.Checked = true;
			}

			//操作2p
			if ( gmStg.inputPlayer2p )
			{
				rb_input2pPlayer.Checked = true;
			}
			else
			{
				rb_input2pCPU.Checked = true;
			}

			//キャラ選択コンボボックス初期化
			cB_Chara1p.Items.Add ( CHARA_NAME.SONIA );
			cB_Chara1p.Items.Add ( CHARA_NAME.ORFLOAT );
			cB_Chara1p.SelectedIndex = (int)gmStg.name1p;

			//キャラ選択コンボボックス初期化
			cB_Chara2p.Items.Add ( CHARA_NAME.SONIA );
			cB_Chara2p.Items.Add ( CHARA_NAME.ORFLOAT );
			cB_Chara2p.SelectedIndex = (int)gmStg.name2p;

			//キーコンフィグ初期化
			LoadKeyConfig ();

			base.OnLoad ( e );
		}

		private void LoadFile ()
		{
			apStg.Load ( apStg_filename );
			gmStg.Load ( gmStg_filename );
		}

		//キャンセルして終了
		private void btn_Cancel_Click ( object sender, EventArgs e )
		{
			Application.Exit ();
		}

		//保存して終了
		private void btn_OK_Click ( object sender, EventArgs e )
		{
			SaveFile ();
			Application.Exit ();
		}

		//ファイル保存
		private void SaveFile ()
		{
			apStg.Save ( apStg_filename );
			gmStg.Save ( gmStg_filename );
			keySetting.Write ();
		}

		//フルスクリーンチェックボックス
		private void cb_fullscreen_CheckedChanged ( object sender, EventArgs e )
		{
			apStg.fullscreen = cb_fullscreen.Checked;
		}

		//ウィンドウサイズ(解像度)
		private void cmb_resolution_SelectedIndexChanged ( object sender, EventArgs e )
		{
			apStg.indexResolution = (uint)cmb_resolution.SelectedIndex;
		}

		//操作1p
		private void rb_input1pPlayer_CheckedChanged ( object sender, EventArgs e )
		{
			gmStg.inputPlayer1p = rb_input1pPlayer.Checked;
		}

		//操作2p
		private void rb_input2pPlayer_CheckedChanged ( object sender, EventArgs e )
		{
			gmStg.inputPlayer2p = rb_input2pPlayer.Checked;
		}

		//デモ
		private void CH_Demo_CheckedChanged ( object sender, System.EventArgs e )
		{
			gmStg.demo = CH_Demo.Checked;
		}

		//バトルから開始
		private void CH_StartBattle_CheckedChanged ( object sender, System.EventArgs e )
		{
			gmStg.startBattle = CH_StartBattle.Checked;
		}

		//トレーニングモード
		private void CH_Training_CheckedChanged ( object sender, System.EventArgs e )
		{
			gmStg.training = CH_Training.Checked;
		}

		//キャラ選択1p
		private void cB_Chara1p_SelectedIndexChanged ( object sender, EventArgs e )
		{
			gmStg.name1p = (CHARA_NAME)cB_Chara1p.SelectedItem;
		}

		//キャラ選択2p
		private void cB_Chara2p_SelectedIndexChanged ( object sender, System.EventArgs e )
		{
			gmStg.name2p = (CHARA_NAME)cB_Chara2p.SelectedItem;
		}

		//フォルダを開く
		private void btn_folder_Click ( object sender, EventArgs e )
		{
//			string curDir = Directory.GetCurrentDirectory () + "\\";
//			Process.Start ( "Explorer.exe", @"/select, " + curDir );

			//"@"はコマンドラインに文字列が表示されないようにする構文
			// Explorer.exe . (ピリオドで現在ディレクトリ)
			Process.Start ( "Explorer.exe", @"." );
		}
	}
}
