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
#include "../BtlParam.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispFrontEnd
	{
		PLAYER_ID	m_playerID;				//�v���C���ʕ\����

		P_PrmRect	m_gaugeLife;			//���C�t�Q�[�W�\��
		P_PrmRect	m_gaugeFrameLife;		//���C�t�Q�[�W�g�\��
		P_PrmRect	m_gaugeDecreaseLife;	//���C�t�Q�[�W�������\��
		float		m_fDamage;				//���C�t�Q�[�W������

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
#if	0
		//�G�t�F�N�g
		GrpEf		m_grpHitEf;			//�q�b�g�G�t�F�N�g
		GrpEf		m_grpAvoidEf;		//�A���H�C�h�G�t�F�N�g
		GrpEf		m_grpPoisedEf;		//�\���G�t�F�N�g

		P_GrpApTx		m_efGraphic;		//�G�t�F�N�g�O���t�B�b�N�\��
		OperateEffect*		m_pOprtEf;
#endif	//0


	public:
		DispFrontEnd ();
		DispFrontEnd ( const DispFrontEnd & rhs ) = delete;
		~DispFrontEnd ();

		//�Q�[�W�ނ̕\�����̂ݏ�����
		void LoadPlayer ( PLAYER_ID playerID );

		//������
		void Init ();

		//�Q�[�W�ލX�V
		void UpdateGauge ( BtlParam btlPrm );

#if 0
		//�q�b�g�X�g�b�v���ԕ\���̍X�V
		void UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer );

		//�̂����莞�ԕ\���̍X�V
		void UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer );

		//�q�b�g
		void OnHit ( VEC2 ptChara, bool dirRight );

		//�A���H�C�h
		void OnAvoid ( VEC2 ptChara, bool dirRight );

		//�|�C�Y�h
		void OnPoised ( VEC2 ptChara, bool dirRight );
#endif // 0

	};


}	//namespace GAME

