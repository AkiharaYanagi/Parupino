using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace ScriptEditor
{
	using BL_Sqc = BindingList < Sequence >;
	//------------------------------------------------------------
	// アクションバインディングリストから一つを選択するコンボボックス
	//------------------------------------------------------------
	public class CB_ActionList : ComboBox 
	{
		//関連付けられる数値
//		public RefInt PR_RefInt { get; set; } = null;


		//RefIntから設定用デリゲートに変更する

		//設定用デリゲート
		public System.Action < int > SetFunc { get; set; }


		//毎回の初期化
		public void SetCharaData ( Compend cmpd )
		{
			//選択用にコピー
			this.DataSource = new BL_Sqc ( cmpd.Bldct_sqc.GetBindingList() );

			//キャラから保存された値を反映
//			this.SelectedIndex = PR_RefInt.i;
		}

		//関連付け
//		public void Associate ( RefInt ri, System.Action < int > func )
		public void Associate ( System.Action < int > func )
		{
//			PR_RefInt = ri;

			SetFunc = func;
		}

		protected override void OnDropDownClosed ( EventArgs e )
		{
			//キャラに選択された値を反映
//			PR_RefInt.i = this.SelectedIndex;

			//デリゲートにより設定された関数で値を反映
			SetFunc ( this.SelectedIndex );
		}
	}
}
