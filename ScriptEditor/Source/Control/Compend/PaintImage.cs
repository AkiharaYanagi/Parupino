using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;
namespace ScriptEditor
{
	using BD_SQC = BindingDictionary < Sequence >;
	using BL_Sqc = BindingList < Sequence >;
	using BD_IMGD = BindingDictionary < ImageData >;

	public sealed class PaintImage 
	{
		//-----------------------------------------------------------
		//キャラデータの参照
		public BD_IMGD ListImage { get; set; } = null;		//イメージリストの参照
		public BL_Sqc ListEf { get; set; } = null;			//Efリストの参照
		public BD_IMGD ListEfImage { get; set; } = null;	//Efイメージリストの参照

		//イメージ表示基準位置 ( X, Y )
		public Point PtPbImageBase { get; set; } = new Point ( 250, 480 );

		//-----------------------------------------------------
		//内部使用
		private PictureBox PB_Image = null;
		private readonly DispRects dispRects = new DispRects ();

		//-----------------------------------------------------
		//コントロールの設定
		public void SetCtrl ( PictureBox pb )
		{
			PB_Image = pb;
		}

		//キャラ読込時
		public void SetCharaData ( BD_IMGD mainImg, BL_Sqc lsEf, BD_IMGD efImg )
		{
			//データ参照
			ListImage = mainImg;
			ListEf = lsEf;
			ListEfImage = efImg;
		}

		//内容表示
		public void Paint ( Script script )
		{
			if ( script is null ) { return; }

			//描画対象
			Bitmap bmp = new Bitmap ( PB_Image.Width, PB_Image.Height );
			Graphics g = Graphics.FromImage ( bmp );

			using ( Pen PenWhite = new Pen ( Color.White, 4 ) )
			{

			//基準線
			g.DrawLine ( PenWhite, new Point ( PtPbImageBase.X, 0 ), new Point ( PtPbImageBase.X, PB_Image.Height ) );
			g.DrawLine ( PenWhite, new Point ( 0, PtPbImageBase.Y ), new Point ( PB_Image.Width, PtPbImageBase.Y ) );

			}
			
			//----------------------------------------
			//イメージID
			//ImageData imgdt = ListImage[ script.ImgIndex ];
			ImageData imgdt = ListImage.Get ( script.ImgName );
			if ( null == imgdt ) { return; }
			Image img = imgdt.Img;
			if ( null == img ) { return; }
			int x = PtPbImageBase.X + script.Pos.X;
			int y = PtPbImageBase.Y + script.Pos.Y;
			g.DrawImage ( img, x, y, img.Width, img.Height );

			//エフェクトID
			foreach ( EffectGenerate efGnrt in script.ListGenerateEf )
			{
				//対象エフェクトとイメージを取得
				int efID = efGnrt.Id;
				if ( ListEf.Count <= efID ) { return; }
				Effect ef = ( Effect ) ListEf[ efID ];
				if ( null == ef ) { continue; }
				Script efSc = ef.ListScript[ 0 ];

				//エフェクトのスクリプトからイメージを取得
				ImageData efImgdt = ListEfImage.Get ( efSc.ImgName );
				if ( null == efImgdt ) { return; }
				Image efImg = efImgdt.Img;
				if ( null == efImg ) { continue; }

				//エフェクトのスクリプトから位置を取得
				Point efPt = PointUt.PtAdd ( PtPbImageBase, efSc.Pos );
				efPt = PointUt.PtAdd ( efPt, efGnrt.Pt );	

				//描画
				g.DrawImage ( efImg, efPt.X, efPt.Y, efImg.Width, efImg.Height );
			}

			//枠
			dispRects.Disp ( g, script, PtPbImageBase );	//枠リストの描画

			//----------------------------------------
			//イメージの反映
			PB_Image.Image = bmp;
			PB_Image.Invalidate ();
		}

	}
}
