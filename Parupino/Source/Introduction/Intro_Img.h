//=================================================================================================
//
//	イントロダクション イメージのみ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Intro_Img : public Scene, public enable_shared_from_this < Intro_Img >
	{
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//遷移可能な次のシーン

		//===========================================================


	public:
		Intro_Img ();
		Intro_Img ( const Intro_Img & rhs ) = delete;
		~Intro_Img ();

		void Load ();
		void Move ();

		void ParamInit ();
		P_GameScene Transit ();
	};

	using P_Intro_Img = shared_ptr < Intro_Img >;


}	//namespace GAME

