//=================================================================================================
//
// DispDecision �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "../../GameMain/GameConst.h"
#include "../../CharaData/Chara.h"
//#include "../../Fighting/Const_Fighting.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispDecision : public GameTaskVector
	{
		P_GrpAcv		m_L_P1;
		P_GrpAcv		m_M_P1;
		P_GrpAcv		m_H_P1;
		P_GrpAcv		m_A_P1;
		P_GrpAcv		m_Right_P1;
		P_GrpAcv		m_Left_P1;
		P_GrpAcv		m_Equal_P1;

		P_GrpAcv		m_L_P2;
		P_GrpAcv		m_M_P2;
		P_GrpAcv		m_H_P2;
		P_GrpAcv		m_A_P2;
		P_GrpAcv		m_Right_P2;
		P_GrpAcv		m_Left_P2;
		P_GrpAcv		m_Equal_P2;

		P_GrpAcv		m_resultEqual;
		P_GrpAcv		m_resultLeft;
		P_GrpAcv		m_resultRight;

	public:
		DispDecision ();
		DispDecision ( const DispDecision & rhs ) = delete;
		~DispDecision ();

		void Init ();
		void Move ();

		void Clear ();

		void ClearCategory ();
		void ClearDecision ();

		//�A�N�V�����J�e�S���ݒ�
		void SetActionCategory ( ACTION_CATEGORY ac1, ACTION_CATEGORY ac2 );

		//�ō����ʐݒ�
		void SetDecision ( CLANG_DECISION_LR cd );
	};


}	//namespace GAME


