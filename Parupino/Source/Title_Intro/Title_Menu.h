//=================================================================================================
//
//	タイトル メニュ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------------------------------
	//前方宣言 親ポインタ
	class Title_Intro;
	using WP_Title_Intro = weak_ptr < Title_Intro >;

	//--------------------------------------------------------------
	//状態基底クラス
	class Title_MenuState : public Menu
	{
	protected:
		WP_Title_Intro		m_pTitle_Intro;
		static const float		MENU_X;
		static const float		MENU_Y_0;
		static const float		MENU_Y_1;
		static const float		CURSOR_X;
		static const float		CURSOR_Y;
		static const float		PITCH_Y;
		static const float		EXPLAIN_X;
		static const float		EXPLAIN_Y;

		bool	m_active;
	public:
		Title_MenuState () : m_active ( T ) {}
		Title_MenuState ( const Title_MenuState & rhs ) = delete;
		~Title_MenuState () {}

		//タイトルメニュの基幹ポインタ
		void SetwpTitle_Intro ( WP_Title_Intro p ) { m_pTitle_Intro = p; }

		void SetActive ( bool b ) { m_active = b; }
		bool GetActive () const { return m_active; }
	};

	using P_Title_MenuState = shared_ptr < Title_MenuState >;

	//--------------------------------------------------------------


}	//namespace GAME

