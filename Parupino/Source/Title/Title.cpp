//=================================================================================================
//
//	Title �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Title.h"
#include "../FtgMain/FtgMain.h"
#include "../Training/Training.h"
#include "../CharaSele/CharaSele.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Title::Title ()
	 :	  m_fadeOutTimer ( 0 ), m_timer ( 0 ), m_blink ( true )
//		, m_muchMode ( MODE_PLAYER_PLAYER )
		, m_menuPos ( TTLM_TRAINING )
		, m_demoTimer ( 0 )
	{
		//Scene�̍ŏ����̂݁AGrpLst���Q�[���^�X�N�ɐݒ�
//		AddpTask ( GRPLST_MAKE () );

		//�e�O���t�B�b�N�̏�����
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "title_bg.png" ) );
//		m_bg->AddTexture ( _T ( "title_bg_cloud.png" ) );
		m_bg->SetZ ( Z_BG );
		GRPLST_INSERT ( m_bg );

		m_titleEf.Load ();		//Ef�̈ʒu�̂��߂����ŏ�����

		m_logo = make_shared < GrpAcv > ();
//		m_logo->AddTexture ( _T ( "title_logo.png" ) );
		m_logo->AddTexture ( _T ( "title.png" ) );
//		m_logo->SetPos ( VEC2 ( (1280 - 1024) * 0.5f, 80 ) );
		m_logo->SetZ ( Z_BG );
		GRPLST_INSERT ( m_logo );

		m_menu = make_shared < GrpAcv > ();
		m_menu->AddTexture ( _T ( "title_menu.png" ) );
		m_menu->SetPos ( VEC2 ( (1280 - 512) * 0.5f, TITLE_menu_y ) );
		m_menu->SetZ ( Z_BG );
		GRPLST_INSERT ( m_menu );

		m_cursor = make_shared < GrpBlink > ();
		m_cursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_cursor->SetPos ( VEC2 ( TTL_CURSOR_X, TTL_CURSOR_Y0 ) );
		m_cursor->SetZ ( Z_BG );
		GRPLST_INSERT ( m_cursor );

		m_demo_mode = make_shared < GrpAcv > ();
		m_demo_mode->AddTexture ( _T("title_demo_mode.png") );
		m_demo_mode->SetPos ( VEC2 ( (1280 - 512) * 0.5f, 700 ) );
		m_demo_mode->SetZ ( Z_BG );
		m_demo_mode->SetValid ( false );
		GRPLST_INSERT ( m_demo_mode );

#if 0
		m_fade = make_shared < Fade > ();
		m_fade->SetDarkIn ( 15 );
		GRPLST_INSERT ( m_fade );
