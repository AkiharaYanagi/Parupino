using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;

namespace ScriptEditor
{
	public partial class SqcBoard : UserControl
	{
		//アクションもしくはエフェクトの編集と表示を参照する
		//外部でビヘイビアとガーニッシュのいずれかを指定してSet()する
		public EditCompend EditCompend { get; set; } = null;

		//参照
		public Sequence Sqc = null;

		//グループ数
		private int nGroup = 0;

		//-----------------------------------------------------------------------------
		//内部使用定数
		private const int W = 20;	//升幅
		private const int H = 20;	//升高
		private const int BX = 100;	//基準X
		private const int BY = 20;	//基準Y

		//内部使用リソース (解放はDispose()で行う)
		private Pen PEN_BAR = new Pen ( Color.FromArgb ( 0x80, 0x80, 0xff ), 1 );
		private Pen PEN_BASE_BAR = new Pen ( Color.FromArgb ( 0xa0, 0xa0, 0xa0 ), 1 );
		private Pen PEN_SELECTED = new Pen ( Color.FromArgb ( 0x00, 0x00, 0xff ), 1.1f );
		private SolidBrush BRUSH_0 = new SolidBrush ( Color.FromArgb ( 0xff, 0xd0, 0xff, 0xd0 ) );
		private StringFormat STR_FMT = new StringFormat ();	//文字列の体裁

		//-----------------------------------------------------------------------------
		public SqcBoard ()
		{
			STR_FMT.Alignment = StringAlignment.Center;	//文字列の中央揃え(水平)
			STR_FMT.LineAlignment = StringAlignment.Center;	//文字列の中央揃え(垂直)

			this.BackColor = SystemColors.Control;

			InitializeComponent ();
		}

		//コントロールの設定
		public void SetCtrl ( EditCompend ec )
		{
			EditCompend = ec;
		}

		public void Set ( Sequence sqc )
		{
			Sqc = sqc;
		}

		//-----------------------------------------------------------------------------
		//描画
		private void SqcBoard_Paint ( object sender, PaintEventArgs e )
		{
			pictureBox1.Invalidate ();
		}

