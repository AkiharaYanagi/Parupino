using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class FormRect2 : EditorForm
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormRect2 Inst { get; set; } = new FormRect2 ();
		
		//プライベートコンストラクタ
		private FormRect2 ()
		{
			//枠リスト コントロール
			this.Controls.Add ( Ctrl_AllRect );

			InitializeComponent ();
			base.LoadObject ();
		}
		//---------------------------------------------------------------------

		//枠リスト コントロール
		public Ctrl_AllRect Ctrl_AllRect { get; set; } = new Ctrl_AllRect ();

		//環境設定
		public void SetEnvironment ( EditCompend ec, DispCompend dc )
		{
			Ctrl_AllRect.SetEnvironment ( ec, ()=>dc.Disp() );
		}

		//関連付け
		public void Assosiate ( Script scp )
		{
			Ctrl_AllRect.Assosiate ( scp );
		}

		//更新
		public void UpdateData ()
		{
			Ctrl_AllRect.UpdateData ();
		}

	}
}
