using System;
using System.Windows.Forms;
using System.Diagnostics;

namespace ScriptEditor
{
	public partial class FormMain : Form
	{
		//==================================================================================
		//タブ
		//==================================================================================
		//タブ名
		public enum TAB_NAME
		{
			TAB_ACTION,     // 0 : "アクション"
			TAB_EFFECT,     // 1 : "エフェクト"
			TAB_COMMAND,    // 2 : "コマンド" 
			TAB_BRANCH,		// 3 : "ブランチ" 
			TAB_ROUTE,      // 4 : "ルート"
		}

		//タブ変更時
		private void tabControl1_SelectedIndexChanged ( object sender, EventArgs e )
		{
			//タブ	(enumはintキャストが必要)
			switch ( tabControl1.SelectedIndex )
			{
				case ( int ) TAB_NAME.TAB_ACTION: tabAction_Selected (); break;
				case ( int ) TAB_NAME.TAB_EFFECT: tabEffect_Selected (); break;
				case ( int ) TAB_NAME.TAB_COMMAND: tabCommand_Selected (); break;
				case ( int ) TAB_NAME.TAB_BRANCH: tabChara_Selected (); break;
				case ( int ) TAB_NAME.TAB_ROUTE: tabChara_Selected (); break;
				default: Debug.Assert ( false, "タブの選択失敗" ); break;
			}
		}

		//タブ離去時
		private void tabControl1_Deselected ( object sender, TabControlEventArgs e )
		{
			//タブ	(enumはintキャストが必要)
			switch ( tabControl1.SelectedIndex )
			{
				case ( int ) TAB_NAME.TAB_ACTION: tabAction_Deselected (); break;
				case ( int ) TAB_NAME.TAB_EFFECT: tabEffect_Deselected (); break;
				case ( int ) TAB_NAME.TAB_COMMAND: tabCommand_Deselected (); break;
				case ( int ) TAB_NAME.TAB_BRANCH: tabChara_Selected (); break;
				case ( int ) TAB_NAME.TAB_ROUTE: tabChara_Selected (); break;
				default: Debug.Assert ( false, "タブの離去失敗" ); break;
			}
		}

		//タブ閉止時
		private void Form1_FormClosing ( object sender, FormClosingEventArgs e )
		{
		}

		//[アクション]タブ選択時
		public void tabAction_Selected ()
		{
			//共通フォームにビヘイビアを設定
			EditBehavior eb = EditChara.Inst.EditBehavior;
			Assosiate ( eb.SelectedSequence, eb.SelectedScript );
			eb.SelectScript ( 0, 0 );

			//イメージフォームにビヘイビアを設定
			FormImage.Inst.Set ( eb.Compend.BD_Image );
			FormImage.Inst.EditCompend = eb;
		}

		//[アクション]タブ離去時
		public void tabAction_Deselected ()
		{
			FormImage.Inst.Hide ();
			FormAction.Inst.Hide ();
			FormScript.Inst.Hide ();
			FormRect.Inst.Hide ();
			FormEfGnrt.Inst.Hide ();
		}

		public void tabEffect_Selected ()
		{
			//共通フォームにガーニッシュを設定
			EditGarnish eg = EditChara.Inst.EditGarnish;
			Assosiate ( eg.SelectedSequence, eg.SelectedScript );
			eg.SelectScript ( 0, 0 );

			//イメージフォームにガーニッシュを設定
			//FormImage.Inst.SetTarget ( eg.Compend.BD_Image.GetBindingList () );
			FormImage.Inst.Set ( eg.Compend.BD_Image );
			FormImage.Inst.EditCompend = eg;
		}

		public void tabEffect_Deselected ()
		{

		}

		public void tabCommand_Selected ()
		{

		}
		public void tabCommand_Deselected ()
		{

		}

		public void tabChara_Selected ()
		{

		}
		public void tabChara_Deselected ()
		{

		}
	}
}
