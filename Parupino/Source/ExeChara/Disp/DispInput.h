//=================================================================================================
//
// DispInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../CharaData/Chara.h"
#include "../../FtgMain/G_Ftg.h"
#include "../Input/CharaInput.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispInput
	{
		//キー入力表示個数
		static const UINT NUM_DISP_INPUT;

		P_PrmRect		m_bg;		//背景

		P_GrpAcv		m_grp;		//入力表示
		VP_Object		m_vpOb;

		UINT			m_timer;
		float			m_vel;
		float			m_base;

	public:
		DispInput ();
		DispInput ( const DispInput & rhs ) = delete;
		~DispInput ();

		void LoadPlayer ( PLAYER_ID playerID );

		//入力更新
		void UpdateInput ( P_CharaInput pCharaInput );


	private:
		bool GetBoolInput ( P_CharaInput pCharaInput, int n, int i );
	};

}	//namespace GAME


