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
			TAB_SCRIPT_A,	// 1 : "スクリプト(A)"
			TAB_EFFECT,     // 2 : "エフェクト"
			TAB_SCRIPT_E,	// 3 : "スクリプト(E)"
			TAB_COMMAND,    // 4 : "コマンド" 
			TAB_BRANCH,		// 5 : "ブランチ" 
			TAB_ROUTE,      // 6 : "ルート"
		}

		//タブ変更時
		private void tabControl1_SelectedIndexChanged ( object sender, EventArgs e )
		{
			//タブ	(enumをswitchの条件に用いるには(int)キャストが必要)
			switch ( tabControl1.SelectedIndex )
			{
				case (int)TAB_NAME.TAB_ACTION: tabAction_Selected (); break;
				case (int)TAB_NAME.TAB_SCRIPT_A: tabScript_A_Selected (); break;
				case (int)TAB_NAME.TAB_EFFECT: tabEffect_Selected (); break;
				case (int)TAB_NAME.TAB_SCRIPT_E: tabScript_E_Selected (); break;
				case (int)TAB_NAME.TAB_COMMAND: tabCommand_Selected (); break;
				case (int)TAB_NAME.TAB_BRANCH: tabBranch_Selected (); break;
				case (int)TAB_NAME.TAB_ROUTE: tabRoute_Selected (); break;
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
				case ( int ) TAB_NAME.TAB_SCRIPT_A: tabScript_A_Deselected (); break;
				case ( int ) TAB_NAME.TAB_EFFECT: tabEffect_Deselected (); break;
				case ( int ) TAB_NAME.TAB_SCRIPT_E: tabScript_E_Deselected (); break;
				case ( int ) TAB_NAME.TAB_COMMAND: tabCommand_Deselected (); break;
				case ( int ) TAB_NAME.TAB_BRANCH: tabBranch_Deselected (); break;
				case ( int ) TAB_NAME.TAB_ROUTE: tabRoute_Deselected (); break;
				default: Debug.Assert ( false, "タブの離去失敗" ); break;
			}
		}

		//フォーム閉止時
		private void Form1_FormClosing ( object sender, FormClosingEventArgs e )
		{
		}



		//-----------------------------------------------------------------------
		//[アクション]タブ選択時
		public void tabAction_Selected ()
		{
			ctrl_SqcList_Act.UpdateData ();
		}

		//[アクション]タブ離去時
		public void tabAction_Deselected ()
		{
			//アクション
			ctrl_SqcList_Act.ApplyData_Action ();
			All_Ctrl.Inst.Compend_Bhv.UpdateSqcTree ();
			All_Ctrl.Inst.UpdateData ();
		}

		//-----------------------------------------------------------------------
		//[スクリプト(A)]タブ選択時
		public void tabScript_A_Selected ()
		{
			//サブフォームすべてにコンペンド指定
			EditBehavior eb = EditChara.Inst.EditBehavior;
			SetEnvironment_SubForms ( eb );
			All_Ctrl.Inst.SetEditCompend ( eb );
		}

		//[スクリプト(A)]タブ離去時
		public void tabScript_A_Deselected ()
		{
			HideSubForms ();
		}

		//-----------------------------------------------------------------------
		//[エフェクト]タブ選択時
		public void tabEffect_Selected ()
		{
			ctrl_SqcList_Efc.UpdateData ();
		}

		//[エフェクト]タブ離去時
		public void tabEffect_Deselected ()
		{
			ctrl_SqcList_Efc.ApplyData_Effect ();
			All_Ctrl.Inst.Compend_Gns.UpdateSqcTree ();
			All_Ctrl.Inst.UpdateData ();
		}

		//-----------------------------------------------------------------------
		//[スクリプト(E)]
		public void tabScript_E_Selected ()
		{
			//コンペンド指定
			EditGarnish eg = EditChara.Inst.EditGarnish;
			SetEnvironment_SubForms ( eg );
			All_Ctrl.Inst.SetEditCompend ( eg );
		}

		//[スクリプト(E)]
		public void tabScript_E_Deselected ()
		{
			HideSubForms ();
		}


		//-----------------------------------------------------------------------
		public void tabCommand_Selected ()
		{
		}
		public void tabCommand_Deselected ()
		{
		}

		//-----------------------------------------------------------------------
		public void tabBranch_Selected ()
		{
			ctrl_Brc.SetCharaData ( chara );
		}
		public void tabBranch_Deselected ()
		{
		}

		//-----------------------------------------------------------------------
		public void tabRoute_Selected ()
		{
			ctrl_Rut.SetCharaData ( chara );
		}
		public void tabRoute_Deselected ()
		{
		}
	}
}
