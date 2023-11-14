//=================================================================================================
//
// DispEffect �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "../../FtgMain/G_Ftg.h"
#include "../Disp/DispRect.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispEffect : public TASK_VEC
	{
		P_GrpApTx		m_grp;			//�O���t�B�b�N�\��
		PVP_TxBs		m_pvpEfTx;		//�G�t�F�N�g�C���[�W�̃e�N�X�`�����X�g
		P_DispRect		m_dispRect;		//�G�t�F�N�g�g�\��

	public:
		DispEffect ( PVP_TxBs pvpEfTx, float z );
		DispEffect ( const DispEffect & rhs ) = delete;
		~DispEffect ();
		
		//�L���t���O�ݒ�
		void SetValid ( bool b ) { m_grp->SetValid ( b ); }

		//�X�V
		void Update ( P_Script pScript, VEC2 ptEf, bool dirRight );

		//�\���g�ݒ�
		void SetpCharaRect ( P_CharaRect pCharaRect );

		//�g�\��
		void OnRect () { m_dispRect->OnRect (); }
		//�g��\��
		void OffRect () { m_dispRect->OffRect (); }
	};

	using P_DispEffect = std::shared_ptr < DispEffect >;


}	//namespace GAME


