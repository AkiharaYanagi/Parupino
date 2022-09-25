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
		m_stopTimer = make_shared < Timer > ();
		AddpTask ( m_stopTimer );
	}

	BtlParam::~BtlParam ()
	{
	}


}	//namespace GAME

