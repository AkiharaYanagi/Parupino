using System;
using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormBranch0 :Form
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormBranch0 Inst { get; } = new FormBranch0 ();

		//プライベートコンストラクタ
		private FormBranch0 ()
		{
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
		//表示反転
		public void VisFlip ()
		{
			this.Visible = ! this.Visible;
		}
		//---------------------------------------------------------------------

		//親フォーム参照
		public FormMain FormMain { get; set; } = null;

		//データ設定
		public void SetCharaData ( Chara ch )
		{

		}

		//関連付け
		public void Assosiate ( Script scp )
		{

		}
	}
}
