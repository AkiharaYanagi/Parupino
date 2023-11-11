//=================================================================================================
//
//	MutualChara �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "MutualChara.h"
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MutualChara::MutualChara ()
		: m_scpStop ( 0 ), m_blackOut ( 0 )
	{
		m_decision = make_shared < Decision > ();

		//�L����
		m_exeChara1 = make_shared < ExeChara > ( PLAYER_ID_1 );
		m_exeChara2 = make_shared < ExeChara > ( PLAYER_ID_2 );

		m_exeChara1->SetpOther ( m_exeChara2 );
		m_exeChara2->SetpOther ( m_exeChara1 );

		m_exeChara1->SetpParticle ( m_decision->GetpEfPart () );
		m_exeChara2->SetpParticle ( m_decision->GetpEfPart () );

		AddpTask ( m_exeChara1 );
		AddpTask ( m_exeChara2 );

		//����
		m_decision->SetpChara (m_exeChara1, m_exeChara2);
		AddpTask ( m_decision );

		//�q�b�g�X�g�b�v�^�C�}�[
		m_tmrHitstop = make_shared < Timer > ();
		m_tmrHitstop->SetTargetTime ( HITSTOP_TIME );
		AddpTask ( m_tmrHitstop );
		m_decision->SetpHitStop ( m_tmrHitstop );

		//�f�o�b�O�p�g�\��
#define DISP_RECT	1
#if DISP_RECT
		m_exeChara1->OnDispRect ();
		m_exeChara2->OnDispRect ();
#else
		m_exeChara1->OffDispRect ();
		m_exeChara2->OffDispRect ();
#endif // DISP_RECT

	}

	MutualChara::~MutualChara ()
	{
	}

	void MutualChara::ParamInit ( P_Param pParam )
	{
		m_pParam = pParam;

		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
	}

	void MutualChara::Init ()
	{
		m_pParam->SetN_Act1p ( 0 );
		m_pParam->SetN_Act2p ( 0 );

		TASK_VEC::Init ();
	}



	//��#########################################################
	//��
	//��	�X�N���v�g�̖��t���[������
	//��
	//��#########################################################
	void MutualChara::Conduct ()
	{
		//---------------------------------------------------
		//�V�X�e���ύX
		SwitchRect ();	//�g�\���ؑ�
		SwithcCPU ();	//CPU����ؑ�
		ResetMatch ();	//����������
		//---------------------------------------------------

		//���X�N���v�g�O����(���́A�ړ��Ȃ�)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//�����ݔ���(�Ԃ���g)
		Collision ();

		//���Ԃ����A�U���E�q�b�g����g��ݒ�
		m_exeChara1->RectMove ();
		m_exeChara2->RectMove ();

		//�����ݔ���(�U���E�q�b�g�g)
		_Decision ();

		//���X�N���v�g�㏈��(�O���t�B�b�N�ʒu�Ȃ�)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//�O���t�B�b�N����
		Grp ();

		//�V�[�����ʃp�����[�^�L�^
		m_pParam->SetN_Life1p ( m_exeChara1->GetLife () );
		m_pParam->SetN_Life2p ( m_exeChara2->GetLife () );
		m_pParam->SetN_Act1p ( m_exeChara1->GetBtlParam ().GetNActTrs () );
		m_pParam->SetN_Act2p ( m_exeChara2->GetBtlParam ().GetNActTrs () );
	}
	//��#########################################################



	//��================================
	//��		���ݔ���(�Ԃ���g)
	//��================================
	void MutualChara::Collision ()
	{
		//���҂̐ڐG�g���擾
		P_CharaRect pCharaRect1p = m_exeChara1->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_exeChara2->GetpCharaRect ();
		PV_RECT pvRect1p = pCharaRect1p->GetpvCRect ();
		PV_RECT pvRect2p = pCharaRect2p->GetpvCRect ();

		//�ڐG����
		//�d�Ȃ��Ă���Ƃ�
		if ( OverlapAryRect ( pvRect1p, pvRect2p ) )
		{
			bool dir1 = m_exeChara1->GetDirRight ();
			bool dir2 = m_exeChara2->GetDirRight ();
			VEC2 pos1_0 = m_exeChara1->GetPos ();
			VEC2 pos2_0 = m_exeChara2->GetPos ();

			m_exeChara1->BackPtX ();	//�݂���x�����݈̂ʒu��߂�
			m_exeChara2->BackPtX ();

			VEC2 pos1_1 = m_exeChara1->GetPos ();
			VEC2 pos2_1 = m_exeChara2->GetPos ();

			//����ɏd�Ȃ��Ă���Ƃ�
			if ( OverlapAryRect ( pvRect1p, pvRect2p ) )
			{
				//�ʒu������ɖ߂���(���삵����̈ʒu)����␳����
				if ( LeaveDir ( dir1, pos1_0.x, pos1_1.x ) )
				{
					m_exeChara1->SetPos ( pos1_0 );
				}
				if ( LeaveDir ( dir2, pos2_0.x, pos2_1.x ) )
				{
					m_exeChara2->SetPos ( pos2_0 );
				}
			}


			int i = 0;
			while ( OverlapAryRect ( pvRect1p, pvRect2p ) )
			{
#if 0
#endif // 0
				m_exeChara1->BackMoveX ();	//�d�Ȃ������
				m_exeChara2->BackMoveX ();

				m_exeChara1->SetCollisionRect ();	//����g�Đݒ�
				m_exeChara2->SetCollisionRect ();

				pvRect1p = pCharaRect1p->GetpvCRect ();
				pvRect2p = pCharaRect2p->GetpvCRect ();

				if ( ++ i > 10 ) { break; }
			}
		}

		//�U��
		m_exeChara1->LookOther ();
		m_exeChara2->LookOther ();

		//��������(��ʒ[���m)
		float p1x = m_exeChara1->GetPos ().x;
		float p2x = m_exeChara2->GetPos ().x;
		
		// P1 << P2
		if ( p2x - p1x > GAME_WINDOW_WIDTH - FIELD_EDGE * 2 )
		{
			m_exeChara1->BackPtX ();	//�݂��Ɉʒu��߂�
			m_exeChara2->BackPtX ();
		}
		// P2 << P1
		else if ( p1x - p2x > GAME_WINDOW_WIDTH - FIELD_EDGE * 2 )
		{
			m_exeChara1->BackPtX ();	//�݂��Ɉʒu��߂�
			m_exeChara2->BackPtX ();
		}
	}

	bool MutualChara::LeaveDir ( bool dirRight, float pos0, float pos1 )
	{
		//���������̂Ƃ�
		bool leave = F;
		if ( dirRight )	//�E�������ړ�
		{
			if ( pos1 < pos0 ) leave = T;
		}
		else//�������E�ړ�
		{
			if ( pos0 < pos1 ) leave = T;
		}
		return leave;
	}

	//��================================
	//��		���ݔ��� (�U���E�q�b�g�g)
	//��================================
	void MutualChara::_Decision ()
	{
		m_decision->Do ();
	}

	//��================================
	//��		���ʃO���t�B�b�N
	//��================================
	void MutualChara::Grp ()
	{
		//---------------------------------------------------
		//�Ó]
		UINT bo1 = m_exeChara1->GetBlackOut ();
		UINT bo2 = m_exeChara2->GetBlackOut ();

		//�ǂ��炩�����������Ƃ�
		if ( 0 < bo1 || 0 < bo2 )
		{
			SOUND->Play_SE ( SE_Sys_EnterFighting );

			//�傫�����ŏ㏑
			m_blackOut = ( bo2 < bo1 ) ? bo1 : bo2;
			m_exeChara1->SetBlackOut ( 0 );
			m_exeChara2->SetBlackOut ( 0 );
		}

		//---------------------------------------------------
		//�X�N���v�g����̒�~
		UINT scpStop1P = m_exeChara1->GetScpStop ();
		UINT scpStop2P = m_exeChara2->GetScpStop ();
		if ( 0 < scpStop1P )
		{
			m_scpStop = scpStop1P;
			m_exeChara1->SetScpStop ( 0 );

			m_exeChara1->SetStopTimer ( m_scpStop );
			m_exeChara2->SetStopTimer ( m_scpStop );
		}

		//---------------------------------------------------
		//��ʕ\���̊�ʒu������
		VEC2 pos1p = m_exeChara1->GetPos ();
		VEC2 pos2p = m_exeChara2->GetPos ();
		G_Ftg::inst ()->CulcPosMutualBase ( pos1p, pos2p );
	}



	//------------------------------------------------------
	//	�I������
	//------------------------------------------------------
	bool MutualChara::CheckZeroLife ()
	{
		//�I������
		bool finish1p = m_exeChara1->IsZeroLife ();
		bool finish2p = m_exeChara2->IsZeroLife ();

		//�ǂ��炩�A�܂��͗������C�t�O�Ȃ�I��
		if ( finish1p || finish2p )
		{
			PLAYER_ID plr = _PLAYER_NUM;
			if ( finish1p && finish2p )
			{
				plr = _PLAYER_NUM;
			}
			else if ( ! finish1p && finish2p )
			{
				plr = PLAYER_ID_1;
			}
			else if ( finish1p && ! finish2p )
			{
				plr = PLAYER_ID_2;
			}
			//�V�[�����ʃp�����[�^�L�^
			m_pParam->SetWinner ( plr );
			return T;
		}

		return F;
	}

