//=================================================================================================
//
//	PauseMenu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "PauseMenu.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	PauseMenu::PauseMenu ()
	{
		m_bg = make_shared < PrmRect > ();
		m_bg->SetSize ( GAME_WINDOW_WIDTH - 200, GAME_WINDOW_HEIGHT - 200 );
		m_bg->SetAllColor ( 0x80000000 );
		m_bg->SetPos ( 100, 100 );
		m_bg->SetZ ( Z_MENU + 0.01f );
		GRPLST_INSERT ( m_bg );

		//--------------------------------------------
		m_grpStr_pause = make_shared < MenuString > ();
		m_grpStr_pause->SetStr ( _T ( "- PAUSE -" ) );
		m_grpStr_pause->SetPos ( 500, 120 );
		GRPLST_INSERT ( m_grpStr_pause );

		m_grpStr_title = make_shared < MenuString > ();
		m_grpStr_title->SetStr ( _T ( "タイトルに戻る" ) );
		m_grpStr_title->SetPos ( 200, 300 );
		GRPLST_INSERT ( m_grpStr_title );

		m_grpStr_resume = make_shared < MenuString > ();
		m_grpStr_resume->SetStr ( _T ( "ゲームに戻る" ) );
		m_grpStr_resume->SetPos ( 200, 400 );
		GRPLST_INSERT ( m_grpStr_resume );

		//--------------------------------------------
		m_mi_title = make_shared < PauseMenuItem > ();
		Menu::SetMenuItem ( m_mi_title );
		m_mi_resume = make_shared < PauseMenuItem > ();
		Menu::SetMenuItem ( m_mi_resume );

		//--------------------------------------------
		m_cursor = make_shared < GrpAcv > ();
		m_cursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_cursor->SetPos ( 100, 300 );
		m_cursor->SetZ ( Z_MENU - 0.01f);
		AddpTask ( m_cursor );

		//--------------------------------------------
		Off ();
	}

	PauseMenu::~PauseMenu ()
	{
	}

	void PauseMenu::Move ()
	{
		//ポーズ解除
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) )
		{
			Off ();
		}

		//選択
		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		{
			Menu::Next ();
		}
		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		{
			Menu::Prev ();
		}

		//決定
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			Menu::Do ();
		}

		m_cursor->SetPos ( 100.f, 300.f + 100 * Menu::GetIdItem () );

		Menu::Move ();
	}

	void PauseMenu::On ()
	{
		m_bg->SetValid ( T );
		m_grpStr_pause->SetValid ( T );
		m_grpStr_title->SetValid ( T );
		m_grpStr_resume->SetValid ( T );
		m_cursor->SetValid ( T );

		SetActive ( T );
	}

	void PauseMenu::Off ()
	{
		m_bg->SetValid ( F );
		m_grpStr_pause->SetValid ( F );
		m_grpStr_title->SetValid ( F );
		m_grpStr_resume->SetValid ( F );
		m_cursor->SetValid ( F );

		SetActive ( F );
	}


}	//namespace GAME

