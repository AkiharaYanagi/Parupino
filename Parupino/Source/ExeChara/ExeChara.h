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
#include "../GameMain/GameConst.h"
#include "../GameMain/Param.h"
#include "../FtgMain/G_Ftg.h"
#include "../FtgMain/FtgConst.h"
#include "../CharaData/Chara.h"
#include "../CharaData/IO/LoadChara.h"
#include "Disp/DispChara.h"
#include "Disp/DispInput.h"
#include "Input/CharaInput.h"
#include "Input/PlayerInput.h"
#include "Input/CPUInput.h"
#include "Effect/OperateEffect.h"
#include "CharaRect.h"
#include "BtlParam.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�O���錾
	class ExeChara;
	using P_ExeChara = shared_ptr < ExeChara >;
	using WP_ExeChara = weak_ptr < ExeChara >;

	//�N���X
	class ExeChara : public TASK_VEC, public enable_shared_from_this < ExeChara >
	{
		//------------------------------------------------
		//��{�f�[�^
		P_Chara			m_pChara;		//�L�����f�[�^
		PLAYER_ID		m_playerID;		//�v���C���[ID
		CHARA_NAME		m_name;			//�L������
		WP_ExeChara		m_pOther;		//����L����(�z�Q�ƂȂ̂�weak_ptr)
		PLAYER_MODE		m_playerMode;	//�v���C���[���[�h(�l,CPU,�l�b�g���[�N)

		//------------------------------------------------
		//�\��
		DispChara		m_dispChara;	//�L�����S�ʕ\��
		DispInput		m_dispInput;	//���͕\��

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
		//�G�t�F�N�g�ė�
		OperateEffect	m_oprtEf;

		//------------------------------------------------
		//�g
		P_CharaRect		m_charaRect;	//�g
		bool			m_bDispRect;	//�g�\��

		//------------------------------------------------
		//�p�����[�^
		BtlParam		m_btlPrm;		//�o�g���p�����[�^	

#if 0
		//------------------------------------------------
		//�p�����[�^
		VEC2	m_ptChara;		//�L�����ʒu
		VEC2	m_tempPt;		//�ꎞ�ۑ�
		bool	m_dirRight;		//����(�E�F��, ���F�t)
		VEC2	m_inertial;		//����
		VEC2	m_vel;	//���x
		VEC2	m_acc;	//�����x
		float	m_g;	//�d��
		float	m_vg;	//�d��

		int		m_life;			//���C�t
		int		m_balance;		//�o�����X
		int		m_power;		//�����U���l
		int		m_damage;		//�_���[�W(���C�t������)

		bool	m_damaged;		//���炢�t���O
		bool	m_hitEst;		//�U�������t���O
		bool	m_FirstEf;		//����Ef�t���O
		bool	m_FirstSE;		//����SE�t���O

		bool	m_ForcedChange;	//�����ύX

		P_Timer	m_tmrHitstop;	//�q�b�g�X�g�b�v�^�C�}�[
		P_Timer	m_tmrDown;		//�_�E���^�C�}�[
		P_Timer	m_tmrEnd;		//�I����ԃ^�C�}�[

		bool	m_clang;		//�ō������t���O
		bool	m_transit;		//�X�N���v�g�J�ڂ����t���[��

//		UINT	m_lurch;		//�̂�����(�L�����Z���s��)���Ԓǉ�
//		UINT	m_lurchTimer;

		bool	m_wait;			//���͂��ꎞ��~
		bool	m_stop;			//���́A�X�N���v�g�������ꎞ��~
		P_Timer	m_stopTimer;
		UINT	m_blackOut;		//�Ó]
		UINT	m_scpStop;		//�X�N���v�g����̒�~
#endif // 0

		//------------------------------------------------
		//�Q�[���i�s���
		CHARA_STATE		m_charaState;

	public:
		ExeChara () = delete;
		ExeChara ( PLAYER_ID m_playerID );
		ExeChara ( const ExeChara & rhs ) = delete;
		~ExeChara ();

		void ParamInit ( P_Param pParam );
		void Load ();
		void Init ();
		void Reset ();
		void Resume ();	//������

		//------------------------------------------------------------
		//******************************
		// ���t���[�� �X�N���v�g������A
		//******************************
		void PreScriptMove ();			//	�X�N���v�g�O����
		//MutualChara::Collision ();	//	���ݔ��� (�ڐG�g)
		void ScriptRectMove ();			//	�Ԃ����A����g��ݒ�
		//MutualChara::Decision ();		//	���ݔ��� (�U���g�A�q�b�g�g)
		void PostScriptMove ();			//	�X�N���v�g�㏈��
		//------------------------------------------------------------

		//�����ݒ�
		void SetpOther ( WP_ExeChara p ) { m_pOther = p; /*m_cpuInput.SetpExeCharaOther ( p );*/ }

		//------------------------------------------------------------
		//�p�����[�^
		VEC2 GetPos () const { return m_btlPrm.GetPos (); }		//�ʒu���擾
		bool GetDirRight () const { return m_btlPrm.GetDirRight (); }	//�������擾
		void SetDirRight ( bool b ) { m_btlPrm.SetDirRight ( b ); }		//������ԂŌ�����ݒ�

#if 0
		//�A�N�V�����I������
		void EndAction ();

		//�Ԃ����A�ʒu�̏C��
		void BackPt () { m_ptChara = m_tempPt; }
		void BackPtX () { m_ptChara.x = m_tempPt.x; }
#endif // 0
		void BackPt () { m_btlPrm.BackPt (); }
		void BackPtX () { m_btlPrm.BackPtX (); }
		void BackMoveX ();
		void LookOther ();	//����̕���������

		//---------------------------------------------
		//�Q�[���i�s���

		CHARA_STATE GetCharaState () const { return m_charaState; }
		void SetCharaState ( CHARA_STATE chst ) { m_charaState = chst; }

		//�J�n
		void SetMain () { m_charaState = CHST_MAIN; }

		//���͂������Ԃ��ǂ���
		bool CanInput () const;

		//���C����Ԃ��ǂ���
		bool IsMain () const;

		//���C�t�O�`�F�b�N
		bool IsZeroLife () const { return ( 0 >= m_btlPrm.GetLife () ); }

#if 0
		bool GetStart () const { return m_start; }		//�J�n��Ԏ擾
		void SetStart ( bool b ) { m_start = b; }
		bool GetEnd () const { return m_end; }			//�I����Ԏ擾
		void SetEndWait ( bool b ) { m_endWait = b; }
#endif // 0

		//------------------------------------------------
		//�G�t�F�N�g

		//�G�t�F�N�g���X�g�擾
		PLP_ExEf GetplpExEf () { return m_oprtEf.GetplpExEf (); }

		//---------------------------------------------
		//�g
		void AdjustCRect ();		//���݈ʒu����ڐG�g�𔽉f
		P_CharaRect GetpCharaRect () { return m_charaRect; }		//�g�擾

		//---------------------------------------------
		//�p�����[�^�擾

		//�e�l�擾
		CHARA_NAME GetCharaName () const { return m_name; }
		int GetPower () const { return m_btlPrm.GetPower (); }		//�U���l�擾
		int GetLife () const { return m_btlPrm.GetLife (); }		//���C�t�擾
		ACTION_POSTURE GetPosture () const { return m_pAction->GetPosture (); }

		//---------------------------------------------
		//�O������̏�ԕύX

		//�ꎞ��~
		void SetWait ( bool b ) { m_btlPrm.SetWait ( b ); }	//���͂��~
		void SetStop ( bool b ) { m_btlPrm.SetStop ( b ); }	//�`��X�V���~
		void SetStopTimer ( UINT i ) {
			m_btlPrm.GetTmr_Stop ()->SetTargetTime ( i );
			m_btlPrm.GetTmr_Stop ()->Start ();
		}

		//�ō�
		bool GetClang () const { return m_btlPrm.GetClang (); }
		void SetClang ( bool b ) { m_btlPrm.SetClang ( b ); }

		//�����F�ō���~����
		void OnClang ( UINT nLurch, CLANG_DECISION_WL clangDecision );

		//���炢����
		bool IsDamaged () const { return m_btlPrm.GetDamaged (); }
		void SetDamaged ( bool b ) { m_btlPrm.SetDamaged ( b ); }
		void OnDamaged ( int damage );

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

		//�I���ҋ@
		void SetEndWait ();

		//�I�����o
		void OnEndAct ();

		//�_�E�����
		bool IsDown () { return CHST_DOWN == m_charaState; }

		//�_�E���I�����
		bool IsDownEnd () { return CHST_DOWN_END == m_charaState; }

		//�������
		bool IsWin () { return CHST_WIN == m_charaState; }

		//�����I�����
		bool IsWinEnd () { return CHST_WIN_END == m_charaState; }

		//�����I�����
		void ForcedEnd ()
		{
			if ( m_btlPrm.GetLife () <= 0 )
			{
				m_charaState = CHST_DOWN_END;
//				m_actionID = m_pChara->GetBsAction ( BA_DOWN );
				TransitAction ( m_actionID );
			}
			else
			{
				m_charaState = CHST_WIN_END;
//				m_actionID = m_pChara->GetBsAction ( BA_WIN );
				TransitAction ( m_actionID );
			}
		}

		//Rect
		void OnDispRect () { m_bDispRect = true; }
		void OffDispRect () { m_bDispRect = false; }

	//================================================
	//	�����֐�
	//================================================
	private:
		//------------------------------------------------
		//Init
		void MakeEfOprt ();		//�G�t�F�N�g�����̐���

		//PreScriptMove
		void AlwaysMove ();		// �A�N�V�����ƃX�N���v�g�ɂ��Ȃ����̏���

		void TransitAction ();	// �A�N�V�����ڍ�
		void TransitAction ( UINT actionID );		//�A�N�V�����̈ڍ�
		UINT TransitAction_Condition ( BRANCH_CONDITION CONDITION );	//�A�N�V�����ڍs(����)

		//�Ԃ����A�ʒu�̏C��
		void Landing ();	//���n

		//PostScriptMove
		void CheckLife ();			//���C�t����
		void UpdateGraphic ();		//�O���t�B�b�N�X�V
		void EffectGenerate ();		//�G�t�F�N�g����
		void EffectMove ();
		void TurnDispRect ();		//�g�\���ؑ�

		//------------------------------------------------
		//�A�N�V�����̐�
		bool Is_APStand () { return m_pAction->GetPosture () == AP_STAND; }
		bool IsJump () { return m_pAction->GetPosture () == AP_JUMP; }
		bool IsCrouch () { return m_pAction->GetPosture () == AP_CROUCH; }

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
		bool IsStand ()		{ return m_pAction->GetCategory ()  == AC_STAND; }
		bool IsMove ()		{ return m_pAction->GetCategory ()  == AC_MOVE; }
		bool IsDash ()		{ return m_pAction->GetCategory ()  == AC_DASH; }
		bool IsPoised ()	{ return m_pAction->GetCategory ()  == AC_POISED; }
		bool IsClang ()		{ return m_pAction->GetCategory ()  == AC_CLANG; }
		bool IsAvoid ()		{ return m_pAction->GetCategory ()  == AC_AVOID; }
		bool IsDotty ()		{ return m_pAction->GetCategory ()  == AC_DOTTY; }
		bool IsDamaged ()	{ return m_pAction->GetCategory ()  == AC_DAMAGED; }

#if 0
		//���݂̃A�N�V��������{�A�N�V�������ǂ���
		bool IsBasicAction ( BASIC_ACTION ba ) 
		{
			UINT id = m_pChara->GetBsAction ( ba ); 
			return id == m_actionID;
		}
#endif // 0

		//------------------------------------------------
#if 0
		//�̂����莞��
		void SetLurch ( UINT n ) { if ( 0 != n ) { m_lurch = n;  } }
		bool LurchTimer ();

#endif // 0

	};


}	//namespace GAME


