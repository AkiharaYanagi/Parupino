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
#include "Game.h"
#include "../Chara.h"

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
		EL_COMMAND			,
	};

	//-------------------------------------------
	//�A�N�V�������̃A�g���r���[�g
	enum ATTR_ACTION
	{
		ATTR_ACTION_NAME		, 
		ATTR_ACTION_NEXT		, 
		ATTR_ACTION_CATEGORY	,
		ATTR_ACTION_POSTURE		,
		ATTR_ACTION_BALANCE		, 
	};

	//-------------------------------------------
	//�X�N���v�g���̃A�g���r���[�g
	enum ATTR_SCRIPT
	{
		ATTR_SCRIPT_GROUP,
		ATTR_SCRIPT_IMAGE_ID,
		ATTR_SCRIPT_POS_X		,
		ATTR_SCRIPT_POS_Y		, 
		ATTR_SCRIPT_VEL_X		, 
		ATTR_SCRIPT_VEL_Y		, 
		ATTR_SCRIPT_ACC_X		, 
		ATTR_SCRIPT_ACC_Y		, 
		ATTR_SCRIPT_CLCST		, 
		ATTR_SCRIPT_POWER		, 
	};

	//�X�N���v�g���̃G�������g
	enum
	{
		ELEM_SCRIPT_BRANCH, 
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
		ATTR_GAMEKEY_LVR_NUM,
		ATTR_GAMEKEY_LVR_ST,
		ATTR_GAMEKEY_BTN_ST,	//�ȍ~GAME_KEY_BUTTON_NUM�����Z
	};

	//�u�����`�̃A�g���r���[�g��
	enum
	{
		ATTR_BRANCH_COMMAND_INDEX, 
		ATTR_BRANCH_COMMAND_NAME, 
		ATTR_BRANCH_ACTION_INDEX, 
		ATTR_BRANCH_ACTION_NAME,
		ATTR_BRANCH_FRAME_INDEX,
	};


}	//namespace GAME


