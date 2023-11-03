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
		START_TITLE_INTRO,
		START_INTRO,
		START_CHARA_SELE,
		START_BATTLE,
		START_RESULT,
		START_TRAINING,
		START_DEMO,
	};


	//SOUND
	enum SOUND_No
	{
		BGM_Title,
		SE_Sys_Select,
		SE_Sys_Enter,
		SE_Sys_Cancel,
		SE_Btl_Clang,
		BGM_Intro,
	};

}

