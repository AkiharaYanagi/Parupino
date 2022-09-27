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
		: m_pChara ( nullptr )
		, m_playerID ( m_playerID ), m_name ( CHARA_RAKUNO ), m_playerMode ( MODE_PLAYER )
		, m_actionID ( 0 ), m_frame ( 0 )
		, m_bDispRect ( true )
		, m_charaState ( CHST_START )
	{
		//キャラデータ生成
		m_pChara = make_shared < Chara > ();	//キャラデータ実体
		m_charaRect = make_shared < CharaRect > ();		//枠
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
		//名前からスクリプトファイルを指定してキャラのロード
		//※	D3DXのテクスチャを用いるためフォーカス変更時などに再設定(Reset())が必要
//		tstring name (_T ("testChara.dat"));
		tstring name (_T ("chara.dat"));
#if 0
		switch ( m_name )
		{
		case CHARA_RAKUNO: name.assign ( _T ( "Rakuno.dat" ) ); break;
		case CHARA_YUKINO: name.assign ( _T ( "Yukino.dat" ) ); break;
		default: break;
		}
#endif // 0
		LoadChara loadChara ( name, *m_pChara );

		//キャラ表示初期化
		m_dispChara.SetpChara ( m_pChara );
		m_dispChara.Load ();

		//キャラ入力初期化
		m_dispInput.Load ();

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

		//バトルパラメータ
		m_btlPrm.InitPlayerID ( m_playerID );
		m_btlPrm.Init ();

		//表示
		//@info Move()中のTransit()の後に遷移し、
		//		再度Move()は呼ばれずDraw()が呼ばれるため、ここで初期化が必要(Init()は呼ばれる)
		m_dispChara.UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );
		m_dispChara.InitDisp ( m_playerID );

		m_dispInput.InitDisp ( m_playerID );

		TASK_VEC::Init ();
	}

	//再設定
	void ExeChara::Reset ()
	{
		_Reset ();	//復旧時
	}

	//------------------------
	//復旧時の再設定
	void ExeChara::_Reset ()
	{
		//テクスチャメモリ確保関連は再設定
		Rele ();
		m_pChara = make_shared < Chara > ();
		Load ();
		m_dispChara.SetpChara ( m_pChara );
		m_oprtEf.SetpChara ( m_pChara );

		//アクション・スクリプト再取得
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//メイン イメージ
		m_dispChara.UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );

		//エフェクト イメージ
		m_oprtEf.PostScriptMove ( GetPos (), GetDirRight () );
	}

	//==========================================================
	//MutualCharaから呼ばれる主な関数
	//==========================================================
	//	↓ 処理順番
	//	void ExeChara::PreScriptMove ();	//	スクリプト前処理
	//	void MutualChara::Collision ();		//	相互判定 (接触枠)
	//	void ExeChara::ScriptRectMove ();	//	ぶつかり後、判定枠を設定
	//	void MutualChara::Decision ();		//	相互判定 (攻撃枠、ヒット枠)
	//	void ExeChara::PostScriptMove ();	//	スクリプト後処理

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
		//	入力など
		AlwaysMove ();

		//一時停止のときは何もしない
		if ( m_btlPrm.GetTmr_Stop()->IsActive () )
		{ return; }

		// ヒットストップ時は入力の保存と表示関連の処理をして終了
		//Activeとの兼ね合いでタイマーのラストは有効　0～N-1まで
		if ( ! m_btlPrm.GetTmr_HitStop()->IsLast () )
		{
			if ( m_btlPrm.GetTmr_HitStop ()->IsActive () ) { return; }
		}
#if 0
		if ( m_btlPrm.GetTmr_HitStop ()->IsActive () )
		{ return; }
