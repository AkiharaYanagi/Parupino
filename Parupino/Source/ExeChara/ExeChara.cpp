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
		: m_pChara ( nullptr )
		, m_playerID ( m_playerID ), m_name ( CHARA_RAKUNO ), m_playerMode ( MODE_PLAYER )
		, m_actionID ( 0 ), m_frame ( 0 )
		, m_bDispRect ( true )
		, m_charaState ( CHST_START )
	{
		//�L�����f�[�^����
		m_pChara = make_shared < Chara > ();	//�L�����f�[�^����
		m_charaRect = make_shared < CharaRect > ();		//�g
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
		//���O����X�N���v�g�t�@�C�����w�肵�ăL�����̃��[�h
		//��	D3DX�̃e�N�X�`����p���邽�߃t�H�[�J�X�ύX���ȂǂɍĐݒ�(Reset())���K�v
//		tstring name (_T ("testChara.dat"));
		tstring name (_T ("chara.dat"));
#if 0
		switch ( m_name )
		{
		case CHARA_RAKUNO: name.assign ( _T ( "Rakuno.dat" ) ); break;
		case CHARA_YUKINO: name.assign ( _T ( "Yukino.dat" ) ); break;
		default: break;
		}
#endif // 0
		LoadChara loadChara ( name, *m_pChara );

		//�L�����\��������
		m_dispChara.SetpChara ( m_pChara );
		m_dispChara.Load ();

		//�L�������͏�����
		m_dispInput.Load ();

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

		//�o�g���p�����[�^
		m_btlPrm.InitPlayerID ( m_playerID );
		m_btlPrm.Init ();

		//�\��
		//@info Move()����Transit()�̌�ɑJ�ڂ��A
		//		�ēxMove()�͌Ă΂ꂸDraw()���Ă΂�邽�߁A�����ŏ��������K�v(Init()�͌Ă΂��)
		m_dispChara.UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );
		m_dispChara.InitDisp ( m_playerID );

		m_dispInput.InitDisp ( m_playerID );

		TASK_VEC::Init ();
	}

	//�Đݒ�
	void ExeChara::Reset ()
	{
		_Reset ();	//������
	}

	//------------------------
	//�������̍Đݒ�
	void ExeChara::_Reset ()
	{
		//�e�N�X�`���������m�ۊ֘A�͍Đݒ�
		Rele ();
		m_pChara = make_shared < Chara > ();
		Load ();
		m_dispChara.SetpChara ( m_pChara );
		m_oprtEf.SetpChara ( m_pChara );

		//�A�N�V�����E�X�N���v�g�Ď擾
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//���C�� �C���[�W
		m_dispChara.UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );

		//�G�t�F�N�g �C���[�W
		m_oprtEf.PostScriptMove ( GetPos (), GetDirRight () );
	}

	//==========================================================
	//MutualChara����Ă΂���Ȋ֐�
	//==========================================================
	//	�� ��������
	//	void ExeChara::PreScriptMove ();	//	�X�N���v�g�O����
	//	void MutualChara::Collision ();		//	���ݔ��� (�ڐG�g)
	//	void ExeChara::ScriptRectMove ();	//	�Ԃ����A����g��ݒ�
	//	void MutualChara::Decision ();		//	���ݔ��� (�U���g�A�q�b�g�g)
	//	void ExeChara::PostScriptMove ();	//	�X�N���v�g�㏈��

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
		//	���͂Ȃ�
		AlwaysMove ();

		//�ꎞ��~�̂Ƃ��͉������Ȃ�
		if ( m_btlPrm.GetTmr_Stop()->IsActive () )
		{ return; }

		// �q�b�g�X�g�b�v���͓��͂̕ۑ��ƕ\���֘A�̏��������ďI��
		//Active�Ƃ̌��ˍ����Ń^�C�}�[�̃��X�g�͗L���@0�`N-1�܂�
		if ( ! m_btlPrm.GetTmr_HitStop()->IsLast () )
		{
			if ( m_btlPrm.GetTmr_HitStop ()->IsActive () ) { return; }
		}
#if 0
		if ( m_btlPrm.GetTmr_HitStop ()->IsActive () )
		{ return; }
