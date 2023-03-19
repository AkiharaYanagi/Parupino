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
		: m_fDamage ( LIFE_MAX )
	{
		//---------------------
		//	ゲージ類
		//---------------------

		//ライフゲージ
		//ライフ枠
		m_gaugeFrameLife = make_shared < PrmRect > ();
		m_gaugeFrameLife->SetAllColor ( _CLR ( 0xff606060 ) );
		GRPLST_INSERT ( m_gaugeFrameLife );

		//ライフ減少分
		m_gaugeDecreaseLife = make_shared < PrmRect > ();
		m_gaugeDecreaseLife->SetAllColor ( _CLR ( 0xffff9090 ) );
		GRPLST_INSERT ( m_gaugeDecreaseLife );

		//ライフ
		m_gaugeLife = make_shared < PrmRect > ();
		m_gaugeLife->SetAllColor ( _CLR ( 0xffa0f0d0 ) );
		m_gaugeLife->SetColorN ( 0, _CLR ( 0xffd0f040 ) );
		m_gaugeLife->SetColorN ( 2, _CLR ( 0xfff0f040 ) );
		GRPLST_INSERT ( m_gaugeLife );

		//バランスゲージ
		m_gaugeFrameBalance = make_shared < PrmRect > ();
		m_gaugeFrameBalance->SetAllColor ( _CLR ( 0xff808080 ) );
		GRPLST_INSERT ( m_gaugeFrameBalance );

		m_gaugeDecreaseBalance = make_shared < PrmRect > ();
		m_gaugeDecreaseBalance->SetAllColor ( _CLR ( 0xffff9090 ) );
		GRPLST_INSERT ( m_gaugeDecreaseBalance );

		m_gaugeBalance = make_shared < PrmRect > ();
		m_gaugeBalance->SetAllColor ( _CLR ( 0xffa0d0f0 ) );
		m_gaugeBalance->SetColorN ( 0, _CLR ( 0xff40d0f0 ) );
		m_gaugeBalance->SetColorN ( 2, _CLR ( 0xff40f0f0 ) );
		GRPLST_INSERT ( m_gaugeBalance );
#if 0
		//プレイヤー表示
		m_grpPlayer1P.AddTexture ( _T ( "Player_1P.png" ) );
		m_grpPlayer1P.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayer1P );
		m_grpPlayer2P.AddTexture ( _T ( "Player_2P.png" ) );
		m_grpPlayer2P.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayer2P );
		m_grpPlayerCOM.AddTexture ( _T ( "Player_COM.png" ) );
		m_grpPlayerCOM.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayerCOM );

		//ヒットストップ時間表示
		m_gaugeHitStop.SetAllColor ( _CLR ( 0xffa0a0ff ) );
		m_pGrpAry->InsertTask ( & m_gaugeHitStop );

		//のけぞり時間表示
		m_gaugeLurch.SetAllColor ( _CLR ( 0xffa0ffa0 ) );
		m_pGrpAry->InsertTask ( & m_gaugeLurch );

		//エフェクト
		m_grpHitEf.AddTexture ( _T ( "efHit.png" ) );
		m_pGrpAry->InsertTask ( & m_grpHitEf );

		m_grpAvoidEf.AddTexture ( _T ( "efAvoid.png" ) );
		m_pGrpAry->InsertTask ( & m_grpAvoidEf );

		m_grpPoisedEf.AddTexture ( _T ( "poised0.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised1.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised2.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised3.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised4.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised5.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised6.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised7.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised8.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised9.png" ) );
		AddTask ( & m_grpPoisedEf );
