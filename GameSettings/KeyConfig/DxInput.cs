using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//using Microsoft.DirectX;
//using Microsoft.DirectX.DirectInput;
using SlimDX.DirectInput;

//@todo SlimDXに移行
//		プロジェクト参照にSlimDXを追加


namespace GameSettings
{
	//-------------------------------------------------------------------
	//	DirectInputのラッパ
	//		キーボードとジョイスティックの状態
	//-------------------------------------------------------------------
    public class DxInput
    {
		public DirectInput	dInput;	//DirectInputオブジェクト

		private DxKeyboard dxKeyboard;		//キーボード
        private DxJoyStick dxJoystick;      //ジョイスティック

        //コンストラクタ
        public DxInput()
        {
			//DirectInputオブジェクト
			dInput = new SlimDX.DirectInput.DirectInput ();

			dxKeyboard = new DxKeyboard ( dInput );		//キーボード
            dxJoystick = new DxJoyStick ( dInput );		//ジョイスティック
        }

        //毎回の保存と更新
        public void Update()
        {
			dxKeyboard.Update ();
			dxJoystick.Update();
        }

        //押された状態のジョイスティックのボタンを返す
        public JoyStickKey GetJoyStickButton()
        {
            int device = 0;
            int button = DxJoyStick.JOYSTICK_NEUTRAL;

            //すべてのデバイスとボタンをループして押された状態があったらbreak
            for (device = 0; device < dxJoystick.GetDeviceNum(); device++)
            {
                for (button = 0; button < DxJoyStick.NUM_JOYSTICK_BUTTON; button++)
                {
                    if (dxJoystick.IsButton(device, button))
                    {
                        return new JoyStickKey(device, button);
                    }
                }
                if (dxJoystick.GetUP(device)) { button = DxJoyStick.JOYSTICK_UP; break; }
                if (dxJoystick.GetDOWN(device)) { button = DxJoyStick.JOYSTICK_DOWN; break; }
                if (dxJoystick.GetLEFT(device)) { button = DxJoyStick.JOYSTICK_LEFT; break; }
                if (dxJoystick.GetRIGHT(device)) { button = DxJoyStick.JOYSTICK_RIGHT; break; }
                button = DxJoyStick.JOYSTICK_NEUTRAL; //未入力
            }
            return new JoyStickKey(device, button);
        }

        //押された瞬間のジョイスティックのボタンを返す
        public JoyStickKey PushJoyStickButton()
        {
            int device = 0;
            int button = DxJoyStick.JOYSTICK_NEUTRAL;

            //すべてのデバイスとボタンをループして押された状態があったらbreak
            for (device = 0; device < dxJoystick.GetDeviceNum(); device++)
            {
                for (button = 0; button < DxJoyStick.NUM_JOYSTICK_BUTTON; button++)
                {
                    if (dxJoystick.IsButtonPush(device, button))
                    {
                        return new JoyStickKey(device, button);
                    }
                }
                if (dxJoystick.IsPushUP(device)) { button = DxJoyStick.JOYSTICK_UP; break; }
                if (dxJoystick.IsPushDOWN(device)) { button = DxJoyStick.JOYSTICK_DOWN; break; }
                if (dxJoystick.IsPushLEFT(device)) { button = DxJoyStick.JOYSTICK_LEFT; break; }
                if (dxJoystick.IsPushRIGHT(device)) { button = DxJoyStick.JOYSTICK_RIGHT; break; }
                button = DxJoyStick.JOYSTICK_NEUTRAL; //未入力
            }
            return new JoyStickKey(device, button);
        }

        //押された瞬間の入力を返す
        public DeviceInput GetInput()
        {
			//戻値
            DeviceInput di = new DeviceInput();

            //ジョイスティック入力検出
            JoyStickKey jk = PushJoyStickButton();
            if (jk.ButtonID != DxJoyStick.JOYSTICK_NEUTRAL)
            {
                di.joykey = jk;
                di.type = DeviceTypeForGame.JOYSTICK;
                return di;
            }

            //キーボード入力検出
            Key k = dxKeyboard.PushKeyBoard();
            if (k != Key.Escape)    //入力があった場合
            {
                di.keyboard = k;
                di.type = DeviceTypeForGame.KEYBOARD;
                return di;
            }

            //未入力はそのまま返す
            return di;
        }

    }
}
