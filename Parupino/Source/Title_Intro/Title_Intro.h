//=================================================================================================
//
//	タイトル イントロダクション対応
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
	class TestGrpAcv : public GrpAcv
	{
	public: 
		void Load () { GrpAcv::Load (); }
	};
	using P_TestGrpAcv = shared_ptr < TestGrpAcv >;


	class Title_Intro : public Scene, public enable_shared_from_this < Title_Intro >
	{
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//遷移可能な次のシーン

		//===========================================================

		P_GrpAcv	m_bg;
		P_GrpAcv	m_logo;
		int			m_count;
		static const float		OMEGA;
		static const float		KEY_X;
		static const float		KEY_Y;

		//メニュアクタ
		P_Title_MenuActor	m_menuActor;

		P_PrmRect	m_explain_bg;
		P_GrpAcv	m_explain_key;

		//開始後、入力待ち
		UINT	m_wait;


		//デモモード
		//CPU vs CPU を自動選択繰り返し
		P_GrpAcv	m_demoMode;		//Validでフラグ替わり
		P_Timer		m_demoTimer;


	public:
		Title_Intro ();
		Title_Intro ( const Title_Intro & rhs ) = delete;
		~Title_Intro ();

		void ParamInit ();

		void Move ();
		void Load ();
		P_GameScene Transit ();


		void Transit_Intro ();
		void Transit_Training ();
		void Transit_1P_VS_2P ();
		void Transit_1P_VS_CPU ();
		void Transit_CPU_VS_CPU ();
		void Select_VS ();
		void Return_Start ();

		//--------------------------
		//デモモード
		void On_DemoMode ();
		void Off_DemoMode ();

	private:
		P_GameScene MakepFtgMain ();
	};

	using P_Title_Intro = shared_ptr < Title_Intro >;


}	//namespace GAME

