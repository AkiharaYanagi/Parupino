//=================================================================================================
//
//	FtgMain �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"
#include "../Title/Title.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
	{
		//�퓬
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );

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

		m_pauseMenu->SetpParent ( shared_from_this () );

		Scene::Load ();
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}


	void FtgMain::Move ()
	{

		//���j���|�[�Y��
		if ( m_pauseMenu->GetActive () )
		{
			m_pauseMenu->Move ();
			return;
		}

		//���j���|�[�Y�J�n
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) )
		{
			m_pauseMenu->On ();
			return;
		}

#if 0
		//���j���|�[�Y��
		if ( m_ynMenu->GetActive () )
		{
			m_ynMenu->Move ();
			return;
		}

		//�|�[�Y�J�n
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) )
		{
			m_ynMenu->On ();
			return;
		}
#endif // 0

		//�ʏ퓮��
		Scene::Move ();
	}


	//��ԑJ��
	P_GameScene FtgMain::Transit ()
	{
		//ESC�Ŗ߂�
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}

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
		m_gameScene = make_shared < Title > ();
//		m_scene = p;
//		m_scene = make_shared < Title > ();
		GRPLST_LOAD ();
//		GRPLST_INIT ();
	}

	//���j���������Ė߂�
	void FtgMain::Resume_Fighting ()
	{
//		m_pauseMenu->Off ();
	}

}	//namespace GAME

