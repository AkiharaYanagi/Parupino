//=================================================================================================
//
// DispMainImage �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "../../FtgMain/G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�L�����ɂ����郁�C���C���[�W�̕\��
	//�e�N�X�`�����L�����f�[�^����p����
	class DispMainImage : public TASK_VEC
	{
		P_GrpApTx	m_mainGraphic;		//���C���O���t�B�b�N�\��
		PVP_TxBs	m_pvpMainTexture;	//���C���C���[�W�̃e�N�X�`�����X�g

	public:
		DispMainImage ();
		DispMainImage ( const DispMainImage & rhs ) = delete;
		~DispMainImage ();

		//���f�[�^�̐ݒ�
		void SetpChara ( P_Chara pChara );

		//���C���C���[�W�̍X�V
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );
	};

	using P_DispMainImage = std::shared_ptr < DispMainImage >;


}	//namespace GAME