#endif // 0


		// �A�N�V�����ڍ�
		TransitAction ();

		// �ʒu�v�Z
		m_btlPrm.CalcPos ( m_pScript );

		// ���n
		Landing ();

		//�ڐG�g�ݒ�
		AdjustCRect ();
	}


	//��###########################################################################
	//��		
	//��		���҂̐ڐG�����ɍU���E���E�E���蔻��g��ݒ�
	//��		
	//��###########################################################################
	void ExeChara::ScriptRectMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//�ꎞ��~�̂Ƃ��͉������Ȃ�
		if ( m_btlPrm.GetStop () ) { return; }

		//���E�g�ݒ�
		m_charaRect->SetORect ( m_pScript->GetpvORect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );

		//�U���g�ݒ�
		// �q�b�g���Ɍ�̍U���g���ꎞ��~(���i�h�~)
		//�U���������E�ō����ɓ���A�N�V�������̂ݘg������������
		if ( m_btlPrm.GetHitEst () || m_btlPrm.GetClang () )
		{
			m_charaRect->ResetARect ();
		}
		else
		{
			m_charaRect->SetARect ( m_pScript->GetpvARect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
		}

		//�U���͐ݒ�
//		m_power = m_pScript->GetPower ();

		//����g�ݒ�
		m_charaRect->SetHRect ( m_pScript->GetpvHRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
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
		
		//1[F]�Ɉ�x�s������
		AlwaysPostMove ();

		//�ꎞ��~�̂Ƃ��͉������Ȃ�
		if ( m_btlPrm.GetStop () ) { return; }

		//���C�t����
		CheckLife ();

		// �O���t�B�b�N
		UpdateGraphic ();
	}

	//==========================================================


	//================================================
	//	�O������̏�ԕύX
	//================================================

	//�ō�����
	void ExeChara::OnClang ( UINT nLurch, CLANG_DECISION_WL clangDecision )
	{
#if 0
//		if ( CD_LOSE == clangDecision )
		{
			//��Ԃ̕ύX
			m_actionID = m_pChara->GetBsAction ( BA_CLANG );
			m_frame = 0;
		}
#endif // 0
		m_btlPrm.SetClang ( true );		//�ō����
//		m_lurch = nLurch;		//�̂����莞�Ԃ̐ݒ�
		m_btlPrm.GetTmr_HitStop()->Start ();		//�q�b�g�X�g�b�v�̐ݒ�
	}


	//����E�U�� �� �����E���炢
	//���炢��ԁE�_���[�W����
	void ExeChara::OnDamaged ( int damage )
	{

		bool hit = true;
		bool guard = false;


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

		//�K�[�h����
#if 0
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
#endif // 0

		//���炢�� ( �K�[�h�����Ă��Ȃ� ) && ( �����ύX����Ă��Ȃ� )
		if ( hit && ! m_btlPrm.GetForcedChange () )
		{
			int lf = m_btlPrm.GetLife ();
			//�_���[�W�����C�t�ɂ���ĕ␳(�����l)
			if ( lf < LIFE_MAX * 0.5f )
			{
				damage = (int)(damage * (0.001f * (0.5f * LIFE_MAX + lf )));
			}

			//�_���[�W����
			if ( lf < damage ) { m_btlPrm.SetDamage ( lf ); }	//���C�t�ȏ�͕\������
			else { m_btlPrm.SetDamage ( damage ); }		//�\���p

			m_btlPrm.SetLife ( lf - damage );

			//��Ԃ̕ύX
#if 0
			tstring act;
			switch ( m_pAction->GetPosture () )
			{
			case AP_STAND:	act.assign ( _T ( "Damaged_L" ) ); break;
			case AP_CROUCH: act.assign ( _T ( "C_DamagedL" ) ); break;
			case AP_JUMP:	act.assign ( _T ( "J_DamagedL" ) ); break;
			}
			TransitAction ( m_pChara->GetActionID ( act ) );
#endif // 0

			//���̑��@����
			m_btlPrm.GetTmr_HitStop ()->Start ();			//�q�b�g�X�g�b�v�̐ݒ�
			m_btlPrm.SetFirstEf ( true );			//����̂݃G�t�F�N�g����
			m_btlPrm.SetFirstSE ( true );			//����̂�SE����

		}
	}

	//�q�b�g����(�U��������)
	//�����E�U�� -> ����E���炢
	void ExeChara::OnHit ()
	{
		m_btlPrm.SetHitEst ( true );		//�U�������t���O

		//-----------------------------------------------------
		//��������

		//�����E����
		UINT indexAction_i = TransitAction_Condition ( BRC_THR_I );
		if ( NO_COMPLETE != indexAction_i )
		{
			//�J�ڐ�`�F�b�N
			P_Action pact = m_pChara->GetpAction ( indexAction_i );
			P_Script pscr = pact->GetpScript ( 0 );

			m_actionID = indexAction_i;			//�J��
		}

		//�����E����
		UINT indexAction_e = TransitAction_Condition ( BRC_THR_E );
		if ( NO_COMPLETE != indexAction_e )
		{
			//�J�ڐ�`�F�b�N
			P_Action pact = m_pChara->GetpAction ( indexAction_e );
			P_Script pscr = pact->GetpScript ( 0 );

			m_pOther.lock ()->TransitAction ( indexAction_e );			//�J��
			m_pOther.lock ()->m_btlPrm.SetForcedChange ( true );
		}

		//�q�b�g�E����
		UINT indexAction_Hit_m = TransitAction_Condition ( BRC_HIT_I );
		if ( NO_COMPLETE != indexAction_Hit_m )
		{
			//�J�ڐ�`�F�b�N
			P_Action pact = m_pChara->GetpAction ( indexAction_Hit_m );
			P_Script pscr = pact->GetpScript ( 0 );

			m_actionID = indexAction_Hit_m;			//�J��
			TransitAction ( m_actionID );
		}

		//�q�b�g�E����
		UINT indexAction_Hit_e = TransitAction_Condition ( BRC_HIT_E );
		if ( NO_COMPLETE != indexAction_Hit_e )
		{
			//�J�ڐ�`�F�b�N
			P_Action pact = m_pChara->GetpAction ( indexAction_Hit_e );
			P_Script pscr = pact->GetpScript ( 0 );

			m_pOther.lock ()->TransitAction ( indexAction_Hit_e );			//�J��
			m_pOther.lock ()->m_btlPrm.SetForcedChange ( true );
		}
		//-----------------------------------------------------

		m_btlPrm.GetTmr_HitStop()->Start ();		//�q�b�g�X�g�b�v�̐ݒ�
	}

	//�G�t�F�N�g�q�b�g����(�U��������)
	void ExeChara::OnEfHit ()
	{
		m_btlPrm.SetHitEst ( true );		//�U�������t���O
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
		//�_���[�W���̃��C�t�\������
		int dmg = m_btlPrm.GetDamage ();
		if ( 0 < dmg ) { m_btlPrm.SetDamage ( dmg - 1 ); }

		//---------------------------------------------------
		//�f���J�E���g
		//�_�E����Ԃ̂Ƃ�
		if ( CHST_DOWN == m_charaState )
		{
			if ( ! m_btlPrm.GetTmr_Down()->IsActive () )
			{
				m_charaState = CHST_DOWN_END;
			}
		}

		//�����ҋ@��Ԃ̂Ƃ�
		if ( CHST_WIN_WAIT == m_charaState )
		{
#if 0
			//�n��j���[�g�����Ȃ�
			if ( IsBasicAction ( BA_STAND ) )
			{
				//������ԂɈڍs
				m_actionID = m_pChara->GetBsAction ( BA_WIN );
				TransitAction ( m_actionID );
				m_tmrEnd->Start ();
				m_charaState = CHST_WIN;
			}
#endif // 0
		}

		//������Ԃ̂Ƃ�
		if ( CHST_WIN == m_charaState )
		{
			//if ( ! m_tmrEnd->IsActive () )
			if ( ! m_btlPrm.GetTmr_End () ->IsActive () )
			{
				m_charaState = CHST_WIN_END;
			}
		}
		//---------------------------------------------------
		//SE
		if ( m_btlPrm.GetFirstEf () )
		{
			SOUND->Play ( SE_Hit );
			m_btlPrm.SetFirstEf ( F );
		}

		//---------------------------------------------------
		//����
		// ���͂��\�ȏ��
		if ( CanInput () )
		{
			//���͂̕ۑ�
			m_pCharaInput->Update ( GetDirRight () );
		}
		//���͍X�V
		m_dispInput.UpdateInput ( m_pCharaInput );

	}


	//�A�N�V�����̈ڍ�(���ڎw��)
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

	// �A�N�V�����ڍ�(����:�R�}���h, �A�N�V�����I��)
	void ExeChara::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		// �̂����莞�Ԃ̓R�}���h�ɂ��s���s��
#if 0
		if ( LurchTimer () ) { return; }
#endif // 0

		// �R�}���h�ɂ�镪��
		UINT transitID = m_pCharaInput->GetTransitID ( *m_pChara, m_pScript, m_btlPrm.GetDirRight () );

		//�R�}���h���������Ă�����
		if ( NO_COMPLETE != transitID )
		{
			//�J�ڐ�`�F�b�N
			P_Action pact = m_pChara->GetpAction ( transitID );
			P_Script pscr = pact->GetpScript ( 0 );

			m_actionID = transitID;			//�J��

			//�e���Ԃ̏I��
			m_btlPrm.EndAction ();
			m_frame = 0;

			//m_frame��0����J�n�AMove()��Draw()�œ���X�N���v�g����������
			//���̃t���[���ŃX�N���v�g���������邽�߁A�ڍs��A�N�V�����ƃX�N���v�g��ۑ�
			m_pAction = m_pChara->GetpAction ( m_actionID );
			m_pScript = m_pAction->GetpScript ( m_frame );
		}
		//---------------------------------------------------

		//�R�}���h�Ŕ�J�� ����
		else
		{
			//���݃A�N�V�������ŏI�t���[�� �Ȃ��
			if ( m_pAction->IsEndScript ( m_frame ) )
			{
				int i = 0;
			}
			
			if ( m_pAction->IsOverScript ( m_frame ) )
			{
				//�����A�N�V����m_pAction�͎��t���[������Move()��m_actionID���g���Ď擾�����
				m_actionID = m_pAction->GetNextID ();
				m_frame = 0;
				//����̃t���[������m_pAction��m_pScript��p���A
				//����ȍ~��m_actionID��m_frame��p���Ȃ�

				//m_frame��0����J�n�AMove()��Draw()�œ���X�N���v�g����������
				//���̃t���[���ŃX�N���v�g���������邽�߁A�ڍs��A�N�V�����ƃX�N���v�g��ۑ�
				m_pAction = m_pChara->GetpAction ( m_actionID );
				m_pScript = m_pAction->GetpScript ( m_frame );
			}
			else
			{
				//m_frame��0����J�n�AMove()��Draw()�œ���X�N���v�g����������
				//���̃t���[���ŃX�N���v�g���������邽�߁A�ڍs��A�N�V�����ƃX�N���v�g��ۑ�
				m_pAction = m_pChara->GetpAction ( m_actionID );
				m_pScript = m_pAction->GetpScript ( m_frame );

				//�ʏ폈���F�X�N���v�g���P�i�߂�
				++ m_frame;
			}
		}
		//---------------------------------------------------

		assert ( nullptr != m_pAction && nullptr != m_pScript );
	}

	//�A�N�V�����ڍs(����)
	UINT ExeChara::TransitAction_Condition ( BRANCH_CONDITION BRC_CND )
	{
		//�L�����̎����[�g,�u�����`,�R�}���h�̎Q��
		const VP_Route vpRoute = m_pChara->GetvpRoute ();
		const VP_Branch vpBranch = m_pChara->GetvpBranch ();

		//�X�N���v�g�̎����[�g���X�g
		for ( UINT indexRut : m_pScript->GetvRouteID () )
		{
			const V_UINT vBrcID = vpRoute [ indexRut ]->GetvIDBranch ();

			//�Ώۂ̃u�����`���X�g
			for ( UINT id : vBrcID )
			{
				//��������
				if ( BRC_CND != vpBranch [ id ]->GetCondition () ) { continue; }

				return vpBranch [ id ]->GetIndexSequence ();
			}
		}
		return NO_COMPLETE;
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
				m_oprtEf.AddListEffect ( pEf, pEfGnrt, m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );
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
		if ( m_btlPrm.GetFirstEf () )	//�q�b�g��̏���݂͓̂���
		{
			EffectGenerate ();
			m_btlPrm.SetFirstEf ( F );
		}
		else
		{
			if ( ! m_btlPrm.GetTmr_HitStop ()->IsActive () )	//�q�b�g�X�g�b�v���͐������Ȃ�
			{
				EffectGenerate ();
			}
		}

		//�G�t�F�N�g����
		m_oprtEf.PreScriptMove ();

		//�G�t�F�N�g����
		m_oprtEf.PostScriptMove ( m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );
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
			if ( 0 >= m_btlPrm.GetLife () )
			{
				//�_�E����Ԃɋ����ύX
				//m_actionID = m_pChara->GetBsAction ( BA_DOWN );
				TransitAction ( m_actionID );
				m_btlPrm.GetTmr_Down ()->Start ();
				m_charaState = CHST_DOWN;
			}
		}
	}

	//�O���t�B�b�N�X�V
	void ExeChara::UpdateGraphic ()
	{
		//���C���C���[�W
		m_dispChara.UpdateMainImage ( m_pScript, m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );

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


		//@todo ���ʃO���t�B�b�N�̋L�q�ʒu�𒲐�
		//��~���̃X�L�b�v�ɂ��

		//���ʃO���t�B�b�N
		if ( ! m_btlPrm.GetTmr_Stop()->IsActive () )
		{
			//�Ó]
			m_btlPrm.SetBlackOut ( m_pScript->GetBlackOut () );

			//�X�N���v�g����̒�~
			m_btlPrm.SetScpStop ( m_pScript->GetStop () );
		}

		//�Q�[�W�X�V
		m_dispChara.UpdateGauge ( m_playerID, m_btlPrm.GetLife (), m_btlPrm.GetDamage (), m_btlPrm.GetBalance () );

	}

	//���n
	void ExeChara::Landing ()
	{
		VEC2 pos = m_btlPrm.GetPos ();
		if ( PLAYER_BASE_Y < pos.y )
		{
			//�f�����͉������Ȃ�
			if ( IsActCtg ( AC_DEMO ) )
			{
				return;
			}

			float x = pos.x;
			float y = PLAYER_BASE_Y;
			m_btlPrm.SetPos ( VEC2 ( x, y ) );
			m_btlPrm.SetVg ( 0 );
			m_btlPrm.SetG ( 0 );

			//�����A�N�V����m_pAction�͎��t���[������Move()��m_actionID���g���Ď擾�����
			m_actionID = 0;	//stand�̎w��
			m_frame = 0;
		}

		//����
		if ( IsStand () && PLAYER_BASE_Y > m_btlPrm.GetPos ().y )
		{
			m_btlPrm.SetG ( 5 );
		}
	}


	void ExeChara::BackMoveX ()
	{
		//�����ɂ�炸�A���肩�痣������
		VEC2 iPos = m_btlPrm.GetPos ();
		VEC2 ePos = m_pOther.lock ()->GetPos ();
		bool dirBack = true;

		//���l�̏ꍇ��1P2P�őI��
		if ( iPos.x == ePos.x )
		{
			dirBack = ( m_playerID == PLAYER_ID_1 );
		}
		else
		{
			//�݂��̈ʒu�ŕ␳����������
			dirBack = ( iPos.x < ePos.x );
		}

		float x = iPos.x + ( dirBack ? -1.f : 1.f );
		float y = iPos.y;
		m_btlPrm.SetPos ( VEC2 ( x, y ) );
	}

	void ExeChara::LookOther ()
	{
		//�󒆂͎���
		if ( IsJump () )
		{
			return;
		}

		//�ʒux�������ꍇ�͎���
		VEC2 iPos = m_btlPrm.GetPos ();
		VEC2 ePos = m_pOther.lock ()->GetPos ();
		if ( iPos.x == ePos.x )
		{
			return;
		}

		//�݂��̈ʒu�ŕ���������
		m_btlPrm.SetDirRight ( iPos.x < ePos.x );
	}


	//-------------------------------------------------------------------------------------------------
	//	�g�ݒ�
	//-------------------------------------------------------------------------------------------------
	//���݈ʒu����ڐG�g�𔽉f
	void ExeChara::AdjustCRect ()
	{
		m_charaRect->SetCRect ( m_pScript->GetpvCRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
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

	void ExeChara::AlwaysPostMove ()
	{
		m_btlPrm.Move ();
	}



}	//namespace GAME

