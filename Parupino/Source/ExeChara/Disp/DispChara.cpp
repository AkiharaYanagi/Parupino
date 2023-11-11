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
		m_mainImage = make_shared < DispMainImage > ();
		AddpTask ( m_mainImage );

		m_dispRect = make_shared < DispRect > ();
		AddpTask ( m_dispRect );

		m_frontEnd = make_shared < DispFrontEnd > ();
		AddpTask ( m_frontEnd );

		m_dispInput = make_shared < DispInput > ();
		AddpTask ( m_dispInput );

		//�e
		m_grpShadow = make_shared < GrpAcv > ();
		m_grpShadow->AddTexture ( _T ( "shadow.png" ) );
		m_grpShadow->SetZ ( Z_SHADOW );
		AddpTask ( m_grpShadow );
		GRPLST_INSERT_MAIN ( m_grpShadow );
	}

	DispChara::~DispChara ()
	{
	}

	//�v���C��ID��ݒ�
	void DispChara::LoadPlayer ( PLAYER_ID playerID )
	{
		m_frontEnd->LoadPlayer ( playerID );
		m_dispInput->LoadPlayer ( playerID );
	}

	//------------------------
	//�V�[���p�����[�^�֘A������
	void DispChara::ParamInit ( P_Param pParam )
	{
		m_frontEnd->ParamInit ( pParam );

#if DEBUG_DISP
		OnRect ();
#else
		OffRect ();
#endif // DEBUG_DISP

	}

	//�L�����f�[�^��ݒ�
	void DispChara::SetpChara ( const P_Chara pChara )
	{
		m_mainImage->SetpChara ( pChara );
	}

	//�g�f�[�^��ݒ�
	void DispChara::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect->SetCharaRect ( pCharaRect );
	}

	//���t���[���ɂ����郁�C���C���[�W�̍X�V
	void DispChara::UpdateMainImage ( P_Script pScript, VEC2 posChara, bool dirRight )
	{
		//���C��
		m_mainImage->UpdateMainImage ( pScript, posChara, dirRight );

		//�e
		float fDir = dirRight ? ( 1.f ) : ( -1.f );		//����
		float bx = G_Ftg::inst ()->GetPosMutualBase ().x;	//��ʒu
		VEC2 vecImgShadow = VEC2 ( bx, 0 ) + posChara + VEC2 ( -128 + fDir * 12, 0 );
		vecImgShadow.y = -32.f + 1.f * PLAYER_BASE_Y;	//y�����̂ݎw��
		m_grpShadow->SetPos ( vecImgShadow );

		//�g
		m_dispRect->Update ();

		//�t�����g�G���h�X�V
		m_frontEnd->UpdateMainImage ( posChara );
	}


	//�Q�[�W�ލX�V
	void DispChara::UpdateGauge ( BtlParam btlPrm )
	{
		m_frontEnd->UpdateGauge ( btlPrm );
	}


}	//namespace GAME

