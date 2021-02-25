using System;
using System.Collections.Generic;
using System.Windows.Forms;

//using Microsoft.DirectX;
//using Microsoft.DirectX.DirectInput;

namespace GameSettings
{
	public partial class MainForm : Form
	{
		private DxInput dxInput = new DxInput ();            //DirectInput管理

		private GameInput nRadio; //ラジオボタン位置
		private Dictionary<GameInput, TextBox> dc_gameInput_tb = null;
		private Dictionary<GameInput, RadioButton> dc_gameInput_rb = null;

		private KeySetting keySetting = new KeySetting ();  //キー設定

		public void LoadKeyConfig ()
		{
			//テキストボックスの参照
			dc_gameInput_tb = new Dictionary < GameInput, TextBox >
			{
				{ GameInput.P1_UP, textBox1 },
				{ GameInput.P1_DOWN, textBox2 },
				{ GameInput.P1_LEFT, textBox3 },
				{ GameInput.P1_RIGHT, textBox4 },
				{ GameInput.P1_KEY1, textBox5 },
				{ GameInput.P1_KEY2, textBox6 },
				{ GameInput.P1_KEY3, textBox7 },
				{ GameInput.P1_KEY4, textBox8 },
				{ GameInput.P2_UP, textBox9 },
				{ GameInput.P2_DOWN, textBox10 },
				{ GameInput.P2_LEFT, textBox11 },
				{ GameInput.P2_RIGHT, textBox12 },
				{ GameInput.P2_KEY1, textBox13 },
				{ GameInput.P2_KEY2, textBox14 },
				{ GameInput.P2_KEY3, textBox15 },
				{ GameInput.P2_KEY4, textBox16 }
			};

			//ラジオボタンの参照
			dc_gameInput_rb = new Dictionary < GameInput, RadioButton >
			{
				{ GameInput.P1_UP, radioButton1 },
				{ GameInput.P1_DOWN, radioButton2 },
				{ GameInput.P1_LEFT, radioButton3 },
				{ GameInput.P1_RIGHT, radioButton4 },
				{ GameInput.P1_KEY1, radioButton5 },
				{ GameInput.P1_KEY2, radioButton6 },
				{ GameInput.P1_KEY3, radioButton7 },
				{ GameInput.P1_KEY4, radioButton8 },
				{ GameInput.P2_UP, radioButton9 },
				{ GameInput.P2_DOWN, radioButton10 },
				{ GameInput.P2_LEFT, radioButton11 },
				{ GameInput.P2_RIGHT, radioButton12 },
				{ GameInput.P2_KEY1, radioButton13 },
				{ GameInput.P2_KEY2, radioButton14 },
				{ GameInput.P2_KEY3, radioButton15 },
				{ GameInput.P2_KEY4, radioButton16 }
			};

			//データファイルの読込
			keySetting.Read ();
			Disp ();

			//ラジオボタンの位置
			nRadio = GameInput.P1_UP;

			//タブストップの停止
			tabControl1.TabStop = false;
		}

		//タブの選択
		private void tabControl1_Selecting ( object sender, TabControlCancelEventArgs e )
		{
			switch ( tabControl1.SelectedIndex )
			{
			case 0: break;	//メイン
			case 1:
				radioButton1.Select ();
				radioButton1.Checked = true;
			break;	//キーコンフィグ
			default: break;
			}
		}

		//メインループ
		public void MainLoop ()
		{
			StrGameInput strGameInput = new StrGameInput ();    //名前検索オブジェクト

			dxInput.Update ();   //毎回の入力の更新
			DeviceInput di = dxInput.GetInput ();

			//入力があったらテキストボックスを変更して次へ
			if ( di.type != DeviceTypeForGame.NODEVICE )
			{
				//キー設定保存
				keySetting.Set ( nRadio, di );

				//表示文字列に反映 ラジオボタンの位置を一つ進める
//              knTextBox[nRadio++].Text = di.keyboard.ToString();
				dc_gameInput_tb[ nRadio++ ].Text = strGameInput.GetName ( di );

				//ラジオボタン位置のループ
				if ( nRadio == GameInput.NUM_KEYNAME ) { nRadio = GameInput.P1_UP; }
				dc_gameInput_rb[ nRadio ].Checked = true;
			}
		}

		//表示
		public void Disp ()
		{
			foreach ( GameInput gInput in Enum.GetValues ( typeof ( GameInput ) ) )
			{
				if ( gInput == GameInput.NUM_KEYNAME ) { break; }
				dc_gameInput_tb[ gInput ].Text = keySetting.Get ( gInput ).ToString ();
			}
		}

		//ラジオボタン共通イベント　カーソルキーでフォーカスの移動を禁止する
		private void radioButton1_PreviewKeyDown ( object sender, PreviewKeyDownEventArgs e )
		{
			switch ( e.KeyCode )
			{
			case Keys.Up:
			case Keys.Down:
			case Keys.Left:
			case Keys.Right:
				e.IsInputKey = true;
				break;
			}
		}

		//ラジオボタンの選択(各ボタンのイベントから共通で呼ばれる)
		private void radioButton1_CheckedChanged ( object sender, EventArgs e )
		{
			//入力した次の位置に変更する
			RadioButton rb = ( RadioButton ) sender;
			foreach ( KeyValuePair<GameInput, RadioButton> kvp in dc_gameInput_rb )
			{
				if ( kvp.Value == rb )
				{
					nRadio = kvp.Key;
					break;
				}
			}
		}

		//タブコントロールでキー入力
		private void tabControl1_PreviewKeyDown ( object sender, PreviewKeyDownEventArgs e )
		{
			switch ( e.KeyCode )
			{
			case Keys.Up:
			case Keys.Down:
			case Keys.Left:
			case Keys.Right:
					e.IsInputKey = true;
					break;
			}

		}

		//決定ボタン
		private void btnKeyConfigOK_Click ( object sender, EventArgs e )
		{
			keySetting.Write ();
			this.Close ();
		}

		//キャンセルボタン
		private void btnKeyConfigCancel_Click ( object sender, EventArgs e )
		{
			keySetting.Read ();
			Disp ();
			this.Close ();
		}
	}
}
