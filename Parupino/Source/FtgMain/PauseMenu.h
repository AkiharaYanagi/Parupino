//=================================================================================================
//
//	PauseMenu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Menu.h"
#include "PauseMenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class PauseMenu : public Menu
	{
		P_PrmRect		m_bg;
		P_MenuString	m_grpStr_pause;
		P_GrpAcv		m_cursor;


		P_MenuString	m_grpStr_title;
		P_MenuString	m_grpStr_resume;

		P_PauseMenuItem		m_mi_title;
		P_PauseMenuItem		m_mi_resume;

	public:
		PauseMenu ();
		PauseMenu ( const PauseMenu & rhs ) = delete;
		~PauseMenu ();

		void Move ();

		void On ();
		void Off ();
	};


	using P_PauseMenu = shared_ptr < PauseMenu >;


}	//namespace GAME

