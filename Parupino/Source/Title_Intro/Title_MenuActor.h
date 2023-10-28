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
		void Off ();
		void On ();
	};
	using P_TMS_Intro = shared_ptr < TMS_Intro >;

	//--------------------------------------------------------------
	class TMS_VS : public Title_MenuState
	{
		P_GrpAcv		m_grp;
	public:
		TMS_VS ();
		TMS_VS ( const TMS_VS & rhs ) = delete;
		~TMS_VS ();
		void Do ();
		void Off ();
		void On ();
	};
	using P_TMS_VS = shared_ptr < TMS_VS >;

	//--------------------------------------------------------------



	//==============================================================
	//メニュ　初期状態
	class Title_Menu_Start : public Title_MenuState
	{
		P_TMS_Intro		m_state_Intro;
		P_TMS_VS		m_state_VS;

		P_GrpAcv		m_grpCursor;
		int				m_count;
		static const float		OMEGA;

	public:
		Title_Menu_Start ();
		Title_Menu_Start ( const Title_Menu_Start & rhs ) = delete;
		~Title_Menu_Start ();

		void Move ();
		void Load ();
		void Do ();

		void SetwpTitle_Intro ( WP_Title_Intro p );
		void Off ();
		void On ();
	};
	using P_Title_Menu_Start = shared_ptr < Title_Menu_Start >;


	//==============================================================
	using WP_Title_Intro = weak_ptr < Title_Intro >;

	//メニュ 動作主体
	class Title_MenuActor : public Menu
	{
		P_Title_Menu_Start	m_start;
		P_Title_Menu_VS		m_vs;

	public:
		Title_MenuActor ();
		Title_MenuActor ( const Title_MenuActor & rhs ) = delete;
		~Title_MenuActor ();

		void Load ();
		void Move ();

		void SetwpTitle_Intro ( WP_Title_Intro p );

		void Select_VS ();
	};

	using P_Title_MenuActor = shared_ptr < Title_MenuActor >;


	//--------------------------------------------------------------


}	//namespace GAME

