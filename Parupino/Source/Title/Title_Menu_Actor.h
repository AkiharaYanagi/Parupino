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
#include "Title_Menu_State.h"
#include "Title_Menu_Start.h"
#include "Title_Menu_VS.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==============================================================
//	using WP_Title = std::weak_ptr < Title >;
	class Scene;	using WP_Scnen = std::weak_ptr < Scene >;

	//==============================================================
	//メニュ 動作主体
	class Title_Menu_Actor : public Menu
	{
		P_Title_Menu_Start	m_start;
		P_Title_Menu_VS		m_vs;

		WP_Scene	mwp_Scene;


	public:
		Title_Menu_Actor ();
		Title_Menu_Actor ( const Title_Menu_Actor & rhs ) = delete;
		~Title_Menu_Actor ();

		void Load ();
		void Move ();

		void SetwpTitle ( WP_Title wp );
		void SetwpScene ( WP_Scene wp );

		void Select_VS ();
		void Return_Start ();
	};

	using P_Title_MenuActor = std::shared_ptr < Title_Menu_Actor >;


	//--------------------------------------------------------------


}	//namespace GAME

