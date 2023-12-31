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

		//-----------------
		//稼働フラグ
		
		bool			m_bMenu;		//全体

		//メニュの単体ページ
		//Menu::m_active

	public:
		PauseMenu ();
		PauseMenu ( const PauseMenu & rhs ) = delete;
		~PauseMenu ();

		void Load ();
		void Do ();
		void Move ();

		//メインMove()中でチェックしてtrueのとき他を処理しないでreturnする
		bool MenuCheck ();
		void Input ();

		void On ();
		void Off ();

		void UnDisp ();

//		void SetwpParent ( WP_FtgMain p );
		void SetwpParentScene ( WP_Scene wp );

		void OpenYNMenu () { m_yesnoMenu->On (); }
	};


	using P_PauseMenu = std::shared_ptr < PauseMenu >;


}	//namespace GAME

