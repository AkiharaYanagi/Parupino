using System;
using System.Windows.Forms;

namespace ScriptEditor
{
	//=============================================================
	// バインディングディクショナリの追加・削除・位置変更を持つコントロール 
	//=============================================================
	public partial class Ctrl_ListBox < T > : UserControl
		where T : IName, new () 
	{
		private BindingDictionary < T > BD_t = new BindingDictionary < T > ();

		public Ctrl_ListBox ()
		{
			InitializeComponent ();
			ListBox0.DisplayMember = "Name";
		}

		public void Set ( BindingDictionary < T > bd )
		{
			BD_t = bd;
			ListBox0.DataSource = BD_t.GetBindingList ();
		}

		private void ListBox_SelectedIndexChanged ( object sender, EventArgs e )
		{

		}

		private void BTN_Add_Click ( object sender, EventArgs e )
		{
			ListBox0.Items.Add ( "test" );
			BD_t.Add ( "new", new T () );
			BD_t.GetBindingList ().ResetBindings ();
		}

		private void BTN_Del_Click ( object sender, EventArgs e )
		{
			BD_t.RemoveAt ( ListBox0.SelectedIndex );
		}

		private void Btn_Up_Click ( object sender, EventArgs e )
		{

		}

		private void Btn_Down_Click ( object sender, EventArgs e )
		{

		}

	}
}
