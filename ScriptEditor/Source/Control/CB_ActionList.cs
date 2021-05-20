using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace ScriptEditor
{
	using BL_Sqc = BindingList < Sequence >;
	//------------------------------------------------------------
	// コンペンドから一つを選択するコンボボックス
	//------------------------------------------------------------
	public class CB_ActionList : ComboBox 
	{
		//選択時、元データに値を反映するためのデリゲート
		public System.Action < int > SetFunc { get; set; }

		//データ読込時の初期化
		public void SetCharaData ( Compend cmpd )
		{
			//選択用に値をコピー
			this.DataSource = new BL_Sqc ( cmpd.Bldct_sqc.GetBindingList() );
		}

		//関連付け
		public void Associate ( System.Action < int > func )
		{
			SetFunc = func;
		}

		protected override void OnDropDownClosed ( EventArgs e )
		{
			//デリゲートにより設定された関数で値を元データに反映
			SetFunc ( this.SelectedIndex );
		}
	}
}