#endif	//0
	}

	DispFrontEnd::~DispFrontEnd ()
	{
	}

	void DispFrontEnd::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;

		float dispGameBaseX = G_BASE_POS ().x;
		float x_l = LIFE_GAUGE_X;
		float y_l = LIFE_GAUGE_Y;
		float w_l = LIFE_GAUGE_W;
		float h_l = LIFE_GAUGE_H;
		float x_b = BALANCE_GAUGE_X;
		float y_b = BALANCE_GAUGE_Y;
		float w_b = BALANCE_GAUGE_W;
		float h_b = BALANCE_GAUGE_H;

		//初期位置
		if ( PLAYER_ID_1 == m_playerID )
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
			m_gaugeFrameLife->SetRect ( x_l - 2, y_l - 2, w_l + 4, h_l + 4 );
			m_gaugeLife->SetRect ( x_l, y_l, w_l, h_l );
			m_gaugeDecreaseLife->SetRect ( 0, 0, 0, 0 );
			
			m_gaugeFrameBalance->SetRect ( x_b - 2, y_b - 2, w_b + 4, h_b + 4 );
			m_gaugeBalance->SetRect ( x_b, y_b, w_b, h_b );
			m_gaugeDecreaseBalance->SetRect ( 0, 0, 0, 0 );
			}
		else if ( PLAYER_ID_2 == m_playerID )
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
			float p2_bx_l = GAME_WINDOW_WIDTH - x_l - w_l;
			m_gaugeFrameLife->SetRect ( p2_bx_l - 2, y_l - 2, w_l + 4, h_l + 4 );
			m_gaugeLife->SetRect ( p2_bx_l, y_l, w_l, h_l );
			m_gaugeDecreaseLife->SetRect ( 0, 0, 0, 0 );

			float p2_bx_b = GAME_WINDOW_WIDTH - x_b - w_b;
			m_gaugeFrameBalance->SetRect ( p2_bx_b - 2, y_b - 2, w_b + 4, h_b + 4 );
			m_gaugeBalance->SetRect ( p2_bx_b, y_b, w_b, h_b );
			m_gaugeDecreaseBalance->SetRect ( 0, 0, 0, 0 );
		}
#if 0
		//ヒットストップ時間表示
		m_gaugeHitStop.SetRect ( 0, 0, 0, 0 );

		//のけぞり時間表示
		m_gaugeLurch.SetRect ( 0, 0, 0, 0 );

		//枠初期化
		InitRect ();
#endif // 0
	}

	void DispFrontEnd::Init ()
	{
		m_fDamage = LIFE_MAX;
		m_gaugeDecreaseLife->SetRect ( 0, 0, 0, 0 );
	}

#if 0
	//ゲージ更新
	void DispFrontEnd::UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance )
	{
		const static float cfl = 1.f * LIFE_GAUGE_W / LIFE_MAX;		//1ライフあたりの表示長さ
		float l = cfl * life;
		float d = cfl * damage;
		float b = cfl * balance;

		const float lw = LIFE_GAUGE_W;
		const float lh = LIFE_GAUGE_H;
		const float lx = LIFE_GAUGE_X;
		const float ly = LIFE_GAUGE_Y;
		const float lx2p = GAME_WINDOW_WIDTH - lx - lw;

		const float bw = BALANCE_GAUGE_W;
		const float bh = BALANCE_GAUGE_H;
		const float bx = BALANCE_GAUGE_X;
		const float by = BALANCE_GAUGE_Y;
		const float bx2p = GAME_WINDOW_WIDTH - bx - bw;

		if ( l < 0 ) { l = 0; }

		if ( PLAYER_ID_1 == playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx + lw - l - d, ly, d, lh );
			m_gaugeLife->SetRect ( lx + lw - l, ly, l, lh );

			//			m_gaugeDecreaseBalance->SetRect ( bx - wb - wd, by, wd, bh );
			m_gaugeBalance->SetRect ( bx + bw - b, by, b, bh );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx2p + l, ly, d, lh );
			m_gaugeLife->SetRect ( lx2p, ly, l, lh );

			//			m_gaugeDecreaseBalance->SetRect ( lx2p + wb, by, wd, bh );
			m_gaugeBalance->SetRect ( bx2p, by, b, bh );
		}

		//硬直時間表示
#if 0
		static bool b2 = true;
		if ( ::GetAsyncKeyState ( '2' ) & 0x0001 ) { b2 ^= 1; }
		if ( b2 )
		{
			//ヒットストップ時間
			m_dispChara.UpdateHitStop ( m_ptChara, m_dirRight, m_hitstop, m_hitstopTimer );

			//のけぞり時間
			m_dispChara.UpdateLurch ( m_ptChara, m_dirRight, m_lurch, m_lurchTimer );
		}
#endif // 0

	}
