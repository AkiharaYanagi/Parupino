//=================================================================================================
//
// ExeChara_Demo�@�\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "ExeChara_Demo.h"
#include "..\CharaData\IO\LoadCharaBin.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�R���X�g���N�^
	ExeChara_Demo::ExeChara_Demo ( PLAYER_ID m_playerID )
		: m_pChara ( nullptr )
		, m_playerID ( m_playerID ), m_name ( CHARA_TEST )
		, m_actionID ( 0 ), m_frame ( 0 )
		, m_charaState ( CHST_START )
	{
		//�L�����f�[�^����
		m_pChara = make_shared < Chara > ();	//�L�����f�[�^����
	}

	//�f�X�g���N�^
	ExeChara_Demo::~ExeChara_Demo ()
	{
	}

	//------------------------
	//�V�[���p�����[�^�֘A������
	void ExeChara_Demo::ParamInit ( P_Param pParam )
	{
		//�Q�[���ݒ�
		GameSettingFile stg = pParam->GetGameSetting ();

		//�I���L���� //���̓��[�h
		if ( m_playerID == PLAYER_ID_1 )
		{
			m_name = stg.GetName1p ();
		}
		if ( m_playerID == PLAYER_ID_2 )
		{
			m_name = stg.GetName2p ();
		}
	}

	//------------------------
	//�Ǎ�
	void ExeChara_Demo::Load ()
	{
		//���O����X�N���v�g�t�@�C�����w�肵�ăL�����̃��[�h
		//��	D3DX�̃e�N�X�`����p���邽�߃t�H�[�J�X�ύX���ȂǂɍĐݒ�(Reset())���K�v
		tstring name ( _T ( "charaBin.dat" ) );

		//�o�C�i���f�[�^�Ǎ�
		LoadCharaBin loadCharaBin ( name, *m_pChara );

		//�L�����\��������
		m_dispChara.SetpChara ( m_pChara );
		m_dispChara.Load ();

		TASK_VEC::Load ();
	}

	//------------------------
	//������(��������s�\)
	void ExeChara_Demo::Init ()
	{
		//�A�N�V�����E�X�N���v�g������
//		m_actionID = 0;
		m_actionID = m_pChara->GetActionID ( _T("Start_Demo") );
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

		TASK_VEC::Init ();
	}

	//�Đݒ�
	void ExeChara_Demo::Reset ()
	{
		_Reset ();	//������
	}

	//------------------------
	//�������̍Đݒ�
	void ExeChara_Demo::_Reset ()
	{
		//�e�N�X�`���������m�ۊ֘A�͍Đݒ�
		Rele ();
		m_pChara = make_shared < Chara > ();
		Load ();
		m_dispChara.SetpChara ( m_pChara );

		//�A�N�V�����E�X�N���v�g�Ď擾
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//���C�� �C���[�W
		m_dispChara.UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );
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
	void ExeChara_Demo::PreScriptMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//�ꎞ��~�̂Ƃ��͉������Ȃ�
		if ( m_btlPrm.GetTmr_Stop()->IsActive () )
		{ return; }

		// �A�N�V�����ڍ�
		TransitAction ();
	}



	//��###########################################################################
	//��
	//��		���t���[�� �X�N���v�g�㏈��
	//��			�����E����̃X�N���v�g�O���������݂̔���A�̌�ɂ��ꂼ��̏���������
	//��			����̌��ʕ\��(��ɃO���t�B�b�N�֘A)
	//��
	//��###########################################################################
	void ExeChara_Demo::PostScriptMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );
		
		//1[F]�Ɉ�x�s������
		AlwaysPostMove ();

		//�ꎞ��~�̂Ƃ��͉������Ȃ�
		if ( m_btlPrm.GetStop () ) { return; }

		// �O���t�B�b�N
		UpdateGraphic ();
	}

	//================================================
	//	�����֐�
	//================================================

	//�A�N�V�����̈ڍ�(���ڎw��)
	void ExeChara_Demo::TransitAction ( UINT actionID )
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
	void ExeChara_Demo::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//���݃A�N�V�������ŏI�t���[�� �Ȃ��
		if ( m_pAction->IsOverScript ( m_frame ) )
		{
			//�����A�N�V����m_pAction�͎��t���[������Move()��m_actionID���g���Ď擾�����
			m_actionID = m_pAction->GetNextID ();
			//�e���Ԃ̏I��
			m_btlPrm.EndAction ();
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

		assert ( nullptr != m_pAction && nullptr != m_pScript );
	}



	//�O���t�B�b�N�X�V
	void ExeChara_Demo::UpdateGraphic ()
	{
		//���C���C���[�W
		m_dispChara.UpdateMainImage ( m_pScript, m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );
	}


	void ExeChara_Demo::AlwaysPostMove ()
	{
		m_btlPrm.Move ();	//�^�C�}�[�ғ�
	}


}	//namespace GAME

