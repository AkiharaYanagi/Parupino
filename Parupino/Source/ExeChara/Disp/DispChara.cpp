//=================================================================================================
//
// DispChara �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DispChara.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DispChara::DispChara ()
	{
		//�e
		m_grpShadow = make_shared < GrpAcv > ();
		m_grpShadow->AddTexture ( _T("shadow.png") );
		m_grpShadow->SetZ ( Z_SHADOW );
		GRPLST_INSERT ( m_grpShadow );
	}

	DispChara::~DispChara ()
	{
	}

	//�v���C��ID��ݒ�
	void DispChara::LoadPlayer ( PLAYER_ID playerID )
	{ 
		m_frontEnd.LoadPlayer ( playerID );
		m_dispInput.LoadPlayer ( playerID );
	}

	//�L�����f�[�^��ݒ�
	void DispChara::SetpChara ( const P_Chara pChara )
	{
		m_mainImage.SetpChara ( pChara );
	}

	//�g�f�[�^��ݒ�
	void DispChara::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect.SetCharaRect ( pCharaRect );
	}

	//���t���[���ɂ����郁�C���C���[�W�̍X�V
	void DispChara::UpdateMainImage ( P_Script pScript, VEC2 posChara, bool dirRight )
	{
		//���C��
		m_mainImage.UpdateMainImage ( pScript, posChara, dirRight );

		//�e
		float fDir = dirRight ? ( 1.f ) : ( -1.f );		//����
		float bx = G_Ftg::inst ()->GetPosMutualBase ().x;	//��ʒu
		VEC2 vecImgShadow = VEC2 ( bx, 0 ) + posChara + VEC2 ( -128 + fDir * 12, 0 );
		vecImgShadow.y = -32.f + 1.f * PLAYER_BASE_Y;
		m_grpShadow->SetPos ( vecImgShadow );

		//����
		m_dispRect.Update ();
	}


	//�Q�[�W�ލX�V
	void DispChara::UpdateGauge ( BtlParam btlPrm )
	{
		m_frontEnd.UpdateGauge ( btlPrm );
	}


}	//namespace GAME

