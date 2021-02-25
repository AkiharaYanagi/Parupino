//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//コンストラクタ
	ExeChara::ExeChara ( PLAYER_ID m_playerID )
		: m_pChara ( nullptr ), m_playerID ( m_playerID ), m_name ( CHARA_TEST )
		, m_playerMode ( MODE_PLAYER ), m_oprtEf ()
		, m_actionID ( 0 ), m_frame ( 0 )
		, m_dirRight ( true ), m_ptChara ( 0, 0 ), m_tempPt ( 0, 0 ), m_inertial ( 0, 0 )
		, m_vel ( 0, 0 ), m_acc ( 0, 0 ), m_g ( 0 ), m_vg ( 0 )
		, m_charaState ( CHST_START )
		, m_wait ( true ), m_stop ( false ), m_FirstEf ( false ), m_FirstSE ( false )
		, m_life ( 0 ), m_balance ( 0 ), m_damage ( 0 ), m_power ( 0 )
		, m_hitEst ( false ), m_clang ( false ), m_transit ( false )
		, m_bDispRect ( true )
//		, m_lurch ( 0 ), m_lurchTimer ( 0 )
	{
		//ポインタ生成
		m_pChara = make_shared < Chara > ();	//キャラデータ実体
		m_charaRect = make_shared < CharaRect > ();		//枠

		//タイマーの初期化
		m_tmrHitstop = make_shared < Timer > ();
		m_tmrHitstop->SetTargetTime ( HITSTOP_TIME );
		AddpTask ( m_tmrHitstop );

		//ダウンタイマー
		m_tmrDown = make_shared < Timer > ();
		m_tmrDown->SetTargetTime ( DOWN_TIME );
		AddpTask ( m_tmrDown );

		//終了状態タイマー
		m_tmrEnd = make_shared < Timer > ();
		m_tmrEnd->SetTargetTime ( END_TIME );
		AddpTask ( m_tmrEnd );
	}

	//デストラクタ
	ExeChara::~ExeChara ()
	{
	}

	//------------------------
	//シーンパラメータ関連初期化
	void ExeChara::ParamInit ( P_Param pParam )
	{
		//選択キャラ
		m_name = pParam->GetCharaName ( m_playerID );

		//入力モード
		m_playerMode = pParam->GetMode ( m_playerID );
		switch ( m_playerMode )
		{
		case MODE_PLAYER: m_pCharaInput = make_shared < PlayerInput > (); break;
		case MODE_CPU: m_pCharaInput = make_shared < CPUInput > ( shared_from_this (), m_pOther ); break;
		case MODE_NETWORK: m_pCharaInput = make_shared < PlayerInput > (); break;
		default: break;
		}
		m_pCharaInput->SetPlayer ( m_playerID );
	}

	//------------------------
	//読込
	void ExeChara::Load ()
	{
		//スクリプトファイルからキャラのロード
		//※	D3DXのテクスチャを用いるためフォーカス変更時などに再設定が必要
		tstring name ( _T ( "testChara.dat" ) );

		//tstring&のためassignで指定する
		switch ( m_name )
		{
		case CHARA_TEST: name.assign ( _T ( "testChara.dat" ) ); break;
#if 0

		case CHARA_RAKUNO: name.assign ( _T ( "Rakuno.dat" ) ); break;
		case CHARA_YUKINO: name.assign ( _T ( "Yukino.dat" ) ); break;
#endif // 0
		default: break;
		}
		LoadChara loadChara ( name, *m_pChara );

		//基本状態アクションIDを手動で設定する
#if 0
		<STAND ID = "0" Name = "Stand">< / STAND>
		<POISED ID = "25" Name = "S_Guard">< / POISED>
		<CLANG ID = "29" Name = "Clang">< / CLANG>
		<AVOID ID = "30" Name = "Avoid">< / AVOID>
		<DOTTY ID = "31" Name = "Dotty">< / DOTTY>
		<DAMAGED ID = "32" Name = "DamagedL">< / DAMAGED>
		<DOWN ID = "39" Name = "Lose">< / DOWN>
		<WIN ID = "41" Name = "Win">< / WIN>
#endif // 0
		m_pChara->SetBsAction ( BA_STAND, 0 );
		m_pChara->SetBsAction ( BA_POISED, 25 );
		m_pChara->SetBsAction ( BA_CLANG, 29 );
		m_pChara->SetBsAction ( BA_AVOID, 30 );
		m_pChara->SetBsAction ( BA_DOTTY, 31 );
		m_pChara->SetBsAction ( BA_DAMAGED, 32 );
		m_pChara->SetBsAction ( BA_DOWN, 39 );
		m_pChara->SetBsAction ( BA_WIN, 41 );


		//キャラ表示初期化
		m_dispChara.SetpChara ( m_pChara );
		m_dispChara.Load ();

		//エフェクト生成ベクタの生成
		MakeEfOprt ();

		TASK_VEC::Load ();
	}

	//------------------------
	//初期化(複数回実行可能)
	void ExeChara::Init ()
	{
		//アクション・スクリプト初期化
		m_actionID = 0;
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_frame = 0;
		m_pScript = m_pAction->GetpScript ( m_frame );

		//初期位置
		if ( PLAYER_ID_1 == m_playerID )
		{
			m_ptChara = VEC2 ( PLAYER_1_BASE_X, PLAYER_1_BASE_Y );
			m_dirRight = true;
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			m_ptChara = VEC2 ( PLAYER_2_BASE_X, PLAYER_2_BASE_Y );
			m_dirRight = false;
		}

		//ゲームパラメータ
		m_life = LIFE_MAX;
		m_damage = 0;
		m_power = 0;
		m_hitEst = false;
		m_FirstEf = false;
		m_FirstSE = false;
		m_charaState = CHST_START;

		EndAction ();

		//タイマー
		m_tmrEnd->Reset ();
		m_tmrHitstop->Reset ();

		//表示
		//@info Move()中のTransit()の後に遷移し、
		//		再度Move()は呼ばれずDraw()が呼ばれるため、ここで初期化が必要(Init()は呼ばれる)
		m_dispChara.UpdateMainImage ( m_pScript, m_ptChara, m_dirRight );
		m_dispChara.InitDisp ( m_playerID );

		TASK_VEC::Init ();
	}


	//------------------------
	//解放
	void ExeChara::Rele ()
	{
		m_pChara.reset ();
		TASK_VEC::Rele ();
	}

	//------------------------
	//再設定
	void ExeChara::Reset ()
	{
		Rele ();
		m_pChara = make_shared < Chara > ();
		Load ();
		m_dispChara.SetpChara ( m_pChara );
		m_oprtEf.SetpChara ( m_pChara );
		Resume ();	//復旧時
	}

	//------------------------
	//復旧時の再設定
	void ExeChara::Resume ()
	{
		//アクション・スクリプト再取得
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//メイン イメージ
		m_dispChara.UpdateMainImage ( m_pScript, m_ptChara, m_dirRight );

		//エフェクト イメージ
		m_oprtEf.PostScriptMove ( m_ptChara, m_dirRight );
	}


	//■#########################################################
	//■
	//■		毎フレーム スクリプト前処理
	//■			位置や枠の設定
	//■
	//■#########################################################
	void ExeChara::PreScriptMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		// アクションとスクリプトによらない一定の処理
		AlwaysMove ();

		if ( m_stop ) { return; }		//一時停止のときは何もしない

		// ヒットストップ時は入力の保存と表示関連の処理をして終了
		//Activeとの兼ね合いでタイマーのラストは有効　0～N-1まで
		if ( ! m_tmrHitstop->IsLast () )
		{
			if ( m_tmrHitstop->IsActive () ) { return; }
		}

		// アクション移項
		TransitAction ();

		// 位置計算
		CalcPos ();

		//接触枠設定
		AdjustCRect ();
	}


	//■###########################################################################
	//■
	//■		毎フレーム スクリプト後処理
	//■			自分・相手のスクリプト前処理→相互の判定、の後にそれぞれの処理をする
	//■			判定の結果表示(主にグラフィック関連)
	//■
	//■###########################################################################
	void ExeChara::PostScriptMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );
		if ( m_stop ) { return; }		//一時停止のときは何もしない

		//ライフ判定
		CheckLife ();

		// グラフィック
		UpdateGraphic ();
	}


	//================================================
	//	外部からの状態変更
	//================================================

	//打合発生
	void ExeChara::OnClang ( UINT nLurch, CLANG_DECISION_WL clangDecision )
	{
//		if ( CD_LOSE == clangDecision )
		{
			//状態の変更
			m_actionID = m_pChara->GetBsAction ( BA_CLANG );
			m_frame = 0;
		}
		m_clang = true;		//打合状態
//		m_lurch = nLurch;		//のけぞり時間の設定
		m_tmrHitstop->Start ();		//ヒットストップの設定
	}


	//ヒット発生
	void ExeChara::OnDamaged ( int damage )
	{
		//回避判定
#if 0
		//攻撃中でなく、下要素が入力されているとき
		//ダッシュ中、よろけ中なども除外する (歩きは可能)
		if ( !IsAttacking () && !(GetActionName () == Chara::DOTTY) )
		{
			if ( IsInput2E () )
			{
				//避けに移項
				TransitAction ( m_pChara->GetBsAction ( Chara::AVOID ) );

				//ヒットストップの設定
				m_hitstop = 15;

				//エフェクトの発生
//				float dispGameBaseX = GetDispGameBaseX ();	//画面端による表示基準位置
				m_dispChara.OnAvoid ( m_ptChara, m_dirRight );

				//SE
				SoundArchiver::instance ()->Play ( 2 );

				//自分のバランス減少・追加分
				int balanceDamage0 = 200 - damage;		//ダメージの逆数(L>M>H)
				if ( m_balance < balanceDamage0 ) { balanceDamage0 = m_balance; }	//現在値以上は表示制限
				m_balance -= balanceDamage0;

				//相手のバランス減少
				int balanceDamage = damage;		//ダメージ分バランス減少(L<M<H)
				int balance = m_pOther->GetBalance ();
				if ( balance < balanceDamage ) { balanceDamage = balance; }	//現在値以上は表示制限
				m_pOther->AddbBalance ( -1 * balanceDamage );

				return;
			}
		}
#endif // 0

		bool hit = true;
		bool guard = false;

		//ガード発生
		//攻撃中でないとき
		//ダッシュ中、よろけ中なども除外する (歩きは可能)
		if ( !IsAttacking () && !IsDamaged () )
		{
			//上中下段　分岐処理
			ACTION_POSTURE ap = m_pOther.lock ()->GetPosture ();

			//後方向が入力されているとき
			if ( m_pCharaInput->IsInput4 () )
			{
				//相手の状態で分岐
				switch ( ap )
				{
				case AP_STAND:	hit = false; guard = true; break;
				case AP_CROUCH: hit = true; guard = false; break;
				case AP_JUMP:	hit = false; guard = true; break;
				}
			}

			//後下方向が入力されているとき
			if ( m_pCharaInput->IsInput1 () )
			{
				//相手の状態で分岐
				switch ( ap )
				{
				case AP_STAND:	hit = false; guard = true; break;
				case AP_CROUCH: hit = false; guard = true; break;
				case AP_JUMP:	hit = true; guard = false; break;
				}
			}

		}

		//--------------------------------------------------------

		//ガード成立
		if ( guard )
		{
			tstring act;
			switch ( m_pAction->GetPosture () )
			{
			case AP_STAND:	act.assign ( _T ( "S_Guard" ) ); break;
			case AP_CROUCH: act.assign ( _T ( "C_Guard" ) ); break;
			case AP_JUMP:	act.assign ( _T ( "J_Guard" ) ); break;
			}
			TransitAction ( m_pChara->GetActionID ( act ) );

			m_FirstEf = true;				//初回のみエフェクト発生
			m_tmrHitstop->Start ();				//ヒットストップの設定

			//SE
			SOUND->Play ( SE_Guard );
		}

		//ヒット時
		if ( hit )
		{
			//ダメージをライフによって補正(根性値)
			if ( m_life < LIFE_MAX * 0.5f )
			{
				damage = (int)(damage * (0.001f * (0.5f * LIFE_MAX + m_life)));
			}

			//ダメージ処理
			if ( m_life < damage ) { m_damage = m_life; }	//ライフ以上は表示制限
			else { m_damage = damage; }		//表示用
			m_life -= damage;

			//状態の変更
			tstring act;
			switch ( m_pAction->GetPosture () )
			{
			case AP_STAND:	act.assign ( _T ( "DamagedL" ) ); break;
			case AP_CROUCH: act.assign ( _T ( "C_DamagedL" ) ); break;
			case AP_JUMP:	act.assign ( _T ( "J_DamagedL" ) ); break;
			}
			TransitAction ( m_pChara->GetActionID ( act ) );

			m_tmrHitstop->Start ();			//ヒットストップの設定
			m_FirstEf = true;			//初回のみエフェクト発生
			m_FirstSE = true;			//初回のみSE発生

		}
	}

	//ヒット発生(攻撃成立側)
	void ExeChara::OnHit ()
	{
		m_hitEst = true;		//攻撃成立フラグ
		m_tmrHitstop->Start ();		//ヒットストップの設定
	}

	//エフェクトヒット発生(攻撃成立側)
	void ExeChara::OnEfHit ()
	{
		m_hitEst = true;		//攻撃成立フラグ
//		m_tmrHitstop->Start ();		//エフェクトはヒットストップしない
	}

	//終了演出
	void ExeChara::OnEndAct ()
	{
		m_charaState = CHST_WIN_WAIT;
	}


	//================================================
	//	内部関数
	//================================================

	// アクションとスクリプトによらない一定の処理
	void ExeChara::AlwaysMove ()
	{
		//ダメージ表示減少
		if ( 0 < m_damage ) { --m_damage; }

		//---------------------------------------------------
		//デモカウント
		//ダウン状態のとき
		if ( CHST_DOWN == m_charaState )
		{
			if ( ! m_tmrDown->IsActive () )
			{
				m_charaState = CHST_DOWN_END;
			}
		}

		//勝利待機状態のとき
		if ( CHST_WIN_WAIT == m_charaState )
		{
			//地上ニュートラルなら
			if ( IsBasicAction ( BA_STAND ) )
			{
				//勝利状態に移行
				m_actionID = m_pChara->GetBsAction ( BA_WIN );
				TransitAction ( m_actionID );
				m_tmrEnd->Start ();
				m_charaState = CHST_WIN;
			}
		}

		//勝利状態のとき
		if ( CHST_WIN == m_charaState )
		{
			if ( ! m_tmrEnd->IsActive () )
			{
				m_charaState = CHST_WIN_END;
			}
		}
		//---------------------------------------------------
		//SE
		if ( m_FirstSE )
		{
			SOUND->Play ( SE_Hit );
			m_FirstSE = false;
		}

		//---------------------------------------------------
		// 入力を可能な状態
		if ( CanInput () )
		{
			//入力の保存
			m_pCharaInput->Update ( m_dirRight );
		}
	}


	//アクションの移項
	void ExeChara::TransitAction ( UINT actionID )
	{
		//遷移先チェック
		P_Action pact = m_pChara->GetpAction( actionID );
		P_Script pscr = pact->GetpScript ( 0 );

		m_actionID = actionID;		//遷移
		m_frame = 0;		//スクリプト初期化

		//一時アクションとスクリプトを再設定
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );
	}

	// アクション移項
	void ExeChara::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		// のけぞり時間はコマンドによる行動不可
