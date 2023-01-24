//=================================================================================================
//
// ExeChara_Demo�@�w�b�_�t�@�C��
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
#include "BtlParam.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�O���錾
	class ExeChara_Demo;
	using P_ExeChara_Demo = shared_ptr < ExeChara_Demo >;
	using WP_ExeChara_Demo = weak_ptr < ExeChara_Demo >;

	//�N���X
	class ExeChara_Demo : public TASK_VEC, public enable_shared_from_this < ExeChara_Demo >
	{
		//------------------------------------------------
		//��{�f�[�^
		P_Chara			m_pChara;		//�L�����f�[�^
		PLAYER_ID		m_playerID;		//�v���C���[ID
		CHARA_NAME		m_name;			//�L������

		//------------------------------------------------
		//�p�����[�^
		BtlParam		m_btlPrm;		//�o�g���p�����[�^	

		//------------------------------------------------
		//�\��
		DispChara		m_dispChara;	//�L�����S�ʕ\��

		//------------------------------------------------
		//�X�N���v�g���s
		UINT			m_actionID;		//�������݃A�N�V����ID
		P_Action		m_pAction;		//�����A�N�V�����|�C���^
		UINT			m_frame;		//���������t���[��(�X�N���v�gID)
		P_Script		m_pScript;		//�����X�N���v�g�|�C���^

		//------------------------------------------------
		//�Q�[���i�s���
		CHARA_STATE		m_charaState;

	public:
		ExeChara_Demo () = delete;
		ExeChara_Demo ( PLAYER_ID m_playerID );
		ExeChara_Demo ( const ExeChara_Demo & rhs ) = delete;
		~ExeChara_Demo ();

		void ParamInit ( P_Param pParam );
		void Load ();
		void Init ();
		void Reset ();
		void _Reset ();	//������

		//------------------------------------------------------------
		//******************************
		// ���t���[�� �X�N���v�g������A
		//******************************
		void PreScriptMove ();			//	�X�N���v�g�O����
		void PostScriptMove ();			//	�X�N���v�g�㏈��
		//------------------------------------------------------------

		//------------------------------------------------------------
		//�p�����[�^
		VEC2 GetPos () const { return m_btlPrm.GetPos (); }		//�ʒu���擾
		bool GetDirRight () const { return m_btlPrm.GetDirRight (); }	//�������擾
		void SetDirRight ( bool b ) { m_btlPrm.SetDirRight ( b ); }		//������ԂŌ�����ݒ�

		void BackPt () { m_btlPrm.BackPt (); }
		void BackPtX () { m_btlPrm.BackPtX (); }

	//================================================
	//	�����֐�
	//================================================
	private:
		//------------------------------------------------
		//PreScriptMove
		void TransitAction ();	// �A�N�V�����ڍ�
		void TransitAction ( UINT actionID );		//�A�N�V�����̈ڍ�

		//PostScriptMove
		void AlwaysPostMove ();		// �A�N�V�����ƃX�N���v�g�ɂ��Ȃ����̏���
		void UpdateGraphic ();		//�O���t�B�b�N�X�V

	};


}	//namespace GAME


