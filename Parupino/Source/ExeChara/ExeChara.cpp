//=================================================================================================
//
// �G�O�[�L�����@�\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�R���X�g���N�^
	ExeChara::ExeChara ( PLAYER_ID m_playerID )
		: m_pChara ( nullptr ), m_playerID ( m_playerID ), m_name ( CHARA_TEST )
		, m_playerMode ( MODE_PLAYER ), m_oprtEf ()
		, m_actionID ( 0 ), m_frame ( 0 )
		, m_dirRight ( true ), m_ptChara ( 0, 0 ), m_tempPt ( 0, 0 ), m_inertial ( 0, 0 )
		, m_vel ( 0, 0 ), m_acc ( 0, 0 ), m_g ( 0 ), m_vg ( 0 )
		, m_charaState ( CHST_START )
		, m_wait ( true ), m_stop ( false ), m_FirstEf ( false ), m_FirstSE ( false )
		, m_life ( 0 ), m_balance ( 0 ), m_damage ( 0 ), m_power ( 0 )
		, m_hitEst ( false ), m_clang ( false ), m_transit ( false )
		, m_bDispRect ( true )
//		, m_lurch ( 0 ), m_lurchTimer ( 0 )
	{
		//�|�C���^����
		m_pChara = make_shared < Chara > ();	//�L�����f�[�^����
		m_charaRect = make_shared < CharaRect > ();		//�g

		//�^�C�}�[�̏�����
		m_tmrHitstop = make_shared < Timer > ();
		m_tmrHitstop->SetTargetTime ( HITSTOP_TIME );
		AddpTask ( m_tmrHitstop );

		//�_�E���^�C�}�[
		m_tmrDown = make_shared < Timer > ();
		m_tmrDown->SetTargetTime ( DOWN_TIME );
		AddpTask ( m_tmrDown );

		//�I����ԃ^�C�}�[
		m_tmrEnd = make_shared < Timer > ();
		m_tmrEnd->SetTargetTime ( END_TIME );
		AddpTask ( m_tmrEnd );
	}

	//�f�X�g���N�^
	ExeChara::~ExeChara ()
	{
	}

	//------------------------
	//�V�[���p�����[�^�֘A������
	void ExeChara::ParamInit ( P_Param pParam )
	{
		//�I���L����
		m_name = pParam->GetCharaName ( m_playerID );

		//���̓��[�h
		m_playerMode = pParam->GetMode ( m_playerID );
		switch ( m_playerMode )
		{
		case MODE_PLAYER: m_pCharaInput = make_shared < PlayerInput > (); break;
		case MODE_CPU: m_pCharaInput = make_shared < CPUInput > ( shared_from_this (), m_pOther ); break;
		case MODE_NETWORK: m_pCharaInput = make_shared < PlayerInput > (); break;
		default: break;
		}
		m_pCharaInput->SetPlayer ( m_playerID );
	}

	//------------------------
	//�Ǎ�
	void ExeChara::Load ()
	{
		//�X�N���v�g�t�@�C������L�����̃��[�h
		//��	D3DX�̃e�N�X�`����p���邽�߃t�H�[�J�X�ύX���ȂǂɍĐݒ肪�K�v
		tstring name ( _T ( "testChara.dat" ) );

		//tstring&�̂���assign�Ŏw�肷��
		switch ( m_name )
		{
		case CHARA_TEST: name.assign ( _T ( "testChara.dat" ) ); break;
#if 0

		case CHARA_RAKUNO: name.assign ( _T ( "Rakuno.dat" ) ); break;
		case CHARA_YUKINO: name.assign ( _T ( "Yukino.dat" ) ); break;
#endif // 0
		default: break;
		}
		LoadChara loadChara ( name, *m_pChara );

		//��{��ԃA�N�V����ID���蓮�Őݒ肷��
#if 0
		<STAND ID = "0" Name = "Stand">< / STAND>
		<POISED ID = "25" Name = "S_Guard">< / POISED>
		<CLANG ID = "29" Name = "Clang">< / CLANG>
		<AVOID ID = "30" Name = "Avoid">< / AVOID>
		<DOTTY ID = "31" Name = "Dotty">< / DOTTY>
		<DAMAGED ID = "32" Name = "DamagedL">< / DAMAGED>
		<DOWN ID = "39" Name = "Lose">< / DOWN>
		<WIN ID = "41" Name = "Win">< / WIN>
#endif // 0
		m_pChara->SetBsAction ( BA_STAND, 0 );
		m_pChara->SetBsAction ( BA_POISED, 25 );
		m_pChara->SetBsAction ( BA_CLANG, 29 );
		m_pChara->SetBsAction ( BA_AVOID, 30 );
		m_pChara->SetBsAction ( BA_DOTTY, 31 );
		m_pChara->SetBsAction ( BA_DAMAGED, 32 );
		m_pChara->SetBsAction ( BA_DOWN, 39 );
		m_pChara->SetBsAction ( BA_WIN, 41 );


		//�L�����\��������
		m_dispChara.SetpChara ( m_pChara );
		m_dispChara.Load ();

		//�G�t�F�N�g�����x�N�^�̐���
		MakeEfOprt ();

		TASK_VEC::Load ();
	}

	//------------------------
	//������(��������s�\)
	void ExeChara::Init ()
	{
		//�A�N�V�����E�X�N���v�g������
		m_actionID = 0;
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_frame = 0;
		m_pScript = m_pAction->GetpScript ( m_frame );

		//�����ʒu
		if ( PLAYER_ID_1 == m_playerID )
		{
			m_ptChara = VEC2 ( PLAYER_1_BASE_X, PLAYER_1_BASE_Y );
			m_dirRight = true;
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			m_ptChara = VEC2 ( PLAYER_2_BASE_X, PLAYER_2_BASE_Y );
			m_dirRight = false;
		}

		//�Q�[���p�����[�^
		m_life = LIFE_MAX;
		m_damage = 0;
		m_power = 0;
		m_hitEst = false;
		m_FirstEf = false;
		m_FirstSE = false;
		m_charaState = CHST_START;

		EndAction ();

		//�^�C�}�[
		m_tmrEnd->Reset ();
		m_tmrHitstop->Reset ();

		//�\��
		//@info Move()����Transit()�̌�ɑJ�ڂ��A
		//		�ēxMove()�͌Ă΂ꂸDraw()���Ă΂�邽�߁A�����ŏ��������K�v(Init()�͌Ă΂��)
		m_dispChara.UpdateMainImage ( m_pScript, m_ptChara, m_dirRight );
		m_dispChara.InitDisp ( m_playerID );

		TASK_VEC::Init ();
	}


	//------------------------
	//���
	void ExeChara::Rele ()
	{
		m_pChara.reset ();
		TASK_VEC::Rele ();
	}

	//------------------------
	//�Đݒ�
	void ExeChara::Reset ()
	{
		Rele ();
		m_pChara = make_shared < Chara > ();
		Load ();
		m_dispChara.SetpChara ( m_pChara );
		m_oprtEf.SetpChara ( m_pChara );
		Resume ();	//������
	}

	//------------------------
	//�������̍Đݒ�
	void ExeChara::Resume ()
	{
		//�A�N�V�����E�X�N���v�g�Ď擾
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//���C�� �C���[�W
		m_dispChara.UpdateMainImage ( m_pScript, m_ptChara, m_dirRight );

		//�G�t�F�N�g �C���[�W
		m_oprtEf.PostScriptMove ( m_ptChara, m_dirRight );
	}


	//��#########################################################
	//��
	//��		���t���[�� �X�N���v�g�O����
	//��			�ʒu��g�̐ݒ�
	//��
	//��#########################################################
	void ExeChara::PreScriptMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		// �A�N�V�����ƃX�N���v�g�ɂ��Ȃ����̏���
		AlwaysMove ();

		if ( m_stop ) { return; }		//�ꎞ��~�̂Ƃ��͉������Ȃ�

		// �q�b�g�X�g�b�v���͓��͂̕ۑ��ƕ\���֘A�̏��������ďI��
		//Active�Ƃ̌��ˍ����Ń^�C�}�[�̃��X�g�͗L���@0�`N-1�܂�
		if ( ! m_tmrHitstop->IsLast () )
		{
			if ( m_tmrHitstop->IsActive () ) { return; }
		}

		// �A�N�V�����ڍ�
		TransitAction ();

		// �ʒu�v�Z
		CalcPos ();

		//�ڐG�g�ݒ�
		AdjustCRect ();
	}


	//��###########################################################################
	//��
	//��		���t���[�� �X�N���v�g�㏈��
	//��			�����E����̃X�N���v�g�O���������݂̔���A�̌�ɂ��ꂼ��̏���������
	//��			����̌��ʕ\��(��ɃO���t�B�b�N�֘A)
	//��
	//��###########################################################################
	void ExeChara::PostScriptMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );
		if ( m_stop ) { return; }		//�ꎞ��~�̂Ƃ��͉������Ȃ�

		//���C�t����
		CheckLife ();

		// �O���t�B�b�N
		UpdateGraphic ();
	}


	//================================================
	//	�O������̏�ԕύX
	//================================================

	//�ō�����
	void ExeChara::OnClang ( UINT nLurch, CLANG_DECISION_WL clangDecision )
	{
//		if ( CD_LOSE == clangDecision )
		{
			//��Ԃ̕ύX
			m_actionID = m_pChara->GetBsAction ( BA_CLANG );
			m_frame = 0;
		}
		m_clang = true;		//�ō����
//		m_lurch = nLurch;		//�̂����莞�Ԃ̐ݒ�
		m_tmrHitstop->Start ();		//�q�b�g�X�g�b�v�̐ݒ�
	}


	//�q�b�g����
	void ExeChara::OnDamaged ( int damage )
	{
		//��𔻒�
#if 0
		//�U�����łȂ��A���v�f�����͂���Ă���Ƃ�
		//�_�b�V�����A��낯���Ȃǂ����O���� (�����͉\)
		if ( !IsAttacking () && !(GetActionName () == Chara::DOTTY) )
		{
			if ( IsInput2E () )
			{
				//�����Ɉڍ�
				TransitAction ( m_pChara->GetBsAction ( Chara::AVOID ) );

				//�q�b�g�X�g�b�v�̐ݒ�
				m_hitstop = 15;

				//�G�t�F�N�g�̔���
//				float dispGameBaseX = GetDispGameBaseX ();	//��ʒ[�ɂ��\����ʒu
				m_dispChara.OnAvoid ( m_ptChara, m_dirRight );

				//SE
				SoundArchiver::instance ()->Play ( 2 );

				//�����̃o�����X�����E�ǉ���
				int balanceDamage0 = 200 - damage;		//�_���[�W�̋t��(L>M>H)
				if ( m_balance < balanceDamage0 ) { balanceDamage0 = m_balance; }	//���ݒl�ȏ�͕\������
				m_balance -= balanceDamage0;

				//����̃o�����X����
				int balanceDamage = damage;		//�_���[�W���o�����X����(L<M<H)
				int balance = m_pOther->GetBalance ();
				if ( balance < balanceDamage ) { balanceDamage = balance; }	//���ݒl�ȏ�͕\������
				m_pOther->AddbBalance ( -1 * balanceDamage );

				return;
			}
		}
#endif // 0

		bool hit = true;
		bool guard = false;

		//�K�[�h����
		//�U�����łȂ��Ƃ�
		//�_�b�V�����A��낯���Ȃǂ����O���� (�����͉\)
		if ( !IsAttacking () && !IsDamaged () )
		{
			//�㒆���i�@���򏈗�
			ACTION_POSTURE ap = m_pOther.lock ()->GetPosture ();

			//����������͂���Ă���Ƃ�
			if ( m_pCharaInput->IsInput4 () )
			{
				//����̏�Ԃŕ���
				switch ( ap )
				{
				case AP_STAND:	hit = false; guard = true; break;
				case AP_CROUCH: hit = true; guard = false; break;
				case AP_JUMP:	hit = false; guard = true; break;
				}
			}

			//�㉺���������͂���Ă���Ƃ�
			if ( m_pCharaInput->IsInput1 () )
			{
				//����̏�Ԃŕ���
				switch ( ap )
				{
				case AP_STAND:	hit = false; guard = true; break;
				case AP_CROUCH: hit = false; guard = true; break;
				case AP_JUMP:	hit = true; guard = false; break;
				}
			}

		}

		//--------------------------------------------------------

		//�K�[�h����
		if ( guard )
		{
			tstring act;
			switch ( m_pAction->GetPosture () )
			{
			case AP_STAND:	act.assign ( _T ( "S_Guard" ) ); break;
			case AP_CROUCH: act.assign ( _T ( "C_Guard" ) ); break;
			case AP_JUMP:	act.assign ( _T ( "J_Guard" ) ); break;
			}
			TransitAction ( m_pChara->GetActionID ( act ) );

			m_FirstEf = true;				//����̂݃G�t�F�N�g����
			m_tmrHitstop->Start ();				//�q�b�g�X�g�b�v�̐ݒ�

			//SE
			SOUND->Play ( SE_Guard );
		}

		//�q�b�g��
		if ( hit )
		{
			//�_���[�W�����C�t�ɂ���ĕ␳(�����l)
			if ( m_life < LIFE_MAX * 0.5f )
			{
				damage = (int)(damage * (0.001f * (0.5f * LIFE_MAX + m_life)));
			}

			//�_���[�W����
			if ( m_life < damage ) { m_damage = m_life; }	//���C�t�ȏ�͕\������
			else { m_damage = damage; }		//�\���p
			m_life -= damage;

			//��Ԃ̕ύX
			tstring act;
			switch ( m_pAction->GetPosture () )
			{
			case AP_STAND:	act.assign ( _T ( "DamagedL" ) ); break;
			case AP_CROUCH: act.assign ( _T ( "C_DamagedL" ) ); break;
			case AP_JUMP:	act.assign ( _T ( "J_DamagedL" ) ); break;
			}
			TransitAction ( m_pChara->GetActionID ( act ) );

			m_tmrHitstop->Start ();			//�q�b�g�X�g�b�v�̐ݒ�
			m_FirstEf = true;			//����̂݃G�t�F�N�g����
			m_FirstSE = true;			//����̂�SE����

		}
	}

	//�q�b�g����(�U��������)
	void ExeChara::OnHit ()
	{
		m_hitEst = true;		//�U�������t���O
		m_tmrHitstop->Start ();		//�q�b�g�X�g�b�v�̐ݒ�
	}

	//�G�t�F�N�g�q�b�g����(�U��������)
	void ExeChara::OnEfHit ()
	{
		m_hitEst = true;		//�U�������t���O
//		m_tmrHitstop->Start ();		//�G�t�F�N�g�̓q�b�g�X�g�b�v���Ȃ�
	}

	//�I�����o
	void ExeChara::OnEndAct ()
	{
		m_charaState = CHST_WIN_WAIT;
	}


	//================================================
	//	�����֐�
	//================================================

	// �A�N�V�����ƃX�N���v�g�ɂ��Ȃ����̏���
	void ExeChara::AlwaysMove ()
	{
		//�_���[�W�\������
		if ( 0 < m_damage ) { --m_damage; }

		//---------------------------------------------------
		//�f���J�E���g
		//�_�E����Ԃ̂Ƃ�
		if ( CHST_DOWN == m_charaState )
		{
			if ( ! m_tmrDown->IsActive () )
			{
				m_charaState = CHST_DOWN_END;
			}
		}

		//�����ҋ@��Ԃ̂Ƃ�
		if ( CHST_WIN_WAIT == m_charaState )
		{
			//�n��j���[�g�����Ȃ�
			if ( IsBasicAction ( BA_STAND ) )
			{
				//������ԂɈڍs
				m_actionID = m_pChara->GetBsAction ( BA_WIN );
				TransitAction ( m_actionID );
				m_tmrEnd->Start ();
				m_charaState = CHST_WIN;
			}
		}

		//������Ԃ̂Ƃ�
		if ( CHST_WIN == m_charaState )
		{
			if ( ! m_tmrEnd->IsActive () )
			{
				m_charaState = CHST_WIN_END;
			}
		}
		//---------------------------------------------------
		//SE
		if ( m_FirstSE )
		{
			SOUND->Play ( SE_Hit );
			m_FirstSE = false;
		}

		//---------------------------------------------------
		// ���͂��\�ȏ��
		if ( CanInput () )
		{
			//���͂̕ۑ�
			m_pCharaInput->Update ( m_dirRight );
		}
	}


	//�A�N�V�����̈ڍ�
	void ExeChara::TransitAction ( UINT actionID )
	{
		//�J�ڐ�`�F�b�N
		P_Action pact = m_pChara->GetpAction( actionID );
		P_Script pscr = pact->GetpScript ( 0 );

		m_actionID = actionID;		//�J��
		m_frame = 0;		//�X�N���v�g������

		//�ꎞ�A�N�V�����ƃX�N���v�g���Đݒ�
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );
	}

	// �A�N�V�����ڍ�
	void ExeChara::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		// �̂����莞�Ԃ̓R�}���h�ɂ��s���s��
