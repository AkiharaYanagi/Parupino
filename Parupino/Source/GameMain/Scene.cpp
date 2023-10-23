//=================================================================================================
//
// シーン
//		解放と確保を伴う状態遷移
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Scene.h"

//状態遷移先
#include "../Title_Intro/Title_Intro.h"
#include "../Introduction/Introduction.h"
#include "../CharaSele/CharaSele.h"
#include "../FtgMain/FtgMain.h"
#include "../Training/Training.h"
#include "../Demo/DemoMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------------

	Scene::Scene ()
		: m_bTransit ( F )
	{
	}

	Scene::~Scene ()
	{
	}

	//------------------------------------------------------------------
	SceneManager::SceneManager()
	{

		//最初のシーンを設定ファイルから取得する
		m_pParam = make_shared < Param > ();	//パラメータ
		GameSettingFile stgs = m_pParam->GetGameSetting ();
		START_MODE startMode = stgs.GetStartMode ();


		//test
			startMode = START_TITLE_INTRO;
		//	startMode = START_INTRO;
		//	startMode = START_BATTLE;
		//	startMode = START_DEMO;
		//	startMode = START_TRAINING;


		//開始シーンの選択
		P_GameScene pScene = nullptr;
		
		switch ( startMode )
		{
		case START_TITLE:
			//タイトルから開始
//			pScene = make_shared < Title > ();
			break;

		case START_TITLE_INTRO:
			//タイトル イントロから開始
			pScene = make_shared < Title_Intro > ();
//			pScene = make_shared < TestScene > ();
			break;

		case START_INTRO:
			//イントロから開始
			pScene = make_shared < Introduction > ();
			break;

		case START_BATTLE:
			//バトルから開始
			pScene = make_shared < FtgMain > ();
			break;

		case START_TRAINING:
			//トレーニングから開始
			pScene = make_shared < Training > ();
			break;

		case START_DEMO:
			//デモから開始
			pScene = make_shared < DemoMain > ();
			break;
		}

		//パラメータの設定
		pScene->SetpParam ( m_pParam );
		pScene->ParamInit ();
//		pScene->Load ();

		//シーンの設定
		SetScene ( pScene );

#if 0
		//フェード
		m_fade = make_shared < FadeRect > ();
//		m_fade->SetBlackIn ( 60 );
		AddpTask ( m_fade );

#endif // 0
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Move ()
	{
#if 0

		//シーン移項時
		P_Scene pScene = dynamic_pointer_cast < Scene > ( GameSceneManager::GetpScene() );
		if ( pScene->GetTransit () )
		{
			//フェード開始
			m_fade->SetBlackOut ( 60 );
		}
		//フェード中
		if ( m_fade->IsActive () )
		{
			m_fade->Move ();
			return;
		}


#endif // 0
		GameSceneManager::Move ();
	}

}	//namespace GAME

