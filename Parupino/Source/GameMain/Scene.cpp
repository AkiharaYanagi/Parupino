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
		//Transit用にthisを保存
		mwp_This = shared_from_this ();

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
		//BGM
//		SOUND->Stop_BGM ( BGM_Main );

		GRPLST_CLEAR ();
		mp_Transit = make_shared < Title_Intro > ();
		GRPLST_LOAD ();
	}
	
#if 0
	//メニュを消してゲームに戻る
	void Scene::Resume_Fighting ()
	{
		m_pauseMenu->Off ();
	}
#endif // 0

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
		P_GameScene pScene = nullptr;
		
		switch ( startMode )
		{
		case START_TITLE_INTRO:
			//タイトル イントロから開始
			pScene = make_shared < Title_Intro > ();
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

		case START_DEMO:
			//デモから開始
			pScene = make_shared < Title_Intro > ();
			break;

#if 0
		case TEST_VOID:
			//テスト：空のシーン
			pScene = make_shared < TestScene > ();
			break;
#endif // 0

		}

		//パラメータの設定
		pScene->SetpParam ( m_pParam );
		pScene->ParamInit ();
		pScene->Load ();

		//シーンの設定
		SetScene ( pScene );
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Move ()
	{
		GameSceneManager::Move ();
	}


}	//namespace GAME