#if 0
	bool MutualChara::CheckDown ()
	{
		//�_�E������
		bool down1p = m_exeChara1->IsDown ();
		bool down2p = m_exeChara2->IsDown ();
		return (down1p || down2p);
	}

	bool MutualChara::CheckDownEnd ()
	{
		//�_�E������
		bool downEnd1p = m_exeChara1->IsDownEnd ();
		bool downEnd2p = m_exeChara2->IsDownEnd ();
		return (downEnd1p || downEnd2p);
	}

	bool MutualChara::CheckWin ()
	{
		//������Ԕ���
		bool win1p = m_exeChara1->IsWin ();
		bool win2p = m_exeChara2->IsWin ();
		return (win1p || win2p);
	}

	bool MutualChara::CheckWinEnd ()
	{
		//������Ԕ���
		bool winEnd1p = m_exeChara1->IsWinEnd ();
		bool winEnd2p = m_exeChara2->IsWinEnd ();
		return (winEnd1p || winEnd2p);
	}

	bool MutualChara::CheckWinner ()
	{
		bool bRet = false;

		//���C�t�ŏ����҂����肷��
		int life1p = m_exeChara1->GetLife ();
		int life2p = m_exeChara2->GetLife ();

		//Double K.O.
		if ( life1p <= 0 && life2p <= 0 ) { m_winner = WINNER_DP; }
		//2P Win
		else if ( life1p <= 0 ) { m_winner = WINNER_2P; }
		//1P Win
		else if ( life2p <= 0 ) { m_winner = WINNER_1P; }
		//Draw
		else if ( life1p == life2p ) { m_winner = WINNER_DRAW; }

		switch ( m_winner )
		{
		case WINNER_1P: 
			m_exeChara1->SetCharaState ( CHST_WIN_END );
			m_exeChara2->SetCharaState ( CHST_DOWN_END );
			break;
		case WINNER_2P: 
			m_exeChara1->SetCharaState ( CHST_DOWN_END );
			m_exeChara2->SetCharaState ( CHST_WIN_END );
			break;
		case WINNER_DP: break;
		default: break;
		}

		return bRet;
	}

	void MutualChara::ForcedEnd ()
	{
		m_exeChara1->ForcedEnd ();
		m_exeChara2->ForcedEnd ();
	}
