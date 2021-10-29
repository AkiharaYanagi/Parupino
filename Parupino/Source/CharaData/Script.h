//=================================================================================================
//
//	Script wb_t@C
//		t[É·él
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// wb_t@CÌCN[h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Route.h"
#include "EffectGenerate.h"

//-------------------------------------------------------------------------------------------------
// é¾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================================
	//	XNvg		LÉ¨¯éANVÌPt[Ìl
	//		°t[
	//		°C[WID
	//		°æ\¦Êu
	//		°¬x
	//		°Á¬x
	//		°vZóÔ(±/ãü/ÁZ)
	//		°[][g
	//		°[]ÚGg
	//		°[]Ug
	//		°[]èg
	//		°[]Eg
	//		°Ul
	//		°[]GtFNg­¶
	//
	//================================================================

	//vZóÔ(CalcState)
	enum CLC_ST
	{
		CLC_MAINTAIN,	//±
		CLC_SUBSTITUDE,	//ãü
		CLC_ADD,		//ÁZ
	};

	//NX
	class Script
	{
		UINT	m_frame;		//Yt[
		UINT	m_imageIndex;	//C[WID

		VEC2	m_pos;			//æ\¦Êu
		VEC2	m_vel;			//¬x
		VEC2	m_acc;			//Á¬x

		CLC_ST	m_CalcState;	//vZóÔ

		PV_RECT	m_pvCRect;		//ÚGgXg
		PV_RECT	m_pvARect;		//UgXg
		PV_RECT	m_pvHRect;		//ègXg
		PV_RECT	m_pvORect;		//EgXg

		V_UINT		m_vRouteID;		//[gXg
		PVP_EfGnrt	m_pvpEfGnrt;	//EfWFl[gXg

		int		m_power;		//Ul
		UINT	m_blackOut;		//Ã]
		UINT	m_vibration;	//U®
		UINT	m_stop;			//â~

	public:
		Script ();
		Script ( const Script & rhs ) = delete;
		~Script ();

		void Make ();
		void Rele ();

		//Yt[
		void SetFrame ( UINT frame ) { m_frame = frame; }
		UINT GetFrame () const { return m_frame; }

		//C[WID
		void SetImageIndex ( UINT index ) { m_imageIndex = index; }
		UINT GetImageIndex () const { return m_imageIndex; }

		//æ\¦Êu
		void SetPos ( VEC2 pos ) { m_pos = pos; }
		VEC2 GetPos () const { return m_pos; }

		//¬x
		void SetVel ( VEC2 vel ) { m_vel = vel; }
		VEC2 GetVel () const { return m_vel; }

		//Á¬x
		void SetAcc ( VEC2 acc ) { m_acc = acc; }
		VEC2 GetAcc () const { return m_acc; }

		//vZóÔ
		void SetCalcState ( CLC_ST clcSt ) { m_CalcState = clcSt; }
		CLC_ST GetCalcState () const { return m_CalcState; }

		//[g
		void AddRouteID ( UINT i ) { m_vRouteID.push_back ( i ); }
		const V_UINT & GetvRouteID () const { return m_vRouteID; }

		//EfGnrtXg
		PVP_EfGnrt GetpvpEfGnrt () const { return m_pvpEfGnrt; }

		//EfGnrtXgÉÇÁ
		void AddpEfGnrt ( P_EfGnrt pEfGnrt ) { m_pvpEfGnrt->push_back ( pEfGnrt ); }

		//ÚGg, Ug, èg, Eg
		PV_RECT GetpvCRect () const { return m_pvCRect; }
		PV_RECT GetpvARect () const { return m_pvARect; }
		PV_RECT GetpvHRect () const { return m_pvHRect; }
		PV_RECT GetpvORect () const { return m_pvORect; }
		void AddCRect ( RECT crect ) { m_pvCRect->push_back ( crect ); }
		void AddARect ( RECT arect ) { m_pvARect->push_back ( arect ); }
		void AddHRect ( RECT hrect ) { m_pvHRect->push_back ( hrect ); }
		void AddORect ( RECT orect ) { m_pvORect->push_back ( orect ); }

		//Ul
		int GetPower () const { return m_power; }
		void SetPower ( int power ) { m_power = power; }

		//Ã]
		UINT GetBlackOut () const { return m_blackOut; }
		void SetBlackOut ( UINT blackout ) { m_blackOut = blackout; }

		//U®
		UINT GetVibration () const { return m_vibration; }
		void SetVibration ( UINT viberation ) { m_vibration = viberation; }

		//â~
		UINT GetStop () const { return m_stop; }
		void SetStop ( UINT stop ) { m_stop = stop; }
	};


	using P_Script = shared_ptr < Script >;
	using VP_Script = vector < P_Script >;
	using PVP_Script = shared_ptr < VP_Script >;


}	//namespace GAME


