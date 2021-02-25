using System.IO;

namespace GameSettings
{
	public class SettingsHeader
	{
		//ファイル名
		public string filename = "settings.dat";

		//<CPU_or_PLAYER> //0:PLAYER //1:CPU
		public byte cpu_or_player_1p { get; set; }	//<1P>
		public byte cpu_or_player_2p { get; set; }	//<2P>

		//<Chara> //0:Knight //1:Wizzard
		public byte chara_1p { get; set; }	//<1P>
		public byte chara_2p { get; set; }	//<2P>

		enum CHARA_NAME
		{
			Knight = 0,
			Wizzard = 1,
		};

		//<Demo> //0:Normal mode //1:Demo mode
		public byte demo { get; set; }

		//<Battle> //0:battle start //1:title start
		public byte battle { get; set; }

		public SettingsHeader ()
		{
			cpu_or_player_1p = 0;
			cpu_or_player_2p = 0;
			chara_1p = 0;
			chara_2p = 1;
			demo = 0;
			battle = 0;
		}
	}

	public class SettingsReader
	{
		public SettingsReader ( SettingsHeader sh )
		{
			FileStream fs;

			//ファイルが存在しないとき
			if ( ! File.Exists ( sh.filename ) )
			{
				//初期設定でファイルを作成
				SettingsWriter sw = new SettingsWriter ( sh );
				return;
			}

			//ファイルが存在するとき
			fs = new FileStream ( sh.filename, FileMode.Open, FileAccess.Read );
			BinaryReader biReader = new BinaryReader ( fs );

			//<CPU_or_PLAYER> //0:PLAYER //1:CPU
			sh.cpu_or_player_1p = biReader.ReadByte ();			//<1P>
			sh.cpu_or_player_2p = biReader.ReadByte ();			//<2P>

			//<Chara> //0:Setsuka //1:Hisame
			sh.chara_1p = biReader.ReadByte ();			//<1P>
			sh.chara_2p = biReader.ReadByte ();			//<2P>

			//<Demo> //0:Normal mode //1:Demo mode
			sh.demo = biReader.ReadByte ();

			//<Battle> //0:battle start //1:title start
			sh.battle = biReader.ReadByte ();

			fs.Close ();
		}
	}

	public class SettingsWriter
	{
		public SettingsWriter ( SettingsHeader sh )
		{
			FileStream fs = new FileStream ( sh.filename, FileMode.Create, FileAccess.Write );
			BinaryWriter biWriter = new BinaryWriter ( fs );

			//<CPU_or_PLAYER> //0:PLAYER //1:CPU
			biWriter.Write ( sh.cpu_or_player_1p );			//<1P>
			biWriter.Write ( sh.cpu_or_player_2p );			//<2P>

			//<Chara> //0:Setsuka //1:Hisame
			biWriter.Write ( sh.chara_1p );			//<1P>
			biWriter.Write ( sh.chara_2p );			//<2P>

			//<Demo> //0:Normal mode //1:Demo mode
			biWriter.Write ( sh.demo );

			//<Battle> //0:battle start //1:title start
			biWriter.Write ( sh.battle );

			fs.Close ();
		}
	}
}
