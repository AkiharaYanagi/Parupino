//=================================================================================================
//
//	FtgMain ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"
//#include "../Title/Title.h"
#include "../Title_Intro/Title_Intro.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
	{
#if 0

		//戦闘
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );

#endif // 0
		//ポーズメニュ
		m_pauseMenu = make_shared < PauseMenu > ();
		AddpTask ( m_pauseMenu );

		//@info コンストラクタでshared_from_this()を用いない

	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::Load ()
	{

//		m_scene = shared_from_this ();
		m_gameScene = shared_from_this ();

#if 0
		m_pauseMenu->SetwpParent ( shared_from_this () );

#endif // 0

		Scene::Load ();
	}

	void FtgMain::ParamInit ()
	{
#if 0

		m_fighting->ParamInit ( GetpParam () );

#endif // 0
	}


	void FtgMain::Move ()
	{
#if 0
		//メニュポーズ開始
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) )
		{
			m_pauseMenu->On ();
		}

		//メニュポーズ中
		if ( m_pauseMenu->GetActive () )
		{
			m_pauseMenu->Move ();
		}


		//通常動作
//		Scene::Move ();

		//描画に必要なMove()はGRPLSTで行う

		m_fighting->Move ();	//個別で手動
#endif // 0
		Scene::Move ();
	}


	//状態遷移
	P_GameScene FtgMain::Transit ()
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
//		return shared_from_this ();
//		return m_scene;
		return m_gameScene;
	}
	

	//[シーン遷移] タイトルに戻る
	void FtgMain::Transit_Title ()
	{
		GRPLST_CLEAR ();
//		P_Scene&& p = make_shared < Title > ();

//		m_gameScene = make_shared < Title > ();
		m_gameScene = make_shared < Title_Intro > ();

//		m_scene = p;
//		m_scene = make_shared < Title > ();
		GRPLST_LOAD ();
//		GRPLST_INIT ();
	}

	//メニュを消してゲームに戻る
	void FtgMain::Resume_Fighting ()
	{
//		m_pauseMenu->Off ();
	}

}	//namespace GAME

