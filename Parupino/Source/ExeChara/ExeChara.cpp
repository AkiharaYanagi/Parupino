//=================================================================================================
//
// �G�O�[�L�����@�\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"
#include "Input/PlayerInput.h"
#include "Input/CPUInput.h"
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�R���X�g���N�^
	ExeChara::ExeChara ( PLAYER_ID m_playerID )
		: m_pChara ( nullptr )
		, m_playerID ( m_playerID ), m_name ( CHARA_TEST ), m_playerMode ( MODE_PLAYER )
		, m_actionID ( 0 ), m_frame ( 0 )
	{
		//�L�����f�[�^����
		m_pChara = make_shared < Chara > ();	//�L�����f�[�^����
		m_charaRect = make_shared < CharaRect > ();	//�����g
		m_btlPrm.LoadPlayerID ( m_playerID );	//�o�g���p�����[�^

		//�\��
		m_dispChara = make_shared < DispChara > ();
		m_dispChara->LoadPlayer ( m_playerID );	//�\��(1P/2P���ɂ��ʒu)
		AddpTask ( m_dispChara );

		//�G�t�F�N�g�ė�
		m_oprtEf = make_shared < OperateEffect > ();
		AddpTask ( m_oprtEf );
	}

	//�f�X�g���N�^
	ExeChara::~ExeChara ()
	{
	}

	//------------------------
	//�V�[���p�����[�^�֘A������
	void ExeChara::ParamInit ( P_Param pParam )
	{
		//�Q�[���ݒ�
		GameSettingFile stg = pParam->GetGameSetting ();

		//�I���L�������O�E���[�h���擾
		m_name = stg.GetName ( m_playerID );
		m_playerMode = stg.GetPlayerMode ( m_playerID );

		//�v���C�����[�h(���͎��)�ɂ�鏉����
		switch ( m_playerMode )
		{
		case MODE_PLAYER: m_pCharaInput = make_shared < PlayerInput > (); break;
		case MODE_CPU: m_pCharaInput = make_shared < CPUInput > ( shared_from_this (), m_pOther ); break;
		case MODE_NETWORK: m_pCharaInput = make_shared < PlayerInput > (); break;	//(��)
		default: break;
		}
		m_pCharaInput->SetPlayer ( m_playerID );

		m_dispChara->ParamInit ( pParam );
	}

	//------------------------
	//�Ǎ�
	void ExeChara::Load ()
	{
		//--------------------------------------------
		//m_pChara�̃f�[�^�Ǎ�
		_Load ();

		//--------------------------------------------
		//�L�����\��������
		m_dispChara->SetpChara ( m_pChara );
		m_dispChara->SetpCharaRect ( m_charaRect );

		//�G�t�F�N�g�����x�N�^�̐���
		MakeEfOprt ();

		//�A�N�^�E�X�e�[�g�ɗp�����ԃp�����[�^�ɓo�^
		m_actor.SetwpExeChara ( shared_from_this () );

		TASK_VEC::Load ();
	}

	void ExeChara::_Load ()
	{
		//--------------------------------------------
		//m_pChara�̃f�[�^�Ǎ�

//���O����X�N���v�g�t�@�C�����w�肵�ăL�����̃��[�h
//��	D3DX�̃e�N�X�`����p���邽�߃t�H�[�J�X�ύX���ȂǂɍĐݒ�(Reset())���K�v
//		tstring name (_T ("testChara.dat"));
//		tstring name ( _T ( "chara.dat" ) );
		tstring name ( _T ( "charaBin.dat" ) );
		//		tstring name (_T ("chara_standBin.dat"));
#if 0
		switch ( m_name )
		{
		case CHARA_RAKUNO: name.assign ( _T ( "Rakuno.dat" ) ); break;
		case CHARA_YUKINO: name.assign ( _T ( "Yukino.dat" ) ); break;
		default: break;
		}
#endif // 0

		//�o�C�i���f�[�^�Ǎ�
		LoadCharaBin loadCharaBin ( name.c_str (), *m_pChara );
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
		m_btlPrm.Init ();
		SetParamFromScript ();	//�X�N���v�g����p�����[�^�𔽉f����

		//�g
		m_charaRect->ResetAllRect ();

		//���
		m_actor.Init ();

		//�\��
		//@info Move()����Transit()�̌�ɑJ�ڂ��A
		//		�ēxMove()�͌Ă΂ꂸDraw()���Ă΂�邽�߁A�����Ŏ蓮�̏��������K�v(Init()�͌Ă΂��)
		m_dispChara->UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );
		//���͕\���X�V
		m_dispChara->UpdateInput ( m_pCharaInput );


		TASK_VEC::Init ();
	}

	//�Đݒ�
	void ExeChara::Reset ()
	{
		_Reset ();	//������

		TASK_VEC::Reset ();
	}

	//------------------------
	//�������̍Đݒ�
	void ExeChara::_Reset ()
	{
		//�e�N�X�`���������m�ۊ֘A�͍Đݒ�
		Rele ();
		m_pChara = make_shared < Chara > ();
		Load ();
		m_dispChara->SetpChara ( m_pChara );
		m_oprtEf->SetpChara ( m_pChara );

		//�A�N�V�����E�X�N���v�g�Ď擾
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//���C�� �C���[�W
		m_dispChara->UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );

		//�G�t�F�N�g �C���[�W
		m_oprtEf->PostScriptMove ( GetPos (), GetDirRight () );
	}

	//==========================================================
	//MutualChara����Ă΂���Ȋ֐�
	//==========================================================
	//	�� ��������
	//	void ExeChara::PreScriptMove ();	//	�X�N���v�g�O����
	//	void MutualChara::Collision ();		//	���ݔ��� (�ڐG�g)
	//	void ExeChara::RectMove ();			//	�Ԃ����A����g��ݒ�
	//	void MutualChara::Decision ();		//	���ݔ��� (�U���g�A�q�b�g�g)
	//	void ExeChara::PostScriptMove ();	//	�X�N���v�g�㏈��

	//��	���t���[�� �X�N���v�g�O����
	void ExeChara::PreScriptMove () { m_actor.PreScriptMove (); }

	//��	���҂̐ڐG�����ɍU���E���E�E���蔻��g��ݒ�
	void ExeChara::RectMove () { m_actor.RectMove (); }

	//��	���t���[�� �X�N���v�g�㏈��
	void ExeChara::PostScriptMove () { m_actor.PostScriptMove (); }


	//================================================
	//	�O������̏�ԕύX
	//================================================
	void ExeChara::StartGreeting () { m_actor.StartGreeting (); }
	void ExeChara::StartGetReady () { m_actor.StartGetReady (); }
	void ExeChara::StartFighting () { m_actor.StartFighting (); }



	//================================================
	//	�����֐�
	//================================================

	// �A�N�V�����ڍ�(����:�R�}���h, �A�N�V�����I��)
	void ExeChara::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		// �̂����莞�Ԃ̓R�}���h�ɂ��s���s��
