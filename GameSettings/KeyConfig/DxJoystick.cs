using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//using Microsoft.DirectX;
//using Microsoft.DirectX.DirectInput;
//using DirectInput = Microsoft.DirectX.DirectInput;
using SlimDX.DirectInput;


namespace GameSettings
{
    class DxJoyStick
    {
        //ジョイスティック配列
        List<Joystick> joysticks = new List<Joystick>();
        List<JoystickState> joyStates = new List<JoystickState>();
        List<JoystickState> preJoyStates = new List<JoystickState>();

        public const int NUM_JOYSTICK_BUTTON = 128;   //ジョイスティックのボタンの数
        public const int JOYSTICK_UP = NUM_JOYSTICK_BUTTON + 1;       //レバー上
        public const int JOYSTICK_DOWN = NUM_JOYSTICK_BUTTON + 2;     //レバー下
        public const int JOYSTICK_LEFT = NUM_JOYSTICK_BUTTON + 3;     //レバー左
        public const int JOYSTICK_RIGHT = NUM_JOYSTICK_BUTTON + 4;    //レバー右
        public const int JOYSTICK_NEUTRAL = NUM_JOYSTICK_BUTTON + 5;    //未入力

        //コンストラクタ
        public DxJoyStick( DirectInput dInput )
        {
#if false
			//DirectInputデバイスのリストを取得
			DeviceList deviceList = Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AllDevices);

            //ジョイスティックデバイス
            Device device;

            //取得したデバイスリストを登録
            foreach (DeviceInstance instance in deviceList)
            {
                device = new Device(instance.InstanceGuid);
                device.SetCooperativeLevel(null,
                      CooperativeLevelFlags.NonExclusive
                    | CooperativeLevelFlags.NoWindowsKey
                    | CooperativeLevelFlags.Background
                );

                //ジョイスティックタイプのデータフォーマットを設定
                device.SetDataFormat(DeviceDataFormat.Joystick);

                //Axisレンジを設定
                foreach (DeviceObjectInstance doi in device.Objects)
                {
                    if ((doi.ObjectId & (int)DeviceObjectTypeFlags.Axis) != 0)
                    {
                        device.Properties.SetRange(
                            ParameterHow.ById,
                            doi.ObjectId,
                            new InputRange(-1000, 1000));
                    }
                }

                //Axisの絶対位置モードを設定
                device.Properties.AxisModeAbsolute = true;

                //デバイスの動作
                try { device.Acquire(); }
                catch ( Microsoft.DirectX.DirectXException ) {}
                
                //ジョイスティックのデバイスをリストに追加
                joysticks.Add(device);

                //jsStateにジョイスティックの状態を保存
                joyStates.Add(new JoystickState());
                preJoyStates.Add(new JoystickState());
            }
#endif

			foreach ( DeviceInstance dvc in dInput.GetDevices ( DeviceClass.GameController, DeviceEnumerationFlags.AttachedOnly ) )
			{
				try
				{
					Joystick js = new Joystick ( dInput, dvc.InstanceGuid );
					js.Acquire ();

					//Set Range
					foreach ( DeviceObjectInstance dvcOb in js.GetObjects () )
					{
						if ( 0 != ( dvcOb.ObjectType & ObjectDeviceType.Axis ) ) 
						{
							ObjectProperties op = js.GetObjectPropertiesById ( (int)dvcOb.ObjectType );
							op.SetRange ( -1000, 1000 );
						}
					}

					joysticks.Add ( js );

					//ジョイスティックの状態を保存
					joyStates.Add ( new JoystickState () );
					preJoyStates.Add ( new JoystickState () );
				}
				catch ( DirectInputException )
				{
				}
			}
        }


        //毎回の更新
        public void Update()
        {
            int deviceID = 0;
            foreach ( Device device in joysticks )
            {
                AcquireDeviceState ( deviceID ++ );
            }
        }

        //デバイスIDで指定したジョイスティックの状態を取得する
        private void AcquireDeviceState(int deviceID)
        {
			//以前の状態を保存
            preJoyStates [ deviceID ] = joyStates [ deviceID ];

			//今回の状態を取得
#if false
			try { joysticks [ deviceID ].Poll(); }
            catch ( NotAcquiredException e1)
            {
                System.Diagnostics.Trace.WriteLine(e1.ToString());
                try
                {
                    joysticks[deviceID].Acquire();
                    joysticks[deviceID].Poll();
                }
                catch (InputException e2)
                {
                    System.Diagnostics.Trace.WriteLine(e2.ToString());
                }
            }
            catch (InputException e2)
            {
                System.Diagnostics.Trace.WriteLine(e2.ToString());
            }
#endif
			joysticks [ deviceID ].Poll ();
//            joyStates[deviceID] = joysticks[deviceID].CurrentJoystickState;
            joyStates [ deviceID ] = joysticks [ deviceID ].GetCurrentState ();
        }

        //指定したデバイスID、ボタンIDが押されているかどうか
        public bool IsButton(int deviceID, int buttonID)
        {
			//※ 保存データはboolなので、比較にEqualsを用いない
  //          return joyStates[deviceID].GetButtons()[buttonID].Equals(128);
            return joyStates[deviceID].GetButtons()[buttonID];
        }

        //指定したデバイスID、ボタンIDが押された瞬間かどうか
        public bool IsButtonPush(int deviceID, int buttonID)
        {
			//※ 保存データはboolなので、比較にEqualsを用いない
//            bool b = joyStates[deviceID].GetButtons()[buttonID].Equals(128);
//           bool pb = preJoyStates[deviceID].GetButtons()[buttonID].Equals(128);
            bool b = joyStates[deviceID].GetButtons()[buttonID];
			bool pb = preJoyStates[deviceID].GetButtons()[buttonID];
            return (b && !pb);
        }

        //指定したデバイスIDのアナログ入力の状態（未入力で-1、上が０で時計回りに増加
        public int GetAnalogKey(int deviceID)
        {
//            return joyStates[deviceID].GetPointOfView()[0];
            return joyStates[deviceID].GetPointOfViewControllers ()[0];
        }

        //指定したデバイスIDの上下左右入力
        public bool GetUP(int deviceID) { return (joyStates[deviceID].Y < -500); }
        public bool GetDOWN(int deviceID) { return (joyStates[deviceID].Y > 500); }
        public bool GetLEFT(int deviceID) { return (joyStates[deviceID].X < -500); }
        public bool GetRIGHT(int deviceID) { return (joyStates[deviceID].X > 500); }

        public bool IsPushUP(int deviceID)
        {
            return (joyStates[deviceID].Y < -500 && ! (preJoyStates[deviceID].Y < -500)); 
        }
        public bool IsPushDOWN(int deviceID) 
        {
            return (joyStates[deviceID].Y > 500 && ! (preJoyStates[deviceID].Y > 500)); 
        }
        public bool IsPushLEFT(int deviceID) 
        {
            return (joyStates[deviceID].X < -500 && ! (preJoyStates[deviceID].X < -500)); 
        }
        public bool IsPushRIGHT(int deviceID) 
        {
            return (joyStates[deviceID].X > 500 && ! (preJoyStates[deviceID].X > 500)); 
        }

        //デバイス数を取得する
        public int GetDeviceNum()
        {
            return joysticks.Count;
        }
       

    }   //class JoySthick
}
