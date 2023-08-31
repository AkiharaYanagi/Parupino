//=================================================================================================
//
//	Menu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "MenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Menu : public GameTaskVector
	{
		bool			m_active;
		P_PrmRect		m_bg;

		VP_MenuItem		mvp_MenuItem;
		VP_MenuItem::iterator		m_itItem;

	public:
		Menu ();
		Menu ( const Menu & rhs ) = delete;
		~Menu ();

		void Init ();

		void SetActive ( bool b ) { m_active = b; }
		bool GetActive () const { return m_active; }

		void SetMenuItem ( P_MenuItem mi );

		void Next ();
		void Prev ();

		DWORD GetIdItem () const;
	};

	using P_Menu = shared_ptr < Menu >;


	//-------------------------------------------
	class MenuString : public GrpStr
	{
	public:
		MenuString ();
		MenuString ( const MenuString & rhs ) = delete;
		~MenuString ();
	};

	using P_MenuString = shared_ptr < MenuString >;


}	//namespace GAME

