//=================================================================================================
//
//	FtgMain ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"
#include "../Title/Title.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
	{
		//戦闘
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );

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

		m_pauseMenu->SetpParent ( shared_from_this () );

		Scene::Load ();
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}


	void FtgMain::Move ()
	{

		//メニュポーズ中
		if ( m_pauseMenu->GetActive () )
		{
			m_pauseMenu->Move ();
			return;
		}

		//メニュポーズ開始
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) )
		{
			m_pauseMenu->On ();
			return;
		}

#if 0
		//メニュポーズ中
		if ( m_ynMenu->GetActive () )
		{
			m_ynMenu->Move ();
			return;
		}

		//ポーズ開始
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) )
		{
			m_ynMenu->On ();
			return;
		}
#endif // 0

		//通常動作
		Scene::Move ();
	}


	//状態遷移
	P_GameScene FtgMain::Transit ()
	{
		//ESCで戻る
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}

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
		m_gameScene = make_shared < Title > ();
//		m_scene = p;
//		m_scene = make_shared < Title > ();
		GRPLST_LOAD ();
//		GRPLST_INIT ();
	}

	//メニュを消して戻る
	void FtgMain::Resume_Fighting ()
	{
//		m_pauseMenu->Off ();
	}

}	//namespace GAME

