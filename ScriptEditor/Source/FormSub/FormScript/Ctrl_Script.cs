using System;
using System.Windows.Forms;
using System.Collections.Generic;

namespace ScriptEditor
{
	using PrmInt = ScriptParam < int >;


	public partial class Ctrl_Script : UserControl
	{
		//スクリプト総合編集
		public EditScript EditScript { get; set; } = null;

		//現在スクリプト
		private Script script = null;

		//コントロール集合
		private List < TB_Number > l_tbn = new List<TB_Number> ();

		//計算状態反映グループセッタ
		private System.Action < Script, CLC_ST > GrouptSetterCLC_ST;


		//@todo グループを越えて、設定項目を全体に反映する切り替えボタン
		//グループ編集
		// 各値が異なるとき空白表示、同一のとき値表示


		//コンストラクタ
		public Ctrl_Script ()
		{
			InitializeComponent ();

			//計算状態 プルダウンメニュー初期化
			foreach ( CLC_ST clcst in Enum.GetValues ( typeof ( CLC_ST ) ) )
			{
				cB_ClcSt.Items.Add ( clcst );
			}
			GrouptSetterCLC_ST = (s,c) => s.CalcState = c;

			//設定用デリゲートを指定
			TBSN_posx.PrmInt = new PrmInt ( (s,i)=>s.SetPosX(i), s=>s.Pos.X );

			//登録
			l_tbn.Add ( tBN_PosX );
			l_tbn.Add ( tBN_PosY );
			l_tbn.Add ( tBN_VelX );
			l_tbn.Add ( tBN_VelY );
			l_tbn.Add ( tBN_AccX );
			l_tbn.Add ( tBN_AccY );
			l_tbn.Add ( tBN_Power );
			l_tbn.Add ( tBN_BlackOut );
			l_tbn.Add ( tBN_Vibration );
			l_tbn.Add ( tBN_Stop );
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

			foreach ( TB_Number tbn in l_tbn )
			{
				tbn.UpdateData ();
			}
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
			tBN_BlackOut.Assosiate ( i => scp.BlackOut = i, ()=> scp.BlackOut );
			tBN_Vibration.Assosiate ( i => scp.Vibration = i, ()=> scp.Vibration );
			tBN_Stop.Assosiate ( i => scp.Stop = i, ()=> scp.Stop );

#if false
			//グループセッタを登録
			tBN_PosX.GroupSetter = EditScript.GroupSetterPosX;
			tBN_PosY.GroupSetter = EditScript.GroupSetterPosY;
			tBN_VelX.GroupSetter = EditScript.GroupSetterVelX;
			tBN_VelY.GroupSetter = EditScript.GroupSetterVelY;
			tBN_AccX.GroupSetter = EditScript.GroupSetterAccX;
			tBN_AccY.GroupSetter = EditScript.GroupSetterAccY;
			tBN_Power.GroupSetter = EditScript.GroupSetterPower;
#endif
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

		//編集範囲を設定
		private void RB_TRG_ALL_CheckedChanged ( object sender, EventArgs e )
		{
			//foreach ( TB_Number tbn in l_tbn ) { tbn.SetAll (); }
		}

		private void RB_TRG_GRP_CheckedChanged ( object sender, EventArgs e )
		{
			//foreach ( TB_Number tbn in l_tbn ) { tbn.SetGroup (); }
		}

		private void RB_TRG_SGL_CheckedChanged ( object sender, EventArgs e )
		{
			//foreach ( TB_Number tbn in l_tbn ) { tbn.SetSingle (); }
		}
	}

}
