using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SlimDX.DirectInput;


namespace GameSettings
{
	public class DxKeyboard
	{
//		private Device			keyboard;	//キーボードデバイス
		private Keyboard		keyboard;	//キーボード
        private KeyboardState	keyState;	//押された状態
        private BIndexer		preKeyState = new BIndexer();  //一つ前の押された状態

		public DxKeyboard ( DirectInput dInput )
		{
//			keyboard = new Device( );
			keyboard = new Keyboard ( dInput );
			keyboard.Acquire ();
			keyState = keyboard.GetCurrentState ();
			preKeyState.SetKeyState ( keyState );
		}

		public void Update ()
		{
            preKeyState.SetKeyState ( keyState );
			keyState = keyboard.GetCurrentState();
		}

        //押された状態のキーボードを返す
        public Key GetKeyBoard()
        {
#if false
			Key k;
            for (k = Key.D1; k <= Key.MediaSelect; k++)
            {
                if (k == Key.Tab || k == Key.Return) continue;
                if ( keyState.IsPressed ( k ) ) { break; }
            }
            return Key.Escape;
#endif
			IList<Key> lkey = keyState.PressedKeys;
			if ( 0 == lkey.Count ) { return Key.Escape; }
			Key k = lkey [ 0 ];
			if ( Key.Tab == k || Key.Return == k ) { return Key.Escape; }
			return  k;
       }

        //押された瞬間のキーボードを返す
        //戻値：入力があったキー（Escape以外）。何も入力が無いときKey.Escape
        public Key PushKeyBoard()
        {
 #if false
           Key k;
            for (k = Key.D1; k <= Key.MediaSelect; k++)     //先頭のEscは除く
            {
                if ( k == Key.Tab || k == Key.Return ) continue;
                if ( keyState.IsPressed ( k ) && ! preKeyState [ k ] )
                {
                    return k;
                }
            }
            return Key.Escape;  //何も入力が無いときEscapeを返す
 #endif
			IList<Key> lkey = keyState.PressedKeys;
			if ( 0 == lkey.Count ) { return Key.Escape; }
			Key k = lkey [ 0 ];
			if ( Key.Tab == k || Key.Return == k ) { return Key.Escape; }
            if ( preKeyState [ k ] ) { return Key.Escape; }	//押しっぱなしのときは否定
			return  k;
       }

	}
}
