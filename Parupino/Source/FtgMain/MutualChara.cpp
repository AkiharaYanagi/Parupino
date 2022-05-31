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

		//ヒットストップタイマー
		m_tmrHitstop = make_shared < Timer > ();
		m_tmrHitstop->SetTargetTime ( HITSTOP_TIME );
		AddpTask ( m_tmrHitstop );

		//共通エフェクト
		m_efClang = make_shared < EfClang > ();
		GRPLST_INSERT ( m_efClang );
		m_efSpark = make_shared < EfSpark > ();
		GRPLST_INSERT ( m_efSpark );
//		m_testEf = make_shared < TestEf > ();
//		GRPLST_INSERT ( m_testEf );
	}

	MutualChara::~MutualChara ()
	{
	}

	void MutualChara::ParamInit ( P_Param pParam )
	{
		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
	}

	//■#########################################################
	//■
	//■	スクリプトの毎フレーム処理
	//■
	//■#########################################################
	void MutualChara::Conduct ()
	{
		//---------------------------------------------------
		SwitchRect ();	//枠表示切替
		//---------------------------------------------------

		//スクリプト前処理(入力、移動など)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//相互判定(ぶつかり枠)
		Collision ();

		//ぶつかり後、攻撃・ヒット判定枠を設定
		m_exeChara1->ScriptRectMove ();
		m_exeChara2->ScriptRectMove ();

		//相互判定(攻撃・ヒット枠)
		Decision ();

		//スクリプト後処理(グラフィック位置など)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//グラフィック共通
		Grp ();
	}


	//■================================
	//		相互判定(ぶつかり枠)
	//■================================
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
		if ( p2x - p1x > WINDOW_WIDTH - FIELD_EDGE * 2 )
		{
			m_exeChara1->BackPtX ();	//互いに位置を戻す
			m_exeChara2->BackPtX ();
		}
	}

	//■================================
	//■		相互判定(攻撃・ヒット枠)
	//■================================
	void MutualChara::Decision ()
	{
		//------------------------------------------------------
		//ヒットストップは何もしない
		if ( m_tmrHitstop->IsActive () ) { return; }
#if 0
		//打合時は何もしない
		if ( m_exeChara1.GetClang () || m_exeChara2.GetClang () ) { return;	}
#endif // 0

		//------------------------------------------------------
		//判定用一時変数

		//判定送信用
//		CLANG_DECISION_LR sendDecision = CD_OFF; 

		//重なり中心位置
		VEC2 center = VEC2 ( 0, 0 );

		//本体相殺フラグ
		bool offset = false;

		//本体ヒットフラグ
		bool hit1P = false;
		bool hit2P = false;

		//エフェクトヒットフラグ
		bool Efhit1P = false;
		bool Efhit2P = false;

		//枠管理の取得
		P_CharaRect pCharaRect1p = m_exeChara1->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_exeChara2->GetpCharaRect ();

		//攻撃枠を取得
		PV_RECT pvARect1 = pCharaRect1p->GetpvARect ();
		PV_RECT pvARect2 = pCharaRect2p->GetpvARect ();

		//相殺枠を取得
		PV_RECT pvORect1 = pCharaRect1p->GetpvORect ();
		PV_RECT pvORect2 = pCharaRect2p->GetpvORect ();

		//当り枠を取得
		PV_RECT pvHRect1 = pCharaRect1p->GetpvHRect ();
		PV_RECT pvHRect2 = pCharaRect2p->GetpvHRect ();

		//エフェクトリストの取得
		PLP_ExEf plpExEf1 = m_exeChara1->GetplpExEf ();
		PLP_ExEf plpExEf2 = m_exeChara2->GetplpExEf ();

		//------------------------------------------------------
		//判定


		//------------------------------------------------------
		//ダッシュぶつかり判定
		//[D]:ダッシュにおける攻撃判定[A]


		//[D]-><-[D] : 特殊相殺
		bool b = DcsAtoA ( pCharaRect1p, pCharaRect2p, center );


		//[D]->[A],[D]->[O] : 通常相殺
		//[D]->[H] : 通常ヒットから互いにスクリプトでアクション移行



		//------------------------------------------------------
		//打合：攻撃判定と攻撃判定、または攻撃判定と相殺判定 (相殺と相殺は何もしない)

		//エフェクトリストの相殺チェック
		DcsOffsetEf ( plpExEf1, plpExEf2, pCharaRect2p );		//p1からp2へのチェック
		DcsOffsetEf ( plpExEf2, plpExEf1, pCharaRect1p );		//p2からp1へのチェック

		//メインキャラ同士の相殺チェック
		offset = DcsOffset ( pCharaRect1p, pCharaRect2p, center );


		//------------------------------------------------------
		//エフェクトのヒットチェック
		int powerEf1p;
		int powerEf2p;
		if ( DcsHitEf ( plpExEf1, pvHRect2, m_exeChara2, powerEf1p ) )
		{
			Efhit2P = true;	//p1からp2へのチェック
		}
		if ( DcsHitEf ( plpExEf2, pvHRect1, m_exeChara1, powerEf2p ) )
		{
			Efhit1P = true;	//p2からp1へのチェック
		}

		//メインキャラのヒットチェック
		//両者の判定を行ってから反映する(片方ずつ反映するとヒット状態を参照してしまうため)
		if ( !offset )	//相殺していないときのみ
		{	//or演算
			hit2P |= OverlapAryRect ( pvARect1, pvHRect2 );	//ヒット判定と攻撃判定(1P->2P)
			hit1P |= OverlapAryRect ( pvARect2, pvHRect1 );	//ヒット判定と攻撃判定(2P->1P)
		}

	}

	//------------------------------------------------------
	//	共通グラフィック
	//------------------------------------------------------
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
	//攻撃枠 同士判定　(中心付)
	bool MutualChara::DcsAtoA (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//攻撃枠を取得
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvARect2 = pcr2->GetpvARect ();

		//------------------------------------------------------
		//攻撃判定と攻撃判定が重なっていたらtrue
		if ( OverlapAryRect_Center (pvARect1, pvARect2, center) )
		{
			return true;
		}

		return false;
	}

	//相殺枠判定(中心付)
	bool MutualChara::DcsOffset (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//攻撃枠を取得
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvARect2 = pcr2->GetpvARect ();

		//相殺枠を取得
		PV_RECT pvORect1 = pcr1->GetpvORect ();
		PV_RECT pvORect2 = pcr2->GetpvORect ();

		//当り枠を取得
		PV_RECT pvHRect1 = pcr1->GetpvHRect ();
		PV_RECT pvHRect2 = pcr2->GetpvHRect ();

		//------------------------------------------------------
		//打合：攻撃判定と攻撃判定、または攻撃判定と相殺判定 (相殺と相殺は何もしない)
		if (OverlapAryRect_Center (pvARect1, pvARect2, center)
			|| OverlapAryRect_Center (pvORect1, pvARect2, center)
			|| OverlapAryRect_Center (pvARect1, pvORect2, center))
		{
			return true;
		}

		return false;
	}

	//エフェクトの相殺枠判定
	void MutualChara::DcsOffsetEf ( PLP_ExEf plpExEf1, PLP_ExEf plpExEf2, P_CharaRect pCharaRect2p )
	{
		VEC2 centeref = VEC2 ( 0, 0 );

		//エフェクトリストの相殺チェック
		for ( P_ExEf pexef1 : (*plpExEf1) )
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//Ef
			for ( P_ExEf pexef2 : (*plpExEf2) )
			{
				P_CharaRect pcref2 = pexef2->GetpCharaRect ();

				if ( DcsOffset ( pcref1, pcref2, centeref ) )
				{
					//相殺時 各Efに記録
					pexef1->SetOffset ( true );
				}
			}
			//Chara
			if ( DcsOffset ( pcref1, pCharaRect2p, centeref ) )
			{
				//Efに相殺状態を設定
				pexef1->SetOffset ( true );
			}
		}

	}


	//エフェクトのヒット枠判定
	bool MutualChara::DcsHitEf ( PLP_ExEf plpExEf1, PV_RECT pvHRect2, P_ExeChara pHitChara, int & refPower )
	{
		bool ret = false;
		VEC2 centeref = VEC2 ( 0, 0 );

		//エフェクトリストのヒットチェック
		for ( P_ExEf pexef1 : (*plpExEf1) )
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//相殺時は飛ばす
			if ( pexef1->GetOffset () ) { continue; }

			//枠管理の取得
			P_CharaRect pcr1pEf = pexef1->GetpCharaRect ();

			//攻撃枠を取得
			PV_RECT pvARect1 = pcr1pEf->GetpvARect ();

			//Chara
			if ( OverlapAryRect_Center ( pvARect1, pvHRect2, centeref ) )
			{
				//攻撃値を設定
				refPower = pexef1->GetpScript ()->GetPower ();

				//Efにヒット状態を設定
				pexef1->SetHit ( true );

				//Charaにヒット状態を設定
				ret = true;
			}
		}

		return ret;
	}

	//判定後にキャラに反映する
	void MutualChara::Propagate ()
	{
		//------------------------------------------------------
		//反映

		//相殺処理
		if (offset)
		{
#if 0
			//攻撃種類の取得
			Action::ACTION_CATEGORY ac1p = m_exeChara1.GetActionCategory ();
			Action::ACTION_CATEGORY ac2p = m_exeChara2.GetActionCategory ();

			//攻撃種類の組合せ
			UINT x = 0;
			switch (ac1p)
			{
			case Action::ATTACK_L: x = 0; break;
			case Action::ATTACK_M: x = 1; break;
			case Action::ATTACK_H: x = 2; break;
			default: 0; break;	//その他は"弱"扱い
			}
			UINT y = 0;
			switch (ac2p)
			{
			case Action::ATTACK_L: y = 0; break;
			case Action::ATTACK_M: y = 1; break;
			case Action::ATTACK_H: y = 2; break;
			default: 0; break;	//その他は"弱"扱い
			}
			UINT lurch1p = LURCH[x][y];
			UINT lurch2p = LURCH[y][x];


			//[縦][横]
			const UINT c_indexDecision[3][3] =
			{
				//	{弱弱, 弱中, 弱強}, 
				//	{中弱, 中中, 中強}, 
				//	{強弱, 強中, 強強}
	#if	0
					{ CD_EQUAL, CD_RIGHT, CD_RIGHT },
					{ CD_LEFT, CD_EQUAL, CD_RIGHT },
					{ CD_LEFT, CD_LEFT, CD_EQUAL }
	#endif	//0
					//弱＞強
					{ CD_EQUAL, CD_RIGHT, CD_LEFT },
					{ CD_LEFT, CD_EQUAL, CD_RIGHT },
					{ CD_RIGHT, CD_LEFT, CD_EQUAL }
			};

			//判定勝ちの方は打合のけぞりにならず、ヒットストップの後アクション続行(キャンセル可能)

			//ExeCharaに通達
			const CLANG_DECISION_WL c_decision_wl[3] = { CD_DRAW, CD_WIN, CD_LOSE };

			m_exeChara1.OnClang (lurch1p, c_decision_wl[c_indexDecision[x][y]]);
			m_exeChara2.OnClang (lurch2p, c_decision_wl[c_indexDecision[y][x]]);


			//打合結果
			const CLANG_DECISION_LR c_decision[3] = { CD_EQUAL, CD_LEFT, CD_RIGHT };

			//打合結果表示 (打合結果勝負を左右に変換)
			if (m_exeChara1.GetDirRight ())	//1Pが右向(左側：LEFT)
			{
				sendDecision = c_decision[c_indexDecision[x][y]];
			}
			else
			{
				sendDecision = c_decision[c_indexDecision[y][x]];
			}
#endif // 0

			//打合時のエフェクト発生
			m_efClang->On (center);
			m_efSpark->On (center);

			//SE
			SOUND->Play (SE_Clang);

			//ヒットストップ開始
			m_tmrHitstop->Start ();
			m_exeChara1->OnClang (0, CD_DRAW);
			m_exeChara2->OnClang (0, CD_DRAW);
		}

		//------------------------------------------------------
		//Efヒット処理
		if (Efhit2P)
		{
			m_exeChara1->OnEfHit ();		//ヒット状態
			m_exeChara2->OnDamaged (powerEf1p);		//くらい状態・ダメージ処理
		}

		if (Efhit1P)
		{
			m_exeChara2->OnEfHit ();		//ヒット状態
			m_exeChara1->OnDamaged (powerEf2p);		//くらい状態・ダメージ処理
		}

		//メインヒット処理
		if (hit2P)
		{
			int power1P = m_exeChara1->GetPower ();	//攻撃値
			m_exeChara1->OnHit ();		//ヒット状態
			m_exeChara2->OnDamaged (power1P);		//くらい状態・ダメージ処理
		}

		if (hit1P)
		{
			int power2P = m_exeChara2->GetPower ();	//攻撃値
			m_exeChara2->OnHit ();		//ヒット状態
			m_exeChara1->OnDamaged (power2P);		//くらい状態・ダメージ処理
		}
	}


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

