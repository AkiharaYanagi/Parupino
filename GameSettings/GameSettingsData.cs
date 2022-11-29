using System;
using System.Diagnostics;
using System.IO;


namespace GameSettings
{
	public class GameSettingsData
	{
		//開始状態
		public enum Stng_Start
		{
			General, Battle, Traning, Demo, 
		};

		public Stng_Start Start { get; set; } = Stng_Start.General;


		//操作
		public enum Stng_Operate
		{
			Player, CPU,
		};

		public Stng_Operate Operate1p { get; set; } = Stng_Operate.Player;
		public Stng_Operate Operate2p { get; set; } = Stng_Operate.Player;

		//キャラ
		public enum Stng_Chara
		{
			testPlayer, Rakuno, Yukino, Random, 
		};

		public Stng_Chara Chara1p { get; set; } = Stng_Chara.testPlayer;
		public Stng_Chara Chara2p { get; set; } = Stng_Chara.testPlayer;

		//-------------------------------------------------------------------
		public void Init ()
		{
			Start = Stng_Start.General;
			Operate1p = Stng_Operate.Player;
			Operate2p = Stng_Operate.Player;
			Chara1p = Stng_Chara.testPlayer;
			Chara2p = Stng_Chara.testPlayer;
		}

		public void Save ( string filename )
		{
			using ( FileStream fs = new FileStream ( filename, FileMode.Create, FileAccess.Write ) )
			using ( BinaryWriter bw = new BinaryWriter ( fs ) )
			{ 
				bw.Write ( (int)Start );
				bw.Write ( (int)Operate1p );
				bw.Write ( (int)Operate2p );
			}
		}

		public void Load ( string filename )
		{
			try
			{
				using ( FileStream fs = new FileStream ( filename, FileMode.Open, FileAccess.Read ) )
				using ( BinaryReader br = new BinaryReader ( fs ) )
				{ 
					Start = (Stng_Start) br.ReadInt32 ();
					Operate1p = (Stng_Operate) br.ReadInt32 ();
					Operate2p = (Stng_Operate) br.ReadInt32 ();
				}

			}
			catch ( Exception e )
			{
				Debug.WriteLine ( e.ToString () );

				//例外時は初期化データ
				Init ();
			}
		}
	}
}
