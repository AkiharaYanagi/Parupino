//=================================================================================================
//
//	タイトル メニュ アクタ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_Menu_VS.h"
#include "Title_Intro.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==============================================================
	//State

	//--------------------------------------------------------------
	//Title_MenuState

	//--------------------------------------------------------------
	TMS_VS::TMS_VS ()
	{
		m_grp = make_shared < GrpAcv > ();
		m_grp->AddTexture ( _T ( "title_menu.png" ) );
		m_grp->SetPos ( VEC2 ( 100, 300 ) );
		AddpTask ( m_grp );
		GRPLST_INSERT_MAIN ( m_grp );
	}

	TMS_VS::~TMS_VS ()
	{
	}

	void TMS_VS::Do ()
	{
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			m_pTitle_Intro->Transit_Intro ();
		}
	}


	//==============================================================
	//Menu_VS
	Title_Menu_VS::Title_Menu_VS ()
	{
		m_state_VS = make_shared < TMS_VS > ();
		AddpTask ( m_state_VS );

		m_selectedState = m_state_VS;


		m_grpCursor = make_shared < GrpAcv > ();
		m_grpCursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_grpCursor->SetPos ( VEC2 ( 80, 300 ) );
		AddpTask ( m_grpCursor );
		GRPLST_INSERT_MAIN ( m_grpCursor );
	}

	Title_Menu_VS::~Title_Menu_VS ()
	{
	}

	void Title_Menu_VS::SetpParent ( P_Title_Intro p )
	{
		m_state_VS->SetpParent ( p );
	}

	void Title_Menu_VS::Do ()
	{
		m_selectedState->Do ();
	}
	//==============================================================


}	//namespace GAME

