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
#include "Ef/EfClang.h"
#include "Ef/EfSpark.h"
#include "Ef/EfParticle.h"
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

		//���ʃG�t�F�N�g
		P_EfClang		m_efClang;
		P_EfSpark		m_efSpark;

		//���q
		P_EEfParticle	m_efParticle;
	
		//�J�n�E�F�C�g
		UINT	m_startTimer;
		UINT	m_startTime;
		P_Timer	m_tmrStartWait;

		//�I���E�F�C�g
		UINT	m_endTimer;
		UINT	m_endTime;
		P_Timer	m_tmrEndWait;

		//�Ó]
		UINT	m_blackOut;

		//�X�N���v�g����̃X�g�b�v
		UINT	m_scpStop;

		//�q�b�g�X�g�b�v
		P_Timer	m_tmrHitstop;

		//����
		WINNER	m_winner;


		//����N���X
		Decision	m_decision;


	public:
		MutualChara ();
		MutualChara ( const MutualChara & rhs ) = delete;
		~MutualChara ();

		void ParamInit ( P_Param pParam );

		//�X�N���v�g�̖��t���[������
		void Conduct ();

		void Collision ();		//�d�Ȃ蔻��
		void Decision ();		//�U������

		void Grp ();			//�O���t�B�b�N����


		//��ԕύX
		void SetReady ();
		void SetMain ();
		void Wait ( bool b );
		void Stop ( bool b );
		void EndAct ();
		bool CheckZeroLife ();	//�i���I������
		bool CheckDown ();		//�_�E������
		void SetEndWait ();
		bool CheckDownEnd ();	//�_�E����ԏI������
		bool CheckWin ();		//������Ԕ���
		bool CheckWinEnd ();	//�����I����Ԕ���
		bool CheckWinner ();	//����������
		void ForcedEnd ();	//�����I��

		UINT GetBlackOut () const { return m_blackOut; };	//�Ó]
		void SetBlackOut ( UINT i ) { m_blackOut = i; };

		UINT GetScpStop () const { return m_scpStop; };	//��~
		void SetScpStop ( UINT i ) { m_scpStop = i; };

		void SetCharaState ( CHARA_STATE chst );

		//����
		WINNER GetWinner () const { return m_winner; }
		CHARA_NAME GetWinnerName () const;

	private:
		//------------------------------------------------------
		//	�����֐�
		//------------------------------------------------------


		//�g�\���ؑ�
		void SwitchRect ();
	};

	using P_MutualChara = shared_ptr < MutualChara >;


}	//namespace GAME


