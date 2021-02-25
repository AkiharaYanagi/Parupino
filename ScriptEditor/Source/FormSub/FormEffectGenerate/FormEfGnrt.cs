﻿using System.Windows.Forms;
using System.Drawing;

namespace ScriptEditor
{
	public sealed partial class FormEfGnrt : Form
	{
		//---------------------------------------------------------------------
		//シングルトン実体
		public static FormEfGnrt Inst { get; set; } = new FormEfGnrt ();
		
		//プライベートコンストラクタ
		private FormEfGnrt ()
		{
			this.ShowInTaskbar = false;	//タスクバーに非表示
			InitializeComponent ();
			cB_SequenceList1.DisplayMember = "Name";
			listBox1.DisplayMember = "Name";
		}
			
		//閉じたときに破棄しない
		protected override void OnFormClosing ( FormClosingEventArgs e )
		{
			e.Cancel = true;
			this.Hide ();
		}
			
		//親フォーム参照
		public FormMain FormMain { get; set; } = null;

		//フォーム位置を親フォームの右端にする
		private void FormEfGnrt_VisibleChanged ( object sender, System.EventArgs e )
		{
			int x = FormMain.Location.X + FormMain.Width;
			int y = FormMain.Location.Y + 600;
			this.Location = new Point ( x, y );
		}
		//---------------------------------------------------------------------
		
		//対象
		public Script Scp = null;

		//コントロールの設定
		public void SetCtrl ()
		{
		}

		//キャラデータの設定
		public void SetCharaData ( Chara ch )
		{
			cB_SequenceList1.DataSource = ch.garnish.Bldct_sqc.GetBindingList();
		}

		//関連付け
		public void Assosiate ( Script script )
		{
			Scp = script;
			listBox1.DataSource = script.ListGenerateEf;
			UpdateData ();
		}

		//更新
		public void UpdateData ()
		{
			int i = 0;
			foreach ( EffectGenerate efGnrt in Scp.ListGenerateEf )
			{
				Scp.ListGenerateEf.ResetItem ( i ++ );
			}
			if ( 0 < listBox1.Items.Count )
			{
				listBox1.SelectedIndex = 0;
				EffectGenerate efgnrt = GetEfGnrt ();
				Tbn_X.Text = efgnrt.Pt.X.ToString();
				Tbn_Y.Text = efgnrt.Pt.Y.ToString();
				Tbn_Z.Text = efgnrt.Z.ToString();
				Cb_Gnrt.Checked = efgnrt.Gnrt;
				Cb_Loop.Checked = efgnrt.Loop;
				Cb_Sync.Checked = efgnrt.Sync;
				On ();
			}
			else
			{
				SetZero ();
				Off ();
			}
		}

		public EffectGenerate GetEfGnrt ()
		{
			if ( null == listBox1.SelectedItem ) { return null; }
			return (EffectGenerate)listBox1.SelectedItem;
		}

		public void SetZero ()
		{
			Tbn_X.Text = "0";
			Tbn_Y.Text = "0";
			Tbn_Z.Text = "0";
			Cb_Gnrt.Checked = false;
			Cb_Loop.Checked = false;
			Cb_Sync.Checked = false;
		}

		public void Off ()
		{
			Tbn_X.Enabled = false;
			Tbn_Y.Enabled = false;
			Tbn_Z.Enabled = false;
			Cb_Gnrt.Enabled = false;
			Cb_Loop.Enabled = false;
			Cb_Sync.Enabled = false;
		}

		public void On ()
		{
			Tbn_X.Enabled = true;
			Tbn_Y.Enabled = true;
			Tbn_Z.Enabled = true;
			Cb_Gnrt.Enabled = true;
			Cb_Loop.Enabled = true;
			Cb_Sync.Enabled = true;
		}

		//データの設定
		public void SetEfPos ( Point pt )
		{
			if ( null == listBox1.SelectedItem ) { return; }
			EffectGenerate efGnrt = (EffectGenerate)listBox1.SelectedItem;
			efGnrt.Pt = pt;
			UpdateData ();
		}

		//追加
		private void Btn_Add_Click ( object sender, System.EventArgs e )
		{
			Effect ef = (Effect)cB_SequenceList1.SelectedItem;
			EffectGenerate efGnrt = new EffectGenerate ();
			efGnrt.Name = ef.Name;
			efGnrt.Id = cB_SequenceList1.SelectedIndex;
			efGnrt.Gnrt = Cb_Gnrt.Checked;
			efGnrt.Loop = Cb_Loop.Checked;
			efGnrt.Sync = Cb_Sync.Checked;
			Scp.ListGenerateEf.Add ( efGnrt );
			UpdateData ();
		}

		//削除
		private void Btn_Del_Click ( object sender, System.EventArgs e )
		{
			if ( null == listBox1.SelectedItem ) { return; }
			
			EffectGenerate efGnrt = (EffectGenerate)listBox1.SelectedItem;
			Scp.ListGenerateEf.Remove ( efGnrt );
			Scp.ListGenerateEf.ResetBindings ();
		}

		//チェックボックス
		private void Cb_Gnrt_CheckedChanged ( object sender, System.EventArgs e )
		{
			EffectGenerate efGnrt = (EffectGenerate)listBox1.SelectedItem;
			if ( null == efGnrt ) { return; }
			efGnrt.Gnrt = Cb_Gnrt.Checked;
		}

		private void Cb_Loop_CheckedChanged ( object sender, System.EventArgs e )
		{
			EffectGenerate efGnrt = (EffectGenerate)listBox1.SelectedItem;
			if ( null == efGnrt ) { return; }
			efGnrt.Loop = Cb_Loop.Checked;
		}

		private void Cb_Sync_CheckedChanged ( object sender, System.EventArgs e )
		{
			EffectGenerate efGnrt = (EffectGenerate)listBox1.SelectedItem;
			if ( null == efGnrt ) { return; }
			efGnrt.Sync = Cb_Sync.Checked;
		}
	}
}
