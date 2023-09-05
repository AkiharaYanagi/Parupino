//=================================================================================================
//
// IOCharaDefine �w�b�_�t�@�C��
//		���ʒ�`
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Chara.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=================================
	//�t�@�C���`���̃o�[�W����
	enum { CHARA_VERSION = 110 };
	//=================================

	//-------------------------------------------
	//Document(���[�g)���̃G�������g��Chara�̂�

	//-------------------------------------------
	//Chara���̃G�������g
	enum ELEM_CHARA
	{
		ELEM_CHARA_VER		,
		EL_MAIN_IMAGE_LIST	,
		EL_EF_IMAGE_LIST	,
		EL_ACTION			,
		EL_EFFECT			,
		EL_COMMAND,
		EL_BRANCH,
		EL_ROUTE,
	};

	//-------------------------------------------
	//���O�݂̂̋��ʃA�g���r���[�g
	enum ATTR_NAME
	{
		ATTR_NAME_0 = 0,
	};

	//�A�N�V�������̃A�g���r���[�g
	enum ATTR_ACTION
	{
		ATTR_ACTION_NAME		, 
		ATTR_ACTION_NEXT,
		ATTR_ACTION_ID,
		ATTR_ACTION_CATEGORY	,
		ATTR_ACTION_POSTURE		,
		ATTR_ACTION_BALANCE		, 
	};

	//-------------------------------------------
	//�X�N���v�g���̃A�g���r���[�g
	enum ATTR_SCRIPT
	{
		ATTR_SCRIPT_GROUP,
		ATTR_SCRIPT_IMAGE_NAME,
		ATTR_SCRIPT_IMAGE_ID,
		ATTR_SCRIPT_POS_X		,
		ATTR_SCRIPT_POS_Y		, 
		ATTR_SCRIPT_VEL_X		, 
		ATTR_SCRIPT_VEL_Y		, 
		ATTR_SCRIPT_ACC_X		, 
		ATTR_SCRIPT_ACC_Y		, 
		ATTR_SCRIPT_CLCST		, 
		ATTR_SCRIPT_POWER,
		ATTR_SCRIPT_BLACKOUT,
		ATTR_SCRIPT_VIBRATION,
		ATTR_SCRIPT_STOP,
	};

	//�X�N���v�g�����[�g��ID
	enum
	{
		ATTR_SCRIPT_ROUTE_NAME = 0,
		ATTR_SCRIPT_ROUTE_ID = 1,
	};

	//�X�N���v�g���̃G�������g
	enum
	{
		ELEM_SCRIPT_ROUTE, 
		ELEM_SCRIPT_EFGNRT, 
		ELEM_SCRIPT_CRECT, 
		ELEM_SCRIPT_ARECT, 
		ELEM_SCRIPT_HRECT, 
		ELEM_SCRIPT_ORECT, 
	};

	//�R�}���h�̃A�g���r���[�g
	enum
	{
		ATTR_COMMAND_NAME,
		ATTR_COMMAND_LIMIT,
	};

	//�Q�[���L�[�R�}���h�̃A�g���r���[�g
	enum
	{
		ATTR_GAMEKEY_NOT,
		ATTR_GAMEKEY_LVR_ST,	//�ȍ~GAME_KEY_LEVER_NUM�����Z
		ATTR_GAMEKEY_BTN_ST,	//�ȍ~GAME_KEY_BUTTON_NUM�����Z
	};

	//�u�����`�̃A�g���r���[�g��
	enum
	{
		ATTR_BRANCH_NAME,
		ATTR_BRANCH_CONDITION,
		ATTR_BRANCH_COMMAND_NAME,
		ATTR_BRANCH_COMMAND_ID,
		ATTR_BRANCH_SEQUENCE_NAME,
		ATTR_BRANCH_SEQUENCE_ID,
		ATTR_BRANCH_FRAME_INDEX,
	};


}	//namespace GAME


