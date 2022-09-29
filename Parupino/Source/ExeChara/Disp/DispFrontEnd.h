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

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispFrontEnd
	{
		P_PrmRect	m_gaugeLife;			//ライフゲージ表示
		P_PrmRect	m_gaugeFrameLife;		//ライフゲージ枠表示
		P_PrmRect	m_gaugeDecreaseLife;	//ライフゲージ減少分表示

	public:
		DispFrontEnd ();
		DispFrontEnd ( const DispFrontEnd & rhs ) = delete;
		~DispFrontEnd ();

		//ゲージ類の表示部のみ初期化
		void InitDisp ( PLAYER_ID playerID );

		//ゲージ類更新
		void UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance );
	};


}	//namespace GAME

