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
		//�p�����[�^�蓮�w��
		P_Param pParam = GetpParam ();
		GameSettingFile stg = pParam->GetGameSetting ();
		stg.SetPlayerMode1p ( MODE_CPU );
		stg.SetPlayerMode2p ( MODE_CPU );
		pParam->SetSettingFile ( stg );

		m_fighting->ParamInit ( pParam );


		//�R���X�g���N�^�� shared_from_this ()
		m_scene = shared_from_this ();
		m_menu->ParamInit ( shared_from_this () );
	}

	P_GameScene DemoMain::Transit ()
	{
		//@info MenuItem��this��n���Ă���
#if 0
		//ESC�Ŗ߂�
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}
#endif // 0

		//�J�ڐ��Ԃ��i�ʏ펞�͎��g�j
//		return shared_from_this ();
		return m_scene;
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
		GRPLST_CLEAR ();
		m_scene = make_shared < FtgMain > ();
		GRPLST_LOAD ();
//		GRPLST_INIT ();
	}

	void DemoMain::To_1vC ()
	{
		m_scene = make_shared < FtgMain > ();
	}

	void DemoMain::To_Cv2 ()
	{
		m_scene = make_shared < FtgMain > ();
	}

	void DemoMain::To_CvC ()
	{
		m_scene = make_shared < FtgMain > ();
	}


}	//namespace GAME

