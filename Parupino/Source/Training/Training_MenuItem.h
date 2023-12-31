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
#include "Training_Menu_KI.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Training_MenuItem : public PauseMenuItem
	{
		P_MenuString	m_str_KI;

		P_Training_Menu_KI	m_ki;

	public:
		Training_MenuItem ();
		Training_MenuItem ( const Training_MenuItem & rhs ) = delete;
		~Training_MenuItem ();

		void Off ();
		void On ();
		void Decide ();
	};


	using P_Training_MenuItem = std::shared_ptr < Training_MenuItem >;


}	//namespace GAME

