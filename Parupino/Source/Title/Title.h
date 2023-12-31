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
#include "Title_Menu_Actor.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Title : public Scene, public enable_shared_from_this < Title >
	{
		P_GrpAcv	m_bg;
		P_GrpAcv	m_logo;
		int			m_count;
		static const float		OMEGA;
		static const VEC2		KEY_POS;

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
		Title ();
		Title ( const Title & rhs ) = delete;
		~Title ();

		void ParamInit ();

		void Move ();
		void Load ();

		P_GameScene Transit ();

#if 0
		void Transit_1P_VS_2P ();
		void Transit_1P_VS_CPU ();
		void Transit_CPU_VS_CPU ();
#endif // 0
		void Select_VS ();
		void Return_Start ();

		//--------------------------
		//デモモード
		void On_DemoMode ();
		void Off_DemoMode ();
	};

	using P_Title = std::shared_ptr < Title >;


}	//namespace GAME

