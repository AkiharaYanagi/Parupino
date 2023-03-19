using System.Drawing;
using System.Collections.Generic;

namespace ScriptEditor
{
	using L_Rct = List < Rectangle >;

	public class DispRects
	{
		private readonly Color clrCRect = Color.FromArgb( 0x400000ff );
		private readonly Color clrHRect = Color.FromArgb( 0x4000ff00 );
		private readonly Color clrARect = Color.FromArgb( 0x40ff0000 );
		private readonly Color clrORect = Color.FromArgb( 0x40ffff00 );

		public void Disp ( Graphics g, Script s ,Point ptBase )
		{
			_DispRects ( g, s.ListCRect, ptBase, clrCRect );
			_DispRects ( g, s.ListHRect, ptBase, clrHRect );
			_DispRects ( g, s.ListARect, ptBase, clrARect );
			_DispRects ( g, s.ListORect, ptBase, clrORect );
		}

		private void _DispRects ( Graphics g, L_Rct lRect, Point ptBase, Color clr )
		{
			using ( Brush br = new SolidBrush ( clr ) )
			{
			foreach ( Rectangle r in lRect )
			{
				int x = ptBase.X + r.X;
				int y = ptBase.Y + r.Y;
				Rectangle drawRect = new Rectangle ( x, y, r.Width, r.Height );
				g.FillRectangle ( br, drawRect );
			}
			}
		}

	}
}
