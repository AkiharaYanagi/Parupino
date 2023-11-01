//=================================================================================================
//
//	EfHit �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "EfHit.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�g��tan(��)�p
	const float EfHit::OMEGA = D3DX_PI_HALF / ( 30 );

	EfHit::EfHit ()
		: m_tx_rev ( VEC2 ( 0, 0 ) ), m_center ( VEC2 ( 0, 0 ) ), m_dispBase ( VEC2 ( 0, 0 ) )
	{
		AddTexture ( _T ( "Ef_Hit.png" ) );

		m_count = 0;
#if 0
		SetStartScaling ( VEC2 ( 1.f, 1.f ) );
		SetTargetScaling ( VEC2 ( 2.f, 2.f ) );
		SetVel ( VEC2 ( 0.1f, 1.f ) );
#endif // 0

		SetValid ( F );
	}

	EfHit::~EfHit ()
	{
	}

	void EfHit::TxLoad ()
	{
		GrpAcv::TxLoad ();

		//�e�N�X�`���̓Ǎ���
		VEC2 center = GetCenterOfTexture ( 0 );
		SetScalingCenter ( center );	//�g�k�̒��S
		SetRotationCenter ( center );	//��]�̒��S
		m_tx_rev -= center;
		SetPos ( m_tx_rev );
	}

	void EfHit::On ( VEC2 center )
	{
		//�ғ��J�n
		SetValid ( T );

		//�ʒu
		m_center = center;

		//�t�F�[�h([F],�J���[)
		SetFadeOut ( 30, 0x80ffffff );

		//��]�p(�����_��)
		float rad = D3DX_2PI / 360;
		int random = rand () % 360;
		SetRadian ( rad * random );

		//�g�k
		m_count = 0;
	}

	void EfHit::Move ()
	{
		//��A�N�e�B�u���͉������Ȃ�
		if ( ! GetValid () ) { GrpAcv::Move (); return; }

		float scale = 1.f;
		if ( OMEGA * m_count >= D3DX_PI_HALF )
		{
			scale = 100.f;
		}
		else
		{
			scale = tanf ( OMEGA * m_count );
		}

		SetScaling ( scale, scale );

		++ m_count;
//		m_count += 2;
		if ( OMEGA * m_count >= D3DX_PI_HALF ) { m_count = 0; }


		//��ʈʒu�␳
		m_dispBase = G_BASE_POS ();

		//���S�ʒu + �O���␳�ʒu
		SetPos ( m_tx_rev + m_center + m_dispBase );

		GrpAcv::Move ();
	}
}
