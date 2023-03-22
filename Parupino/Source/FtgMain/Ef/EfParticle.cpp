////=================================================================================================
//
//	EfParticle �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "EfParticle.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�����͕����E���x�Ƃ��Ƀ����_��
	//���̌����ł��̏�ɗh��Ȃ����������

	EfParticle::EfParticle ()
	{
		AddTexture ( _T ( "Ef_Particle.png" ) );

		//�O���t�B�b�N�I�u�W�F�N�g��������
		ResetObjectNum ( SPARK_NUM );

		//�p�����[�^��������
		PVP_Object pvpObject = GetpvpObject ();
		UINT i = 0;
		for ( P_Object pOb : * pvpObject )
		{
			PrmEfParticle prm;
			
			//�ʒu
			prm.m_pos.x = 0;
			prm.m_pos.y = 0;

			//�p�x
			float rad = D3DX_2PI / SPARK_NUM;
			float rad_i = rad * i;
			prm.m_angle = rad_i;

			//cos((�ߎ�)��/2)�𐧌�
			float c = cosf ( rad_i );
			if ( D3DX_PI_HALF - 0.01 < rad_i && rad_i < D3DX_PI_HALF + 0.01 ) { c = 0; }

			//sin((�ߎ�)��)�𐧌�
			float s = sinf ( rad_i );
			if ( 3.14f < rad_i && rad_i < 3.15f ) { s = 0; }

			float rndx = 1.f * (rand () % 20);
			float rndy = 1.f * (rand () % 20);

			prm.m_startVel = VEC2 ( (rndx + 5.f) * c, (rndy + 5.f) * s );
			prm.m_vel.x = 0;
			prm.m_vel.y = 0;
			prm.m_G = VEC2 ( 0, 0 );

			pOb->SetRadian ( D3DX_PI_HALF + rad_i );
			pOb->SetValid ( false );

			m_vPrm.push_back ( prm );

			++ i;
		}
	}

	EfParticle::~EfParticle ()
	{
	}

	void EfParticle::Move ()
	{
		PVP_Object pvpObject = GetpvpObject ();
		UINT i = 0;
		for ( P_Object pOb : *pvpObject )
		{
			if ( ! pOb->GetValid () ) { continue; }

			//�ʒu�v�Z
			VEC2 prePos = m_vPrm[i].m_pos;
			m_vPrm[i].m_vel += -0.03f * m_vPrm[i].m_vel;	//����
			m_vPrm[i].m_vel += m_vPrm[i].m_G;
			m_vPrm[i].m_pos += m_vPrm[i].m_vel;

			//��ʒu + �␳�ʒu + �O���␳�ʒu + �ʈʒu
			VEC2 prePosMatrix = GetCalcPos ( i );
			SetPosMatrix ( i, m_vPrm[i].m_pos );

			//�C���f�b�N�X
			++ i;
		}

		GrpEf::Move ();
	}

	void EfParticle::On ( VEC2 center )
	{
		//�����ʒu�Ə��������Z�b�g
		PVP_Object pvpObject = GetpvpObject ();
		UINT i = 0;
		for ( P_Object pOb : *pvpObject )
		{
			pOb->SetValid ( T );
			m_vPrm[i].m_pos = VEC2 ( 0, 0 );
			m_vPrm[i].m_vel = m_vPrm[i].m_startVel;
			//�C���f�b�N�X
			++i;
		}

		SetpDispBase ( G_BASE_POS () );
		SetPos ( center );
		SetValid ( true );
		GrpEf::On ();
	}
}
