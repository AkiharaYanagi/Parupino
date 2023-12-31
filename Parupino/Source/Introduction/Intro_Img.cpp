//=================================================================================================
//
//	イントロダクション イメージ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Intro_Img.h"
#include "../GameMain/SoundConst.h"
#include "../Title/Title.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const VEC2 Intro_Img::KEY_POS ( 400, 930 );
	const VEC2 Intro_Img::CURSOR_POS0 ( 5, 450 );
	const VEC2 Intro_Img::CURSOR_POS1 ( 1280 - 128 - 5, 450 );
	const UINT Intro_Img::N_PAGE = 3;	//index : 0-3, 枚数４,


	Intro_Img::Intro_Img ()
	{
		m_grpIntro = make_shared < GrpAcv > ();
		m_grpIntro->AddTexture ( _T ( "Intro1.png" ) );
		m_grpIntro->AddTexture ( _T ( "Intro2.png" ) );
		m_grpIntro->AddTexture ( _T ( "Intro3.png" ) );
		m_grpIntro->AddTexture ( _T ( "Intro4.png" ) );
		AddpTask ( m_grpIntro );
		GRPLST_INSERT_MAIN ( m_grpIntro );

		m_page = 0;

		m_grpKey = make_shared < GrpAcv > ();
		m_grpKey->SetPos ( KEY_POS );
		m_grpKey->AddTexture ( _T ( "Intro_Key.png" ) );
		AddpTask ( m_grpKey );
		GRPLST_INSERT_MAIN ( m_grpKey );

		m_waitSound = make_shared < Timer > ();
		AddpTask ( m_waitSound );

		m_grpCursor0 = make_shared < Title_Cursor > ();
		m_grpCursor0->SetPos ( CURSOR_POS0 );
		m_grpCursor0->Reverse ();
		AddpTask ( m_grpCursor0 );
		GRPLST_INSERT_MAIN ( m_grpCursor0 );

		m_grpCursor1 = make_shared < Title_Cursor > ();
		m_grpCursor1->SetPos ( CURSOR_POS1 );
		AddpTask ( m_grpCursor1 );
		GRPLST_INSERT_MAIN ( m_grpCursor1 );
	}

	Intro_Img::~Intro_Img ()
	{
	}

	void Intro_Img::Load ()
	{
		//遷移先指定にthisを保存
		Scene::SetwpThis ( shared_from_this () );

		//入力待ち
		m_wait = 0;

		//SOUND
		m_waitSound->SetTargetTime ( 5 );
		m_waitSound->Start ();

		Scene::Load ();
	}

	void Intro_Img::ParamInit ()
	{
	}

	P_GameScene Intro_Img::Transit ()
	{
		//開始後、1[F]は入力をチェックしない
		if ( m_wait == 0 )
		{
			m_wait = 1; return GetwpThis().lock ();
		}

		//SOUND wait
		if ( m_waitSound->IsLast () )
		{
			//SOUND
			SOUND->Play_Loop_BGM ( BGM_Intro );
			m_waitSound->Clear ();
		}

		//===========================================================
		//選択
		if ( CFG_PUSH_KEY ( _P1_RIGHT ) || CFG_PUSH_KEY ( _P2_RIGHT ) )
		{
			if ( ++ m_page > N_PAGE ) { m_page = 0; }
			m_grpIntro->SetIndexTexture ( m_page );
		}
		else 
		if ( CFG_PUSH_KEY ( _P1_LEFT ) || CFG_PUSH_KEY ( _P2_LEFT ) )
		{
			m_page = ( m_page == 0 ) ? N_PAGE : m_page - 1;
			m_grpIntro->SetIndexTexture ( m_page );
		}

		//===========================================================
		//戻る
		bool b0 = WND_UTL::AscKey ( VK_ESCAPE );
		bool b1 = CFG_PUSH_KEY ( _P1_BTN0 ) || CFG_PUSH_KEY ( _P2_BTN0 );
		bool b2 = CFG_PUSH_KEY ( _P1_BTN1 ) || CFG_PUSH_KEY ( _P2_BTN1 );
		if ( b0 || b1 || b2 )
		{
			//SOUND
			SOUND->Play_SE ( SE_Sys_Cancel );
			SOUND->Stop_BGM ( BGM_Intro );

#if 0
			GRPLST_CLEAR ();
			mp_Transit = make_shared < Title > ();
			GRPLST_LOAD ();
#endif // 0
			GetwpThis().lock()->Transit_Title ();
		}

		//===========================================================
#if 0
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		return mwp_This.lock();
#endif // 0
		return Scene::Transit ();
	}

	void Intro_Img::Move ()
	{
		Scene::Move ();
	}


}	//namespace GAME

