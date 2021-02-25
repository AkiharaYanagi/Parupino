//=================================================================================================
//
// DispEffect �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DispEffect.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DispEffect::DispEffect ( PVP_TxBs pvpEfTx , float z ) 
		: m_pvpEfTx ( pvpEfTx )
	{
		//���C���O���t�B�b�N
		m_grp = make_shared < GrpApTx > ();
		m_grp->SetZ ( z / 100 );	//�����ʒu
		GRPLST_INSERT ( m_grp );

		//�g�\��(DispRect)�̓|�C���^�łȂ����̂�ێ�
	}

	DispEffect::~DispEffect ()
	{
		//�I�����ɃO���t�B�b�N�^�X�N���O��
		GRPLST_ERASE ( m_grp );
	}


	void DispEffect::Update ( P_Script pScript, VEC2 ptEf, bool dirRight )
	{
		//Disp�F�X�N���v�g�̃C���[�W�\���ʒu

		//�e�N�X�`���̎擾
		P_TxBs pEfTx = m_pvpEfTx->at ( pScript->GetImageIndex() );

		//�ʒu (�G�t�F�N�g�̃Q�[���ʒu�{�X�N���v�g�̕\���ʒu(*����)�{�L�����ɂ���ʕ␳�ʒu)
		float fDir = dirRight ? (1.f) : (-1.f);
		VEC2 tempImgPos = pScript->GetPos ();
		VEC2 imgPos = VEC2( fDir * tempImgPos.x, tempImgPos.y );
		VEC2 vecEfImg = ptEf + imgPos + G_BASE_POS ();

//		DBGOUT_WND_F ( 2, _T ( "DispEfPos = (%d,%d)" ), vecEfImg.x, vecEfImg.y );

		//�\���ɔ��f
		m_grp->SetPos ( vecEfImg );
		m_grp->SetScaling ( 1.f * fDir, 1.f );
		m_grp->SetpTexture ( pEfTx );
	}

	void DispEffect::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect.SetCharaRect ( pCharaRect );
	}


}	//namespace GAME

