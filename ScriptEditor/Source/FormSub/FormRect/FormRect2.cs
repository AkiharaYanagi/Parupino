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
			this.Controls.Add ( ctrl_AllRect );

			InitializeComponent ();
			base.LoadObject ();
		}
		//---------------------------------------------------------------------

		//枠リスト コントロール
		Ctrl_AllRect ctrl_AllRect = new Ctrl_AllRect ();

		//環境設定
		public void SetEnvironment ( EditCompend ec )
		{
			ctrl_AllRect.SetEnvironment ( ec );
		}

		//関連付け
		public void Assosiate ( Script scp )
		{
			ctrl_AllRect.Assosiate ( scp );
		}

		//更新
		public void UpdateData ()
		{
			ctrl_AllRect.UpdateData ();
		}

	}
}
