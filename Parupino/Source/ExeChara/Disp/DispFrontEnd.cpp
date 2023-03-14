//=================================================================================================
//
// DispFrontEnd ƒ\[ƒXƒtƒ@ƒCƒ‹
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ƒwƒbƒ_ƒtƒ@ƒCƒ‹‚ÌƒCƒ“ƒNƒ‹[ƒh
//-------------------------------------------------------------------------------------------------
#include "DispFrontEnd.h"

//-------------------------------------------------------------------------------------------------
// ’è‹`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DispFrontEnd::DispFrontEnd ()
	{
<<<<<<< HEAD
		//ƒ‰ƒCƒtƒQ[ƒW
=======
		//---------------------
		//	ƒQ[ƒW—Ş
		//---------------------

		//ƒ‰ƒCƒt˜g
>>>>>>> origin/ExeCharaã‚’StateåŒ–ã™ã‚‹
		m_gaugeFrameLife = make_shared < PrmRect > ();
		m_gaugeFrameLife->SetAllColor ( _CLR ( 0xff404040 ) );
		GRPLST_INSERT ( m_gaugeFrameLife );

		//ƒ‰ƒCƒtŒ¸­•ª
		m_gaugeDecreaseLife = make_shared < PrmRect > ();
		m_gaugeDecreaseLife->SetAllColor ( _CLR ( 0xffff9090 ) );
		GRPLST_INSERT ( m_gaugeDecreaseLife );

		//ƒ‰ƒCƒt
		m_gaugeLife = make_shared < PrmRect > ();
		m_gaugeLife->SetAllColor ( _CLR ( 0xffa0f0d0 ) );
		m_gaugeLife->SetColorN ( 0, _CLR ( 0xffd0f040 ) );
		m_gaugeLife->SetColorN ( 2, _CLR ( 0xfff0f040 ) );
		GRPLST_INSERT ( m_gaugeLife );

<<<<<<< HEAD
		//ƒoƒ‰ƒ“ƒXƒQ[ƒW
		m_gaugeFrameBalance = make_shared < PrmRect > ();
		m_gaugeFrameBalance->SetAllColor ( _CLR ( 0xff404040 ) );
		GRPLST_INSERT ( m_gaugeFrameBalance );

		m_gaugeDecreaseBalance = make_shared < PrmRect > ();
		m_gaugeDecreaseBalance->SetAllColor ( _CLR ( 0xffff9090 ) );
		GRPLST_INSERT ( m_gaugeDecreaseBalance );

		m_gaugeBalance = make_shared < PrmRect > ();
		m_gaugeBalance->SetAllColor ( _CLR ( 0xffa0d0f0 ) );
		m_gaugeBalance->SetColorN ( 0, _CLR ( 0xff40d0f0 ) );
		m_gaugeBalance->SetColorN ( 2, _CLR ( 0xff40f0f0 ) );
		GRPLST_INSERT ( m_gaugeBalance );
=======
#if 0
		//ƒvƒŒƒCƒ„[•\¦
		m_grpPlayer1P.AddTexture ( _T ( "Player_1P.png" ) );
		m_grpPlayer1P.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayer1P );
		m_grpPlayer2P.AddTexture ( _T ( "Player_2P.png" ) );
		m_grpPlayer2P.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayer2P );
		m_grpPlayerCOM.AddTexture ( _T ( "Player_COM.png" ) );
		m_grpPlayerCOM.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayerCOM );

		//ƒqƒbƒgƒXƒgƒbƒvŠÔ•\¦
		m_gaugeHitStop.SetAllColor ( _CLR ( 0xffa0a0ff ) );
		m_pGrpAry->InsertTask ( & m_gaugeHitStop );

		//‚Ì‚¯‚¼‚èŠÔ•\¦
		m_gaugeLurch.SetAllColor ( _CLR ( 0xffa0ffa0 ) );
		m_pGrpAry->InsertTask ( & m_gaugeLurch );

		//ƒGƒtƒFƒNƒg
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
>>>>>>> origin/ExeCharaã‚’StateåŒ–ã™ã‚‹
	}

	DispFrontEnd::~DispFrontEnd ()
	{
	}

	void DispFrontEnd::LoadPlayer ( PLAYER_ID playerID )
	{
		float dispGameBaseX = G_BASE_POS ().x;

		//‰ŠúˆÊ’u
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
			
			m_gaugeFrameBalance->SetRect ( BALANCE_GAUGE_X - 2, BALANCE_GAUGE_Y - 2, GAUGE_WIDTH + 4, GAUGE_HEIGHT + 4 );
			m_gaugeBalance->SetRect ( BALANCE_GAUGE_X, BALANCE_GAUGE_Y, GAUGE_WIDTH, GAUGE_HEIGHT );
			m_gaugeDecreaseBalance->SetRect ( 0, 0, 0, 0 );
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
			m_gaugeFrameLife->SetRect ( GAME_WINDOW_WIDTH - GAUGE_WIDTH - BALANCE_GAUGE_X - 2, BALANCE_GAUGE_Y - 2, GAUGE_WIDTH + 4, GAUGE_HEIGHT + 4 );
			m_gaugeLife->SetRect ( GAME_WINDOW_WIDTH - GAUGE_WIDTH - LIFE_GAUGE_X, LIFE_GAUGE_Y, GAUGE_WIDTH, GAUGE_HEIGHT );
			m_gaugeDecreaseLife->SetRect ( 0, 0, 0, 0 );

			m_gaugeFrameBalance->SetRect ( GAME_WINDOW_WIDTH - GAUGE_WIDTH - BALANCE_GAUGE_X - 2, BALANCE_GAUGE_Y - 2, GAUGE_WIDTH + 4, GAUGE_HEIGHT + 4 );
			m_gaugeBalance->SetRect ( GAME_WINDOW_WIDTH - GAUGE_WIDTH - BALANCE_GAUGE_X, BALANCE_GAUGE_Y, GAUGE_WIDTH, GAUGE_HEIGHT );
			m_gaugeDecreaseBalance->SetRect ( 0, 0, 0, 0 );
		}
