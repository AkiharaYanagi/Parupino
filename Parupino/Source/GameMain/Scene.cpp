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
#include "../FtgMain/Fighting.h"
#include "../Training/Training.h"

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
		
		//開始シーンの選択
		switch ( startMode )
		{
		case START_TITLE:
			//タイトルから開始
			pScene = make_shared < Title > ();
			break;

		case START_BATTLE:
			//バトルから開始
			pScene = make_shared < Fighting > ();
			break;

		case START_TRAINING:
			//トレーニングから開始
			pScene = make_shared < Training > ();
			break;

		case START_DEMO:
			//デモから開始
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

