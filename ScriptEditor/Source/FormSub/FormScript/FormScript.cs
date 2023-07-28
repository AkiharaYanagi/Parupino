using System;
using System.Drawing;


namespace ScriptEditor
{
	//---------------------------------------------------------------------
	//	スクリプトの詳細を設定するフォーム
	//---------------------------------------------------------------------
	public sealed partial class FormScript : SubForm_Compend
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

			base.InitPt = new Point ( 0, 230 );
			InitializeComponent ();
			LoadObject ();
		}
		//---------------------------------------------------------------------

		//編集と表示
		public EditScript EditScript { get; set; } = null;
//		public DispScript DispScript { get; set; } = null;

		public System.Action _Assosiate { get; set; } = () => {};
		public System.Action _UpdateData { get; set; } = () => {};
		public System.Action AllDisp { get; set; } = () => {};
		
		//設定
//		public void SetEnvironment ( EditCompend ec, DispScript ds )
		public void SetEnvironment ( EditCompend ec )
		{
			EditScript = ec.EditScript;
//			DispScript = ds;

			ctrl_Script1.SetEnvironment ( ec, DispChara.Inst.Disp );
//			ds.SetCtrlScript ( ctrl_Script1 );
		}
	
		public void Assosiate ( Script scp, Sequence sqc )
		{
			//ctrl_Script1.Assosiate ( scp );
			_Assosiate ();
		}

		public void UpdateData ()
		{
			//ctrl_Script1.UpdateData ();
			_UpdateData ();
		}
	}
}
