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
	class TestScene : public Scene, public enable_shared_from_this < TestScene >
	{
		//遷移先シーンポインタ
		WP_GameScene			mwp_Transit;

	public:
		TestScene () {}
		TestScene ( const TestScene & rhs ) = delete;
		~TestScene () {}

		void ParamInit () {}
		P_GameScene Transit ();
		void Load ();
		void Init ();

	};

	class Title_Intro : public Scene, public enable_shared_from_this < Title_Intro >
	{
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene			mwp_Transit;

		//メニュアクタ
//		P_Title_MenuActor	m_menuActor;

	public:
		Title_Intro ();
		Title_Intro ( const Title_Intro & rhs ) = delete;
		~Title_Intro ();

		void ParamInit () {}

		void Load ();
		P_GameScene Transit ();

#if 0

		void Transit_Intro ();
		void Transit_Training ();
		void Transit_1P_VS_2P ();
		void Transit_1P_VS_CPU ();
		void Transit_CPU_VS_CPU ();
		void Select_VS ();


#endif // 0
		void Transit_Intro () {}
		void Transit_Training () {}
		void Transit_1P_VS_2P () {}
		void Transit_1P_VS_CPU () {}
		void Transit_CPU_VS_CPU () {}
		void Select_VS () {}
	};

	using P_Title_Intro = shared_ptr < Title_Intro >;


}	//namespace GAME

