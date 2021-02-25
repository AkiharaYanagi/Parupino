//=================================================================================================
//
// DispChara ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "DispRect.h"
#include "../../GameMain/GameConst.h"
#include "../../CharaData/Chara.h"
//#include "../Effect/OperateEffect.h"
//#include "DispMainImage.h"
//#include "DispFrontEnd.h"
#include "../../FtgMain/G_Ftg.h"
#include "../CharaRect.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispChara : public TASK_VEC
	{
		P_Chara		m_pChara;			//キャラポインタ
		P_GrpApTx	m_mainGraphic;		//メイングラフィック表示
		PVP_TxBs	m_pvpMainTexture;	//メインイメージのテクスチャリスト

		DispRect	m_dispRect;			//枠
		P_GrpAcv	m_grpShadow;		//影

		P_PrmRect	m_gaugeLife;			//ライフゲージ表示
		P_PrmRect	m_gaugeFrameLife;		//ライフゲージ枠表示
		P_PrmRect	m_gaugeDecreaseLife;	//ライフゲージ減少分表示
#if	0
//		DispMainImage			m_dispMainImage;	//メインイメージ
//		DispFrontEnd			m_dispFrontEnd;		//フロントエンド

		GrpAcv		m_grpPlayer1P;	//プレイヤー表示"1P"
		GrpAcv		m_grpPlayer2P;	//プレイヤー表示"2P"
		GrpAcv		m_grpPlayerCOM;	//プレイヤー表示"CPU"

		PrmRect		m_gaugeHitStop;			//ヒットストップ時間表示
		PrmRect		m_gaugeLurch;			//のけぞり時間表示

		//エフェクト
		GrpEf		m_grpHitEf;			//ヒットエフェクト
		GrpEf		m_grpAvoidEf;		//アヴォイドエフェクト
		GrpEf		m_grpPoisedEf;		//構えエフェクト

		P_GrpApTx		m_efGraphic;		//エフェクトグラフィック表示
		OperateEffect*		m_pOprtEf;
#endif	//0

	public:
		DispChara ();
		DispChara ( const DispChara & rhs ) = delete;
		~DispChara ();

		//キャラを設定する
		void SetpChara ( const P_Chara pChara );

		//メインイメージの初期化
		void InitMainImage ( UINT indexTexture );

		//メインイメージの更新
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );

#if 0
		//エフェクトイメージテクスチャリストの設定
//		void SetpEfImageTextureList ( PVP_TEXTURE pvpEfTexture ) { m_pvpEfTexture = pvpEfTexture; }

		//オペレートエフェクト
		OperateEffect* GetpOperateEffect () const { return m_pOprtEf; }

		//エフェクトイメージの更新
		void UpdateEffectImage ( Script* pScript, float dispGameBaseX, VEC2 ptChara, bool dirRight );

		//オペレートエフェクトの更新
		void UpdateOperateEffect ( float dispGameBaseX, VEC2 ptChara, bool dirRight );
#endif	//0

		//表示枠設定
		void SetpCharaRect ( P_CharaRect pCharaRect );

		//枠表示
		void OnRect () { m_dispRect.OnRect (); }
		//枠非表示
		void OffRect () { m_dispRect.OffRect (); }

		//ゲージ類の表示部のみ初期化
		void InitDisp ( PLAYER_ID playerID );

		//ゲージ類更新
		void UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance );

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


