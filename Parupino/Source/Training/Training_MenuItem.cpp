//=================================================================================================
//
//	Training_MenuItem
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Training_MenuItem.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Training_MenuItem::Training_MenuItem ()
	{
		m_grpStr_test = make_shared < MenuString > ();
		m_grpStr_test->SetStr ( _T ( "トレーニングメニュ テスト" ) );
		m_grpStr_test->SetPos ( 200, 500 );
		m_grpStr_test->SetZ ( Z_MENU - 0.01f );
		AddpTask ( m_grpStr_test );
		GRPLST_INSERT_MAIN ( m_grpStr_test );
	}

	Training_MenuItem::~Training_MenuItem ()
	{
	}

	void Training_MenuItem::Off ()
	{
		m_grpStr_test->SetValid ( F );
		PauseMenuItem::Off ();
	}

	void Training_MenuItem::On ()
	{
		m_grpStr_test->SetValid ( T );
		PauseMenuItem::On ();
	}

}	//namespace GAME

