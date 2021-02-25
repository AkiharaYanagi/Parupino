//=============================================================
// 定数宣言
//=============================================================

namespace GameSettings
{
    public enum GameInput : int
    {
        P1_UP = 0,
        P1_DOWN = 1,
        P1_LEFT = 2,
        P1_RIGHT = 3,
        P1_KEY1 = 4,
        P1_KEY2 = 5,
        P1_KEY3 = 6,
        P1_KEY4 = 7,
        P2_UP = 8,
        P2_DOWN = 9,
        P2_LEFT = 10,
        P2_RIGHT = 11,
        P2_KEY1 = 12,
        P2_KEY2 = 13,
        P2_KEY3 = 14,
        P2_KEY4 = 15,
        NUM_KEYNAME = 16,	//foreachのときには飛ばす
    };

    //ゲームで利用できるデバイスの種類
    public enum DeviceTypeForGame
    {
        KEYBOARD = 0,
        JOYSTICK = 1,
        NODEVICE = 2,
    }

    //ジョイスティックのキー
    public class JoyStickKey
    {
        public int DeviceID { get; set; }
        public int ButtonID { get; set; }

        public JoyStickKey()
        {
            DeviceID = 0;
            ButtonID = DxJoyStick.JOYSTICK_NEUTRAL;
        }
        public JoyStickKey(int device, int button)
        {
            DeviceID = device;
            ButtonID = button;
        }
    }


}
