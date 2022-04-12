using System.Windows.Forms;
using System.Drawing;
using System;

namespace ScriptEditor
{
	//@todo ２重スタートのときエラー


	//--------------------------------------------
	//	アクションを指定して繰り返し動作する
	//		イメージ表示のみ
	//		[F]に基づく描画
	//--------------------------------------------
	public partial class FormPreview :Form
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormPreview Inst { get; } = new FormPreview ();

		//プライベートコンストラクタ
		private FormPreview ()
		{
			this.StartPosition = FormStartPosition.Manual;
			this.ShowInTaskbar = false;	//タスクバーに非表示

			InitializeComponent ();

			GameMain.Pb = this.pictureBox1;
			FrameControl.GameMain = GameMain;
			Btn_Advance.Enabled = false;
		}

		//閉じたときに破棄しない
		protected override void OnFormClosing ( FormClosingEventArgs e )
		{
			fcon.End ();

			e.Cancel = true;
			this.Hide ();
		}

		private void FormPreview_VisibleChanged ( object sender, System.EventArgs e )
		{
			//フォーム位置を親フォームからの相対位置にする
			int x = FormMain.Location.X + 100;
			int y = FormMain.Location.Y + 100;
			this.Location = new Point ( x, y );
		}

		//---------------------------------------------------------------------

		private FormMain FormMain = null;
		private EditCompend EditCompend = null;

		private FrameControl fcon = new FrameControl ();
		private GameMain GameMain = new GameMain ();

		public void SetBmp ( Bitmap bmp )
		{
			this.pictureBox1.Image = bmp;
		}

		protected override void OnShown ( EventArgs e )
		{
			Start ();
			base.OnShown ( e );
		}

		public void Start ()
		{
			string imgname = EditCompend.SelectedScript.ImgName;
			ImageData imgdt = EditCompend.Compend.BD_Image.Get ( imgname );
			pictureBox2.Image = imgdt.Img;


			GameMain.SetCharaData ( EditChara.Inst.Chara );
			GameMain.Setter0 = SetBmp;
			GameMain.Seq = EditCompend.SelectedSequence;
			GameMain.Init ();
			fcon.FormPreview = this;
			fcon.Start ();

			Btn_Start.Enabled = false;
			Btn_Stop.Enabled = true;
		}

		public void SetEnviron ( FormMain fm, EditCompend ec )
		{
			FormMain = fm;
			EditCompend = ec;
		}

		public void _Move ()
		{
			if ( pause )
			{
				if ( advance )
				{
					GameMain.Move ();
					advance = false;
				}
			}
			else
			{
				GameMain.Move ();
			}
		}

		public void _Draw ()
		{
			GameMain.Draw ();
		}

		private void Btn_Start_Click ( object sender, System.EventArgs e )
		{
			Start ();
		}

		private void Btn_Stop_Click ( object sender, System.EventArgs e )
		{
			fcon.End ();
			Btn_Start.Enabled = true;
			Btn_Stop.Enabled = false;
		}

		//--------------------------------------------------------------------------
		//一時停止・コマ送り
		private bool pause = false;
		private bool advance = false;

		private void Btn_Pause_Click ( object sender, EventArgs e )
		{
			if ( pause )
			{
				pause = false;
				Btn_Advance.Enabled = false;
			}
			else
			{
				pause = true;
				Btn_Advance.Enabled = true;
			}
		}

		private void Btn_Advance_Click ( object sender, EventArgs e )
		{
			advance = true;
		}
	}
}
