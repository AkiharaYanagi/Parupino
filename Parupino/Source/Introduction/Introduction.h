//=================================================================================================
//
//	イントロダクション
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

	class Introduction : public Scene, public enable_shared_from_this < Introduction >
	{
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//遷移可能な次のシーン

		//===========================================================

		//---------------------------------------

		P_GrpAcv		m_grpIntro;
		P_GrpAcv		m_grpCursor;

		P_HoldTimer		m_tmrCursorDown;
		P_HoldTimer		m_tmrCursorUp;
		UINT			m_cursorPos;


		std::vector < P_GrpStr >		mv_Str;
		INT				m_start_str_y;	//文字列開始行

		UINT			m_selectPos;
		P_GrpStr		m_grpDispPos;

//		static const size_t SIZE_STR;	//文字列個数
		static const size_t DISP_H;		//文字列表示個数範囲
		static const size_t PAD_HEAD;	//固定位置：先頭
		static const size_t PAD_TAIL;	//固定位置：末尾
		static const float	BASE_STR_Y;	//文字列基準位置


		//画像説明
		P_GrpAcv		m_grpInput;		//入力

		//開始後、入力待ち
		UINT		m_wait;
		P_Timer		m_waitSound;	//音声待ち

	public:
		Introduction ();
		Introduction ( const Introduction & rhs ) = delete;
		~Introduction ();

		void Load ();
		void Move ();

		void ParamInit ();	//純粋仮想関数
		P_GameScene Transit ();
	};

	using P_Intro = std::shared_ptr < Introduction >;


}	//namespace GAME

