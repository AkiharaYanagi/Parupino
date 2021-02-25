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

	//キャラを受けてフレーム毎に動作し描画する
	public sealed partial class Form_ActionPreview : Form
	{

		//動作と描画の具体的処理
		private PreviewChara previewChara;

		//フレーム表示時間をスレッドによりコントロールする
		private FrameControl frameControl = new FrameControl ();

		//フレーム制御からフォームを呼び出す

		//一時保存
		Chara _chara  = null;
		EditCompend.SELECTED_SCRIPT selectedScript = new EditCompend.SELECTED_SCRIPT ( 0, 0 );
		
		private PreviewCharaCall previewCharaCall = new PreviewCharaCall ();

		//スレッド
		Thread thread = null;

		//--------------------------------------------------------------------
		//シングルトンパターン
		private static readonly Form_ActionPreview _instance = new Form_ActionPreview ();
		public static Form_ActionPreview Instance　{　get { return _instance; }	}

		//プライベート コンストラクタ
		private Form_ActionPreview ()
		{
			//フォームをマウス位置にする
			this.StartPosition = FormStartPosition.Manual;
			this.Location = System.Windows.Forms.Cursor.Position;

			InitializeComponent ();

			bmp = new Bitmap ( pictureBox1.Width, pictureBox1.Height );

			previewChara= new PreviewChara ( pictureBox1 );
			previewChara.form_actPrev = this;

			previewCharaCall.form_actPrev = this;
		}

		//--------------------------------------------------------------------
		//ダイアログ(モーダルウィンドウ)表示のオーバーロード
		//表示
		public void ShowDialog ( Chara chara, EditCompend.SELECTED_SCRIPT ss )
//		public void ShowDialog ( chara chara, Action action )
		{
			//値を保存
			_chara = chara;
			selectedScript = ss;

			//スレッドからの呼び出し
			previewCharaCall.IsActive = true;

			//具体処理の初期設定
			previewChara.Init ( chara, ss );
//			previewChara.Init ( chara, action );

			//フレーム制御スレッド
			frameControl.refGameMain = previewCharaCall;
			frameControl.ThreadOver = false;
			frameControl.UnlockStop ();

			thread = new Thread ( new ThreadStart ( frameControl.ThreadFrame ) );
			thread.Start ();

			//test
//			Debug.WriteLine ( "FormからDraw()" );
//			Draw ();

			base.ShowDialog ();
		}

		//閉じたときに破棄しない(シングルトン)
		protected override void OnFormClosing ( FormClosingEventArgs e )
		{
			//スレッド終了
#if false

			//			previewChara.IsActive = false;

//			Debug.WriteLine ( "OnFormClosing" );
			if ( ! frameControl.ThreadOver )
			{
				frameControl.RequestStop ();
			}

			//終了確認
			while ( ! frameControl.ThreadOver )
			{
				Thread.Sleep ( 1 );
			}
#endif
			//スレッド強制終了
			thread.Abort ();
			Debug.WriteLine ( "OnFormClosing : スレッド強制終了" );

			//charaに変更した現在スクリプト位置を元に戻す
//			_chara.SelectedScript = selectedScript;

			e.Cancel = true;
			this.Hide ();
		}

		//描画

		private Bitmap bmp = null;
		public Bitmap Bmp { get { return bmp; } }

#if false
		public delegate void DrawDelegage ();

		public void Draw ()
		{
			if ( pictureBox1.InvokeRequired )
			{
				//スレッド外からコントロールにアクセスする
				pictureBox1.Invoke ( new DrawDelegage ( _Draw ) );
			}
			else
			{
				Debug.WriteLine ( "Form not InvokeRequired" );
			}
		}
#endif

		public void _Draw ()
		{
			previewChara.Draw ();
		}

		public void _Move ()
		{
			if ( ! pause )
			{
				previewChara.Move ();
			}
			else if ( frameAdvance )
			{
				previewChara.Move ();
				frameAdvance = false;
			}
		}

		//一時停止
		private bool pause = false;
		//コマ送り
		private bool frameAdvance = false;

		private void pictureBox1_MouseDown ( object sender, MouseEventArgs e )
		{
			if ( e.Button == MouseButtons.Left )
			{
				pause = ! pause;
			}
			else if ( e.Button == MouseButtons.Right )
			{
				frameAdvance = true;
			}

		}

		//アクション実行
		private void btnPlay_Click ( object sender, EventArgs e )
		{
//			previewChara.Init ( _chara, selectedScript );
//			Action _action = _chara.behavior[ selectedScript.sequence ];
//			previewChara.Init ( _chara, _chara.behavior[ selectedScript.sequence ] );
			previewChara.Init ( _chara, selectedScript );
		}

		//--------------------------------------------------------------------


	}
}
