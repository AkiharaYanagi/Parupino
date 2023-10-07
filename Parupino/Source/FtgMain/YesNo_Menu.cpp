//=================================================================================================
//
//	YesNo_Menu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "YesNo_Menu.h"
#include "FtgMain.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	YesNo_Menu::YesNo_Menu ()
	{
		//--------------------------------------------
		m_bg = make_shared < PrmRect > ();
		m_bg->SetSize ( 500, 200 );
		m_bg->SetAllColor ( 0x80000000 );
		float center = GAME_WINDOW_WIDTH * 0.5f;
		m_bg->SetPos ( center - (m_bg->GetSize().x * 0.5f), 400 );
		m_bg->SetZ ( Z_MENU - 0.01f );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		const int FONTSIZE = 60;
		m_grpStr_yesno = make_shared < MenuString > ();
		m_grpStr_yesno->SetFontParam ( FONTSIZE, 2, 2 );
		m_grpStr_yesno->SetStr ( _T ( "- 終了します -" ) );
		m_grpStr_yesno->SetZ ( Z_MENU - 0.01f );
		AddpTask ( m_grpStr_yesno );
		GRPLST_INSERT_MAIN ( m_grpStr_yesno );

		m_grpStr_yes = make_shared < MenuString > ();
		m_grpStr_yes->SetFontParam ( FONTSIZE, 2, 2 );
		m_grpStr_yes->SetStr ( _T ( "はい" ) );
		m_grpStr_yes->SetZ ( Z_MENU - 0.01f );
		AddpTask ( m_grpStr_yes );
		GRPLST_INSERT_MAIN ( m_grpStr_yes );

		m_grpStr_no = make_shared < MenuString > ();
		m_grpStr_no->SetFontParam ( FONTSIZE, 2, 2 );
		m_grpStr_no->SetStr ( _T ( "いいえ" ) );
		m_grpStr_no->SetZ ( Z_MENU - 0.01f );
		AddpTask ( m_grpStr_no );
		GRPLST_INSERT_MAIN ( m_grpStr_no );

		//--------------------------------------------
		m_cursor = make_shared < GrpAcv > ();
		m_cursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_cursor->SetPos ( 380, 500 );
		m_cursor->SetZ ( Z_MENU - 0.01f );
		AddpTask ( m_cursor );
		GRPLST_INSERT_MAIN ( m_cursor );

		//--------------------------------------------
		//メニュー項目
		m_yes = make_shared < YNM_Item_Yes > ();
		Menu::SetMenuItem ( m_yes );
		m_no = make_shared < YNM_Item_No > ();
		Menu::SetMenuItem ( m_no );

		//--------------------------------------------
		Off ();
		//On ();
	}

	YesNo_Menu::~YesNo_Menu ()
	{
	}

	void YesNo_Menu::Load ()
	{
		Menu::Load ();
	}

	void YesNo_Menu::Init ()
	{
		const float center = GAME_WINDOW_WIDTH * 0.5f;
		const float by = 400;
		m_grpStr_yesno->SetPos ( center - 140, by );
		m_grpStr_yes->SetPos ( 510, by + 100 );
		m_grpStr_no->SetPos ( 720, by + 100 );

		Menu::Init ();
	}

	void YesNo_Menu::Move ()
	{
		//非アクティブ時は何もしない
		if ( ! GetActive () ) { Menu::Move (); return; }

		//選択
		if ( CFG_PUSH_KEY ( _P1_RIGHT ) || CFG_PUSH_KEY ( _P2_RIGHT ) )
		{
			Menu::Next ();
		}
		if ( CFG_PUSH_KEY ( _P1_LEFT ) || CFG_PUSH_KEY ( _P2_LEFT ) )
		{
			Menu::Prev ();
		}

		//ON後１[F]待つ
		static bool wait = false;
		if ( wait )
		{
			//決定
			if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
			{
				Menu::Do ();
			}
		}
		wait = true;

		//カーソル位置
		m_cursor->SetPos ( 380.f + 210 * Menu::GetIdItem (), 500.f );

		Menu::Move ();
	}

	void YesNo_Menu::On ()
	{
		m_bg->SetValid ( T );
		m_grpStr_yesno->SetValid ( T );
		m_grpStr_yes->SetValid ( T );
		m_grpStr_no->SetValid ( T );
		m_cursor->SetValid ( T );
		SetActive ( T );
	}

	void YesNo_Menu::Off ()
	{
		m_bg->SetValid ( F );
		m_grpStr_yesno->SetValid ( F );
		m_grpStr_yes->SetValid ( F );
		m_grpStr_no->SetValid ( F );
		m_cursor->SetValid ( F );
		SetActive ( F );
	}

	void YesNo_Menu::SetpParent ( P_FtgMain p )
	{
		m_yes->SetpFtgMain ( p );
		m_no->SetpParent ( shared_from_this () );
	}

	//===================================================

	//決定　タイトルに戻る
	void YNM_Item_Yes::Do ()
	{
		mp_FtgMain->Transit_Title ();
	}

	//キャンセル 自メニュを閉じる
	void YNM_Item_No::Do ()
	{
		mp_parent->Off ();
	}



}	//namespace GAME

