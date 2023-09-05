//=================================================================================================
//	Behavior ヘッダファイル
//=================================================================================================
#pragma once
//#include "Game.h"
#include "GameTexture.h"

#include "Sequence.h"
#include "Compend.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================================
	//	イメージリストとシークエンスリスト
	//================================================================
	class Behavior : public Compend
	{
		PVP_TxBs	m_pvpTxBs;		//イメージ配列
		PVP_Sqc		m_seq;			//シークエンス配列

	public:
		Behavior ();
		Behavior ( const Behavior & rhs ) = delete;
		~Behavior ();
	};

	using P_Behavior = shared_ptr < Behavior >;


}	//namespace GAME