#if 0
		if ( LurchTimer () ) { return; }
#endif // 0

		// �R�}���h�ɂ�镪��
		PVP_Branch pvpBranch = m_pScript->GetpvpBranch ();
		UINT transitID = m_pCharaInput->GetTransitID ( pvpBranch, m_dirRight );

		//�R�}���h���������Ă�����
		if ( NO_COMPLETE != transitID )
		{
			//�J�ڐ�`�F�b�N
			P_Action pact = m_pChara->GetpAction ( transitID );
			P_Script pscr = pact->GetpScript ( 0 );

			m_actionID = transitID;			//�J��

			//�e���Ԃ̏I��
			EndAction ();
		}

		//---------------------------------------------------
		//�J�ڎ��Ɋe���Ԃ̏I��
		if ( 0 == m_frame )
		{
			//�e���Ԃ̏I��
			EndAction ();
		}

		//0����J�n�AMove()��Draw()�œ���X�N���v�g����������
		//���̃t���[���ŃX�N���v�g���������邽�߁A�ڍs��A�N�V�����ƃX�N���v�g��ۑ�
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//���݃A�N�V�������ŏI�t���[���Ȃ��
		if ( m_pAction->IsEndScript ( m_frame ) )
		{
			//�����A�N�V����m_pAction�͎��t���[������Move()��m_actionID���g���Ď擾�����
			m_actionID = m_pAction->GetNextID ();
			m_frame = 0;
			//����̃t���[������m_pAction��m_pScript��p���A
			//����ȍ~��m_actionID��m_frame��p���Ȃ�
		}
		else
		{
			++m_frame;
		}

		assert ( nullptr != m_pAction && nullptr != m_pScript );
	}

	//�G�t�F�N�g�����̐���
	void ExeChara::MakeEfOprt ()
	{
		//�G�t�F�N�g�����ɃL�����|�C���^��ݒ�
		m_oprtEf.SetpChara ( m_pChara );

		//���ׂẴA�N�V�����ƃX�N���v�g������
		PVP_Action pvpAction = m_pChara->GetpvpAction ();
		for ( P_Action pAction : (* pvpAction) )
		{
			PVP_Script pvpScript = pAction->GetpvpScript ();
			for ( P_Script pScript : (* pvpScript ) )
			{
				PVP_EfGnrt pvpEfGnrt = pScript->GetpvpEfGnrt ();
				for ( P_EfGnrt pEfGnrt : (* pvpEfGnrt) )
				{
					//�񐶐��Ȃ珉��ɓo�^���Ă����AID�ŉғ���Ԃɂ���
					if ( ! pEfGnrt->GetGnrt () )
					{
						//�G�t�F�N�g�C���f�b�N�X�̎擾
						UINT index = pEfGnrt->GetIndex ();

						//�G�t�F�N�g�̎擾
						P_Effect pEf = m_pChara->GetpEffect ( index );
						
						//�G�t�F�N�g�Ǘ��ɓn����ID�𓾂�
//						UINT id = m_oprtEf.AddVectorEffect ( pEf, pEfGnrt->GetZ () );
						
						//ID���L�^
//						pEfGnrt->SetID ( id );
					}
				}
			}
		}
	}

	//�G�t�F�N�g����
	void ExeChara::EffectGenerate ()
	{
		//����
		PVP_EfGnrt  pvpEfGnrt = m_pScript->GetpvpEfGnrt ();
		for ( P_EfGnrt pEfGnrt : (*pvpEfGnrt) )
		{
			//�����p�Ȃ�
			if ( pEfGnrt->GetGnrt () )
			{
				//�G�t�F�N�g�C���f�b�N�X�̎擾
				UINT index = pEfGnrt->GetIndex ();
				//�G�t�F�N�g�̎擾
				P_Effect pEf = m_pChara->GetpEffect ( index );
				//���X�g�ɒǉ�
				m_oprtEf.AddListEffect ( pEf, pEfGnrt, m_ptChara, m_dirRight );
			}
			else //�ė��p�Ȃ�
			{
				int i = 0;
#if false


				//�G�t�F�N�g�C���f�b�N�X�̎擾
				UINT index = pEfGnrt->GetIndex ();
				//�G�t�F�N�g�̎擾
				P_Effect pEf = m_pChara->GetpEffect ( index );
				//�ғ������ǂ���
				if ( !m_oprtEf.IsActive ( pEf ) )
				{
					m_oprtEf.DriveEffect ( pEf );
				}
#endif // false
			}
		}
	}

	void ExeChara::EffectMove ()
	{
		//�G�t�F�N�g�����Ɠ���
		if ( m_FirstEf )	//�q�b�g��̏���݂͓̂���
		{
			EffectGenerate ();
			m_FirstEf = false;
		}
		else
		{
			if ( !m_tmrHitstop->IsActive () )	//�q�b�g�X�g�b�v���͐������Ȃ�
			{
				EffectGenerate ();
			}
		}

		//�G�t�F�N�g����
		m_oprtEf.PreScriptMove ();

		//�G�t�F�N�g����
		m_oprtEf.PostScriptMove ( m_ptChara, m_dirRight );
	}

	//�g�\���ؑ�
	void ExeChara::TurnDispRect ()
	{
		if ( m_bDispRect )
		{
			m_dispChara.OnRect ();
			m_dispChara.SetpCharaRect ( m_charaRect );
			m_oprtEf.OnDispRect ();
		}
		else
		{
			m_dispChara.OffRect ();
			m_oprtEf.OffDispRect ();
		}
	}

	//���C�t����
	void ExeChara::CheckLife ()
	{
		//���C����Ԃ̂Ƃ�
		if ( IsMain () )
		{
			//���������C�t�O
			if ( 0 >= m_life )
			{
				//�_�E����Ԃɋ����ύX
				m_actionID = m_pChara->GetBsAction ( BA_DOWN );
				TransitAction ( m_actionID );
				m_tmrDown->Start ();
				m_charaState = CHST_DOWN;
			}
		}
	}

	//�O���t�B�b�N�X�V
	void ExeChara::UpdateGraphic ()
	{
		//���C���C���[�W
		m_dispChara.UpdateMainImage ( m_pScript, m_ptChara, m_dirRight );

		//�G�t�F�N�g�����Ɠ���
		EffectMove ();

		//�g�\���ؑ�
		TurnDispRect ();

		//�d�����ԕ\��
#if 0
		static bool b2 = true;
		if ( ::GetAsyncKeyState ( '2' ) & 0x0001 ) { b2 ^= 1; }
		if ( b2 )
		{
			//�q�b�g�X�g�b�v����
			m_dispChara.UpdateHitStop ( m_ptChara, m_dirRight, m_hitstop, m_hitstopTimer );

			//�̂����莞��
			m_dispChara.UpdateLurch ( m_ptChara, m_dirRight, m_lurch, m_lurchTimer );
		}
#endif // 0

		//�Q�[�W�X�V
		m_dispChara.UpdateGauge ( m_playerID, m_life, m_damage, m_balance );
	}


	//------------------------------------------------
	//�ʒu�v�Z
	void ExeChara::CalcPos ()
	{
		//------------------------
		// �ʒu (x�̂݌�������Z)
		m_tempPt = m_ptChara;		//�ꎞ�ۑ�
		float dir = m_dirRight ? 1.f: -1.f;		//����

		//------------------------
		// ����
#if 0
		//�U��(�X�N���v�g�J��)���A���݂̊����𔽉f����
		//�����x(����)
		if ( m_transit )
		{
			m_inertial = m_pScript->GetAcc ();
			float dir = m_dirRight ? 1.f : -1.f;
			m_ptChara += dir * m_inertial;
		}

		// �����̌���
		if ( m_inertial.x > 0 )
		{
			m_inertial.x -= 0.3f;
			if ( m_inertial.x < 0 ) { m_inertial.x = 0; }
		}
		else
		{
			m_inertial.x += 0.3f;
			if ( m_inertial.x > 0 ) { m_inertial.x = 0; }
		}

		if ( m_inertial.y > 0 )
		{
			m_inertial.y -= 0.3f;
			if ( m_inertial.y < 0 ) { m_inertial.y = 0; }
		}
		else
		{
			m_inertial.y += 0.3f;
			if ( m_inertial.y > 0 ) { m_inertial.y = 0; }
		}
#endif // 0

		//�v�Z��ނŕ���
		CLC_ST clcSt = m_pScript->GetCalcState ();
		switch ( clcSt )
		{
		case CLC_MAINTAIN: 	//����

			m_vel.x += m_acc.x;		//�����x
			m_ptChara.x += dir * m_vel.x;		//���x
			m_ptChara.x += dir * m_inertial.x;		//����

			m_vel.y += m_acc.y;		//�����x
			m_ptChara.y += m_vel.y;		//���x
			m_ptChara.y += m_inertial.y;		//����

		break;

		case CLC_SUBSTITUDE:	//���

			m_vel.x = m_pScript->GetVel ().x;
			m_acc.x = m_pScript->GetAcc ().x;
			m_ptChara.x += dir * m_vel.x;		//���x
			m_ptChara.x += dir * m_inertial.x;		//����

			m_vg += m_g;
			m_vel.y = m_pScript->GetVel ().y + m_vg;
			m_acc.y = m_pScript->GetAcc ().y;
			m_ptChara.y += m_vel.y;		//���x
			m_ptChara.y += m_inertial.y;		//����

		break;
		
		case CLC_ADD:	//���Z

			m_vel.x += m_pScript->GetVel ().x;
			m_acc.x += m_pScript->GetAcc ().x;
			m_ptChara.x += dir * m_vel.x;		//���x
			m_ptChara.x += dir * m_inertial.x;		//����

			m_vel.y += m_pScript->GetVel ().y;
			m_acc.y += m_pScript->GetAcc ().y;
			m_ptChara.y += m_vel.y;		//���x
			m_ptChara.y += m_inertial.y;		//����

		break;
		
		default: break;
		}

		//---------------
		//���n
		if ( PLAYER_BASE_Y < m_ptChara.y )
		{
			//�f�����͉������Ȃ�
			if ( IsActCtg ( AC_DEMO ) ) 
			{ return; }

			m_ptChara.y = PLAYER_BASE_Y; 
			m_vg = 0;
			m_g = 0;

			//�����A�N�V����m_pAction�͎��t���[������Move()��m_actionID���g���Ď擾�����
			m_actionID = 0;	//stand�̎w��
			m_frame = 0;
		}

		//����
		if ( IsStand () && PLAYER_BASE_Y > m_ptChara.y )
		{
			m_g = 5;
		}

		//---------------
		//��ʒ[
		if ( m_ptChara.x < FIELD_BASE_X + FIELD_EDGE ) { m_ptChara.x = FIELD_BASE_X + FIELD_EDGE; }
		if ( m_ptChara.x > FIELD_WIDTH - FIELD_EDGE ) { m_ptChara.x = FIELD_WIDTH - FIELD_EDGE; }
	}

	void ExeChara::BackMoveX ()
	{
		//�����ɂ�炸�A���肩�痣������
		VEC2 otherPos = m_pOther.lock ()->GetPos ();
		bool dirBack = true;

		//���l�̏ꍇ��1P2P�őI��
		if ( m_ptChara.x == otherPos.x )
		{
			dirBack = (m_playerID == PLAYER_ID_1);
		}
		else
		{
			//�݂��̈ʒu�ŕ␳����������
			dirBack = (m_ptChara.x < otherPos.x);
		}

		m_ptChara.x += dirBack ? -1.f : 1.f;
	}

	void ExeChara::LookOther ()
	{
		//�󒆂͎���
		if ( IsJump () ) { return; }

		//�ʒux�������ꍇ�͎���
		VEC2 otherPos = m_pOther.lock ()->GetPos ();
		if ( m_ptChara.x == otherPos.x ) { return; }

		//�݂��̈ʒu�ŕ���������
		m_dirRight = (m_ptChara.x < otherPos.x);
	}

	//-------------------------------------------------------------------------------------------------
	//	�g�ݒ�
	//-------------------------------------------------------------------------------------------------
	//���݈ʒu����ڐG�g�𔽉f
	void ExeChara::AdjustCRect ()
	{
		m_charaRect->SetCRect ( m_pScript->GetpvCRect (), m_dirRight, m_ptChara );
	}

	//���҂̐ڐG�����ɍU���E���E�E���蔻��g��ݒ�
	void ExeChara::ScriptRectMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );
		if ( m_stop ) { return; }		//�ꎞ��~�̂Ƃ��͉������Ȃ�

		//���E�g�ݒ�
		m_charaRect->SetORect ( m_pScript->GetpvORect (), m_dirRight, m_ptChara );

		//�U���g�ݒ�
		// �q�b�g���Ɍ�̍U���g���ꎞ��~(���i�h�~)
		//�U���������E�ō����ɓ���A�N�V�������̂ݘg������������
		if ( m_hitEst || m_clang )
		{
			m_charaRect->ResetARect ();
		}
		else
		{
			m_charaRect->SetARect ( m_pScript->GetpvARect (), m_dirRight, m_ptChara );
		}

		//�U���͐ݒ�
		m_power = m_pScript->GetPower ();

		//����g�ݒ�
		m_charaRect->SetHRect ( m_pScript->GetpvHRect (), m_dirRight, m_ptChara );
	}

	//------------------------------------------------
	//�A�N�V�����I������
	void ExeChara::EndAction ()
	{
		m_frame = 0;				//�t���[��������
		m_clang = false;
		m_hitEst = false;
		m_FirstEf = false;
//		m_lurch = 0;
//		m_lurchTimer = 0;
	}

	void ExeChara::SetEndWait ()
	{
		//�_�E���D��
		if ( IsDown () ) { return; }

		m_charaState = CHST_END_WAIT;
	}


	//�̂�����^�C�}�[
#if 0
	bool ExeChara::LurchTimer ()
	{
		// �̂����莞�Ԃ̓R�}���h�ɂ��s���s��
		if ( 0 < m_lurch )
		{
			if ( m_lurchTimer == m_lurch )	//�̂�����I��
			{
				m_lurch = 0;
				m_lurchTimer = 0;
			}
			else
			{
				++m_lurchTimer;
				return true;
			}
		}
		return false;
	}
#endif // 0

	//���͂������Ԃ��ǂ���
	bool ExeChara::CanInput () const
	{
		return IsMain ();
	}

	bool ExeChara::IsMain () const
	{
		switch ( m_charaState )
		{
		case CHST_MAIN: return true;  break;

		case CHST_START:
		case CHST_DOWN:
		case CHST_WIN:
		case CHST_END_WAIT:
		case CHST_WIN_END:
			return false; break;
		}
		return false;
	}


}	//namespace GAME

