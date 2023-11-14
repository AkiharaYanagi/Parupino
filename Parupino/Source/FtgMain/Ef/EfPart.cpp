//=================================================================================================
//
//	EfPart �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "EfPart.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfPart::EfPart ()
	{
		AddTexture ( _T ( "Ef_Particle.png" ) );
		SetZ ( Z_EFF );
		SetValid ( T );

		mv_Rnd.resize ( SPARK_MAX );
		for ( UINT i = 0; i < SPARK_MAX; ++ i )
		{
			mv_Rnd [ i ] = 0;
		}

		//-----------------------------------------------------
		//�O���t�B�b�N�I�u�W�F�N�g���w����ŏ�����
		ResetObjectNum ( SPARK_MAX );

		//-----------------------------------------------------
		//�p�x�������p�����_�}�C�U
		std::vector < UINT > v_rnd_ui;
		Rnd_0_N ( SPARK_MAX, v_rnd_ui );

		//-----------------------------------------------------

		UINT i = 0;
		for ( P_Object pOb : * GetpvpObject () )
		{
			pOb->SetValid ( F );

			PrmEfPart prm;
			prm.m_pOb = pOb;
			prm.m_angle = D3DX_2PI / SPARK_MAX * v_rnd_ui [ i ];
			float c = cosf ( prm.m_angle );
			float s = sinf ( prm.m_angle );
			int rndx = rand () % 20;
			int rndy = rand () % 20;
			prm.m_startVel = VEC2 ( (rndx + 1) * c,  (rndy + 1) * s );
			prm.m_G = VEC2( 0, 0.05f );

			mv_Prm.push_back ( prm );
			++ i;
		}
	}

	EfPart::~EfPart ()
	{
	}

	void EfPart::Move ()
	{
#if 0
		//SetPos ( VEC2 ( GAME_WINDOW_WIDTH * 0.5f, GAME_WINDOW_HEIGHT * 0.5 ) );
		//SetPos ( 0,0 ) );
		VEC2 pos = GetRevised ();
		DBGOUT_WND_F ( 3, _T ( "y = %d" ), pos.y );

		if ( pos.y >= GROUND_Y )
		{
			SetColor ( 0xff8080ff );
			SetRevised ( VEC2 ( pos.x, pos.y - 500 ) );
			SetValid ( F );
		}
		else
		{
			SetRevised ( VEC2 ( pos.x, pos.y + 5 ) );
		}
#endif // 0

		UINT i = 0;
		for ( P_Object pOb : * GetpvpObject () )
		{
//			if ( ! pOb->GetValid () ) { continue; }

			mv_Prm [ i ].m_vel += mv_Prm [ i ].m_G;
			mv_Prm [ i ].m_vel += -0.03f * mv_Prm [ i ].m_vel;	//����
			mv_Prm [ i ].m_pos += mv_Prm [ i ].m_vel;

			//���n����
			if ( mv_Prm [ i ].m_pos.y >= GROUND_Y )
			{
				pOb->SetValid ( F );
			}

			//��ʈʒu�␳
			pOb->SetPos ( mv_Prm [ i ].m_pos + G_BASE_POS () );

			//�J�E���g
			if ( 0 != mv_Prm [ i ].m_count ) { -- mv_Prm [ i ].m_count; }

			++ i;
		}

		//test ���\��
		UINT T_count = 0;
		for ( P_Object pOb : * GetpvpObject () )
		{
			T_count += pOb->GetValid () ? 1 : 0;
		}
//		DBGOUT_WND_F ( 6, _T ( "T_count = %d" ), T_count );


		//�d�Ȃ蔻���
		PVP_Object pvpOb = GetpvpObject ();
		for ( PrmEfPart prm : mv_Prm )
		{
			if ( prm.m_gotten )
			{
				prm.m_pOb->SetValid ( F );
				prm.m_gotten = F;
			}
		}


		GrpAcv::Move ();
	}

	void EfPart::On ( VEC2 center )
	{

		//�L���t���O�𒲂ׁA��ғ��C���f�b�N�X���L�^����
		UINT i = 0;
		UINT n = 0;
		for ( P_Object pOb : * GetpvpObject () )
		{
			if ( ! pOb->GetValid () )
			{
				mv_Rnd [ n ++ ] = i;
			}
			++ i;
		}

		//0����N-1�̗���
		std::vector < UINT > vecRnd;
		Rnd_0_N ( n, vecRnd );
		
		//�ғ��J�n
		UINT na = ( n < SPARK_NUM ) ? n : SPARK_NUM;
		PVP_Object pvpOb = GetpvpObject ();
		for ( i = 0; i < na; ++ i )
		{
			UINT index = vecRnd [ i ];
			(*pvpOb) [ index ]->SetValid ( T );

			mv_Prm [ index ].m_pos = center + mv_Prm [ index ].m_startPos;
			mv_Prm [ index ].m_vel = mv_Prm [ index ].m_startVel;

			mv_Prm [ index ].m_count = SPARK_INIT;
		}
	}

	void EfPart::Rnd_0_N ( UINT N, std::vector < UINT > & vec )
	{
		vec.clear ();
		vec.resize ( N );

		for ( UINT i = 0; i < N; ++ i )
		{
			vec [ i ] = i;
		}
		for ( UINT i = 0; i < N; ++ i )
		{
			int j = rand () % ( i + 1 );
			UINT temp = vec [ i ];
			vec [ i ] = vec [ j ];
			vec [ j ] = temp;
		}
	}

	//�d�Ȃ蔻��
	//->ExeChara���ōs��
	UINT EfPart::Collision ( PV_RECT pv_rect )
	{
		UINT ret = 0;
		//�Ώۂ̃R���W�������N�g���擾

		for ( PrmEfPart prm : mv_Prm )
		{
			if ( 0 != prm.m_count ) { continue; }

			for ( RECT rect : *pv_rect )
			{
				if ( OverlapPoint ( prm.m_pos, rect ) )
				{
					prm.m_gotten = T;
					++ ret;
				}
			}
		}
		
		//1p2p�����ɏd�Ȃ��Ă���ꍇ�A���҂ɔ��肠��
		
		//�����Ȃ��Ă���I�u�W�F�N�g���ғ��ɂ���

		//ExeChara�ɂ͏d�Ȃ����Ԃ�
		return ret;
	}
	
}
