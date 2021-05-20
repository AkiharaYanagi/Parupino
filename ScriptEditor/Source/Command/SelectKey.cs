namespace ScriptEditor
{
	using GKC_ST = GameKeyCommand.GameKeyCommandState;

	//選択されているコマンド中のキー
	public class SelectKey
	{
		//未選択状態
		public bool Selecting { get; set; } = true;

		//対象データ
		public Command Cmd { get; set; } = new Command ();

		//フレーム数
		public int Frame { get; set; } = 0;

		//キー種類
		public enum KeyKind
		{
			ARROW,
			KEY_L,
			KEY_M,
			KEY_H,
			KEY_S
		}

		public KeyKind Kind { get; set; } = KeyKind.ARROW;


		public void Set ( Command cmd, int frame, KeyKind keyKind )
		{
			Cmd = cmd;
			Frame = frame;
			Kind = keyKind;
			Selecting = true;
		}

		public GameKeyCommand GetGKC ( Command cmd )
		{
			if ( cmd.ListGameKeyCommand.Count <= Frame ) { return null; }
			return cmd.ListGameKeyCommand [ Frame ];
		}

		public GKC_ST GetSt ( Command cmd )
		{
			GameKeyCommand gkc = cmd.ListGameKeyCommand [ Frame ];

			GKC_ST ret = GKC_ST.KEY_OFF;
			switch ( Kind )
			{
			case KeyKind.ARROW: ret = gkc.GetLvrSt (); break;
			case KeyKind.KEY_L: ret = gkc.Btn [ 0 ]; break;
			case KeyKind.KEY_M: ret = gkc.Btn [ 1 ]; break;
			case KeyKind.KEY_H: ret = gkc.Btn [ 2 ]; break;
			case KeyKind.KEY_S: ret = gkc.Btn [ 3 ]; break;
			}

			return ret; 
		}

		public void SetSt ( Command cmd, GKC_ST gkcst )
		{
			GameKeyCommand gkc = cmd.ListGameKeyCommand [ Frame ];

			switch ( Kind )
			{
			case KeyKind.ARROW: gkc.SetLvrSt ( gkcst ); break;
			case KeyKind.KEY_L: gkc.Btn [ 0 ] = gkcst; break;
			case KeyKind.KEY_M: gkc.Btn [ 1 ] = gkcst; break;
			case KeyKind.KEY_H: gkc.Btn [ 2 ] = gkcst; break;
			case KeyKind.KEY_S: gkc.Btn [ 3 ] = gkcst; break;
			}
		}
	}
}