		private void pictureBox1_Paint ( object sender, PaintEventArgs e )
		{
			//オブジェクトが設定されていないときデフォルトの表示
			if ( null == Sqc ) { pictureBox1_Paint_Default ( sender, e ); return; }
			if ( null == Sqc.ListScript ) { pictureBox1_Paint_Default ( sender, e ); return;}

			//---------------------------------------------------------
			//共通基準値
			Graphics g = e.Graphics;
			List<Script> ls = Sqc.ListScript;

			//大きさ
			int minWidth = 1000;
			int scWidth = 100+BX + ( ls.Count + 2 ) * W;
			this.Width = ( minWidth < scWidth ) ? scWidth: minWidth;
			this.Height = 80 + BY + ( 2 * H );

			//大きさの一時保存
			int TW = this.Width;
			int TH = this.Height;

			//選択
			int selectedScript = EditCompend.SelectedScriptIndex;
			int selectedSpanStart = EditCompend.SelectedSpanStart;
			int selectedSpanEnd = EditCompend.SelectedSpanEnd;

			//---------------------------------------------------------
			//フレーム表示部分の背景(存在しない部分を一括描画)
			g.FillRectangle ( Brushes.LightGray, BX, 0, TW - BX, TH );

			//---------------------------------------------------------
			//キャラデータの表示
			g.FillRectangle ( Brushes.AliceBlue, BX, H, W * ls.Count, H );

			//---------------------------------------------------------
			//選択スパン表示
			int wSpan = W * ( 1 + selectedSpanEnd - selectedSpanStart );
			int xSpan = BX + W * selectedSpanStart;
			Rectangle rectSpan = new Rectangle ( xSpan, BY, wSpan, H );
			g.FillRectangle ( BRUSH_0, rectSpan );

			//---------------------------------------------------------
			//グループ表示
			int count = 0;
			foreach ( Script s in Sqc.ListScript )
			{
				Rectangle r = new Rectangle ( BX + (W * count ++), 0, W, H );
				g.FillRectangle ( new SolidBrush ( DefineColor.Get ( s.Group ) ), r );
			}

			//スクリプト内容
			int count0 = 0;
			foreach ( Script s in Sqc.ListScript )
			{
				Color c_0 =  Color.FromArgb ( 0xff, 0xff, 0xff );
				
				//攻撃枠
				Rectangle r_a = new Rectangle ( BX + (W * count0), W * 2, W, H );
				Color c_a = ( 0 < s.ListARect.Count ) ? Color.FromArgb ( 0xff, 0xe0, 0xe0 ) : c_0;
				g.FillRectangle ( new SolidBrush ( c_a ), r_a );
				
				//相殺枠
				Rectangle r_o = new Rectangle ( BX + (W * count0), W * 3, W, H );
				Color c_o = ( 0 < s.ListORect.Count ) ? Color.FromArgb ( 0xff, 0xff, 0xe0 ) : c_0;
				g.FillRectangle ( new SolidBrush ( c_o ), r_o );
				
				//EfGnrt
				Rectangle r_eg = new Rectangle ( BX + (W * count0), W * 4, W, H );
				Color c_eg = ( 0 < s.ListGenerateEf.Count ) ? Color.FromArgb ( 0xc0, 0xff, 0xff ) : c_0;
				g.FillRectangle ( new SolidBrush ( c_eg ), r_eg );

				++ count0;
			}


			//---------------------------------------------------------
			//フレーム数
			for ( int i = 0; i < TW / W; ++i )
			{
				Rectangle r = new Rectangle ( BX + i * W, H, W, H );
				g.DrawString ( i.ToString (), this.Font, Brushes.Gray, r, STR_FMT );
			}

			//文字
			Rectangle rs0 = new Rectangle ( 0, 0, BX, H );
			g.DrawString ( "Group", Font, Brushes.Gray, rs0, STR_FMT );
			Rectangle rs1 = new Rectangle ( 0, H, BX, H );
			g.DrawString ( "Frame", Font, Brushes.Gray, rs1, STR_FMT );
			Rectangle rs2 = new Rectangle ( 0, H * 2, BX, H );
			g.DrawString ( "ARect", Font, Brushes.LightCoral, rs2, STR_FMT );
			Rectangle rs3 = new Rectangle ( 0, H * 3, BX, H );
			g.DrawString ( "ORect", Font, Brushes.Goldenrod, rs3, STR_FMT );
			Rectangle rs4 = new Rectangle ( 0, H * 4, BX, H );
			g.DrawString ( "EfGnrt", Font, Brushes.Goldenrod, rs4, STR_FMT );

			//---------------------------------------------------------
			//基準線
			for ( int i = 0; i < TW / W; ++ i )	//縦線
			{
				int bx0 = ( BX + W ) + W * i;
				g.DrawLine ( PEN_BASE_BAR, bx0, H, bx0, (2+3) * H );
			}
			for ( int i = 0; i < 3; ++ i )	//横線
			{
				int by0 = BY + H * (i + 2);
				g.DrawLine ( PEN_BASE_BAR, 0, by0, TW, by0 );
			}
			g.DrawLine ( PEN_BAR, BX, 0, BX, TH );
			g.DrawLine ( PEN_BAR, 0, BY, TW, BY );
			g.DrawLine ( PEN_BAR, 0, 0, TW, 0 );
			g.DrawLine ( PEN_BAR, 0, BY + H, TW, BY + H );

			//---------------------------------------------------------
			//選択位置表示
			g.DrawRectangle ( Pens.Firebrick, BX + selectedScript * W, H, W, H );	//フレーム選択
		}

