using System.IO;
using System.Windows.Forms;
using System.Drawing;

namespace GameSettings
{
	public partial class MainForm : Form
	{
		//設定
		private AppSettings apStg = new AppSettings ();
		private GameSettings gmStg = new GameSettings ();

		private const int start_X = -200;	//フォーム位置定数
		private const int start_Y = -50;	//フォーム位置定数

		//コンストラクタ
		public MainForm ()
		{
			//フォーム開始位置をマウス位置にする
			this.StartPosition = FormStartPosition.Manual;
			Point ptStart = Cursor.Position;
			ptStart.X += start_X;
			ptStart.Y += start_Y;
			this.Location = ptStart;

			//タイトルバーに現在位置を表示
			this.Text = Directory.GetCurrentDirectory ();

			//コンポーネント初期化
			InitializeComponent ();


			tabControl1.Controls[2].Controls.Add ( new ScriptEditor.AppSettings () ); 
		}

	}
}
