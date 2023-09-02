//=================================================================================================
//
//	PauseMenuItem
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "MenuItem.h"
#include "../GameMain/Scene.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class FtgMain;
	using P_FtgMain = shared_ptr < FtgMain >;


	class PauseMenuItem : public MenuItem
	{
		//親ポインタ
		P_FtgMain		m_pFtgMain;

	public:
		PauseMenuItem ();
		PauseMenuItem ( const PauseMenuItem & rhs ) = delete;
		~PauseMenuItem ();

		virtual void Do ();

		void SetpParent ( P_FtgMain p ) { m_pFtgMain = p; }
	};


	using P_PauseMenuItem = shared_ptr < PauseMenuItem >;


}	//namespace GAME

