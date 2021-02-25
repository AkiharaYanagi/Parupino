using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SlimDX.DirectInput;


namespace GameSettings
{
	//-------------------------------------------------------------------
    //デバイス入力保存  
	//		ジョイスティック、キーボードの値を一つか、または未入力状態を持つ。
 	//-------------------------------------------------------------------
   public class DeviceInput
    {
        //タイプ(KEYBOARD, JOYSTICK, NODEVICE )
        public DeviceTypeForGame type { get; set; }

        public JoyStickKey joykey { get; set; }        //ジョイスティック入力
        public Key keyboard { get; set; }      //キーボード入力

        //コンストラクタ
		public DeviceInput ()
		{
			type = DeviceTypeForGame.NODEVICE;
			joykey = new JoyStickKey ();
		}

		public DeviceInput ( DeviceTypeForGame t, JoyStickKey j, Key k )
		{
			this.type = t;
			joykey = new JoyStickKey ();
			if ( null != j )
			{
				joykey.DeviceID = j.DeviceID;
				joykey.ButtonID = j.ButtonID;
			}
			keyboard = k;
		}

		//文字列変換オーバーライド
        public override string ToString()
        {
            StrGameInput str = new StrGameInput();
            return str.GetName(this);
        }
    }

	//-------------------------------------------------------------------
    //キーボード入力保存
	//-------------------------------------------------------------------
    public class BIndexer
    {
        //Key列挙体の個数で配列を宣言
//        private bool[] b = new bool[(int)Key.Unknown];
        private bool[] b = new bool[Enum.GetValues(typeof(Key)).Length];

        //インデクサ
        public bool this [ Key index ]
        {
            get { return b [ (int)index ]; }
            set { b [ (int)index ] = value; }
        }

        //キーボードの状態から直接保存
        public void SetKeyState ( KeyboardState keyboardState )
        {
#if false
			for (Key k = Key.Escape - 1; k < Key.Unknown; k++)
            {
                b [ (int)k ] = state.IsPressed ( k );
            }
#endif
			foreach ( Key k in Enum.GetValues ( typeof ( Key ) ) )
			{
                b [ (int)k ] = keyboardState.IsPressed ( k );
			}
        }
    }

}
