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


	void BtlParam::BackMoveX ()
	{
		//向きによらず、相手から離れる方向
		VEC2 otherPos = m_pOther.lock ()->GetPos ();
		bool dirBack = true;

		//同値の場合は1P2Pで選別
		if ( m_ptChara.x == otherPos.x )
		{
			dirBack = ( m_playerID == PLAYER_ID_1 );
		}
		else
		{
			//互いの位置で補正方向を決定
			dirBack = ( m_ptChara.x < otherPos.x );
		}

		m_ptChara.x += dirBack ? -1.f : 1.f;
	}

	void BtlParam::LookOther ()
	{
		//空中は持続
		if ( IsJump () )
		{
			return;
		}

		//位置xが同じ場合は持続
		VEC2 otherPos = m_pOther.lock ()->GetPos ();
		if ( m_ptChara.x == otherPos.x )
		{
			return;
		}

		//互いの位置で方向を決定
		m_dirRight = ( m_ptChara.x < otherPos.x );
	}


}	//namespace GAME

