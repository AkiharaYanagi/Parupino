//=================================================================================================
//
// DispDecision ソースファイル
//
//=================================================================================================


//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "stdafx.h"

#include "DispDecision.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	DispDecision::DispDecision ()
	{
		m_L_P1.AddTexture ( _T("DispDecision_L.png") );
		m_L_P1.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_X_P1 , DISP_DECISION_Y ) );
		GameTaskArray::AddTask ( & m_L_P1 );

		m_M_P1.AddTexture ( _T("DispDecision_M.png") );
		m_M_P1.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_X_P1 , DISP_DECISION_Y ) );
		GameTaskArray::AddTask ( & m_M_P1 );

		m_H_P1.AddTexture ( _T("DispDecision_H.png") );
		m_H_P1.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_X_P1 , DISP_DECISION_Y ) );
		GameTaskArray::AddTask ( & m_H_P1 );

		m_A_P1.AddTexture ( _T("DispDecision_A.png") );
		m_A_P1.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_X_P1 , DISP_DECISION_Y ) );
		GameTaskArray::AddTask ( & m_A_P1 );


		m_L_P2.AddTexture ( _T("DispDecision_L.png") );
		m_L_P2.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_X_P2 , DISP_DECISION_Y ) );
		GameTaskArray::AddTask ( & m_L_P2 );

		m_M_P2.AddTexture ( _T("DispDecision_M.png") );
		m_M_P2.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_X_P2 , DISP_DECISION_Y ) );
		GameTaskArray::AddTask ( & m_M_P2 );

		m_H_P2.AddTexture ( _T("DispDecision_H.png") );
		m_H_P2.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_X_P2 , DISP_DECISION_Y ) );
		GameTaskArray::AddTask ( & m_H_P2 );

		m_A_P2.AddTexture ( _T("DispDecision_A.png") );
		m_A_P2.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_X_P2 , DISP_DECISION_Y ) );
		GameTaskArray::AddTask ( & m_A_P2 );


		m_resultEqual.AddTexture ( _T("DispDecision_Equal.png") );
		m_resultEqual.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_RESULT_X , DISP_DECISION_RESULT_Y ) );
		GameTaskArray::AddTask ( & m_resultEqual );

		m_resultLeft.AddTexture ( _T("DispDecision_Left.png") );
		m_resultLeft.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_RESULT_X , DISP_DECISION_RESULT_Y ) );
		GameTaskArray::AddTask ( & m_resultLeft );

		m_resultRight.AddTexture ( _T("DispDecision_Right.png") );
		m_resultRight.GetpMatrix()->SetPos ( VEC2 ( DISP_DECISION_RESULT_X , DISP_DECISION_RESULT_Y ) );
		GameTaskArray::AddTask ( & m_resultRight );


		Clear ();
	}

	DispDecision::~DispDecision ()
	{
	}

	void DispDecision::Init ()
	{
		GameTaskArray::Init ();
	}

	void DispDecision::Move ()
	{
		GameTaskArray::Move ();
	}

	void DispDecision::Clear ()
	{
		ClearCategory ();
		ClearDecision ();
	}

	void DispDecision::ClearCategory ()
	{
		m_L_P1.SetValid ( false );
		m_M_P1.SetValid ( false );
		m_H_P1.SetValid ( false );
		m_A_P1.SetValid ( false );
		m_L_P2.SetValid ( false );
		m_M_P2.SetValid ( false );
		m_H_P2.SetValid ( false );
		m_A_P2.SetValid ( false );
	}

	void DispDecision::ClearDecision ()
	{
		m_resultEqual.SetValid ( false );
		m_resultLeft.SetValid ( false );
		m_resultRight.SetValid ( false );
	}

	void DispDecision::SetActionCategory ( Action::ACTION_CATEGORY ac1, Action::ACTION_CATEGORY ac2 )
	{
		ClearCategory ();

		switch ( ac1 )
		{
		case Action::ATTACK_L:
			m_L_P1.SetValid ( true );
			break;
		case Action::ATTACK_M:
			m_M_P1.SetValid ( true );
			break;
		case Action::ATTACK_H:
			m_H_P1.SetValid ( true );
			break;
		case Action::AVOID:
			m_A_P1.SetValid ( true );
			break;
		default:
			break;
		}

		switch ( ac2 )
		{
		case Action::ATTACK_L:
			m_L_P2.SetValid ( true );
			break;
		case Action::ATTACK_M:
			m_M_P2.SetValid ( true );
			break;
		case Action::ATTACK_H:
			m_H_P2.SetValid ( true );
			break;
		case Action::AVOID:
			m_A_P2.SetValid ( true );
			break;
		default:
			break;
		}
	}

	void DispDecision::SetDecision ( CLANG_DECISION_LR cd )
	{
		ClearDecision ();

		switch ( cd )
		{
		case CD_EQUAL:
			m_resultEqual.SetValid ( true );
			break;
		case CD_LEFT:
			m_resultLeft.SetValid ( true );
			break;
		case CD_RIGHT:
			m_resultRight.SetValid ( true );
			break;
		case CD_OFF:
			break;
		default:
			break;
		}
	}


}	//namespace GAME

