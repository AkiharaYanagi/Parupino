//=================================================================================================
//
// OperateEffect �w�b�_�t�@�C��
//		Effect���O�`�����Ŏ��s����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "ExeEffect.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class OperateEffect : public TASK_VEC
	{
		P_Chara			m_pChara;			//�L����
		PLP_ExEf		m_plpExeEffect;		//�G�t�F�N�g�̎��s���X�g(GameMain���ɓ��I�ɐ����E�������)

		PVP_TxBs		m_pvpEfTexture;		//�G�t�F�N�g�C���[�W�̃e�N�X�`�����X�g
		VP_Branch		m_vpBranch;			//�G�t�F�N�g�̕���
		VP_Route		m_vpRoute;			//���[�g

	public:
		OperateEffect ();
		OperateEffect ( const OperateEffect & rhs ) = delete;
		~OperateEffect ();

		void Rele ();

		//�L�����|�C���^�̐ݒ�
		void SetpChara ( P_Chara p );

		//�G�t�F�N�g���X�g�擾
		PLP_ExEf GetplpExEf () { return m_plpExeEffect; }

		//-----------------------------
		//�G�t�F�N�g���X�g�ɒǉ�
		void AddListEffect ( P_Effect pEffect, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight );

		//�I�u�W�F�N�g����ExeEf���擾
		P_ExEf GetpExEf ( P_Effect p ) const;

		//�I�u�W�F�N�g�����s�����ǂ���
		bool IsActive ( P_Effect p ) const { return GetpExEf ( p )->IsActive (); }

		//�I�u�W�F�N�g�ɂ��ғ��J�n
		void DriveEffect ( P_Effect p ) { GetpExEf ( p )->Drive (); }

		//�I�u�W�F�N�g�ɂ��ғ���~
		void StopEffect ( P_Effect p ) { GetpExEf ( p )->Stop (); }

		//---------------------------------------------------------------
		//�G�t�F�N�g�̓���
		void PreScriptMove ();
		void PostScriptMove ( VEC2 ptChara, bool dirRight );
		void SynchroScript ( VEC2 ptChara );

		//---------------------------------------------------------------
		//Rect
		void OnDispRect ();
		void OffDispRect ();
	};

	using P_OprEf = std::shared_ptr < OperateEffect >;


}	//namespace GAME


