//=================================================================================================
//
//	Sequence �w�b�_�t�@�C��
//		�X�N���v�g�̈�A�A�A�N�V�����ƃG�t�F�N�g�ɔh��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Script.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Sequence
	{
		PVP_Script		m_pvpScript;	//�X�N���v�g�z��
		UINT			m_next;			//���V�[�N�G���XID

	public:
		Sequence ();
		Sequence ( const Sequence & rhs ) = delete;
		virtual ~Sequence ();

		void Rele ();

		//-----------------------------------------------------------------
		//�X�N���v�g�̒ǉ�
		void AddpScript ( P_Script pScript ) { m_pvpScript->push_back ( pScript ); }

		//�X�N���v�g�z��T�C�Y�̎擾
		UINT SizeScript () const { return m_pvpScript->size(); }

		//�X�N���v�g�z��|�C���^���擾
		PVP_Script GetpvpScript () { return m_pvpScript; }

		//�X�N���v�g�̎擾
		P_Script GetpScript ( UINT index ) { return m_pvpScript->at ( index ); }

		//���X�N���v�g�����݂��邩�ǂ���
		bool IsNextScript ( UINT index ) const { return ( index < m_pvpScript->size() - 1 ); }

		//�ŏI�X�N���v�g���ǂ���
		bool IsEndScript ( UINT index ) const { return ( index == m_pvpScript->size() - 1 ); }

		//���V�[�N�G���XID
		UINT GetNextID () const { return m_next; }
		void SetNextID ( UINT id ) { m_next = id; }
	};

	using WP_Sqc = weak_ptr < Sequence >;
	using P_Sqc = shared_ptr < Sequence >;
	using VP_Sqc = vector < P_Sqc >;
	using PVP_Sqc = shared_ptr < VP_Sqc >;


}	//namespace GAME


