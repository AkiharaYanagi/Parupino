//=================================================================================================
//
//	Training ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Training.h"
#include "../Title_Intro/Title_Intro.h"
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//定数
	const float Training::BX = ( 1280 - 256 ) * 0.5f;
	const float Training::BY = 170.f;


	Training::Training ()
	{
		//戦闘
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );

		//トレーニング表示
		m_training = make_shared < GrpAcv > ();
		m_training->AddTexture ( _T ( "training.png" ) );
		m_training->SetPos ( BX, BY );
		m_training->SetZ ( Z_SYS );
		AddpTask ( m_training );
		GRPLST_INSERT_MAIN ( m_training );

#if 0
		//ポーズ
		m_pause = make_shared < GrpAcv > ();
		m_pause->AddTexture ( _T ( "Pause.png" ) );
		m_pause->SetPos ( (1280 - 512)*0.5, 480.f );
		m_pause->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT_MAIN ( m_pause );
		m_pause->SetValid ( false );

#endif // 0
	}

	Training::~Training ()
	{
	}

	void Training::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}

	void Training::Load ()
	{
		//Transit用にthisを保存
		mwp_This = shared_from_this ();

		Scene::Load ();
	}

	void Training::Init ()
	{
#if 0

#if 0
		SOUND->Stop ( BGM_Main );
		SOUND->PlayLoop ( BGM_Main );
#endif // 0
		m_pause->SetValid ( false );

		//デモを飛ばしてゲーム開始
#if 0
		G_FTG_STATE_SET ( FS_GAME_MAIN );
		m_mutualChara->Wait ( false );
		Scene::Init ();
		m_mutualChara->SetMain ();
#endif // 0

		m_pause->SetValid ( false );

#endif // 0

		Scene::Init ();
	}

	void Training::Move ()
	{
#if 0

		Pause ();

		// 格闘終了判定
		if ( m_mutualChara->CheckZeroLife () )
		{
			//リセット
			Init ();
		}
		
		//両者処理
		m_mutualChara->Conduct ();

		//背景位置補正
		m_bg->SetPos ( G_BASE_POS ().x, (float)BG_POS_Y );

#endif // 0

		Scene::Move ();
	}

	P_GameScene Training::Transit ()
	{
		//ESCで戻る
//		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		if ( WND_UTL::AscKey ( VK_ESCAPE ) )
		{
			SOUND->Stop_BGM ( BGM_Main );
			GRPLST_CLEAR ();
			P_GameScene p = make_shared < Title_Intro > ();
			GRPLST_LOAD ();
			return p;
		}

		//他のシーンが確保されたなら遷移する
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//通常時
		return mwp_This.lock ();
	}

#if 0

	void Training::Pause ()
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

#endif // 0


}	//namespace GAME

