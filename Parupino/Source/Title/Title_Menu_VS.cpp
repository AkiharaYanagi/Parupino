//=================================================================================================
//
//	タイトル メニュ アクタ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_Menu_VS.h"
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
	//TMS_VS_Common
	//VSメニュ共通

	TMS_VS_Common::TMS_VS_Common ()
	{
		m_expl = make_shared < Title_Explain > ();
		m_expl->SetBase ( VEC2 ( EXPLAIN_X, EXPLAIN_Y ) );
		AddpTask ( m_expl );
		GRPLST_INSERT_MAIN ( m_expl );

		m_str = make_shared < GrpStr > ();
		m_str->SetPos ( VEC2 ( EXPLAIN_X, EXPLAIN_Y + 40 ) );
		AddpTask ( m_str );
//		GRPLST_INSERT_MAIN ( m_str );

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
	}

	void TMS_VS_Common::Load ()
	{
		m_str->SetFontFace ( _T("MSゴシック") );
		m_str->SetFontParam ( 24, 0, 2 );
		m_str->SetFontColor ( 0xff000000, 0xff000000 );
		m_str->SetStr ( _T("TMS_VS_Common") );

		Title_Menu_State::Load ();
	}

	void TMS_VS_Common::Do ()
	{
		if ( ! GetActive () ) { return; }

		m_expl->Do ();

		//フェードウェイト中
		if ( m_wait != 0 )
		{
			++m_wait;

			if ( m_wait > 6 )
			{
				Decide ();
				m_wait = 0;
			}
			return;
		}

		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) || CFG_PUSH_KEY ( _P2_BTN0 ) )
		{
			//SE
			SOUND->Play_SE ( SE_Sys_EnterFighting );

			//フェード開始
			m_fade->SetFade ( 5, _CLR ( 0x00000000UL ), _CLR ( 0xff000000UL ) );	//開始値、目標値を手動設定
			m_wait = 1;
		}
	}

	void TMS_VS_Common::Off ()
	{
		SetActive ( F );
		m_expl->SetValid ( F );
	}
	void TMS_VS_Common::On ()
	{
		SetActive ( T );
		m_expl->SetValid ( F );
	}

	//--------------------------------------------------------------
	TMS_TRAINING::TMS_TRAINING ()
	{
		m_expl->AddTexture ( _T ( "Title_explain_Training.png" ) );
	}

	void TMS_TRAINING::Decide ()
	{
//		m_pTitle.lock ()->Transit_Training ();
		SOUND->Stop_BGM ( BGM_Title );
		mwp_Scene.lock ()->Transit_Training ();
	}

	//--------------------------------------------------------------
	TMS_1P_VS_2P::TMS_1P_VS_2P ()
	{
		m_expl->AddTexture ( _T ( "Title_explain_1Pvs2P.png" ) );
	}

	void TMS_1P_VS_2P::Decide ()
	{
		SOUND->Stop_BGM ( BGM_Title );
		mwp_Scene.lock ()->Transit_Fighting ( MODE_PLAYER_PLAYER );
	}

	//--------------------------------------------------------------
	TMS_1P_VS_CPU::TMS_1P_VS_CPU ()
	{
		m_expl->AddTexture ( _T ( "Title_explain_1PvsCPU.png" ) );
	}

	void TMS_1P_VS_CPU::Decide ()
	{
		SOUND->Stop_BGM ( BGM_Title );
//		m_pTitle.lock ()->Transit_1P_VS_CPU ();
		mwp_Scene.lock ()->Transit_Fighting ( MODE_PLAYER_CPU );
	}

	//--------------------------------------------------------------
	TMS_CPU_VS_CPU::TMS_CPU_VS_CPU ()
	{
		m_expl->AddTexture ( _T ( "Title_explain_CPUvsCPU.png" ) );
	}

	void TMS_CPU_VS_CPU::Decide ()
	{
		SOUND->Stop_BGM ( BGM_Title );
		//m_pTitle.lock ()->Transit_CPU_VS_CPU ();
		mwp_Scene.lock ()->Transit_Fighting ( MODE_CPU_CPU );
	}


	//==============================================================
	//Menu_VS
	const float	Title_Menu_VS::BASE_X = 400;
	const float	Title_Menu_VS::BASE_Y = 420;
	const float	Title_Menu_VS::PITCH_Y = 60;

	Title_Menu_VS::Title_Menu_VS ()
	{
		m_state_Training = make_shared < TMS_TRAINING > ();
		AddpTask ( m_state_Training );

		m_state_1P_VS_2P = make_shared < TMS_1P_VS_2P > ();
		AddpTask ( m_state_1P_VS_2P );

		m_state_1P_VS_CP = make_shared < TMS_1P_VS_CPU > ();
		AddpTask ( m_state_1P_VS_CP );

		m_state_CP_VS_CP = make_shared < TMS_CPU_VS_CPU > ();
		AddpTask ( m_state_CP_VS_CP );


		m_grp = make_shared < GrpAcv > ();
		m_grp->AddTexture ( _T ( "title_menu.png" ) );
		m_grp->SetPos ( VEC2 ( BASE_X, BASE_Y ) );
		AddpTask ( m_grp );
		GRPLST_INSERT_MAIN ( m_grp );

		m_cursor = make_shared < Title_Cursor > ();
		AddpTask ( m_cursor );
		GRPLST_INSERT_MAIN ( m_cursor );
	}

	Title_Menu_VS::~Title_Menu_VS ()
	{
	}

	void Title_Menu_VS::SetwpTitle ( WP_Title wp )
	{
		m_pTitle = wp;
		m_state_Training->SetwpTitle ( wp );
		m_state_1P_VS_2P->SetwpTitle ( wp );
		m_state_1P_VS_CP->SetwpTitle ( wp );
		m_state_CP_VS_CP->SetwpTitle ( wp );
	}

	void Title_Menu_VS::SetwpScene ( WP_Scene wp )
	{
//		m_pTitle = wp;
		m_state_Training->SetwpScene ( wp );
		m_state_1P_VS_2P->SetwpScene ( wp );
		m_state_1P_VS_CP->SetwpScene ( wp );
		m_state_CP_VS_CP->SetwpScene ( wp );

		Title_Menu_State::SetwpScene ( wp );
	}

	void Title_Menu_VS::Load ()
	{
		Menu::SetpMenuItem ( m_state_Training );
		Menu::SetpMenuItem ( m_state_1P_VS_2P );
		Menu::SetpMenuItem ( m_state_1P_VS_CP );
		Menu::SetpMenuItem ( m_state_CP_VS_CP );
		Title_Menu_State::Load ();
	}

	void Title_Menu_VS::Do ()
	{
		//選択
		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		{
			Menu::Next ();
			SelectMenuItem ();
			//SE
			SOUND->Play_SE ( SE_Sys_Select );
		}
		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		{
			Menu::Prev ();
			SelectMenuItem ();
			//SE
			SOUND->Play_SE ( SE_Sys_Select );
		}

		//ひとつ戻る
		if ( CFG_PUSH_KEY ( _P1_BTN1 ) || CFG_PUSH_KEY ( _P2_BTN1 ) )
		{
			m_pTitle.lock ()->Return_Start ();
			Menu::ItemOff ();
			//SE
			SOUND->Play_SE ( SE_Sys_Cancel );
		}

		//カーソル位置
		m_cursor->SetPos ( VEC2 ( BASE_X - 20, BASE_Y + 130 + PITCH_Y * Menu::GetIdItem () ) );

		//動作
		Title_Menu_State::Do ();
	}

	void Title_Menu_VS::Off ()
	{
		m_grp->SetValid ( F );
		m_cursor->SetValid ( F );

		Menu::ItemOff ();
	}

	void Title_Menu_VS::On ()
	{
		m_grp->SetValid ( T );
		m_cursor->SetValid ( T );

		Menu::ItemOn ();
	}

	void Title_Menu_VS::SelectMenuItem ()
	{
		Menu::ItemOff ();
		P_MenuItem p = Menu::GetpMenuItem ();
		P_TMS_VS_Common pvs = dynamic_pointer_cast <TMS_VS_Common> ( p );
		pvs->On ();
	}

	//==============================================================


}	//namespace GAME

