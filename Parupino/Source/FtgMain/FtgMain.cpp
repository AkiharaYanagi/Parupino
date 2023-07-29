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
	{
		m_fighting = make_shared < Fighting > ();
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ();
	}

	void FtgMain::Init ()
	{
		m_fighting->Init ();
		Scene::Init ();
	}


	void FtgMain::Move ()
	{
		m_fighting->Move ();
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
	
	void FtgMain::SetpParam ( P_GameParam && pParam )
	{
		P_Param		p = pParam;
		Scene::SetpParam ( p );
		m_fighting->SetpParam ( GetpParam () );
	}

}	//namespace GAME

