//=================================================================================================
//
//	タイトル メニュ スタート状態
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Title_Cursor.h"
#include "Title_Explain.h"
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
		P_Title_Explain	m_expl;

		P_PrmRect	m_fade;
		UINT		m_wait;

	public:
		TMS_Intro ();
		TMS_Intro ( const TMS_Intro & rhs ) = delete;
		~TMS_Intro ();
		void Do ();
		void Off ();
		void On ();

		void Unselect ();
	};
	using P_TMS_Intro = shared_ptr < TMS_Intro >;

	//--------------------------------------------------------------
	class TMS_VS : public Title_MenuState
	{
		P_GrpAcv		m_grpVS;
		P_Title_Explain	m_expl;

	public:
		TMS_VS ();
		TMS_VS ( const TMS_VS & rhs ) = delete;
		~TMS_VS ();
		void Do ();
		void Off ();
		void On ();

		void Unselect ();
	};
	using P_TMS_VS = shared_ptr < TMS_VS >;

	//--------------------------------------------------------------




	//==============================================================
	//メニュ　初期状態
	class Title_Menu_Start : public Title_MenuState
	{
		P_TMS_Intro		m_state_Intro;
		P_TMS_VS		m_state_VS;

		P_Title_Cursor	m_grpCursor;

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


}	//namespace GAME

