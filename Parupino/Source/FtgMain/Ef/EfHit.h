//=================================================================================================
//
//	EfHit �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"
#include "../G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�q�b�g�G�t�F�N�g�N���X
//	class EfHit : public GrpEf
	class EfHit : public GrpAcv
	{
		int			m_count;
		static const float		OMEGA;
		VEC2	m_tx_rev;		//�e�N�X�`���̑傫���ɂ��\���␳�ʒu
		VEC2	m_center;		//�Q�[���ʒu�ɂ�����O���t�B�b�N���S�ʒu
		VEC2	m_dispBase;		//�f�B�X�v���C�␳�ʒu

	public:
		EfHit ();
		EfHit ( const EfHit & rhs ) = delete;
		~EfHit ();

		void TxLoad ();
		void Move ();
		void On ( VEC2 center );
	};

	using P_EfHit = std::shared_ptr < EfHit >;

}	//namespace GAME


