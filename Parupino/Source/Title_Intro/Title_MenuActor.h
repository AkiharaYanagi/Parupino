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
#include "Title_Cursor.h"
#include "Title_Menu.h"
#include "Title_Menu_Start.h"
#include "Title_Menu_VS.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
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
		void Return_Start ();
	};

	using P_Title_MenuActor = std::shared_ptr < Title_MenuActor >;


	//--------------------------------------------------------------


}	//namespace GAME

