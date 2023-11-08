//=================================================================================================
//
//	Training �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Training.h"
#include "../Title_Intro/Title_Intro.h"
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�萔
	const float Training::BX = ( 1280 - 256 ) * 0.5f;
	const float Training::BY = 170.f;


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

#if 0
		//�|�[�Y
		m_pause = make_shared < GrpAcv > ();
		m_pause->AddTexture ( _T ( "Pause.png" ) );
		m_pause->SetPos ( (1280 - 512)*0.5, 480.f );
		m_pause->SetSpritePosition ( VEC3 ( 0, 0, Z_SYS ) );
		GRPLST_INSERT_MAIN ( m_pause );
		m_pause->SetValid ( false );

#endif // 0

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
		SOUND->Stop_BGM ( BGM_Main );
		SOUND->Play_Loop_BGM ( BGM_Main );

		//Transit�p��this��ۑ�
		mwp_This = shared_from_this ();

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

		//�g���[�j���O���Z�b�g
		if ( CFG_PUSH_KEY ( _P1_BTN6 ) || CFG_PUSH_KEY ( _P2_BTN6 ) )
		{
			m_fighting->TrainingRestart ();
		}

#if 0
		Pause ();
#endif // 0

		Scene::Move ();
	}

	P_GameScene Training::Transit ()
	{
		//ESC�Ŗ߂�
//		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 )
		if ( WND_UTL::AscKey ( VK_ESCAPE ) )
		{
			SOUND->Stop_BGM ( BGM_Main );
			GRPLST_CLEAR ();
			P_GameScene p = make_shared < Title_Intro > ();
			GRPLST_LOAD ();
			return p;
		}

		//���̃V�[�����m�ۂ��ꂽ�Ȃ�J�ڂ���
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//�ʏ펞
		return mwp_This.lock ();
	}

#if 0

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

#endif // 0


}	//namespace GAME

