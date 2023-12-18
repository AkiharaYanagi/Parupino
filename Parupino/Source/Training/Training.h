//=================================================================================================
//
//	Training �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "../FtgMain/Fighting.h"
//#include "../Menu/PauseMenu.h"
#include "Training_Menu.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Training : public Scene, public enable_shared_from_this < Training >
	{
		//�퓬
		P_FTG			m_fighting;

		//�g���[�j���O�\��
		P_GrpAcv		m_training;
		P_GrpAcv		m_keyIntro;

		//���[�h��
		P_PrmRect		m_rectLoad;
		UINT			m_wait;
		P_GrpStr		m_NowLoading;

		//�|�[�Y���j��
//		P_PauseMenu		m_pauseMenu;
		P_Training_Menu		m_pauseMenu;

		static const float	BX;
		static const float	BY;
		static const float	BX_KI;
		static const float	BY_KI;

	public:
		Training ();
		Training ( const Training & rhs ) = delete;
		~Training ();

		void ParamInit ();
		void Load ();
		void Init ();
		void Move ();

		P_GameScene Transit ();
	};


}	//namespace GAME


