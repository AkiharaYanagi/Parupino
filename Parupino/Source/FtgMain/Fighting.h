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
#include "FtgDemo.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Fighting : public TASK_LST
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

		//=====================================================
		//デモ
//		P_FtgDemoActor		m_demoActor;

		//=====================================================

		//ポーズ
		P_GrpAcv		m_pause;

	public:
		Fighting ();
		Fighting ( const Fighting & rhs ) = delete;
		~Fighting ();

		void Init ();
		void Move ();

		void ParamInit ( P_Param pParam );

	private:
		void Pause ();

		//共通グラフィック処理
		void Grp ();
	};

	using P_FTG = shared_ptr < Fighting >;


}	//namespace GAME


