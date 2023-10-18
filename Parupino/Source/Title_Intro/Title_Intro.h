//=================================================================================================
//
//	タイトル イントロ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "Title_MenuActor.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Title_Intro : public Scene, public enable_shared_from_this < Title_Intro >
	{
		//遷移先シーンポインタ
		P_GameScene			m_pTransit;

		//メニュアクタ
		P_Title_MenuActor	m_menuActor;

	public:
		Title_Intro ();
		Title_Intro ( const Title_Intro & rhs ) = delete;
		~Title_Intro ();

		void ParamInit ();
		P_GameScene Transit ();

		void Load ();

		void Transit_Intro ();
		void Select_VS ();
	};

	using P_Title_Intro = shared_ptr < Title_Intro >;


}	//namespace GAME

