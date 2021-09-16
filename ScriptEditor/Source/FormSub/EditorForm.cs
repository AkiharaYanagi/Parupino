using System;
using System.Windows.Forms;
using System.Drawing;

namespace ScriptEditor
{
	//---------------------------------------------------------------------
	//@info Show(this);によりメインフォームにより隠れないようにしたが、
	// サブフォームが開いているとメインフォームが閉じない問題
	// -> 常時存在するシングルトンとしてvisibleを切替で解決
	//---------------------------------------------------------------------

	//---------------------------------------------------------------------
	//	ScriptEditor 各種設定フォーム
	//---------------------------------------------------------------------
	//このフォームは１プロセス１フォームなのでシングルトンで実装する
	//・静的で単一な実体化	//static
	//・継承禁止	//sealed
	//・プライベートコンストラクタ
	//---------------------------------------------------------------------

	public class EditorForm : Form
	{
		public EditorForm ()
		{
			this.StartPosition = FormStartPosition.Manual;	//位置を手動にする
			this.ShowInTaskbar = false;	//タスクバーに非表示

			//イベント追加
			this.VisibleChanged += new EventHandler ( EditForm_VisibleChanged );
		}

		//閉じたときに破棄しない
		protected override void OnFormClosing ( FormClosingEventArgs e )
		{
			e.Cancel = true;
			this.Hide ();
		}

		//表示反転
		public void VisFlip ()
		{
			this.Visible = ! this.Visible;
		}

		//親フォーム参照
		public FormMain FormMain { get; set; } = null;
		public Point InitPt { get; set; } = new Point ( 0, 0 );

		//表示
		private void EditForm_VisibleChanged ( object sender, EventArgs e )
		{
			//フォーム位置を親フォームの右端にする
			int x = InitPt.X + FormMain.Location.X + FormMain.Width;
			int y = InitPt.Y + FormMain.Location.Y;
			this.Location = new Point ( x, y );
		}

	}
}
