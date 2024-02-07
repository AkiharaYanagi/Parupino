using System;
using System.Drawing;
using System.Collections.Generic;
using System.Windows.Forms;


namespace ScriptEditor
{
	public partial class FormRoute : SubForm_Compend
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormRoute Inst { get; } = new FormRoute ();

		//プライベートコンストラクタ
		private FormRoute ()
		{
			InitializeComponent ();
			base.InitPt = new Point ( 0, 0 );
			base.LoadObject ();
		}

		//---------------------------------------------------------------------
		//コントロール
		private Ctrl_Scp_Route Ctrl_Scp_Route = new Ctrl_Scp_Route ();	//仮オブジェクト

		//FormMainで実体を確保し、設置する
		public void SetCtrl ( Ctrl_Scp_Route ctrl )
		{
			Ctrl_Scp_Route = ctrl;
			this.Controls.Add ( Ctrl_Scp_Route );
		}


		//データ設定
		public void SetCharaData ( Chara ch )
		{
			Ctrl_Scp_Route.SetCharaData ( ch );
		}

		//環境設定

		//コンペンド編集の切り替え
		public override void SetEditCompend ( EditCompend ec )
		{
			Ctrl_Scp_Route.SetEnvironment ( ec );
			base.SetEditCompend ( ec );
		}
	}
}
