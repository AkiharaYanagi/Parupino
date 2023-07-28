﻿using System.Windows.Forms;
using System.IO;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//更新
		public void UpdateData ()
		{
			Ctrl_All.Inst.UpdateData ();
			Disp ();
		}

		//==================================================================================
		//表示
		//==================================================================================
		//手動全体表示
		private void Disp ()
		{
			//DispChara.Inst.Disp ();
			Ctrl_All.Inst.AllDisp ();
		}
		//イベント
		private void FormMain_Paint ( object sender, PaintEventArgs e )
		{
//			DispChara.Inst.Disp ();
		}

		//タイトルバーテキスト更新
		private void ReloadTitleBarText ()
		{
			this.Text = Directory.GetCurrentDirectory() + "\\" + stgs.LastFilepath + " - " + formText;
		}
	}
}
