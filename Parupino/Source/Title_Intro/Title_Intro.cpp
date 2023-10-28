//=================================================================================================
//
//	タイトル イントロ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_Intro.h"
#include "../Introduction/Introduction.h"
#include "../Training/Training.h"
#include "../FtgMain/FtgMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	const float Title_Intro::OMEGA = D3DX_2PI / ( 8 * 60.f );	//[rad/F]

	Title_Intro::Title_Intro ()
	{
		//---------------------------------------------------
		//グラフィック初期化
		//---------------------------------------------------
		m_bg = make_shared < GrpAcv > ();
//		m_bg->AddTexture ( _T ( "title_bg.png" ) );
		m_bg->AddTexture ( _T ( "title_bg2.png" ) );
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
	}

	Title_Intro::~Title_Intro ()
	{
	}

	void Title_Intro::Move ()
	{
		float dy = cosf ( OMEGA * m_count );
		m_logo->SetPos ( VEC2 ( 0, -20.f + 5.f * ( 1 - dy ) ) );

		++ m_count;
		if ( OMEGA * m_count > D3DX_2PI ) { m_count = 0; }
		
		Scene::Move ();
	}

	void Title_Intro::Load ()
	{
		//アクタに親ポインタを設定
		m_menuActor->SetwpTitle_Intro ( shared_from_this () );

		//遷移先を自身に設定
		mwp_This = shared_from_this ();

		Scene::Load ();
	}

	P_GameScene Title_Intro::Transit ()
	{
		//===========================================================
		//ESCでアプリケーションを終了(タイトルのみ・他シーンでは1つ戻る)
//		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		if ( WND_UTL::AscKey ( VK_ESCAPE ) )
		{
			::PostQuitMessage ( 0 );
		}
		//===========================================================

#if 0
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			//共通グラフィック配列をクリア
			GRPLST_CLEAR ();

			P_GameScene p = make_shared < Introduction > ();
			GRPLST_LOAD ();
			return p;
		}

#endif // 0
		
		//次遷移先を返す
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//通常時は自身を返す
//		return shared_from_this ();
		return mwp_This.lock();
	}

	//シーン状態遷移
	void Title_Intro::Transit_Intro ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Introduction > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_Training ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Training > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_1P_VS_2P ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < FtgMain > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_1P_VS_CPU ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Introduction > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_CPU_VS_CPU ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Introduction > ();
		GRPLST_LOAD ();
	}

	//メニュ選択
	void Title_Intro::Select_VS ()
	{
		m_menuActor->Select_VS ();
	}

}	//namespace GAME

