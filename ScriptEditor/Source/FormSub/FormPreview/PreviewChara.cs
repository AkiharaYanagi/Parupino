using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Windows.Forms;
using System.Drawing;
using System.Diagnostics;


namespace ScriptEditor
{
	//-----------------------------------------------------------
	//呼出
	//
	//		スレッドからフレームを制御され呼ばれる
	//		親フォームを呼び、動作と描画を行う
	//		（描画コントロール(PictureBox)はメインスレッドであるフォームの制御下にある）
	//
	public class PreviewCharaCall : GameMain
	{
		//デリゲートのため親フォームを参照する
		public Form_ActionPreview form_actPrev { get; set; }

		public override void Move ()
		{
			form_actPrev._Move ();
		}

		public override void Draw ()
		{
			form_actPrev._Draw ();
		}
	}

	//-----------------------------------------------------------
	//アクションのプレビュー
	//
	//		フォームから呼ばれる
	//		コントロールを受け、具体的な動作と描画を行う
	//
	public class PreviewChara
	{
		//描画のため親フォームを参照する
		public Form_ActionPreview form_actPrev { get; set; }

		//Charaを受けてスクリプト内容をフレーム制御によって表示する
		private Chara _chara;
		public Chara Chara { set { _chara = value; } }

		//表示先
		private PictureBox pictureBox;

		//内部フレーム
		private int frame = 0;
		public int Frame { get { return frame; } set { frame = value; } }
		
		//描画フレーム
		private int frameDraw = 0;

		//内部保持アクション
		private Action _action = null;
		private Action _actionDraw = null;

		//動作フラグ
		private bool isMove = false;
		public bool IsMove { get; set; }

		//--------------------------------------------------------------------
		//画像表示関連
		private Point disp = new Point ( 0, 0 );		//表示位置
		private Point pt_base = new Point ( 150, 500 );		//基準位置
		private Point pt = new Point ( 0, 0 );		//現在位置
		private Point vel = new Point ( 0, 0 );		//速度
		private Point acc = new Point ( 0, 0 );		//加速度
		//--------------------------------------------------------------------

		//コンストラクタ
		public PreviewChara ( PictureBox pb )
		{
			pictureBox = pb;
		}

		//初期化
		public void Init ( Chara chara, EditCompend.SELECTED_SCRIPT ss )
		{
			if ( null == chara ) { return; }
			_chara = chara;
			_action = _chara.behavior[ ss.sequence ];
			frame = 0;
			frameDraw = 0;
			disp = pt_base;
			pt = new Point ( 0, 0 );
			vel = new Point ( 0, 0 );
			isMove = false;
		}

		//フレーム毎動作
		public void Move ()
		{
			//--------------------------------------------------------------------
			//動作条件
			if ( null == _action ) { return; }			//アクションが無いとき何もしない
			if ( _action.ListScript.Count <= frame ) { return; }		//フレーム数がスクリプト数を超えているとき何もしない
			Script s = _action.ListScript[ frame ];
			if ( null == s ) { return; }           //スクリプトが無いとき何もしない
			//--------------------------------------------------------------------

			//計算状態
			switch ( s.CalcState )
			{
			case CLC_ST.CLC_ADD: CalcAdd ( s );	break;		//加算
			case CLC_ST.CLC_MAINTAIN: CalcMaintain ( s );	break;	//持続
			case CLC_ST.CLC_SUBSTITUDE:	CalcSubstitude ( s );	break;	//代入
			default:	break;
			}

			//位置制限
			if ( disp.Y >= pt_base.Y ) { disp.Y = pt_base.Y; }

			//描画フレームを保存
			frameDraw = frame;
			_actionDraw = _action;

			//最終フレーム
			if ( frame + 1 >= _action.ListScript.Count )
			{
				int next = _action.NextIndex;
				if ( _chara.behavior.ListSequence.Count <= next ) { return; }
				_action = _chara.behavior.ListSequence[_action.NextIndex] as Action;

				frame = 0;
//				frameDraw = 0;
				pt.X = 0;
				pt.Y = 0;
//				vel.X = 0;
//				vel.Y = 0;
			}
			else
			{
				++frame;
			}

			isMove = true;
		}

		//フレーム毎描画
		public void Draw ()
		{
			//--------------------------------------------------------------------
			//動作条件
			if ( false == isMove ) { return; }		//動作をしていないと待つ
			if ( null == _actionDraw ) { return; }							//アクションが無いとき何もしない
			Script script = _actionDraw.ListScript[ frameDraw ];
			if ( null == script ) { return; }		//スクリプトが無いとき何もしない
//			if ( null == _actionDraw.ListScript[ frameDraw ].img ) { return; }	//イメージが無いとき何もしない
			Image img = _chara.ListImageData[ script.imgIndex ].Img;
			if ( null == img ) { return; }	//イメージが無いとき何もしない
			//--------------------------------------------------------------------

			Bitmap bmp = new Bitmap ( pictureBox.Width, pictureBox.Height );

			Graphics g = Graphics.FromImage ( bmp );
			g.Clear ( Color.Empty );

			//基準線
			Point ptBase = new Point ( 150, 500 );
			Pen pen0 = new Pen ( Color.White, 3 );
			g.DrawLine ( pen0, new Point ( ptBase.X, 0 ), new Point ( ptBase.X, pictureBox.Height ) );
			g.DrawLine ( pen0, new Point ( 0, ptBase.Y ), new Point ( pictureBox.Width, ptBase.Y ) );
			pen0.Dispose ();

			//			g.DrawRectangle ( new Pen ( Brushes.Beige ), new Rectangle ( 0, 100, 100, 200 ) );

			g.DrawImage ( img, disp.X, disp.Y, img.Width, img.Height );

			g.DrawString ( "( " + disp.X.ToString () + ", " + disp.Y + ")", new Font ( "MSゴシック", 12 ), Brushes.White, new PointF ( 10, 10 ) );
			g.DrawString ( _actionDraw.ToString () + "[" + frameDraw.ToString() + "]", new Font ( "MSゴシック", 12 ), Brushes.White, new PointF ( 10, 20 ) );

			g.Dispose ();

			pictureBox.Image = bmp;


//			bmp.Dispose ();
		}

		//加算
		private void CalcAdd ( Script s )
		{
			//加速
			vel.X += s.RefAcc.Get().X;
			vel.Y += s.RefAcc.Get().Y;

			//速度
			vel.X += s.RefVel.Get().X;
			vel.Y += s.RefVel.Get().Y;

			//位置
			disp.X = pt_base.X + s.RefPt.x.i + pt.X;
			disp.Y = pt_base.Y + s.RefPt.y.i + pt.Y;
		}

		//代入
		private void CalcSubstitude ( Script s )
		{
			//加速
			acc = s.RefAcc.Get();

			//速度
			vel.X = s.RefVel.Get().X + acc.X;
			vel.Y = s.RefVel.Get().Y + acc.Y;

			//位置
			disp.X = pt_base.X + s.RefPt.x.i+ vel.X;
			disp.Y = pt_base.Y + s.RefPt.y.i+ vel.Y;
		}

		//維持
		private void CalcMaintain ( Script s )
		{
			//速度
			pt.X += vel.X;
			pt.Y += vel.Y;

			//位置
			disp.X = pt_base.X + s.RefPt.x.i + pt.X;
			disp.Y = pt_base.Y + s.RefPt.y.i + pt.Y;
		}
	}
}
