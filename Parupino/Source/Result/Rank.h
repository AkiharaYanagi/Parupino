//=================================================================================================
//
//	Rank ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Rank : public TASK_VEC
	{
		P_GrpAcv		m_rank;

		UINT			m_blink;
		UINT			m_step;

	public:
		Rank ();
		Rank ( const Rank & rhs ) = delete;
		~Rank ();

		void Move ();


		//範囲 ( 0 ~ 7 )
		enum RANK
		{
			RANK_AAA = 0,
			RANK_AA	 = 1,
			RANK_A	 = 2,
			RANK_B	 = 3,
			RANK_C	 = 4,
			RANK_D	 = 5,
			RANK_E	 = 6,
			RANK_F	 = 7,
		};

		void SelectRank ( RANK rank );
	};

	using P_Rank = std::shared_ptr < Rank >;


}	//namespace GAME


