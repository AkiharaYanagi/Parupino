//=================================================================================================
//
//	Demo �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgMain/FtgConst.h"	
#include "../FtgMain/MutualChara.h"
#include "../GameMain/Scene.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Demo : public Scene
	{
		P_GrpAcv		m_bg;			//�w�i
		P_GrpAcv		m_training;		//�g���[�j���O�\��

		//��ʌŒ�V�X�e���\��
		//�Q�[�W�g
		P_GrpAcv		m_gauge_frame;

		//�L�������ݏ���
		P_MutualChara	m_mutualChara;

		//�|�[�Y
		P_GrpAcv		m_pause;

	public:
		Demo ();
		Demo ( const Demo & rhs ) = delete;
		~Demo ();

		void ParamInit ();
		void Init ();
		void Move ();

		P_GameScene Transit ();

	private:
		void Pause ();
	};


}	//namespace GAME


