using System;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;

namespace ScriptEditor
{
	public class FrameControl
	{
		static readonly long FPS = 60;
		static readonly float mSPF = 1000f / FPS;				//16.6666...[ms/F]
//		static readonly long mSPF = 1000 / FPS;				//16.6666...[ms/F]
		static readonly long mmSPF = 1000 * 1000 / FPS;		//16666.6...[mms/F]

		public static GameMain GameMain { get; set; } = null;
		public FormPreview FormPreview { get; set; } = null;

		private readonly object LockOb = new object ();
		public volatile static bool Active = false;

		public void Start ()
//		public async void Start ()
		{
			Active = true;
			Task task = Task.Run ( ()=>{ FrameThread (); } );
		}

		public void End ()
		{
			lock ( LockOb )
			{
			Active = false;
			}	//lock
		}

//		private static async void  FrameThread ()
//		private async void  FrameThread ()
		private void  FrameThread ()
		{
			int frame = 0;

			Stopwatch wtc = new Stopwatch ();
			wtc.Start ();
			long before = wtc.ElapsedMilliseconds;

#if false

			Debug.WriteLine ( "Freq:" + Stopwatch.Frequency );
			long startTime = wtc.ElapsedMilliseconds;
//			await Task.Delay ( 1000 );
			Thread.Sleep ( 1000 );
			long endTime = wtc.ElapsedMilliseconds;
			Debug.WriteLine ( startTime.ToString () + " - " + endTime.ToString () );
#endif

		
			while ( Active )
			{
				//動作
				//GameMain.Move ();
				FormPreview._Move ();

				long now = wtc.ElapsedMilliseconds;
				long progress = now - before;	//実効時間
				long ideal = frame * mmSPF;		//理想時間
//				long ideal = (int)(frame * mSPF);		//理想時間

				int sleepTime = (int)((ideal - 1000 * progress) / 1000);
				//理想時間より実効時間が短いとき時間調整
//				if ( ideal > progress )
				if ( ideal > 1000 * progress )
				{
//					long t0 = wtc.ElapsedMilliseconds;
					//@info		await Task.Delay より Thread.Sleepの方が精度が高い
					//await Task.Delay ( delayTime );
					Thread.Sleep ( sleepTime );
//					long t1 = wtc.ElapsedMilliseconds;
//					Debug.WriteLine ( delayTime.ToString () + ", " + t0.ToString () + " - " + t1.ToString () );
				}

				//1000[ms]で更新
				if ( progress >= 1000 )
				{
					int m_frame_fraction = 0;
					if( 0 != ideal )
					{
						m_frame_fraction = (int)( 1000 * (ideal - 1000 * progress) / ideal );
					}
//					GameMain.FPS = frame;
					GameMain.FPS = ( 1000 * ( frame - 1 ) )+ m_frame_fraction;
					string s0 = sleepTime.ToString ();
					GameMain.Trace = s0;
					frame = 0;
					before = now;
				}

				//描画
				//GameMain.Draw ();
				FormPreview.Invoke ( (System.Action)FormPreview._Draw );

				++ frame;
			}
		}
	}
}
