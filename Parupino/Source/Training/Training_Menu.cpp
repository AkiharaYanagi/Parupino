//=================================================================================================
//
//	Training_Menu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Training_Menu.h"
#include "../Menu/PauseMenu_Const.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Training_Menu::Training_Menu ()
	{
		//--------------------------------------------
		//メニュー項目
		m_testItem = make_shared < Training_MenuItem > ();
		AddpTask ( m_testItem );
		//--------------------------------------------

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

		//--------------------------------------------
		Off ();
	}

	Training_Menu::~Training_Menu ()
	{
	}

	void Training_Menu::Load ()
	{
		PauseMenu::Load ();

		//--------------------------------------------
		//メニュー項目 (追加分なので基底の後で実行)
		Menu::SetpMenuItem ( m_testItem );
		//--------------------------------------------
	}

	void Training_Menu::Off ()
	{
		m_testItem->Off ();
		m_keyIndex->SetValid ( F );
		m_selectRect->SetValid ( F );

		PauseMenu::Off ();
	}

	void Training_Menu::On ()
	{
		m_testItem->On ();
		m_keyIndex->SetValid ( T );
		m_selectRect->SetValid ( T );

		PauseMenu::On ();
	}

}	//namespace GAME

