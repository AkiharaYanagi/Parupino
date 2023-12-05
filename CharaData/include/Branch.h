//=================================================================================================
//
//	Branch �w�b�_�t�@�C��
//		�X�N���v�g�J�ڏ����̓��̓R�}���h�ƑJ�ڐ�V�[�N�G���X
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define.h"
#include "Chara_Const.h"
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�O���錾
	class Sequence;
	using P_Sqc = std::shared_ptr < Sequence >;
	using WP_Sqc = std::weak_ptr < Sequence >;		//�z�Q��

	using VP_Sqc = std::vector < P_Sqc >;
	using PVP_Sqc = std::shared_ptr < VP_Sqc >;
	using WP_Command = std::weak_ptr < Command >;		//�z�Q��

	class Branch
	{
		tstring		m_name;				//���O
		BRANCH_CONDITION		m_condition;	//�������
		UINT		m_indexCommand;		//�����R�}���h�z��Y��
		WP_Command	m_pCommand;			//�����R�}���h�|�C���^
		UINT		m_indexSequence;	//�J�ڐ�V�[�N�G���X�Y��
		WP_Sqc		m_pSequence;		//�J�ڐ�V�[�N�G���X�|�C���^
		UINT		m_indexFrame;		//�J�ڐ�X�N���v�g�ʒu

	public:
		Branch ();
		Branch ( const Branch & rhs ) = delete;
		~Branch ();

		//���O
		tstring GetName () const { return m_name; }
		void SetName ( tstring name ) { m_name.assign ( name ); }

		//�������
		void SetCondition ( BRANCH_CONDITION bc ) { m_condition = bc; }
		BRANCH_CONDITION GetCondition () const { return m_condition; }

		//�����R�}���h�z��Y��
		void SetIndexCommand ( UINT index ) { m_indexCommand = index; }
		UINT GetIndexCommand () const { return m_indexCommand; }

		//�����R�}���h�|�C���^
		void SetpCommand ( P_Command pCommand ) { m_pCommand = pCommand; }
		WP_Command GetpCommand () const { return m_pCommand; }

		//�J�ڐ�V�[�N�G���X�z��Y��
		void SetIndexSequence ( UINT index ) { m_indexSequence = index; }
		UINT GetIndexSequence () const { return m_indexSequence; }

		//�J�ڐ�V�[�N�G���X�|�C���^
		void SetpSequence ( P_Sqc pAction ) { m_pSequence = pAction; }
		WP_Sqc GetpSequence () const { return m_pSequence; }

		//�J�ڐ�X�N���v�g�ʒu
		void SetIndexFrame ( UINT index ) { m_indexFrame = index; }
		UINT GetIndexFrame () const { return m_indexFrame; }
	};


	using P_Branch = std::shared_ptr < Branch >;
	using VP_Branch = std::vector < P_Branch >;
	using PVP_Branch = std::shared_ptr < VP_Branch >;


}	//namespace GAME


