using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Windows.Forms;
using System.Drawing;

using Microsoft.DirectX;
using Microsoft.DirectX.DirectInput;
using DirectInput = Microsoft.DirectX.DirectInput;


namespace ScriptEditor
{
	//-----------------------------------------------------------
	//呼出
	public class TestCharaCall : GameMain
	{
		public override void Move ()
		{
			Form_Test.Instance._Move ();
		}

		public override void Draw ()
		{
			Form_Test.Instance._Draw ();
		}
	}

	//-----------------------------------------------------------
	//Charaを受けて入力と出力のテストを行う
	public class TestChara
	{
		//表示先
		private PictureBox pb = null;
//		public PictureBox Pb { set { pb = value; } }
		private Bitmap bmp = null;

		//キャラ
		private Chara refChara = null;
//		public chara RefChara { set { refChara = value; } }

		//表示位置関連
		private Point ptDisp = new Point ( 0, 0 );		//表示位置
		private Point ptBase = new Point ( 150, 320 );		//基準位置
		private Point ptChara = new Point ( 0, 0 );		//現在位置
		private Point ptVel = new Point ( 0, 0 );		//速度

		//向き(右：正, 左：逆)
		private bool dirRight = true;

		//内部フレーム数
		private int frame = 0;

		//選択アクション
		ScriptEditor.Action _action = null;

		//表示イメージ
		Image img = null;

		//アクション名
		string strAction = null;

		//ｺﾏﾝﾄﾞチェック
		private CheckBranchList _checkBranchList = new CheckBranchList ();
		public CheckBranchList checkBranchList { get { return _checkBranchList; } set { _checkBranchList = value; } }
		
		//デバッグ表示
		public string strDebug { get; set; }


		//コンストラクタ
		public TestChara ( Chara chara, PictureBox pictureBox )
		{
			refChara = chara;
			pb = pictureBox;
		}

		//入力

		//初期化
		public void Init ()
		{
			_action = refChara.behavior.ListSequence[0] as Action;
			_checkBranchList.Init ();
		}


		//フレーム毎動作
		public void Move ()
		{
			//--------------------------------------------------------------------
			//動作条件
			if ( null == refChara ) { return; }
//			_action = refChara.GetAction();
			if ( null == _action ) { return; }
			//--------------------------------------------------------------------

#if false
			//キー入力更新
			KeyInput.Instance.Update ();

			refChara.Update ();
			this.strDebug = refChara.checkBranchList.strDebug;

			if ( KeyInput.Instance.PushKey ( GAME_INPUT.P1_BUTTON1 ) )
			{
				Script script =  refChara.GetScript ();
				if ( 0 >= script.ListBranch.Count ) { return; }
				int index = script.ListBranch[0].IndexAction;
				Chara.SELECTED_SCRIPT ss = new Chara.SELECTED_SCRIPT ( index, 0 );
				refChara.SelectedScript = ss;
				action = refChara.GetAction ();
				frame = 0;
			}

			//コマンド
#endif		

			//--------------------------------------------------------------------
			//ブランチ
			//各フレームにおけるスクリプトでブランチは異なる
			//毎フレームで新しいブランチリストを取得する
			//毎フレームで保存されたキー入力をすべてチェックする

			//毎フレームにブランチのチェック
			//コマンド条件が達成されたら遷移先のアクションに移項する
			_checkBranchList.Update ();
			Action transit = _checkBranchList.GetTransit ( _action.ListScript[frame].ListBranch, dirRight );
			if ( null != transit )
			{
//				editChara.SetAction ( transit );
				_action = transit;
				frame = 0;
			}
			//--------------------------------------------------------------------

			//スクリプト処理
			Script script = _action.ListScript[frame];
			ptChara.X += script.RefVel.x.i;
			ptChara.Y += script.RefVel.y.i;

			//判定処理

			//反映

			//位置
//			ptDisp.X = ptBase.X + script.Pt.X + ptChara.X;
//			ptDisp.Y = ptBase.Y + script.Pt.Y + ptChara.Y;
			ptDisp.X = ptBase.X + script.RefPt.x.i + ptChara.X;
			ptDisp.Y = ptBase.Y + script.RefPt.y.i + ptChara.Y;

			//表示
			img = refChara.ListImageData[ script.imgIndex ].Img;

			//アクション名表示
			strAction = _action.Name;

			//終了時
			if ( frame + 1 >= _action.ListScript.Count )
			{
				//終了時に次アクションに移項
//				refChara.SelectedScript = new chara.SELECTED_SCRIPT ( _action.NextIndex, 0 );
				_action = refChara.behavior[ _action.NextIndex ];
				frame = 0;
			}
			else
			{
				++frame;
			}

//			refChara.SetFrame ( frame );
		}