#if 0
		//ƒqƒbƒgƒXƒgƒbƒvŠÔ•\¦
		m_gaugeHitStop.SetRect ( 0, 0, 0, 0 );

		//‚Ì‚¯‚¼‚èŠÔ•\¦
		m_gaugeLurch.SetRect ( 0, 0, 0, 0 );

		//˜g‰Šú‰»
		InitRect ();
#endif // 0
	}

	//ƒQ[ƒWXV
	void DispFrontEnd::UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance )
	{
		const static float cfl = 1.f * GAUGE_WIDTH / LIFE_MAX;		//1ƒ‰ƒCƒt‚ ‚½‚è‚Ì•\¦’·‚³
		float wl = cfl * life;
		float wd = cfl * damage;

		const float lx = LIFE_GAUGE_X + GAUGE_WIDTH;

		const float lx2p = GAME_WINDOW_WIDTH - LIFE_GAUGE_X - GAUGE_WIDTH;

		if ( wl < 0 ) { wl = 0; }

		if ( PLAYER_ID_1 == playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx - wl - wd, LIFE_GAUGE_Y, wd, GAUGE_HEIGHT );
			m_gaugeLife->SetRect ( lx - wl, LIFE_GAUGE_Y, wl, GAUGE_HEIGHT );

			m_gaugeDecreaseBalance->SetRect ( lx - wl - wd, BALANCE_GAUGE_Y, wd, GAUGE_HEIGHT );
			m_gaugeBalance->SetRect ( lx - wl, BALANCE_GAUGE_Y, wl, GAUGE_HEIGHT );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx2p + wl, LIFE_GAUGE_Y, wd, GAUGE_HEIGHT );
			m_gaugeLife->SetRect ( lx2p, LIFE_GAUGE_Y, wl, GAUGE_HEIGHT );

			m_gaugeDecreaseBalance->SetRect ( lx2p + wl, BALANCE_GAUGE_Y, wd, GAUGE_HEIGHT );
			m_gaugeBalance->SetRect ( lx2p, BALANCE_GAUGE_Y, wl, GAUGE_HEIGHT );
		}

		//d’¼ŠÔ•\¦
