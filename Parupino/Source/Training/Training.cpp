//=================================================================================================
//
//	Training �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Training.h"
#include "../Title/Title.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Training::Training ()
	{
		//�i���������ʃp�����[�^�V���O���g������
		G_Ftg::Create ();

		//�w�i
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "ftgmain_bg1.png" ) );
		m_bg->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg->SetSpritePosition ( VEC3 ( 0, 0, Z_BG ) );
		GRPLST_INSERT ( m_bg );

		//�L�������ݏ���
		m_mutualChara = make_shared < MutualChara > ();
		AddpTask ( m_mutualChara );

		//�Q�[�W�g
		m_gauge_frame = make_shared < GrpAcv > ();
		m_gauge_frame->AddTexture ( _T ( "gauge_frame.png" ) );
		m_gauge_frame->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT ( m_gauge_frame );

		//�g���[�j���O�\��
		m_training = make_shared < GrpAcv > ();
		m_training->AddTexture ( _T ( "training.png" ) );
		m_training->SetPos ( (1280 - 256) * 0.5f, 70.f );
		m_training->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT ( m_training );

		//�|�[�Y
		m_pause = make_shared < GrpAcv > ();
		m_pause->AddTexture ( _T ( "Pause.png" ) );
		m_pause->SetPos ( (1280 - 512)*0.5, 480.f );
		m_pause->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT ( m_pause );
		m_pause->SetValid ( false );
	}

	Training::~Training ()
	{
	}

	void Training::ParamInit ()
	{
		m_mutualChara->ParamInit ( GetpParam () );
	}

	void Training::Init ()
	{
		SOUND->Stop ( BGM_Main );
		SOUND->PlayLoop ( BGM_Main );
		m_pause->SetValid ( false );

		//�f�����΂��ăQ�[���J�n
#if 0
		G_FTG_STATE_SET ( FS_GAME_MAIN );
		m_mutualChara->Wait ( false );
		Scene::Init ();
		m_mutualChara->SetMain ();
#endif // 0

		m_pause->SetValid ( false );

		Scene::Init ();
	}

	void Training::Move ()
	{
		Pause ();

		// �i���I������
		if ( m_mutualChara->CheckZeroLife () )
		{
			//���Z�b�g
			Init ();
		}
		
		//���ҏ���
		m_mutualChara->Conduct ();

		//�w�i�ʒu�␳
		m_bg->SetPos ( G_BASE_POS ().x, (float)BG_POS_Y );

		Scene::Move ();
	}

	P_GameScene Training::Transit ()
	{
		//ESC�Ŗ߂�
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		{
			SOUND->Stop ( BGM_Main );
//			return make_shared < Title > ();

			GRPLST_CLEAR ();
			P_GameScene p = make_shared < Title > ();
			GRPLST_LOAD ();
			GRPLST_INIT ();
			return p;
		}

		//�퓬�I����
#if 0
		if ( FS_END == G_FTG_STATE () )
		{
			SOUND->Stop ( BGM_Main );
			return make_shared < Title > ();
		}
#endif // 0

		//�ʏ펞
		return shared_from_this ();
	}


	void Training::Pause ()
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


}	//namespace GAME

