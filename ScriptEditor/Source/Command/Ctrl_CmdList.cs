using System;
using System.Drawing;
using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class Ctrl_CmdList :UserControl
	{
		private EditListbox < Command > EL_Cmd = new EditListbox<Command> ();
		
		public Ctrl_CmdList ()
		{
			InitializeComponent ();

			//----------------------------------
			//コントロール(ルート)
			EL_Cmd.Location = new Point ( 3, 3 );
			this.Controls.Add ( EL_Cmd );

			EL_Cmd.SelectedIndexChanged = ()=>
			{
				Command cmd = EL_Cmd.Get ();
				ctrl_Command1.Set ( cmd );
			};
		}

		public void SetCharaData ( Chara ch )
		{
			EL_Cmd.SetData ( ch.BD_Command.GetBindingList () );
			Command cmd = EL_Cmd.Get ();
			if ( cmd != null )
			{
				ctrl_Command1.Set ( cmd );
			}
		}
	}
}
