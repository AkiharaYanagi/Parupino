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

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispChara : public TASK_VEC
	{
		DispMainImage	m_mainImage;	//���C���C���[�W
		DispRect		m_dispRect;		//�g
		P_GrpAcv		m_grpShadow;	//�e
		DispFrontEnd	m_frontEnd;		//�t�����g�G���h

#if	0
		//�G�t�F�N�g
		GrpEf		m_grpHitEf;			//�q�b�g�G�t�F�N�g
		GrpEf		m_grpAvoidEf;		//�A���H�C�h�G�t�F�N�g
		GrpEf		m_grpPoisedEf;		//�\���G�t�F�N�g

		P_GrpApTx		m_efGraphic;		//�G�t�F�N�g�O���t�B�b�N�\��
		OperateEffect*		m_pOprtEf;
#endif	//0

	public:
		DispChara ();
		DispChara ( const DispChara & rhs ) = delete;
		~DispChara ();

		//�L������ݒ肷��
		void SetpChara ( const P_Chara pChara );

		//���C���C���[�W�̏�����
	//void InitMainImage ( UINT indexTexture );

		//���C���C���[�W�̍X�V
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );

		//�\���g�ݒ�
		void SetpCharaRect ( P_CharaRect pCharaRect );

		//�g�\��
		void OnRect () { m_dispRect.OnRect (); }
		//�g��\��
		void OffRect () { m_dispRect.OffRect (); }

		//�Q�[�W�ނ̕\�����̂ݏ�����
		void InitDisp ( PLAYER_ID playerID );

		//�Q�[�W�ލX�V
		void UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance );


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


