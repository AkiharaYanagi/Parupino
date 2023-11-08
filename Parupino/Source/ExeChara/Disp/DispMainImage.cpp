//=================================================================================================
//
// DispMainImage �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DispMainImage.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DispMainImage::DispMainImage ()
	{
		//���C���O���t�B�b�N
		m_mainGraphic = make_shared < GrpApTx > ();
		AddpTask ( m_mainGraphic );
		GRPLST_INSERT_MAIN ( m_mainGraphic );
	}

	DispMainImage::~DispMainImage ()
	{
	}

	void DispMainImage::SetpChara ( P_Chara pChara )
	{
		m_pvpMainTexture = pChara->GetpvpMainTexture ();
	}

	void DispMainImage::UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight )
	{
		//�ʒu
		VEC2 posScript = pScript->GetPos ();
		float fDir = dirRight ? ( 1.f ) : ( -1.f );		//����
		float bx = G_Ftg::inst ()->GetPosMutualBase ().x;	//��ʒu
		float x = bx + ptChara.x + fDir * posScript.x;
		float y = 0 + ptChara.y + 1.f * posScript.y;
		VEC2 vecImg = VEC2 ( x, y );

		//�\���ɔ��f
		m_mainGraphic->SetPos ( vecImg );
		m_mainGraphic->SetScaling ( 1.f * fDir, 1.f );

		UINT index = pScript->GetImageIndex ();

		//@todo �C���[�W����`��摜�폜���ID�ȂǃC���f�b�N�X�������ꍇ������
		if ( m_pvpMainTexture->size () < index ) { return; }

		P_TxBs pTexture = m_pvpMainTexture->at ( index );
		m_mainGraphic->SetpTexture ( pTexture );
	}

}	//namespace GAME

