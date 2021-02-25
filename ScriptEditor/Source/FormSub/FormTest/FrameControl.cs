using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Threading;
using System.Diagnostics;


namespace ScriptEditor
{

	//抽象クラス・ゲームメイン
	//	Move()とDraw()を持つ
	public abstract class GameMain
	{
		public bool IsActive { get; set; }
		public abstract void Move ();
		public abstract void Draw ();
	}


	//フレーム制御
	//	ゲームメインのMove()とDraw()を毎フレームで実行する
	class FrameControl
	{
		private const int FPS = 60;			//frame Per Second
		public GameMain refGameMain { get; set; }
		
		//終了要求
		//スレッドセーフのために最適化しない(volatile)
		private volatile bool _shuldStop = false;

		//終了状態
		public bool ThreadOver { get; set; }

		//コンストラクタ
		public FrameControl ()
		{
		}

		//スレッド終了要求
		public void UnlockStop () { _shuldStop = false; }

		//スレッド終了要求を解除
		public void RequestStop () { _shuldStop = true; }

		//フレーム制御におけるメインスレッド
		public void ThreadFrame ()
		{
			ThreadOver = false;
			Debug.WriteLine ( "スレッド開始" );
	
			int frame = 0;
			System.Diagnostics.Stopwatch stopWatch = new System.Diagnostics.Stopwatch ();
			stopWatch.Start ();
			int before = ( int ) stopWatch.ElapsedMilliseconds;

			//メインループ
			while ( ! _shuldStop )
			{
				int now = ( int ) stopWatch.ElapsedMilliseconds;
				int progress = now - before;

				int ideal = ( int ) ( frame * ( 1000.0F / FPS ) );		//[ms]

				//				Thread.Sleep ( 5 );
				refGameMain.Move ();

				//				stopWatch.Stop ();

				if ( ideal > progress )
				{
					Thread.Sleep ( ideal - progress );
					//					Debug.WriteLine ( "ideal = " + ideal + ", stopWatch.ElapsedMilliseconds = " +  stopWatch.ElapsedMilliseconds + " *60=" + (stopWatch.ElapsedMilliseconds * 60));
					//					Debug.WriteLine ( "FPS = " + frame + ", sleepTime = " + ( int ) ( ( ideal - progress ) / FPS ) );
				}

				refGameMain.Draw ();

				++frame;

				if ( progress >= 1000 )
				{
					//					Debug.WriteLine ( "before = " + before + ", now = " + now );
					//					Debug.WriteLine ( "ideal = " + ideal + ", progress = " + progress );
					//					Debug.WriteLine ( "FPS = " + frame + ", sleepTime = " + (ideal - progress) );
					frame = 0;
					before = now;
					//					stopWatch.Stop ();
					//					stopWatch.Reset ();
					//					stopWatch.Start ();
				}
			}

			Debug.WriteLine ( "スレッド終了" );
			_shuldStop = false;
			ThreadOver = true;
		}
	}
}
