using System;

namespace ScriptEditor
{
	public partial class FormRoute :EditorForm
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormRoute Inst { get; } = new FormRoute ();

		//プライベートコンストラクタ
		private FormRoute ()
		{
			this.InitPt = new System.Drawing.Point ( -200, 220 );
			InitializeComponent ();
		}

		//---------------------------------------------------------------------

		//データ設定
		public void SetCharaData ( Chara ch )
		{
			ctrl_Route1.SetCharaData ( ch );
		}

		//関連付け
		public void Assosiate ( Script scp )
		{

		}
	}
}
