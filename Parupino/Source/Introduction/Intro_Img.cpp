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
#include "../Title_Intro/Title_Intro.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Intro_Img::Intro_Img ()
	{
		m_grpIntro = make_shared < GrpAcv > ();
		AddpTask ( m_grpIntro );
		GRPLST_INSERT_MAIN ( m_grpIntro );
	}

	Intro_Img::~Intro_Img ()
	{
	}

	void Intro_Img::Load ()
	{
		//遷移先を自身に設定
		mwp_This = shared_from_this ();

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
			m_wait = 1; return mwp_This.lock ();
		}

		if ( m_waitSound->IsLast () )
		{
			//SOUND
			SOUND->Play_Loop_BGM ( BGM_Intro );
			m_waitSound->Clear ();
		}

		//===========================================================
		//戻る
		if ( CFG_IS_KEY ( _P1_BTN1 ) || CFG_IS_KEY ( _P2_BTN1 ) )
		{
			//SOUND
			SOUND->Play_SE ( SE_Sys_Cancel );
			SOUND->Stop_BGM ( BGM_Intro );

			GRPLST_CLEAR ();
			mp_Transit = make_shared < Title_Intro > ();
			GRPLST_LOAD ();
		}

		//===========================================================

		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		return mwp_This.lock();
	}

	void Intro_Img::Move ()
	{
		Scene::Move ();
	}


}	//namespace GAME

