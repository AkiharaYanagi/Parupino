//=================================================================================================
//
//	タイトル メニュ スタート状態
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_Menu_Start.h"
#include "../GameMain/SoundConst.h"
#include "Title.h"


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
	TMS_VS::TMS_VS ()
	{
		m_grpVS = make_shared < GrpAcv > ();
		m_grpVS->AddTexture ( _T ( "TitleMenu_Fighting.png" ) );
		m_grpVS->SetPos ( VEC2 ( MENU_X, MENU_Y_0 ) );
		AddpTask ( m_grpVS );
		GRPLST_INSERT_MAIN ( m_grpVS );

		m_expl = make_shared < Title_Explain > ();
		m_expl->AddTexture ( _T ( "Title_explain_Fighting.png" ) );
		m_expl->SetBase ( VEC2 ( EXPLAIN_X, EXPLAIN_Y ) );
		AddpTask ( m_expl );
		GRPLST_INSERT_MAIN ( m_expl );
	}

	TMS_VS::~TMS_VS ()
	{
	}

	void TMS_VS::Do ()
	{
		m_expl->Do ();

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) || CFG_PUSH_KEY ( _P2_BTN0 ) )
		{
			//SOUND
			SOUND->Play_SE ( SE_Sys_Enter );

			m_pTitle.lock ()->Select_VS ();
//			mwp_parent.lock ()->Select_VS ();
		}
	}

	void TMS_VS::Off ()
	{
		m_grpVS->SetValid ( F );
		m_expl->SetValid ( F );
	}

	void TMS_VS::On ()
	{
		m_grpVS->SetValid ( T );
	}

	void TMS_VS::Unselect ()
	{
		m_expl->SetValid ( F );
	}


	//--------------------------------------------------------------
	TMS_Intro::TMS_Intro ()
	{
		m_grpIntro = make_shared < GrpAcv > ();
		m_grpIntro->AddTexture ( _T ( "TitleMenu_Introduction.png" ) );
		m_grpIntro->SetPos ( VEC2 ( MENU_X, MENU_Y_1 ) );
		AddpTask ( m_grpIntro );
		GRPLST_INSERT_MAIN ( m_grpIntro );

		m_expl = make_shared < Title_Explain > ();
		m_expl->SetBase ( VEC2 ( EXPLAIN_X, EXPLAIN_Y ) );
		m_expl->AddTexture ( _T ( "Title_explain_Introduction.png" ) );
		AddpTask ( m_expl );
		GRPLST_INSERT_MAIN ( m_expl );

		//フェード
		m_fade = make_shared < PrmRect > ();
		m_fade->SetSize ( VEC2 ( 1280, 960 ) );
		m_fade->SetPos ( VEC2 ( 0, 0 ) );
		m_fade->SetAllColor ( 0x00000000 );
		m_fade->SetZ ( Z_FADE );
		m_fade->SetValid ( F );
		AddpTask ( m_fade );
		GRPLST_INSERT_MAIN ( m_fade );

		m_wait = 0;
		m_startWait = 0;
	}

	TMS_Intro::~TMS_Intro ()
	{
	}

	void TMS_Intro::Do ()
	{
		m_expl->Do ();

		//終了フェードウェイト中
		if ( m_wait != 0 )
		{
			++m_wait;

			if ( m_wait > 6 )
			{
				//BGM
				SOUND->Stop_BGM ( BGM_Title );

				//m_pTitle_Intro.lock ()->Transit_Intro ();
				mwp_Scene.lock ()->Transit_Intro ();

				m_wait = 0;
			}
			return;
		}

		//開始入力待ち
		if ( m_startWait == 0 )
		{
			m_startWait = 1; return;
		}

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) || CFG_PUSH_KEY ( _P2_BTN0 ) )
		{
			//SOUND
			SOUND->Play_SE ( SE_Sys_Enter );
			SOUND->Stop_BGM ( BGM_Title );

//			m_pTitle_Intro.lock()->Transit_Intro ();
			mwp_Scene.lock ()->Transit_Intro ();

			//フェード開始
			m_fade->SetFade ( 5, _CLR ( 0x00000000UL ), _CLR ( 0xff000000UL ) );	//開始値、目標値を手動設定
			m_wait = 1;
		}
	}

	void TMS_Intro::Off ()
	{
		m_grpIntro->SetValid ( F );
		m_expl->SetValid ( F );
	}

	void TMS_Intro::On ()
	{
		m_grpIntro->SetValid ( T );
	}

	void TMS_Intro::Unselect ()
	{
		m_expl->SetValid ( F );
	}


	//==============================================================
	//Menu_Start

	Title_Menu_Start::Title_Menu_Start ()
	{
		m_state_VS = make_shared < TMS_VS > ();
		AddpTask ( m_state_VS );

		m_state_Intro = make_shared < TMS_Intro > ();
		AddpTask ( m_state_Intro );

		//カーソル
		m_grpCursor = make_shared < Title_Cursor > ();
		m_grpCursor->SetPos ( VEC2 ( CURSOR_X, CURSOR_Y ) );
		AddpTask ( m_grpCursor );
		GRPLST_INSERT_MAIN ( m_grpCursor );

	}

	Title_Menu_Start::~Title_Menu_Start ()
	{
	}

	void Title_Menu_Start::Move ()
	{
		Title_Menu_State::Move ();
	}

	void Title_Menu_Start::Load ()
	{
		//メニュ順番（追加順）
		Menu::SetpMenuItem ( m_state_VS );
		Menu::SetpMenuItem ( m_state_Intro );

		Title_Menu_State::Load ();
	}

	void Title_Menu_Start::SetwpTitle ( WP_Title p )
	{
		m_state_VS->SetwpTitle ( p );
		m_state_Intro->SetwpTitle ( p );

		Title_Menu_State::SetwpTitle ( p );
	}

	void Title_Menu_Start::SetwpScene ( WP_Scene p )
	{
		m_state_VS->SetwpScene ( p );
		m_state_Intro->SetwpScene ( p );

		Title_Menu_State::SetwpScene ( p );
	}

	void Title_Menu_Start::Do ()
	{
		//選択
		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		{
			m_state_Intro->Unselect ();
			m_state_VS->Unselect ();
			Menu::Next ();
			//SE
			SOUND->Play_SE ( SE_Sys_Select );
		}
		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		{
			m_state_Intro->Unselect ();
			m_state_VS->Unselect ();
			Menu::Prev ();
			//SE
			SOUND->Play_SE ( SE_Sys_Select );
		}

		//カーソル位置
		m_grpCursor->SetPos ( VEC2 ( CURSOR_X, CURSOR_Y + PITCH_Y * Menu::GetIdItem() ) );

		//動作
		Menu::Do ();
	}

	void Title_Menu_Start::Off ()
	{
		m_state_VS->Off ();
		m_state_Intro->Off ();
		m_grpCursor->SetValid ( F );
	}

	void Title_Menu_Start::On ()
	{
		m_state_VS->On ();
		m_state_Intro->On ();
		m_grpCursor->SetValid ( T );
	}

	//==============================================================


}	//namespace GAME

