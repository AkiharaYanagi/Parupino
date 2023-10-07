//=================================================================================================
//
//	YesNo_Menu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "YesNo_Menu.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	YesNo_Menu::YesNo_Menu ()
	{
		//--------------------------------------------
		m_bg = make_shared < PrmRect > ();
		m_bg->SetSize ( 200, 200 );
		m_bg->SetAllColor ( 0x80000000 );
		float center = GAME_WINDOW_WIDTH * 0.5f;
		m_bg->SetPos ( center - (m_bg->GetSize().x * 0.5f), 100 );
		m_bg->SetZ ( Z_MENU - 0.01f );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		m_grpStr_yesno = make_shared < MenuString > ();
		m_grpStr_yesno->SetStr ( _T ( "- 確認 -" ) );
		m_grpStr_yesno->SetZ ( Z_MENU - 0.01f );
		AddpTask ( m_grpStr_yesno );
		GRPLST_INSERT_MAIN ( m_grpStr_yesno );

		//Off ();
		On ();
	}

	YesNo_Menu::~YesNo_Menu ()
	{
	}

	void YesNo_Menu::Move ()
	{
		float center = GAME_WINDOW_WIDTH * 0.5f;
		m_grpStr_yesno->SetPos ( center - ( m_grpStr_yesno->GetSize ().w * 0.5f ), 120 );
		Menu::Move ();
	}

	void YesNo_Menu::On ()
	{
	}

	void YesNo_Menu::Off ()
	{
	}

	void YesNo_Menu::SetpParent ( P_FtgMain p )
	{
	}

}	//namespace GAME

