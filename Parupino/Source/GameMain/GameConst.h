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
		START_BATTLE,
		START_TRAINING,
		START_DEMO,
	};

	//入力
	enum COMMAND
	{
		NO_COMPLETE = 0xFFFFFFFF
	};

	//キャラ定数
	enum CONST_CHARA
	{
		NUM_RECT = 8,	//判定枠配列の保持サイズ
//		NUM_RECT = 2,	//判定枠配列の保持サイズ
	};

	//枠表示(色)
	enum RECT_COLOR
	{
		RECT_COLOR_C = 0x400000ff,
		RECT_COLOR_A = 0x40ff0000,
		RECT_COLOR_H = 0x4000ff00,
		RECT_COLOR_O = 0x40ffff00,
	};

	//割合
	enum PERCENTAGE
	{
		CENT = 100,
	};

	//CPU_INPUT
	enum CPU_INPUT
	{
		CPU_INPUT_GAMEKEY_NUM = 60,
	};
	
	//アクション属性
	enum ACTION_CATEGORY 
	{
		AC_NEUTRAL, AC_MOVE, AC_JUMP, AC_DASH,
		
		AC_ATTACK_L, AC_ATTACK_M, AC_ATTACK_H, 
		AC_ATTACK_J, 
		AC_SPECIAL, AC_OVERDRIVE, 

		AC_DAMAGED, 
		AC_POISED, AC_CLANG, AC_AVOID, 
		AC_DOTTY, AC_THROW, AC_GUARD,

		AC_DEMO, AC_OTHER, 
		ACTION_CATEGORY_NUM
	};

	//アクション体勢 定義
	enum ACTION_POSTURE
	{
		AP_STAND, AP_CROUCH, AP_JUMP
	};

	//計算状態(CalcState)
	enum CLC_ST
	{
		CLC_MAINTAIN,	//持続
		CLC_SUBSTITUDE,	//代入
		CLC_ADD,		//加算
	};

	//ブランチ条件
	enum BRANCH_CONDITION
	{
		BRC_CMD,	//コマンド成立
		BRC_GRD,	//着地

		BRC_DMG,	//自分が喰らい
		BRC_HIT_I,	//相手にヒット(自身を変更)
		BRC_HIT_E,	//相手にヒット(相手を変更)

		//打撃がヒット→バランス値参照→０なら成立
		BRC_THR_I,	//投げ成立 (ゲームメイン指定)
		BRC_THR_E,	//投げ成立 (ゲームメイン指定)

		BRC_OFS,	//相殺時
		BRC_END,	//シークエンス終了時

		//他、特殊フラグをゲームメインで設定できる
		//FLG_0, 
		BRC_DASH,		//ダッシュ相殺
	};

	//打合結果 (左右)
	enum CLANG_DECISION_LR
	{
		CD_EQUAL,
		CD_LEFT,
		CD_RIGHT,
		CD_OFF, 
	};

	//打合結果 (勝負)
	enum CLANG_DECISION_WL
	{
		CD_DRAW,
		CD_WIN,
		CD_LOSE,
	};

	//画面描画用 初期位置
	enum PLAYER_BASE_PT
	{
		GAME_WIDTH = 2048,
		GAME_HEIGHT = 1024,

		BG_SIZE_X = 2048,
		BG_SIZE_Y = 1024,
		BG_POS_X = 0 - ( 2048 - 1280 ) / 2,
		BG_POS_Y = 0 - ( 1024 - 960 ) / 2,

		GROUND_Y = 750,			//地面高さ
		PLAYER_BASE_Y = GROUND_Y,

		PLAYER_1_BASE_X = GAME_WIDTH / 2 - GAME_WINDOW_WIDTH / 2 + 200,
		PLAYER_1_BASE_Y = PLAYER_BASE_Y,
		PLAYER_2_BASE_X = GAME_WIDTH / 2 + GAME_WINDOW_WIDTH / 2 - 200,
		PLAYER_2_BASE_Y = PLAYER_BASE_Y,

		GRP_PLAYER1_X = 0,
		GRP_PLAYER1_Y = 14,
		GRP_PLAYER2_X = GAME_WINDOW_WIDTH - 64 - 0,
		GRP_PLAYER2_Y = 14,
	};

	//ゲージ類
	enum GAUGE
	{
		LIFE_GAUGE_X = 80,
		LIFE_GAUGE_Y = 60,
		LIFE_GAUGE_W = 500,
		LIFE_GAUGE_H = 40,

		LIFE_GAUGE_VALUE_CLR0	 = 0xffd0f040,
		LIFE_GAUGE_VALUE_CLR1	 = 0xffa0f0d0,
		LIFE_GAUGE_VALUE_CLR2	 = 0xfff0f040,
		LIFE_GAUGE_VALUE_CLR3	 = 0xffa0f0d0,
		LIFE_GAUGE_FRAME_CLR	 = 0xff606060,
		LIFE_GAUGE_DECREASE_CLR	 = 0xffff9090,


		BALANCE_GAUGE_X = 80,
		BALANCE_GAUGE_Y = 110,
		BALANCE_GAUGE_W = 500,
		BALANCE_GAUGE_H = 25,

		BALANCE_GAUGE_VALUE_CLR0 = 0xff40d0f0,
		BALANCE_GAUGE_VALUE_CLR1 = 0xffa0d0f0,
		BALANCE_GAUGE_VALUE_CLR2 = 0xff40f0f0,
		BALANCE_GAUGE_VALUE_CLR3 = 0xffa0d0f0,
		BALANCE_GAUGE_FRAME_CLR = 0xff808080,
		BALANCE_GAUGE_DECREASE_CLR = 0xffff9090,


		MANA_GAUGE_X = 80,
		MANA_GAUGE_Y = 900,
		MANA_GAUGE_W = 500,
		MANA_GAUGE_H = 25,

		MANA_GAUGE_VALUE_CLR0 = 0xffd0f040,
		MANA_GAUGE_VALUE_CLR1 = 0xffa0f0d0,
		MANA_GAUGE_VALUE_CLR2 = 0xfff0f040,
		MANA_GAUGE_VALUE_CLR3 = 0xffa0f0d0,
		MANA_GAUGE_FRAME_CLR = 0xff606060,
		MANA_GAUGE_DECREASE_CLR = 0xffff9090,

	};

	//バトル関連定数
	enum BATTLE_CONST
	{
		//サイズ
		FIELD_BASE_X = 0,
		FIELD_WIDTH = 2048,
		FIELD_EDGE = 64,		//画面端の補正

		//ゲージ類
		LIFE_MAX = 10000,

		BALANCE_MAX = 10000,
		BALANCE_START = 8000,

		MANA_MAX = 10000,
		MANA_START = 1000,

		//停止
		HITSTOP_TIME = 15,
		DOWN_TIME = 120 + 60,
		END_TIME = 60,
	};

	//SOUND
	enum SOUND_No
	{
		BGM_Select,
		BGM_Main,
		SE_Clang,
		SE_Hit,
		SE_cursor_move,
		SE_Cancel,
		SE_Guard,
	};

}

