using System;
using System.IO;

namespace GameSettings
{
	//---------------------------------------------------------------------
	//	ゲーム内で用いる設定
	//---------------------------------------------------------------------

	//キャラ名
	public enum CHARA_NAME
	{
		RAKUNO,
		YUKINO,
	};

	public class GameSettings
	{
		//デモ
		public bool demo = false;

		//バトルから開始
		public bool startBattle = false;

		//トレーニングモード
		public bool training = false;

		//キャラ
		public CHARA_NAME name1p;
		public CHARA_NAME name2p;

		//入力 ( プレイヤー / CPU )
		public bool inputPlayer1p = true;
		public bool inputPlayer2p = true;

		//読込
		public void Load ( string filename )
		{
			//ファイルチェック
			if ( File.Exists ( filename ) ) //存在するとき読込
			{
				using ( BinaryReader br = new BinaryReader ( new FileStream ( filename, FileMode.Open, FileAccess.ReadWrite ) ) )
				{
					demo = br.ReadBoolean ();
					startBattle = br.ReadBoolean ();
					training = br.ReadBoolean ();
					inputPlayer1p = br.ReadBoolean ();
					inputPlayer2p = br.ReadBoolean ();
					name1p = (CHARA_NAME)br.ReadByte ();
					name2p = (CHARA_NAME)br.ReadByte ();
				}
			}
			else
			{
				//ファイル作成
				Save ( filename );
			}
		}

		//書出
		public void Save ( string filename )
		{
			//ファイル書込
			using ( BinaryWriter bw = new BinaryWriter ( new FileStream ( filename, FileMode.Create, FileAccess.Write ) ) )
			{
				bw.Write ( demo );
				bw.Write ( startBattle );
				bw.Write ( training );
				bw.Write ( inputPlayer1p );
				bw.Write ( inputPlayer2p );
				bw.Write ( (byte)name1p );
				bw.Write ( (byte)name2p );
			}

		}

	}
}
