//=================================================================================================
//
//	PauseMenuItem
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "PauseMenuItem.h"
#include "PauseMenu.h"
#include "PauseMenu_Const.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=========================================================

	PMI_To_Title::PMI_To_Title ()
	{
		m_grpStr_title = make_shared < MenuString > ();
		m_grpStr_title->SetStr ( _T ( "タイトルに戻る" ) );
		m_grpStr_title->SetPos ( 200, 300 );
		m_grpStr_title->SetZ ( Z_MENU_STR );
		AddpTask ( m_grpStr_title );
		GRPLST_INSERT_MAIN ( m_grpStr_title );
	}

	PMI_To_Title::~PMI_To_Title ()
	{
	}

	void PMI_To_Title::Do ()
	{
		PauseMenuItem::Do ();
	}

	void PMI_To_Title::Decide ()
	{
		P_PauseMenu p = dynamic_pointer_cast < PauseMenu > ( mwp_Parent.lock () );
		p->OpenYNMenu ();
	}

	void PMI_To_Title::Off ()
	{
		m_grpStr_title->SetValid ( F );
	}

	void PMI_To_Title::On ()
	{
		m_grpStr_title->SetValid ( T );
	}

	//--------------------------------------------------------------
	PMI_ResumeGame::PMI_ResumeGame ()
	{
		m_grpStr_resume = make_shared < MenuString > ();
		m_grpStr_resume->SetStr ( _T ( "ゲームに戻る" ) );
		m_grpStr_resume->SetPos ( 200, 400 );
		m_grpStr_resume->SetZ ( Z_MENU_STR );
		AddpTask ( m_grpStr_resume );
		GRPLST_INSERT_MAIN ( m_grpStr_resume );
	}

	PMI_ResumeGame::~PMI_ResumeGame ()
	{
	}

	void PMI_ResumeGame::Do ()
	{
		PauseMenuItem::Do ();
	}

	void PMI_ResumeGame::Decide ()
	{
		P_PauseMenu p = dynamic_pointer_cast <PauseMenu> ( mwp_Parent.lock () );
		p->Off ();
	}

	void PMI_ResumeGame::Off ()
	{
		m_grpStr_resume->SetValid ( F );
	}

	void PMI_ResumeGame::On ()
	{
		m_grpStr_resume->SetValid ( T );
	}

	//=========================================================

}	//namespace GAME

