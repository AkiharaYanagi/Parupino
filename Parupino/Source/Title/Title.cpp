//=================================================================================================
//
//	Title ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title.h"
#include "../FtgMain/Fighting.h"
#include "../Training/Training.h"
#include "../CharaSele/CharaSele.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Title::Title ()
	 :	  m_fadeOutTimer ( 0 ), m_timer ( 0 ), m_blink ( true )
//		, m_muchMode ( MODE_PLAYER_PLAYER )
		, m_menuPos ( TTLM_TRAINING )
		, m_demoTimer ( 0 )
	{
		//Sceneの最初一回のみ、GrpLstをゲームタスクに設定
		AddpTask ( GRPLST_NEW () );

		//各グラフィックの初期化
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "title_bg.png" ) );
//		m_bg->AddTexture ( _T ( "title_bg_cloud.png" ) );
		m_bg->SetZ ( Z_BG );
		GRPLST_INSERT ( m_bg );

		m_titleEf.Load ();		//Efの位置のためここで初期化

		m_logo = make_shared < GrpAcv > ();
		m_logo->AddTexture ( _T ( "title_logo.png" ) );
		m_logo->SetPos ( VEC2 ( (1280 - 1024) * 0.5f, 80 ) );
		m_logo->SetZ ( Z_BG );
		GRPLST_INSERT ( m_logo );

		m_menu = make_shared < GrpAcv > ();
		m_menu->AddTexture ( _T ( "title_menu.png" ) );
		m_menu->SetPos ( VEC2 ( (1280 - 512) * 0.5f, TITLE_menu_y ) );
		m_menu->SetZ ( Z_BG );
		GRPLST_INSERT ( m_menu );

		m_cursor = make_shared < GrpBlink > ();
		m_cursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_cursor->SetPos ( VEC2 ( TTL_CURSOR_X, TTL_CURSOR_Y0 ) );
		m_cursor->SetZ ( Z_BG );
		GRPLST_INSERT ( m_cursor );

		m_demo_mode = make_shared < GrpAcv > ();
		m_demo_mode->AddTexture ( _T("title_demo_mode.png") );
		m_demo_mode->SetPos ( VEC2 ( (1280 - 512) * 0.5f, 700 ) );
		m_demo_mode->SetZ ( Z_BG );
		m_demo_mode->SetValid ( false );
		GRPLST_INSERT ( m_demo_mode );

		m_fade = make_shared < Fade > ();
		m_fade->SetDarkIn ( 15 );
		GRPLST_INSERT ( m_fade );

		//乱数の種
		::srand ( timeGetTime () );
	}

	Title::~Title ()
	{
	}

	void Title::ParamInit ()
	{
	}

	void Title::Load ()
	{
		GameScene::Load ();
	}

	void Title::Init ()
	{
		//デモモードにより表示の切替を初期化
		GetpParam()->GetDemo () ? DemoOn () : DemoOff ();

		//カーソル位置を初期化
		m_cursor->SetPos ( VEC2 ( TTL_CURSOR_X, TTL_CURSOR_Y0 ) );

		GameScene::Init ();
	}

	void Title::Move ()
	{
		//EF
		m_titleEf.Move ();

		//F1でデモモードを切り替え
		if ( ::GetAsyncKeyState ( VK_F1 ) & 0x0001 )
		{
			if ( GetpParam ()->GetDemo () )
			{
				GetpParam ()->SetDemo ( false );
				DemoOff ();		//On->Off
			}
			else
			{
				GetpParam ()->SetDemo ( true );
				DemoOn ();		//Off->On
			}
		}

		//デモモード時は何もしない
		if ( GetpParam()->GetDemo () )
		{
			GameScene::Move ();
			return;
		}

		//カーソル移動
		switch ( m_menuPos )
		{
		case TTLM_TRAINING:   if ( CsrUp () ) { SelectCC (); } if ( CsrDn () ) { SelectPP (); } break;
		case TTLM_1P_VS_2P:   if ( CsrUp () ) { SelectTR (); } if ( CsrDn () ) { SelectPC (); } break;
		case TTLM_1P_VS_CPU:  if ( CsrUp () ) { SelectPP (); } if ( CsrDn () ) { SelectCC (); } break;
		case TTLM_CPU_VS_CPU: if ( CsrUp () ) { SelectPC (); } if ( CsrDn () ) { SelectTR (); } break;
		default: break;
		}

		GameScene::Move ();
	}

	bool Title::CsrUp () {
		if ( PUSH_KEY ( P1_UP ) || PUSH_KEY ( P2_UP ) )
		{
			SOUND->Play ( SE_cursor_move );
			return true;
		}
		return false;
	}
	bool Title::CsrDn () {
		if ( PUSH_KEY ( P1_DOWN ) || PUSH_KEY ( P2_DOWN ) )
		{
			SOUND->Play ( SE_cursor_move );
			return true;
		}
		return false;
	}

	void Title::SelectTR () { m_menuPos = TTLM_TRAINING; SetCrsY ( TTL_CURSOR_Y0 ); }
	void Title::SelectPP () { m_menuPos = TTLM_1P_VS_2P;   SetCrsY ( TTL_CURSOR_Y1 ); }
	void Title::SelectPC () { m_menuPos = TTLM_1P_VS_CPU;  SetCrsY ( TTL_CURSOR_Y2 ); }
	void Title::SelectCC () { m_menuPos = TTLM_CPU_VS_CPU; SetCrsY ( TTL_CURSOR_Y3 ); }

	void Title::SetCrsY ( int y ) { m_cursor->SetPos ( VEC2 ( TTL_CURSOR_X, 1.f * y ) ); }

	MUTCH_MODE Title::MENU_to_MODE ( TITLE_MENU tm, PLAYER_ID id )
	{
		MUTCH_MODE ret = MODE_PLAYER_PLAYER;
		switch ( m_menuPos )
		{
		case TTLM_TRAINING: ret = MODE_PLAYER_CPU; break;
		case TTLM_1P_VS_2P: ret = MODE_PLAYER_PLAYER; break;
		case TTLM_1P_VS_CPU: ret = MODE_PLAYER_CPU; break;
		case TTLM_CPU_VS_CPU: ret = MODE_CPU_CPU; break;
		default: break;
		}

		//2pで決定の場合
		if ( PLAYER_ID_2 == id )
		{
			switch ( m_menuPos )
			{
			case TTLM_TRAINING: ret = MODE_CPU_PLAYER; break;
			case TTLM_1P_VS_2P: ret = MODE_PLAYER_PLAYER; break;
			case TTLM_1P_VS_CPU: ret = MODE_CPU_PLAYER; break;
			case TTLM_CPU_VS_CPU: ret = MODE_CPU_CPU; break;
			default: break;
			}
		}
		return ret;
	}


	P_GameScene Title::Transit ()
	{
		//ESCでアプリケーションを終了(タイトルのみ・他シーンでは1つ戻る)
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 ) 
		{ 
			::PostQuitMessage( 0 );
		}

		//---------------------------------------------------------------
		//デモモード
		if ( GetpParam ()->GetDemo () )
		{
			//自動
			if ( ++ m_demoTimer == DM_TITLE_WAIT )
			{
				m_demoTimer = 0;

				//共通パラメータに値を保存してシーンの移行
				Scene::GetpParam ()->SetMutchMode ( MODE_CPU_CPU );

				//キャラ選択はランダム
				Scene::GetpParam ()->SetRandomChara ();

				//共通グラフィック配列をクリア
//				GRPARY_CLEAR ();

				return make_shared < Fighting > ();
			}

			return shared_from_this ();		//通常は自身を返す
		}

		//---------------------------------------------------------------
		//通常(非デモモード)時

		//キー1でシーンを進める
		if ( PUSH_KEY ( P1_BUTTON1 ) )
		{
			//共通パラメータに値を保存してシーンの移行
			Scene::GetpParam ()->SetMutchMode ( MENU_to_MODE ( m_menuPos, PLAYER_ID_1 ) );

			m_fade->SetDarkOut ( 15 );
			m_fadeOutTimer = 17;
		}

		if ( PUSH_KEY ( P2_BUTTON1 ) )
		{
			//共通パラメータに値を保存してシーンの移行
			Scene::GetpParam ()->SetMutchMode ( MENU_to_MODE ( m_menuPos, PLAYER_ID_2 ) );

			m_fade->SetDarkOut ( 15 );
			m_fadeOutTimer = 17;
		}

		if ( 0 != m_fadeOutTimer )
		{
			-- m_fadeOutTimer;
			if ( 0 == m_fadeOutTimer )
			{
				//共通グラフィック配列をクリア
				GRPLST_CLEAR ();

				//パラメータに記録
				P_Param pParam = GetpParam ();

				//トレーニング
				if ( TTLM_TRAINING == m_menuPos )
				{
					pParam->SetTraining ( true );					
					return make_shared < CharaSele > ();
//					return make_shared < Training > ();
				}
				else
				{
					//メイン
					pParam->SetTraining ( false );
					return make_shared < CharaSele > ();
	//				return make_shared < Fighting > ();
				}
			}
		}

		return shared_from_this ();		//通常は自身を返す
	}


	void Title::DemoOn ()
	{
		//デモモード表示:true
		m_demo_mode->SetValid ( true );
		m_demoTimer = 0;
		//通常メニュー:false
		m_cursor->SetValid ( false );
		m_menu->SetValid ( false );
	}

	void Title::DemoOff ()
	{
		//デモモード表示:false
		m_demo_mode->SetValid ( false );
		m_demoTimer = 0;
		//通常メニュー:true
		m_cursor->SetValid ( true );
		m_menu->SetValid ( true );
	}

}	//namespace GAME

