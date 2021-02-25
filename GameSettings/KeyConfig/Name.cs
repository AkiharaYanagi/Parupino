﻿//using Microsoft.DirectX;
//using Microsoft.DirectX.DirectInput;
//using DirectInput = Microsoft.DirectX.DirectInput;
using SlimDX.DirectInput;

namespace GameSettings
{
    class StrGameInput
    {
        public string GetName(DeviceInput di)
        {
            switch (di.type)
            {
                //キーボード
 //               case DeviceTypeForGame.KEYBOARD: return KeyToStr(di.keyboard);
                case DeviceTypeForGame.KEYBOARD: return di.keyboard.ToString();
                //ジョイスティック
                case DeviceTypeForGame.JOYSTICK: return GetJoyName(di.joykey);
            }
            return "NO_NAME";   //対応デバイスなし
        }

        public string KeyToStr(Key key)
        {
            string str = "NO_KEY";
            switch (key)
            {
                case Key.Escape: str = "Escape"; break;
                case Key.D1: str = "D1"; break;
                case Key.D2: str = "D2"; break;
                case Key.D3: str = "D3"; break;
                case Key.D4: str = "D4"; break;
                case Key.D5: str = "D5"; break;
                case Key.D6: str = "D6"; break;
                case Key.D7: str = "D7"; break;
                case Key.D8: str = "D8"; break;
                case Key.D9: str = "D9"; break;
                case Key.D0: str = "D0"; break;
                case Key.Minus: str = "Minus"; break;
                case Key.Equals: str = "Equals"; break;
//                case Key.Back: str = "Back"; break;
//                case Key.BackSpace: str = "BackSpace"; break;   //Key.Backと同値
                case Key.Backspace: str = "Backspace"; break;
                case Key.Tab: str = "Tab"; break;
                case Key.Q: str = "Q"; break;
                case Key.W: str = "W"; break;
                case Key.E: str = "E"; break;
                case Key.R: str = "R"; break;
                case Key.T: str = "T"; break;
                case Key.Y: str = "Y"; break;
                case Key.U: str = "U"; break;
                case Key.I: str = "I"; break;
                case Key.O: str = "O"; break;
                case Key.P: str = "P"; break;
                case Key.LeftBracket: str = "LeftBracket"; break;
                case Key.RightBracket: str = "RightBracket"; break;
                case Key.Return: str = "Return"; break;
                case Key.LeftControl: str = "LeftControl"; break;
                case Key.A: str = "A"; break;
                case Key.S: str = "S"; break;
                case Key.D: str = "D"; break;
                case Key.F: str = "F"; break;
                case Key.G: str = "G"; break;
                case Key.H: str = "H"; break;
                case Key.J: str = "J"; break;
                case Key.K: str = "K"; break;
                case Key.L: str = "L"; break;
                case Key.Semicolon: str = "Semicolon"; break;
                case Key.Apostrophe: str = "Apostrophe"; break;
                case Key.Grave: str = "Grave"; break;
                case Key.LeftShift: str = "LeftShift"; break;
                case Key.Backslash: str = "Backslash"; break;
                case Key.Z: str = "Z"; break;
                case Key.X: str = "X"; break;
                case Key.C: str = "C"; break;
                case Key.V: str = "V"; break;
                case Key.B: str = "B"; break;
                case Key.N: str = "N"; break;
                case Key.M: str = "M"; break;
                case Key.Comma: str = "Comma"; break;
                case Key.Period: str = "Period"; break;
                case Key.Slash: str = "Slash"; break;
                case Key.RightShift: str = "RightShift"; break;
                case Key.LeftAlt: str = "LeftAlt"; break;   //Key.LeftMenuと同値
                case Key.Space: str = "Space"; break;
                case Key.CapsLock: str = "CapsLock"; break;     //Key.Capitalと同値
                case Key.ScrollLock: str = "Scroll"; break;
                case Key.F1: str = "F1"; break;
                case Key.F2: str = "F2"; break;
                case Key.F3: str = "F3"; break;
                case Key.F4: str = "F4"; break;
                case Key.F5: str = "F5"; break;
                case Key.F6: str = "F6"; break;
                case Key.F7: str = "F7"; break;
                case Key.F8: str = "F8"; break;
                case Key.F9: str = "F9"; break;
                case Key.F10: str = "F10"; break;
                case Key.NumberLock: str = "Numlock"; break;
                case Key.NumberPadPlus: str = "NumPadPlus"; break;     //Key.Addと同値
                case Key.NumberPadMinus: str = "NumPadMinus"; break;   //Key.Subtractと同値
                case Key.NumberPadPeriod: str = "NumPadPeriod"; break; //Key.Decimalと同値
                case Key.NumberPadStar: str = "NumPadStar"; break;     //Key.Multiplyと同値
                case Key.NumberPadEquals: str = "NumPadEquals"; break;
                case Key.NumberPadEnter: str = "NumPadEnter"; break;
                case Key.NumberPad0: str = "NumPad0"; break;
                case Key.NumberPad1: str = "NumPad1"; break;
                case Key.NumberPad2: str = "NumPad2"; break;
                case Key.NumberPad3: str = "NumPad3"; break;
                case Key.NumberPad4: str = "NumPad4"; break;
                case Key.NumberPad5: str = "NumPad5"; break;
                case Key.NumberPad6: str = "NumPad6"; break;
                case Key.NumberPad7: str = "NumPad7"; break;
                case Key.NumberPad8: str = "NumPad8"; break;
                case Key.NumberPad9: str = "NumPad9"; break;
                case Key.Oem102: str = "OEM102"; break;
                case Key.F11: str = "F11"; break;
                case Key.F12: str = "F12"; break;
                case Key.F13: str = "F13"; break;
                case Key.F14: str = "F14"; break;
                case Key.F15: str = "F15"; break;
                case Key.Kana: str = "Kana"; break;
                case Key.AbntC1: str = "AbntC1"; break;
                case Key.Convert: str = "Convert"; break;
                case Key.NoConvert: str = "NoConvert"; break;
                case Key.Yen: str = "Yen"; break;
                case Key.AbntC2: str = "AbntC2"; break;
 //               case Key.Circumflex: str = "Circumflex"; break;     //Key.PrevTrackと同値
                case Key.AT: str = "At"; break;
                case Key.Colon: str = "Colon"; break;
                case Key.Underline: str = "Underline"; break;
                case Key.Kanji: str = "Kanji"; break;
                case Key.Stop: str = "Stop"; break;
                case Key.AX: str = "AX"; break;
                case Key.Unlabeled: str = "Unlabeled"; break;
                case Key.NextTrack: str = "NextTrack"; break;
                case Key.RightControl: str = "RightControl"; break;
                case Key.Mute: str = "Mute"; break;
                case Key.Calculator: str = "Calculator"; break;
                case Key.PlayPause: str = "PlayPause"; break;
                case Key.MediaStop: str = "MediaStop"; break;
                case Key.VolumeDown: str = "VolumeDown"; break;
                case Key.VolumeUp: str = "VolumeUp"; break;
                case Key.WebHome: str = "WebHome"; break;
                case Key.NumberPadComma: str = "NumPadComma"; break;
                case Key.NumberPadSlash: str = "Divide"; break;     //Key.NumPadSlashと同値
//                case Key.SysRq: str = "SysRq"; break;
                case Key.RightAlt: str = "RightMenu"; break;   //Key.RightAltと同値
                case Key.Pause: str = "Pause"; break;
                case Key.Home: str = "Home"; break;
                case Key.UpArrow: str = "Up"; break;
                case Key.PageUp: str = "PageUp"; break;   //Key.Priorと同値
                case Key.LeftArrow: str = "Left"; break;   //Key.LeftArrowと同値
                case Key.RightArrow: str = "Right"; break;   //Key.RightArrowと同値
                case Key.End: str = "End"; break;
                case Key.DownArrow: str = "Down"; break;     //Key.DownArrowと同値
                case Key.PageDown: str = "PageDown"; break; //Key.Nextと同値
                case Key.Insert: str = "Insert"; break;
                case Key.Delete: str = "Delete"; break;
                case Key.LeftWindowsKey: str = "LeftWindows"; break;
                case Key.RightWindowsKey: str = "RightWindows"; break;
                case Key.Applications: str = "Apps"; break;
                case Key.Power: str = "Power"; break;
                case Key.Sleep: str = "Sleep"; break;
                case Key.Wake: str = "Wake"; break;
                case Key.WebSearch: str = "WebSearch"; break;
                case Key.WebFavorites: str = "WebFavorites"; break;
                case Key.WebRefresh: str = "WebRefresh"; break;
                case Key.WebStop: str = "WebStop"; break;
                case Key.WebForward: str = "WebForward"; break;
                case Key.WebBack: str = "WebBack"; break;
                case Key.MyComputer: str = "MyComputer"; break;
                case Key.Mail: str = "Mail"; break;
                case Key.MediaSelect: str = "MediaSelect"; break;
                default: break;
            }
            return str;
        }

        public string GetJoyStickButtonName(JoyStickKey jk)
        {
            return "Pad" + jk.DeviceID.ToString() + "_key" + jk.ButtonID.ToString();
        }

        public string GetJoyName(JoyStickKey jk)
        {
            switch (jk.ButtonID)
            {
                case DxJoyStick.JOYSTICK_UP:
                    return "Pad" + jk.DeviceID.ToString() + "_UP";
                case DxJoyStick.JOYSTICK_DOWN:
                    return "Pad" + jk.DeviceID.ToString() + "_DOWN";
                case DxJoyStick.JOYSTICK_LEFT:
                    return "Pad" + jk.DeviceID.ToString() + "_LEFT";
                case DxJoyStick.JOYSTICK_RIGHT:
                    return "Pad" + jk.DeviceID.ToString() + "_RIGHT";
            }
            return "Pad" + jk.DeviceID.ToString() + "_key" + jk.ButtonID.ToString();
        }
    }
}
