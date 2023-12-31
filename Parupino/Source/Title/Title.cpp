//=================================================================================================
//
//	タイトル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title.h"
#include "../GameMain/SoundConst.h"

//#include "../Introduction/Introduction.h"
#include "../Introduction/Intro_Img.h"

#include "../Training/Training.h"
#include "../FtgMain/FtgMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	const float Title::OMEGA = D3DX_2PI / ( 12 * 60.f );	//[rad/F]
	const VEC2	Title::KEY_POS ( 400, 930 );

	Title::Title ()
	{
		//---------------------------------------------------
		//グラフィック初期化
		//---------------------------------------------------
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "title_bg.png" ) );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		m_count = 0;

		m_logo = make_shared < GrpAcv > ();
		m_logo->AddTexture ( _T ( "Title_Logo.png" ) );
		m_logo->SetZ ( Z_BG );
		m_logo->SetPos ( VEC2 ( 0, 0 ) );
		AddpTask ( m_logo );
		GRPLST_INSERT_MAIN ( m_logo );

		//---------------------------------------------------
		//メニュ
		m_menuActor = make_shared < Title_Menu_Actor > ();
		AddpTask ( m_menuActor );

		m_explain_bg = make_shared < PrmRect > ();
		m_explain_bg->SetPos ( VEC2 ( 0, 840 ) );
		m_explain_bg->SetSize ( VEC2 ( 1280, 40 ) );
		m_explain_bg->SetAllColor ( _CLR ( 0x80ffffff ) );
		m_explain_bg->SetAllZ ( Z_BG );
		AddpTask ( m_explain_bg );
		GRPLST_INSERT_MAIN ( m_explain_bg );

		m_explain_key = make_shared < GrpAcv > ();
		m_explain_key->AddTexture ( _T("Title_key.png") );
		m_explain_key->SetPos ( KEY_POS );
		AddpTask ( m_explain_key );
		GRPLST_INSERT_MAIN ( m_explain_key );

		m_wait = 0;

		//---------------------------------------------------

		m_demoMode = make_shared < GrpAcv > ();
		m_demoMode->AddTexture ( _T ( "title_demo_mode.png" ) );
		m_demoMode->SetPos ( VEC2 ( KEY_POS.x, 650 ) );
		AddpTask ( m_demoMode );
		GRPLST_INSERT_MAIN ( m_demoMode );

		m_demoTimer = make_shared < Timer > ();
		AddpTask ( m_demoTimer );
	}

	Title::~Title ()
	{
	}

	void Title::ParamInit ()
	{
		//外部指定パラメータによるデモ切替
		P_Param p = GetpParam ();
		GameSettingFile stg = p->GetGameSetting ();

		if ( stg.GetDemo () )
		{
			On_DemoMode ();
		}
		else
		{
			Off_DemoMode ();
		}

//		Scene::ParamInit ();	//純粋仮想関数
	}

	void Title::Load ()
	{
		//遷移先を自身に設定
		Scene::SetwpThis ( shared_from_this () );

		//アクタに親ポインタを設定
//		P_Scene p = std::enable_shared_from_this < Scene > ::shared_from_this () ;
		P_Scene p = std::enable_shared_from_this < Title > ::shared_from_this () ;
		m_menuActor->SetwpScene ( p );

//		m_menuActor->SetwpTitle ( Scene::shared_from_this () );
//		m_menuActor->SetwpTitle ( std::enable_shared_from_this < Title >::shared_from_this () );
		m_menuActor->SetwpTitle ( shared_from_this () );

		//テクスチャの読込の最初の１回は手動で行う
		m_bg->TxLoad ();

		//ウェイトの設定
		m_wait = 0;

		//BGM
		SOUND->Stop_BGM ( BGM_Title );
		SOUND->Play_BGM ( BGM_Title );

		Scene::Load ();
	}


	//フレーム毎動作
	void Title::Move ()
	{
		//===========================================================
		//ESCでアプリケーションを終了(タイトルのみ・他シーンでは1つ戻る)
		if ( WND_UTL::AscKey ( VK_ESCAPE ) ) { ::PostQuitMessage ( 0 ); }
		//===========================================================
		
		//共通BG処理
		float dy = cosf ( OMEGA * m_count );
		m_logo->SetPos ( VEC2 ( 0, -20.f + 5.f * ( 1 - dy ) ) );

		++ m_count;
		if ( OMEGA * m_count > D3DX_2PI ) { m_count = 0; }
		

		//デモ中
		if ( m_demoMode->GetValid () )
		{
			//F1でデモ切替
			if ( WND_UTL::AscKey ( VK_F1 ) )
			{
				Off_DemoMode ();

				//外部指定パラメータによるデモ切替
				P_Param p = GetpParam();
				GameSettingFile stg = p->GetGameSetting();
				stg.SetDemo( F );
				stg.Save();

				//タイトルメニュの初期状態に戻る
				m_menuActor->Return_Start();
			}

			if ( m_demoTimer->IsLast () )
			{
				m_demoTimer->Clear ();
				Scene::Transit_Fighting ( MODE_CPU_CPU );
			}

			m_bg->Move ();
			m_logo->Move ();
			m_demoMode->Move ();
			m_demoTimer->Move ();
			return;	//他のMove()は行わないで終了
		}
		else
		{
			//F1でデモ切替
			if ( WND_UTL::AscKey ( VK_F1 ) )
			{
				On_DemoMode ();


				//外部指定パラメータによるデモ切替
				P_Param p = GetpParam();
				GameSettingFile stg = p->GetGameSetting();
				stg.SetDemo( T );
				stg.Save();
			}
		}

		//開始後、1[F]は入力をチェックしない
		if ( m_wait == 0 )
		{
			m_wait = 1; return;
		}

		//通常時
		Scene::Move ();
	}


	P_GameScene Title::Transit ()
	{
		return Scene::Transit ();
	}

#if 0
	void Title::Transit_Training ()
	{
		SOUND->Stop_BGM ( BGM_Title );
		Scene::Transit_Training ();
	}

	void Title::Transit_1P_VS_2P ()  { TransitFtgMain ( MODE_PLAYER_PLAYER ); }
	void Title::Transit_1P_VS_CPU () { TransitFtgMain ( MODE_PLAYER_CPU ); }
	void Title::Transit_CPU_VS_CPU (){ TransitFtgMain ( MODE_CPU_CPU ); }
#endif // 0


	//VSメニュ選択
	void Title::Select_VS ()
	{
		m_menuActor->Select_VS ();
	}

	//タイトルメニュの最初に戻る
	void Title::Return_Start ()
	{
		m_menuActor->Return_Start ();
	}


	//-------------------------------------
	//デモモード
	void Title::On_DemoMode ()
	{
		m_menuActor->AllOff ();

		m_demoMode->SetValid ( T ); 
		m_demoTimer->SetTargetTime ( 180 );
		m_demoTimer->Start ();

		m_explain_bg->SetValid ( F );
	}

	void Title::Off_DemoMode ()
	{
		m_demoMode->SetValid ( F ); 

		m_explain_bg->SetValid  ( T );
	}




}	//namespace GAME

