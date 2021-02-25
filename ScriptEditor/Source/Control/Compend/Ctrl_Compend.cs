using System.Windows.Forms;
using System.ComponentModel;

namespace ScriptEditor
{
	using BL_Sqc = BindingList < Sequence >;

	public partial class Ctrl_Compend : UserControl
	{
		//キャラの参照 (固有リストを参照する)
		Chara Chara = null;

		//アクションもしくはエフェクトの編集と表示を参照する
		//外部でビヘイビアとガーニッシュのいずれかを指定してSet()する
		public EditCompend EditCompend { get; set; } = null;

		//アクションのときのみ
		public bool BoolAction { get; set; } = false;

		//-------------------------------------------------------------------------
		//コンストラクタ
		public Ctrl_Compend ()
		{
			InitializeComponent ();
		}

		//初期化
		public void SetCtrl ( EditCompend ec )
		{
			EditCompend = ec;
			sqcBoard1.SetCtrl ( ec );
			Ctrl_Img.SetCtrl ( ec );
		}

		public void SetBehavior ()
		{
			BoolAction = true;
			Btn_Sqc.Text = "アクション";
		}

		public void SetGarnish ()
		{
			BoolAction = false;
			Btn_Sqc.Text = "エフェクト";
			Btn_Sqc.Enabled = false;
		}

		//キャラの設定
		public void SetCharaData ( Chara ch )
		{
			Chara = ch;

			if ( BoolAction )
			{
				Ctrl_Img.SetCharaData ( ch.behavior.ListImage, ch.garnish.Bldct_sqc.GetBindingList(), ch.garnish.ListImage );
			}
			else
			{
				Ctrl_Img.SetCharaData ( ch.garnish.ListImage, ch.garnish.Bldct_sqc.GetBindingList(), ch.garnish.ListImage );
			}

			FormAction.Inst.SetCharaData ( ch );
			Lb_SqcName.DataSource = EditCompend.Compend.Bldct_sqc.GetBindingList();
			Set ();
		}

		//リストボックスによるシークエンスの選択
		private void Lb_SqcName_SelectedIndexChanged ( object sender, System.EventArgs e )
		{
			EditCompend.SelectSequence ( Lb_SqcName.SelectedIndex );

			Set ();

			DispChara.Inst.Disp ();
		}

		public void Set ()
		{
			Sequence sqc = (Sequence)Lb_SqcName.SelectedItem;
			sqcBoard1.Set ( sqc );

			Script scp = EditCompend.SelectedScript;
			Assosiate ( scp );
		}

		//関連付け
		public void Assosiate ( Script scp )
		{
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
			BL_Sqc blsqc = EditCompend.Compend.Bldct_sqc.GetBindingList();
			for ( int i = 0; i < blsqc.Count; ++ i )
			{
				blsqc.ResetItem ( i );	
			}
		}

		//-------------------------------------------------------------------------
		//シークエンスボタン
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
			FormScript f = FormScript.Inst;
			f.Visible = ! f.Visible;
		}

		//-------------------------------------------------------------------------
		//イメージ
		private void Btn_Image_Click ( object sender, System.EventArgs e )
		{
			//選択用別フォーム
			ImageList blImgList = ( BoolAction ) ? Chara.behavior.ListImage : Chara.garnish.ListImage;
			BindingList < ImageData > blImg = blImgList.GetBindingList ();
			FormImage formImage = new FormImage ( blImg );

			//フォームを開く
			if ( formImage.ShowDialog ( this ) == DialogResult.OK )
			{
				//フォームをOKで閉じる

				//イメージの設定
				Script scp = EditCompend.SelectedScript;
				scp.ImgIndex = formImage.GetImageIndex();

				//スクリプト変更後に他スクリプトにコピーするかチェックする
//				CheckSetOtherScript ();
//				editChara.EditAction.CheckSetOtherScript ();
				EditCompend.EditScript.GroupSetterImageIndex ( scp.ImgIndex );


				//表示の更新
				Tb_ImageName.Text = scp.ImgIndex.ToString();
				DispChara.Inst.Disp ();
			}

			formImage.Dispose ();
		}

		//-------------------------------------------------------------------------
		//判定枠
		private void Btn_Rect_Click ( object sender, System.EventArgs e )
		{
			FormRect f = FormRect.Inst;
			f.Visible = ! f.Visible;
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
	}
}
