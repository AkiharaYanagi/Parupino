//=================================================================================================
//
//	FtgMain ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"
#include "../Title_Intro/Title_Intro.h"
#include "../Result/Result.h"


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

		//ロード中
//		m_rectLoad = make_shared < PrmRect > ();
		m_rectLoad = make_shared < TestDraw > ();
		m_rectLoad->SetSize ( VEC2 ( 1280, 960 ) );
		m_rectLoad->SetPos ( VEC2 ( 0, 0 ) );
		m_rectLoad->SetAllColor ( 0xff000000 );
		m_rectLoad->SetZ ( Z_FADE );

		m_rectLoad->Load ();
		m_rectLoad->Move ();

//		m_rectLoad->SetFadeOut ( 10 );	//SetFadeOut()は0xffffffff->0x00ffffffなので白くなる
		m_rectLoad->SetFade ( 3, _CLR(0xff000000), _CLR(0x00000000UL) );	//開始値、目標値を手動設定

		AddpTask ( m_rectLoad );
		GRPLST_INSERT_MAIN ( m_rectLoad );
		m_wait = 0;

		
		m_NowLoading = make_shared < GrpStr > ();
		m_NowLoading->SetStr ( _T ( "Now Loading..." ) );
		m_NowLoading->SetPos ( VEC2 ( 1000, 915 ) );
		m_NowLoading->Load ();
		m_NowLoading->Move ();
		m_NowLoading->SetZ ( Z_FADE - 0.01f );
		AddpTask ( m_NowLoading );
		GRPLST_INSERT_MAIN ( m_NowLoading );


		//----------------------------------------------------
		//@info コンストラクタでshared_from_this()を用いない
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::Load ()
	{
		//Transit用にthisを保存
		mwp_This = shared_from_this ();

		//Menu用にthisを保存
		m_pauseMenu->SetwpParent ( shared_from_this () );

		Scene::Load ();
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}


	void FtgMain::Move ()
	{
		if ( m_rectLoad->GetFadeTimer () == 0 )
		{
			m_NowLoading->SetValid ( F );
		}

		//メニュポーズ中
		if ( m_pauseMenu->GetActive () )
		{
			//メニュポーズ解除
			bool bEsc = ( WND_UTL::AscKey ( VK_ESCAPE ) );
			bool bMenuBtn = ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) );
			if ( bEsc || bMenuBtn )
			{
				m_pauseMenu->Off ();
			}
			else
			{
				m_pauseMenu->Move ();
				return;
			}
		}

		//メニュポーズ開始
		bool bEsc = ( WND_UTL::AscKey ( VK_ESCAPE ) );
		bool bMenuBtn = ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) );
		if ( bEsc || bMenuBtn )
		{
			m_pauseMenu->On ();
		}

		Scene::Move ();

		//終了チェック
		if ( m_fighting->IsEnd () )
		{
			Transit_Result ();
		}
	}


	//状態遷移
	P_GameScene FtgMain::Transit ()
	{
		//他のシーンが確保されたなら遷移する
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//通常時
		return mwp_This.lock();
	}
	

	//[シーン遷移] タイトルに戻る
	void FtgMain::Transit_Title ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Title_Intro > ();
		GRPLST_LOAD ();
	}

	//メニュを消してゲームに戻る
	void FtgMain::Resume_Fighting ()
	{
		m_pauseMenu->Off ();
	}

	//[シーン遷移] リザルト移行
	void FtgMain::Transit_Result ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Result > ();
		GRPLST_LOAD ();
	}

}	//namespace GAME

