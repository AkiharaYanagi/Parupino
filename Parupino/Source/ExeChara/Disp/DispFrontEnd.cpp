//=================================================================================================
//
// DispFrontEnd ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispFrontEnd.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DispFrontEnd::DispFrontEnd ()
	{
		//ゲージ
		m_gaugeFrameLife = make_shared < PrmRect > ();
		m_gaugeFrameLife->SetAllColor ( _CLR ( 0xff404040 ) );
		GRPLST_INSERT ( m_gaugeFrameLife );

		m_gaugeDecreaseLife = make_shared < PrmRect > ();
		m_gaugeDecreaseLife->SetAllColor ( _CLR ( 0xffff9090 ) );
		GRPLST_INSERT ( m_gaugeDecreaseLife );

		m_gaugeLife = make_shared < PrmRect > ();
		m_gaugeLife->SetAllColor ( _CLR ( 0xffa0f0d0 ) );
		m_gaugeLife->SetColorN ( 0, _CLR ( 0xffd0f040 ) );
		m_gaugeLife->SetColorN ( 2, _CLR ( 0xfff0f040 ) );
		GRPLST_INSERT ( m_gaugeLife );
	}

	DispFrontEnd::~DispFrontEnd ()
	{
	}

	void DispFrontEnd::InitDisp ( PLAYER_ID playerID )
	{
		float dispGameBaseX = G_BASE_POS ().x;

		//初期位置
		if ( PLAYER_ID_1 == playerID )
		{
#if 0
			if ( cpu )
			{
				m_grpPlayerCOM.GetpMatrix ()->SetValid ( true );
				m_grpPlayerCOM.GetpMatrix ()->SetPos ( VEC2 ( GRP_PLAYER1_X, GRP_PLAYER1_Y ) );
			}
			else
			{
				m_grpPlayer1P.GetpMatrix ()->SetValid ( true );
				m_grpPlayer1P.GetpMatrix ()->SetPos ( VEC2 ( GRP_PLAYER1_X, GRP_PLAYER1_Y ) );
			}
#endif // 0
			m_gaugeFrameLife->SetRect ( LIFE_GAUGE_X - 2, LIFE_GAUGE_Y - 2, GAUGE_WIDTH + 4, GAUGE_HEIGHT + 4 );
			m_gaugeLife->SetRect ( LIFE_GAUGE_X, LIFE_GAUGE_Y, GAUGE_WIDTH, GAUGE_HEIGHT );
			m_gaugeDecreaseLife->SetRect ( 0, 0, 0, 0 );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
#if 0
			if ( cpu )
			{
				m_grpPlayerCOM.GetpMatrix ()->SetValid ( true );
				m_grpPlayerCOM.GetpMatrix ()->SetPos ( VEC2 ( GRP_PLAYER2_X, GRP_PLAYER2_Y ) );
			}
			else
			{
				m_grpPlayer2P.GetpMatrix ()->SetValid ( true );
				m_grpPlayer2P.GetpMatrix ()->SetPos ( VEC2 ( GRP_PLAYER2_X, GRP_PLAYER2_Y ) );
			}
#endif // 0
			m_gaugeFrameLife->SetRect ( GAME_WINDOW_WIDTH - GAUGE_WIDTH - LIFE_GAUGE_X - 2, LIFE_GAUGE_Y - 2, GAUGE_WIDTH + 4, GAUGE_HEIGHT + 4 );
			m_gaugeLife->SetRect ( GAME_WINDOW_WIDTH - GAUGE_WIDTH - LIFE_GAUGE_X, LIFE_GAUGE_Y, GAUGE_WIDTH, GAUGE_HEIGHT );
			m_gaugeDecreaseLife->SetRect ( 0, 0, 0, 0 );
		}
	}

	//ゲージ更新
	void DispFrontEnd::UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance )
	{
		const static float cfl = 1.f * GAUGE_WIDTH / LIFE_MAX;		//1ライフあたりの表示長さ
		float wl = cfl * life;
		float wd = cfl * damage;

		const float lx = LIFE_GAUGE_X + GAUGE_WIDTH;

		const float lx2p = GAME_WINDOW_WIDTH - LIFE_GAUGE_X - GAUGE_WIDTH;

		if ( wl < 0 ) { wl = 0; }

		if ( PLAYER_ID_1 == playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx - wl - wd, LIFE_GAUGE_Y, wd, GAUGE_HEIGHT );
			m_gaugeLife->SetRect ( lx - wl, LIFE_GAUGE_Y, wl, GAUGE_HEIGHT );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx2p + wl, LIFE_GAUGE_Y, wd, GAUGE_HEIGHT );
			m_gaugeLife->SetRect ( lx2p, LIFE_GAUGE_Y, wl, GAUGE_HEIGHT );
		}

	}


}	//namespace GAME

