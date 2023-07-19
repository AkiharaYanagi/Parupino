using System;


namespace ScriptEditor
{

	//各コントロールの統合処理
	public sealed class Ctrl_All
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static Ctrl_All Inst { get; } = new Ctrl_All ();

		//プライベートコンストラクタ
		private Ctrl_All ()
		{
		}
		//---------------------------------------------------------------------

		//コントロール参照
		private _Ctrl_Compend Ctrl_Cmpd_Bhv { get; set; } = new _Ctrl_Compend ();
		private Ctrl_SqcList Ctrl_SqcList_Act { get; set; } = new Ctrl_SqcList ();
		private _Ctrl_Compend Ctrl_Cmpd_Gns { get; set; } = new _Ctrl_Compend ();
		private Ctrl_SqcList Ctrl_SqcList_Efc { get; set; } = new Ctrl_SqcList ();


		public void SetCtrl ( Ctrl_SqcList act, _Ctrl_Compend ctrl_bhv, Ctrl_SqcList efc, _Ctrl_Compend ctrl_gns )
		{
			Ctrl_Cmpd_Bhv = ctrl_bhv;
			Ctrl_SqcList_Act = act;
			Ctrl_Cmpd_Gns = ctrl_gns;
			Ctrl_SqcList_Efc = efc;
		}

		public void SetCharaData ( Chara ch )
		{

		}

		public void UpdateData ()
		{

		}

		public void AllDisp ()
		{
			
		}

		public void AllAssosiate ()
		{
			Ctrl_Cmpd_Bhv.Assosiate ();
		}
	}
}
