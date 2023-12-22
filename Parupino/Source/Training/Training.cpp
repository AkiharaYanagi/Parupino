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
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�萔
	const float Training::BX = ( 1280 - 256 ) * 0.5f;
	const float Training::BY = 170.f;
	const float Training::BX_KI = ( 1280 - 512 ) * 0.5f;
	const float Training::BY_KI = 900.f;


	Training::Training ()
	{
		//�퓬
		m_fighting = make_shared < Fighting > ();
		AddpTask ( m_fighting );
	
		//�g���[�j���O�\��
		m_training = make_shared < GrpAcv > ();
		m_training->AddTexture ( _T ( "training.png" ) );
		m_training->SetPos ( BX, BY );
		m_training->SetZ ( Z_BG - 0.01f );
		AddpTask ( m_training );
		GRPLST_INSERT_MAIN ( m_training );

		m_keyIntro = make_shared < GrpAcv > ();
		m_keyIntro->AddTexture ( _T ( "TRN_keyIntro.png" ) );
		m_keyIntro->SetPos ( BX_KI, BY_KI );
		m_keyIntro->SetZ ( Z_BG - 0.01f );
		AddpTask ( m_keyIntro );
		GRPLST_INSERT_MAIN ( m_keyIntro );

		//�|�[�Y���j��
		m_pauseMenu = make_shared < Training_Menu > ();
		AddpTask ( m_pauseMenu );

		//���[�h��
		m_rectLoad = make_shared < PrmRect > ();
		m_rectLoad->SetSize ( VEC2 ( 1280, 960 ) );
		m_rectLoad->SetPos ( VEC2 ( 0, 0 ) );
		m_rectLoad->SetAllColor ( 0xff000000 );
		m_rectLoad->SetZ ( Z_FADE );
		m_rectLoad->Load ();
		m_rectLoad->Move ();
		//�J�n�l�A�ڕW�l���蓮�ݒ�
		m_rectLoad->SetFade ( 3, _CLR ( 0xff000000 ), _CLR ( 0x00000000UL ) );
		AddpTask ( m_rectLoad );
		GRPLST_INSERT_MAIN ( m_rectLoad );
		m_wait = 0;

		m_NowLoading = make_shared < GrpStr > ();
		m_NowLoading->SetStr ( _T ( "Now Loading..." ) );
		m_NowLoading->SetPos ( VEC2 ( 1000, 915 ) );
		m_NowLoading->Load ();
		m_NowLoading->Move ();
		m_NowLoading->SetZ ( Z_FADE - 0.01f );
		AddpTask ( m_NowLoading );
		GRPLST_INSERT_MAIN ( m_NowLoading );
	}

	Training::~Training ()
	{
	}

	void Training::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}

	void Training::Load ()
	{
		//�J�ڐ�w���this��ۑ�
		Scene::SetwpThis ( shared_from_this () );

		//Menu�p��this��ۑ�
		m_pauseMenu->SetwpParentScene ( shared_from_this () );

		//CPU / PLAYER
		m_fighting->Set_1P_vs_2P ();

		SOUND->Stop_BGM ( BGM_Main );
		SOUND->Play_Loop_BGM ( BGM_Main );

		Scene::Load ();
	}

	void Training::Init ()
	{
		//�f�����X�L�b�v
		m_fighting->SetDemoSkip ();

		Scene::Init ();

		//�ʏ�Init�̌�ɍs��
		m_fighting->TrainingRestart ();
	}

	void Training::Move ()
	{
		//NowLoading�I��
		if ( m_rectLoad->GetFadeTimer () == 0 )
		{
			m_NowLoading->SetValid ( F );
		}

		//���j���|�[�Y��
		if ( m_pauseMenu->MenuCheck () )
		{
			return;
		}

		//�g���[�j���O���Z�b�g
		if ( CFG_PUSH_KEY ( _P1_BTN6 ) || CFG_PUSH_KEY ( _P2_BTN6 ) )
		{
			m_fighting->TrainingRestart ();
		}

		Scene::Move ();
	}

	P_GameScene Training::Transit ()
	{
		//ESC�Ŗ߂�
		if ( WND_UTL::AscKey ( VK_ESCAPE ) )
		{
			SOUND->Stop_BGM ( BGM_Main );
			GetwpThis().lock ()->Transit_Title ();
		}

		return Scene::Transit ();
	}



}	//namespace GAME