#endif // 0

		//�����̎�
		::srand ( timeGetTime () );
	}

	Title::~Title ()
	{
	}

	void Title::ParamInit ()
	{
	}

	void Title::Load ()
	{
		GameScene::Load ();
	}

	void Title::Init ()
	{
		//�f�����[�h�ɂ��\���̐ؑւ�������
#if 0
		GetpParam()->GetDemo () ? DemoOn () : DemoOff ();
#endif // 0
		START_MODE start = GetpParam ()->GetGameSetting ().GetStartMode ();
		( start == START_DEMO ) ? DemoOn (): DemoOff ();

		//�J�[�\���ʒu��������
		m_cursor->SetPos ( VEC2 ( TTL_CURSOR_X, TTL_CURSOR_Y0 ) );

		GameScene::Init ();
	}

	void Title::Move ()
	{
		//EF
		m_titleEf.Move ();

		//F1�Ńf�����[�h��؂�ւ�
		if ( ::GetAsyncKeyState ( VK_F1 ) & 0x0001 )
		{
			if ( IsDemo () )
			{
				GetpParam ()->GetGameSetting().SetDemo ( F );
				DemoOff ();		//On->Off
			}
			else
			{
				GetpParam ()->GetGameSetting ().SetDemo ( T );
				DemoOn ();		//Off->On
			}
		}

		//�f�����[�h���͉������Ȃ�
		if ( IsDemo () )
		{
			GameScene::Move ();
			return;
		}

		//�J�[�\���ړ�
		switch ( m_menuPos )
		{
		case TTLM_TRAINING:   if ( CsrUp () ) { SelectCC (); } if ( CsrDn () ) { SelectPP (); } break;
		case TTLM_1P_VS_2P:   if ( CsrUp () ) { SelectTR (); } if ( CsrDn () ) { SelectPC (); } break;
		case TTLM_1P_VS_CPU:  if ( CsrUp () ) { SelectPP (); } if ( CsrDn () ) { SelectCC (); } break;
		case TTLM_CPU_VS_CPU: if ( CsrUp () ) { SelectPC (); } if ( CsrDn () ) { SelectTR (); } break;
		default: break;
		}

		GameScene::Move ();
	}

	bool Title::CsrUp () {
		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		{
			SOUND->Play ( SE_cursor_move );
			return true;
		}
		return false;
	}
	bool Title::CsrDn () {
		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		{
			SOUND->Play ( SE_cursor_move );
			return true;
		}
		return false;
	}

	void Title::SelectTR () { m_menuPos = TTLM_TRAINING; SetCrsY ( TTL_CURSOR_Y0 ); }
	void Title::SelectPP () { m_menuPos = TTLM_1P_VS_2P;   SetCrsY ( TTL_CURSOR_Y1 ); }
	void Title::SelectPC () { m_menuPos = TTLM_1P_VS_CPU;  SetCrsY ( TTL_CURSOR_Y2 ); }
	void Title::SelectCC () { m_menuPos = TTLM_CPU_VS_CPU; SetCrsY ( TTL_CURSOR_Y3 ); }

	void Title::SetCrsY ( int y ) { m_cursor->SetPos ( VEC2 ( TTL_CURSOR_X, 1.f * y ) ); }

	MUTCH_MODE Title::MENU_to_MODE ( TITLE_MENU tm, PLAYER_ID id )
	{
		MUTCH_MODE ret = MODE_PLAYER_PLAYER;
		switch ( m_menuPos )
		{
		case TTLM_TRAINING: ret = MODE_PLAYER_CPU; break;
		case TTLM_1P_VS_2P: ret = MODE_PLAYER_PLAYER; break;
		case TTLM_1P_VS_CPU: ret = MODE_PLAYER_CPU; break;
		case TTLM_CPU_VS_CPU: ret = MODE_CPU_CPU; break;
		default: break;
		}

		//2p�Ō���̏ꍇ
		if ( PLAYER_ID_2 == id )
		{
			switch ( m_menuPos )
			{
			case TTLM_TRAINING: ret = MODE_CPU_PLAYER; break;
			case TTLM_1P_VS_2P: ret = MODE_PLAYER_PLAYER; break;
			case TTLM_1P_VS_CPU: ret = MODE_CPU_PLAYER; break;
			case TTLM_CPU_VS_CPU: ret = MODE_CPU_CPU; break;
			default: break;
			}
		}
		return ret;
	}


	P_GameScene Title::Transit ()
	{
		//ESC�ŃA�v���P�[�V�������I��(�^�C�g���̂݁E���V�[���ł�1�߂�)
		if ( ::GetAsyncKeyState ( VK_ESCAPE ) & 0x0001 ) 
		{ 
			::PostQuitMessage( 0 );
		}

		//---------------------------------------------------------------
		//�f�����[�h
		if ( IsDemo () )
		{
			//����
			if ( ++ m_demoTimer == DM_TITLE_WAIT )
			{
				m_demoTimer = 0;

				//���ʃp�����[�^�ɒl��ۑ����ăV�[���̈ڍs
				Scene::GetpParam ()->SetMutchMode ( MODE_CPU_CPU );

				//�L�����I���̓����_��
				Scene::GetpParam ()->SetRandomChara ();

				//���ʃO���t�B�b�N�z����N���A
//				GRPARY_CLEAR ();

//				return make_shared < Fighting > ();
				return make_shared < FtgMain > ();
			}

			return shared_from_this ();		//�ʏ�͎��g��Ԃ�
		}

		//---------------------------------------------------------------
		//�ʏ�(��f�����[�h)��

		if ( 0 != m_fadeOutTimer )
		{
			-- m_fadeOutTimer;
			if ( 0 == m_fadeOutTimer )
			{
				//���ʃO���t�B�b�N�z����N���A
				GRPLST_CLEAR ();

				//�p�����[�^�ɋL�^
				P_Param pParam = GetpParam ();

				//�g���[�j���O
				if ( TTLM_TRAINING == m_menuPos )
				{
					pParam->GetGameSetting().SetTraining ( T );					
//					return make_shared < CharaSele > ();
//					return make_shared < Training > ();

					P_GameScene p = make_shared < Training > ();
					GRPLST_LOAD ();
					GRPLST_INIT ();
					return p;
				}
				else
				{
					//���C��
					pParam->GetGameSetting ().SetTraining ( false );
//					return make_shared < CharaSele > ();
					//return make_shared < FtgMain > ();

					P_GameScene p = make_shared < FtgMain > ();
					GRPLST_LOAD ();
					GRPLST_INIT ();
					return p;
				}
			}
		}
		else
		{
			//�L�[1�ŃV�[����i�߂�
			if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
			{
				//���ʃp�����[�^�ɒl��ۑ����ăV�[���̈ڍs
				Scene::GetpParam ()->SetMutchMode ( MENU_to_MODE ( m_menuPos, PLAYER_ID_1 ) );

	//			m_fade->SetDarkOut ( 15 );
				m_fadeOutTimer = 17;
			}

			if ( CFG_PUSH_KEY ( _P2_BTN0 ) )
			{
				//���ʃp�����[�^�ɒl��ۑ����ăV�[���̈ڍs
				Scene::GetpParam ()->SetMutchMode ( MENU_to_MODE ( m_menuPos, PLAYER_ID_2 ) );

	//			m_fade->SetDarkOut ( 15 );
				m_fadeOutTimer = 17;
			}
		}


		return shared_from_this ();		//�ʏ�͎��g��Ԃ�
	}

	bool Title::IsDemo ()
	{
		START_MODE start = GetpParam ()->GetGameSetting ().GetStartMode ();
		return ( start == START_DEMO );
	}

	void Title::DemoOn ()
	{
		//�f�����[�h�\��:true
		m_demo_mode->SetValid ( true );
		m_demoTimer = 0;
		//�ʏ탁�j���[:false
		m_cursor->SetValid ( false );
		m_menu->SetValid ( false );
	}

	void Title::DemoOff ()
	{
		//�f�����[�h�\��:false
		m_demo_mode->SetValid ( false );
		m_demoTimer = 0;
		//�ʏ탁�j���[:true
		m_cursor->SetValid ( true );
		m_menu->SetValid ( true );
	}

}	//namespace GAME

