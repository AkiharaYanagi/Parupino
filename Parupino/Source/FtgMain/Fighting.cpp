//=================================================================================================
//
//	Fighting �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Fighting.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Fighting::Fighting ()
	{
		//�i���������ʃp�����[�^�V���O���g������
		G_Ftg::Create ();

		//------------------------------------------------
		//�w�i
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "ftgmain_bg1.png" ) );
		m_bg->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg->SetSpritePosition ( VEC3 ( 0, 0, Z_BG ) );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		m_bg_blackout = make_shared < GrpAcv > ();
		m_bg_blackout->AddTexture ( _T ( "ftgmain_bg_black.png" ) );
		m_bg_blackout->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_blackout->SetSpritePosition ( VEC3 ( 0, 0, Z_BG ) );
		m_bg_blackout->SetValid ( false );
		AddpTask ( m_bg_blackout );
		GRPLST_INSERT_MAIN ( m_bg_blackout );

		//�Q�[�W�g
		m_gauge_frame = make_shared < GrpAcv > ();
		m_gauge_frame->AddTexture ( _T ( "gauge_frame.png" ) );
		m_gauge_frame->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		AddpTask ( m_gauge_frame );
		GRPLST_INSERT_MAIN ( m_gauge_frame );

		//BG�^�C�}
		m_bgTimer = make_shared < Timer > ();
		AddpTask ( m_bgTimer );

		//------------------------------------------------

		//=====================================================
		//�L�������ݏ���
		//=====================================================
		m_mutualChara = make_shared < MutualChara > ();
		AddpTask ( m_mutualChara );

		//=====================================================
		//�f��
//		m_demoActor = make_shared < FtgDemoActor > ();
//		m_demoActor->Load ();
//		m_demoActor->SetpMutualChara ( m_mutualChara );

		//=====================================================

		//�|�[�Y
		m_pause = make_shared < GrpAcv > ();
		m_pause->AddTexture ( _T ( "Pause.png" ) );
		m_pause->SetPos ( (1280-512)*0.5, 480.f );
		m_pause->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT_MAIN ( m_pause );
		m_pause->SetValid ( false );
	}

	Fighting::~Fighting ()
	{
	}


	void Fighting::ParamInit ( P_Param pParam )
	{
		m_mutualChara->ParamInit ( pParam );
	}

	void Fighting::Init ()
	{
		SOUND->Stop ( BGM_Main );
		SOUND->PlayLoop ( BGM_Main );
		m_pause->SetValid ( false );

		TASK_LST::Init ();

		//Debug�p�@�J�n�f�����X�L�b�v�ؑ�
#define DEMO_ON 0
#if DEMO_ON
		m_demoActor->StartGreeting ();
#else
//		m_demoActor->StartFighting ();
#endif // DEMO_ON
	}


	void Fighting::Move ()
	{
		//--------------------------
		//�|�[�Y
		Pause ();

		//--------------------------
		//�f������
//		m_demoActor->Do ();

		//--------------------------
		//���ҏ���
		m_mutualChara->Conduct ();

		//--------------------------
		//���ʃO���t�B�b�N����
		Grp ();

		//--------------------------
		TASK_LST::Move ();
	}

#if 0
	//��ԑJ��
	P_GameScene Fighting::Transit ()
	{
#if 0
		//ESC�Ŗ߂�
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}
#endif // 0

		//�퓬�I����
#if 0
		if ( FS_END == G_FTG_STATE () )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}
#endif // 0

		//�ʏ펞
//		return shared_from_this ();
	}
#endif // 0
	

	//=============================================================
	//	�����֐�
	//=============================================================
	void Fighting::Pause ()
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

	//���ʃO���t�B�b�N����
	void Fighting::Grp ()
	{
		UINT blackOut = 0;

		//�Ó]
		if ( ! m_bgTimer->IsActive () )
		{
//			blackOut = m_mutualChara->GetBlackOut ();
			//����
			if ( 0 < blackOut )
			{
				m_bgTimer->SetTargetTime ( blackOut );
				m_bgTimer->Start ();

				blackOut = 0;
//				m_mutualChara->SetBlackOut ( 0 );

				m_bg->SetValid ( false );
				m_bg_blackout->SetValid ( true );
			}
		}

		if ( m_bgTimer->IsLast () )
		{
			m_bgTimer->Stop ();
			m_bgTimer->Reset ();
			m_bg->SetValid ( true );
			m_bg_blackout->SetValid ( false );
		}

		//�w�i�ʒu�␳
		m_bg->SetPos ( G_BASE_POS ().x, (float)BG_POS_Y );
	}


}	//namespace GAME

