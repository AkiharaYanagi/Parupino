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

	public:
		DispFrontEnd ();
		DispFrontEnd ( const DispFrontEnd & rhs ) = delete;
		~DispFrontEnd ();

		//�Q�[�W�ނ̕\�����̂ݏ�����
		void InitDisp ( PLAYER_ID playerID );

		//�Q�[�W�ލX�V
		void UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance );
	};


}	//namespace GAME

