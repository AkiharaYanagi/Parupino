//=================================================================================================
//
//	Fighting デモ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "FtgConst.h"	
#include "MutualChara.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	class FtgDemoActor; using P_FtgDemoActor = shared_ptr < FtgDemoActor >;

	//param
	class FtgDemoParam
	{
		P_MutualChara		m_mutualChara;
		P_FtgDemoActor		m_ftgDemoActor;

	public:
		
		void SetpMutualChara ( P_MutualChara p ) { m_mutualChara = p; }
		P_MutualChara GetpMutualChara () const { return m_mutualChara; }

		void SetpFtgDemoActor ( P_FtgDemoActor p ) { m_ftgDemoActor = p; }
		P_FtgDemoActor GetpFtgDemoActor () const { return m_ftgDemoActor; }
	};
	using P_PRM_FTG_DEMO = shared_ptr < FtgDemoParam >;

	//=====================================================
	//State
	class FtgDemoState
	{
	protected:
		P_PRM_FTG_DEMO		m_prmFtgDemo;
	public:
		FtgDemoState () {}
		FtgDemoState ( const FtgDemoState & rhs ) = delete;
		~FtgDemoState () {}

		virtual void Do () {}

		void SetpPrm ( P_PRM_FTG_DEMO p ) { m_prmFtgDemo = p; }

		P_GrpDemo SetGrpValue ( LPCTSTR txName );
	};
	using P_FtgDemo = shared_ptr < FtgDemoState >;

	//=====================================================

	//State_Derivered
	//------------------------------------------------

	class FTG_DM_GetReady : public FtgDemoState
	{
		P_GrpDemo		m_grpGetReady;
	public:
		FTG_DM_GetReady ();
		FTG_DM_GetReady ( const FTG_DM_GetReady & rhs ) = delete;
		~FTG_DM_GetReady () {}
		void Do ();
	};
	using P_FTG_DM_GetReady = shared_ptr < FTG_DM_GetReady >;


	//------------------------------------------------
	class FTG_DM_Attack : public FtgDemoState
	{
		P_GrpDemo		m_grpAttack;
	public:
		FTG_DM_Attack ();
		FTG_DM_Attack ( const FTG_DM_Attack & rhs ) = delete;
		~FTG_DM_Attack () {}
		void Init ();
		void Do ();
	};
	using P_FTG_DM_Attack = shared_ptr < FTG_DM_Attack >;


	//------------------------------------------------
	class FTG_DM_Main : public FtgDemoState
	{
	public:
		void Do ();
	};
	using P_FTG_DM_Main = shared_ptr < FTG_DM_Main >;


	//------------------------------------------------
	class FTG_DM_Down : public FtgDemoState
	{
	public:
		void Do ();
	};
	using P_FTG_DM_Down = shared_ptr < FTG_DM_Down >;


	//------------------------------------------------
	class FTG_DM_Winner : public FtgDemoState
	{
	public:
		void Do ();
	};
	using P_FTG_DM_Winner = shared_ptr < FTG_DM_Winner >;


	//=====================================================

	using VP_FtgDemo = vector < P_FtgDemo >;

	//Actor
	class FtgDemoActor : public enable_shared_from_this < FtgDemoActor >
	{
		//ステート
		P_FTG_DM_GetReady	m_GetReady;
		P_FTG_DM_Attack		m_Attack;
		P_FTG_DM_Main		m_Main;
		P_FTG_DM_Down		m_Down;
		P_FTG_DM_Winner		m_Winner;

		//ステート監理
		VP_FtgDemo			mvp_FtgDemo;

		//現在ステート
		P_FtgDemo			mp_FtgDemo;

		//共通パラメータ
		P_PRM_FTG_DEMO		mp_Param;

	public:
		FtgDemoActor ();

		void Load ();
		void Do ();

		void SetpMutualChara ( P_MutualChara p ) { mp_Param->SetpMutualChara ( p ); }
		void Change_GetReady_To_Attack ();
	};


}	//namespace GAME


