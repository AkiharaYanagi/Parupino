//=================================================================================================
//
//	Training_MenuItem
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../Menu/PauseMenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Training_MenuItem : public PauseMenuItem
	{
		P_MenuString	m_grpStr_test;
	public:
		Training_MenuItem ();
		Training_MenuItem ( const Training_MenuItem & rhs ) = delete;
		~Training_MenuItem ();

		void Off ();
		void On ();
	};


	using P_Training_MenuItem = std::shared_ptr < Training_MenuItem >;


}	//namespace GAME

