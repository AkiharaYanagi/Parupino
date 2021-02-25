using System;
using System.Windows.Forms;
using System.ComponentModel;

namespace ScriptEditor
{
	using BL_Sqc = BindingList < Sequence >;
	using SetFunc = System.Action < ScriptEditor.Sequence >;
//	using GetFunc = System.Func < int >;

	//------------------------------------------------------------
	// シークエンスバインディングリストから一つを選択するコンボボックス
	//------------------------------------------------------------
	public class CB_SequenceList : ComboBox 
	{
		//表示の更新用
		public DispCompend DispCompend { get; set; } = null;

		//設定用デリゲート
		public SetFunc Set { get; set; } = null;

		//初期化
		public void SetDisp ( DispCompend dc )
		{
			DispCompend = dc;
		}

		//キャラデータ読込時
		public void SetCharaData ( BL_Sqc bl_sqc )
		{
			//データソースに指定
			this.DataSource = bl_sqc;
		}

		//関連付け
		public void Associate ( SetFunc sf )
		{
			Set = sf;
		}

		//閉じたときのイベント
		protected override void OnDropDownClosed ( EventArgs e )
		{
			if ( null == Set ) { return; }

			//キャラに選択された値を反映
			Set ( (Sequence)this.SelectedItem );

			//表示更新
			DispCompend.Disp ();

			base.OnDropDownClosed ( e );
		}
	}

}

