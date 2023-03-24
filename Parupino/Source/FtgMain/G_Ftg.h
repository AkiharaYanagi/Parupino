//=================================================================================================
//
//	G_Ftg �w�b�_�t�@�C��
//		Fighting���ʃO���[�o���ϐ��Q
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
#include "../FtgMain/FtgConst.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class G_Ftg
	{
	//---------------------------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using  _P_G_Ftg = unique_ptr < G_Ftg >;
		static _P_G_Ftg m_inst;		//�V���O���g���C���X�^���X
		G_Ftg ();		//private �R���X�g���N�^�Œʏ�̎��̉��͋֎~
	public:
		~G_Ftg ();		//�f�X�g���N�^��unique_ptr�̂���public
		static void Create() { if ( ! m_inst ) { m_inst = _P_G_Ftg ( new G_Ftg () ); } }
		static _P_G_Ftg & inst () { return m_inst; }	//�C���X�^���X�擾
	//---------------------------------------------------------------------

	private:

//		FIGHTING_STATE		m_enmFightingState;	//�i�s���

		VEC2	m_posMutualBase;		//�L�����ʒu�ɂ���ʕ␳��

	public:
#if 0
		//�t�@�C�e�B���O�V�[�����
		void SetFightingState ( FIGHTING_STATE fs ) { m_enmFightingState = fs; }
		FIGHTING_STATE GetFightingState () const { return m_enmFightingState; }
#endif // 0

		//��ʒ[�ł̕\����ʒu
		void CulcPosMutualBase ( VEC2 pos1p, VEC2 pos2p ) const;
		void SetPosMutualBase ( VEC2 v ) { m_posMutualBase = v; }
		VEC2 GetPosMutualBase () const { return m_posMutualBase; }

	};

	using  UP_G_Ftg = unique_ptr < G_Ftg >;
//#define G_FTG_STATE	G_Ftg::inst()->GetFightingState
//#define G_FTG_STATE_SET	G_Ftg::inst()->SetFightingState
#define G_BASE_POS	G_Ftg::inst()->GetPosMutualBase

}	//namespace GAME


