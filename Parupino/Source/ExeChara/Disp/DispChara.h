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
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/G_Ftg.h"
#include "../../CharaData/Chara.h"
#include "DispMainImage.h"
#include "DispRect.h"
#include "../CharaRect.h"
#include "DispFrontEnd.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispChara : public TASK_VEC
	{
		DispMainImage	m_mainImage;	//メインイメージ
		DispRect		m_dispRect;		//枠
		P_GrpAcv		m_grpShadow;	//影
		DispFrontEnd	m_frontEnd;		//フロントエンド

#if	0
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
	//void InitMainImage ( UINT indexTexture );

		//メインイメージの更新
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );

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


