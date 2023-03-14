//=================================================================================================
//
// GameConst �t�@�C��
//		�Q�[�������ʒ�`
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

	//�L������
	enum CHARA_NAME
	{
		CHARA_TEST,
		CHARA_RAKUNO,
		CHARA_YUKINO,
		CHARA_RONDUM,
		CHARA_NAME_NUM,
	};

	//�J�n���
	enum START_MODE
	{
		START_TITLE,
		START_BATTLE,
		START_TRAINING,
		START_DEMO,
	};

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
	
	//�A�N�V��������
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

	//�A�N�V�����̐� ��`
	enum ACTION_POSTURE
	{
		AP_STAND, AP_CROUCH, AP_JUMP
	};

	//�v�Z���(CalcState)
	enum CLC_ST
	{
		CLC_MAINTAIN,	//����
		CLC_SUBSTITUDE,	//���
		CLC_ADD,		//���Z
	};

	//�u�����`����
	enum BRANCH_CONDITION
	{
		BRC_CMD,	//�R�}���h����
		BRC_GRD,	//���n

		BRC_DMG,	//��������炢
		BRC_HIT_I,	//����Ƀq�b�g(���g��ύX)
		BRC_HIT_E,	//����Ƀq�b�g(�����ύX)

		//�Ō����q�b�g���o�����X�l�Q�Ɓ��O�Ȃ琬��
		BRC_THR_I,	//�������� (�Q�[�����C���w��)
		BRC_THR_E,	//�������� (�Q�[�����C���w��)

		BRC_OFS,	//���E��
		BRC_END,	//�V�[�N�G���X�I����

		//���A����t���O���Q�[�����C���Őݒ�ł���
		//FLG_0, 
		BRC_DASH,		//�_�b�V�����E
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

	//�����ʒu
	enum PLAYER_BASE_PT
	{
		GAME_WIDTH = 2048,
		GAME_HEIGHT = 1024,

		BG_SIZE_X = 2048,
		BG_SIZE_Y = 1024,
		BG_POS_X = 0 - ( 2048 - 1280 ) / 2,
		BG_POS_Y = 0 - ( 1024 - 960 ) / 2,

		PLAYER_BASE_Y = 750,

		PLAYER_1_BASE_X = GAME_WIDTH / 2 - GAME_WINDOW_WIDTH / 2 + 200,
		PLAYER_1_BASE_Y = 750,
		PLAYER_2_BASE_X = GAME_WIDTH / 2 + GAME_WINDOW_WIDTH / 2 - 200,
		PLAYER_2_BASE_Y = 750,

		GRP_PLAYER1_X = 0,
		GRP_PLAYER1_Y = 14,
		GRP_PLAYER2_X = GAME_WINDOW_WIDTH - 64 -0,
		GRP_PLAYER2_Y = 14,

		GAUGE_WIDTH = 500,
		GAUGE_HEIGHT = 40,
		LIFE_GAUGE_X = 80,
		LIFE_GAUGE_Y = 60,
		BALANCE_GAUGE_X = 80,
		BALANCE_GAUGE_Y = 110,

		FIELD_BASE_X = 0,
		FIELD_WIDTH = 2048,
		FIELD_EDGE = 64,

		LIFE_MAX = 10000,
		BALANCE_MAX = 10000,

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

