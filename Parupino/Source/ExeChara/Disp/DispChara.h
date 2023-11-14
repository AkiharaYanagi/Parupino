//=================================================================================================
//
// DispChara �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/G_Ftg.h"
#include "../../GameMain/Param.h"
#include "DispMainImage.h"
#include "DispRect.h"
#include "DispFrontEnd.h"
#include "DispInput.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispChara : public TASK_VEC
	{
		P_DispMainImage	m_mainImage;	//���C���C���[�W
		P_DispRect		m_dispRect;		//�g
		P_GrpAcv		m_grpShadow;	//�e
		P_DispFrontEnd	m_frontEnd;		//�t�����g�G���h
		P_DispInput		m_dispInput;	//���͕\��


	public:
		DispChara ();
		DispChara ( const DispChara & rhs ) = delete;
		~DispChara ();

		void ParamInit ( P_Param pParam );


		//�L������ݒ肷��
		void SetpChara ( const P_Chara pChara );

		//���C���C���[�W�̍X�V
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );

		//�\���g�ݒ�
		void SetpCharaRect ( P_CharaRect pCharaRect );


		//�g�\��ON
		void OnRect () { m_dispRect->OnRect (); }
		//�g�\��OFF
		void OffRect () { m_dispRect->OffRect (); }

		//PLAYER / CPU
		void SetControl_PLAYER () { m_frontEnd->SetPlayer (); }
		void SetControl_CPU () { m_frontEnd->SetCPU (); }


		//�Q�[�W�ނ̕\�����̂ݏ�����
		void LoadPlayer ( PLAYER_ID playerID );

		//�Q�[�W�ލX�V
		void UpdateGauge ( BtlParam btlPrm );

		//���͍X�V
		void UpdateInput ( P_CharaInput p ) { m_dispInput->UpdateInput ( p ); }
	};


	using P_DispChara = std::shared_ptr < DispChara >;


}	//namespace GAME


