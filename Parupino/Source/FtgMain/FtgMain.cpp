//=================================================================================================
//
//	FtgMain �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"
//#include "../Title/Title.h"
#include "../Title_Intro/Title_Intro.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
	{
#if 0

		//�퓬
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );

#endif // 0
		//�|�[�Y���j��
		m_pauseMenu = make_shared < PauseMenu > ();
		AddpTask ( m_pauseMenu );

		//@info �R���X�g���N�^��shared_from_this()��p���Ȃ�

	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::Load ()
	{

//		m_scene = shared_from_this ();
		m_gameScene = shared_from_this ();

#if 0
		m_pauseMenu->SetwpParent ( shared_from_this () );

#endif // 0

		Scene::Load ();
	}

	void FtgMain::ParamInit ()
	{
#if 0

		m_fighting->ParamInit ( GetpParam () );

#endif // 0
	}


	void FtgMain::Move ()
	{
#if 0
		//���j���|�[�Y�J�n
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) )
		{
			m_pauseMenu->On ();
		}

		//���j���|�[�Y��
		if ( m_pauseMenu->GetActive () )
		{
			m_pauseMenu->Move ();
		}


		//�ʏ퓮��
//		Scene::Move ();

		//�`��ɕK�v��Move()��GRPLST�ōs��

		m_fighting->Move ();	//�ʂŎ蓮
#endif // 0
		Scene::Move ();
	}


	//��ԑJ��
	P_GameScene FtgMain::Transit ()
	{
#if 0

		//ESC�Ŗ߂�
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}

#endif // 0

		//�ʏ펞
//		return shared_from_this ();
//		return m_scene;
		return m_gameScene;
	}
	

	//[�V�[���J��] �^�C�g���ɖ߂�
	void FtgMain::Transit_Title ()
	{
		GRPLST_CLEAR ();
//		P_Scene&& p = make_shared < Title > ();

//		m_gameScene = make_shared < Title > ();
		m_gameScene = make_shared < Title_Intro > ();

//		m_scene = p;
//		m_scene = make_shared < Title > ();
		GRPLST_LOAD ();
//		GRPLST_INIT ();
	}

	//���j���������ăQ�[���ɖ߂�
	void FtgMain::Resume_Fighting ()
	{
//		m_pauseMenu->Off ();
	}

}	//namespace GAME

