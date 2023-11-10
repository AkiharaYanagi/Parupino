//=================================================================================================
//
//	Chara_Const �w�b�_�t�@�C��
//		Chara���ʒ�`
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

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

	//�������p
	enum
	{
		NO_ACTION = 0xFFFF0001,		//�����p�t���O
	};


}	//namespace GAME


