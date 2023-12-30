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
#include <array>


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�O���錾
	class ExeChara;
	using P_ExeChara = std::shared_ptr < ExeChara >;
	using WP_ExeChara = weak_ptr < ExeChara >;

	//CPU�s�����
	enum CPU_ACT
	{
		CPU_NEUTRAL = 0,
		CPU_FRONT = 1,
		CPU_BACK = 2,
		CPU_FRONT_DASH = 3,
		CPU_BACK_DASH = 4,
		CPU_L = 5,
		CPU_Ma = 6,
		CPU_Mb = 7,
		CPU_H = 8,
		CPU_POISED = 9,
		CPU_ACT_NUM = 10,
	};
	using ARY_CPU_ACT = std::array < CPU_ACT, CENT >;
	using ARY_INT = std::array < int, CPU_ACT_NUM >;


	//-------
	class CPUInput : public CharaInput
	{
		const UINT		m_vGameKeyNum;		//�L�[���͂̕ۑ��t���[����
		V_GAME_KEY		m_vGameKey;			//�L�[���͕ۑ�
		PLAYER_ID		m_playerID;			//�v���C���[ID
		WP_ExeChara		m_pExeChara;		//���g�̎Q��
		WP_ExeChara		m_pExeCharaOther;	//����̎Q��

		ARY_CPU_ACT		m_randomKeyNear;	//�ߋ���
		ARY_CPU_ACT		m_randomKeyMiddle;	//������
		ARY_CPU_ACT		m_randomKeyFar;		//������

		bool		m_bAct;		//�s�������
		CPU_ACT		m_act;
		UINT		m_timer;
		UINT		m_actTime;

		int m_testAct;

		//�O���Ǎ�
		ARY_INT		m_actNear;
		ARY_INT		m_actMiddle;
		ARY_INT		m_actFar;

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

		void SetCPU_Act ( int index, ARY_INT act, CPU_ACT& cpu_act );
	};


}	//namespace GAME


