//=================================================================================================
//
//	MutualChara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "MutualChara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MutualChara::MutualChara ()
		: m_startTimer ( 0 ), m_startTime ( 0 ), m_endTimer ( 0 ), m_endTime ( 0 )
		, m_tmrHitstop ( 0 ), m_blackOut ( 0 )
	{
		//キャラ
		m_exeChara1 = make_shared < ExeChara > ( PLAYER_ID_1 );
		m_exeChara2 = make_shared < ExeChara > ( PLAYER_ID_2 );

		m_exeChara1->SetpOther ( m_exeChara2 );
		m_exeChara2->SetpOther ( m_exeChara1 );

		AddpTask ( m_exeChara1 );
		AddpTask ( m_exeChara2 );

		m_decision.SetpChara (m_exeChara1, m_exeChara2);

		//ヒットストップタイマー
		m_tmrHitstop = make_shared < Timer > ();
		m_tmrHitstop->SetTargetTime ( HITSTOP_TIME );
		AddpTask ( m_tmrHitstop );
		m_decision.SetpHitStop ( m_tmrHitstop );

		//共通エフェクト
		m_efClang = make_shared < EfClang > ();
		GRPLST_INSERT ( m_efClang );
		m_efSpark = make_shared < EfSpark > ();
		GRPLST_INSERT ( m_efSpark );
//		m_testEf = make_shared < TestEf > ();
//		GRPLST_INSERT ( m_testEf );

		m_decision.SetpCommonEf (m_efClang, m_efSpark);
	}

	MutualChara::~MutualChara ()
	{
	}

	void MutualChara::ParamInit ( P_Param pParam )
	{
		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
	}


	void MutualChara::Start ()
	{
		m_exeChara1->Init ();
		m_exeChara2->Init ();
	}


	//■#########################################################
	//■
	//■	スクリプトの毎フレーム処理
	//■
	//■#########################################################
	void MutualChara::Conduct ()
	{
		//---------------------------------------------------
		//システム変更
		SwitchRect ();	//枠表示切替
		SwithcCPU ();	//CPU操作切替
		//---------------------------------------------------

		//◆スクリプト前処理(入力、移動など)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//◆相互判定(ぶつかり枠)
		Collision ();

		//◆ぶつかり後、攻撃・ヒット判定枠を設定
		m_exeChara1->ScriptRectMove ();
		m_exeChara2->ScriptRectMove ();

		//◆相互判定(攻撃・ヒット枠)
		Decision ();

		//◆スクリプト後処理(グラフィック位置など)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//グラフィック共通
		Grp ();
	}
	//■#########################################################



	//◆================================
	//◆		相互判定(ぶつかり枠)
	//◆================================
	void MutualChara::Collision ()
	{
		//両者の接触枠を取得
		P_CharaRect pCharaRect1p = m_exeChara1->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_exeChara2->GetpCharaRect ();
		PV_RECT pvRect1p = pCharaRect1p->GetpvCRect ();
		PV_RECT pvRect2p = pCharaRect2p->GetpvCRect ();

		//接触判定
		//重なっているとき
		if ( OverlapAryRect ( pvRect1p, pvRect2p ) )
		{
			m_exeChara1->BackPtX ();	//互いにx方向のみ位置を戻す
			m_exeChara2->BackPtX ();

			//さらに重なっているとき
			int i = 0;
			while ( OverlapAryRect ( pvRect1p, pvRect2p ) )
			{
				m_exeChara1->BackMoveX ();	//微調整
				m_exeChara2->BackMoveX ();

				m_exeChara1->AdjustCRect ();
				m_exeChara2->AdjustCRect ();

				pvRect1p = pCharaRect1p->GetpvCRect ();
				pvRect2p = pCharaRect2p->GetpvCRect ();

				if ( ++i > 10 ) { break; }
			}
		}

		//振向
		m_exeChara1->LookOther ();
		m_exeChara2->LookOther ();

		//距離制限(画面端同士)
		float p1x = m_exeChara1->GetPos ().x;
		float p2x = m_exeChara2->GetPos ().x;
		
		// P1 << P2
		if ( p2x - p1x > GAME_WINDOW_WIDTH - FIELD_EDGE * 2 )
		{
			m_exeChara1->BackPtX ();	//互いに位置を戻す
			m_exeChara2->BackPtX ();
		}
		// P2 << P1
		else if ( p1x - p2x > GAME_WINDOW_WIDTH - FIELD_EDGE * 2 )
		{
			m_exeChara1->BackPtX ();	//互いに位置を戻す
			m_exeChara2->BackPtX ();
		}
	}

	//◆================================
	//◆		相互判定 (攻撃・ヒット枠)
	//◆================================
	void MutualChara::Decision ()
	{
		m_decision.Do ();
	}

	//◆================================
	//◆		共通グラフィック
	//◆================================
	void MutualChara::Grp ()
	{
		//---------------------------------------------------
		//暗転
		UINT blackout1P = m_exeChara1->GetBlackOut ();
		UINT blackout2P = m_exeChara2->GetBlackOut ();
		if ( 0 < blackout1P )
		{
			m_blackOut = blackout1P;
			m_exeChara1->SetBlackOut ( 0 );
		}

		//---------------------------------------------------
		//スクリプトからの停止
		UINT scpStop1P = m_exeChara1->GetScpStop ();
		UINT scpStop2P = m_exeChara2->GetScpStop ();
		if ( 0 < scpStop1P )
		{
			m_scpStop = scpStop1P;
			m_exeChara1->SetScpStop ( 0 );

			m_exeChara1->SetStopTimer ( m_scpStop );
			m_exeChara2->SetStopTimer ( m_scpStop );
		}

		//---------------------------------------------------
		//画面表示の基準位置を決定
		VEC2 pos1p = m_exeChara1->GetPos ();
		VEC2 pos2p = m_exeChara2->GetPos ();
		G_Ftg::inst ()->CulcPosMutualBase ( pos1p, pos2p );
	}



	//------------------------------------------------------
	//	終了判定
	//------------------------------------------------------
	bool MutualChara::CheckZeroLife ()
	{
		//終了判定
		bool finish1p = m_exeChara1->IsZeroLife ();
		bool finish2p = m_exeChara2->IsZeroLife ();
		return ( finish1p || finish2p );
	}

	bool MutualChara::CheckDown ()
	{
		//ダウン判定
		bool down1p = m_exeChara1->IsDown ();
		bool down2p = m_exeChara2->IsDown ();
		return (down1p || down2p);
	}

	bool MutualChara::CheckDownEnd ()
	{
		//ダウン判定
		bool downEnd1p = m_exeChara1->IsDownEnd ();
		bool downEnd2p = m_exeChara2->IsDownEnd ();
		return (downEnd1p || downEnd2p);
	}

	bool MutualChara::CheckWin ()
	{
		//勝利状態判定
		bool win1p = m_exeChara1->IsWin ();
		bool win2p = m_exeChara2->IsWin ();
		return (win1p || win2p);
	}

	bool MutualChara::CheckWinEnd ()
	{
		//勝利状態判定
		bool winEnd1p = m_exeChara1->IsWinEnd ();
		bool winEnd2p = m_exeChara2->IsWinEnd ();
		return (winEnd1p || winEnd2p);
	}

	bool MutualChara::CheckWinner ()
	{
		bool bRet = false;

		//ライフで勝利者を決定する
		int life1p = m_exeChara1->GetLife ();
		int life2p = m_exeChara2->GetLife ();

		//Double K.O.
		if ( life1p <= 0 && life2p <= 0 ) { m_winner = WINNER_DP; }
		//2P Win
		else if ( life1p <= 0 ) { m_winner = WINNER_2P; }
		//1P Win
		else if ( life2p <= 0 ) { m_winner = WINNER_1P; }
		//Draw
		else if ( life1p == life2p ) { m_winner = WINNER_DRAW; }

		switch ( m_winner )
		{
		case WINNER_1P: 
			m_exeChara1->SetCharaState ( CHST_WIN_END );
			m_exeChara2->SetCharaState ( CHST_DOWN_END );
			break;
		case WINNER_2P: 
			m_exeChara1->SetCharaState ( CHST_DOWN_END );
			m_exeChara2->SetCharaState ( CHST_WIN_END );
			break;
		case WINNER_DP: break;
		default: break;
		}

		return bRet;
	}

	CHARA_NAME MutualChara::GetWinnerName () const
	{
		switch ( m_winner )
		{
		case WINNER_1P: return m_exeChara1->GetCharaName (); break;
		case WINNER_2P: return m_exeChara2->GetCharaName (); break;
		case WINNER_DP: break;
		default: break;
		}
		return CHARA_NAME ();
	}


	void MutualChara::ForcedEnd ()
	{
		m_exeChara1->ForcedEnd ();
		m_exeChara2->ForcedEnd ();
	}

	//------------------------------------------------------
	//	内部関数
	//------------------------------------------------------

	//------------------------------------------------------
	//枠表示切替 ExeCharaで呼ぶと1P2Pで２回呼ばれてしまう
	void MutualChara::SwitchRect ()
	{
		//static bool b1 = false;
		static bool b1 = true;
		if ( ::GetAsyncKeyState ( '1' ) & 0x0001 ) { b1 ^= true; }
		if ( b1 )
		{
			m_exeChara1->OnDispRect ();
			m_exeChara2->OnDispRect ();
		}
		else
		{
			m_exeChara1->OffDispRect ();
			m_exeChara2->OffDispRect ();
		}
	}

	//------------------------------------------------------
	//CPU操作切替
	void MutualChara::SwithcCPU ()
	{
		static bool cpu1 = F;
		static bool cpu2 = F;

		if ( ::GetAsyncKeyState ( '7' ) & 0x0001 ) 
		{
			cpu2 ^= T; 
			if ( cpu2 )
			{
				m_exeChara2->ControlCPU ();
			}
			else
			{
				m_exeChara2->ControlPlayer ();
			}
		}
	}

	//------------------------------------------------------
	//	ExeChara両者操作
	//------------------------------------------------------
	void MutualChara::SetReady ()
	{
		//準備
		m_exeChara1->SetCharaState ( CHST_START );
		m_exeChara2->SetCharaState ( CHST_START );
	}
	void MutualChara::SetMain ()
	{
		//開始
		m_exeChara1->SetMain ();
		m_exeChara2->SetMain ();
	}
	void MutualChara::Wait ( bool b )
	{
		//入力停止
		m_exeChara1->SetWait ( b );
		m_exeChara2->SetWait ( b );
	}
	void MutualChara::Stop ( bool b )
	{
		//一時停止
		m_exeChara1->SetStop ( b );
		m_exeChara2->SetStop ( b );
	}
	void MutualChara::SetEndWait ()
	{
		//終了待機
		m_exeChara1->SetEndWait ();
		m_exeChara2->SetEndWait ();
	}
	void MutualChara::EndAct ()
	{
		//終了
		m_exeChara1->OnEndAct ();
		m_exeChara2->OnEndAct ();
	}
	void MutualChara::SetCharaState ( CHARA_STATE chst )
	{
		//状態の設定
		m_exeChara1->SetCharaState ( chst );
		m_exeChara2->SetCharaState ( chst );
	}

}	//namespace GAME

