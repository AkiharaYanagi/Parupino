//=================================================================================================
//
// EffectGenerate �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
//#include "../Const.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class EffectGenerate
	{
		//--------------------------------------------------
		UINT	m_id;		//�G�t�F�N�g������ID

		//--------------------------------------------------
		UINT	m_index;	//�w��Ef�C���f�b�N�X
		VEC2	m_pos;		//�����ʒu
		float	m_z;		//z�ʒu
		bool	m_gnrt;		//����
		bool	m_loop;		//�J��
		bool	m_sync;		//����

	public:
		EffectGenerate ();
		EffectGenerate ( const EffectGenerate& rhs ) = delete;		//�R�s�[�֎~
		~EffectGenerate ();

		void SetID ( UINT i ) { m_id = i; }
		UINT GetID () const { return m_id; }

		void SetIndex ( UINT i ) { m_index = i; }
		UINT GetIndex () const { return m_index; }

		void SetPos ( VEC2 v ) { m_pos = v; }
		VEC2 GetPos () const { return m_pos; }

		void SetZ ( float f ) { m_z = f; }
		float GetZ () const { return m_z; }

		void SetGnrt ( bool b ) { m_gnrt = b; }
		bool GetGnrt () const { return m_gnrt; }

		void SetLoop ( bool b ) { m_loop = b; }
		bool GetLoop () const { return m_loop; }

		void SetSync ( bool b ) { m_sync = b; }
		bool GetSync () const { return m_sync; }

	};
	

	using P_EfGnrt = shared_ptr < EffectGenerate >;
	using VP_EfGnrt = vector < P_EfGnrt >;
	using PVP_EfGnrt = shared_ptr < VP_EfGnrt >;


}	//namespace GAME


