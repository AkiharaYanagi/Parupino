//=================================================================================================
//
//	Fighting ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "FtgConst.h"	
#include "MutualChara.h"
#include "../GameMain/Scene.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Fighting : public Scene
	{
		//背景
		P_GrpAcv		m_bg;
		P_GrpAcv		m_bg_blackout;

		P_Timer			m_bgTimer;

		//画面固定システム表示
		//ゲージ枠
		P_GrpAcv		m_gauge_frame;

		//キャラ相互処理
		P_MutualChara	m_mutualChara;

		//デモ
		P_GrpDemo		m_demo_GetReady;
		P_GrpDemo		m_demo_Attack;
		P_GrpDemo		m_demo_Down;
		P_GrpDemo		m_demo_Winner;
		P_GrpDemo		m_demo_SONIA;
		P_GrpDemo		m_demo_ORFLOAT;

		//ポーズ
		P_GrpAcv		m_pause;

	public:
		Fighting ();
		Fighting ( const Fighting & rhs ) = delete;
		~Fighting ();

		void ParamInit ();
		void Init ();
		void Move ();

		P_GameScene Transit ();

	private:
		void MakeGrpDemo ( P_GrpDemo & pGrp, LPCTSTR txName );
		void SetGrpDemo ( P_GrpDemo pGrp );
		void StartGrpDemo ( P_GrpDemo pGrp, UINT time );

		void Pause ();

		//共通グラフィック処理
		void Grp ();
	};


}	//namespace GAME


