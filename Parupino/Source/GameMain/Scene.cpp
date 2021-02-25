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
		
		//開始シーンの選択
		if ( m_pParam->GetBattleStart () )
		{
			//トレーニング
			if ( m_pParam->GetTraining () )
			{
				pScene = make_shared < Training > ();
			}
			else
			{
				//バトルから開始
				pScene = make_shared < Fighting > ();
			}
		}
		else
		{
			//タイトルから開始
			pScene = make_shared < Title > ();
//			pScene = make_shared < CharaSele > ();
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

