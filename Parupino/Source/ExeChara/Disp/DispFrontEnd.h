//=================================================================================================
//
// DispFrontEnd ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../FtgMain/G_Ftg.h"
#include "../../CharaData/Chara.h"
#include "../BtlParam.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispFrontEnd
	{
		PLAYER_ID	m_playerID;				//プレイヤ別表示側

		P_PrmRect	m_gaugeLife;			//ライフゲージ表示
		P_PrmRect	m_gaugeFrameLife;		//ライフゲージ枠表示
		P_PrmRect	m_gaugeDecreaseLife;	//ライフゲージ減少分表示
		float		m_fDamage;				//ライフゲージ減少分

		P_PrmRect	m_gaugeBalance;			//バランスゲージ表示
		P_PrmRect	m_gaugeFrameBalance;	//バランスゲージ枠表示
		P_PrmRect	m_gaugeDecreaseBalance;	//バランスゲージ減少分表示

#if	0
		GrpAcv		m_grpPlayer1P;	//プレイヤー表示"1P"
		GrpAcv		m_grpPlayer2P;	//プレイヤー表示"2P"
		GrpAcv		m_grpPlayerCOM;	//プレイヤー表示"CPU"

		PrmRect		m_gaugeHitStop;			//ヒットストップ時間表示
		PrmRect		m_gaugeLurch;			//のけぞり時間表示
#endif	//0
#if	0
		//エフェクト
		GrpEf		m_grpHitEf;			//ヒットエフェクト
		GrpEf		m_grpAvoidEf;		//アヴォイドエフェクト
		GrpEf		m_grpPoisedEf;		//構えエフェクト

		P_GrpApTx		m_efGraphic;		//エフェクトグラフィック表示
		OperateEffect*		m_pOprtEf;
#endif	//0


	public:
		DispFrontEnd ();
		DispFrontEnd ( const DispFrontEnd & rhs ) = delete;
		~DispFrontEnd ();

		//ゲージ類の表示部のみ初期化
		void LoadPlayer ( PLAYER_ID playerID );

		//初期化
		void Init ();

		//ゲージ類更新
		void UpdateGauge ( BtlParam btlPrm );

#if 0
		//ヒットストップ時間表示の更新
		void UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer );

		//のけぞり時間表示の更新
		void UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer );

		//ヒット
		void OnHit ( VEC2 ptChara, bool dirRight );

		//アヴォイド
		void OnAvoid ( VEC2 ptChara, bool dirRight );

		//ポイズド
		void OnPoised ( VEC2 ptChara, bool dirRight );
#endif // 0

	};


}	//namespace GAME

