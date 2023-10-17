//=================================================================================================
//
//	タイトル メニュ アクタ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Title_Menu.h"
#include "Title_Menu_VS.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------------------------------
	//State

	//--------------------------------------------------------------
	class TMS_Intro : public Title_MenuState
	{
		P_GrpAcv		m_grpIntro;
	public:
		TMS_Intro ();
		TMS_Intro ( const TMS_Intro & rhs ) = delete;
		~TMS_Intro ();
		void Do ();
	};
	using P_TMS_Intro = shared_ptr < TMS_Intro >;

	//--------------------------------------------------------------
	class TMS_Fighting : public Title_MenuState
	{
		P_GrpAcv		m_grp;
	public:
		TMS_Fighting ();
		TMS_Fighting ( const TMS_Fighting & rhs ) = delete;
		~TMS_Fighting ();
		void Do ();
	};
	using P_TMS_Fighting = shared_ptr < TMS_Fighting >;

	//--------------------------------------------------------------



	//==============================================================
	//メニュ　初期状態
	class Title_Menu_Start : public Title_MenuState
	{
		P_TMS_Intro			m_state_Intro;
		P_TMS_Fighting		m_state_Fighting;

		P_Title_MenuState	m_selectedState;


		P_GrpAcv			m_grpCursor;

	public:
		Title_Menu_Start ();
		Title_Menu_Start ( const Title_Menu_Start & rhs ) = delete;
		~Title_Menu_Start ();

		void SetpParent ( P_Title_Intro p );
		void Do ();
	};
	using P_Title_Menu_Start = shared_ptr < Title_Menu_Start >;


	//==============================================================
	//メニュ 動作主
	class Title_MenuActor : public Menu
	{
		P_Title_Menu_Start	m_start;
		P_Title_Menu_VS		m_vs;

		P_Title_MenuState	m_selectedState;
#if 0
#endif // 0

	public:
		Title_MenuActor ();
		Title_MenuActor ( const Title_MenuActor & rhs ) = delete;
		~Title_MenuActor ();

		void Load ();
		void Move ();

		void SetpParent ( P_Title_Intro p );
	};

	using P_Title_MenuActor = shared_ptr < Title_MenuActor >;


	//--------------------------------------------------------------


}	//namespace GAME

