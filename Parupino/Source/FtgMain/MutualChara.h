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
#include "EfClang.h"
#include "EfSpark.h"

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
	
		//�J�n�E�F�C�g
		UINT	m_startTimer;
		UINT	m_startTime;
		P_Timer	m_tmrStartWait;

		//�I���E�F�C�g
		UINT	m_endTimer;
		UINT	m_endTime;
		P_Timer	m_tmrEndWait;

		//�q�b�g�X�g�b�v
		P_Timer	m_tmrHitstop;

		//����
		WINNER m_winner;

	public:
		MutualChara ();
		MutualChara ( const MutualChara & rhs ) = delete;
		~MutualChara ();

		void ParamInit ( P_Param pParam );

		//�X�N���v�g�̖��t���[������
		void Conduct ();

		void Collision ();		//�d�Ȃ蔻��
		void Decision ();		//�U������


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

		void SetCharaState ( CHARA_STATE chst );

		//����
		WINNER GetWinner () const { return m_winner; }
		CHARA_NAME GetWinnerName () const;

	private:
		//------------------------------------------------------
		//	�����֐�
		//------------------------------------------------------

		//���E�g����(���S�t)
		bool DcsOffset ( P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center );

		//�G�t�F�N�g�̑��E�g����
		void DcsOffsetEf ( PLP_ExEf plpExEf1, PLP_ExEf plpExEf2, P_CharaRect pCharaRect2p );

		//�G�t�F�N�g�̃q�b�g�g����
		bool DcsHitEf ( PLP_ExEf plpExEf1, PV_RECT pvHRect2, P_ExeChara pHitChara, int & refPower );

		//�g�\���ؑ�
		void SwitchRect ();
	};

	using P_MutualChara = shared_ptr < MutualChara >;


}	//namespace GAME


