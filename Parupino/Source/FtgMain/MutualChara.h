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

		//�J�n�E�F�C�g
		UINT	m_startTimer;
		UINT	m_startTime;
		P_Timer	m_tmrStartWait;

		//�I���E�F�C�g
		UINT	m_endTimer;
		UINT	m_endTime;
		P_Timer	m_tmrEndWait;

		UINT	m_blackOut;		//�Ó]
		UINT	m_scpStop;		//�X�N���v�g����̃X�g�b�v
		P_Timer	m_tmrHitstop;		//�q�b�g�X�g�b�v

		//����
		WINNER	m_winner;

		//����N���X
		P_Decision	m_decision;

	public:
		MutualChara ();
		MutualChara ( const MutualChara & rhs ) = delete;
		~MutualChara ();

		void ParamInit ( P_Param pParam );

		//�X�N���v�g�̖��t���[������
		void Conduct ();
		void Collision ();		//�d�Ȃ蔻��
		void _Decision ();		//�U������
		void Grp ();			//�O���t�B�b�N����

		//��ԕύX
		void StartGreeting ();		//�J�n�f��
		void StartGetReady ();		//�J�n����
		void StartFighting ();		//�퓬�J�n

#if 0
		void SetReady ();
		void SetMain ();
		void Wait ( bool b );
		void Stop ( bool b );
		void EndAct ();
		bool CheckDown ();		//�_�E������
		void SetEndWait ();
		bool CheckDownEnd ();	//�_�E����ԏI������
		bool CheckWin ();		//������Ԕ���
		bool CheckWinEnd ();	//�����I����Ԕ���
		bool CheckWinner ();	//����������
		void ForcedEnd ();	//�����I��
#endif // 0
		bool CheckZeroLife ();	//�i���I������

		UINT GetBlackOut () const { return m_blackOut; };	//�Ó]
		void SetBlackOut ( UINT i ) { m_blackOut = i; };

		UINT GetScpStop () const { return m_scpStop; };	//��~
		void SetScpStop ( UINT i ) { m_scpStop = i; };

//		void SetCharaState ( CHARA_STATE chst );

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
	};

	using P_MutualChara = shared_ptr < MutualChara >;


}	//namespace GAME


