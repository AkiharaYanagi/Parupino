using System.Windows.Forms;
using ScriptEditor;

namespace GameSettings
{
	public partial class Form1 : Form
	{
		public Form1 ()
		{
			FormUtility.InitPosition ( this );

			InitializeComponent ();

			//各タブページに追加
			TabControl.TabPageCollection tbPage  = this.tabControl1.TabPages;

			//システム設定追加
			tbPage [ "tabPage_System" ].Controls.Add ( new AppSettings () );

			//キーコンフィグ追加
			tbPage [ "tabPage_KeyConfig" ].Controls.Add ( new Ctrl_KeyConfig () );

			//ゲーム設定追加
			tbPage [ "tabPage_Game" ].Controls.Add ( new Ctrl_GameSettings () );


			//test
			//開始タブ選択
			tabControl1.SelectedIndex = 0;
//			tabControl1.SelectedIndex = 2;
			
		}
	}
}
