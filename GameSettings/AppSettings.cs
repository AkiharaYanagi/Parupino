using System;
using System.IO;

namespace GameSettings
{
	//---------------------------------------------------------------------
	//	アプリケーションの起動時に必要な解像度やウィンドウサイズの設定
	//---------------------------------------------------------------------

	//解像度
	public class Resolution
	{
		public uint x = 0;
		public uint y = 0;

		public Resolution ( uint _x, uint _y )
		{
			x = _x; y = _y;
		}
		public override string ToString ()
		{
			return x.ToString () + ", " + y.ToString (); 
		}
	}

	//設定
	public class AppSettings
	{
		//画面
		public bool fullscreen = false;
		public uint window_x = 640;
		public uint window_y = 480;
		public uint indexResolution = 0;

		//解像度
		public Resolution[] v_resolution = new Resolution[]
		{ 
			new Resolution ( 640, 480 ), 
			new Resolution ( 1280, 960 ) 
		};

		//-------------------------------------------
		//コンストラクタ
		public AppSettings ()
		{
		}

		public void Load ( string filename )
		{
			//ファイルチェック
			if ( File.Exists ( filename ) ) //存在するとき読込
			{
				using ( BinaryReader br = new BinaryReader ( new FileStream ( filename, FileMode.Open, FileAccess.ReadWrite ) ) )
				{
					fullscreen = br.ReadBoolean ();
					window_x = br.ReadUInt32 ();
					window_y = br.ReadUInt32 ();
				}
			}
			else
			{
				//ファイル作成
				Save ( filename );
			}
		}

		//ファイル書込
		public void Save ( string filename )
		{
			using ( BinaryWriter bw = new BinaryWriter ( new FileStream ( filename, FileMode.Create, FileAccess.Write ) ) )
			{
				bw.Write ( fullscreen );
				bw.Write ( v_resolution [ indexResolution ].x );
				bw.Write ( v_resolution [ indexResolution ].y );
			}
		}
	}
}
