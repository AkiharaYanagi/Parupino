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
#include "MenuItem.h"
#include "../GameMain/Scene.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class PauseMenu;
	using P_PauseMenu = shared_ptr < PauseMenu >;


	//=========================================================

	class PauseMenuItem : public MenuItem
	{
	protected:
		//親ポインタ
		P_PauseMenu		mp_PauseMenu;

	public:
		PauseMenuItem () {}
		PauseMenuItem ( const PauseMenuItem & rhs ) = delete;
		~PauseMenuItem () {}

		virtual void Do () {}

		void SetpParent ( P_PauseMenu p ) { mp_PauseMenu = p; }
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

