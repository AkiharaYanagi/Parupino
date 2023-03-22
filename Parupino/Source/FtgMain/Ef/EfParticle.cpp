////=================================================================================================
//
//	EfParticle ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfParticle.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//初速は方向・速度ともにランダム
	//一定の減衰でその場に揺れながら微速落下

	EfParticle::EfParticle ()
	{
		AddTexture ( _T ( "Ef_Particle.png" ) );

		//グラフィックオブジェクトを初期化
		ResetObjectNum ( SPARK_NUM );

		//パラメータを初期化
		PVP_Object pvpObject = GetpvpObject ();
		UINT i = 0;
		for ( P_Object pOb : * pvpObject )
		{
			PrmEfParticle prm;
			
			//位置
			prm.m_pos.x = 0;
			prm.m_pos.y = 0;

			//角度
			float rad = D3DX_2PI / SPARK_NUM;
			float rad_i = rad * i;
			prm.m_angle = rad_i;

			//cos((近似)π/2)を制御
			float c = cosf ( rad_i );
			if ( D3DX_PI_HALF - 0.01 < rad_i && rad_i < D3DX_PI_HALF + 0.01 ) { c = 0; }

			//sin((近似)π)を制御
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

			//位置計算
			VEC2 prePos = m_vPrm[i].m_pos;
			m_vPrm[i].m_vel += -0.03f * m_vPrm[i].m_vel;	//減衰
			m_vPrm[i].m_vel += m_vPrm[i].m_G;
			m_vPrm[i].m_pos += m_vPrm[i].m_vel;

			//基準位置 + 補正位置 + 外部補正位置 + 個別位置
			VEC2 prePosMatrix = GetCalcPos ( i );
			SetPosMatrix ( i, m_vPrm[i].m_pos );

			//インデックス
			++ i;
		}

		GrpEf::Move ();
	}

	void EfParticle::On ( VEC2 center )
	{
		//初期位置と初速をリセット
		PVP_Object pvpObject = GetpvpObject ();
		UINT i = 0;
		for ( P_Object pOb : *pvpObject )
		{
			pOb->SetValid ( T );
			m_vPrm[i].m_pos = VEC2 ( 0, 0 );
			m_vPrm[i].m_vel = m_vPrm[i].m_startVel;
			//インデックス
			++i;
		}

		SetpDispBase ( G_BASE_POS () );
		SetPos ( center );
		SetValid ( true );
		GrpEf::On ();
	}
}
