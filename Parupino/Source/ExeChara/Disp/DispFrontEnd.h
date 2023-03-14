//=================================================================================================
//
// DispFrontEnd �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../FtgMain/G_Ftg.h"
#include "../../CharaData/Chara.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispFrontEnd
	{
		P_PrmRect	m_gaugeLife;			//���C�t�Q�[�W�\��
		P_PrmRect	m_gaugeFrameLife;		//���C�t�Q�[�W�g�\��
		P_PrmRect	m_gaugeDecreaseLife;	//���C�t�Q�[�W�������\��

		P_PrmRect	m_gaugeBalance;			//�o�����X�Q�[�W�\��
		P_PrmRect	m_gaugeFrameBalance;	//�o�����X�Q�[�W�g�\��
		P_PrmRect	m_gaugeDecreaseBalance;	//�o�����X�Q�[�W�������\��

#if	0
		GrpAcv		m_grpPlayer1P;	//�v���C���[�\��"1P"
		GrpAcv		m_grpPlayer2P;	//�v���C���[�\��"2P"
		GrpAcv		m_grpPlayerCOM;	//�v���C���[�\��"CPU"

		PrmRect		m_gaugeHitStop;			//�q�b�g�X�g�b�v���ԕ\��
		PrmRect		m_gaugeLurch;			//�̂����莞�ԕ\��
#endif	//0

	public:
		DispFrontEnd ();
		DispFrontEnd ( const DispFrontEnd & rhs ) = delete;
		~DispFrontEnd ();

		//�Q�[�W�ނ̕\�����̂ݏ�����
		void LoadDisp ( PLAYER_ID playerID );

		//�Q�[�W�ލX�V
		void UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance );
	};


}	//namespace GAME

