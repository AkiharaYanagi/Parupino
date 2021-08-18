using System;
using System.Windows.Forms;
using System.Drawing;

namespace ScriptEditor
{
	public class GameMain
	{
		public Chara Chara { get; set; } = null;
		public Sequence Seq { get; set; } = null;

		public PictureBox Pb { get; set; } = null;
		private Bitmap bmp = null;

		private int frame = 0;
		private readonly Point pt0 = new Point ( 300, 400 );

		public int FPS { get; set; } = 60000;
		public string Trace { get; set; } = "Trace";


		public void SetCharaData ( Chara ch )
		{
			Chara = ch;
		}

		public void Init ()
		{
			frame = 0;
			int W = Pb.Width;
			int H = Pb.Height;
			bmp = new Bitmap ( W, H );
		}
		
		//--------------------------------------------
		public delegate void Setter ( Bitmap bmp );
		public Setter Setter0 { get; set; } = null;

		//--------------------------------------------

		public void Move ()
		{
			++ frame;
			if ( Seq.ListScript.Count <= frame ) { frame = 0; }
		}


		public void Draw ()
		{
			int W = Pb.Width;
			int H = Pb.Height;
			
			Script scp = Seq.ListScript [ frame ];
			

			using ( Graphics g = Graphics.FromImage ( bmp )  )
			using ( Pen PEN0 = new Pen ( Brushes.White, 4.0f ) )
			using ( Font FONT0 = new Font ( "Meiryo", 20.0f ) )
			{
			//クリア
			g.Clear ( Color.Empty );
			
			//基準線
			g.DrawLine ( PEN0, new Point ( 0, pt0.Y ), new Point ( W, pt0.Y ) );
			g.DrawLine ( PEN0, new Point ( pt0.X, 0 ), new Point ( pt0.X, H ) );

			//イメージ
			ImageData imgDt = Chara.behavior.BD_Image.Get ( scp.ImgName );
			g.DrawImage ( imgDt.Img, PointUt.PtAdd ( pt0, scp.Pos ) );

			//[F]
			g.DrawString ( frame.ToString () + "[F]", FONT0, Brushes.White, new Point ( 200, 2 ) );

			//FPS
			float f_fps = FPS / 1000f;
			g.DrawString ( f_fps.ToString ("0.000"), FONT0, Brushes.White, new Point ( 2, 2 ) );
			g.DrawString ( Trace, FONT0, Brushes.White, new Point ( 2, 25 ) );
			}	//using

			//描画
			Pb.Invoke ( Setter0, bmp );
//			Pb.Image = bmp;
		}
	}
}
