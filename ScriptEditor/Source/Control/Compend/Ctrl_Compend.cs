using System.Windows.Forms;
using System.ComponentModel;

namespace ScriptEditor
{
	using BL_Sqc = BindingList < Sequence >;

	//==================================================================================
	//	Compendを扱うコントロールの集合
	//		アクションもしくはエフェクトの編集と表示を参照する
	//		外部からSetCtrl()でビヘイビアとガーニッシュのいずれかを指定する
	//==================================================================================
	public partial class Ctrl_Compend : UserControl
	{
		public EditCompend EditCompend { get; set; } = null;

		//アクションのときtrue, エフェクトのときfalse
		public bool BoolAction { get; set; } = false;

		//-------------------------------------------------------------------------
		//コンストラクタ
		public Ctrl_Compend ()
		{
			InitializeComponent ();

			sequenceTree1.CtrlCompend = this;
		}

		//初期化
		public void SetEnviron ( EditCompend ec, DispCompend dc )
		{
			EditCompend = ec;
			sqcBoard1.SetEnviron ( ec, dc );
			Ctrl_Img.SetEnviron ( ec, dc );
			sequenceTree1.SetCtrl ( ec, dc );
		}

		public void SetBehavior ()
		{
			BoolAction = true;
			Btn_Sqc.Text = "アクション";
			Btn_Sqc.Enabled = true;
		}

		public void SetGarnish ()
		{
			BoolAction = false;
			Btn_Sqc.Text = "エフェクト";
			Btn_Sqc.Enabled = false;
		}

		//読込時キャラデータの設定
		public void SetCharaData ( Chara ch )
		{
			Behavior b = ch.behavior;
			Garnish g = ch.garnish;
			if ( BoolAction )
			{
				Ctrl_Img.SetCharaData ( b.BD_Image, g.BD_Sequence, g.BD_Image );
				sequenceTree1.SetCharaData ( b.BD_Sequence );
			}
			else
			{
				Ctrl_Img.SetCharaData ( g.BD_Image, g.BD_Sequence, g.BD_Image );
				sequenceTree1.SetCharaData ( g.BD_Sequence );
			}

			FormAction.Inst.SetCharaData ( ch );

			SelectTarget ();
		}


		public void SelectTarget ()
		{
			//選択
			Sequence sqc = EditCompend.SelectedSequence;
			sqcBoard1.SetData ( sqc );

			Assosiate ();
		}

		//関連付け
		public void Assosiate ()
		{
			EditScript es = EditCompend.EditScript;

			//--------------------------------------------------------
			//シークエンス
			Sequence sqc = EditCompend.SelectedSequence;
			sqcBoard1.Assosiate ( sqc );

			//アクションとエフェクトで分岐
			if ( BoolAction )
			{
				FormAction.Inst.Assosiate ( ( Action ) sqc );
			}

			//--------------------------------------------------------
			//スクリプト
			Script scp = EditCompend.SelectedScript;
			FormScript.Inst.Assosiate ( scp );	//各値
			FormRect.Inst.Assosiate ( scp );	//枠
			FormEfGnrt.Inst.Assosiate ( scp );	//Ef生成
			FormBranch0.Inst.Assosiate ( scp );	//ブランチ
			//--------------------------------------------------------
		}

		//更新
		public void UpdateData ()
		{
			BL_Sqc blsqc = EditCompend.Compend.BD_Sequence.GetBindingList();
			for ( int i = 0; i < blsqc.Count; ++ i )
			{
				blsqc.ResetItem ( i );	
			}

			sequenceTree1.UpdateCategory ( blsqc );
		}

		//-------------------------------------------------------------------------
		//[アクション/エフェクト] (シークエンス) ボタン
		private void Btn_Sqc_Click ( object sender, System.EventArgs e )
		{
			SwitchFormAction ();
		}

		private void シークエンスToolStripMenuItem_Click ( object sender, System.EventArgs e )
		{
			SwitchFormAction ();
		}

		private void SwitchFormAction ()
		{
			FormAction f = FormAction.Inst;
			f.Visible = ! f.Visible;	//反転
		}

		//-------------------------------------------------------------------------
		//スクリプトボタン
		private void Btn_Scp_Click ( object sender, System.EventArgs e )
		{
			SwitchFormScript ();
		}

		private void スクリプトPToolStripMenuItem_Click ( object sender, System.EventArgs e )
		{
			SwitchFormScript ();
		}

		private void SwitchFormScript ()
		{
			FormScript.Inst.Visible = ! FormScript.Inst.Visible;
		}

		//-------------------------------------------------------------------------
		//イメージ
		private void Btn_Image_Click ( object sender, System.EventArgs e )
		{
			FormImage.Inst.VisFlip ();
		}

		//-------------------------------------------------------------------------
		//判定枠
		private void Btn_Rect_Click ( object sender, System.EventArgs e )
		{
			FormRect.Inst.Visible = ! FormRect.Inst.Visible;
		}

		//-------------------------------------------------------------------------
		//Ef生成
		private void Btn_EfGnrt_Click ( object sender, System.EventArgs e )
		{
			FormEfGnrt.Inst.Visible = ! FormEfGnrt.Inst.Visible;
		}

		//-------------------------------------------------------------------------
		//ブランチ
		private void Btn_Branch_Click ( object sender, System.EventArgs e )
		{
			FormBranch0.Inst.VisFlip ();
		}

		//-------------------------------------------------------------------------
		//ルート
		private void Btn_Route_Click ( object sender, System.EventArgs e )
		{
			FormRoute.Inst.VisFlip ();
		}
		//-------------------------------------------------------------------------

		public SequenceTree GetSequenceTree ()
		{
			return sequenceTree1;
		}

		//-------------------------------------------------------------------------
		//プレビュー
		private void Btn_Preview_Click ( object sender, System.EventArgs e )
		{
			FormPreview.Inst.Visible = ! FormPreview.Inst.Visible;
		}

	}
}
