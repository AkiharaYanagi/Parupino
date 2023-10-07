//=================================================================================================
//
//	YesNo_Menu
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

	class YesNo_Menu : public Menu
	{
		P_PrmRect		m_bg;
		P_MenuString	m_grpStr_yesno;
		P_GrpAcv		m_cursor;

		P_MenuString	m_grpStr_yes;
		P_MenuString	m_grpStr_no;


	public:
		YesNo_Menu ();
		YesNo_Menu ( const YesNo_Menu & rhs ) = delete;
		~YesNo_Menu ();

		void Move ();

		void On ();
		void Off ();

		void SetpParent ( P_FtgMain p );
	};


	using P_YesNo_Menu = shared_ptr < YesNo_Menu >;


}	//namespace GAME