#endif // 0

	void DispFrontEnd::UpdateGauge ( BtlParam btlPrm )
	{
		const static float cfl = 1.f * LIFE_GAUGE_W / LIFE_MAX;		//1ライフあたりの表示長さ

		//ライフ
		float l = cfl * btlPrm.GetLife ();
		if ( l < 0 ) { l = 0; }

		float d = cfl * m_fDamage;
		if ( m_fDamage < 0 ) { m_fDamage = 0; }

		//ライフよりダメージ分が多い場合
		if ( d > l )
		{
			//徐々に減少
			m_fDamage -= 10;
		}

		const float lw = LIFE_GAUGE_W;
		const float lh = LIFE_GAUGE_H;
		const float lx = LIFE_GAUGE_X;
		const float ly = LIFE_GAUGE_Y;
		const float lx2p = GAME_WINDOW_WIDTH - lx - lw;

		//バランス
		const static float cfb = 1.f * BALANCE_GAUGE_W / BALANCE_MAX;		//1バランスあたりの表示長さ
		float b = cfl * btlPrm.GetBalance ();
		const float bw = BALANCE_GAUGE_W;
		const float bh = BALANCE_GAUGE_H;
		const float bx = BALANCE_GAUGE_X;
		const float by = BALANCE_GAUGE_Y;
		const float bx2p = GAME_WINDOW_WIDTH - bx - bw;


		if ( PLAYER_ID_1 == m_playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx + lw - d, ly, d - l, lh );
			m_gaugeLife->SetRect ( lx + lw - l, ly, l, lh );

			//			m_gaugeDecreaseBalance->SetRect ( bx - wb - wd, by, wd, bh );
			m_gaugeBalance->SetRect ( bx + bw - b, by, b, bh );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx2p + l, ly, d - l, lh );
			m_gaugeLife->SetRect ( lx2p, ly, l, lh );

			//			m_gaugeDecreaseBalance->SetRect ( lx2p + wb, by, wd, bh );
			m_gaugeBalance->SetRect ( bx2p, by, b, bh );
		}

		//硬直時間表示
#if 0
		static bool b2 = true;
		if ( ::GetAsyncKeyState ( '2' ) & 0x0001 ) { b2 ^= 1; }
		if ( b2 )
		{
			//ヒットストップ時間
			m_dispChara.UpdateHitStop ( m_ptChara, m_dirRight, m_hitstop, m_hitstopTimer );

			//のけぞり時間
			m_dispChara.UpdateLurch ( m_ptChara, m_dirRight, m_lurch, m_lurchTimer );
		}
#endif // 0

	}

#if 0
	void DispChara::UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT hitstop, UINT hitstopTimer )
	{
		//のけぞりフレーム時間表示
		float fLurch = 10 * ( (float)hitstop - hitstopTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeHitStop.SetRect ( ( *m_pDispGameBase ).x + ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 ), ptChara.y - fLurch, 10.f, fLurch );
	}

	void DispChara::UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer )
	{
		//のけぞりフレーム時間表示
		float fLurch = 10 * ( (float)lurch - lurchTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeLurch.SetRect ( ( *m_pDispGameBase ).x + ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 ), ptChara.y - fLurch, 10.f, fLurch );
	}
#endif	//0

#if 0

	//ヒット
	void DispChara::OnHit ( VEC2 ptChara, bool dirRight )
	{
		//エフェクトの設定
		m_grpHitEf.SetWait ( 15 );
		m_grpHitEf.SetFadeOut ( 15 );

		//向きによる位置の計算
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( 0, -128 );
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara;
//		m_grpHitEf.GetpMatrix()->SetPos ( img_vec );
		m_grpHitEf.SetPos ( ptChara + VEC2 ( 0, -128 ) );

		//向きは毎回更新する
		float dir = dirRight ? 1.f : -1.f;
		m_grpHitEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpHitEf.SetTargetScaling ( VEC2 ( dir * 1.3f, 1.3f ) );
		m_grpHitEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpHitEf.On ();
	}

	//アヴォイド
	void DispChara::OnAvoid ( VEC2 ptChara, bool dirRight )
	{
		//エフェクトの設定
		m_grpAvoidEf.SetWait ( 15 );
		m_grpAvoidEf.SetFadeIn ( 15 );

		//向きによる位置の計算
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( -128, -256 );
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( 0, -64 );
//		m_grpAvoidEf.GetpMatrix()->SetPos ( img_vec );
//		m_grpAvoidEf.SetPos ( img_vec );
		m_grpAvoidEf.SetPos ( ptChara + VEC2 ( 0, -64 ) );

		//向きは毎回更新する
		float dir = dirRight ? 1.f : -1.f;
		m_grpAvoidEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpAvoidEf.SetTargetScaling ( VEC2 ( dir * 1.3f, 1.3f ) );
		m_grpAvoidEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpAvoidEf.On ();
	}

	//ポイズド
	void DispChara::OnPoised ( VEC2 ptChara, bool dirRight )
	{
		//エフェクトの設定
		m_grpPoisedEf.SetWait ( 15 );
		m_grpPoisedEf.SetFadeIn ( 15 );

		//位置の計算
		m_grpPoisedEf.SetPos ( ptChara + VEC2 ( 0, -96 ) );

		//向きは毎回更新する
		float dir = dirRight ? 1.f : -1.f;
		m_grpPoisedEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpPoisedEf.SetTargetScaling ( VEC2 ( dir * 1.5f, 1.5f ) );
		m_grpPoisedEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpPoisedEf.On ();
	}


#endif // 0


}	//namespace GAME

