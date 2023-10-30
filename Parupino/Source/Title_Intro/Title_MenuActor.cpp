//=================================================================================================
//
//	タイトル メニュ アクタ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_MenuActor.h"
#include "Title_Intro.h"


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
	TMS_Intro::TMS_Intro ()
	{
		m_grpIntro = make_shared < GrpAcv > ();
		m_grpIntro->AddTexture ( _T ( "TitleMenu_Introduction.png" ) );
		m_grpIntro->SetPos ( VEC2 ( MENU_X, MENU_Y ) );
		AddpTask ( m_grpIntro );
		GRPLST_INSERT_MAIN ( m_grpIntro );

		m_grpExplain = make_shared < GrpAcv > ();
		m_grpExplain->AddTexture ( _T ( "Title_explain_Introduction.png" ) );
		m_grpExplain->SetPos ( VEC2 ( EXPLAIN_X, EXPLAIN_Y ) );
		m_grpExplain->SetZ ( Z_DEFALT );
		AddpTask ( m_grpExplain );
		GRPLST_INSERT_MAIN ( m_grpExplain );
		m_grpExplain->SetValid ( F );
	}

	TMS_Intro::~TMS_Intro ()
	{
	}

	void TMS_Intro::Do ()
	{
		//切替
		if ( ! m_grpExplain->GetValid () )
		{
			m_grpExplain->SetValid ( T );
		}

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) || CFG_PUSH_KEY ( _P2_BTN0 ) )
		{
			m_pTitle_Intro.lock()->Transit_Intro ();
		}
	}

	void TMS_Intro::Off ()
	{
		m_grpIntro->SetValid ( F );
		m_grpExplain->SetValid ( F );
	}

	void TMS_Intro::On ()
	{
		m_grpIntro->SetValid ( T );
	}

	void TMS_Intro::Unselect ()
	{
		m_grpExplain->SetValid ( F );
	}


	//--------------------------------------------------------------
	TMS_VS::TMS_VS ()
	{
		m_grpVS = make_shared < GrpAcv > ();
		m_grpVS->AddTexture ( _T ( "TitleMenu_Fighting.png" ) );
		m_grpVS->SetPos ( VEC2 ( MENU_X, MENU_Y + PITCH_Y ) );
		AddpTask ( m_grpVS );
		GRPLST_INSERT_MAIN ( m_grpVS );

		m_grpExplain = make_shared < GrpAcv > ();
		m_grpExplain->AddTexture ( _T ( "Title_explain_Fighting.png" ) );
		m_grpExplain->SetPos ( VEC2 ( EXPLAIN_X, EXPLAIN_Y ) );
		m_grpExplain->SetZ ( Z_DEFALT );
		AddpTask ( m_grpExplain );
		GRPLST_INSERT_MAIN ( m_grpExplain );
		m_grpExplain->SetValid ( F );
	}

	TMS_VS::~TMS_VS ()
	{
	}

	void TMS_VS::Do ()
	{
		//切替
		if ( ! m_grpExplain->GetValid () )
		{
			m_grpExplain->SetValid ( T );
		}

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) || CFG_PUSH_KEY ( _P2_BTN0 ) )
		{
			m_pTitle_Intro.lock ()->Select_VS ();
		}
	}

	void TMS_VS::Off ()
	{
		m_grpVS->SetValid ( F );
		m_grpExplain->SetValid ( F );
	}

	void TMS_VS::On ()
	{
		m_grpVS->SetValid ( T );
	}

	void TMS_VS::Unselect ()
	{
		m_grpExplain->SetValid ( F );
	}


	//==============================================================
	//Menu_Start
//	const float Title_Menu_Start::OMEGA = D3DX_2PI / ( 1 * 60.f );	//[rad/F]

	Title_Menu_Start::Title_Menu_Start ()
	{
		m_state_Intro = make_shared < TMS_Intro > ();
		AddpTask ( m_state_Intro );

		m_state_VS = make_shared < TMS_VS > ();
		AddpTask ( m_state_VS );


		//カーソル
#if 0
		m_grpCursor = make_shared < GrpAcv > ();
		m_grpCursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_grpCursor->SetPos ( VEC2 ( CURSOR_X, CURSOR_Y ) );
		m_grpCursor->SetScalingCenter ( VEC2 ( 64.f, 32.f ) );
		m_grpCursor->SetScaling ( VEC2 ( 1.f, 1.f ) );
		AddpTask ( m_grpCursor );
		GRPLST_INSERT_MAIN ( m_grpCursor );

		m_count = 0;
#endif // 0
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
#if 0
		float f = sinf ( OMEGA * m_count );
		m_grpCursor->SetScaling ( VEC2 ( 1.f, f ) );

		++ m_count;
		if ( OMEGA * m_count > D3DX_2PI ) { m_count = 0; }
#endif // 0

		Title_MenuState::Move ();
	}

	void Title_Menu_Start::Load ()
	{
		Menu::SetpMenuItem ( m_state_Intro );
		Menu::SetpMenuItem ( m_state_VS );
		Title_MenuState::Load ();
	}

	void Title_Menu_Start::SetwpTitle_Intro ( WP_Title_Intro p )
	{
		m_state_Intro->SetwpTitle_Intro ( p );
		m_state_VS->SetwpTitle_Intro ( p );
	}

	void Title_Menu_Start::Do ()
	{
		//選択
		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		{
			m_state_Intro->Unselect ();
			m_state_VS->Unselect ();
			Menu::Next ();
		}
		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		{
			m_state_Intro->Unselect ();
			m_state_VS->Unselect ();
			Menu::Prev ();
		}

		//カーソル位置
		m_grpCursor->SetPos ( VEC2 ( CURSOR_X, CURSOR_Y + PITCH_Y * Menu::GetIdItem() ) );

		//動作
		Menu::Do ();
	}

	void Title_Menu_Start::Off ()
	{
		m_state_Intro->Off ();
		m_state_VS->Off ();
		m_grpCursor->SetValid ( F );
	}

	void Title_Menu_Start::On ()
	{
		m_state_Intro->On ();
		m_state_VS->On ();
		m_grpCursor->SetValid ( T );
	}

	//==============================================================
	//Actor

	Title_MenuActor::Title_MenuActor ()
	{
		m_start = make_shared < Title_Menu_Start > ();
		AddpTask ( m_start );

		m_vs = make_shared < Title_Menu_VS > ();
		AddpTask ( m_vs );
		m_vs->Off ();
	}

	Title_MenuActor::~Title_MenuActor ()
	{
	}


	void Title_MenuActor::Load ()
	{
		//shared_from_this () を含むのでコンストラクタで用いない
		Menu::SetpMenuItem ( m_start );
		Menu::SetpMenuItem ( m_vs );

		Menu::Load ();
	}

	void Title_MenuActor::SetwpTitle_Intro ( WP_Title_Intro p )
	{
		m_start->SetwpTitle_Intro ( p );
		m_vs->SetwpTitle_Intro ( p );
	}

	void Title_MenuActor::Move ()
	{
		Menu::Do ();

		TASK_VEC::Move ();
	}

	//VSメニュに移行
	void Title_MenuActor::Select_VS ()
	{
		m_start->Off ();
		Menu::Next ();
		m_vs->On ();
	}

	//タイトルの最初に戻る
	void Title_MenuActor::Return_Start ()
	{
		m_start->On ();
		Menu::Top ();
		m_vs->Off ();
	}

	//==============================================================


}	//namespace GAME

