using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameSettings
{
	static class Program
	{
		/// <summary>
		/// アプリケーションのメイン エントリ ポイントです。
		/// </summary>
		[STAThread]
		static void Main ()
		{
			Application.EnableVisualStyles ();
			Application.SetCompatibleTextRenderingDefault ( false );
//			Application.Run ( new Form1 () );
//			Application.Run ( new MainForm () );

			MainForm frm = new MainForm ();
			frm.Show ();

			//メインループ
			while ( frm.Created )
			{
				frm.MainLoop ();
				System.Threading.Thread.Sleep ( 10 );
				Application.DoEvents ();
			}
		}
	}
}
