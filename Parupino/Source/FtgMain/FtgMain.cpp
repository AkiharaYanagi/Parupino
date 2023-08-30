//=================================================================================================
//
//	FtgMain �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
		: m_menu ( F )
	{
		//�퓬
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );

		//�|�[�Y���j��
//		m_pauseMenu = make_shared < PauseMenu > ();
//		AddpTask ( m_pauseMenu );
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}

	void FtgMain::Init ()
	{
		m_menu = F;
		Scene::Init ();
	}


	void FtgMain::Move ()
	{
		if ( CFG_PUSH_KEY ( _P1_BTN5 ) )
		{
			m_menu = T;
		}


		if ( m_menu )
		{
			return;
		}

		Scene::Move ();
	}


	//��ԑJ��
	P_GameScene FtgMain::Transit ()
	{
		//ESC�Ŗ߂�
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
//			return make_shared < Title > ();
		}

		//�ʏ펞
		return shared_from_this ();
	}
	
}	//namespace GAME

