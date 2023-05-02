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
		P_Object m_pOb;
		VEC2	m_startPos;
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;	//[rad]

		bool	m_gotten;		//重なり取得フラグ

	public:
		PrmEfPart ()
			: m_pOb ( nullptr )
			, m_startPos ( 0, 0 ), m_pos ( 0, 0 )
			, m_startVel ( 0, 0 ), m_vel ( 0, 0 )
			, m_G ( 0, 0 ), m_angle ( 0 ), m_gotten ( F )
		{}
	};

	//粒子エフェクトクラス
	class EfPart : public GrpAcv
	{
		enum NUM
		{
			SPARK_NUM = 30,		//1回発生個数
			SPARK_MAX = 300,	//最大個数
		};
		vector < PrmEfPart >	mv_Prm;	//パラメータ
		vector < UINT >			mv_Rnd;	//非稼働オブジェクト数上

	public:
		EfPart ();
		EfPart ( const EfPart & rhs ) = delete;
		~EfPart ();
		
		void Move ();
		void On ( VEC2 center );


		vector < PrmEfPart > & Getrv_Prm () { return mv_Prm; }


		//重なり判定
		//戻値：重なり個数
		UINT Collision ( PV_RECT pv_rect );


	private:
		//引数のベクタに0からN-1までの乱数を格納する
		void Rnd_0_N ( UINT N, vector < UINT > & vec );
	};

	using P_EfPart = shared_ptr < EfPart >;

}	//namespace GAME


