//=================================================================================================
//
//	Fighting �f��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "FtgDemo.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	P_GrpDemo FtgDemoState::SetGrpValue ( LPCTSTR txName )
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
	FTG_DM_GetReady::FTG_DM_GetReady ()
	{
		m_grpGetReady = SetGrpValue ( _T ( "Demo_GetReady.png" ) );

		m_grpGetReady->SetValid ( T );
		m_grpGetReady->Init ();
		m_grpGetReady->SetEnd ( 90 );
	}

	void FTG_DM_GetReady::Do ()
	{
		if ( ! m_grpGetReady->GetValid () )
		{
			m_prmFtgDemo->GetpMutualChara ()->Wait ( F );
			m_prmFtgDemo->GetpMutualChara ()->SetMain ();

			m_prmFtgDemo->GetpFtgDemoActor ()->Change_GetReady_To_Attack ();
		}
	}

	//-------------

	FTG_DM_Attack::FTG_DM_Attack ()
	{
		m_grpAttack = SetGrpValue ( _T ( "Demo_Attack.png" ) );
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
		m_GetReady = make_shared < FTG_DM_GetReady > ();
		m_Attack = make_shared < FTG_DM_Attack > ();
		m_Main = make_shared < FTG_DM_Main > ();
		m_Down = make_shared < FTG_DM_Down > ();
		m_Winner = make_shared < FTG_DM_Winner > ();

		mvp_FtgDemo.push_back ( m_GetReady );
		mvp_FtgDemo.push_back ( m_Attack );
		mvp_FtgDemo.push_back ( m_Main );
		mvp_FtgDemo.push_back ( m_Down );
		mvp_FtgDemo.push_back ( m_Winner );

		mp_FtgDemo = m_GetReady;


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

	void FtgDemoActor::Do ()
	{
		mp_FtgDemo->Do ();
	}

	void FtgDemoActor::Change_GetReady_To_Attack ()
	{
		m_Attack->Init ();
		mp_FtgDemo = m_Attack;
	}


}	//namespace GAME