#if 0
		if ( LurchTimer () ) { return; }
#endif // 0


		//-----------------------------------------------------
		//�o�����X�A�E�g
		if ( m_btlPrm.GetBalance () <= 0 )
		{
			SetAction ( _T ( "Dotty" ) );
		}


		//-----------------------------------------------------
		// �R�}���h�ɂ�镪��
		if ( TranditAction_Command () )
		{
			//���򂪐������Ă�����ȍ~�̓`�F�b�N���Ȃ�
			return;
		}

		//-----------------------------------------------------
		//���݃X�N���v�g�����݃A�N�V�����ɂ�����ŏI�t���[�� �Ȃ��
		if ( m_pAction->IsOverScript ( m_frame ) )
		{
			//�A�N�V�����I������
			EndAction ();

			//�����A�N�V����m_pAction�͎��t���[������Move()��m_actionID���g���Ď擾�����
			m_actionID = m_pAction->GetNextID ();
			TransitScript ();

			//�I��
			return;
		}

		//-----------------------------------------------------
		// �X�N���v�g�ʏ폈��
#if 0
		//m_frame��0����J�n�AMove()��Draw()�œ���X�N���v�g����������
		//���̃t���[���ŃX�N���v�g���������邽�߁A�ڍs��A�N�V�����ƃX�N���v�g��ۑ�
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );
#endif // 0
		TransitScript ();

		//�ʏ폈���F�X�N���v�g���P�i�߂�
		++ m_frame;
	}


	//�A�N�V�����ڍ��i�R�}���h�Ɋւ��鏈���j
	bool ExeChara::TranditAction_Command ()
	{
		//-----------------------------------------------------
		//�e�X�g�p
		//����̃A�N�V����
		if ( IsNameAction ( _T ( "FrontDash" ) ) )
		{
			int i = 0;
		}

		//-----------------------------------------------------
		// �R�}���h�ɂ�镪��

//		UINT transitID = m_pCharaInput->GetTransitID ( *m_pChara, m_pScript, m_btlPrm.GetDirRight () );

		//�R�}���h����������ID��D�揇�ɕۑ��������X�g
		m_pCharaInput->MakeTransitIDList ( *m_pChara, m_pScript, m_btlPrm.GetDirRight () );
		const std::vector < UINT > & vCompID = m_pCharaInput->GetvCompID ();

		UINT transitID = NO_COMPLETE;
		for ( UINT id : vCompID )
		{
			//�J�ڐ�`�F�b�N
			P_Action pact = m_pChara->GetpAction ( id );

			//�Ώ�ID���o�����X����ňڍ��\�Ȃ�ړ�������


			//�s�\�Ȃ玟���`�F�b�N
			transitID = id;
			break;
		}


		//�R�}���h���������Ă�����
		if ( NO_COMPLETE != transitID )
		{
			//���K�@���菈��
			if ( transitID == m_pChara->GetActionID ( _T ( "OD0_L" ) ) )
			{
				//�}�i����
				if ( m_btlPrm.GetMana () >= MANA_HALF )
				{
					m_btlPrm.AddMana ( - MANA_MAX / 2 );
				}
				else //����Ȃ��Ƃ��J�ڂ��Ȃ�
				{
					return F;
				}
			}

			//���݃A�N�V�����Ƃ��čŌ�̏���
			EndAction ();

			//�J�ڐ�`�F�b�N
			P_Action pact = m_pChara->GetpAction ( transitID );
			P_Script pscr = pact->GetpScript ( 0 );


			//�o�����X����
			int bl_a = pact->GetBalance ();		//�A�N�V��������o�����X
			int bl_p = m_btlPrm.GetBalance ();	//�p�����[�^���݃o�����X

			int d = bl_p - bl_a;
			if ( d < 0 ) { d = 0; }
			m_btlPrm.SetBalance ( d );


			//�A�N�V�����J��
			m_actionID = transitID;
			TransitScript ();

			//�v��
			m_btlPrm.AddNActTrs ( 1 );

			//���t���[���̃X�N���v�g���P�i�߂�
			//����t���[���͎擾�ς݂�m_pScript��p����
			++ m_frame;

			//�I��
			return T;
		}

		return F;
	}


	//�A�N�V�����̈ڍ�(���ڎw��)
