//=================================================================================================
//
//	Fighting �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "FtgConst.h"	
#include "MutualChara.h"
#include "../GameMain/Scene.h"
#include "FtgDemo.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Fighting : public TASK_LST
	{
		//�w�i
		P_GrpAcv		m_bg;
		P_GrpAcv		m_bg_blackout;

		//�L�������ݏ���
		P_MutualChara	m_mutualChara;

		//��ʌŒ�V�X�e���\��
		//�Q�[�W�g
		P_GrpAcv		m_gauge_frame;

		//=====================================================
		//�f��
		P_FtgDemoActor	m_demoActor;
		bool			m_demoSkip;	//�X�L�b�v

		//=====================================================

		//�Ó]
		P_Timer			m_tmrBlackOut;

		//�|�[�Y
		P_GrpAcv		m_pause;

	public:
		Fighting ();
		Fighting ( const Fighting & rhs ) = delete;
		~Fighting ();

		void Init ();
		void Move ();

		void ParamInit ( P_Param pParam );

		bool IsEnd () const { return m_demoActor->IsEnd (); }

		//�������� �v���C��/CPU �ݒ�
		void Set_1P_vs_2P () { m_mutualChara->Set_1P_vs_2P (); }
		void Set_1P_vs_CPU () { m_mutualChara->Set_1P_vs_CPU (); }
		void Set_CPU_vs_CPU () { m_mutualChara->Set_CPU_vs_CPU (); }

		//�����f���X�L�b�v�ݒ�
		void SetDemoOn () { m_demoSkip = F; }
		void SetDemoSkip () { m_demoSkip = T; }

		//�g���[�j���O�p���X�^�[�g
		void TrainingRestart ();

	private:
		void Pause ();

		//���ʃO���t�B�b�N����
		void Grp ();
	};

	using P_FTG = std::shared_ptr < Fighting >;


}	//namespace GAME


