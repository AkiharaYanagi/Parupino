//=================================================================================================
//
//	EfSpark �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "EfSpark.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfSpark::EfSpark ()
	{
		AddTexture ( _T ( "Ef_Spark.png" ) );

		//�O���t�B�b�N�I�u�W�F�N�g��������
		ResetObjectNum ( SPARK_NUM );

		//�p�����[�^��������
		PVP_Object pvpObject = GetpvpObject ();
		UINT i = 0;
		for ( P_Object pOb : * pvpObject )
		{
			PrmEfSpark prm;
			
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
			prm.m_G = VEC2 ( 0, 0.3f );

			pOb->SetRadian ( D3DX_PI_HALF + rad_i );
			pOb->SetValid ( false );

			m_vPrm.push_back ( prm );

			++ i;
		}
	}

	EfSpark::~EfSpark ()
	{
	}

	void EfSpark::Move ()
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

			//�o�E���h
			VEC2 pos = GetCalcPos ( i );
			if ( PLAYER_BASE_Y < pos.y )
			{
				m_vPrm[i].m_vel.y *= -0.8f;
				m_vPrm[i].m_vel.x *= 0.8f;
				SetPosMatrix ( i, prePosMatrix );
			}

			//��]
//			float rad = D3DX_2PI / SPARK_NUM;
//			float rad = atan2f ( m_sparkPos[i].y - prePos.y, m_sparkPos[i].x - prePos.x );
			float rad = atan2f ( m_vPrm[i].m_pos.y - prePos.y, m_vPrm[i].m_pos.x - prePos.x );
//			(*pvpMatrix)[i]->SetRadian ( D3DX_PI_HALF + rad * i );
			pOb->SetRadian ( D3DX_PI_HALF + rad );

			//�C���f�b�N�X
			++ i;
		}
		SetDispBase ( G_BASE_POS () );

		GrpEf::Move ();
	}

	void EfSpark::On ( VEC2 center )
	{
		//�����ʒu�Ə��������Z�b�g
		PVP_Object pvpObject = GetpvpObject ();
		UINT i = 0;
		for ( P_Object pOb : *pvpObject )
		{
			pOb->SetValid ( T );
			pOb->SetFadeOut ( 60 );
			m_vPrm[i].m_pos = VEC2 ( 0, 0 );
			m_vPrm[i].m_vel = m_vPrm[i].m_startVel;
			//�C���f�b�N�X
			++i;
		}

		SetRevised ( center );
//		SetWait ( 60 );
//		SetFadeOut ( 60 );
		SetValid ( true );
		GrpEf::On ();
	}
}
