//=================================================================================================
//
//	Training ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgMain/FtgConst.h"	
#include "../FtgMain/MutualChara.h"
#include "../GameMain/Scene.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Training : public Scene, enable_shared_from_this < Training >
	{
		P_GrpAcv		m_bg;			//背景
		P_GrpAcv		m_training;		//トレーニング表示

		//画面固定システム表示
		//ゲージ枠
		P_GrpAcv		m_gauge_frame;

		//キャラ相互処理
		P_MutualChara	m_mutualChara;

		//ポーズ
		P_GrpAcv		m_pause;

	public:
		Training ();
		Training ( const Training & rhs ) = delete;
		~Training ();

		void ParamInit ();
		void Init ();
		void Move ();

		P_GameScene Transit ();

	private:
		void Pause ();
	};


}	//namespace GAME


