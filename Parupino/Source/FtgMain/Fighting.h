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
		P_FtgDemoActor		m_demoActor;

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

	private:
		void Pause ();

		//���ʃO���t�B�b�N����
		void Grp ();
	};

	using P_FTG = shared_ptr < Fighting >;


}	//namespace GAME


