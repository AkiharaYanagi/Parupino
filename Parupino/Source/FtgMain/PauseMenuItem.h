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
	//前方宣言
	class FtgMain;
	using P_FtgMain = shared_ptr < FtgMain >;


	class PauseMenuItem : public MenuItem
	{
	protected:
		//親ポインタ
		P_FtgMain		m_pFtgMain;

	public:
		PauseMenuItem ();
		PauseMenuItem ( const PauseMenuItem & rhs ) = delete;
		~PauseMenuItem ();

		virtual void Do ();

		void SetpParent ( P_FtgMain p ) { m_pFtgMain = p; }
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