#if 0
	void ExeChara::TransitAction ( UINT actionID )
	{
		m_actionID = actionID;		//�J��
		m_frame = 0;		//�X�N���v�g������

		//�ꎞ�A�N�V�����ƃX�N���v�g���Đݒ�
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );
	}
#endif // 0
	void ExeChara::SetAction ( tstring action_name )
	{
		SetAction ( m_pChara->GetActionID ( action_name ) );
	}

	void ExeChara::SetAction ( UINT action_id )
	{
		m_actionID = action_id;
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_frame = 0;
		m_pScript = m_pAction->GetpScript ( m_frame );

		//�X�N���v�g����̃p�����[�^���f
		SetParamFromScript ();
	}

	//�X�N���v�g��J�ڂ�����
	void ExeChara::TransitScript ()
	{
		//����̃t���[������m_pAction��m_pScript��p���A
		//����ȍ~��m_actionID��m_frame��p���Ȃ�
		//���̃t���[���ŃX�N���v�g���������邽�߁A�ڍs��A�N�V�����ƃX�N���v�g��ۑ�
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//�X�N���v�g����̃p�����[�^���f
		SetParamFromScript ();

		//����A�N�V�����w��

		//�_�b�V���J�n
		if ( IsNameAction ( _T ( "FrontDashStart" ) ) )
		{
			if ( m_frame == 0 )
			{
				//SE
				SOUND->Play_SE ( SE_Btl_Dash );
			}
		}
		//�W�����v
		if ( IsNameAction ( _T ( "FrontJump" ) )
			|| IsNameAction ( _T ( "VerticalJump" ) )
			|| IsNameAction ( _T ( "BackJump" ) )
			)
		{
			if ( m_frame == 0 )
			{
				//SE
				SOUND->Play_SE ( SE_Btl_Jump );
			}
		}

	}

	//�X�N���v�g����p�����[�^�𔽉f����
	void ExeChara::SetParamFromScript ()
	{
		//�Ó]
		m_btlPrm.SetBlackOut ( m_pScript->m_prmStaging.BlackOut );
	}





	//�A�N�V�����ڍs(���g)
	void  ExeChara::TransitAction_Condition_I ( BRANCH_CONDITION CONDITION, bool forced )
	{
		//�q�b�g�E����
		UINT indexAction = Check_TransitAction_Condition ( CONDITION );
		if ( NO_COMPLETE != indexAction )
		{
			//�J�ڐ�`�F�b�N
			P_Action pAct = m_pChara->GetpAction ( indexAction );
			P_Script pScr = pAct->GetpScript ( 0 );

			//���g��ύX
			SetAction ( indexAction );	//�J��
			m_btlPrm.SetForcedChange ( forced );
		}
	}

	//�A�N�V�����ڍs(����)
	void  ExeChara::TransitAction_Condition_E ( BRANCH_CONDITION CONDITION, bool forced )
	{
		//�q�b�g�E����
		UINT indexAction = Check_TransitAction_Condition ( CONDITION );
		if ( NO_COMPLETE != indexAction )
		{
			//�J�ڐ�`�F�b�N
			P_Action pAct = m_pChara->GetpAction ( indexAction );
			P_Script pScr = pAct->GetpScript ( 0 );

			//�����ύX
			m_pOther.lock ()->SetAction ( indexAction );	//�J��
			m_pOther.lock ()->m_btlPrm.SetForcedChange ( forced );
		}
	}

	//�A�N�V�����ڍs(�����`�F�b�N)
	UINT ExeChara::Check_TransitAction_Condition ( BRANCH_CONDITION BRC_CND )
	{
		//�L�����̎����[�g,�u�����`,�R�}���h�̎Q��
		const VP_Route& vpRoute = m_pChara->GetvpRoute ();
		const VP_Branch& vpBranch = m_pChara->GetvpBranch ();

		//�X�N���v�g�̎����[�g���X�g
		for ( UINT indexRut : m_pScript->GetcvRouteID () )
		{
			const V_UINT& vBrcID = vpRoute [ indexRut ]->GetcvIDBranch ();

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


	//====================================================================================
	// �ʒu�v�Z
	void ExeChara::CalcPos ()
	{
		//�o�����X����
		int b = m_btlPrm.GetBalance ();
		int sb = m_pScript->m_prmBattle.Balance_I;
		b -= sb;
		if ( b < 0 ) { b = 0; }
		if ( b > BALANCE_MAX ) { b = BALANCE_MAX; }

		m_btlPrm.SetBalance ( b );

		//�ʒu�v�Z
		m_btlPrm.CalcPos ( m_pScript );

		Landing ();	//���n
	}

	//====================================================================================
	//�G�t�F�N�g�����̐���
	void ExeChara::MakeEfOprt ()
	{
		//�G�t�F�N�g�����ɃL�����|�C���^��ݒ�
		m_oprtEf->SetpChara ( m_pChara );

		//���ׂẴA�N�V�����ƃX�N���v�g������
		PVP_Action pvpAction = m_pChara->GetpvpAction ();
		for ( P_Action pAction : ( * pvpAction ) )
		{
			PVP_Script pvpScript = pAction->GetpvpScript ();
			for ( P_Script pScript : ( * pvpScript ) )
			{
				PVP_EfGnrt pvpEfGnrt = pScript->GetpvpEfGnrt ();
				for ( P_EfGnrt pEfGnrt : ( * pvpEfGnrt ) )
				{
					//�񐶐��Ȃ珉��ɓo�^���Ă����AID�ŉғ���Ԃɂ���
					if ( ! pEfGnrt->GetGnrt () )
					{
						//�G�t�F�N�g�C���f�b�N�X�̎擾
						UINT index = pEfGnrt->GetIndex ();

						//�G�t�F�N�g�̎擾
						P_Effect pEf = m_pChara->GetpEffect ( index );

						//�G�t�F�N�g�Ǘ��ɓn����ID�𓾂�
//						UINT id = m_oprtEf.Addstd::vectorEffect ( pEf, pEfGnrt->GetZ () );

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
		for ( P_EfGnrt pEfGnrt : ( *pvpEfGnrt ) )
		{
			//�����p�Ȃ�
			if ( pEfGnrt->GetGnrt () )
			{
				//�G�t�F�N�g�C���f�b�N�X�̎擾
				UINT index = pEfGnrt->GetIndex ();
				//�G�t�F�N�g�̎擾
				P_Effect pEf = m_pChara->GetpEffect ( index );
				//���X�g�ɒǉ�
				m_oprtEf->AddListEffect ( pEf, pEfGnrt, m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );
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
		m_oprtEf->PreScriptMove ();

		//�G�t�F�N�g����
		m_oprtEf->PostScriptMove ( m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );
	}
	//====================================================================================


	//���C�t����
	void ExeChara::CheckLife ()
	{
		//���������C�t�O
		if ( 0 >= m_btlPrm.GetLife () )
		{
			//�_�E����Ԃɋ����ύX
			SetAction ( ACT_DOWN );
			m_btlPrm.GetTmr_Down ()->Start ();
		}
	}

	//====================================================================================
	//�O���t�B�b�N�X�V
	void ExeChara::UpdateGraphic ()
	{
		//���C���C���[�W
		m_dispChara->UpdateMainImage ( m_pScript, m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );

		//���͕\���X�V
		m_dispChara->UpdateInput ( m_pCharaInput );

		//���ʃO���t�B�b�N
		if ( ! m_btlPrm.GetTmr_Stop ()->IsActive () )
		{
			//�X�N���v�g����̒�~
			m_btlPrm.SetScpStop ( m_pScript->m_prmStaging.Stop );
		}

		//�Q�[�W�X�V
		m_dispChara->UpdateGauge ( m_btlPrm );
	}
	//====================================================================================

	//�����E���n

	//@todo �u�����`�����ŃX�N���v�g�ڍ�����悤�ɂ���

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

			//SE
			SOUND->Play_SE ( SE_Btl_Landing );

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
#if 0
		//�W�����v��(�A�N�V�����̐�/�󒆏��)�͎���
		if ( Is_AP_Jump () )
		{
			return;
		}
#endif // 0
		//�j���[�g�����̂ݐU��Ԃ�
		if ( ! IsStand () )
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

	//EfPart�d�Ȃ�
	void ExeChara::OverEfPart ()
	{
		//1p2p�����d�Ȃ�͗������擾

		//����g���擾
		PV_RECT pvHRect = GetpCharaRect ()->GetpvHRect ();

		//EF���̓_�W�����擾
		std::vector < PrmEfPart > & vPrm = m_efPart->Getrv_Prm ();

		//�d�Ȃ蔻��
		UINT count = 0;
		UINT i = 0;
		for ( PrmEfPart prm : vPrm )
		{
			if ( 0 != prm.m_count ) { continue; }

			if ( prm.m_pOb->GetValid () )
			{
				for ( RECT rect : ( *pvHRect ) )
				{
					//�d�Ȃ��Ă����Ƃ�
					if ( OverlapPoint ( prm.m_pos, rect ) )
					{
						vPrm [ i ].m_gotten = T;
						++count;
						break;	//RECT�̃��[�v�𔲂��AEfPart�̓_�𑱍s
					}
				}
			}

			++ i;
		}

		m_btlPrm.AddMana ( 100 * count );
	}


	//-------------------------------------------------------------------------------------------------
	//	�g�ݒ�
	//-------------------------------------------------------------------------------------------------
	//�ڐG�g�ݒ�
	void ExeChara::SetCollisionRect ()
	{
		m_charaRect->SetCRect ( m_pScript->GetpvCRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
	}


	//���E�E�U���E����E�g�ݒ�
	void ExeChara::SetRect ()
	{
		SetOffsetRect ();
		SetAttackRect ();
		SetHitRect ();
	}

	//���E�g�ݒ�
	void ExeChara::SetOffsetRect ()
	{
		m_charaRect->SetORect ( m_pScript->GetpvORect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
	}

	//�U���g�ݒ�
	void ExeChara::SetAttackRect ()
	{
		//======================================
		// �q�b�g���Ɍ�̍U���g���ꎞ��~(���i�h�~)
		//======================================

		//�q�b�g��Ԃ��m�F (�q�b�g��Ԑݒ�� OnHit(), OnClang() )
		bool bHit = m_btlPrm.GetHitEst () || m_btlPrm.GetClang ();

#if DEBUG_DISP
		//�f�o�b�O�\������
		if ( m_playerID == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( 4, _T ( "bHit = %d" ), bHit ? 1 : 0 );
			P_Timer ptHitStop = m_btlPrm.GetTmr_HitStop ();
			DBGOUT_WND_F ( 5, _T ( "hitStop = %d" ), ptHitStop->GetTime () );
			UINT hitpitch = m_pAction->GetHitPitch ();
			P_Timer ptHitPitch = m_btlPrm.GetTmr_HitPitch ();
			DBGOUT_WND_F ( 6, _T ( "hitPitch = %d / %d" ), ptHitPitch->GetTime (), hitpitch );
			UINT hitmax = m_pAction->GetHitNum ();
			UINT hitnum = m_btlPrm.GetHitNum ();
			DBGOUT_WND_F ( 7, _T ( "hitnum = %d / %d" ), hitnum, hitmax );
		}
#else
		//�f�o�b�O�\���Ȃ�
#endif // DEBUG_DISP

		//--------------------------------------------------
		//�q�b�g���Ă��Ȃ���(�ʏ펞)�A�U���g��ݒ肵�ďI��
		if ( ! bHit )
		{
			//�U���g�̐ݒ�
			m_charaRect->SetARect ( m_pScript->GetpvARect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
			return;
		}

		//--------------------------------------------------
		//�U���������E�ō����ɓ���A�N�V�������̂ݘg������������

		//1�q�b�g�Z�͍U���g����ɂ��ďI��
		if ( 1 >= m_pAction->GetHitNum () )
		{
			//�U���g����ɂ���
			m_charaRect->ResetARect ();
			return;
		}

		//--------------------------------------------------
		//�A�N�V�������q�b�g��������ɒB�����Ƃ��g����ɂ���

		UINT hitmax = m_pAction->GetHitNum ();
		if ( hitmax <= m_btlPrm.GetHitNum () )
		{
			//�U���g����ɂ���
			m_charaRect->ResetARect ();
			return;
		}

		//--------------------------------------------------
		//���i�\�ȃA�N�V�����́A�q�b�g�Ԋu���`�F�b�N���čU���g���Đݒ肷��
		P_Timer ptHitPitch = m_btlPrm.GetTmr_HitPitch ();
		UINT pitch = m_pAction->GetHitPitch ();
		if ( pitch < ptHitPitch->GetTime () )
		{
			//�ăX�^�[�g
			m_btlPrm.HitPitchWaitStart ();

			//�U���g�̐ݒ�
			m_charaRect->SetARect ( m_pScript->GetpvARect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
			return;
		}

		//--------------------------------------------------
		//�Y�����Ȃ���΍U���g����ɂ���
		m_charaRect->ResetARect ();
	}

	//����g�ݒ�
	void ExeChara::SetHitRect ()
	{
		m_charaRect->SetHRect ( m_pScript->GetpvHRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
	}

	//�g�\���ؑ�
	void ExeChara::OnDispRect ()
	{
		m_dispChara->OnRect ();
		m_oprtEf->OnDispRect ();
	}
	void ExeChara::OffDispRect ()
	{
		m_dispChara->OffRect ();
		m_oprtEf->OffDispRect ();
	}

	//�g�����ׂă��Z�b�g
	void ExeChara::ResetRect ()
	{
		m_charaRect->ResetAllRect ();
	}

	//-------------------------------------------------------------------------------------------------

	//�A�N�V�����ڍ����A�O�A�N�V�����̍Ō�̏���
	void ExeChara::EndAction ()
	{
		//�_�b�V�����玟�A�N�V�����Ɉڍ�����Ƃ��A�������c��
		if ( m_pChara->GetActionID ( _T ( "FrontDashStart" ) ) == m_actionID )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( 10.f, 0 ) );
		}
		if ( m_pChara->GetActionID ( _T ( "FrontDash" ) ) == m_actionID )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( 10.f, 0 ) );
		}
		if ( m_pChara->GetActionID ( _T ( "BackDash" ) ) == m_actionID )
		{
			m_btlPrm.SetDashInertial ( VEC2 ( -8.f, 0 ) );
		}

		//�e���Ԃ̏I��
		m_btlPrm.EndAction ();
		m_frame = 0;

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


	//-------------------------------------------------------------------------------------------------
	//���͏���
	void ExeChara::Input ()
	{
		//���͂̍X�V
		m_pCharaInput->Update ( GetDirRight () );
	}


	//�g���[�j���O���[�h������
	void ExeChara::TrainingInit ()
	{
		Init ();
		m_btlPrm.TrainingInit ();
	}



	//CPU����ؑ�
	void ExeChara::ControlCPU ()
	{
		m_pCharaInput = make_shared < CPUInput > ( shared_from_this (), m_pOther );
		m_pCharaInput->SetPlayer ( m_playerID );

		m_dispChara->SetControl_CPU ();
	}

	void ExeChara::ControlPlayer ()
	{
		m_pCharaInput = make_shared < PlayerInput > ();
		m_pCharaInput->SetPlayer ( m_playerID );

		m_dispChara->SetControl_PLAYER ();
	}

	//---------------------------------------------
	//�C�x���g

	void ExeChara::OnDashBranch ()
	{
		m_btlPrm.AddBalance ( -1000 );
		TransitAction_Condition_I ( BRC_DASH, F );	//�_�b�V�����E�E����
	}

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

		//����̃p�����[�^�ő���
		P_Script scp = m_pOther.lock ()->GetpScript ();
		int balance_e = scp->m_prmBattle.Balance_E;
		m_btlPrm.AddBalance ( balance_e );

		//�o�����X�A�E�g
		if ( m_btlPrm.GetBalance () <= 0 )
		{
			SetAction ( _T ( "Dotty" ) );
		}

		//���g�̏�ԕύX
		m_btlPrm.SetClang ( true );		//�ō����
//		m_lurch = nLurch;		//�̂����莞�Ԃ̐ݒ�
		m_btlPrm.GetTmr_HitStop ()->Start ();		//�q�b�g�X�g�b�v�̐ݒ�
	}


	//����E�U�� �� �����E���炢
	//���炢��ԁE�_���[�W����
#if 0
	void ExeChara::OnDamaged ( int damage )
	{
		bool hit = true;
		bool guard = false;

		//��𔻒�
#if 0
		//�U�����łȂ��A���v�f�����͂���Ă���Ƃ�
		//�_�b�V�����A��낯���Ȃǂ����O���� (�����͉\)
		if ( !IsAttacking () && !( GetActionName () == Chara::DOTTY ) )
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
				damage = (int)( damage * ( 0.001f * ( 0.5f * LIFE_MAX + lf ) ) );
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
#endif // 0


	//����E�U�� �� �����E���炢
	//���炢��ԁE�_���[�W����
	void ExeChara::OnDamaged ()
	{
		//����
		P_Script pScp = m_pOther.lock ()->m_pScript;

		//-------------------------------------------------
		//�_���[�W����
		int damage = pScp->m_prmBattle.Power;

#if 0
		//�_���[�W�����C�t�ɂ���ĕ␳(�����l)
		int lf = m_btlPrm.GetLife ();
		if ( lf < LIFE_MAX * 0.5f )
		{
			damage = (int)( damage * ( 0.001f * ( 0.5f * LIFE_MAX + lf ) ) );
		}
#endif // 0

#if 0
		if ( lf < damage ) { m_btlPrm.SetDamage ( lf ); }	//���C�t�ȏ�͕\������
		else { m_btlPrm.SetDamage ( damage ); }		//�\���p
		m_btlPrm.SetLife ( lf - damage );
#endif // 0
		m_btlPrm.AddLife ( - damage );

		//-------------------------------------------------
		//�o�����X����
		int b_e = pScp->m_prmBattle.Balance_E;
		int bl = m_btlPrm.GetBalance ();
		m_btlPrm.SetBalance ( bl - b_e );

		//-------------------------------------------------
		//���̑��@����
		m_btlPrm.GetTmr_HitStop ()->Start ();			//�q�b�g�X�g�b�v�̐ݒ�
		m_btlPrm.SetFirstEf ( true );			//����̂݃G�t�F�N�g����
		m_btlPrm.SetFirstSE ( true );			//����̂�SE����
	}


	//�����E�U�� -> ����E���炢
	//�q�b�g����(�U��������)
	void ExeChara::OnHit ()
	{
		//-----------------------------------------------------
		//�������� (���聨�����łȂ��ƃX�N���v�g���ς���Ă��܂�)
		TransitAction_Condition_E ( BRC_THR_E, T );	//�����E����
		TransitAction_Condition_I ( BRC_THR_I, F );	//�����E����
		TransitAction_Condition_E ( BRC_HIT_E, T );	//�q�b�g�E����
		TransitAction_Condition_I ( BRC_HIT_I, F );	//�q�b�g�E����

		//-----------------------------------------------------

		//m_btlPrm.SetHitEst ( true );		//�U�������t���O
		//m_btlPrm.GetTmr_HitStop ()->Start ();		//�q�b�g�X�g�b�v�̐ݒ�
		m_btlPrm.OnHit ();
	}

	//�G�t�F�N�g�q�b�g����(�U��������)
	void ExeChara::OnEfHit ()
	{
		m_btlPrm.SetHitEst ( true );		//�U�������t���O
//		m_tmrHitstop->Start ();		//�G�t�F�N�g�̓q�b�g�X�g�b�v���Ȃ�

		m_btlPrm.GetTmr_HitPitch ()->Start ();
	}

#if 0
	//�I�����o
	void ExeChara::OnEndAct ()
	{
		m_charaState = CHST_WIN_WAIT;
	}

	//�����I�����
	void ExeChara::ForcedEnd ()
	{
		if ( m_btlPrm.GetLife () <= 0 )
		{
			m_charaState = CHST_DOWN_END;
			//			m_actionID = m_pChara->GetBsAction ( BA_DOWN );
			TransitAction ( m_actionID );
		}
		else
		{
			m_charaState = CHST_WIN_END;
			//			m_actionID = m_pChara->GetBsAction ( BA_WIN );
			TransitAction ( m_actionID );
		}
	}
#endif // 0

}	//namespace GAME

