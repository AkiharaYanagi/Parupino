//=================================================================================================
//
//	TitleEf ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TitleEf.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	TitleEf::TitleEf ()
//		: m_timer ( 0 ), m_timer0 ( 15 )
	{
		m_ef = make_shared < GrpDemo > ();
		m_ef->AddTexture ( _T ( "title_ef.png" ) );
		m_ef->SetZ ( Z_BG );
		m_ef->SetPos ( VEC2 ( (1280 - 2048) * 0.5f, (960 - 1024) * 0.5f ) );
		m_ef->SetScalingCenter ( VEC2 ( 1024, 512 ) );
		m_ef->SetStartScaling ( VEC2 ( 0.5f, 0.5f ) );
		m_ef->SetTargetScaling ( VEC2 ( 10.f, 10.f ) );
		m_ef->SetAcc ( VEC2 ( 0.01f, 0.01f ) );
		m_ef->SetSecondVel ( VEC2 ( 0.1f, 0.1f ) );

#if 0
		m_ef0 = make_shared < GrpDemo > ();
		m_ef0->AddTexture ( _T ( "title_ef.png" ) );
		m_ef0->SetZ ( Z_BG );
		m_ef0->SetPos ( VEC2 ( (1280 - 2048) * 0.5f, (960 - 1024) * 0.5f ) );
		m_ef0->SetScalingCenter ( VEC2 ( 1024, 512 ) );
		m_ef0->SetStartScaling ( VEC2 ( 0.5f, 0.5f ) );
		m_ef0->SetTargetScaling ( VEC2 ( 10.f, 10.f ) );
		m_ef0->SetAcc ( VEC2 ( 0.01f, 0.01f ) );
		m_ef0->SetSecondVel ( VEC2 ( 0.1f, 0.1f ) );
#endif // 0

		m_another = make_shared < GrpAcv > ();
		m_another->AddTexture ( _T ( "titleAnother.png" ) );
		m_another->SetZ ( Z_BG );
		m_another->SetPos ( VEC2 ( (1280 - 2048) * 0.5f, (960 - 2048) * 0.5f ) );
		m_another->SetRotationCenter ( VEC2 ( 1024.f, 1024.f ) );
		//		m_another->AddTexture ( _T ( "title_bg_cloud.png" ) );
		m_radian = 0;
		m_rv = D3DX_2PI / (360 * 30);

		Init ();
	}

	TitleEf::~TitleEf ()
	{
	}

	void TitleEf::Load ()
	{
		GRPLST_INSERT_MAIN ( m_ef );
//		GRPLST_INSERT_MAIN ( m_ef0 );
		GRPLST_INSERT_MAIN ( m_another );
	}

	void TitleEf::Init ()
	{
		m_ef->Init ();
		m_ef->SetVel ( VEC2 ( 0.1f, 0.1f ) );
//		m_ef0->Init ();
//		m_ef0->SetVel ( VEC2 ( 5.f, 5.f ) );
	}

	void TitleEf::Move ()
	{
#if 0
		if ( ++ m_timer > 30 )
		{
			m_ef->Init ();
			m_ef->SetVel ( VEC2 ( 0.1f, 0.1f ) );
			m_timer = 0;
		}
		if ( ++ m_timer0 > 30 )
		{
			m_ef0->Init ();
			m_ef0->SetVel ( VEC2 ( 5.f, 5.f ) );
			m_timer0 = 0;
		}
#endif // 0
		m_radian += m_rv;
		if ( m_radian > D3DX_2PI ) { m_radian -= D3DX_2PI; }
		m_another->SetRadian ( m_radian );
}


}	//namespace GAME

