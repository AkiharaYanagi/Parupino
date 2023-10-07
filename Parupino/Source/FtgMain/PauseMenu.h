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
#include "Fighting.h"


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

		P_PMI_To_Title		m_mi_title;
		P_PMI_ResumeGame	m_mi_resume;

		P_FTG			m_ftg;

	public:
		PauseMenu ();
		PauseMenu ( const PauseMenu & rhs ) = delete;
		~PauseMenu ();

		void Move ();

		void On ();
		void Off ();

		void SetpParent ( P_FtgMain p );
		void SetpFTG ( P_FTG p ) { m_ftg = p; }
	};


	using P_PauseMenu = shared_ptr < PauseMenu >;


}	//namespace GAME