		//オブジェクトが設定されていない状態でのIDE表示
		private void pictureBox1_Paint_Default ( object sender, PaintEventArgs e )
		{
			Graphics g = e.Graphics;

			//枡個数
			int NW = 20; int NH = 2;

			//コントロールの大きさ
			this.Width = BX + ( NW ) * W;
			this.Height = 80 + BY + ( NH ) * H;

			//一時保存
			int TW = this.Width;
			int TH = this.Height;

			//フレーム表示部分の背景(存在しない部分を一括描画)
			g.FillRectangle ( Brushes.LightGray, BX, BY + H, TW - BX, TH - BY );

			//---------------------------------------------------------
			//選択スパン表示
			int wSpan = W;
			int xSpan = BX + W;
			Rectangle rectSpan = new Rectangle ( xSpan, BY, wSpan, H );
			g.FillRectangle ( BRUSH_0, rectSpan );

			//---------------------------------------------------------
			//グループ表示

			//---------------------------------------------------------
			//フレーム数
			for ( int i = 0; i < TW / W; ++i )
			{
				Rectangle r = new Rectangle ( BX + i * W, H, W, H );
				g.DrawString ( i.ToString (), this.Font, Brushes.Gray, r, STR_FMT );
			}
			
			Rectangle rs0 = new Rectangle ( 0, 0, BX, H );
			g.DrawString ( "Group", Font, Brushes.Gray, rs0, STR_FMT );
			Rectangle rs1 = new Rectangle ( 0, H, BX, H );
			g.DrawString ( "Frame", Font, Brushes.Gray, rs1, STR_FMT );
			Rectangle rs2 = new Rectangle ( 0, H * 2, BX, H );
			g.DrawString ( "ARect", Font, Brushes.LightCoral, rs2, STR_FMT );
			Rectangle rs3 = new Rectangle ( 0, H * 3, BX, H );
			g.DrawString ( "ORect", Font, Brushes.Goldenrod, rs3, STR_FMT );

			//---------------------------------------------------------
			//基準線
			for ( int i = 0; i < TW / W; ++i )	//縦線
			{
				int bx0 = ( BX + W ) + W * i;
				g.DrawLine ( PEN_BASE_BAR, bx0, H, bx0, (NH+2) * H );
			}
			for ( int i = 0; i < NH; ++i )	//横線
			{
				int by0 = BY + H * (i+2);
				g.DrawLine ( PEN_BASE_BAR, 0, by0, TW, by0 );
			}
			g.DrawLine ( PEN_BAR, BX, 0, BX, TH );
			g.DrawLine ( PEN_BAR, 0, BY, TW, BY );
			g.DrawLine ( PEN_BAR, 0, 0, TW, 0 );
			g.DrawLine ( PEN_BAR, 0, BY + H, TW, BY + H );

			//---------------------------------------------------------
			//選択位置表示
			g.DrawRectangle ( Pens.Firebrick, BX + W, H, W, H );	//フレーム選択
		}

		//----------------------------------------------------------------------------------
		//	マウスイベント
		//----------------------------------------------------------------------------------
		bool bDrag = false;	//ドラッグ中

		//マウス位置からフレーム表の升目位置を取得する
		private Point GetCell () 
		{
			//マウス位置をコントロールのクライアント位置に直す
			Point pt = this.PointToClient ( Cursor.Position );
			if ( pt.X < BX || pt.Y < BY ) { return new Point ( 0, 0 ); }

			//升目に合わせる
			int pos_x = ( pt.X - BX ) / W;
			int pos_y = ( pt.Y - BY ) / H;
			STS_TXT.Trace ( pos_x.ToString() + "," + pos_y.ToString () );
			return new Point ( pos_x, pos_y );
		}

		private void pictureBox1_MouseDown ( object sender, MouseEventArgs e )
		{
			Point pos = GetCell ();
			EditCompend.SelectFrame ( pos.X );

			EditCompend.SelectedSpanStart = pos.X;
			EditCompend.SelectedSpanEnd = pos.X;
			bDrag = true;

			pictureBox1.Invalidate ();
		}

		private void pictureBox1_MouseMove ( object sender, MouseEventArgs e )
		{
			if ( bDrag )
			{
				Point pos = GetCell ();
				EditCompend.SelectedSpanEnd = pos.X;
				pictureBox1.Invalidate ();
			}
		}

		private void pictureBox1_MouseUp ( object sender, MouseEventArgs e )
		{
			Point pos = GetCell ();
			bDrag = false;
			pictureBox1.Invalidate ();
		}

		//----------------------------------------------------------------------------------
		//	グループ
		//----------------------------------------------------------------------------------
		//作成
		private void button1_Click ( object sender, System.EventArgs e )
		{
			EditCompend ec = EditCompend;
			EditScript es = ec.EditScript;

			int start = ec.SelectedSpanStart;
			int end = ec.SelectedSpanEnd;

			List < Script > lsScp = Sqc.ListScript;
			es.MakeGroup ( lsScp, start, end );

			pictureBox1.Invalidate ();
		}

		//解除
		private void button2_Click ( object sender, System.EventArgs e )
		{
			int count = 0;
			int group = 0;
			//グループ解除対象を取得
			foreach ( Script s in Sqc.ListScript )
			{
				if ( EditCompend.SelectedScriptIndex == count )
				{
					group = s.Group;
					break;
				}
				++ count;
			}
			if ( count == Sqc.ListScript.Count ) { return; }

			//対象グループを解除
			foreach ( Script s in Sqc.ListScript )
			{
				if ( group == s.Group )
				{
					s.Group = 0;
				}
			}
			-- nGroup;

			pictureBox1.Invalidate ();
		}

		//複製
		private void Btn_Paste_Click ( object sender, System.EventArgs e )
		{
			EditCompend ec = EditCompend;
			EditScript es = ec.EditScript;
			es.PasteGroup ( ec.SelectedScript );
		}

	}
}
