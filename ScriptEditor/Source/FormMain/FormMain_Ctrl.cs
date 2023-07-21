using System.Windows.Forms;


namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		private Ctrl_SqcList ctrl_SqcList_Act = new Ctrl_SqcList ();	//シークエンスリスト・アクション
		private _Ctrl_Compend ctrl_cmpd_bhv = new _Ctrl_Compend ();		//コントロール・ビヘイビア
		private Ctrl_FormBtn_v ctrl_fmBtn_bhv = new Ctrl_FormBtn_v ();		//フォームボタン
		
		private Ctrl_SqcList ctrl_SqcList_Efc = new Ctrl_SqcList ();	//シークエンスリスト・エフェクト
		private _Ctrl_Compend ctrl_cmpd_gns = new _Ctrl_Compend ();		//コントロール・ガーニッシュ
		private Ctrl_FormBtn_v ctrl_fmBtn_gns = new Ctrl_FormBtn_v ();		//フォームボタン


		//コントロール登録
		public void LoadCtrl ()
		{
			Ctrl_All.Inst.SetCtrl
			(
				ctrl_SqcList_Act, 
				ctrl_cmpd_bhv, 
				ctrl_SqcList_Ef, 
				ctrl_cmpd_gns
			);
		}
	}
}
