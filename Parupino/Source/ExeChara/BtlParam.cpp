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
		, m_life ( 0 ), m_balance ( 0 ), m_damage ( 0 ), m_power ( 0 )
		, m_hitEst ( false ), m_clang ( false ), m_transit ( false )
		, m_ForcedChange ( false )
		//		, m_lurch ( 0 ), m_lurchTimer ( 0 )
		, m_blackOut ( 0 ), m_scpStop ( 0 )
	{
		//タイマーの初期化
		//ヒットストップ
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

		//ストップタイマ
		m_TmrStop = make_shared < Timer > ();
		AddpTask ( m_TmrStop );
	}

	BtlParam::~BtlParam ()
	{
	}

	void BtlParam::InitPlayerID ( PLAYER_ID playerID )
	{
		//初期位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_posChara = VEC2 ( PLAYER_1_BASE_X, PLAYER_1_BASE_Y );
			m_dirRight = true;
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_posChara = VEC2 ( PLAYER_2_BASE_X, PLAYER_2_BASE_Y );
			m_dirRight = false;
		}
	}

	void BtlParam::Init ()
	{
		//ゲームパラメータ
		m_life = LIFE_MAX;
		m_damage = 0;
		m_power = 0;
		m_hitEst = false;
		m_FirstEf = false;
		m_FirstSE = false;
		m_charaState = CHST_START;

		m_inertial = VEC2 ( 0, 0 );
		m_dashInertial = VEC2 ( 0, 0 );
		m_vel = VEC2 ( 0, 0 );
		m_acc = VEC2 ( 0, 0 );

		EndAction ();

		//タイマー
		m_tmrEnd->Reset ();
		m_tmrHitstop->Reset ();

		TASK_VEC::Init ();
	}

	void BtlParam::EndAction ()
	{
		m_clang = false;
		m_hitEst = false;
		m_FirstEf = false;
		m_ForcedChange = false;
		//		m_lurch = 0;
		//		m_lurchTimer = 0;
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

		//値
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

}	//namespace GAME