#endif // 0


	CHARA_NAME MutualChara::GetWinnerName () const
	{
		switch ( m_winner )
		{
		case WINNER_1P: return m_exeChara1->GetCharaName (); break;
		case WINNER_2P: return m_exeChara2->GetCharaName (); break;
		case WINNER_DP: break;
		default: break;
		}
		return CHARA_NAME ();
	}


	//------------------------------------------------------
	//	�����֐�
	//------------------------------------------------------

	//------------------------------------------------------
	//�g�\���ؑ� 
	//@info ExeChara�ŌĂԂ�1P2P�łQ��Ă΂�Ă��܂�
	void MutualChara::SwitchRect ()
	{
		static bool bDispRect = false;		//���
		static bool pre_bDispRect = false;	//�O�񉟂��Ă��邩
		static bool is_bDispRect = false;	//���񉟂��Ă��邩
		
		
//		is_bDispRect = ( ::GetAsyncKeyState ( '1' ) & 0x0001 );
		is_bDispRect = ( WND_UTL::AscKey ( '1' ) );

		//@info �L�[�{�[�h���͉͂������ςȂ��ň�莞�Ԍ�A�ŏ�ԂɂȂ�
		//TRACE_F ( _T ( "b = %d, pre = %d, is = %d\n" ), bDispRect ? 1 : 0, pre_bDispRect ? 1 : 0, is_bDispRect ? 1 : 0  );
		
		//���񉟂����u�ԂȂ�΁A1��̂ݐؑ�
		if ( ! pre_bDispRect && is_bDispRect )	// false -> true
		{
			if ( ! bDispRect )
			{
				m_exeChara1->OnDispRect ();
				m_exeChara2->OnDispRect ();
				bDispRect = true;
			}
			else
			{
				m_exeChara1->OffDispRect ();
				m_exeChara2->OffDispRect ();
				bDispRect = false;
			}
		}

		pre_bDispRect = is_bDispRect;
	}

	//------------------------------------------------------
	//CPU����ؑ�
	void MutualChara::SwithcCPU ()
	{
		static bool cpu1 = F;
		if ( WND_UTL::AscKey ( '6' ) )
		{
			cpu1 ^= T;
			if ( cpu1 )
			{
				m_exeChara1->ControlCPU ();
			}
			else
			{
				m_exeChara1->ControlPlayer ();
			}
		}

		static bool cpu2 = F;
		if ( WND_UTL::AscKey ( '7' ) )
		{
			cpu2 ^= T;
			if ( cpu2 )
			{
				m_exeChara2->ControlCPU ();
			}
			else
			{
				m_exeChara2->ControlPlayer ();
			}
		}
	}

	void MutualChara::Set_1P_vs_2P ()
	{
		m_exeChara1->ControlPlayer ();
		m_exeChara2->ControlPlayer ();
	}

	void MutualChara::Set_1P_vs_CPU ()
	{
		m_exeChara1->ControlPlayer ();
		m_exeChara2->ControlCPU ();
	}

	void MutualChara::Set_CPU_vs_CPU ()
	{
		m_exeChara1->ControlCPU ();
		m_exeChara2->ControlCPU ();
	}


	//------------------------------------------------------

	//����������
	void MutualChara::ResetMatch ()
	{
		if ( ::GetAsyncKeyState ( '0' ) & 0x0001 )
		{
			m_exeChara1->Init ();
			m_exeChara2->Init ();
		}
	}

	void MutualChara::TrainingInit ()
	{
		m_exeChara1->TrainingInit ();
		m_exeChara2->TrainingInit ();
	}

	//------------------------------------------------------
	//	ExeChara���ґ���
	//------------------------------------------------------
	//�J�n�f��
	void MutualChara::StartGreeting ()
	{
		m_exeChara1->StartGreeting ();
		m_exeChara2->StartGreeting ();
	}

	//�J�n����
	void MutualChara::StartGetReady ()
	{
		m_exeChara1->StartGetReady ();
		m_exeChara2->StartGetReady ();
	}

	//�퓬�J�n
	void MutualChara::StartFighting ()
	{
		m_exeChara1->StartFighting ();
		m_exeChara2->StartFighting ();
	}


