//=================================================================================================
//
//	Fighting ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Fighting.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Fighting::Fighting ()
	{
		//格闘部分共通パラメータシングルトン生成
		G_Ftg::Create ();

		//------------------------------------------------
		//背景
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "ftgmain_bg1.png" ) );
		m_bg->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg->SetSpritePosition ( VEC3 ( 0, 0, Z_BG ) );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		m_bg_blackout = make_shared < GrpAcv > ();
		m_bg_blackout->AddTexture ( _T ( "ftgmain_bg_black.png" ) );
		m_bg_blackout->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_blackout->SetSpritePosition ( VEC3 ( 0, 0, Z_BG ) );
		m_bg_blackout->SetValid ( false );
		AddpTask ( m_bg_blackout );
		GRPLST_INSERT_MAIN ( m_bg_blackout );

		//ゲージ枠
		m_gauge_frame = make_shared < GrpAcv > ();
		m_gauge_frame->AddTexture ( _T ( "gauge_frame.png" ) );
		m_gauge_frame->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		AddpTask ( m_gauge_frame );
		GRPLST_INSERT_MAIN ( m_gauge_frame );

		//BGタイマ
		m_bgTimer = make_shared < Timer > ();
		AddpTask ( m_bgTimer );

		//------------------------------------------------

		//=====================================================
		//キャラ相互処理
		//=====================================================
		m_mutualChara = make_shared < MutualChara > ();
		AddpTask ( m_mutualChara );

		//=====================================================
		//デモ
//		m_demoActor = make_shared < FtgDemoActor > ();
//		m_demoActor->Load ();
//		m_demoActor->SetpMutualChara ( m_mutualChara );

		//=====================================================

		//ポーズ
		m_pause = make_shared < GrpAcv > ();
		m_pause->AddTexture ( _T ( "Pause.png" ) );
		m_pause->SetPos ( (1280-512)*0.5, 480.f );
		m_pause->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT_MAIN ( m_pause );
		m_pause->SetValid ( false );
	}

	Fighting::~Fighting ()
	{
	}


	void Fighting::ParamInit ( P_Param pParam )
	{
		m_mutualChara->ParamInit ( pParam );
	}

	void Fighting::Init ()
	{
		SOUND->Stop ( BGM_Main );
		SOUND->PlayLoop ( BGM_Main );
		m_pause->SetValid ( false );

		TASK_LST::Init ();

		//Debug用　開始デモをスキップ切替
#define DEMO_ON 0
#if DEMO_ON
		m_demoActor->StartGreeting ();
#else
//		m_demoActor->StartFighting ();
#endif // DEMO_ON
	}


	void Fighting::Move ()
	{
		//--------------------------
		//ポーズ
		Pause ();

		//--------------------------
		//デモ分岐
//		m_demoActor->Do ();

		//--------------------------
		//両者処理
		m_mutualChara->Conduct ();

		//--------------------------
		//共通グラフィック処理
		Grp ();

		//--------------------------
		TASK_LST::Move ();
	}

#if 0
	//状態遷移
	P_GameScene Fighting::Transit ()
	{
#if 0
		//ESCで戻る
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}
#endif // 0

		//戦闘終了時
#if 0
		if ( FS_END == G_FTG_STATE () )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}
#endif // 0

		//通常時
//		return shared_from_this ();
	}
#endif // 0
	

	//=============================================================
	//	内部関数
	//=============================================================
	void Fighting::Pause ()
	{
		//F1でポーズ切替
		if ( ::GetAsyncKeyState ( VK_F1 ) & 0x0001 )
		{
			if ( m_pause->GetValid () )	//On->Off
			{
				m_pause->SetValid ( false );
//				m_mutualChara->Stop ( false );
			}
			else	//Off->On
			{
				m_pause->SetValid ( true );
//				m_mutualChara->Stop ( true );
			}
		}
	}

	//共通グラフィック処理
	void Fighting::Grp ()
	{
		UINT blackOut = 0;

		//暗転
		if ( ! m_bgTimer->IsActive () )
		{
//			blackOut = m_mutualChara->GetBlackOut ();
			//初回
			if ( 0 < blackOut )
			{
				m_bgTimer->SetTargetTime ( blackOut );
				m_bgTimer->Start ();

				blackOut = 0;
//				m_mutualChara->SetBlackOut ( 0 );

				m_bg->SetValid ( false );
				m_bg_blackout->SetValid ( true );
			}
		}

		if ( m_bgTimer->IsLast () )
		{
			m_bgTimer->Stop ();
			m_bgTimer->Reset ();
			m_bg->SetValid ( true );
			m_bg_blackout->SetValid ( false );
		}

		//背景位置補正
		m_bg->SetPos ( G_BASE_POS ().x, (float)BG_POS_Y );
	}


}	//namespace GAME

