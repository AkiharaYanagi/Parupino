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
#include "../Title/Title_Cursor.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Intro_Img : public Scene, public enable_shared_from_this < Intro_Img >
	{
#if 0
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//遷移可能な次のシーン
		//===========================================================
#endif // 0

		P_GrpAcv	m_grpIntro;		//説明画像
		UINT		m_page;			//ページ

		P_GrpAcv	m_grpKey;		//入力表示
		static const VEC2		KEY_POS;

		UINT		m_wait;
		P_Timer		m_waitSound;	//音声待ち

		P_Title_Cursor	m_grpCursor0;
		P_Title_Cursor	m_grpCursor1;

		static const VEC2 CURSOR_POS0;
		static const VEC2 CURSOR_POS1;

		static const UINT N_PAGE;	//ページ数

	public:
		Intro_Img ();
		Intro_Img ( const Intro_Img & rhs ) = delete;
		~Intro_Img ();

		void Load ();
		void Move ();

		void ParamInit ();	//純粋仮想関数
		P_GameScene Transit ();
	};

	using P_Intro_Img = std::shared_ptr < Intro_Img >;


}	//namespace GAME

