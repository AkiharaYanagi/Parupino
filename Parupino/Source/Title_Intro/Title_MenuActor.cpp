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
		m_grpIntro->SetPos ( VEC2 ( 100, 300 ) );
		AddpTask ( m_grpIntro );
		GRPLST_INSERT_MAIN ( m_grpIntro );
	}

	TMS_Intro::~TMS_Intro ()
	{
	}

	void TMS_Intro::Do ()
	{
#if 0
		//親状態の選択
		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		{
			mwp_Parent.lock()->Next ();
		}
		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		{
			mwp_Parent.lock ()->Prev ();
		}
#endif // 0

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			m_pTitle_Intro.lock()->Transit_Intro ();
		}
	}

	//--------------------------------------------------------------
	TMS_Fighting::TMS_Fighting ()
	{
		m_grp = make_shared < GrpAcv > ();
		m_grp->AddTexture ( _T ( "TitleMenu_Fighting.png" ) );
		m_grp->SetPos ( VEC2 ( 100, 400 ) );
		AddpTask ( m_grp );
		GRPLST_INSERT_MAIN ( m_grp );
	}

	TMS_Fighting::~TMS_Fighting ()
	{
	}

	void TMS_Fighting::Do ()
	{
	}


	//==============================================================
	//Menu_Start
	Title_Menu_Start::Title_Menu_Start ()
	{
		m_state_Intro = make_shared < TMS_Intro > ();
		AddpTask ( m_state_Intro );

		m_state_Fighting = make_shared < TMS_Fighting > ();
		AddpTask ( m_state_Fighting );

		m_selectedState = m_state_Intro;


		m_grpCursor = make_shared < GrpAcv > ();
		m_grpCursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_grpCursor->SetPos ( VEC2 ( 80, 300 ) );
		AddpTask ( m_grpCursor );
		GRPLST_INSERT_MAIN ( m_grpCursor );
	}

	Title_Menu_Start::~Title_Menu_Start ()
	{
	}

	void Title_Menu_Start::Load ()
	{
		Menu::SetpMenuItem ( m_state_Intro );
		Menu::SetpMenuItem ( m_state_Fighting );
		Title_MenuState::Load ();
	}

	void Title_Menu_Start::SetwpTitle_Intro ( WP_Title_Intro p )
	{
		m_state_Intro->SetwpTitle_Intro ( p );
		m_state_Fighting->SetwpTitle_Intro ( p );
	}

	void Title_Menu_Start::Do ()
	{
		//選択
		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		{
			Menu::Next ();
		}
		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		{
			Menu::Prev ();
		}

		//カーソル位置
		m_grpCursor->SetPos ( VEC2 ( 80.f, 300.f + 100 * Menu::GetIdItem() ) );

		//動作
		m_selectedState->Do ();
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

		m_selectedState = m_start;
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
		m_selectedState->Do ();

		TASK_VEC::Move ();
	}

	//==============================================================


}	//namespace GAME

