using System.Drawing;

namespace ScriptEditor
{
	public static class DefineColor
	{
		public static Color Get ( int i ) 
		{
			switch ( i )
			{
			case  0: return Color.FromArgb ( 0xff, 0xff, 0xff, 0xff );
			case  1: return Color.FromArgb ( 0xff, 0xb0, 0xb0, 0xf0 );
			case  2: return Color.FromArgb ( 0xff, 0xff, 0xb0, 0xb0 );
			case  3: return Color.FromArgb ( 0xff, 0xc0, 0xf0, 0xc0 );
			case  4: return Color.FromArgb ( 0xff, 0xff, 0xd0, 0xff );
			case  5: return Color.FromArgb ( 0xff, 0xa0, 0xf0, 0xff );
			case  6: return Color.FromArgb ( 0xff, 0x80, 0xd0, 0xa0 );
			case  7: return Color.FromArgb ( 0xff, 0xf0, 0xd0, 0x20 );
			case  8: return Color.FromArgb ( 0xff, 0xa0, 0xa0, 0xb0 );
			case  9: return Color.FromArgb ( 0xff, 0x50, 0x50, 0x50 );
			case 10: return Color.Orange;
			case 11: return Color.DarkGreen;
			case 12: return Color.FromArgb ( 0xff, 0x20, 0xd0, 0xd0 );
			case 13: return Color.BlanchedAlmond;
			case 14: return Color.Brown;
			case 15: return Color.Violet;
			case 16: return Color.Gold;
			case 17: return Color.Pink;
			case 18: return Color.Lavender;
			case 19: return Color.DarkRed;
			case 20: return Color.Olive;
			case 21: return Color.PeachPuff;
			case 22: return Color.MediumVioletRed;
			case 23: return Color.SpringGreen;
			case 24: return Color.OldLace;
			case 25: return Color.Purple;
			}
			return Color.Empty;
		} 

	}
}
