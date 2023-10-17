//=================================================================================================
//
// GameConst ファイル
//		ゲーム内共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------

	//キャラ名
	enum CHARA_NAME
	{
		CHARA_TEST,
		CHARA_RAKUNO,
		CHARA_YUKINO,
		CHARA_RONDUM,
		CHARA_NAME_NUM,
	};

	//開始状態
	enum START_MODE
	{
		START_TITLE,
		START_TITLE_INTRO,
		START_BATTLE,
		START_TRAINING,
		START_DEMO,
	};


	//SOUND
	enum SOUND_No
	{
		SE00_kane,
		BGM_Select,
		BGM_Main,
		SE_Clang,
		SE_Hit,
		SE_cursor_move,
		SE_Cancel,
		SE_Guard,
	};

}

