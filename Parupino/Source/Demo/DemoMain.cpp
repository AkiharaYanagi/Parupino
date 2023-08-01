//=================================================================================================
//
//	Demo ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DemoMain.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Demo::Demo ()
	{
		//メニュ
		m_menu = make_shared < DemoMenu > ();
		AddpTask ( m_menu );

		//戦闘
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );
	}

	Demo::~Demo ()
	{
	}

	void Demo::ParamInit ()
	{
		P_Param pParam = GetpParam ();
		GameSettingFile stg = pParam->GetGameSetting ();
		stg.SetPlayerMode1p ( MODE_CPU );
		stg.SetPlayerMode2p ( MODE_CPU );
		pParam->SetSettingFile ( stg );

		m_fighting->ParamInit ( pParam );
	}

	P_GameScene Demo::Transit ()
	{
#if 0
		//ESCで戻る
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}
#endif // 0

		//通常時
		return shared_from_this ();
	}


	void Demo::Pause ()
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


}	//namespace GAME

