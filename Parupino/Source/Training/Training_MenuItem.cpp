//=================================================================================================
//
//	Training_MenuItem
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Training_MenuItem.h"
#include "../Menu/PauseMenu.h"
#include "../Menu/PauseMenu_Const.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Training_MenuItem::Training_MenuItem ()
	{
		//文字列
		m_str_KI = make_shared < MenuString > ();
		m_str_KI->SetStr ( _T ( "キー入力編集" ) );
		m_str_KI->SetPos ( 200, 500 );
		m_str_KI->SetZ ( Z_MENU_STR );
		AddpTask ( m_str_KI );
		GRPLST_INSERT_MAIN ( m_str_KI );

		//メニュ
		m_ki = make_shared < Training_Menu_KI > ();
		AddpTask ( m_ki );
		m_ki->Off ();
	}

	Training_MenuItem::~Training_MenuItem ()
	{
	}

	void Training_MenuItem::Off ()
	{
		m_str_KI->SetValid ( F );
		PauseMenuItem::Off ();
	}

	void Training_MenuItem::On ()
	{
		m_str_KI->SetValid ( T );
		PauseMenuItem::On ();
	}

	void Training_MenuItem::Decide ()
	{
		auto p = dynamic_pointer_cast < PauseMenu > ( mwp_Parent.lock () );
		p->UnDisp ();

		m_ki->On ();

		PauseMenuItem::Decide ();
	}

}	//namespace GAME

