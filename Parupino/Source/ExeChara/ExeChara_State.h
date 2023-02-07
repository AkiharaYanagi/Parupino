//=================================================================================================
//
//	ExeChara ステート
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	//前方宣言	(循環参照なので weak_ptr )
	class ExeChara_Actor;	using WP_ExeChara_Actor = weak_ptr < ExeChara_Actor >;
	class ExeChara;	using WP_ExeChara = weak_ptr < ExeChara >;

	//Param
	class ExeChara_Param
	{
		WP_ExeChara_Actor	mwp_ExeChara_Actor;
		WP_ExeChara			mwp_ExeChara;

	public:
		void SetwpExeChara_Actor ( WP_ExeChara_Actor p ) { mwp_ExeChara_Actor = p; }
		WP_ExeChara_Actor GetwpExeChara_Actor () const { return mwp_ExeChara_Actor; }

		void SetwpExeChara ( WP_ExeChara p ) { mwp_ExeChara = p; }
		WP_ExeChara GetwpExeChara () const { return mwp_ExeChara; }
	};
	using P_ExeChara_Param = shared_ptr < ExeChara_Param >;


	//=====================================================
	//State
	class ExeChara_State
	{
	protected:
		P_ExeChara_Param	mp_PrmExeChara;
	public:
		ExeChara_State () {}
		ExeChara_State ( const ExeChara_State & rhs ) = delete;
		~ExeChara_State () {}

		virtual void Do () {}
		virtual void PreScriptMove () {}
		virtual void RectMove () {}
		virtual void PostScriptMove () {}

		void SetpPrm ( P_ExeChara_Param p ) { mp_PrmExeChara = p; }

		WP_ExeChara GetwpExeChara () const { return mp_PrmExeChara->GetwpExeChara (); }
	};
	using P_ExeChara_State = shared_ptr < ExeChara_State >;
	using VP_ExeChara_State = vector < P_ExeChara_State >;

	//=====================================================
	//State_Derivered

	class CHST_Start : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void RectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_Start = shared_ptr < CHST_Start >;
	//------------------------------------------------


	class CHST_Greeting : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void RectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_Greeting = shared_ptr < CHST_Greeting >;
	//------------------------------------------------

	class CHST_GetReady : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void RectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_GetReady = shared_ptr < CHST_GetReady >;
	//------------------------------------------------

	class CHST_Main : public ExeChara_State
	{
	public:
		void PreScriptMove ();
		void RectMove ();
		void PostScriptMove ();
	};
	using P_CHST_Main = shared_ptr < CHST_Main >;
	//------------------------------------------------

	class CHST_EndWait : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void RectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_EndWait = shared_ptr < CHST_EndWait >;
	//------------------------------------------------

	class CHST_Down : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void RectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_Down = shared_ptr < CHST_Down >;
	//------------------------------------------------

	class CHST_DownWait : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void ScriptRectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_DownWait = shared_ptr < CHST_DownWait >;
	//------------------------------------------------

	class CHST_WinWait : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void RectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_WinWait = shared_ptr < CHST_WinWait >;
	//------------------------------------------------

	class CHST_Win : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void RectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_Win = shared_ptr < CHST_Win >;
	//------------------------------------------------

	class CHST_WinEnd : public ExeChara_State
	{
	public:
		void PreScriptMove () {}
		void RectMove () {}
		void PostScriptMove () {}
	};
	using P_CHST_WinEnd = shared_ptr < CHST_WinEnd >;
	//------------------------------------------------


	//=====================================================


}	//namespace GAME

