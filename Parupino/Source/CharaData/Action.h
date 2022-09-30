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
#include "Game.h"
#include "../GameMain/GameConst.h"
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
		tstring				m_name;			//���O
		UINT				m_cost;			//����R�X�g
		ACTION_CATEGORY		m_category;		//�A�N�V��������
		ACTION_POSTURE		m_posture;		//�A�N�V�����̐�

	public:
		Action ();
		Action ( const Action & rhs ) = delete;
		~Action ();

		//���O
		void SetName ( tstring name ) { m_name.assign ( name ); }
		tstring GetName () const { return m_name; }
		bool IsName ( tstring name ) const { return m_name == name; }

		//�A�N�V��������
		ACTION_CATEGORY GetCategory () const { return m_category; }
		void SetCategory ( ACTION_CATEGORY category ) { m_category = category; }

		//�A�N�V�����̐�
		ACTION_POSTURE GetPosture () const { return m_posture; }
		void SetPosture ( ACTION_POSTURE posture ) { m_posture = posture; }

		int GetBalance () { return 0; }
};

	using P_Action = shared_ptr < Action >;
	using VP_Action = vector < P_Action >;
	using PVP_Action = shared_ptr < VP_Action >;


}	//namespace GAME


