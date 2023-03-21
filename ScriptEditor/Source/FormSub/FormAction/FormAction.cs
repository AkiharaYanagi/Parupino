using System;

namespace ScriptEditor
{
	//-------------------------------------------------------------
	//	アクション設定フォーム
	//-------------------------------------------------------------

	public sealed partial class FormAction : EditorForm
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormAction Inst { get; } = new FormAction ();

		//プライベートコンストラクタ
		private FormAction ()
		{
			InitializeComponent ();
			base.LoadObject ();

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

		//---------------------------------------------------------------------

		//編集と表示
		public EditAction EditAction { get; set; } = null;
		public DispAction DispAction { get; set; } = null;
		public DispCompend DispCompend { get; set; } = null;

		//編集中アクション
		private Action action = new Action ( "New_Action" );
		
		//@info 結びつきの強さからSequenceTreeを直接参照する
		//		Compendを介しない
		//シークエンスツリー
		public SequenceTree SequenceTree { get; set; } = null;

		//初期設定
		public void SetCtrl ( EditAction ea, DispAction da, DispCompend dc )
		{
			EditAction = ea;
			DispAction = da;
			DispCompend = dc;

			da.SetCtrl ( TB_Name, CBSL_Next, CB_Category, CB_Posture, TBN_HitNum );
			CBSL_Next.SetDisp ( dc );

			SequenceTree = dc.CtrlCmpd.GetSequenceTree ();
		}

		//キャラデータ
		public void SetCharaData ( Chara ch )
		{
			CBSL_Next.SetCharaData ( ch.behavior.BD_Sequence );
		}

		//関連付け
		public void Assosiate ( Action act )
		{
			action = act;
			TB_Name.Text = act.Name;
			CBSL_Next.SelectName ( act.NextActionName );
			CB_Category.SelectedItem = act.Category;
			CB_Posture.SelectedItem = act.Posture;
			TBN_HitNum.Text = act.HitNum.ToString();
			Tbn_HitPitch.Text = act.HitPitch.ToString();
			Tbn_Balance.Text = act.Balance.ToString();

			//各コントロールに設定用のデリゲートを渡す
			CBSL_Next.Set = a=>act.NextActionName = a.Name;
			TBN_HitNum.SetFunc = i=>act.HitNum = i;
			Tbn_HitPitch.SetFunc = i=>act.HitPitch = i;
			Tbn_Balance.SetFunc = i=>act.Balance = i;
		}

		//-----------------------------------------------------------
		//アクション：名前の変更
		private void TB_Name_TextChanged ( object sender, EventArgs e )
		{
			action.Name = TB_Name.Text;
//			DispCompend.UpdateData ();
		}


		//-----------------------------------------------------------
		//カテゴリの変更

		//インデックスが変更されたとき
		private void CB_Category_SelectedIndexChanged ( object sender, EventArgs e )
		{
			//@info ◆外部から選択アクションが変更されたときもイベントが発生する
			// ->SelectionChangeCommitted()を用いる
		}

		//ドロップダウンリストから変更されて閉じたとき
		private void CB_Category_SelectionChangeCommitted ( object sender, EventArgs e )
		{
			//@info ◆現ドロップダウンリストを閉じたときのみイベントが発生する

			//シークエンスツリーの再構築が必要
			action.Category = (ActionCategory)CB_Category.SelectedItem;
			//ツリー再構築
			SequenceTree.Remake ();
			DispCompend.UpdateData ();
		}

		//-----------------------------------------------------------
		//体勢
		private void CB_Posture_SelectedIndexChanged ( object sender, EventArgs e )
		{
			action.Posture = (ActionPosture)CB_Posture.SelectedItem;
		}

	}
}
