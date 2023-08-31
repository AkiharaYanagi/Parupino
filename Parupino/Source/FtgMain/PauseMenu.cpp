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

#if 0
		//--------------------------------------------
		OutlineFont::Inst ()->SetParam ( 40, 1, 3 );
		OutlineFont::Inst ()->SetFontFace ( _T ( "MSゴシック" ) );
		m_test = make_shared < Str > ();
		m_test->SetPos ( VEC2 ( 200, 200 ) );
		m_test->SetStr ( _T ( "test." ) );
		AddpTask ( m_test );
#endif // 0

		//--------------------------------------------
		m_grpStr = make_shared < GrpStr > ();
		m_grpStr->SetStr ( _T ( "タイトルに戻る" ) );
		m_grpStr->SetFontParam ( 80, 2, 2 );
		m_grpStr->SetFontFace ( _T ( "MSゴシック" ) );
		m_grpStr->SetFontColor ( 0xff8080ff, 0xffffffff );
		m_grpStr->SetPos ( 200, 300 );
		m_grpStr->SetZ ( Z_MENU );
		GRPLST_INSERT ( m_grpStr );

		//--------------------------------------------
		m_grpStr_resume = make_shared < GrpStr > ();
		m_grpStr_resume->SetStr ( _T ( "ゲームに戻る" ) );
		m_grpStr_resume->SetFontParam ( 80, 2, 2 );
		m_grpStr_resume->SetFontFace ( _T ( "MSゴシック" ) );
		m_grpStr_resume->SetFontColor ( 0xff8080ff, 0xffffffff );
		m_grpStr_resume->SetPos ( 200, 400 );
		m_grpStr_resume->SetZ ( Z_MENU );
		GRPLST_INSERT ( m_grpStr_resume );

	}

	PauseMenu::~PauseMenu ()
	{
	}


}	//namespace GAME

