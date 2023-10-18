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
	TMS_TRAINING::TMS_TRAINING ()
	{
	}

	TMS_TRAINING::~TMS_TRAINING ()
	{
	}

	void TMS_TRAINING::Do ()
	{
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			//Parentとして２つ上る

			//Title_Introから下る
			m_pTitle_Intro.lock ()->Transit_Intro ();
		}
	}

	void TMS_TRAINING::Off ()
	{
	}
	void TMS_TRAINING::On ()
	{
	}


	//--------------------------------------------------------------
	TMS_1P_VS_2P::TMS_1P_VS_2P ()
	{
	}

	TMS_1P_VS_2P::~TMS_1P_VS_2P ()
	{
	}

	void TMS_1P_VS_2P::Do ()
	{
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			//Parentとして２つ上る

			//Title_Introから下る
			m_pTitle_Intro.lock ()->Transit_Intro ();
		}
	}

	void TMS_1P_VS_2P::Off ()
	{
	}
	void TMS_1P_VS_2P::On ()
	{
	}


	//--------------------------------------------------------------
	TMS_1P_VS_CPU::TMS_1P_VS_CPU ()
	{
	}

	TMS_1P_VS_CPU::~TMS_1P_VS_CPU ()
	{
	}

	void TMS_1P_VS_CPU::Do ()
	{
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			//Parentとして２つ上る

			//Title_Introから下る
			m_pTitle_Intro.lock ()->Transit_Intro ();
		}
	}

	void TMS_1P_VS_CPU::Off ()
	{
	}
	void TMS_1P_VS_CPU::On ()
	{
	}


	//--------------------------------------------------------------
	TMS_CPU_VS_CPU::TMS_CPU_VS_CPU ()
	{
	}

	TMS_CPU_VS_CPU::~TMS_CPU_VS_CPU ()
	{
	}

	void TMS_CPU_VS_CPU::Do ()
	{
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			//Parentとして２つ上る

			//Title_Introから下る
			m_pTitle_Intro.lock ()->Transit_Intro ();
		}
	}

	void TMS_CPU_VS_CPU::Off ()
	{
	}
	void TMS_CPU_VS_CPU::On ()
	{
	}


	//==============================================================
	//Menu_VS
	Title_Menu_VS::Title_Menu_VS ()
	{
		m_state_Training = make_shared < TMS_TRAINING > ();
		AddpTask ( m_state_Training );

		m_state_1P_VS_2P = make_shared < TMS_1P_VS_2P > ();
		AddpTask ( m_state_1P_VS_2P );

		m_state_1P_VS_CP = make_shared < TMS_1P_VS_CPU > ();
		AddpTask ( m_state_1P_VS_CP );

		m_state_CP_VS_CP = make_shared < TMS_CPU_VS_CPU > ();
		AddpTask ( m_state_CP_VS_CP );

		//		m_selectedState = m_state_VS;

		m_grp = make_shared < GrpAcv > ();
		m_grp->AddTexture ( _T ( "title_menu.png" ) );
		m_grp->SetPos ( VEC2 ( 100, 400 ) );
		AddpTask ( m_grp );
		GRPLST_INSERT_MAIN ( m_grp );

		m_grpCursor = make_shared < GrpAcv > ();
		m_grpCursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_grpCursor->SetPos ( VEC2 ( 80, 300 ) );
		AddpTask ( m_grpCursor );
		GRPLST_INSERT_MAIN ( m_grpCursor );
	}

	Title_Menu_VS::~Title_Menu_VS ()
	{
	}

	void Title_Menu_VS::SetwpTitle_Intro ( WP_Title_Intro p )
	{
		m_state_1P_VS_2P->SetwpTitle_Intro ( p );
	}

	void Title_Menu_VS::Load ()
	{
		Menu::SetpMenuItem ( m_state_Training );
		Menu::SetpMenuItem ( m_state_1P_VS_2P );
		Menu::SetpMenuItem ( m_state_1P_VS_CP );
		Menu::SetpMenuItem ( m_state_CP_VS_CP );
		Title_MenuState::Load ();
	}

	void Title_Menu_VS::Do ()
	{
		//選択
		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		{
			Menu::Next ();
		}
		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		{
			Menu::Prev ();
		}

		//カーソル位置
		m_grpCursor->SetPos ( VEC2 ( 80.f, 500.f + 64 * Menu::GetIdItem () ) );

		//動作
		//		m_selectedState->Do ();
		Title_MenuState::Do ();
	}

	void Title_Menu_VS::Off ()
	{
		m_state_1P_VS_2P->Off ();
		m_grp->SetValid ( F );
		m_grpCursor->SetValid ( F );
	}

	void Title_Menu_VS::On ()
	{
		m_state_1P_VS_2P->On ();
		m_grp->SetValid ( T );
		m_grpCursor->SetValid ( T );
	}

	//==============================================================


}	//namespace GAME

