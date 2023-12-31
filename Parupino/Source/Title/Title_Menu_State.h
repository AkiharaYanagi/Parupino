//=================================================================================================
//
//	タイトル メニュ状態
//		基準
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
	class Title;	using WP_Title = weak_ptr < Title >;
	class Scene; using WP_Scene = std::weak_ptr < Scene >;

	//--------------------------------------------------------------
	//状態基底クラス
	class Title_Menu_State : public Menu
	{
	protected:
		WP_Title		m_pTitle;
		WP_Scene		mwp_Scene;

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
		Title_Menu_State () : m_active ( T ) {}
		Title_Menu_State ( const Title_Menu_State & rhs ) = delete;
		~Title_Menu_State () {}

		//タイトルメニュの基幹ポインタ
		void SetwpTitle ( WP_Title p ) { m_pTitle = p; }
		virtual void SetwpScene ( WP_Scene wp ) { mwp_Scene = wp; }

		void SetActive ( bool b ) { m_active = b; }
		bool GetActive () const { return m_active; }
	};

	using P_Title_MenuState = std::shared_ptr < Title_Menu_State >;

	//--------------------------------------------------------------


}	//namespace GAME

