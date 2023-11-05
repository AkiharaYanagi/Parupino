//=================================================================================================
//
//	タイトル イントロ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_Intro.h"
#include "../GameMain/SoundConst.h"
#include "../Introduction/Introduction.h"
#include "../Training/Training.h"
#include "../FtgMain/FtgMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	const float Title_Intro::OMEGA = D3DX_2PI / ( 12 * 60.f );	//[rad/F]
	const float	Title_Intro::KEY_X = 400;
	const float	Title_Intro::KEY_Y = 930;

	Title_Intro::Title_Intro ()
	{
		//---------------------------------------------------
		//グラフィック初期化
		//---------------------------------------------------
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "title_bg.png" ) );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		m_count = 0;

		m_logo = make_shared < GrpAcv > ();
		m_logo->AddTexture ( _T ( "Title_Logo.png" ) );
		m_logo->SetZ ( Z_BG );
		m_logo->SetPos ( VEC2 ( 0, 0 ) );
		AddpTask ( m_logo );
		GRPLST_INSERT_MAIN ( m_logo );

		//---------------------------------------------------
		//メニュ
		m_menuActor = make_shared < Title_MenuActor > ();
		AddpTask ( m_menuActor );

		m_explain_bg = make_shared < PrmRect > ();
		m_explain_bg->SetPos ( VEC2 ( 0, 840 ) );
		m_explain_bg->SetSize ( VEC2 ( 1280, 40 ) );
		m_explain_bg->SetAllColor ( _CLR ( 0x80ffffff ) );
		m_explain_bg->SetAllZ ( Z_BG );
		AddpTask ( m_explain_bg );
		GRPLST_INSERT_MAIN ( m_explain_bg );

		m_explain_key = make_shared < GrpAcv > ();
		m_explain_key->AddTexture ( _T("Title_key.png") );
		m_explain_key->SetPos ( VEC2 ( KEY_X, KEY_Y ) );
		AddpTask ( m_explain_key );
		GRPLST_INSERT_MAIN ( m_explain_key );

		m_wait = 0;
	}

	Title_Intro::~Title_Intro ()
	{
	}

	void Title_Intro::Load ()
	{
		//アクタに親ポインタを設定
		m_menuActor->SetwpTitle_Intro ( shared_from_this () );

		//遷移先を自身に設定
		mwp_This = shared_from_this ();

		//SOUND
		SOUND->Stop ( BGM_Title );
		SOUND->Play ( BGM_Title );

		Scene::Load ();
	}

	void Title_Intro::Move ()
	{
		float dy = cosf ( OMEGA * m_count );
		m_logo->SetPos ( VEC2 ( 0, -20.f + 5.f * ( 1 - dy ) ) );

		++ m_count;
		if ( OMEGA * m_count > D3DX_2PI ) { m_count = 0; }
		
		Scene::Move ();
	}

	P_GameScene Title_Intro::Transit ()
	{
		//開始後、1[F]は入力をチェックしない
		if ( m_wait == 0 )
		{
			m_wait = 1; return mwp_This.lock ();
		}

		//===========================================================
		//ESCでアプリケーションを終了(タイトルのみ・他シーンでは1つ戻る)
		if ( WND_UTL::AscKey ( VK_ESCAPE ) )
		{
			::PostQuitMessage ( 0 );
		}
		//===========================================================
		
		//次遷移先を返す
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//通常時は自身を返す
		return mwp_This.lock();
	}

	//シーン状態遷移
	void Title_Intro::Transit_Intro ()
	{
		//SOUND
		SOUND->Stop ( BGM_Title );

		GRPLST_CLEAR ();
		mp_Transit = make_shared < Introduction > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_Training ()
	{
		//SOUND
		SOUND->Stop ( BGM_Title );

		GRPLST_CLEAR ();
		mp_Transit = make_shared < Training > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_1P_VS_2P ()
	{
		mp_Transit = MakepFtgMain ();
		GetpParam ()->SetMutchMode ( MODE_PLAYER_PLAYER );
	}

	void Title_Intro::Transit_1P_VS_CPU ()
	{
		mp_Transit = MakepFtgMain ();
		GetpParam ()->SetMutchMode ( MODE_PLAYER_CPU );
	}

	void Title_Intro::Transit_CPU_VS_CPU ()
	{
		mp_Transit = MakepFtgMain ();
		GetpParam ()->SetMutchMode ( MODE_CPU_CPU );
	}


	//メニュ選択
	void Title_Intro::Select_VS ()
	{
		m_menuActor->Select_VS ();
	}

	//タイトルの最初に戻る
	void Title_Intro::Return_Start ()
	{
		m_menuActor->Return_Start ();
	}

	//-------------------------------------
	P_GameScene Title_Intro::MakepFtgMain ()
	{
		//SOUND
		SOUND->Stop ( BGM_Title );

		GRPLST_CLEAR ();
		P_GameScene p = make_shared < FtgMain > ();
		GRPLST_LOAD ();

		return p;
	}

}	//namespace GAME

