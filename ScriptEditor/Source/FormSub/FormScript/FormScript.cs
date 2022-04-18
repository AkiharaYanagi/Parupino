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
		
		private _Ctrl_Script ctrl_Script1 = null;

		//プライベートコンストラクタ
		private FormScript ()
		{
			ctrl_Script1 = new _Ctrl_Script ();
			this.Controls.Add ( ctrl_Script1 );

			base.InitPt = new System.Drawing.Point ( 0, 230 );
			InitializeComponent ();
			LoadObject ();
		}
		//---------------------------------------------------------------------

		//編集と表示
		public EditScript EditScript { get; set; } = null;
		public DispScript DispScript { get; set; } = null;
		
		//設定
		public void SetEnvironment ( EditCompend ec, DispScript ds )
		{
			EditScript = ec.EditScript;
			DispScript = ds;

			ctrl_Script1.SetEnvironment ( ec, DispChara.Inst.Disp );
//			ds.SetCtrlScript ( ctrl_Script1 );
		}
	
		public void Assosiate ( Script scp, Sequence sqc )
		{
			ctrl_Script1.Assosiate ( scp );
		}

		public void UpdateData ()
		{
			ctrl_Script1.UpdateData ();
		}
	}
}
