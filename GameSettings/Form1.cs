using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace GameSettings
{
	public partial class Form1 : Form
	{
		//ファイル名
		private string filename = "Setting.dat";

		//解像度
		public Resolution[] v_resolution = new Resolution[]
		{ 
			new Resolution ( 640, 480 ), 
			new Resolution ( 1280, 960 ) 
		};

		//設定
		private Settings setting = new Settings ();

		//コンストラクタ
		public Form1 ()
		{
			//ファイルチェック
			if ( File.Exists ( filename ) ) //存在するとき読込
			{
				using ( BinaryReader br = new BinaryReader ( new FileStream ( filename, FileMode.Open, FileAccess.ReadWrite ) ) )
				{
					setting.fullscreen = br.ReadBoolean ();
					setting.window_x = br.ReadUInt32 ();
					setting.window_y = br.ReadUInt32 ();
				}
			}
			else
			{
				//ファイル作成
				using ( BinaryWriter bw = new BinaryWriter ( new FileStream ( filename, FileMode.Create, FileAccess.Write ) ) )
				{
					bw.Write ( setting.fullscreen );
					bw.Write ( setting.window_x );
					bw.Write ( setting.window_y );
				}
			}

			//コンポーネント初期化
			InitializeComponent ();

			//読込終了かつコンポーネント初期化終了後で表示に反映する
			cb_fullscreen.Checked = setting.fullscreen;
	
			//コンボボックス初期化
			cmb_resolution.Items.Add ( v_resolution [ 0 ] );
			cmb_resolution.Items.Add ( v_resolution [ 1 ] );
			
			//読み込んだ値から選択する
			int index = -1;
			bool hit = false;
			foreach ( Resolution res in v_resolution )
			{
				if ( res.x == setting.window_x && res.y == setting.window_y )
				{
					hit = true;
					++index;
					break;
				}
				++index;
			}
			cmb_resolution.SelectedIndex = hit ? index : -1;
		}

		//保存して終了
		private void btn_OK_Click ( object sender, EventArgs e )
		{
			SaveFile ();
			Application.Exit ();
		}

		//キャンセルして終了
		private void btn_Cancel_Click ( object sender, EventArgs e )
		{
			Application.Exit ();
		}

		//ファイル保存
		private void SaveFile ()
		{
			//ファイル書込
			using ( BinaryWriter bw = new BinaryWriter ( new FileStream ( filename, FileMode.Truncate, FileAccess.Write ) ) )
			{
				bw.Write ( setting.fullscreen );
				bw.Write ( v_resolution [ setting.indexResolution ].x );
				bw.Write ( v_resolution [ setting.indexResolution ].y );
			}
		}

		//フルスクリーンチェックボックス
		private void cb_fullscreen_CheckedChanged ( object sender, EventArgs e )
		{
			setting.fullscreen = cb_fullscreen.Checked;
		}

		//ウィンドウサイズ(解像度)
		private void cmb_resolution_SelectedIndexChanged ( object sender, EventArgs e )
		{
			setting.indexResolution = (uint)cmb_resolution.SelectedIndex;
		}
	}
}
