//=================================================================================================
//
//	Fighting ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Fighting.h"
#include "../Title/Title.h"

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
//		m_bg->AddTexture (_T ("ftgmain_bg.png"));
		m_bg->AddTexture (_T ("ftgmain_bg0.png"));
		m_bg->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg->SetSpritePosition ( VEC3 ( 0, 0, Z_BG ) );
		GRPLST_INSERT ( m_bg );

		m_bg_blackout = make_shared < GrpAcv > ();
		m_bg_blackout->AddTexture ( _T ( "ftgmain_bg_black.png" ) );
		m_bg_blackout->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_blackout->SetSpritePosition ( VEC3 ( 0, 0, Z_BG ) );
		m_bg_blackout->SetValid ( false );
		GRPLST_INSERT ( m_bg_blackout );

		//ゲージ枠
		m_gauge_frame = make_shared < GrpAcv > ();
		m_gauge_frame->AddTexture ( _T ( "gauge_frame.png" ) );
		m_gauge_frame->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT ( m_gauge_frame );

		//BGタイマ
		m_bgTimer = make_shared < Timer > ();
		AddpTask ( m_bgTimer );

		//------------------------------------------------

		//=====================================================
		//キャラ相互処理
		//=====================================================
		m_mutualChara = make_shared < MutualChara > ();
		AddpTask ( m_mutualChara );

		//デモ用キャラ相互処理
//		m_mutualChara_Demo = make_shared < MutualChara_Demo > ();
//		AddpTask ( m_mutualChara_Demo );


		//=====================================================
		//デモ
		m_demoActor = make_shared < FtgDemoActor > ();
		m_demoActor->Load ();
		m_demoActor->SetpMutualChara ( m_mutualChara );

		//=====================================================

		//ポーズ
		m_pause = make_shared < GrpAcv > ();
		m_pause->AddTexture ( _T ( "Pause.png" ) );
		m_pause->SetPos ( (1280-512)*0.5, 480.f );
		m_pause->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT ( m_pause );
		m_pause->SetValid ( false );
	}

	Fighting::~Fighting ()
	{
	}


	void Fighting::ParamInit ()
	{
		m_mutualChara->ParamInit ( GetpParam () );
//		m_mutualChara_Demo->ParamInit ( GetpParam () );
	}

	void Fighting::Init ()
	{
		SOUND->Stop ( BGM_Main );
		SOUND->PlayLoop ( BGM_Main );
		m_pause->SetValid ( false );

		Scene::Init ();

		//Debug用　開始デモをスキップ切替
#define DEMO_ON 1
#if DEMO_ON
		m_demoActor->StartGreeting ();
#else
		m_demoActor->StartFighting ();
#endif // DEMO_ON
	}

	void Fighting::Move ()
	{
		//--------------------------
		//ポーズ
		Pause ();

		//--------------------------
#if 0

		//デモ分岐
		switch ( G_FTG_STATE () )
		{
		case FS_GETREADY:
			if ( ! m_demo_GetReady->GetValid () )
			{
				m_demo_Attack->SetFadeOut ( 60 );
				m_demo_Attack->Init ();
				m_mutualChara->Wait ( false );
				m_mutualChara->SetMain ();
				G_FTG_STATE_SET ( FS_GAME_MAIN );
			}
		break;
	
		case FS_ATTACK:
		break;

		case FS_GAME_MAIN:
			// 格闘終了判定
			if ( m_mutualChara->CheckDown () )
			{
				StartGrpDemo ( m_demo_Down, 120 );
				m_mutualChara->Stop ( true );
				m_mutualChara->SetEndWait ();
				G_FTG_STATE_SET ( FS_DOWN_DISP );
			}

		break;

		case FS_DOWN_DISP:
			if ( ! m_demo_Down->GetValid () )
			{
				m_mutualChara->Stop ( false );
				m_mutualChara->CheckWinner ();

				//@info 終了時に挙動が不安定なため飛ばす
//				G_FTG_STATE_SET ( FS_DOWN_WAIT );
				StartGrpDemo ( m_demo_Winner, 180 );
				G_FTG_STATE_SET ( FS_POST_DEMO_START );
			}
		break;

		case FS_DOWN_WAIT:
			if ( m_mutualChara->CheckDownEnd () )
			{
//				m_mutualChara->EndAct ();
				G_FTG_STATE_SET ( FS_POST_DEMO_START );
			}
		break;

		case FS_POST_DEMO_START:
			if ( m_mutualChara->CheckWinEnd () )
			{
				StartGrpDemo ( m_demo_Winner, 180 );
#if 0
				switch ( m_mutualChara->GetWinnerName () )
				{
				case CHARA_SONIA: StartGrpDemo ( m_demo_SONIA, 180 ); break;
				case CHARA_ORFLOAT: StartGrpDemo ( m_demo_ORFLOAT, 180 ); break;
				default: break;
				}
#endif // 0
				G_FTG_STATE_SET ( FS_WINNER );
				m_mutualChara->ForcedEnd ();
			}
		break;

		case FS_WINNER:
			if ( ! m_demo_Winner->GetValid () )
			{
				//G_FTG_STATE_SET ( FS_END );

				//test 初期化
				G_FTG_STATE_SET ( FS_GETREADY );
				m_mutualChara->Start ();
			}
		break;

		case FS_END:
			
			//FS_END時にはTransit()が分岐している

		break;

		default: break;
		}

#endif // 0

		//デモ分岐
		m_demoActor->Do ();

		//--------------------------

		//両者処理
		m_mutualChara->Conduct ();
//		m_mutualChara_Demo->Conduct ();

		//--------------------------
		//共通グラフィック処理
		Grp ();

		//--------------------------
		Scene::Move ();
	}


	//状態遷移
	P_GameScene Fighting::Transit ()
	{
		//ESCで戻る
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}

		//終了時
		if ( FS_END == G_FTG_STATE () )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}

		//通常時
		return shared_from_this ();
	}
	

	//=============================================================
	//	内部関数
	//=============================================================
#if 0
	void Fighting::MakeGrpDemo ( P_GrpDemo & pGrp, LPCTSTR txName )
	{
		pGrp = make_shared < GrpDemo > ();
		pGrp->AddTexture ( txName );
		SetGrpDemo ( pGrp );
		GRPLST_INSERT ( pGrp );
	}

	void Fighting::SetGrpDemo ( P_GrpDemo pGrp )
	{
		pGrp->SetPos ( VEC2 ( 128, 400 ) );
		pGrp->SetScalingCenter ( VEC2 ( 512, 128 ) );
		pGrp->SetStartScaling ( VEC2 ( 1.3f, 1.3f ) );
		pGrp->SetSecondVel ( VEC2 ( -0.001f, -0.001f ) );
		pGrp->SetZ ( Z_SYS );
		pGrp->SetValid ( false );
	}

	void Fighting::StartGrpDemo ( P_GrpDemo pGrp, UINT time )
	{
//		pGrp->SetWait ( time );
		pGrp->Init ();
	}
#endif // 0

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

