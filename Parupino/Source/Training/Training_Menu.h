//=================================================================================================
//
//	Training_Menu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../Menu/PauseMenu.h"
#include "Training_MenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Training_Menu : public PauseMenu
	{
		P_Training_MenuItem		m_testItem;
		P_GrpAcv	m_keyIndex;
		P_GrpAcv	m_selectRect;

	public:
		Training_Menu ();
		Training_Menu ( const Training_Menu & rhs ) = delete;
		~Training_Menu ();

		void Load ();
		void Off ();
		void On ();
	};


	using P_Training_Menu = std::shared_ptr < Training_Menu >;


}	//namespace GAME

