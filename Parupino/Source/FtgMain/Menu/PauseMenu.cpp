//=================================================================================================
//
//	PauseMenu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "PauseMenu.h"
#include "../FtgMain.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	PauseMenu::PauseMenu ()
	{
		//--------------------------------------------
		m_grpStr_pause = make_shared < MenuString > ();
		m_grpStr_pause->SetStr ( _T ( "- PAUSE -" ) );
//		m_grpStr_pause->SetPos ( 500, 120 );
		m_grpStr_pause->SetPos ( 0, 120 );
//		m_grpStr_pause->SetZ ( Z_MENU - 0.01f );
		m_grpStr_pause->SetZ ( 0.40f );

		//@todo Z値が小さい(手前の)とき文字列が描画されないことの調査

		AddpTask ( m_grpStr_pause );
		GRPLST_INSERT_MAIN ( m_grpStr_pause );

		//--------------------------------------------
		m_bg = make_shared < PrmRect > ();
		m_bg->SetSize ( GAME_WINDOW_WIDTH - 200, GAME_WINDOW_HEIGHT - 200 );
		m_bg->SetAllColor ( 0x80000000 );
		m_bg->SetPos ( 100, 100 );
//		m_bg->SetZ ( Z_MENU + 0.01f );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

#if 0
		//--------------------------------------------
		//メニュー項目
		m_mi_title = make_shared < PMI_To_Title > ();
		m_mi_resume = make_shared < PMI_ResumeGame > ();

		//--------------------------------------------
		//カーソル
		m_cursor = make_shared < GrpAcv > ();
		m_cursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_cursor->SetPos ( 100, 300 );
		m_cursor->SetZ ( Z_MENU - 0.01f);
		AddpTask ( m_cursor );
		GRPLST_INSERT_MAIN ( m_cursor );

		//--------------------------------------------
		//Y/Nメニュ
		m_yesnoMenu = make_shared < YesNo_Menu > ();
		AddpTask ( m_yesnoMenu );

		//--------------------------------------------
		Off ();
//		On ();
#endif // 0
	}

	PauseMenu::~PauseMenu ()
	{
	}

	void PauseMenu::Load ()
	{
#if 0
		Menu::SetpMenuItem ( m_mi_title );
		Menu::SetpMenuItem ( m_mi_resume );
#endif // 0
		Menu::Load ();
	}

	void PauseMenu::Do ()
	{
	}

	void PauseMenu::Move ()
	{
#if 0
		//Y/Nメニュ稼働時は何もしない
		if ( m_yesnoMenu->GetActive () )
		{
			Menu::Move ();
			return;
		}

		//非アクティブ時は何もしない
		if ( ! GetActive () ) { Menu::Move (); return; }

		//メニュポーズ解除
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
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) || CFG_PUSH_KEY ( _P2_BTN0 ) )
		{
			Menu::Decide ();
		}

		//Do()は選択されたメニュ項目について常に行う
		Menu::Do ();

		//カーソル位置
		m_cursor->SetPos ( 100.f, 300.f + 100 * Menu::GetIdItem () );

#endif // 0
		Menu::Move ();
	}

	void PauseMenu::Off ()
	{
		m_bg->SetValid ( F );
		m_grpStr_pause->SetValid ( F );
		m_cursor->SetValid ( F );

		m_mi_title->Off ();
		m_mi_resume->Off ();

		SetActive ( F );
	}

	void PauseMenu::On ()
	{
		m_bg->SetValid ( T );
		m_grpStr_pause->SetValid ( T );
		m_cursor->SetValid ( T );

		m_mi_title->On ();
		m_mi_resume->On ();

		SetActive ( T );
	}

	void PauseMenu::SetwpParent ( WP_FtgMain p )
	{
#if 0
		m_mi_title->SetwpParent ( shared_from_this () );
		m_mi_resume->SetwpParent ( shared_from_this () );

		m_yesnoMenu->SetwpParent ( p );
#endif // 0
	}

}	//namespace GAME

