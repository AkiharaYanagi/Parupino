using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;


namespace ScriptEditor
{
	//-------------------------------------------------------------
	//	イメージ選択フォーム
	//-------------------------------------------------------------
	public sealed partial class FormImage : SubForm_Compend
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormImage Inst { get; } = new FormImage ();

		//プライベートコンストラクタ
		private FormImage ()
		{
			InitializeComponent ();
			base.LoadObject ();

			ctrl_Image.SetParent ( this );
		}
		//---------------------------------------------------------------------

		//コントロール
		private Ctrl_Image ctrl_Image = new Ctrl_Image ();

		public void SetCtrl ( Ctrl_Image ctrl )
		{
			ctrl_Image = ctrl;
			this.Controls.Add ( ctrl );
		}

		public override void SetEditCompend ( EditCompend ec )
		{
			ctrl_Image.SetEditCompend ( ec );
			base.SetEditCompend ( ec );
		}

		public void UpdateData ()
		{
			ctrl_Image.UpdateData ();
		}
	}
}
