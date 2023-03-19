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
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/G_Ftg.h"
#include "../../CharaData/Chara.h"
#include "DispMainImage.h"
#include "DispRect.h"
#include "../CharaRect.h"
#include "DispFrontEnd.h"
#include "DispInput.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispChara
	{
		DispMainImage	m_mainImage;	//���C���C���[�W
		DispRect		m_dispRect;		//�g
		P_GrpAcv		m_grpShadow;	//�e
		DispFrontEnd	m_frontEnd;		//�t�����g�G���h
		DispInput		m_dispInput;	//���͕\��

	public:
		DispChara ();
		DispChara ( const DispChara & rhs ) = delete;
		~DispChara ();

		//�L������ݒ肷��
		void SetpChara ( const P_Chara pChara );

		//���C���C���[�W�̍X�V
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );

		//�\���g�ݒ�
		void SetpCharaRect ( P_CharaRect pCharaRect );

		//�g�\��ON
		void OnRect () { m_dispRect.OnRect (); }
		//�g�\��OFF
		void OffRect () { m_dispRect.OffRect (); }

		//�Q�[�W�ނ̕\�����̂ݏ�����
		void LoadPlayer ( PLAYER_ID playerID );

		//�Q�[�W�ލX�V
//		void UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance );
		void UpdateGauge ( BtlParam btlPrm );

		//���͍X�V
		void UpdateInput ( P_CharaInput p ) { m_dispInput.UpdateInput ( p ); }
	};

}	//namespace GAME