#if 0
		if ( LurchTimer () ) { return; }
#endif // 0

		// コマンドによる分岐
		PVP_Branch pvpBranch = m_pScript->GetpvpBranch ();
		UINT transitID = m_pCharaInput->GetTransitID ( pvpBranch, m_dirRight );

		//コマンドが完成していたら
		if ( NO_COMPLETE != transitID )
		{
			//遷移先チェック
			P_Action pact = m_pChara->GetpAction ( transitID );
			P_Script pscr = pact->GetpScript ( 0 );

			m_actionID = transitID;			//遷移

			//各種状態の終了
			EndAction ();
		}

		//---------------------------------------------------
		//遷移時に各種状態の終了
		if ( 0 == m_frame )
		{
			//各種状態の終了
			EndAction ();
		}

		//0から開始、Move()とDraw()で同一スクリプトを処理する
		//このフレームでスクリプトを処理するため、移行先アクションとスクリプトを保存
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//現在アクションが最終フレームならば
		if ( m_pAction->IsEndScript ( m_frame ) )
		{
			//実効アクションm_pActionは次フレーム時のMove()でm_actionIDを使って取得される
			m_actionID = m_pAction->GetNextID ();
			m_frame = 0;
			//今回のフレーム中はm_pActionとm_pScriptを用い、
			//これ以降はm_actionIDとm_frameを用いない
		}
		else
		{
			++m_frame;
		}

		assert ( nullptr != m_pAction && nullptr != m_pScript );
	}

	//エフェクト処理の生成
	void ExeChara::MakeEfOprt ()
	{
		//エフェクト処理にキャラポインタを設定
		m_oprtEf.SetpChara ( m_pChara );

		//すべてのアクションとスクリプトを巡回
		PVP_Action pvpAction = m_pChara->GetpvpAction ();
		for ( P_Action pAction : (* pvpAction) )
		{
			PVP_Script pvpScript = pAction->GetpvpScript ();
			for ( P_Script pScript : (* pvpScript ) )
			{
				PVP_EfGnrt pvpEfGnrt = pScript->GetpvpEfGnrt ();
				for ( P_EfGnrt pEfGnrt : (* pvpEfGnrt) )
				{
					//非生成なら初回に登録しておき、IDで稼働状態にする
					if ( ! pEfGnrt->GetGnrt () )
					{
						//エフェクトインデックスの取得
						UINT index = pEfGnrt->GetIndex ();

						//エフェクトの取得
						P_Effect pEf = m_pChara->GetpEffect ( index );
						
						//エフェクト管理に渡してIDを得る
//						UINT id = m_oprtEf.AddVectorEffect ( pEf, pEfGnrt->GetZ () );
						
						//IDを記録
//						pEfGnrt->SetID ( id );
					}
				}
			}
		}
	}

	//エフェクト生成
	void ExeChara::EffectGenerate ()
	{
		//発生
		PVP_EfGnrt  pvpEfGnrt = m_pScript->GetpvpEfGnrt ();
		for ( P_EfGnrt pEfGnrt : (*pvpEfGnrt) )
		{
			//生成用なら
			if ( pEfGnrt->GetGnrt () )
			{
				//エフェクトインデックスの取得
				UINT index = pEfGnrt->GetIndex ();
				//エフェクトの取得
				P_Effect pEf = m_pChara->GetpEffect ( index );
				//リストに追加
				m_oprtEf.AddListEffect ( pEf, pEfGnrt, m_ptChara, m_dirRight );
			}
			else //再利用なら
			{
				int i = 0;
#if false


				//エフェクトインデックスの取得
				UINT index = pEfGnrt->GetIndex ();
				//エフェクトの取得
				P_Effect pEf = m_pChara->GetpEffect ( index );
				//稼働中かどうか
				if ( !m_oprtEf.IsActive ( pEf ) )
				{
					m_oprtEf.DriveEffect ( pEf );
				}
#endif // false
			}
		}
	}

	void ExeChara::EffectMove ()
	{
		//エフェクト生成と動作
		if ( m_FirstEf )	//ヒット後の初回のみは動作
		{
			EffectGenerate ();
			m_FirstEf = false;
		}
		else
		{
			if ( !m_tmrHitstop->IsActive () )	//ヒットストップ時は生成しない
			{
				EffectGenerate ();
			}
		}

		//エフェクト動作
		m_oprtEf.PreScriptMove ();

		//エフェクト同期
		m_oprtEf.PostScriptMove ( m_ptChara, m_dirRight );
	}

	//枠表示切替
	void ExeChara::TurnDispRect ()
	{
		if ( m_bDispRect )
		{
			m_dispChara.OnRect ();
			m_dispChara.SetpCharaRect ( m_charaRect );
			m_oprtEf.OnDispRect ();
		}
		else
		{
			m_dispChara.OffRect ();
			m_oprtEf.OffDispRect ();
		}
	}

	//ライフ判定
	void ExeChara::CheckLife ()
	{
		//メイン状態のとき
		if ( IsMain () )
		{
			//自分がライフ０
			if ( 0 >= m_life )
			{
				//ダウン状態に強制変更
				m_actionID = m_pChara->GetBsAction ( BA_DOWN );
				TransitAction ( m_actionID );
				m_tmrDown->Start ();
				m_charaState = CHST_DOWN;
			}
		}
	}

	//グラフィック更新
	void ExeChara::UpdateGraphic ()
	{
		//メインイメージ
		m_dispChara.UpdateMainImage ( m_pScript, m_ptChara, m_dirRight );

		//エフェクト生成と動作
		EffectMove ();

		//枠表示切替
		TurnDispRect ();

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

		//ゲージ更新
		m_dispChara.UpdateGauge ( m_playerID, m_life, m_damage, m_balance );
	}


	//------------------------------------------------
	//位置計算
	void ExeChara::CalcPos ()
	{
		//------------------------
		// 位置 (xのみ向きを乗算)
		m_tempPt = m_ptChara;		//一時保存
		float dir = m_dirRight ? 1.f: -1.f;		//向き

		//------------------------
		// 慣性
#if 0
		//攻撃(スクリプト遷移)時、現在の慣性を反映する
		//加速度(慣性)
		if ( m_transit )
		{
			m_inertial = m_pScript->GetAcc ();
			float dir = m_dirRight ? 1.f : -1.f;
			m_ptChara += dir * m_inertial;
		}

		// 慣性の減少
		if ( m_inertial.x > 0 )
		{
			m_inertial.x -= 0.3f;
			if ( m_inertial.x < 0 ) { m_inertial.x = 0; }
		}
		else
		{
			m_inertial.x += 0.3f;
			if ( m_inertial.x > 0 ) { m_inertial.x = 0; }
		}

		if ( m_inertial.y > 0 )
		{
			m_inertial.y -= 0.3f;
			if ( m_inertial.y < 0 ) { m_inertial.y = 0; }
		}
		else
		{
			m_inertial.y += 0.3f;
			if ( m_inertial.y > 0 ) { m_inertial.y = 0; }
		}
#endif // 0

		//計算種類で分岐
		CLC_ST clcSt = m_pScript->GetCalcState ();
		switch ( clcSt )
		{
		case CLC_MAINTAIN: 	//持続

			m_vel.x += m_acc.x;		//加速度
			m_ptChara.x += dir * m_vel.x;		//速度
			m_ptChara.x += dir * m_inertial.x;		//慣性

			m_vel.y += m_acc.y;		//加速度
			m_ptChara.y += m_vel.y;		//速度
			m_ptChara.y += m_inertial.y;		//慣性

		break;

		case CLC_SUBSTITUDE:	//代入

			m_vel.x = m_pScript->GetVel ().x;
			m_acc.x = m_pScript->GetAcc ().x;
			m_ptChara.x += dir * m_vel.x;		//速度
			m_ptChara.x += dir * m_inertial.x;		//慣性

			m_vg += m_g;
			m_vel.y = m_pScript->GetVel ().y + m_vg;
			m_acc.y = m_pScript->GetAcc ().y;
			m_ptChara.y += m_vel.y;		//速度
			m_ptChara.y += m_inertial.y;		//慣性

		break;
		
		case CLC_ADD:	//加算

			m_vel.x += m_pScript->GetVel ().x;
			m_acc.x += m_pScript->GetAcc ().x;
			m_ptChara.x += dir * m_vel.x;		//速度
			m_ptChara.x += dir * m_inertial.x;		//慣性

			m_vel.y += m_pScript->GetVel ().y;
			m_acc.y += m_pScript->GetAcc ().y;
			m_ptChara.y += m_vel.y;		//速度
			m_ptChara.y += m_inertial.y;		//慣性

		break;
		
		default: break;
		}

		//---------------
		//着地
		if ( PLAYER_BASE_Y < m_ptChara.y )
		{
			//デモ時は何もしない
			if ( IsActCtg ( AC_DEMO ) ) 
			{ return; }

			m_ptChara.y = PLAYER_BASE_Y; 
			m_vg = 0;
			m_g = 0;

			//実効アクションm_pActionは次フレーム時のMove()でm_actionIDを使って取得される
			m_actionID = 0;	//standの指定
			m_frame = 0;
		}

		//落下
		if ( IsStand () && PLAYER_BASE_Y > m_ptChara.y )
		{
			m_g = 5;
		}

		//---------------
		//画面端
		if ( m_ptChara.x < FIELD_BASE_X + FIELD_EDGE ) { m_ptChara.x = FIELD_BASE_X + FIELD_EDGE; }
		if ( m_ptChara.x > FIELD_WIDTH - FIELD_EDGE ) { m_ptChara.x = FIELD_WIDTH - FIELD_EDGE; }
	}

	void ExeChara::BackMoveX ()
	{
		//向きによらず、相手から離れる方向
		VEC2 otherPos = m_pOther.lock ()->GetPos ();
		bool dirBack = true;

		//同値の場合は1P2Pで選別
		if ( m_ptChara.x == otherPos.x )
		{
			dirBack = (m_playerID == PLAYER_ID_1);
		}
		else
		{
			//互いの位置で補正方向を決定
			dirBack = (m_ptChara.x < otherPos.x);
		}

		m_ptChara.x += dirBack ? -1.f : 1.f;
	}

	void ExeChara::LookOther ()
	{
		//空中は持続
		if ( IsJump () ) { return; }

		//位置xが同じ場合は持続
		VEC2 otherPos = m_pOther.lock ()->GetPos ();
		if ( m_ptChara.x == otherPos.x ) { return; }

		//互いの位置で方向を決定
		m_dirRight = (m_ptChara.x < otherPos.x);
	}

	//-------------------------------------------------------------------------------------------------
	//	枠設定
	//-------------------------------------------------------------------------------------------------
	//現在位置から接触枠を反映
	void ExeChara::AdjustCRect ()
	{
		m_charaRect->SetCRect ( m_pScript->GetpvCRect (), m_dirRight, m_ptChara );
	}

	//両者の接触判定後に攻撃・相殺・当り判定枠を設定
	void ExeChara::ScriptRectMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );
		if ( m_stop ) { return; }		//一時停止のときは何もしない

		//相殺枠設定
		m_charaRect->SetORect ( m_pScript->GetpvORect (), m_dirRight, m_ptChara );

		//攻撃枠設定
		// ヒット時に後の攻撃枠を一時停止(多段防止)
		//攻撃成立時・打合時に同一アクション中のみ枠を消失させる
		if ( m_hitEst || m_clang )
		{
			m_charaRect->ResetARect ();
		}
		else
		{
			m_charaRect->SetARect ( m_pScript->GetpvARect (), m_dirRight, m_ptChara );
		}

		//攻撃力設定
		m_power = m_pScript->GetPower ();

		//当り枠設定
		m_charaRect->SetHRect ( m_pScript->GetpvHRect (), m_dirRight, m_ptChara );
	}

	//------------------------------------------------
	//アクション終了処理
	void ExeChara::EndAction ()
	{
		m_frame = 0;				//フレーム初期化
		m_clang = false;
		m_hitEst = false;
		m_FirstEf = false;
//		m_lurch = 0;
//		m_lurchTimer = 0;
	}

	void ExeChara::SetEndWait ()
	{
		//ダウン優先
		if ( IsDown () ) { return; }

		m_charaState = CHST_END_WAIT;
	}


	//のけぞりタイマー
#if 0
	bool ExeChara::LurchTimer ()
	{
		// のけぞり時間はコマンドによる行動不可
		if ( 0 < m_lurch )
		{
			if ( m_lurchTimer == m_lurch )	//のけぞり終了
			{
				m_lurch = 0;
				m_lurchTimer = 0;
			}
			else
			{
				++m_lurchTimer;
				return true;
			}
		}
		return false;
	}
#endif // 0

	//入力をする状態かどうか
	bool ExeChara::CanInput () const
	{
		return IsMain ();
	}

	bool ExeChara::IsMain () const
	{
		switch ( m_charaState )
		{
		case CHST_MAIN: return true;  break;

		case CHST_START:
		case CHST_DOWN:
		case CHST_WIN:
		case CHST_END_WAIT:
		case CHST_WIN_END:
			return false; break;
		}
		return false;
	}


}	//namespace GAME

