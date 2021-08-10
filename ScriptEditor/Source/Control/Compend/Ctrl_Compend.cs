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
		public void SetCtrl ( EditCompend ec )
		{
			EditCompend = ec;
			sqcBoard1.SetCtrl ( ec );
			Ctrl_Img.SetCtrl ( ec );
			sequenceTree1.SetCtrl ( ec );
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
				Ctrl_Img.SetCharaData ( b.BD_Image, g.BD_Sequence.GetBindingList(), g.BD_Image );
//				sequenceTree1.SelectSequence = EditCompend.SelectSequence;
				sequenceTree1.SetCharaData ( b.BD_Sequence );
			}
			else
			{
				Ctrl_Img.SetCharaData ( g.BD_Image, g.BD_Sequence.GetBindingList(), g.BD_Image );
//				sequenceTree1.SelectSequence = EditCompend.SelectSequence;
				sequenceTree1.SetCharaData ( g.BD_Sequence );
			}

			FormAction.Inst.SetCharaData ( ch );

			SelectTarget ();
		}


		public void SelectTarget ()
		{
			//選択
			Sequence sqc = EditCompend.SelectedSequence;
			sqcBoard1.Set ( sqc );

			Assosiate ();
		}

		//関連付け
		public void Assosiate ()
		{
			Script scp = EditCompend.SelectedScript;
			EditScript es = EditCompend.EditScript;

			//シークエンス
			//アクションとエフェクトで分岐
			if ( BoolAction )
			{
				FormAction.Inst.Assosiate ( ( Action ) EditCompend.SelectedSequence );
			}

			//スクリプト
			//イメージ
			//@todo 対象がイメージリストに存在しないときエラー表示(色変更？)
			//		指定は可能
			Tb_ImageName.Text = scp.ImgName;
			
			//位置
			Tbn_X.Assosiate ( i=> scp.SetPosX ( i ), ()=> scp.Pos.X );
			Tbn_Y.Assosiate ( i=> scp.SetPosY ( i ), ()=> scp.Pos.Y );

			//詳細
			//Ef生成
			//枠
			FormScript.Inst.Assosiate ( scp );
			FormRect.Inst.Assosiate ( scp );
			FormEfGnrt.Inst.Assosiate ( scp );
			FormBranch.Inst.Assosiate ( scp );
		}

		//更新
		public void UpdateData ()
		{
			BL_Sqc blsqc = EditCompend.Compend.BD_Sequence.GetBindingList();
			for ( int i = 0; i < blsqc.Count; ++ i )
			{
				blsqc.ResetItem ( i );	
			}

//			sequenceTree1.UpdateCategory ( blsqc );
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
//			FormImage.Inst.Visible = ! FormImage.Inst.Visible;
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
			FormEfGnrt f = FormEfGnrt.Inst;
			f.Visible = ! f.Visible;
		}

		//-------------------------------------------------------------------------
		//Ef生成
		private void Btn_Branch_Click ( object sender, System.EventArgs e )
		{
			FormBranch f = FormBranch.Inst;
			f.Visible = ! f.Visible;
		}

		//----
		public SequenceTree GetSequenceTree ()
		{
			return sequenceTree1;
		}
	}
}
