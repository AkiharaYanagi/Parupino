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
#include "Chara.h"
#include "../../GameMain/Param.h"
#include "../../FtgMain/G_Ftg.h"
#include "../BtlParam.h"
#include "DispGauge.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispFrontEnd : public TASK_VEC
	{
		PLAYER_ID	m_playerID;			//�v���C����

		P_DispGauge	m_gaugeLife;		//���C�t�Q�[�W
		P_DispGauge	m_gaugeBalance;		//�o�����X�Q�[�W
		P_DispGauge	m_gaugeMana;		//�}�i�Q�[�W

#if	0
		PrmRect		m_gaugeHitStop;			//�q�b�g�X�g�b�v���ԕ\��
		PrmRect		m_gaugeLurch;			//�̂����莞�ԕ\��

											//�G�t�F�N�g
		GrpEf		m_grpHitEf;			//�q�b�g�G�t�F�N�g
		GrpEf		m_grpAvoidEf;		//�A���H�C�h�G�t�F�N�g
		GrpEf		m_grpPoisedEf;		//�\���G�t�F�N�g

		P_GrpApTx		m_efGraphic;		//�G�t�F�N�g�O���t�B�b�N�\��
		OperateEffect*		m_pOprtEf;
#endif	//0
		//-----------------------------------------------------

		P_GrpAcv	m_grp_Cst_Player1P2P;	//�v���C���� �Œ�\��"1P""2P"
		P_GrpAcv	m_grp_Cst_InputPlayerCOM;	//���͎� �Œ�\��"CPU""Player"

		P_GrpAcv	m_grp_CH_Player1P2P;	//�L�����ߖT �v���C���\��"1P""2P"
		P_GrpAcv	m_grp_CH_InputCOMPLayer;	//�L�����ߖT ���͎ҕ\��"CPU""Player"

		static VEC2 POS_PL_CP_1P;
		static VEC2 POS_PL_CP_2P;

		enum DISP_FE_CONST
		{
			SIDE_1P = 0,
			SIDE_2P = 1,

			INPUT_PLAYER = 0,
			INPUT_CPU = 1,
		};

	public:
		DispFrontEnd ();
		DispFrontEnd ( const DispFrontEnd & rhs ) = delete;
		~DispFrontEnd ();

		void ParamInit ( P_Param pParam );


		//�Q�[�W�ނ̕\�����̂ݏ�����
		void LoadPlayer ( PLAYER_ID playerID );

		//���C���C���[�W�X�V
		void UpdateMainImage ( VEC2 posChara );

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

		void SetPlayer ();
		void SetCPU ();

	private:
		P_GrpAcv MakepGrpPlyr ( LPCTSTR pstr );

	};

	using P_DispFrontEnd = std::shared_ptr < DispFrontEnd >;


}	//namespace GAME

