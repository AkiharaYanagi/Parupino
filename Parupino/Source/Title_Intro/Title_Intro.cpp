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
	void TestScene::Load ()
	{
		//遷移先を自身に設定
		mwp_Transit = shared_from_this ();

		Scene::Load ();
	}

	void TestScene::Init ()
	{
		//遷移先を自身に設定
//		m_pTransit = shared_from_this ();

		Scene::Init ();
	}

	P_GameScene TestScene::Transit () 
	{
		return mwp_Transit.lock ();
	}




	Title_Intro::Title_Intro ()
	{
//		m_menuActor = make_shared < Title_MenuActor > ();
//		AddpTask ( m_menuActor );
	}

	Title_Intro::~Title_Intro ()
	{
	}

	void Title_Intro::Load ()
	{
		//アクタに親ポインタを設定
//		m_menuActor->SetwpTitle_Intro ( shared_from_this () );

		//遷移先を自身に設定
		mwp_Transit = shared_from_this ();

		Scene::Load ();
	}

	P_GameScene Title_Intro::Transit ()
	{
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
		return shared_from_this ();
#endif // 0
//		return m_pTransit;
		return shared_from_this ();
	}
#if 0

	//シーン状態遷移
	void Title_Intro::Transit_Intro ()
	{
		GRPLST_CLEAR ();
		m_pTransit = make_shared < Introduction > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_Training ()
	{
		GRPLST_CLEAR ();
		m_pTransit = make_shared < Training > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_1P_VS_2P ()
	{
		GRPLST_CLEAR ();
		m_pTransit = make_shared < FtgMain > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_1P_VS_CPU ()
	{
		GRPLST_CLEAR ();
		m_pTransit = make_shared < Introduction > ();
		GRPLST_LOAD ();
	}

	void Title_Intro::Transit_CPU_VS_CPU ()
	{
		GRPLST_CLEAR ();
		m_pTransit = make_shared < Introduction > ();
		GRPLST_LOAD ();
	}

	//メニュ選択
	void Title_Intro::Select_VS ()
	{
		m_menuActor->Select_VS ();
	}


#endif // 0

}	//namespace GAME

