//=================================================================================================
//
//	ExeChara アクタ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara_Actor.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	ExeChara_Actor::ExeChara_Actor ()
	{
		//ステート
		m_Start = make_shared < CHST_Start > ();
		m_Greeting = make_shared < CHST_Greeting > ();
		m_GetReady = make_shared < CHST_GetReady > ();
		m_Main = make_shared < CHST_Main > ();
		m_EndWait = make_shared < CHST_EndWait > ();
		m_Down = make_shared < CHST_Down > ();
		m_DownWait = make_shared < CHST_DownWait > ();
		m_WinWait = make_shared < CHST_WinWait > ();
		m_Win = make_shared < CHST_Win > ();
		m_WinEnd = make_shared < CHST_WinEnd > ();

		//ステート監理
		mvp_state.push_back ( m_Start );
		mvp_state.push_back ( m_Greeting );
		mvp_state.push_back ( m_GetReady );
		mvp_state.push_back ( m_Main );
		mvp_state.push_back ( m_EndWait );
		mvp_state.push_back ( m_Down );
		mvp_state.push_back ( m_DownWait );
		mvp_state.push_back ( m_WinWait );
		mvp_state.push_back ( m_Win );
		mvp_state.push_back ( m_WinEnd );

		//初期ステート
		mp_state = m_Start;
//		mp_state = m_Main;

		//パラメータ
		mp_param = make_shared < ExeChara_Param > ();
		for ( P_ExeChara_State p : mvp_state )
		{
			p->SetpPrm ( mp_param );
		}
	}

	void ExeChara_Actor::Init ()
	{
//		mp_state = m_Start;
		mp_state = m_Main;
	}


	//状態変更
	void ExeChara_Actor::StartGreeting ()
	{
		mp_state = m_Greeting;
		mp_state->Start ();
	}

	void ExeChara_Actor::StartGetReady ()
	{
		mp_state = m_GetReady;
		mp_state->Start ();
	}

	void ExeChara_Actor::StartFighting ()
	{
		mp_state = m_Main;
		mp_state->Start ();
	}

	//==========================================================
	//MutualCharaから呼ばれる主な関数
	//==========================================================
	void ExeChara_Actor::PreScriptMove ()
	{
		mp_state->PreScriptMove ();
	}

	void ExeChara_Actor::RectMove ()
	{
		mp_state->RectMove ();
	}

	void ExeChara_Actor::PostScriptMove ()
	{
		mp_state->PostScriptMove ();
	}



}	//namespace GAME

