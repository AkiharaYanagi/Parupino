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
#include "Game.h"
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�O���錾
	class Sequence;
	using P_Sqc = shared_ptr < Sequence >;
	using WP_Sqc = weak_ptr < Sequence >;		//�z�Q��

	using VP_Sqc = vector < P_Sqc >;
	using PVP_Sqc = shared_ptr < VP_Sqc >;
	using WP_Command = weak_ptr < Command >;		//�z�Q��

	class Branch
	{
		UINT		m_indexCommand;		//�����R�}���h�z��Y��
		WP_Command	m_pCommand;			//�����R�}���h�|�C���^
		UINT		m_indexSequence;	//�J�ڐ�V�[�N�G���X�Y��
		WP_Sqc		m_pSequence;		//�J�ڐ�V�[�N�G���X�|�C���^
		UINT		m_indexFrame;		//�J�ڐ�X�N���v�g�ʒu

	public:
		Branch ();
		Branch ( const Branch & rhs ) = delete;
		~Branch ();

		//������Z�q
//		Branch& operator = ( const Branch& rhs );

		//�����R�}���h�z��Y��
		void SetIndexCommand ( UINT index ) { m_indexCommand = index; }
		UINT GetIndexCommand () const { return m_indexCommand; }

		//�����R�}���h�|�C���^
		void SetpCommand ( P_Command pCommand ) { m_pCommand = pCommand; }
		WP_Command GetpCommand () const { return m_pCommand; }

		//�J�ڐ�V�[�N�G���X�z��Y��
		void SetIndexAction ( UINT index ) { m_indexSequence = index; }
		UINT GetIndexAction () const { return m_indexSequence; }

		//�J�ڐ�V�[�N�G���X�|�C���^
		void SetpSequence ( P_Sqc pAction ) { m_pSequence = pAction; }
		WP_Sqc GetpSequence () const { return m_pSequence; }

		//�J�ڐ�X�N���v�g�ʒu
		void SetIndexFrame ( UINT index ) { m_indexFrame = index; }
		UINT GetIndexFrame () const { return m_indexFrame; }
	};


	using P_Branch = shared_ptr < Branch >;
	using VP_Branch = vector < P_Branch >;
	using PVP_Branch = shared_ptr < VP_Branch >;


}	//namespace GAME


