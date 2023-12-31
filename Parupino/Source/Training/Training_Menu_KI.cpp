//=================================================================================================
//
//	Training_Menu_KeyInput
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Training_Menu_KI.h"
#include "../Menu/PauseMenu_Const.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Training_Menu_KI::Training_Menu_KI ()
	{
		//背景
		m_bg = make_shared < PrmRect > ();
		m_bg->SetColor ( _CLR ( 0x80000000 ) );
		m_bg->SetSize ( 1000, 800 );
		m_bg->SetPos ( 140, 80 );
		m_bg->SetZ ( Z_MENU_KI_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		//キー見出
		m_keyIndex = make_shared < GrpAcv > ();
		m_keyIndex->AddTexture ( _T ( "KeyIndex2.png" ) );
		m_keyIndex->SetPos ( 300, 400 );
		m_keyIndex->SetZ ( Z_MENU_KI_STR );
		AddpTask ( m_keyIndex );
		GRPLST_INSERT_MAIN ( m_keyIndex );

		//選択カーソル
		m_selectRect = make_shared < GrpAcv > ();
		m_selectRect->AddTexture ( _T ( "SelectRect.png" ) );
		m_selectRect->SetPos ( 300, 400 );
		m_selectRect->SetZ ( Z_MENU_KI_STR );
		AddpTask ( m_selectRect );
		GRPLST_INSERT_MAIN ( m_selectRect );
	}

	Training_Menu_KI::~Training_Menu_KI ()
	{
	}

	void Training_Menu_KI::Load ()
	{
		Menu::Load ();
	}

	void Training_Menu_KI::Off ()
	{
		m_bg->SetValid ( F );
		m_keyIndex->SetValid ( F );
		m_selectRect->SetValid ( F );
		Menu::Off ();
	}

	void Training_Menu_KI::On ()
	{
		m_bg->SetValid ( T );
		m_keyIndex->SetValid ( T );
		m_selectRect->SetValid ( T );
		Menu::On ();
	}


	//Active == T のみ実行される
	void Training_Menu_KI::Active ()
	{
		//戻る
		if ( CFG_PUSH_KEY ( _P1_BTN1 ) || CFG_PUSH_KEY ( _P2_BTN1 ) )
		{
			Off ();
		}
	}

}	//namespace GAME

