using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.IO;
using System.Text;


namespace ScriptEditor
{
	using L_Scp = List < Script >;


	//-------------------------------------------------------------
	//	スクリプトリスト操作フォーム
	//-------------------------------------------------------------
	public sealed class Form_ScriptList : SubForm_Compend
	{
		//コントロール
		private Ctrl_ScriptList ctrl_Scpls = new Ctrl_ScriptList ();

		//---------------------------------------------------------------------
		//シングルトン実体
		public static Form_ScriptList Inst { get; } = new Form_ScriptList ();

		//プライベートコンストラクタ
		private Form_ScriptList ()
		{
			InitializeComponent ();
			LoadObject ();
			this.Controls.Add ( ctrl_Scpls );

#if false
			textBox1.Text = "";
			Btn_Replace.Enabled = false;
#endif
		}
		//---------------------------------------------------------------------

		private void InitializeComponent ()
		{
			this.SuspendLayout();
			// 
			// Form_ScriptList
			// 
			this.ClientSize = new System.Drawing.Size(318, 336);
			this.Name = "Form_ScriptList";
			this.Text = "ScriptList";
			this.ResumeLayout(false);

		}

		//コンペンド編集の切り替え
		public override void SetEditCompend ( EditCompend ec )
		{
			ctrl_Scpls.SetEditCompend ( ec );
			base.SetEditCompend ( ec );
		}

#if false
		//---------------------------------------------------------------------

		public void SetEnvironment ( EditCompend ec )
		{
			EditCompend = ec;
		}

		//書出
		private void Btn_Save_Click ( object sender, EventArgs e )
		{
			using ( SaveFileDialog sfd = new SaveFileDialog () )
			{
				sfd.DefaultExt = "txt";
				sfd.InitialDirectory = Directory.GetCurrentDirectory ();
				sfd.FileName = "ScriptList.txt";

				if ( sfd.ShowDialog () == DialogResult.OK )
				{
					using ( StreamWriter sw = new StreamWriter ( sfd.FileName, false, Encoding.UTF8 ) )
					{
						Chara ch = EditChara.Inst.Chara;
						CharaToDoc ctod = new CharaToDoc ();
						ctod.WriteListScript ( ch, sw, EditCompend.Compend, EditCompend.SelectedSequence.ListScript ) ;
					}
				}
			}
			
		}

		//読込
		private void Btn_Load_Click ( object sender, EventArgs e )
		{
			using ( OpenFileDialog ofd = new OpenFileDialog () )
			{
				ofd.DefaultExt = "txt";
				ofd.InitialDirectory = Directory.GetCurrentDirectory ();
				ofd.FileName = "ScriptList.txt";

				if ( ofd.ShowDialog () == DialogResult.OK )
				{
					using ( StreamReader sr = new StreamReader ( ofd.FileName, Encoding.UTF8 ) )
					{
						Document doc = new Document ( sr.BaseStream );
						DocToChara dtoc = new DocToChara ();
						Sequence sqc = new Sequence ();
						dtoc.ReadScriptList ( sqc, doc.Root.Elements );

						//選択
						string name = EditCompend.SelectedSequence.Name;
						EditCompend.SelectedSequence.CopyScpList ( sqc );
						EditCompend.SelectSequence ( name );
						
						//表示の更新
						//DispChara.Inst.Disp ();
					}
				}
			}
		}

		//============================================

		//部分コピー
		private L_Scp L_Script = new L_Scp ();
		private void Btn_Copy_Click ( object sender, EventArgs e )
		{
		}

		//全部コピー
		private void Btn_AllCpy_Click ( object sender, EventArgs e )
		{
			L_Scp ls = EditCompend.SelectedSequence.ListScript;
			L_Script = new L_Scp ();
			foreach ( Script scp in ls )
			{
				L_Script.Add ( new Script ( scp ) );
			}

			string name = EditCompend.SelectedSequence.Name;
			textBox1.Text = name + "[0]...[" + ls.Count + "]";
			Btn_Replace.Enabled = true;
		}

		//------------------------------------------------------------
		//置換 リプレイス
		private void Btn_Replace_Click ( object sender, EventArgs e )
		{
			if ( textBox1.Text == "" ) { return; }

			L_Scp ls = EditCompend.SelectedSequence.ListScript;
			ls.Clear ();
			foreach ( Script scp in L_Script )
			{
				ls.Add ( new Script ( scp ) );
			}

			//選択
			EditCompend.SelectSequence ( EditCompend.SelectedSequence.Name );
			
			//表示更新
			//DispChara.Inst.Disp ();
			All_Ctrl.Inst.UpdateData ();
		}

		private void Btn_Add_Click ( object sender, EventArgs e )
		{

		}

		private void Btn_Ins_Click ( object sender, EventArgs e )
		{

		}

	}
#endif

	}
}
