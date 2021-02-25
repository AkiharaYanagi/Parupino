//=================================================================================================
//
//	EfSpark ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
#include "../FtgMain/FtgConst.h"
#include "G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//パラメータ
	struct PrmEfSpark
	{
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;
	};

	//火花エフェクトクラス
	class EfSpark : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 30,
		};
		vector < PrmEfSpark >		m_vPrm;

	public:
		EfSpark ();
		EfSpark ( const EfSpark & rhs ) = delete;
		~EfSpark ();

		void Move ();
		void On ( VEC2 center );
	};

	using P_EfSpark = shared_ptr < EfSpark >;

}	//namespace GAME


