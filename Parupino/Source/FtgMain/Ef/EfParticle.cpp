//=================================================================================================
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

		//-----------------------------------------------------
		//�p�x�������p�����_�}�C�U
		std::vector < UINT > v_rnd_ui;
		v_rnd_ui.reserve ( SPARK_NUM );
		for ( UINT i = 0; i < SPARK_NUM; ++ i )
		{
			v_rnd_ui.push_back ( i );
		}
		for ( UINT i = 0; i < SPARK_NUM; ++ i )
		{
			int j = rand () % (i + 1);
			UINT temp = v_rnd_ui [ i ];
			v_rnd_ui [ i ] = v_rnd_ui [ j ];
			v_rnd_ui [ j ] = temp;
		}
		//-----------------------------------------------------

		//�p�����[�^��������
		UINT i = 0;
		PVP_Object pvpOb = GetpvpObject ();
		for ( P_Object pOb : * GetpvpObject () )
		{
			PrmEfParticle prm;
			
			//�ʒu
			prm.m_pos.x = 0;
			prm.m_pos.y = 0;

			//�p�x
			float rad = D3DX_2PI / SPARK_NUM;
//			float rad_i = rad * i;
			float rad_i = rad * v_rnd_ui [ i ];
			prm.m_angle = rad_i;
			pOb->SetRadian ( D3DX_PI_HALF + rad_i );

			//cos((�ߎ�)��/2)�𐧌�
			float c = cosf ( rad_i );
			if ( D3DX_PI_HALF - 0.01 < rad_i && rad_i < D3DX_PI_HALF + 0.01 ) { c = 0; }

			//sin((�ߎ�)��)�𐧌�
			float s = sinf ( rad_i );
			if ( 3.14f < rad_i && rad_i < 3.15f ) { s = 0; }

			int rndx = rand () % 20;
			int rndy = rand () % 20;

			prm.m_startVel = VEC2 ( (rndx + 5.f) * c, (rndy + 5.f) * s );
			prm.m_vel.x = 0;
			prm.m_vel.y = 0;
			prm.m_G = VEC2 ( 0, 0.01f );

			pOb->SetValid ( false );
//			pOb->SetValid ( T );

			m_vPrm.push_back ( prm );

			++ i;
		}

		SetValid ( true );
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
//			VEC2 prePos = m_vPrm[i].m_pos;

			m_vPrm[i].m_vel += -0.03f * m_vPrm[i].m_vel;	//����
			m_vPrm[i].m_vel += m_vPrm[i].m_G;
			m_vPrm[i].m_pos += m_vPrm[i].m_vel;

			if ( m_vPrm [ i ].m_pos.y >= GROUND_Y )
			{
				pOb->SetColor ( 0xff00ff00 );
				pOb->SetValid ( F );
				m_vPrm [ i ].m_flag = F;
			}

			//��ʒu + �␳�ʒu + �O���␳�ʒu + �ʈʒu
//			VEC2 prePosMatrix = GetCalcPos ( i );

			SetPosMatrix ( i, m_vPrm[i].m_pos );

			//�C���f�b�N�X
			++ i;
		}

		for ( UINT i = 0; i < SPARK_NUM; ++ i )
		{
//			( *pvpObject ) [ i ]->SetValid ( m_vPrm [ i ].m_flag );
		}
		
		//���݃L�����N�^�ʒu�ɂ���ʕ␳�ʒu
		SetDispBase ( G_BASE_POS () );

		GrpEf::Move ();
	}

	void EfParticle::On ( VEC2 center )
	{
		//TRACE_F ( _T("EfParticle::On\n") );

		//�����ʒu�Ə��������Z�b�g
		UINT i = 0;
		UINT count = 0;
		const UINT COUNT_MAX = 30;

		PVP_Object pvpObject = GetpvpObject ();
		for ( P_Object pOb : *pvpObject )
		{
			//��ғ���Ԃ̂��̂��ĉғ�
//			if ( ! pOb->GetValid () )
			if ( ! m_vPrm [ i ].m_flag )
			{
				pOb->SetValid ( T );
				m_vPrm [ i ].m_flag = T;
				m_vPrm [ i ].m_pos = center;
				m_vPrm [ i ].m_startPos = center;
				m_vPrm[i].m_vel = m_vPrm[i].m_startVel;

				//�ғ��C���f�b�N�X
				if ( ++ count >= COUNT_MAX ) { break; }
			}

			//�S�̃C���f�b�N�X
			++i;
		}

		GrpEf::On ();
	}

	void EfParticle::Draw ()
	{
		PVP_Object pvpObject = GetpvpObject ();
		GrpEf::Draw ();
	}


}