#if 0
	void MutualChara::SetReady ()
	{
		//����
		m_exeChara1->SetCharaState ( CHST_START );
		m_exeChara2->SetCharaState ( CHST_START );
	}
	void MutualChara::SetMain ()
	{
		//�J�n
		m_exeChara1->SetMain ();
		m_exeChara2->SetMain ();
	}
	void MutualChara::Wait ( bool b )
	{
		//���͒�~
		m_exeChara1->SetWait ( b );
		m_exeChara2->SetWait ( b );
	}
	void MutualChara::Stop ( bool b )
	{
		//�ꎞ��~
		m_exeChara1->SetStop ( b );
		m_exeChara2->SetStop ( b );
	}
	void MutualChara::SetEndWait ()
	{
		//�I���ҋ@
		m_exeChara1->SetEndWait ();
		m_exeChara2->SetEndWait ();
	}
	void MutualChara::EndAct ()
	{
		//�I��
		m_exeChara1->OnEndAct ();
		m_exeChara2->OnEndAct ();
	}
	void MutualChara::SetCharaState ( CHARA_STATE chst )
	{
		//��Ԃ̐ݒ�
		m_exeChara1->SetCharaState ( chst );
		m_exeChara2->SetCharaState ( chst );
	}
#endif // 0

}	//namespace GAME

