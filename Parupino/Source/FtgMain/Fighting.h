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
	class Fighting : public Scene
	{
		//�w�i
		P_GrpAcv		m_bg;
		P_GrpAcv		m_bg_blackout;

		P_Timer			m_bgTimer;

		//��ʌŒ�V�X�e���\��
		//�Q�[�W�g
		P_GrpAcv		m_gauge_frame;

		//�L�������ݏ���
		P_MutualChara	m_mutualChara;

		//=====================================================
#if 0
		//---------------------------------------
		//�f��
		P_GrpDemo		m_demo_GetReady;
		P_GrpDemo		m_demo_Attack;
		P_GrpDemo		m_demo_Down;
		P_GrpDemo		m_demo_Winner;

		//---------------------------------------
		//�f���I�u�W�F�N�g
		P_FTG_DM_GetReady	m_demoGetReady;
		P_FTG_DM_Attack		m_demoAttack;
		P_FTG_DM_Main		m_demoMain;
		P_FTG_DM_Down		m_demoDown;
		P_FTG_DM_Winner		m_demoWinner;

		//�I���f��
		P_FtgDemo			m_demo;

		//���ʃp�����[�^
		P_PRM_FTG_DEMO		m_prmDemo;
#endif // 0

		//---------------------------------------
		P_FtgDemoActor		m_demoActor;

		//=====================================================

		//�|�[�Y
		P_GrpAcv		m_pause;

	public:
		Fighting ();
		Fighting ( const Fighting & rhs ) = delete;
		~Fighting ();

		void ParamInit ();
		void Init ();
		void Move ();

		P_GameScene Transit ();

	private:
		void MakeGrpDemo ( P_GrpDemo & pGrp, LPCTSTR txName );
		void SetGrpDemo ( P_GrpDemo pGrp );
		void StartGrpDemo ( P_GrpDemo pGrp, UINT time );

		void Pause ();

		//���ʃO���t�B�b�N����
		void Grp ();
	};


}	//namespace GAME


