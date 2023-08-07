//=================================================================================================
//
//	Demo �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DemoMain.h"
#include "../FtgMain/FtgMain.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DemoMain::DemoMain ()
	{
		//���j��
		m_menu = make_shared < DemoMenu > ();
		AddpTask ( m_menu );

		//�퓬
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );

	}

	DemoMain::~DemoMain ()
	{
	}

	void DemoMain::ParamInit ()
	{
		P_Param pParam = GetpParam ();
		GameSettingFile stg = pParam->GetGameSetting ();
		stg.SetPlayerMode1p ( MODE_CPU );
		stg.SetPlayerMode2p ( MODE_CPU );
		pParam->SetSettingFile ( stg );

		m_fighting->ParamInit ( pParam );

		//�R���X�g���N�^��
//		m_scene = shared_from_this ();
		m_scene = nullptr;
	}

	P_GameScene DemoMain::Transit ()
	{
#if 0
		//ESC�Ŗ߂�
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}
#endif // 0

		//�J�ڐ��Ԃ��i�ʏ펞�͎��g�j
		return shared_from_this ();
//		return m_scene;
	}


	void DemoMain::Pause ()
	{
		//F1�Ń|�[�Y�ؑ�
		if ( ::GetAsyncKeyState ( VK_F1 ) & 0x0001 )
		{
			if ( m_pause->GetValid () )	//On->Off
			{
				m_pause->SetValid ( false );
//				m_mutualChara->Stop ( false );
			}
			else	//Off->On
			{
				m_pause->SetValid ( true );
//				m_mutualChara->Stop ( true );
			}
		}
	}

	void DemoMain::To_1v2 ()
	{
		//@todo �V�[���̃|�C���^���ǂ����������߂�

//		P_GameScene pScene = nullptr;
		pScene = make_shared < FtgMain > ();
		m_scene = pScene;

//		m_scene = make_shared < Scene > ();

//		m_scene = make_shared < FtgMain > ();

//		m_scene = make_shared < FtgMain > ();

//		auto p = make_shared < FtgMain > ();
//		m_scene = dynamic_pointer_cast < Scene > ( p );
	}


}	//namespace GAME

