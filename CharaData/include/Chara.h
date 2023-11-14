//=================================================================================================
//
//	Chara �w�b�_�t�@�C��
//		�L�����N�^�̃f�[�^���Ǘ�����
//		�C���[�W�A�X�N���v�g�A�R�}���h
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "GameTexture.h"

#include "Chara_Const.h"
#include "Action.h"
#include "Effect.h"
#include "Behavior.h"
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	�L���� ���s��f�[�^ ver110
	//	
	//	�L����	
	//		���r�w�C�r�A
	//		��	��[]�X�N���v�g
	//		��		��[]���[�g
	//		��		��[]Ef�W�F�l���[�g
	//		��
	//		���K�[�j�b�V��
	//		��	��[]�X�N���v�g
	//		��		��[]Ef�W�F�l���[�g
	//		��
	//		��[]�R�}���h
	//		��[]�u�����`
	//		��[]���[�g
	//
	//==================================================================================


	class Chara
	{
//		Behavior		m_bhvMain;		//���C�� �X�N���v�g
		PVP_TxBs		m_pvpTxMain;	//���C���C���[�W �e�N�X�`���z��
		PVP_Action		m_pvpAction;	//�A�N�V�����z��

//		Garnish			m_bhvEf;		//EF �X�N���v�g
		PVP_TxBs		m_pvpTxEf;		//EF�C���[�W �e�N�X�`���z��
		PVP_Effect		m_pvpEf;		//�G�t�F�N�g�z��

		VP_Command		m_vpCommand;	//�R�}���h�z��
		VP_Branch		m_vpBranch;		//�u�����`�z��
		VP_Route		m_vpRoute;		//���[�g�z��

	public:
		Chara ();
		Chara ( const Chara & rhs ) = delete;
		~Chara ();

		void Make ();
		void Rele ();
		void Reset ();

		void Clear ();

		//-----------------------------------------------------------------
		//���C���C���[�W �e�N�X�`���z��|�C���^
		PVP_TxBs GetpvpMainTexture () const { return m_pvpTxMain; }

		//���C���C���[�W �e�N�X�`���z��ɒǉ�
		void AddpMainTexture ( P_TxBs pTexture ) { m_pvpTxMain->push_back ( pTexture ); }

		//���C���C���[�W �e�N�X�`���|�C���^�̎擾
		P_TxBs GetpMainTexture ( UINT index ) { return m_pvpTxMain->at ( index ); }

		//-----------------------------------------------------------------
		//�A�N�V�����z��|�C���^���擾
		PVP_Action GetpvpAction () { return m_pvpAction; }

		//�A�N�V�����z��ɒǉ�
		void AddpAction ( P_Action pAction ) { m_pvpAction->push_back ( pAction ); }

		//�A�N�V�����z��ɂ܂Ƃ߂Ēǉ�
		void AddpAction ( unique_ptr < P_Action [] > arypAction, rsize_t size );
		void AddpAction ( std::shared_ptr < P_Action [] > arypAction, rsize_t size );
		void AddpAction ( const std::vector < P_Action > & arypAction, rsize_t size );

		//---------------------------------------------------------------------
		//���O����A�N�V����ID���擾����(�����Ƃ��͂O��Ԃ�)
		UINT GetActionID ( tstring name ) const;

		//�A�N�V�����|�C���^���擾
		P_Action GetpAction ( UINT index ) { return m_pvpAction->at ( index ); }
		P_Action GetpAction ( tstring name ) { return GetpAction ( GetActionID ( name ) ); }

		//---------------------------------------------------------------------
		//�X�N���v�g�|�C���^���擾
		P_Script GetpScript ( UINT indexAction, UINT indexScript ) { return m_pvpAction->at ( indexAction )->GetpScript( indexScript ); }

		//���X�N���v�g�����݂��邩�ǂ���
		bool IsNextScript ( UINT indexAction, UINT indexScript )
		{
			return m_pvpAction->at ( indexAction )->IsNextScript( indexScript );
		}

		//-----------------------------------------------------------------
		//Ef�C���[�W �e�N�X�`���z��|�C���^
		PVP_TxBs GetpvpEfTexture () const { return m_pvpTxEf; }

		//Ef�C���[�W �e�N�X�`���z��ɒǉ�
		void AddpEfTexture ( P_TxBs pTexture ) { m_pvpTxEf->push_back ( pTexture ); }

		//�G�t�F�N�g�z��ɂ܂Ƃ߂Ēǉ�
		void AddpEffect ( unique_ptr < P_Effect [] > arypEffect, rsize_t size );
		void AddpEffect ( const std::vector < P_Effect > & arypEffect, rsize_t size );

		//Ef�C���[�W �e�N�X�`���|�C���^�̎擾
		P_TxBs GetpEfTexture ( UINT index ) { return m_pvpTxEf->at ( index ); }

		//-----------------------------------------------------------------
		//�G�t�F�N�g�z��ɒǉ�
		void AddpEffect ( P_Effect pEffect ) { m_pvpEf->push_back ( pEffect ); }

		//�G�t�F�N�g�z��|�C���^���擾
		PVP_Effect GetpvpEffect () { return m_pvpEf; }

		//�G�t�F�N�g�|�C���^���擾
		P_Effect GetpEffect ( UINT index ) { return m_pvpEf->at ( index ); }

		//---------------------------------------------------------------------
		//�R�}���h�z��ɒǉ�
		void AddpCommand ( P_Command pCommand ) { m_vpCommand.push_back ( pCommand ); }
		void AddaCommand ( unique_ptr < P_Command [] > aryCmd, UINT size );

		//�R�}���h���擾
		P_Command GetpCommand ( UINT indexCommand ) const { return m_vpCommand[indexCommand]; }
		const VP_Command & GetvpCommand () const { return m_vpCommand; }


		//�u�����`�z��ɒǉ�
		void AddpBranch ( P_Branch pBranch ) { m_vpBranch.push_back ( pBranch ); }
		void AddaBranch ( unique_ptr < P_Branch [] > aryBrc, UINT size );

		//�u�����`���擾
		P_Branch GetpBranch ( UINT indexBranch ) const { return m_vpBranch[indexBranch]; }
		const VP_Branch & GetvpBranch () const { return m_vpBranch; }


		//���[�g�z��ɒǉ�
		void AddpRoute ( P_Route pRoute ) { m_vpRoute.push_back ( pRoute ); }
		void AddaRoute ( unique_ptr < P_Route [] > aryRut, UINT size );

		//���[�g���擾
		P_Route GetpRoute ( UINT indexRoute ) const { return m_vpRoute[indexRoute]; }
		const VP_Route & GetvpRoute () const { return m_vpRoute; }
	};

	using P_Chara = std::shared_ptr < Chara >;
	using VP_Chara = std::vector < P_Chara >;
	using PVP_Chara = std::shared_ptr < VP_Chara >;


}	//namespace GAME


