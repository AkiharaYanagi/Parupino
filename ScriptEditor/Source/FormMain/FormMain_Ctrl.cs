using System.Windows.Forms;


namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//-------------------------------------------------------
		//各コントロール 実体
#if false
		private Ctrl_SqcList ctrl_SqcList_Act = new Ctrl_SqcList ();	//シークエンスリスト・アクション
		private _Ctrl_Compend ctrl_cmpd_bhv = new _Ctrl_Compend ();		//コントロール・ビヘイビア
		private Ctrl_FormBtn_v ctrl_fmBtn_bhv = new Ctrl_FormBtn_v ();	//フォームボタン
		
		private Ctrl_SqcList ctrl_SqcList_Efc = new Ctrl_SqcList ();	//シークエンスリスト・エフェクト
		private _Ctrl_Compend ctrl_cmpd_gns = new _Ctrl_Compend ();		//コントロール・ガーニッシュ
		private Ctrl_FormBtn_v ctrl_fmBtn_gns = new Ctrl_FormBtn_v ();	//フォームボタン
#endif
		private Ctrl_CmdList ctrl_Cmd = new Ctrl_CmdList ();

		//-------------------------------------------------------


		//コントロール登録
		public void LoadCtrl ()
		{
#if false
			Ctrl_All.Inst.SetCtrl
			(
				ctrl_SqcList_Act, 
				ctrl_cmpd_bhv, 
				ctrl_SqcList_Ef, 
				ctrl_cmpd_gns
			);
#endif

#if false
			//コントロールの全体監理に渡す
			All_Ctrl.Inst.SqcList_Act = ctrl_SqcList_Act;
			All_Ctrl.Inst.Compend_Bhv = ctrl_cmpd_bhv;
			All_Ctrl.Inst.SqcList_Efc = ctrl_SqcList_Efc;
			All_Ctrl.Inst.Compend_Gns = ctrl_cmpd_gns;
#endif
			All_Ctrl.Inst.Cmd = ctrl_Cmd;
		}
	}
}
