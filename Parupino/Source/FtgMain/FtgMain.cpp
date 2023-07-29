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
	{
		m_fighting = make_shared < Fighting > ();
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ();
	}

	void FtgMain::Init ()
	{
		m_fighting->Init ();
		Scene::Init ();
	}


	void FtgMain::Move ()
	{
		m_fighting->Move ();
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
	
	void FtgMain::SetpParam ( P_GameParam && pParam )
	{
		P_Param		p = pParam;
		Scene::SetpParam ( p );
		m_fighting->SetpParam ( GetpParam () );
	}

}	//namespace GAME

