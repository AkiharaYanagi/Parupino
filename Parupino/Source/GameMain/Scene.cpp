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
#include "../Title/Title.h"
#include "../CharaSele/CharaSele.h"
#include "../FtgMain/FtgMain.h"
#include "../Training/Training.h"
#include "../Demo/DemoMain.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{	//------------------------------------------------------------------

	Scene::Scene ()
	{
	}

	Scene::~Scene ()
	{
	}

	//------------------------------------------------------------------
	SceneManager::SceneManager()
	{
		m_pParam = make_shared < Param > ();	//パラメータ
		
		//最初のシーン
		P_GameScene pScene = nullptr;
		GameSettingFile stgs = m_pParam->GetGameSetting ();
		START_MODE startMode = stgs.GetStartMode();


		//test
//		startMode = START_TITLE;
		startMode = START_BATTLE;
//		startMode = START_DEMO;
//		startMode = START_TRAINING;


		//開始シーンの選択
		switch ( startMode )
		{
		case START_TITLE:
			//タイトルから開始
			pScene = make_shared < Title > ();
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

		//シーンの設定
		SetScene( pScene );
	}

	SceneManager::~SceneManager()
	{
	}

}	//namespace GAME

