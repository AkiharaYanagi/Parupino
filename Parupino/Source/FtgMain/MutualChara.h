//=================================================================================================
//
//	MutualChara �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "G_Ftg.h"
#include "FtgConst.h"	
#include "../GameMain/Param.h"
#include "../ExeChara/ExeChara.h"
#include "Decision.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class MutualChara : public TASK_VEC
	{
		//�L����
		P_ExeChara		m_exeChara1;
		P_ExeChara		m_exeChara2;

		//�V�[�����L�p�����[�^
		P_Param		m_pParam;

		//����N���X
		P_Decision	m_decision;

		//-------------------------------------------------
		//�t�@�C�e�B���O�F1p2p���ʃX�N���v�g����
		UINT	m_scpStop;		//�X�N���v�g����̃X�g�b�v
		P_Timer	m_tmrHitstop;		//�q�b�g�X�g�b�v

		//�Ó]�E�F�C�g
		UINT	m_blackOut;		//�Ó]

		//����
		WINNER	m_winner;

	public:
		MutualChara ();
		MutualChara ( const MutualChara & rhs ) = delete;
		~MutualChara ();

		void ParamInit ( P_Param pParam );
		void Init ();

		//�X�N���v�g�̖��t���[������
		void Conduct ();
		void Collision ();		//�d�Ȃ蔻��
		void _Decision ();		//�U������
		void Grp ();			//�O���t�B�b�N����

		//��ԕύX
		void StartGreeting ();		//�J�n�f��
		void StartGetReady ();		//�J�n����
		void StartFighting ();		//�퓬�J�n

		bool CheckZeroLife ();	//�i���I������

		UINT GetBlackOut () const { return m_blackOut; };	//�Ó]
		void SetBlackOut ( UINT i )
		{
			m_blackOut = i;
			m_exeChara1->SetBlackOut ( i );
			m_exeChara2->SetBlackOut ( i );
		};

		UINT GetScpStop () const { return m_scpStop; };	//��~
		void SetScpStop ( UINT i ) { m_scpStop = i; };

		//�g���[�j���O���[�h������
		void TrainingInit ();

		
		//�������� �v���C��/CPU �ݒ�
		void Set_1P_vs_2P ();
		void Set_1P_vs_CPU ();
		void Set_CPU_vs_CPU ();


		//����
		WINNER GetWinner () const { return m_winner; }
		CHARA_NAME GetWinnerName () const;

	private:
		//------------------------------------------------------
		//	�����֐�
		//------------------------------------------------------

		//�g�\���ؑ�
		void SwitchRect ();

		//2P��CPU����ؑ�
		void SwithcCPU ();

		//����������
		void ResetMatch ();

		//�����������ǂ���
		bool LeaveDir ( bool dirRight, float pos0, float pos1 );
	};

	using P_MutualChara = std::shared_ptr < MutualChara >;


}	//namespace GAME


