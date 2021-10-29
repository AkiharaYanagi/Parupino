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

		//�f��
		P_GrpDemo		m_demo_GetReady;
		P_GrpDemo		m_demo_Attack;
		P_GrpDemo		m_demo_Down;
		P_GrpDemo		m_demo_Winner;
		P_GrpDemo		m_demo_SONIA;
		P_GrpDemo		m_demo_ORFLOAT;

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


