using System.Windows.Forms;


namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		Ctrl_SqcList ctrl_SqcList_Act = new Ctrl_SqcList ();	//シークエンスリスト・アクション
		_Ctrl_Compend ctrl_cmpd_bhv = new _Ctrl_Compend ();		//コントロール・ビヘイビア
		
		Ctrl_SqcList ctrl_SqcList_Efc = new Ctrl_SqcList ();	//シークエンスリスト・エフェクト
		_Ctrl_Compend ctrl_cmpd_gns = new _Ctrl_Compend ();		//コントロール・ガーニッシュ


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
