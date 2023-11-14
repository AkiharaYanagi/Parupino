//=================================================================================================
//
//	Action �w�b�_�t�@�C��
//		�X�N���v�g�̈�A�A�ŗL�̒l��ǉ�
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Chara_Const.h"
#include "Sequence.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//==================================================================================
	//	���A�N�V��������
	//		STAND, MOVE, DASH, ATTACK_L, ATTACK_M, ATTACK_H, CLANG, AVOID, DOTTY, DAMAGED, DEMO, OTHER
	//
	//==================================================================================

	//================================================================
	//	�A�N�V����		�e�t���[���̃X�N���v�g���X�g������
	//		��[]�X�N���v�g
	//		�����A�N�V����
	//		������o�����X�l
	//		���A�N�V�����̐�
	//		���A�N�V��������
	//================================================================
	
	class Action : public Sequence
	{
		ACTION_CATEGORY		m_category;		//�A�N�V��������
		ACTION_POSTURE		m_posture;		//�A�N�V�����̐�
		UINT				m_hitNum;		//�q�b�g��
		UINT				m_hitPitch;		//�q�b�g�Ԋu
		int					m_balance;		//�o�����X�l

	public:
		Action ();
		Action ( const Action & rhs ) = delete;
		~Action ();

		//�A�N�V��������
		ACTION_CATEGORY GetCategory () const { return m_category; }
		void SetCategory ( ACTION_CATEGORY category ) { m_category = category; }

		//�A�N�V�����̐�
		ACTION_POSTURE GetPosture () const { return m_posture; }
		void SetPosture ( ACTION_POSTURE posture ) { m_posture = posture; }

		//�q�b�g��
		UINT GetHitNum () const { return m_hitNum; }
		void SetHitNum ( UINT n ) { m_hitNum = n; }

		//�q�b�g�Ԋu
		UINT GetHitPitch () const { return m_hitPitch; }
		void SetHitPitch ( UINT n ) { m_hitPitch = n; }

		//�o�����X�l
		int GetBalance () { return m_balance; }
		void SetBalance ( int i ) { m_balance = i; }
};

	using P_Action = std::shared_ptr < Action >;
	using VP_Action = std::vector < P_Action >;
	using PVP_Action = std::shared_ptr < VP_Action >;


}	//namespace GAME


