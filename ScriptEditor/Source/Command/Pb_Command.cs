using System.Windows.Forms;
using System.ComponentModel;
using System.Drawing;
using ScriptEditor;

namespace ScriptEditor
{
	using GKC_ST = GameKeyCommand.GameKeyCommandState;

	public partial class Pb_Command : PictureBox
	{
		//対象データ
		private Command Cmd = new Command ();

		//選択
		public SelectKey SlctKey { get; set; } = new SelectKey ();

		//表示
		public DispCommand DspCmd { get; set; } = new DispCommand ();

		//ラジオボタン
		public RadioButton RB_OFF { get; set; } = new RadioButton ();
		public RadioButton RB_PUSH { get; set; } = new RadioButton ();
		public RadioButton RB_RELE { get; set; } = new RadioButton ();
		public RadioButton RB_ON { get; set; } = new RadioButton ();
		public RadioButton RB_WILD { get; set; } = new RadioButton ();
		public RadioButton RB_IS { get; set; } = new RadioButton ();
		public RadioButton RB_NIS { get; set; } = new RadioButton ();


		//--------------------------------------------------------------------------
		//コンストラクタ
		public Pb_Command ()
		{
			InitializeComponent ();
		}

		public Pb_Command ( IContainer container )
		{
			container.Add ( this );
			InitializeComponent ();
		}

		//データの設定
		public void Set ( Command cmd )
		{
			Cmd = cmd;
			DspCmd.Set ( cmd );
			Invalidate ();
		}


		//描画
		private void Pb_Command_Paint ( object sender, PaintEventArgs e )
		{
			DspCmd.Disp ( e );
		}

		//--------------------------------------------------------------------------
		//マウスイベント
		private const int W = 32;	//升幅
		private const int H = 32;	//升高
		private const int BX = 32;	//基準X
		private const int BY = 32;	//基準Y

		private void Pb_Command_MouseDown ( object sender, MouseEventArgs e )
		{
			Point pt = GetCell ();

			//範囲外は何もしない
			int nx = Cmd.ListGameKeyCommand.Count - 1;
			int ny = (int)SelectKey.KeyKind.KEY_S;
			if ( pt.X < 0 || pt.Y < 0 || nx < pt.X || ny < pt.Y ) 
			{
				return; 
			}

			//選択
//			SlctKey.Selecting = true;
//			SlctKey.Frame = pt.X;
//			SlctKey.Kind = (SelectKey.KeyKind)pt.Y;
			SlctKey.Set ( Cmd, pt.X, (SelectKey.KeyKind)pt.Y );

			RB_Disp ( SlctKey.GetSt ( Cmd ) );

			
			Invalidate ();
		}

		//マウス位置からフレーム表の升目位置を取得する
		private Point GetCell () 
		{
			//マウス位置をコントロールのクライアント位置に直す
			Point pt = this.PointToClient ( Cursor.Position );
			if ( pt.X < BX || pt.Y < BY ) { return new Point ( -1, -1 ); }

			//升目の位置を計算する
			int pos_x = ( pt.X - BX ) / W;
			int pos_y = ( pt.Y - BY ) / H;

			return new Point ( pos_x, pos_y );
		}

		//ラジオボタンに反映
		private void RB_Disp ( GKC_ST gkcst )
		{
			switch ( gkcst )
			{
			case GKC_ST.KEY_OFF : RB_OFF.Checked  = true; break;
			case GKC_ST.KEY_PUSH: RB_PUSH.Checked = true; break;
			case GKC_ST.KEY_RELE: RB_RELE.Checked = true; break;
			case GKC_ST.KEY_ON  : RB_ON.Checked   = true; break;
			case GKC_ST.KEY_WILD: RB_WILD.Checked = true; break;
			case GKC_ST.KEY_IS  : RB_IS.Checked   = true; break;
			case GKC_ST.KEY_NIS : RB_NIS.Checked  = true; break;
			}
		}
	}
}
