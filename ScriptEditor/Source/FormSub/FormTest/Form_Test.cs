using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;


using System.Threading;
using System.Diagnostics;


namespace ScriptEditor
{


	//sealed : 継承不可
	public sealed partial class Form_Test : Form
	{
		//--------------------------------------------------------------------
		//シングルトンパターン
		private static readonly Form_Test _instance = new Form_Test ();
		public static Form_Test Instance { get { return _instance; } }

		//プライベートコンストラクタ
		private Form_Test ()
		{
			//フォームのロケーションを手動にする
			//	位置は親フォームから指定
			this.StartPosition = FormStartPosition.Manual;
			InitializeComponent ();
		}

		//閉じたときに破棄しない
		protected override void OnFormClosing ( FormClosingEventArgs e )
		{
			//スレッド終了
			if ( ! frameControl.ThreadOver )
			{
//				frameControl.RequestStop ();
			}

			//スレッド強制終了
			thread.Abort ();
			Debug.WriteLine ( "OnFormClosing : スレッド強制終了" );

			e.Cancel = true;
			this.Hide ();
		}

		//--------------------------------------------------------------------

		public void Init ()
		{
		}

		//フレーム表示時間をコントロールする
		private FrameControl frameControl = new FrameControl ();

		//FPSに基づいて呼び出す
		private TestCharaCall testCharaCall = new TestCharaCall ();

		//動作と描画のまとめ
		private TestChara testChara = null;

		//スレッド
		Thread thread = null;

		//表示
		public void ShowDialog ( Chara chara )
		{
			testCharaCall.IsActive = true;

			testChara = new TestChara ( chara, pictureBox1 );
			testChara.Init ();

			frameControl.refGameMain = testCharaCall;
			frameControl.UnlockStop ();

			thread = new Thread ( new ThreadStart ( frameControl.ThreadFrame ) );
			thread.Start ();
			
			base.ShowDialog ();

			testCharaCall.IsActive = false;
		}

		public void _Move ()
		{
			testChara.Move ();
		}

		public void _Draw ()
		{
			testChara.Draw ();
		}
	}
}
