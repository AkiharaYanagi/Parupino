using System.Drawing;
using System.Windows.Forms;

namespace ScriptEditor
{
	//---------------------------------------------------------------------
	//	スクリプトの詳細を設定するフォーム
	//---------------------------------------------------------------------
	public sealed partial class FormScript : Form
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormScript Inst { get; set; } = new FormScript ();
		
		//プライベートコンストラクタ
		private FormScript ()
		{
			//フォーム開始位置をマウス位置にする
			this.StartPosition = FormStartPosition.Manual;
			this.ShowInTaskbar = false;	//タスクバーに非表示

			InitializeComponent ();
		}
			
		//閉じたときに破棄しない
		protected override void OnFormClosing ( FormClosingEventArgs e )
		{
			e.Cancel = true;
			this.Hide ();
		}
		//---------------------------------------------------------------------

		//親フォーム参照
		public FormMain FormMain { get; set; } = null;

		//編集と表示
		public EditScript EditScript { get; set; } = null;
		public DispScript DispScript { get; set; } = null;
		
		//設定
		public void SetCtrl ( EditScript es, DispScript ds )
		{
			EditScript = es;
			DispScript = ds;

			ctrl_Script1.SetCtrl ( es );
			ds.SetCtrlScript ( ctrl_Script1 );
		}

		private void FormScript_VisibleChanged ( object sender, System.EventArgs e )
		{
			//フォーム位置を親フォームの右端にする
			int x = FormMain.Location.X + FormMain.Width;
			int y = FormMain.Location.Y + 200;
			this.Location = new Point ( x, y );
		}
		
		public void Assosiate ( Script scp )
		{
			ctrl_Script1.Assosiate ( scp );
		}

		public void UpdateData ( Script scp )
		{
			ctrl_Script1.UpdateData ( scp );
		}
	}
}
