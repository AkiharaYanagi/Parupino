//=================================================================================================
//
//	FtgMain �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "Fighting.h"
#include "../Menu/PauseMenu.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class FtgMain : public Scene, public enable_shared_from_this < FtgMain >
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

		//�|�[�Y���j��
		P_PauseMenu		m_pauseMenu;

		//���[�h��
		P_PrmRect		m_rectLoad;
		UINT			m_wait;
		P_GrpStr		m_NowLoading;

	public:
		FtgMain ();
		FtgMain ( const FtgMain & rhs ) = delete;
		~FtgMain ();

		void Load ();
		void ParamInit ();
		void Move ();

		//--------------------------
		//��ԑJ��
		P_GameScene Transit ();

		//--------------------------

		//�������� �v���C��/CPU �ݒ�
		void Set_1P_vs_2P () { m_fighting->Set_1P_vs_2P (); }
		void Set_1P_vs_CPU () { m_fighting->Set_1P_vs_CPU (); }
		void Set_CPU_vs_CPU () { m_fighting->Set_CPU_vs_CPU (); }
	};

	using P_FtgMain = std::shared_ptr < FtgMain >;


}	//namespace GAME


