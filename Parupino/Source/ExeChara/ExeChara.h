//=================================================================================================
//
// �G�O�[�L�����@�w�b�_�t�@�C��
//		�L�����̃f�[�^���󂯂ăQ�[����Ŏ��s�i�t���[��������A�`��j����
//		���쎞�̈ʒu�Ȃǂ�ۑ�����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaData.h"
#include "../GameMain/GameConst.h"
#include "../GameMain/Param.h"
#include "../FtgMain/G_Ftg.h"
#include "../FtgMain/FtgConst.h"
#include "Disp/DispChara.h"
#include "Input/CharaInput.h"
#include "Effect/OperateEffect.h"
#include "Rect/CharaRect.h"
#include "BtlParam.h"
#include "ExeChara_Actor.h"
#include "../FtgMain/Ef/EfPart.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�O���錾
	class ExeChara;
	using P_ExeChara = std::shared_ptr < ExeChara >;
	using WP_ExeChara = std::weak_ptr < ExeChara >;

	//�L�������s �N���X
	class ExeChara : public TASK_VEC, public enable_shared_from_this < ExeChara >
	{
		//------------------------------------------------
		//��{�f�[�^
		P_Chara			m_pChara;		//�L�����f�[�^
		WP_ExeChara		m_pOther;		//����L����(�z�Q�ƂȂ̂�weak_ptr)

		PLAYER_ID		m_playerID;		//�v���C���[ID
		PLAYER_MODE		m_playerMode;	//�v���C���[���[�h(�l,CPU,�l�b�g���[�N)
		CHARA_NAME		m_name;			//�L������

		//------------------------------------------------
		//�\��
		P_DispChara		m_dispChara;	//�L�����S�ʕ\��

		//------------------------------------------------
		//����
		P_CharaInput	m_pCharaInput;	//����

		//------------------------------------------------
		//�X�N���v�g���s
		UINT			m_actionID;		//�������݃A�N�V����ID
		P_Action		m_pAction;		//�����A�N�V�����|�C���^
		UINT			m_frame;		//���������t���[��(�X�N���v�gID)
		P_Script		m_pScript;		//�����X�N���v�g�|�C���^

		//------------------------------------------------
		//�g
		P_CharaRect		m_charaRect;	//�g�Z�b�g

		//------------------------------------------------
		//�p�����[�^
		BtlParam		m_btlPrm;		//�o�g���p�����[�^	

		//------------------------------------------------
		//�G�t�F�N�g�ė�
		P_OprEf			m_oprtEf;

		//------------------------------------------------
		//�Q�[���i�s��ԃX�e�[�g
		ExeChara_Actor	m_actor;

		//------------------------------------------------
		//���q�G�t�F�N�g(�Q��)
		P_EfPart	m_efPart;

	public:
		ExeChara () = delete;
		ExeChara ( PLAYER_ID m_playerID );
		ExeChara ( const ExeChara & rhs ) = delete;
		~ExeChara ();

		void ParamInit ( P_Param pParam );
		void Load ();
		void _Load ();
		void Init ();
		void Reset ();
		void _Reset ();	//������

		//===========================================================
		//******************************
		// ���t���[�� �X�N���v�g������A
		//******************************
		void PreScriptMove ();			//	�X�N���v�g�O����
		//MutualChara::Collision ();	//	���ݔ��� (�ڐG�g)
		void RectMove ();			//	�Ԃ����A����g��ݒ�
		//MutualChara::Decision ();		//	���ݔ��� (�U���g�A�q�b�g�g)
		void PostScriptMove ();			//	�X�N���v�g�㏈��
		//===========================================================

		//------------------------------------------------------------
		//�����ݒ�
		void SetpOther ( WP_ExeChara p ) { m_pOther = p; /*m_cpuInput.SetpExeCharaOther ( p );*/ }

		//------------------------------------------------------------

		//�p�����[�^
		//@todo �X�N���v�g�̎��@ScriptParam_Battle �� ExeChara�̎������l BtlPrm �̐���

		BtlParam GetBtlPrm () const { return m_btlPrm; }

		void SetPos ( VEC2 v ) { m_btlPrm.SetPos ( v ); }
		VEC2 GetPos () const { return m_btlPrm.GetPos (); }		//�ʒu���擾
		bool GetDirRight () const { return m_btlPrm.GetDirRight (); }	//�������擾
		void SetDirRight ( bool b ) { m_btlPrm.SetDirRight ( b ); }		//������ԂŌ�����ݒ�

		void BackPt () { m_btlPrm.BackPt (); }
		void BackPtX () { m_btlPrm.BackPtX (); }
		void BackMoveX ();
		void LookOther ();	//����̕���������

		//------------------------------------------------
		//���q�G�t�F�N�g
		void SetpParticle ( P_EfPart p ) { m_efPart = p; }

		//---------------------------------------------
		//���͏���
		void Input ();

		//���C�t�O�`�F�b�N
		bool IsZeroLife () const { return ( 0 >= m_btlPrm.GetLife () ); }

		//------------------------------------------------
		//�G�t�F�N�g

		//�G�t�F�N�g���X�g�擾
		PLP_ExEf GetplpExEf () { return m_oprtEf->GetplpExEf (); }

		//---------------------------------------------
		//�g
		P_CharaRect GetpCharaRect () const { return m_charaRect; }		//�g�擾

		void SetCollisionRect ();	//[PreMove] �ʒu����ڐG�g�ݒ�
		void SetRect ();			//[PostMove] ���E�E�U���E���� �g�ݒ�
		void ResetRect ();			//���Z�b�g
	private:
		void SetOffsetRect ();	//���E�g�ݒ�
		void SetAttackRect ();	//�U���g�ݒ�
		void SetHitRect ();		//����g�ݒ�
	public:

		//---------------------------------------------
		//�e�l�擾
		P_Script GetpScript () { return m_pScript; }
		BtlParam GetBtlParam () const { return m_btlPrm; };

		CHARA_NAME GetCharaName () const { return m_name; }
		int GetLife () const { return m_btlPrm.GetLife (); }		//���C�t�擾
		ACTION_POSTURE GetPosture () const { return m_pAction->GetPosture (); }

		//---------------------------------------------
		//�O������̏�ԕύX

		//Demo�p
		void StartGreeting ();
		void StartGetReady ();
		void StartFighting ();

		//�ꎞ��~
		void SetWait ( bool b ) { m_btlPrm.SetWait ( b ); }	//���͂��~
		void SetStop ( bool b ) { m_btlPrm.SetStop ( b ); }	//�`��X�V���~
		void SetStopTimer ( UINT i ) {
			m_btlPrm.GetTmr_Stop ()->SetTargetTime ( i );
			m_btlPrm.GetTmr_Stop ()->Start ();
		}

		//�q�b�g�X�g�b�v
		bool IsHitStop ()
		{ 
			if ( ! m_btlPrm.GetTmr_HitStop ()->IsLast () )
			{
				return m_btlPrm.GetTmr_HitStop ()->IsActive ();
			}
			return false;
		}

		//�ō�
		bool GetClang () const { return m_btlPrm.GetClang (); }
		void SetClang ( bool b ) { m_btlPrm.SetClang ( b ); }

		//�����F�ō���~����
		void OnClang ( UINT nLurch, CLANG_DECISION_WL clangDecision );

		//����E�U�� �� �����E���炢
		//���炢����
		bool IsDamaged () const { return m_btlPrm.GetDamaged (); }
		void SetDamaged ( bool b ) { m_btlPrm.SetDamaged ( b ); }
		void OnDamaged ( int damage );
		void OnDamaged ();

		//�����E�U�� -> ����E���炢
		//�q�b�g����
		bool IsHit () const { return m_btlPrm.GetHitEst (); }
		void SetHit ( bool b ) { m_btlPrm.SetHitEst ( b ); }
		void OnHit ();
		void OnEfHit ();

		//-------------------------------------------------
		//�X�N���v�g����̕ύX
		//�Ó]
		UINT GetBlackOut () const { return m_btlPrm.GetBlackOut (); }
		void SetBlackOut ( UINT i ) { m_btlPrm.SetBlackOut ( i ); }

		//��~
		UINT GetScpStop () const { return m_btlPrm.GetScpStop (); }
		void SetScpStop ( UINT i ) { m_btlPrm.SetScpStop ( i ); }

		//-------------------------------------------------

		//�O������̏�Ԋm�F
		//����A�N�V�����i���O�w��j
		bool IsNameAction ( tstring nameAction ) const { return m_pAction->IsName ( nameAction ); }

		//�_�b�V������
		void OnDashBranch ();

		//-------------------------------------------------
		//�V�X�e��

		//�g���[�j���O���[�h������
		void TrainingInit ();

		//�g�\���ؑ�
		void OnDispRect ();
		void OffDispRect ();

		//CPU����ؑ�
		void ControlCPU ();
		void ControlPlayer ();

	//================================================
	//	�����֐�
	//================================================
	private:
		void MakeEfOprt ();		//�G�t�F�N�g�����̐���

	public:
		//�A�N�V�����w��
		void SetAction ( tstring action_name );
		void SetAction ( UINT action_id );

		void TransitAction ();	// �A�N�V�����ڍ�
		bool TranditAction_Command ();	//�A�N�V�����ڍ��i�R�}���h�Ɋւ��鏈���j
		void TransitScript ();	//�X�N���v�g��J�ڂ�����

		void SetParamFromScript ();	//�X�N���v�g����p�����[�^�𔽉f����

		void EndAction ();	//�A�N�V�����ڍ����A�O�A�N�V�����̍Ō�̏���
		void CalcPos ();	// �ʒu�v�Z		//�Ԃ����A�ʒu�̏C��
		void Landing ();	//�����E���n

	private:

//		void TransitAction ( UINT actionID );		//�A�N�V�����̈ڍ�
		void TransitAction_Condition_I ( BRANCH_CONDITION CONDITION, bool forced );	//�������`�F�b�N���Ĉڍs
		void TransitAction_Condition_E ( BRANCH_CONDITION CONDITION, bool forced );	//�������`�F�b�N���Ĉڍs
		UINT Check_TransitAction_Condition ( BRANCH_CONDITION CONDITION );	//�A�N�V�����ڍs(�����`�F�b�N)

	public:
		//State����Ă΂���ԕʏ���
		void CheckLife ();			//���C�t����
		void UpdateGraphic ();		//�O���t�B�b�N�X�V
		void EffectGenerate ();		//�G�t�F�N�g����
		void EffectMove ();
		void MoveTimer () { m_btlPrm.TimerMove (); }

		void OverEfPart ();	//EfPart�d�Ȃ�

	private:

		//------------------------------------------------
		//�A�N�V�����̐�
		bool Is_AP_Stand () { return m_pAction->GetPosture () == AP_STAND; }
		bool Is_AP_Jump () { return m_pAction->GetPosture () == AP_JUMP; }
		bool Is_AP_Crouch () { return m_pAction->GetPosture () == AP_CROUCH; }

		//------------------------------------------------
		//�A�N�V�����J�e�S��

		//���݃A�N�V�����J�e�S���擾
		ACTION_CATEGORY ActCtg () const { return m_pAction->GetCategory (); }
		bool IsActCtg ( ACTION_CATEGORY ac ) const { return ac == ActCtg (); }
		//�e�A�N�V�������ǂ���
		bool IsAttacking () const
		{
			return
				m_pAction->GetCategory ()  == AC_ATTACK_L 
			||	m_pAction->GetCategory ()  == AC_ATTACK_M
			||	m_pAction->GetCategory ()  == AC_ATTACK_H; 
		}
		bool IsStand ()		{ return m_pAction->GetCategory ()  == AC_NEUTRAL; }
		bool IsMove ()		{ return m_pAction->GetCategory ()  == AC_MOVE; }
		bool IsDash ()		{ return m_pAction->GetCategory ()  == AC_DASH; }
		bool IsPoised ()	{ return m_pAction->GetCategory ()  == AC_POISED; }
		bool IsClang ()		{ return m_pAction->GetCategory ()  == AC_CLANG; }
		bool IsAvoid ()		{ return m_pAction->GetCategory ()  == AC_AVOID; }
		bool IsDotty ()		{ return m_pAction->GetCategory ()  == AC_DOTTY; }
		bool IsDamaged ()	{ return m_pAction->GetCategory ()  == AC_DAMAGED; }

		//------------------------------------------------
#if 0
		//�̂����莞��
		void SetLurch ( UINT n ) { if ( 0 != n ) { m_lurch = n;  } }
		bool LurchTimer ();

#endif // 0

	};


}	//namespace GAME