#if 0
		static bool b2 = true;
		if ( ::GetAsyncKeyState ( '2' ) & 0x0001 ) { b2 ^= 1; }
		if ( b2 )
		{
			//ƒqƒbƒgƒXƒgƒbƒvŠÔ
			m_dispChara.UpdateHitStop ( m_ptChara, m_dirRight, m_hitstop, m_hitstopTimer );

			//‚Ì‚¯‚¼‚èŠÔ
			m_dispChara.UpdateLurch ( m_ptChara, m_dirRight, m_lurch, m_lurchTimer );
		}
#endif // 0

	}

#if 0
	void DispChara::UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT hitstop, UINT hitstopTimer )
	{
		//‚Ì‚¯‚¼‚èƒtƒŒ[ƒ€ŠÔ•\¦
		float fLurch = 10 * ( (float)hitstop - hitstopTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeHitStop.SetRect ( ( *m_pDispGameBase ).x + ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 ), ptChara.y - fLurch, 10.f, fLurch );
	}

	void DispChara::UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer )
	{
		//‚Ì‚¯‚¼‚èƒtƒŒ[ƒ€ŠÔ•\¦
		float fLurch = 10 * ( (float)lurch - lurchTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeLurch.SetRect ( ( *m_pDispGameBase ).x + ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 ), ptChara.y - fLurch, 10.f, fLurch );
	}
#endif	//0

#if 0

	//ƒqƒbƒg
	void DispChara::OnHit ( VEC2 ptChara, bool dirRight )
	{
		//ƒGƒtƒFƒNƒg‚Ìİ’è
		m_grpHitEf.SetWait ( 15 );
		m_grpHitEf.SetFadeOut ( 15 );

		//Œü‚«‚É‚æ‚éˆÊ’u‚ÌŒvZ
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( 0, -128 );
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara;
//		m_grpHitEf.GetpMatrix()->SetPos ( img_vec );
		m_grpHitEf.SetPos ( ptChara + VEC2 ( 0, -128 ) );

		//Œü‚«‚Í–ˆ‰ñXV‚·‚é
		float dir = dirRight ? 1.f : -1.f;
		m_grpHitEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpHitEf.SetTargetScaling ( VEC2 ( dir * 1.3f, 1.3f ) );
		m_grpHitEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpHitEf.On ();
	}

	//ƒAƒ”ƒHƒCƒh
	void DispChara::OnAvoid ( VEC2 ptChara, bool dirRight )
	{
		//ƒGƒtƒFƒNƒg‚Ìİ’è
		m_grpAvoidEf.SetWait ( 15 );
		m_grpAvoidEf.SetFadeIn ( 15 );

		//Œü‚«‚É‚æ‚éˆÊ’u‚ÌŒvZ
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( -128, -256 );
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( 0, -64 );
//		m_grpAvoidEf.GetpMatrix()->SetPos ( img_vec );
//		m_grpAvoidEf.SetPos ( img_vec );
		m_grpAvoidEf.SetPos ( ptChara + VEC2 ( 0, -64 ) );

		//Œü‚«‚Í–ˆ‰ñXV‚·‚é
		float dir = dirRight ? 1.f : -1.f;
		m_grpAvoidEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpAvoidEf.SetTargetScaling ( VEC2 ( dir * 1.3f, 1.3f ) );
		m_grpAvoidEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpAvoidEf.On ();
	}

	//ƒ|ƒCƒYƒh
	void DispChara::OnPoised ( VEC2 ptChara, bool dirRight )
	{
		//ƒGƒtƒFƒNƒg‚Ìİ’è
		m_grpPoisedEf.SetWait ( 15 );
		m_grpPoisedEf.SetFadeIn ( 15 );

		//ˆÊ’u‚ÌŒvZ
		m_grpPoisedEf.SetPos ( ptChara + VEC2 ( 0, -96 ) );

		//Œü‚«‚Í–ˆ‰ñXV‚·‚é
		float dir = dirRight ? 1.f : -1.f;
		m_grpPoisedEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpPoisedEf.SetTargetScaling ( VEC2 ( dir * 1.5f, 1.5f ) );
		m_grpPoisedEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpPoisedEf.On ();
	}


#endif // 0


}	//namespace GAME

