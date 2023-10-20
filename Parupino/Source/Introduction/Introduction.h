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
		P_GrpAcv		m_grpIntro;
		P_GrpAcv		m_grpCursor;

#if 0
		P_Timer			m_tmrCursor;
		bool			m_bWait;
		bool			m_bHold;
#endif // 0
		P_HoldTimer		m_tmrCursorDown;
		P_HoldTimer		m_tmrCursorUp;


		vector < P_GrpStr >		mv_Str;
		float			m_start_str_y;	//文字列開始位置

		UINT			m_selectPos;
		P_GrpStr		m_dispPos;

		static const size_t SIZE_STR;	//文字列個数
		static const size_t DISP_H;		//文字列表示個数範囲
		static const size_t PAD_HEAD;	//固定位置：先頭
		static const size_t PAD_TAIL;	//固定位置：末尾

	public:
		Introduction ();
		Introduction ( const Introduction & rhs ) = delete;
		~Introduction ();

		void ParamInit ();
		P_GameScene Transit ();

		void Move ();
	};

	using P_Intro = shared_ptr < Introduction >;


}	//namespace GAME

