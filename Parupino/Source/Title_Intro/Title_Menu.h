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
	public:
		Title_MenuState () {}
		Title_MenuState ( const Title_MenuState & rhs ) = delete;
		~Title_MenuState () {}

		virtual void Do () {}

		//タイトルメニュの基幹ポインタ
		void SetwpTitle_Intro ( WP_Title_Intro p ) { m_pTitle_Intro = p; }
	};

	using P_Title_MenuState = shared_ptr < Title_MenuState >;

	//--------------------------------------------------------------


}	//namespace GAME

