//=================================================================================================
//
//	EfPart ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfPart.h"

//-------------------------------------------------------------------------------------------------
// 定義
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
		//グラフィックオブジェクトを指定個数で初期化
		ResetObjectNum ( SPARK_MAX );

		//-----------------------------------------------------
		//角度初期化用ランダマイザ
		vector < UINT > v_rnd_ui;
		Rnd_0_N ( SPARK_MAX, v_rnd_ui );

		//-----------------------------------------------------

		UINT i = 0;
		for ( P_Object pOb : * GetpvpObject () )
		{
			pOb->SetValid ( F );

			PrmEfPart prm;
//			prm.m_startPos = VEC2 ( 100.f, -400.f );
			prm.m_angle = D3DX_2PI / SPARK_MAX * v_rnd_ui [ i ];
			float c = cosf ( prm.m_angle );
			float s = sinf ( prm.m_angle );
			int rndx = rand () % 20;
			int rndy = rand () % 20;
			prm.m_startVel = VEC2 ( (rndx + 1) * c,  (rndy + 1) * s );
			prm.m_G = VEC2( 0, 0.005f );

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
			mv_Prm [ i ].m_vel += -0.03f * mv_Prm [ i ].m_vel;	//減衰
			mv_Prm [ i ].m_pos += mv_Prm [ i ].m_vel;

			if ( mv_Prm [ i ].m_pos.y >= GROUND_Y )
			{
				pOb->SetValid ( F );
			}

			pOb->SetPos ( mv_Prm [ i ].m_pos + G_BASE_POS () );

			++ i;
		}

		//test 個数表示
		UINT T_count = 0;
		for ( P_Object pOb : * GetpvpObject () )
		{
			T_count += pOb->GetValid () ? 1 : 0;
		}
		DBGOUT_WND_F ( 6, _T ( "T_count = %d" ), T_count );


		//重なり判定後
		UINT i_flag = 0;
		PVP_Object pvpOb = GetpvpObject ();
		for ( PrmEfPart prm : mv_Prm )
		{
			if ( prm.m_flag )
			{
				( *pvpOb ) [ i_flag ]->SetValid ( F );
			}

			++ i;
		}


		GrpAcv::Move ();
	}

	void EfPart::On ( VEC2 center )
	{

		//有効フラグを調べ、非稼働インデックスを記録する
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

		//0からN-1の乱数
		vector < UINT > vecRnd;
		Rnd_0_N ( n, vecRnd );
		
		//稼働
		UINT na = ( n < SPARK_NUM ) ? n : SPARK_NUM;
		PVP_Object pvpOb = GetpvpObject ();
		for ( i = 0; i < na; ++ i )
		{
			UINT index = vecRnd [ i ];
			(*pvpOb) [ index ]->SetValid ( T );

			mv_Prm [ index ].m_pos = center + mv_Prm [ index ].m_startPos;
			mv_Prm [ index ].m_vel = mv_Prm [ index ].m_startVel;
		}
	}

	void EfPart::Rnd_0_N ( UINT N, vector < UINT > & vec )
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

	void EfPart::Draw ()
	{
		GrpAcv::Draw ();
	}


}
