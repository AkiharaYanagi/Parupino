//=================================================================================================
//
//	EfPart ヘッダファイル
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
	struct PrmEfPart
	{
		VEC2	m_startPos;
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;	//[rad]

		bool	m_flag;

	public:
		PrmEfPart ()
			: m_startPos ( 0, 0 ), m_pos ( 0, 0 )
			, m_startVel ( 0, 0 ), m_vel ( 0, 0 )
			, m_G ( 0, 0 ), m_angle ( 0 ), m_flag ( F )
		{}
	};

	//粒子エフェクトクラス
	class EfPart : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 300,
		};
		vector < PrmEfPart >	m_vPrm;

	public:
		EfPart ();
		EfPart ( const EfPart & rhs ) = delete;
		~EfPart ();
		
		void Move ();
		void On ( VEC2 center );
		void Draw ();
	};

	using P_EfPart = shared_ptr < EfPart >;

}	//namespace GAME


