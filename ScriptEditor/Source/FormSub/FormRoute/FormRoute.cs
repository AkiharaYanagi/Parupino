using System;
using System.Drawing;


namespace ScriptEditor
{
	public partial class FormRoute :EditorForm
	{
		//コントロール(ルート)
		EditListbox < TName > ED_Route = new EditListbox < TName > ();

		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormRoute Inst { get; } = new FormRoute ();

		//プライベートコンストラクタ
		private FormRoute ()
		{
			this.InitPt = new Point ( 0, 0 );
			InitializeComponent ();
			LoadObject ();

			Cb_Route.DisplayMember = "Name";

			//==============================================================
			//エディットリストボックスの設定

			//----------------------------------
			//コントロール(ルート)
			ED_Route.Location = new Point ( 3, 0 );
			this.Controls.Add ( ED_Route );

			//追加時
			ED_Route.Add = ()=>
			{
			};
			//選択変更時
			ED_Route.SelectedIndexChanged = ()=>
			{
			};

			//==============================================================

		}

		//---------------------------------------------------------------------

		//データ設定
		public void SetCharaData ( Chara ch )
		{
			//コンボボックスに登録
			Cb_Route.DataSource = ch.BD_Route.GetBindingList ();
			Cb_Route.DisplayMember = "Name";
		}

		//ルートの設定
		public void SetRoute ( Route rut )
		{
		}

		//関連付け
		public Script Script { get; set; } = new Script ();
		public void Assosiate ( Script scp )
		{
			Script = scp;
			ED_Route.SetData ( scp.BD_RutName );
		}

		//選択
		private void Cb_Route_SelectionChangeCommitted ( object sender, EventArgs e )
		{
			Route rut = (Route)Cb_Route.SelectedItem;
			ED_Route.Get ().Name = rut.Name;
			ED_Route.ResetItems ();
		}
	}
}
