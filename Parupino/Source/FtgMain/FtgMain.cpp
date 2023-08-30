//=================================================================================================
//
//	FtgMain ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
		: m_menu ( F )
	{
		//戦闘
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );

		//ポーズメニュ
//		m_pauseMenu = make_shared < PauseMenu > ();
//		AddpTask ( m_pauseMenu );
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}

	void FtgMain::Init ()
	{
		m_menu = F;
		Scene::Init ();
	}


	void FtgMain::Move ()
	{
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) )
		{
			m_menu = T;
		}


		if ( m_menu )
		{
			return;
		}

		Scene::Move ();
	}


	//状態遷移
	P_GameScene FtgMain::Transit ()
	{
		//ESCで戻る
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
//			return make_shared < Title > ();
		}

		//通常時
		return shared_from_this ();
	}
	
}	//namespace GAME

