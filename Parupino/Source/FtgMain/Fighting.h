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
#include "MutualChara_Demo.h"
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
//		P_MutualChara_Demo	m_mutualChara_Demo;

		//=====================================================
		//�f��
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
#if 0
		void MakeGrpDemo ( P_GrpDemo & pGrp, LPCTSTR txName );
		void SetGrpDemo ( P_GrpDemo pGrp );
		void StartGrpDemo ( P_GrpDemo pGrp, UINT time );
#endif // 0

		void Pause ();

		//���ʃO���t�B�b�N����
		void Grp ();
	};


}	//namespace GAME


