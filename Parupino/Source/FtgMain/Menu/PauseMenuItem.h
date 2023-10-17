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
#include "Menu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=========================================================
	class PauseMenu;
	using WP_PauseMenu = weak_ptr < PauseMenu >;

	//=========================================================
	class PauseMenuItem : public Menu
	{
	public:
		PauseMenuItem () {}
		PauseMenuItem ( const PauseMenuItem & rhs ) = delete;
		~PauseMenuItem () {}

		virtual void Do () {}
	};

	using P_PauseMenuItem = shared_ptr < PauseMenuItem >;

	//=========================================================
	class PMI_To_Title : public PauseMenuItem
	{
	public :
		void Do ();
	};
	using P_PMI_To_Title = shared_ptr < PMI_To_Title >;


	class PMI_ResumeGame : public PauseMenuItem
	{
	public:
		void Do ();
	};
	using P_PMI_ResumeGame = shared_ptr < PMI_ResumeGame >;


}	//namespace GAME

