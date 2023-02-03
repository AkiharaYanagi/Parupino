//=================================================================================================
//
//	Fighting �f��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "FtgDemo.h"
#include <iomanip>


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	P_GrpDemo FtgDemoState::MakeGrpValue ( LPCTSTR txName )
	{
		P_GrpDemo pGrp = make_shared < GrpDemo > ();
		pGrp->AddTexture ( txName );
		GRPLST_INSERT ( pGrp );

		pGrp->SetPos ( VEC2 ( 128, 400 ) );
		pGrp->SetScalingCenter ( VEC2 ( 512, 128 ) );
		pGrp->SetStartScaling ( VEC2 ( 1.3f, 1.3f ) );
		pGrp->SetSecondVel ( VEC2 ( -0.001f, -0.001f ) );
		pGrp->SetZ ( Z_SYS );
		pGrp->SetValid ( F );

		return pGrp;
	}


	//=====================================================
	FTG_DM_Greeting::FTG_DM_Greeting ()
	{
		m_timer = make_shared < Timer > ();
	}

	void FTG_DM_Greeting::Init ()
	{
		m_timer->SetTargetTime ( 90 );
		m_timer->Start ();
	}

	void FTG_DM_Greeting::Do ()
	{
		m_timer->Move ();
		if ( m_timer->IsLast () )
		{
			m_prmFtgDemo->GetpFtgDemoActor ()->Change_Greeting_To_GetReady ();
		}
	}

	//-------------

	FTG_DM_GetReady::FTG_DM_GetReady ()
	{
		m_grpGetReady = MakeGrpValue ( _T ( "Demo_GetReady.png" ) );


		m_grpClock = make_shared < GrpAcv > ();
		m_grpClock->SetPos ( VEC2 ( 640 - 256 , 300 ) );
		m_grpClock->SetValid ( F );
		m_grpClock->SetZ( Z_EFF );
		GRPLST_INSERT ( m_grpClock );

		tostringstream toss;
		tstring filename_base = _T ( "clock\\clock_" );
		tstring ext = _T ( ".png" );

		for ( UINT i = 1; i < 61; ++ i )
		{
			toss << filename_base << std::setw ( 2 ) << std::setfill ( _T('0') ) << i << ext;
			m_grpClock->AddTexture ( toss.str () );
			toss.str( _T("") );
		}

		m_timer = make_shared < Timer > ();
	}

	void FTG_DM_GetReady::Init ()
	{
		m_grpGetReady->SetValid ( T );
		m_grpGetReady->Init ();
		m_grpGetReady->SetEnd ( 90 );

		m_grpClock->SetValid ( T );
		m_timer->Start ();
	}

	void FTG_DM_GetReady::Final ()
	{
		m_grpClock->SetValid ( F );
	}

	void FTG_DM_GetReady::Do ()
	{
		m_timer->Move ();
		UINT t = m_timer->GetTime ();
		if ( 60 > t )
		{
			m_grpClock->SetIndexTexture ( t );
		}

		if ( ! m_grpGetReady->GetValid () )
		{
			GetpMutualChara ()->SetMain ();

			m_prmFtgDemo->GetpFtgDemoActor ()->Change_GetReady_To_Attack ();
		}
	}

	//-------------

	FTG_DM_Attack::FTG_DM_Attack ()
	{
		m_grpAttack = MakeGrpValue ( _T ( "Demo_Attack.png" ) );
	}

	void FTG_DM_Attack::Init ()
	{
		m_grpAttack->SetValid ( T );
		m_grpAttack->Init ();
		m_grpAttack->SetEnd ( 90 );
	}

	void FTG_DM_Attack::Do ()
	{
		m_grpAttack->Move ();
	}

	//-------------

	void FTG_DM_Main::Do ()
	{
	}

	void FTG_DM_Down::Do ()
	{
	}

	void FTG_DM_Winner::Do ()
	{
	}

	//=====================================================
	FtgDemoActor::FtgDemoActor ()
	{
		//�X�e�[�g
		m_Greeting = make_shared < FTG_DM_Greeting > ();
		m_GetReady = make_shared < FTG_DM_GetReady > ();
		m_Attack = make_shared < FTG_DM_Attack > ();
		m_Main = make_shared < FTG_DM_Main > ();
		m_Down = make_shared < FTG_DM_Down > ();
		m_Winner = make_shared < FTG_DM_Winner > ();

		mvp_FtgDemo.push_back ( m_Greeting );
		mvp_FtgDemo.push_back ( m_GetReady );
		mvp_FtgDemo.push_back ( m_Attack );
		mvp_FtgDemo.push_back ( m_Main );
		mvp_FtgDemo.push_back ( m_Down );
		mvp_FtgDemo.push_back ( m_Winner );

		//�����X�e�[�g
		mp_FtgDemo = m_Greeting;


		//�p�����[�^
		mp_Param = make_shared < FtgDemoParam > ();
		for ( P_FtgDemo p : mvp_FtgDemo )
		{
			p->SetpPrm ( mp_Param );
		}
	}

	void FtgDemoActor::Load ()
	{
		mp_Param->SetpFtgDemoActor ( shared_from_this () );
	}

	void FtgDemoActor::StartGreeting ()
	{
//		m_mutualChara_Demo->SetMain ();
//		m_mutualChara->SetReady ();
//		m_mutualChara->Wait ( true );
		GetpMutualChara ()->StartGreeting ();
		m_Greeting->Init ();
	}

	void FtgDemoActor::Do ()
	{
		mp_FtgDemo->Do ();
	}

	void FtgDemoActor::Change_Greeting_To_GetReady ()
	{
		m_GetReady->Init ();
		mp_FtgDemo = m_GetReady;
	}

	void FtgDemoActor::Change_GetReady_To_Attack ()
	{
		m_GetReady->Final ();
		m_Attack->Init ();
		mp_FtgDemo = m_Attack;
	}


}	//namespace GAME

