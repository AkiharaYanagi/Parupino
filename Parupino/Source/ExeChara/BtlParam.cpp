//=================================================================================================
//
//	バトルパラメータ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "BtlParam.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	BtlParam::BtlParam ()
		: m_dirRight ( true ), m_posChara ( 0, 0 ), m_tempPt ( 0, 0 ), m_inertial ( 0, 0 ), m_dashInertial ( 0, 0 )
		, m_vel ( 0, 0 ), m_acc ( 0, 0 ), m_g ( 0 ), m_vg ( 0 )
		, m_wait ( true ), m_stop ( false ), m_FirstEf ( false ), m_FirstSE ( false )
		, m_life ( 0 ), m_balance ( 0 ), m_mana ( 0 )
		, m_power ( 0 )
		, m_hitEst ( false ), m_clang ( false ), m_transit ( false )
		, m_ForcedChange ( false )
		//		, m_lurch ( 0 ), m_lurchTimer ( 0 )
		, m_blackOut ( 0 ), m_scpStop ( 0 )
		, m_hitNum ( 0 )
		, m_nActTransit ( 0 )
	{
		LoadTimer ();
	}


	//コピーコンストラクタ
	BtlParam::BtlParam ( const BtlParam & rhs )
	{
		m_posChara = rhs.m_posChara;		//キャラ位置
		m_tempPt = rhs.m_tempPt;			//一時保存
		m_dirRight = rhs.m_dirRight;		//向き(右：正, 左：逆)
		m_inertial = rhs.m_inertial;		//慣性
		m_dashInertial = rhs.m_dashInertial;	//ダッシュ慣性
		m_vel = rhs.m_vel;			//速度
		m_acc = rhs.m_acc;			//加速度
		m_g = rhs.m_g;				//重力
		m_vg = rhs.m_vg;			//重力(計算用)

		m_life = rhs.m_life;		//ライフ
		m_balance = rhs.m_balance;	//バランス
		m_mana = rhs.m_mana;		//マナ

		m_power = rhs.m_power;			//実効攻撃値
		m_damaged = rhs.m_damaged;		//くらいフラグ
		m_hitEst = rhs.m_hitEst;		//攻撃成立フラグ
		m_FirstEf = rhs.m_FirstEf;		//初回Efフラグ
		m_FirstSE = rhs.m_FirstSE;		//初回SEフラグ
		m_ForcedChange = rhs.m_ForcedChange;	//強制変更
		m_clang = rhs.m_clang;			//打合発生フラグ
		m_transit = rhs.m_transit;		//スクリプト遷移したフレーム

//		m_lurch;		//のけぞり(キャンセル不可)時間追加
//		m_lurchTimer;

		m_wait = rhs.m_wait;			//入力を一時停止
		m_stop = rhs.m_stop;			//入力、スクリプト処理を一時停止

		//タイマはコピーしない
		LoadTimer ();

		m_blackOut = rhs.m_blackOut;		//暗転
		m_scpStop = rhs.m_scpStop;		//スクリプトからの停止

		m_nActTransit = rhs.m_nActTransit;		//アクション移行回数
	}

	BtlParam::~BtlParam ()
	{
	}


	void BtlParam::LoadPlayerID ( PLAYER_ID playerID )
	{
		m_playerID = playerID;
		PosInit ();
	}

	void BtlParam::LoadTimer ()
	{
		//タイマの初期化
		m_tmrHitstop = make_shared < Timer > ( HITSTOP_TIME );		//ヒットストップ
		m_tmrDown = make_shared < Timer > ( DOWN_TIME );		//ダウンタイマ
		m_tmrEnd = make_shared < Timer > ( END_TIME );		//終了状態タイマ
		m_tmrStop = make_shared < Timer > ();		//ストップタイマ
		m_tmrHitPitch = make_shared < Timer > ();		//ヒット間隔タイマ

		m_timers.push_back ( m_tmrHitstop );
		m_timers.push_back ( m_tmrDown );
		m_timers.push_back ( m_tmrEnd );
		m_timers.push_back ( m_tmrStop );
		m_timers.push_back ( m_tmrHitPitch );
	}

	void BtlParam::PosInit ()
	{
		//初期位置
		if ( PLAYER_ID_1 == m_playerID )
		{
			m_posChara = VEC2 ( PLAYER_1_BASE_X, PLAYER_1_BASE_Y );
			m_dirRight = true;
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			m_posChara = VEC2 ( PLAYER_2_BASE_X, PLAYER_2_BASE_Y );
			m_dirRight = false;
		}
	}

	void BtlParam::Init ()
	{
		//ゲームパラメータ
		m_life = LIFE_START;
		m_balance = BALANCE_START;
		m_mana = MANA_START;

		m_power = 0;

		m_hitEst = false;
		m_FirstEf = false;
		m_FirstSE = false;

		m_inertial = VEC2 ( 0, 0 );
		m_dashInertial = VEC2 ( 0, 0 );
		m_vel = VEC2 ( 0, 0 );
		m_acc = VEC2 ( 0, 0 );

		EndAction ();

		PosInit ();

		m_wait = false;
		m_stop = false;

		//タイマー
		for ( P_Timer ptmr : m_timers )
		{
			ptmr->Reset ();
		}
	}

	void BtlParam::TimerMove ()
	{
		for ( P_Timer ptmr : m_timers )
		{
			ptmr->Move ();
		}
	}

	//------------------------------------------------
	void BtlParam::TrainingInit ()
	{
		Init ();
		m_mana = MANA_MAX;
	}



	//------------------------------------------------
	void BtlParam::EndAction ()
	{
		m_clang = false;
		m_hitEst = false;
		m_FirstEf = false;
		m_ForcedChange = false;
		//		m_lurch = 0;
		//		m_lurchTimer = 0;
		m_tmrHitPitch->Reset ();			//ヒット間隔タイマ
		m_hitNum = 0;
	}

	//------------------------------------------------
	//位置計算
	void BtlParam::CalcPos ( P_Script pScp )
	{
		//------------------------
		// 位置 (xのみ向きを乗算)
		m_tempPt = GetPos ();		//一時保存
		float dir = GetDirRight () ? 1.f : -1.f;		//向き

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

		//ダッシュ慣性
		DecreaseInertial ( 0.5f, m_dashInertial );
		m_posChara += m_dashInertial* dir;

		//スクリプト値
		VEC2 vel = pScp->m_prmBattle.Vel;
		VEC2 acc = pScp->m_prmBattle.Acc;

		//計算種類で分岐
		CLC_ST clcSt = pScp->m_prmBattle.CalcState;
		switch ( clcSt )
		{
		case CLC_MAINTAIN: 	//持続
			m_acc = acc;

			m_vel.x += m_acc.x;		//加速度
			m_posChara.x += dir * m_vel.x;		//速度
			m_posChara.x += dir * m_inertial.x;		//慣性

			m_vel.y += m_acc.y;		//加速度
			m_posChara.y += m_vel.y;		//速度
			m_posChara.y += m_inertial.y;		//慣性

			break;

		case CLC_SUBSTITUDE:	//代入

			m_vel.x = vel.x;
			m_acc.x = acc.x;
			m_posChara.x += dir * m_vel.x;		//速度
			m_posChara.x += dir * m_inertial.x;		//慣性

			m_vg += m_g;
			m_vel.y = vel.y + m_vg;
			m_acc.y = acc.y;
			m_posChara.y += m_vel.y;		//速度
			m_posChara.y += m_inertial.y;		//慣性

			break;

		case CLC_ADD:	//加算

			m_vel.x += vel.x;
			m_acc.x += acc.x;
			m_posChara.x += dir * m_vel.x;		//速度
			m_posChara.x += dir * m_inertial.x;		//慣性

			m_vel.y += vel.y;
			m_acc.y += acc.y;
			m_posChara.y += m_vel.y;		//速度
			m_posChara.y += m_inertial.y;		//慣性

			break;

		default: break;
		}

		//---------------
		//画面端
		if ( m_posChara.x < FIELD_BASE_X + FIELD_EDGE ) { m_posChara.x = FIELD_BASE_X + FIELD_EDGE; }
		if ( m_posChara.x > FIELD_WIDTH - FIELD_EDGE ) { m_posChara.x = FIELD_WIDTH - FIELD_EDGE; }
	}


	// 慣性の減少
	void BtlParam::DecreaseInertial ( float d, VEC2& inertial )
	{
		if ( inertial.x > 0 )
		{
			inertial.x -= d;
			if ( inertial.x < 0 ) { inertial.x = 0; }
		}
		else
		{
			inertial.x += d;
			if ( inertial.x > 0 ) { inertial.x = 0; }
		}

		if ( inertial.y > 0 )
		{
			inertial.y -= d;
			if ( inertial.y < 0 ) { inertial.y = 0; }
		}
		else
		{
			inertial.y += d;
			if ( inertial.y > 0 ) { inertial.y = 0; }
		}
	}


	void BtlParam::AddLife ( int n )
	{
		m_life += n;
		if ( m_life < 0 ) { m_life = 0; }
		if ( LIFE_MAX < m_life ) { m_life = LIFE_MAX; }
	}

	void BtlParam::AddBalance ( int n )
	{
		m_balance += n;
		if ( m_balance < 0 ) { m_balance = 0; }
		if ( BALANCE_MAX < m_balance ) { m_balance = BALANCE_MAX; }
	}

	void BtlParam::AddMana ( int n )
	{
		m_mana += n;
		if ( m_mana < 0 ) { m_mana = 0; }
		if ( MANA_MAX < m_mana ) { m_mana = MANA_MAX; }
	}


	//ヒット時
	void BtlParam::OnHit ()
	{
		m_hitEst = true;		//攻撃成立フラグ
		m_tmrHitstop->Start ();		//ヒットストップの設定
		m_tmrHitPitch->WaitStart ( HITSTOP_TIME );	//ヒット間隔のカウント
		//※ヒットストップ分を待機してからスタート

		++ m_hitNum;
	}

	void BtlParam::HitPitchWaitStart ()
	{
		m_tmrHitPitch->Reset ();
		m_tmrHitPitch->WaitStart ( HITSTOP_TIME );	//ヒット間隔のカウント
	}

}	//namespace GAME

