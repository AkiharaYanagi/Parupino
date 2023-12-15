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
#include "../FtgMain/Menu/PauseMenu.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Training : public Scene, public enable_shared_from_this < Training >
	{
#if 0
		//===========================================================
		//�J�ڐ�V�[���|�C���^
		//@info	this�����g�ɕۑ�����Əz�Q�ƂƂȂ�̂�weak_ptr��p����
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//�J�ډ\�Ȏ��̃V�[��
		//===========================================================
#endif // 0

		//�퓬
		P_FTG			m_fighting;

		P_GrpAcv		m_training;		//�g���[�j���O�\��

		//���[�h��
		P_PrmRect		m_rectLoad;
		UINT			m_wait;
		P_GrpStr		m_NowLoading;

		//�|�[�Y���j��
		P_PauseMenu		m_pauseMenu;

		static const float	BX;
		static const float	BY;

	public:
		Training ();
		Training ( const Training & rhs ) = delete;
		~Training ();

		void ParamInit ();
		void Load ();
		void Init ();
		void Move ();

		P_GameScene Transit ();

	private:
//		void Pause ();
	};


}	//namespace GAME


