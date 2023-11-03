//=================================================================================================
//
//	FtgMain �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"
#include "../Title_Intro/Title_Intro.h"
#include "../Result/Result.h"


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

		//���[�h��
//		m_rectLoad = make_shared < PrmRect > ();
		m_rectLoad = make_shared < TestDraw > ();
		m_rectLoad->SetSize ( VEC2 ( 1280, 960 ) );
		m_rectLoad->SetPos ( VEC2 ( 0, 0 ) );
		m_rectLoad->SetAllColor ( 0xff000000 );
		m_rectLoad->SetZ ( Z_FADE );

		m_rectLoad->Load ();
		m_rectLoad->Move ();

//		m_rectLoad->SetFadeOut ( 10 );	//SetFadeOut()��0xffffffff->0x00ffffff�Ȃ̂Ŕ����Ȃ�
		m_rectLoad->SetFade ( 3, _CLR(0xff000000), _CLR(0x00000000UL) );	//�J�n�l�A�ڕW�l���蓮�ݒ�

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


		//----------------------------------------------------
		//@info �R���X�g���N�^��shared_from_this()��p���Ȃ�
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::Load ()
	{
		//Transit�p��this��ۑ�
		mwp_This = shared_from_this ();

		//Menu�p��this��ۑ�
		m_pauseMenu->SetwpParent ( shared_from_this () );

		Scene::Load ();
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}


	void FtgMain::Move ()
	{
		if ( m_rectLoad->GetFadeTimer () == 0 )
		{
			m_NowLoading->SetValid ( F );
		}

		//���j���|�[�Y��
		if ( m_pauseMenu->GetActive () )
		{
			//���j���|�[�Y����
			bool bEsc = ( WND_UTL::AscKey ( VK_ESCAPE ) );
			bool bMenuBtn = ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) );
			if ( bEsc || bMenuBtn )
			{
				m_pauseMenu->Off ();
			}
			else
			{
				m_pauseMenu->Move ();
				return;
			}
		}

		//���j���|�[�Y�J�n
		bool bEsc = ( WND_UTL::AscKey ( VK_ESCAPE ) );
		bool bMenuBtn = ( CFG_PUSH_KEY ( _P1_BTN5 ) || CFG_PUSH_KEY ( _P2_BTN5 ) );
		if ( bEsc || bMenuBtn )
		{
			m_pauseMenu->On ();
		}

		Scene::Move ();

		//�I���`�F�b�N
		if ( m_fighting->IsEnd () )
		{
			Transit_Result ();
		}
	}


	//��ԑJ��
	P_GameScene FtgMain::Transit ()
	{
		//���̃V�[�����m�ۂ��ꂽ�Ȃ�J�ڂ���
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//�ʏ펞
		return mwp_This.lock();
	}
	

	//[�V�[���J��] �^�C�g���ɖ߂�
	void FtgMain::Transit_Title ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Title_Intro > ();
		GRPLST_LOAD ();
	}

	//���j���������ăQ�[���ɖ߂�
	void FtgMain::Resume_Fighting ()
	{
		m_pauseMenu->Off ();
	}

	//[�V�[���J��] ���U���g�ڍs
	void FtgMain::Transit_Result ()
	{
		GRPLST_CLEAR ();
		mp_Transit = make_shared < Result > ();
		GRPLST_LOAD ();
	}

}	//namespace GAME

