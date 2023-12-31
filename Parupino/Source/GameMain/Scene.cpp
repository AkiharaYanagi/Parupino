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

#include "../Introduction/Introduction.h"
#include "../Introduction/Intro_Img.h"		//画像のみのイントロ

#include "../CharaSele/CharaSele.h"
#include "../FtgMain/FtgMain.h"
#include "../Training/Training.h"
//#include "../Demo/DemoMain.h"
#include "../Result/Result.h"

//SoundOff
#include "../GameMain/SoundConst.h"


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

	void Scene::Load ()
	{
		GameScene::Load ();
	}

	//状態遷移
	P_GameScene Scene::Transit ()
	{
		//他のシーンが確保されたなら遷移する
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//通常時
		return mwp_This.lock ();
	}


	//[シーン遷移] タイトルに戻る
	void Scene::Transit_Title ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Title > ();
		GRPLST_LOAD ();
	}
	
	//[シーン遷移] リザルトに移行
	void Scene::Transit_Result ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Result > ();
		GRPLST_LOAD ();
	}

	//[シーン遷移] イントロに移行
	void Scene::Transit_Intro ()
	{
		GRPLST_CLEAR ();
//		mp_Transit = make_shared < Introduction > ();
		mp_Transit = make_shared < Intro_Img > ();
		GRPLST_LOAD ();
	}

	//[シーン遷移] ファイティングに移行
	void Scene::Transit_Fighting ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < FtgMain > ();
		GRPLST_LOAD ();
	}

	void Scene::Transit_Fighting ( MUTCH_MODE mode )
	{
		Transit_Fighting ();
		GetpParam ()->SetMutchMode ( mode );
	}

	//[シーン遷移] トレーニングに移行
	void Scene::Transit_Training ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Training > ();
		GRPLST_LOAD ();
	}


	//====================================================================
	SceneManager::SceneManager()
	{
		//格闘部分共通パラメータシングルトン生成
		G_Ftg::Create ();


		//最初のシーンを設定ファイルから取得する
		m_pParam = make_shared < Param > ();	//パラメータ
		GameSettingFile stgs = m_pParam->GetGameSetting ();
		START_MODE startMode = stgs.GetStartMode ();

#if 0
		//test
		startMode = START_TITLE_INTRO;
//		startMode = START_INTRO;
//		startMode = START_CHARA_SELE;
//		startMode = START_BATTLE;
//		startMode = START_RESULT;
//		startMode = START_DEMO;
//		startMode = START_TRAINING;
//		startMode = TEST_VOID;
#endif // 0


		//開始シーンの選択
		P_Scene pScene = nullptr;
		
		switch ( startMode )
		{
		case START_TITLE_INTRO:
			//タイトルから開始
			pScene = make_shared < Title > ();
			break;

		case START_INTRO:


			//イントロから開始
//			pScene = make_shared < Introduction > ();
			pScene = make_shared < Intro_Img > ();

			
			break;

		case START_CHARA_SELE:
			//キャラセレから開始
//			pScene = make_shared < CharaSelect > ();
			break;

		case START_BATTLE:
			//バトルから開始
			pScene = make_shared < FtgMain > ();
			break;

		case START_RESULT:
			//リザルトから開始
			pScene = make_shared < Result > ();
			break;

		case START_TRAINING:
			//トレーニングから開始
			pScene = make_shared < Training > ();
			break;

#if 0
		case START_DEMO:
			//デモから開始
			pScene = make_shared < Title > ();
			break;

		case TEST_VOID:
			//テスト：空のシーン
			pScene = make_shared < TestScene > ();
			break;
#endif // 0

		}

		//シーンの設定
		SetScene ( pScene );
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Load ()
	{
		P_GameScene pScene = GetpScene ();

		//パラメータの設定
		pScene->SetpParam ( m_pParam );
		pScene->ParamInit ();
//		pScene->Load ();

		GameSceneManager::Load ();
	}

	void SceneManager::Move ()
	{
		GameSceneManager::Move ();
	}


}	//namespace GAME

