//=================================================================================================
//
// CPUInput �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "CharaInput.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�O���錾
	class ExeChara;
	using P_ExeChara = std::shared_ptr < ExeChara >;
	using WP_ExeChara = weak_ptr < ExeChara >;

	class CPUInput : public CharaInput
	{
		const UINT		m_vGameKeyNum;		//�L�[���͂̕ۑ��t���[����
		V_GAME_KEY		m_vGameKey;			//�L�[���͕ۑ�
		PLAYER_ID		m_playerID;			//�v���C���[ID
		WP_ExeChara		m_pExeChara;		//���g�̎Q��
		WP_ExeChara		m_pExeCharaOther;	//����̎Q��

		//CPU�s�����
		enum CPU_ACT
		{
			CPU_NEUTRAL = 0,
			CPU_FRONT = 1,
			CPU_BACK = 2,
			CPU_FRONT_DASH = 3,
			CPU_BACK_DASH = 4,
			CPU_L = 5,
			CPU_M = 6,
			CPU_H = 7,
			CPU_AVOID = 8,
			CPU_POISED = 9,
			CPU_ACT_NUM = 10,
		};
		CPU_ACT		m_randomKeyNear	[ CENT ];		//�ߋ���
		CPU_ACT		m_randomKeyMiddle [ CENT ];		//������
		CPU_ACT		m_randomKeyFar [ CENT ];		//������

		bool		m_bAct;		//�s�������
		CPU_ACT		m_act;
		UINT		m_timer;
		UINT		m_actTime;

		int m_testAct;

		//�O���Ǎ�
		int			m_actNear[ CPU_ACT_NUM ];
		int			m_actMiddle[ CPU_ACT_NUM ];
		int			m_actFar[ CPU_ACT_NUM ];


	public:
		CPUInput ( WP_ExeChara p, WP_ExeChara pOther );
		CPUInput ( const CPUInput & rhs ) = delete;
		~CPUInput ();

		//�ݒ�
		void SetPlayer ( PLAYER_ID id ) { m_playerID = id; }
//		void SetpExeChara ( WP_ExeChara p ) { m_pExeChara = p; }
//		void SetpExeCharaOther ( WP_ExeChara p ) { m_pExeCharaOther = p; }

		//�t���[�����̍X�V
		void Update ( bool dirRight );

		//�u�����`���X�g���`�F�b�N����
		//�R�}���h�������B������Ă�����J�ڐ�̃A�N�V����ID��Ԃ�
		UINT GetTransitID ( PVP_Branch pvpBranch, bool dirRight );

		void SetCPU_Act ( int index, int act[], CPU_ACT cpu_act[] );

	};


}	//namespace GAME


