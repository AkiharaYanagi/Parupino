using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;

//using Microsoft.DirectX;
//using Microsoft.DirectX.DirectInput;
//using DirectInput = Microsoft.DirectX.DirectInput;
using SlimDX.DirectInput;

namespace GameSettings
{
    //キー設定
    public class KeySetting
    {
        //デバイス入力をゲーム入力の数だけ保持する
        private Dictionary<GameInput, DeviceInput> dctKey = new Dictionary<GameInput, DeviceInput>();

        //コンストラクタ
        public KeySetting()
        {
			//初期値
			const DeviceTypeForGame dt = DeviceTypeForGame.KEYBOARD;
			dctKey.Add ( GameInput.P1_UP,    new DeviceInput ( dt, null, Key.UpArrow ) );
			dctKey.Add ( GameInput.P1_DOWN,  new DeviceInput ( dt, null, Key.DownArrow ) );
			dctKey.Add ( GameInput.P1_LEFT,  new DeviceInput ( dt, null, Key.LeftArrow ) );
			dctKey.Add ( GameInput.P1_RIGHT, new DeviceInput ( dt, null, Key.RightArrow ) );
			dctKey.Add ( GameInput.P1_KEY1,  new DeviceInput ( dt, null, Key.Z ) );
			dctKey.Add ( GameInput.P1_KEY2,  new DeviceInput ( dt, null, Key.X ) );
			dctKey.Add ( GameInput.P1_KEY3,  new DeviceInput ( dt, null, Key.C ) );
			dctKey.Add ( GameInput.P1_KEY4,  new DeviceInput ( dt, null, Key.V ) );
			dctKey.Add ( GameInput.P2_UP,    new DeviceInput ( dt, null, Key.Home ) );
			dctKey.Add ( GameInput.P2_DOWN,  new DeviceInput ( dt, null, Key.End ) );
			dctKey.Add ( GameInput.P2_LEFT,  new DeviceInput ( dt, null, Key.Delete ) );
			dctKey.Add ( GameInput.P2_RIGHT, new DeviceInput ( dt, null, Key.PageDown ) );
			dctKey.Add ( GameInput.P2_KEY1,  new DeviceInput ( dt, null, Key.A ) );
			dctKey.Add ( GameInput.P2_KEY2,  new DeviceInput ( dt, null, Key.S ) );
			dctKey.Add ( GameInput.P2_KEY3,  new DeviceInput ( dt, null, Key.D ) );
			dctKey.Add ( GameInput.P2_KEY4 , new DeviceInput ( dt, null, Key.F ) );
       }

        //ファイル書出
        public void Write()
        {
            FileStream fs = new FileStream("keyconfig.dat", FileMode.Create, FileAccess.Write);
            foreach ( GameInput gInput in dctKey.Keys )
            {
                fs.WriteByte((byte)dctKey[gInput].type);
                if (dctKey[gInput].type == DeviceTypeForGame.JOYSTICK)
                {
                    fs.WriteByte((byte)dctKey[gInput].joykey.DeviceID);
                    fs.WriteByte((byte)dctKey[gInput].joykey.ButtonID);
                }
                else if (dctKey[gInput].type == DeviceTypeForGame.KEYBOARD)
                {
                    //キーボード定数
                    //SlimDxからDirectInput定義に変換
					ConvertStoD cnv = new ConvertStoD ();
					int iKey = cnv.Keyboard ( dctKey[gInput].keyboard );
                    fs.WriteByte((byte)iKey);
                }
            }
            fs.Close();
        }

        //ファイル読込
        public void Read()
        {
            const string filename = "keyConfig.dat";
			//ファイルが存在しないとき
			if ( ! File.Exists ( filename ) )
			{
				//初期設定ファイルを作成する
				Write ();
			}

			using ( FileStream fs = new FileStream(filename, FileMode.Open, FileAccess.Read) )
			{
				foreach ( GameInput gInput in Enum.GetValues ( typeof ( GameInput ) ) )
				{
					if ( GameInput.NUM_KEYNAME == gInput ) { break; }

					int b = fs.ReadByte();
					Debug.Write ( b );
					if ((DeviceTypeForGame)b == DeviceTypeForGame.JOYSTICK)
					{
						dctKey[gInput].joykey.DeviceID = (int)fs.ReadByte();
						dctKey[gInput].joykey.ButtonID = (int)fs.ReadByte();
						Debug.Write ( dctKey[ gInput ].joykey.DeviceID.ToString() + ", " + dctKey[ gInput ].joykey.DeviceID.ToString() );
					}
					else if ((DeviceTypeForGame)b == DeviceTypeForGame.KEYBOARD)
					{
						//キーボード定数
						//DirectInputからSlimDx定義に変換
						int iKey = fs.ReadByte();
						DxKey dxkey = (DxKey)Enum.ToObject ( typeof ( DxKey ), iKey );
						ConvertDtoS cnv = new ConvertDtoS ();
						dctKey[gInput].keyboard = cnv.Keyboard ( dxkey );
						Debug.Write ( "" + (int)dctKey[gInput].keyboard );
					}
					dctKey[gInput].type = (DeviceTypeForGame)b;
					Debug.Write ( "\n" );
#if false
				int b = fs.ReadByte ();
				switch ( b )
				{
				case ( int ) DeviceTypeForGame.JOYSTICK:
					Debug.Write ( b );
					int did = ( int ) fs.ReadByte ();
					int bid = ( int ) fs.ReadByte ();
					Debug.Write ( did );
					Debug.Write ( bid );

					key[ gInput ].joykey.deviceID = did;
					key[ gInput ].joykey.buttonID = bid;

					Debug.Write ( "\n" );
					
					break;

				case ( int ) DeviceTypeForGame.KEYBOARD:
					Debug.Write ( b );
					Key k = ( Key ) fs.ReadByte ();
					Debug.Write ( ( int ) k );
					key[ gInput ].keyboard = k;
					Debug.Write ( "\n" );
					break;

				default:
					Debug.Write ( b );
					key[ gInput ].type = ( DeviceTypeForGame ) b;
					Debug.Write ( "\n" );
					break;
				}
#endif
				}
			}
		}

        //設定
        public void Set(GameInput gInput, DeviceInput dInput)
        {
            dctKey[gInput] = dInput;
        }
        public DeviceInput Get(GameInput gInput)
        {
            return dctKey[gInput];
        }
    }

}
