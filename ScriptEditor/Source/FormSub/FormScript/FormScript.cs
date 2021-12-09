using System;

namespace ScriptEditor
{
	//---------------------------------------------------------------------
	//	スクリプトの詳細を設定するフォーム
	//---------------------------------------------------------------------
	public sealed partial class FormScript : EditorForm
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormScript Inst { get; set; } = new FormScript ();
		
		//プライベートコンストラクタ
		private FormScript ()
		{
			InitPt = new System.Drawing.Point ( 0, 230 );
			InitializeComponent ();
			LoadObject ();
		}
		//---------------------------------------------------------------------

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
	
		public void Assosiate ( Script scp, Sequence sqc )
		{
			ctrl_Script1.Assosiate ( scp, sqc );
		}

		public void UpdateData ()
		{
			ctrl_Script1.UpdateData ();
		}
	}
}
