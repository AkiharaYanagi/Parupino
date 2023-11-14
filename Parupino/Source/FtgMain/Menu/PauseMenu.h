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
#include "PauseMenuItem.h"
#include "YesNo_Menu.h"


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

		P_PMI_To_Title		m_mi_title;
		P_PMI_ResumeGame	m_mi_resume;

		//YNメニュ
		P_YesNo_Menu	m_yesnoMenu;

	public:
		PauseMenu ();
		PauseMenu ( const PauseMenu & rhs ) = delete;
		~PauseMenu ();

		void Load ();
		void Do ();
		void Move ();

		void On ();
		void Off ();

		void SetwpParent ( WP_FtgMain p );

		void OpenYNMenu () { m_yesnoMenu->On (); }
	};


	using P_PauseMenu = std::shared_ptr < PauseMenu >;


}	//namespace GAME

