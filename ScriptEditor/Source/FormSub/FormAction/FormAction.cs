using System;
using System.Drawing;
using System.Windows.Forms;

namespace ScriptEditor
{
	//@todo 結びつきの強さからSequenceTreeを直接参照する
	//		Compendを介しない


	//---------------------------------------------------------------------
	//@info Show(this);によりメインフォームにより隠れないようにしたが、
	// サブフォームが開いているとメインフォームが閉じない問題
	// -> 常時存在するシングルトンとしてvisibleを切替で解決
	//---------------------------------------------------------------------

	//---------------------------------------------------------------------
	//	アクションの詳細を設定するフォーム
	//---------------------------------------------------------------------
	//このフォームは１プロセス１フォームなのでシングルトンで実装する
	//・静的で単一な実体化	//static
	//・継承禁止	//sealed
	//・プライベートコンストラクタ
	//---------------------------------------------------------------------
	public sealed partial class FormAction : Form
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormAction Inst { get; } = new FormAction ();

		//プライベートコンストラクタ
		private FormAction ()
		{
			this.StartPosition = FormStartPosition.Manual;
			this.ShowInTaskbar = false;	//タスクバーに非表示

			InitializeComponent ();

			//アクション属性
			foreach ( ActionCategory ac in Enum.GetValues ( typeof ( ActionCategory ) ) )
			{
				CB_Category.Items.Add ( ac );
			}
			//アクション態勢
			foreach ( ActionPosture ac in Enum.GetValues ( typeof ( ActionPosture ) ) )
			{
				CB_Posture.Items.Add ( ac );
			}
		}

		//閉じたときに破棄しない
		protected override void OnFormClosing ( FormClosingEventArgs e )
		{
			e.Cancel = true;
			this.Hide ();
		}
		//---------------------------------------------------------------------

		//編集と表示
		public EditAction EditAction { get; set; } = null;
		public DispAction DispAction { get; set; } = null;
		public DispCompend DispCompend { get; set; } = null;

		//編集中アクション
		private Action action = null;
		
		//親フォーム参照
		public FormMain FormMain { get; set; } = null;

		//シークエンスツリー
		public SequenceTree SequenceTree { get; set; } = null;

		//初期設定
		public void SetCtrl ( EditAction ea, DispAction da, DispCompend dc )
		{
			EditAction = ea;
			DispAction = da;
			DispCompend = dc;

			da.SetCtrl ( TB_Name, CBSL_Next, CB_Category, CB_Posture, TBN_Balance );
			CBSL_Next.SetDisp ( dc );

			SequenceTree = dc.CtrlCmpd.GetSequenceTree ();
		}

		//キャラデータ
		public void SetCharaData ( Chara ch )
		{
			CBSL_Next.SetCharaData ( ch.behavior.BD_Sequence.GetBindingList() );
		}

		//関連付け
		public void Assosiate ( Action act )
		{
			action = act;
			TB_Name.Text = act.Name;
			CBSL_Next.SelectedItem = act.NextAction;
			CB_Category.SelectedItem = act.Category;
			CB_Posture.SelectedItem = act.Posture;

			//各コントロールに設定用のデリゲートを渡す
			CBSL_Next.Associate ( a => act.NextAction = (Action)a );
			TBN_Balance.Assosiate ( i => act._Balance = i, ()=> act._Balance );
		}

		//表示
		private void FormAction_VisibleChanged ( object sender, EventArgs e )
		{
			//フォーム位置を親フォームの右端にする
			int x = FormMain.Location.X + FormMain.Width;
			int y = FormMain.Location.Y;
			this.Location = new Point ( x, y );
		}

		//名前の変更
		private void TB_Name_TextChanged ( object sender, System.EventArgs e )
		{
			action.Name = TB_Name.Text;
//			DispCompend.UpdateData ();
		}

		//カテゴリの変更
		private void CB_Category_SelectedIndexChanged ( object sender, EventArgs e )
		{
			//シークエンスツリーの再構築が必要
			action.Category = (ActionCategory)CB_Category.SelectedItem;
//			DispCompend.UpdateData ();
			//ツリー再構築
			SequenceTree.Remake ();
		}

		//体勢
		private void CB_Posture_SelectedIndexChanged ( object sender, EventArgs e )
		{
			action.Posture = (ActionPosture)CB_Posture.SelectedItem;
//			DispCompend.UpdateData ();
		}
	}
}
