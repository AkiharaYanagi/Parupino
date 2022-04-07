using System;
using System.Drawing;
using System.Collections.Generic;
using System.Windows.Forms;


namespace ScriptEditor
{
	public partial class FormRoute :EditorForm
	{
		//コントロール(ルート)
		EditListbox < TName > EL_Route = new EditListbox < TName > ();

		//チェック用ルートリスト
		private BindingDictionary < Route > BD_Route = new BindingDictionary<Route> ();


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
			EL_Route.Location = new Point ( 3, -70 );
			this.Controls.Add ( EL_Route );
			EL_Route.IO_Visible ( false );
			EL_Route.TbName_Off ();

			//追加時
			EL_Route.Listbox_Add = ()=>
			{
			};
			//選択変更時
			EL_Route.SelectedIndexChanged = ()=>
			{
			};
			EL_Route.Func_color_check = (ob)=>
			{
				//ルート名が存在するかどうか
				return ! BD_Route.ContainsKey ( ((TName)ob).Name );
			};
			//==============================================================

			Lb_Copy.DisplayMember = "Name";
		}

		//---------------------------------------------------------------------

		//データ設定
		public void SetCharaData ( Chara ch )
		{
			//コンボボックスに登録
			Cb_Route.DataSource = ch.BD_Route.GetBindingList ();
			Cb_Route.DisplayMember = "Name";

			//チェック用保存
			BD_Route = ch.BD_Route;
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
			EL_Route.SetData ( scp.BD_RutName );
		}

		//選択
		private void Cb_Route_SelectionChangeCommitted ( object sender, EventArgs e )
		{
			Route rut = (Route)Cb_Route.SelectedItem;
			EL_Route.Get ().Name = rut.Name;
			EL_Route.ResetItems ();
		}

		//一時コピー
		private void Btn_Copy_Click ( object sender, EventArgs e )
		{
			ListBox lb = EL_Route.GetListBox ();
			Lb_Copy.Items.Clear ();
			foreach ( object ob in lb.Items )
			{
				Lb_Copy.Items.Add ( (TName)ob );
			}
		}

		//グループにペースト
		private void Btn_PasteGroup_Click ( object sender, EventArgs e )
		{

		}

		//全体にペースト
		private void Btn_PastAll_Click ( object sender, EventArgs e )
		{

		}
	}
}
