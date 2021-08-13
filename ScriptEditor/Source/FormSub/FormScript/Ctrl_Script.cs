using System;
using System.Windows.Forms;

namespace ScriptEditor
{
	public partial class Ctrl_Script : UserControl
	{
		//スクリプト総合編集
		public EditScript EditScript { get; set; } = null;

		//現在スクリプト
		private Script script = null;

		//計算状態反映グループセッタ
		private System.Action < Script, CLC_ST > GrouptSetterCLC_ST;


		//コンストラクタ
		public Ctrl_Script ()
		{
			InitializeComponent ();

			//計算状態初期化
			foreach ( CLC_ST clcst in Enum.GetValues ( typeof ( CLC_ST ) ) )
			{
				cB_ClcSt.Items.Add ( clcst );
			}
			GrouptSetterCLC_ST = (s,c) => s.CalcState = c;
		}

		//コントロール設定
		public void SetCtrl ( EditScript es )
		{
			EditScript = es;
		}

		//更新(対象に変更があったとき)
		public void UpdateData ()
		{
			tB_Frame.Text = script.Frame.ToString ();
			cB_ClcSt.SelectedItem = script.CalcState;
			Tb_Img.Text = script.ImgName;

			tBN_PosX.UpdateData ();
			tBN_PosY.UpdateData ();
			tBN_VelX.UpdateData ();
			tBN_VelY.UpdateData ();
			tBN_AccX.UpdateData ();
			tBN_AccY.UpdateData ();
		}

		//関連付け(対象が変更になったとき)
		public void Assosiate ( Script scp )
		{
			script = scp;

			//スクリプトから表示を設定
			tB_Frame.Text = scp.Frame.ToString ();
			cB_ClcSt.SelectedItem = scp.CalcState;
			Tb_Img.Text = script.ImgName;

			//ラムダ式で単体設定デリゲートを指定
			tBN_PosX.Assosiate ( i => scp.SetPosX ( i ), ()=> scp.Pos.X );
			tBN_PosY.Assosiate ( i => scp.SetPosY ( i ), ()=> scp.Pos.Y );
			tBN_VelX.Assosiate ( i => scp.SetVelX ( i ), ()=> scp.Vel.X );
			tBN_VelY.Assosiate ( i => scp.SetVelY ( i ), ()=> scp.Vel.Y );
			tBN_AccX.Assosiate ( i => scp.SetAccX ( i ), ()=> scp.Acc.X );
			tBN_AccY.Assosiate ( i => scp.SetAccY ( i ), ()=> scp.Acc.Y );
			tBN_Power.Assosiate ( i => scp.Power = i, ()=> scp.Power );

			//グループセッタを登録
			tBN_PosX.GroupSetter = EditScript.GroupSetterPosX;
			tBN_PosY.GroupSetter = EditScript.GroupSetterPosY;
			tBN_VelX.GroupSetter = EditScript.GroupSetterVelX;
			tBN_VelY.GroupSetter = EditScript.GroupSetterVelY;
			tBN_AccX.GroupSetter = EditScript.GroupSetterAccX;
			tBN_AccY.GroupSetter = EditScript.GroupSetterAccY;
			tBN_Power.GroupSetter = EditScript.GroupSetterPower;
		}

		private void btn_Rect_Click ( object sender, System.EventArgs e )
		{
		}

		private void btn_branch_Click ( object sender, System.EventArgs e )
		{
		}

		//計算状態
		//インデックスが変更されたときのイベントでは初期化やスクリプト選択で発生してしまう
		private void cB_ClcSt_SelectedIndexChanged ( object sender, EventArgs e )
		{
		}
		//ドロップダウンリストを変更して閉じたときに発生するイベント
		private void cB_ClcSt_SelectionChangeCommitted ( object sender, EventArgs e )
		{
			script.CalcState = (CLC_ST)cB_ClcSt.SelectedItem;
			EditScript.DoGroupSetterT ( GrouptSetterCLC_ST, script.CalcState );
		}
	}

}
