//=================================================================================================
//
// ExeEffect �w�b�_�t�@�C��
//		Effect�P�ɂ��P�̃I�u�W�F�N�g�𐶐������s����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "DispEffect.h"
#include "../Rect/CharaRect.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class ExeEffect : public TASK_VEC
	{
		//------------------------------------------------
		P_Effect		m_pEffect;		//�����G�t�F�N�g�|�C���^

		P_Chara			m_pChara;		//�L����
		VP_Branch		m_vpBranch;		//�G�t�F�N�g�̕���
		VP_Route		m_vpRoute;		//���[�g

		//------------------------------------------------
		P_DispEffect	m_dispEffect;	//�\�����ڊǗ�
		bool			m_bDispRect;	//�g�\��

		//------------------------------------------------
		//�p�����[�^
		bool		m_active;		//�L���t���O
		bool		m_end;			//�I���t���O

		UINT		m_frame;		//���������t���[��(�X�N���v�gID)
		P_Script	m_pScript;		//�����X�N���v�g�|�C���^
		VEC2		m_ptEffect;		//�G�t�F�N�g�ʒu

		VEC2		m_ptGnrt;		//�G�t�F�N�g�����ʒu
		bool		m_gnrt;			//����
		bool		m_loop;			//�J��
		bool		m_sync;			//����

		bool		m_dirRight;	//�G�t�F�N�g�̌���
		VEC2		m_vel;	//���x
		VEC2		m_acc;	//�����x

		P_CharaRect		m_charaRect;	//�g

		bool		m_offset;		//���E
		bool		m_hit;			//�q�b�g

	public:
		ExeEffect ( P_Effect pEffect, P_Chara pChara, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight );
		ExeEffect ( const ExeEffect & rhs ) = delete;
		~ExeEffect ();

		//---------------------------------------------
		//�g�擾
		P_CharaRect GetpCharaRect () { return m_charaRect; }
		//---------------------------------------------

		void SetpEfGnrt ( P_EfGnrt p );

		P_Effect GetpEffect () const { return m_pEffect; }
		bool Compare ( P_Effect p ) { return ( p == m_pEffect); }

		bool IsActive () const { return m_active; }
		bool IsEnd () const { return m_end; }

		P_Script GetpScript ()
		{
			return m_pEffect->GetpScript ( m_frame );
		}

		//�ғ��J�n
		void Drive () { m_active = true; }

		//�ғ���~
		void Stop ()
		{
			m_active = false;
			m_dispEffect->SetValid ( false );
		}

		void PreScriptMove ();
		void PostScriptMove ( VEC2 ptChara, bool dirRight );
		void SynchroScript ( VEC2 ptChara );

//		void SetZ ( float z ) { m_dispEffect.SetZ ( z ); }

		//���E
		void SetOffset ( bool b ) { m_offset = b; }
		bool GetOffset () const { return m_offset; }

		//�q�b�g
		void SetHit ( bool b ) { m_hit = b; }
		bool GetHit () const { return m_hit; }

		//---------------------------------------------------------------
		//Rect
		void OnDispRect () { m_bDispRect = true; }
		void OffDispRect () { m_bDispRect = false; }

	private :
		//x���������𔽉f����
		VEC2 Dir ( VEC2 v ) const
		{
			if ( m_dirRight ) { return v; }
			return VEC2 ( -v.x, v.y );
		}
	};

	//�^�ʒ�` �G�C���A�X
	using ExEf = ExeEffect;
	using P_ExEf = std::shared_ptr < ExEf >;

	using VP_ExEf = std::vector < P_ExEf >;
	using PVP_ExEf = std::shared_ptr < VP_ExEf >;

	using LP_ExEf = list < P_ExEf >;
	using PLP_ExEf = std::shared_ptr < LP_ExEf >;


}	//namespace GAME


