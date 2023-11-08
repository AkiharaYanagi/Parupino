//=================================================================================================
//
// FtgConst �t�@�C��
//		Ftg���C�����ʒ�`
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
//	��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// �萔�錾
	//------------------------------------------

	//���o����
	enum DEMO_TIME
	{
		WIN_WAIT = 360,
		WIN_POSE_WAIT = 180,
	};

	//����
	enum WINNER
	{
		WINNER_DRAW,
		WINNER_1P,
		WINNER_2P,
		WINNER_DP,
	};

	//�����萔
	const LPCTSTR ACT_DOWN = _T ( "Down" );
	//����
	enum COMMAND
	{
		NO_COMPLETE = 0xFFFFFFFF
	};

	//�L�����萔
	enum CONST_CHARA
	{
		NUM_RECT = 8,	//����g�z��̕ێ��T�C�Y
//		NUM_RECT = 2,	//����g�z��̕ێ��T�C�Y
	};

	//�g�\��(�F)
	enum RECT_COLOR
	{
		RECT_COLOR_C = 0x400000ff,
		RECT_COLOR_A = 0x40ff0000,
		RECT_COLOR_H = 0x4000ff00,
		RECT_COLOR_O = 0x40ffff00,
	};

	//����
	enum PERCENTAGE
	{
		CENT = 100,
	};

	//CPU_INPUT
	enum CPU_INPUT
	{
		CPU_INPUT_GAMEKEY_NUM = 60,
	};

	//�ō����� (���E)
	enum CLANG_DECISION_LR
	{
		CD_EQUAL,
		CD_LEFT,
		CD_RIGHT,
		CD_OFF,
	};

	//�ō����� (����)
	enum CLANG_DECISION_WL
	{
		CD_DRAW,
		CD_WIN,
		CD_LOSE,
	};

	//��ʕ`��p �����ʒu
	enum PLAYER_BASE_PT
	{
		GAME_WIDTH = 2048,		//�Q�[����ň�����
		GAME_HEIGHT = 1024,

		BG_SIZE_X = 2048,		//�w�i
		BG_SIZE_Y = 1024,
		BG_POS_X = 0 - ( 2048 - 1280 ) / 2,
		BG_POS_Y = 0 - ( 1024 - 960 ) / 2,

		GROUND_Y = 750,			//�n�ʍ���
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

	//�Q�[�W��
	enum GAUGE
	{
		LIFE_GAUGE_X = 80,
		LIFE_GAUGE_Y = 60,
		LIFE_GAUGE_W = 500,
		LIFE_GAUGE_H = 40,

		LIFE_GAUGE_VALUE_CLR0 = 0xffd0f040,
		LIFE_GAUGE_VALUE_CLR1 = 0xffa0f0d0,
		LIFE_GAUGE_VALUE_CLR2 = 0xfff0f040,
		LIFE_GAUGE_VALUE_CLR3 = 0xffa0f0d0,
		LIFE_GAUGE_FRAME_CLR = 0xff606060,
		LIFE_GAUGE_DECREASE_CLR = 0xffff9090,


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
		MANA_GAUGE_Y = 850,
		MANA_GAUGE_W = 500,
		MANA_GAUGE_H = 25,

		MANA_GAUGE_VALUE_CLR0 = 0xffd080f0,
		MANA_GAUGE_VALUE_CLR1 = 0xffa0d0f0,
		MANA_GAUGE_VALUE_CLR2 = 0xffa080f0,
		MANA_GAUGE_VALUE_CLR3 = 0xffa0d0f0,
		MANA_GAUGE_FRAME_CLR = 0xff606060,
		MANA_GAUGE_DECREASE_CLR = 0xffff9090,

	};

	//�o�g���֘A�萔
	enum BATTLE_CONST
	{
		//�t�B�[���h�T�C�Y
		FIELD_BASE_X = 0,
		FIELD_WIDTH = 2048,
		FIELD_EDGE = 64,		//��ʒ[�̕␳

		//�Q�[�W��
		LIFE_MAX = 10000,
		LIFE_START = 10000,

		BALANCE_MAX = 10000,
		BALANCE_START = 8000,

		MANA_MAX = 10000,
		MANA_START = 1000,
		MANA_HALF = MANA_MAX / 2,

		//��~
		HITSTOP_TIME = 15,
		DOWN_TIME = 120 + 60,
		END_TIME = 60,
	};
}

