//=================================================================================================
//
//	EfParticle ヘッダファイル
//		打合時に発生するの回収可能な粒子
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"
#include "../G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//パラメータ
	struct PrmEfParticle
	{
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;
	public:
		PrmEfParticle () : m_angle ( 0 ) {}
	};

	//火花エフェクトクラス
	class EfParticle : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 30,
		};
		vector < PrmEfParticle >		m_vPrm;

	public:
		EfParticle ();
		EfParticle ( const EfParticle & rhs ) = delete;
		~EfParticle ();

		void Move ();
		void On ( VEC2 center );
	};

	using P_EEfParticle = shared_ptr < EfParticle >;

}	//namespace GAME