		//フレーム毎描画
		public void  Draw()
		{
			if ( null == refChara ) { return; }
			if ( null == _action ) { return; }
			if ( null == img ) { return; }

			bmp = new Bitmap ( pb.Width, pb.Height );

			Graphics g = Graphics.FromImage ( bmp );
			g.Clear ( Color.Empty );

			
			//基準線
			Point ptPbImageBase = new Point ( 150, 320 );
			Pen pen0 = new Pen ( Color.White, 4 );
			Pen pen1 = new Pen ( Color.White, 1 );
			g.DrawLine ( pen0, new Point ( ptPbImageBase.X, 0 ), new Point ( ptPbImageBase.X, pb.Height ) );
			g.DrawLine ( pen0, new Point ( 0, ptPbImageBase.Y ), new Point ( pb.Width, ptPbImageBase.Y ) );

			//画像
//			Image img = refChara.GetScript ().img;
			g.DrawImage ( img, ptDisp.X, ptDisp.Y, img.Width, img.Height );

			//デバッグ表示
			g.DrawString ( strDebug, new Font ( "MSゴシック", 12 ), Brushes.White, 10, 10 );
//			g.DrawString ( "ptChara = " + ptChara.ToString (), new Font ( "MSゴシック", 12 ), Brushes.White, 10, 20 );
//			g.DrawString ( "ptDisp = " + ptDisp.ToString (), new Font ( "MSゴシック", 12 ), Brushes.White, 10, 40 );
//			g.DrawString ( "ptBase = " + ptBase.ToString (), new Font ( "MSゴシック", 12 ), Brushes.White, 10, 60 );

			pb.Image = bmp;

			//アクション名
			g.DrawString ( strAction, new Font ( "MSゴシック", 12 ), Brushes.White, 300, 10 );

			//入力表示
			for ( int i = 0; i < 20; ++i )
			{
				switch ( _checkBranchList.ArrayGameKey[i].Direction )
				{
				case GameKey.GameKeyDirection.DIR_1:
					g.DrawRectangle ( pen1, 10 + 0, 10 + 0 + i * 20, 20, 20 );
					g.FillRectangle ( Brushes.White, 10 + 0, 10 + 14 + i * 20, 7, 7 );
					break;
				case GameKey.GameKeyDirection.DIR_2:
					g.DrawRectangle ( pen1, 10 + 0, 10 + 0 + i * 20, 20, 20 );
					g.FillRectangle ( Brushes.White, 10 + 7, 10 + 14 + i * 20, 7, 7 );
					break;
				case GameKey.GameKeyDirection.DIR_3:
					g.DrawRectangle ( pen1, 10 + 0, 10 + 0 + i * 20, 20, 20 );
					g.FillRectangle ( Brushes.White, 10 + 14, 10 + 14 + i * 20, 7, 7 );
					break;
				case GameKey.GameKeyDirection.DIR_4:
					g.DrawRectangle ( pen1, 10 + 0, 10 + 0 + i * 20, 20, 20 );
					g.FillRectangle ( Brushes.White, 10 + 0, 10 + 7 + i * 20, 7, 7 );
					break;
				case GameKey.GameKeyDirection.DIR_6:
					g.DrawRectangle ( pen1, 10 + 0, 10 + 0 + i * 20, 20, 20 );
					g.FillRectangle ( Brushes.White, 10 + 14, 10 + 7 + i * 20, 7, 7 );
					break;
				case GameKey.GameKeyDirection.DIR_7:
					g.DrawRectangle ( pen1, 10 + 0, 10 + 0 + i * 20, 20, 20 );
					g.FillRectangle ( Brushes.White, 10 + 0, 10 + 0 + i * 20, 7, 7 );
					break;
				case GameKey.GameKeyDirection.DIR_8:
					g.DrawRectangle ( pen1, 10 + 0, 10 + 0 + i * 20, 20, 20 );
					g.FillRectangle ( Brushes.White, 10 + 7, 10 + 0 + i * 20, 7, 7 );
					break;
				case GameKey.GameKeyDirection.DIR_9:
					g.DrawRectangle ( pen1, 10 + 0, 10 + 0 + i * 20, 20, 20 );
					g.FillRectangle ( Brushes.White, 10 + 14, 10 + 0 + i * 20, 7, 7 );
					break;
				default:
					break;
				}

				for ( int j = 0; j < 4; ++j )
				{
					if ( _checkBranchList.ArrayGameKey[i].Button[j] == GameKey.GameKeyButton.BTN_ON )
					{
						g.DrawRectangle ( pen0, 30 + j * 20, 10 + i * 20, 20, 20 );
					}
				}
			}	

//			pb.Invalidate ();

			g.Dispose ();


		}

	}
}