#endif // 0


		// アクション移項
		TransitAction ();

		// 位置計算
		m_btlPrm.CalcPos ( m_pScript );

		// 着地
		Landing ();

		//接触枠設定
		AdjustCRect ();
	}


	//■###########################################################################
	//■		
	//■		両者の接触判定後に攻撃・相殺・当り判定枠を設定
	//■		
	//■###########################################################################
	void ExeChara::ScriptRectMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//一時停止のときは何もしない
		if ( m_btlPrm.GetStop () ) { return; }

		//相殺枠設定
		m_charaRect->SetORect ( m_pScript->GetpvORect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );

		//攻撃枠設定
		// ヒット時に後の攻撃枠を一時停止(多段防止)
		//攻撃成立時・打合時に同一アクション中のみ枠を消失させる
		if ( m_btlPrm.GetHitEst () || m_btlPrm.GetClang () )
		{
			m_charaRect->ResetARect ();
		}
		else
		{
			m_charaRect->SetARect ( m_pScript->GetpvARect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
		}

		//攻撃力設定
//		m_power = m_pScript->GetPower ();

		//当り枠設定
		m_charaRect->SetHRect ( m_pScript->GetpvHRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
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
		
		//1[F]に一度行う処理
		AlwaysPostMove ();

		//一時停止のときは何もしない
		if ( m_btlPrm.GetStop () ) { return; }

		//ライフ判定
		CheckLife ();

		// グラフィック
		UpdateGraphic ();
	}

	//==========================================================


	//================================================
	//	外部からの状態変更
	//================================================

	//打合発生
	void ExeChara::OnClang ( UINT nLurch, CLANG_DECISION_WL clangDecision )
	{
#if 0
//		if ( CD_LOSE == clangDecision )
		{
			//状態の変更
			m_actionID = m_pChara->GetBsAction ( BA_CLANG );
			m_frame = 0;
		}
#endif // 0
		m_btlPrm.SetClang ( true );		//打合状態
//		m_lurch = nLurch;		//のけぞり時間の設定
		m_btlPrm.GetTmr_HitStop()->Start ();		//ヒットストップの設定
	}


	//相手・攻撃 → 自分・くらい
	//くらい状態・ダメージ処理
	void ExeChara::OnDamaged ( int damage )
	{

		bool hit = true;
		bool guard = false;


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

		//ガード発生
#if 0
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
#endif // 0

		//くらい時 ( ガードをしていない ) && ( 強制変更されていない )
		if ( hit && ! m_btlPrm.GetForcedChange () )
		{
			int lf = m_btlPrm.GetLife ();
			//ダメージをライフによって補正(根性値)
			if ( lf < LIFE_MAX * 0.5f )
			{
				damage = (int)(damage * (0.001f * (0.5f * LIFE_MAX + lf )));
			}

			//ダメージ処理
			if ( lf < damage ) { m_btlPrm.SetDamage ( lf ); }	//ライフ以上は表示制限
			else { m_btlPrm.SetDamage ( damage ); }		//表示用

			m_btlPrm.SetLife ( lf - damage );

			//状態の変更
#if 0
			tstring act;
			switch ( m_pAction->GetPosture () )
			{
			case AP_STAND:	act.assign ( _T ( "Damaged_L" ) ); break;
			case AP_CROUCH: act.assign ( _T ( "C_DamagedL" ) ); break;
			case AP_JUMP:	act.assign ( _T ( "J_DamagedL" ) ); break;
			}
			TransitAction ( m_pChara->GetActionID ( act ) );
#endif // 0

			//その他　効果
			m_btlPrm.GetTmr_HitStop ()->Start ();			//ヒットストップの設定
			m_btlPrm.SetFirstEf ( true );			//初回のみエフェクト発生
			m_btlPrm.SetFirstSE ( true );			//初回のみSE発生

		}
	}

	//ヒット発生(攻撃成立側)
	//自分・攻撃 -> 相手・くらい
	void ExeChara::OnHit ()
	{
		m_btlPrm.SetHitEst ( true );		//攻撃成立フラグ

		//-----------------------------------------------------
		//条件分岐

		//投げ・自分
		UINT indexAction_i = TransitAction_Condition ( BRC_THR_I );
		if ( NO_COMPLETE != indexAction_i )
		{
			//遷移先チェック
			P_Action pact = m_pChara->GetpAction ( indexAction_i );
			P_Script pscr = pact->GetpScript ( 0 );

			m_actionID = indexAction_i;			//遷移
		}

		//投げ・相手
		UINT indexAction_e = TransitAction_Condition ( BRC_THR_E );
		if ( NO_COMPLETE != indexAction_e )
		{
			//遷移先チェック
			P_Action pact = m_pChara->GetpAction ( indexAction_e );
			P_Script pscr = pact->GetpScript ( 0 );

			m_pOther.lock ()->TransitAction ( indexAction_e );			//遷移
			m_pOther.lock ()->m_btlPrm.SetForcedChange ( true );
		}

		//ヒット・自分
		UINT indexAction_Hit_m = TransitAction_Condition ( BRC_HIT_I );
		if ( NO_COMPLETE != indexAction_Hit_m )
		{
			//遷移先チェック
			P_Action pact = m_pChara->GetpAction ( indexAction_Hit_m );
			P_Script pscr = pact->GetpScript ( 0 );

			m_actionID = indexAction_Hit_m;			//遷移
			TransitAction ( m_actionID );
		}

		//ヒット・相手
		UINT indexAction_Hit_e = TransitAction_Condition ( BRC_HIT_E );
		if ( NO_COMPLETE != indexAction_Hit_e )
		{
			//遷移先チェック
			P_Action pact = m_pChara->GetpAction ( indexAction_Hit_e );
			P_Script pscr = pact->GetpScript ( 0 );

			m_pOther.lock ()->TransitAction ( indexAction_Hit_e );			//遷移
			m_pOther.lock ()->m_btlPrm.SetForcedChange ( true );
		}
		//-----------------------------------------------------

		m_btlPrm.GetTmr_HitStop()->Start ();		//ヒットストップの設定
	}

	//エフェクトヒット発生(攻撃成立側)
	void ExeChara::OnEfHit ()
	{
		m_btlPrm.SetHitEst ( true );		//攻撃成立フラグ
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
		//ダメージ分のライフ表示減少
		int dmg = m_btlPrm.GetDamage ();
		if ( 0 < dmg ) { m_btlPrm.SetDamage ( dmg - 1 ); }

		//---------------------------------------------------
		//デモカウント
		//ダウン状態のとき
		if ( CHST_DOWN == m_charaState )
		{
			if ( ! m_btlPrm.GetTmr_Down()->IsActive () )
			{
				m_charaState = CHST_DOWN_END;
			}
		}

		//勝利待機状態のとき
		if ( CHST_WIN_WAIT == m_charaState )
		{
#if 0
			//地上ニュートラルなら
			if ( IsBasicAction ( BA_STAND ) )
			{
				//勝利状態に移行
				m_actionID = m_pChara->GetBsAction ( BA_WIN );
				TransitAction ( m_actionID );
				m_tmrEnd->Start ();
				m_charaState = CHST_WIN;
			}
#endif // 0
		}

		//勝利状態のとき
		if ( CHST_WIN == m_charaState )
		{
			//if ( ! m_tmrEnd->IsActive () )
			if ( ! m_btlPrm.GetTmr_End () ->IsActive () )
			{
				m_charaState = CHST_WIN_END;
			}
		}
		//---------------------------------------------------
		//SE
		if ( m_btlPrm.GetFirstEf () )
		{
			SOUND->Play ( SE_Hit );
			m_btlPrm.SetFirstEf ( F );
		}

		//---------------------------------------------------
		//入力
		// 入力を可能な状態
		if ( CanInput () )
		{
			//入力の保存
			m_pCharaInput->Update ( GetDirRight () );
		}
		//入力更新
		m_dispInput.UpdateInput ( m_pCharaInput );

	}


	//アクションの移項(直接指定)
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

	// アクション移項(条件:コマンド, アクション終了)
	void ExeChara::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		// のけぞり時間はコマンドによる行動不可
#if 0
		if ( LurchTimer () ) { return; }
#endif // 0

		// コマンドによる分岐
		UINT transitID = m_pCharaInput->GetTransitID ( *m_pChara, m_pScript, m_btlPrm.GetDirRight () );

		//コマンドが完成していたら
		if ( NO_COMPLETE != transitID )
		{
			//遷移先チェック
			P_Action pact = m_pChara->GetpAction ( transitID );
			P_Script pscr = pact->GetpScript ( 0 );

			m_actionID = transitID;			//遷移

			//各種状態の終了
			m_btlPrm.EndAction ();
			m_frame = 0;

			//m_frameは0から開始、Move()とDraw()で同一スクリプトを処理する
			//このフレームでスクリプトを処理するため、移行先アクションとスクリプトを保存
			m_pAction = m_pChara->GetpAction ( m_actionID );
			m_pScript = m_pAction->GetpScript ( m_frame );
		}
		//---------------------------------------------------

		//コマンドで非遷移 かつ
		else
		{
			//現在アクションが最終フレーム ならば
			if ( m_pAction->IsEndScript ( m_frame ) )
			{
				int i = 0;
			}
			
			if ( m_pAction->IsOverScript ( m_frame ) )
			{
				//実効アクションm_pActionは次フレーム時のMove()でm_actionIDを使って取得される
				m_actionID = m_pAction->GetNextID ();
				m_frame = 0;
				//今回のフレーム中はm_pActionとm_pScriptを用い、
				//これ以降はm_actionIDとm_frameを用いない

				//m_frameは0から開始、Move()とDraw()で同一スクリプトを処理する
				//このフレームでスクリプトを処理するため、移行先アクションとスクリプトを保存
				m_pAction = m_pChara->GetpAction ( m_actionID );
				m_pScript = m_pAction->GetpScript ( m_frame );
			}
			else
			{
				//m_frameは0から開始、Move()とDraw()で同一スクリプトを処理する
				//このフレームでスクリプトを処理するため、移行先アクションとスクリプトを保存
				m_pAction = m_pChara->GetpAction ( m_actionID );
				m_pScript = m_pAction->GetpScript ( m_frame );

				//通常処理：スクリプトを１つ進める
				++ m_frame;
			}
		}
		//---------------------------------------------------

		assert ( nullptr != m_pAction && nullptr != m_pScript );
	}

	//アクション移行(条件)
	UINT ExeChara::TransitAction_Condition ( BRANCH_CONDITION BRC_CND )
	{
		//キャラの持つルート,ブランチ,コマンドの参照
		const VP_Route vpRoute = m_pChara->GetvpRoute ();
		const VP_Branch vpBranch = m_pChara->GetvpBranch ();

		//スクリプトの持つルートリスト
		for ( UINT indexRut : m_pScript->GetvRouteID () )
		{
			const V_UINT vBrcID = vpRoute [ indexRut ]->GetvIDBranch ();

			//対象のブランチリスト
			for ( UINT id : vBrcID )
			{
				//条件成立
				if ( BRC_CND != vpBranch [ id ]->GetCondition () ) { continue; }

				return vpBranch [ id ]->GetIndexSequence ();
			}
		}
		return NO_COMPLETE;
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
				m_oprtEf.AddListEffect ( pEf, pEfGnrt, m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );
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
		if ( m_btlPrm.GetFirstEf () )	//ヒット後の初回のみは動作
		{
			EffectGenerate ();
			m_btlPrm.SetFirstEf ( F );
		}
		else
		{
			if ( ! m_btlPrm.GetTmr_HitStop ()->IsActive () )	//ヒットストップ時は生成しない
			{
				EffectGenerate ();
			}
		}

		//エフェクト動作
		m_oprtEf.PreScriptMove ();

		//エフェクト同期
		m_oprtEf.PostScriptMove ( m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );
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
			if ( 0 >= m_btlPrm.GetLife () )
			{
				//ダウン状態に強制変更
				//m_actionID = m_pChara->GetBsAction ( BA_DOWN );
				TransitAction ( m_actionID );
				m_btlPrm.GetTmr_Down ()->Start ();
				m_charaState = CHST_DOWN;
			}
		}
	}

	//グラフィック更新
	void ExeChara::UpdateGraphic ()
	{
		//メインイメージ
		m_dispChara.UpdateMainImage ( m_pScript, m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );

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


		//@todo 共通グラフィックの記述位置を調整
		//停止時のスキップによる

		//共通グラフィック
		if ( ! m_btlPrm.GetTmr_Stop()->IsActive () )
		{
			//暗転
			m_btlPrm.SetBlackOut ( m_pScript->GetBlackOut () );

			//スクリプトからの停止
			m_btlPrm.SetScpStop ( m_pScript->GetStop () );
		}

		//ゲージ更新
		m_dispChara.UpdateGauge ( m_playerID, m_btlPrm.GetLife (), m_btlPrm.GetDamage (), m_btlPrm.GetBalance () );

	}

	//着地
	void ExeChara::Landing ()
	{
		VEC2 pos = m_btlPrm.GetPos ();
		if ( PLAYER_BASE_Y < pos.y )
		{
			//デモ時は何もしない
			if ( IsActCtg ( AC_DEMO ) )
			{
				return;
			}

			float x = pos.x;
			float y = PLAYER_BASE_Y;
			m_btlPrm.SetPos ( VEC2 ( x, y ) );
			m_btlPrm.SetVg ( 0 );
			m_btlPrm.SetG ( 0 );

			//実効アクションm_pActionは次フレーム時のMove()でm_actionIDを使って取得される
			m_actionID = 0;	//standの指定
			m_frame = 0;
		}

		//落下
		if ( IsStand () && PLAYER_BASE_Y > m_btlPrm.GetPos ().y )
		{
			m_btlPrm.SetG ( 5 );
		}
	}


	void ExeChara::BackMoveX ()
	{
		//向きによらず、相手から離れる方向
		VEC2 iPos = m_btlPrm.GetPos ();
		VEC2 ePos = m_pOther.lock ()->GetPos ();
		bool dirBack = true;

		//同値の場合は1P2Pで選別
		if ( iPos.x == ePos.x )
		{
			dirBack = ( m_playerID == PLAYER_ID_1 );
		}
		else
		{
			//互いの位置で補正方向を決定
			dirBack = ( iPos.x < ePos.x );
		}

		float x = iPos.x + ( dirBack ? -1.f : 1.f );
		float y = iPos.y;
		m_btlPrm.SetPos ( VEC2 ( x, y ) );
	}

	void ExeChara::LookOther ()
	{
		//空中は持続
		if ( IsJump () )
		{
			return;
		}

		//位置xが同じ場合は持続
		VEC2 iPos = m_btlPrm.GetPos ();
		VEC2 ePos = m_pOther.lock ()->GetPos ();
		if ( iPos.x == ePos.x )
		{
			return;
		}

		//互いの位置で方向を決定
		m_btlPrm.SetDirRight ( iPos.x < ePos.x );
	}


	//-------------------------------------------------------------------------------------------------
	//	枠設定
	//-------------------------------------------------------------------------------------------------
	//現在位置から接触枠を反映
	void ExeChara::AdjustCRect ()
	{
		m_charaRect->SetCRect ( m_pScript->GetpvCRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
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

	void ExeChara::AlwaysPostMove ()
	{
		m_btlPrm.Move ();
	}



}	//namespace GAME

