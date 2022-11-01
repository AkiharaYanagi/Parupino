//=================================================================================================
//
//	Script ヘッダファイル
//		毎フレームに処理する値
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Route.h"
#include "EffectGenerate.h"
#include "ScriptParam_Battle.h"
#include "ScriptParam_Staging.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================================
	//	◆スクリプト		キャラにおけるアクションの１フレームの値
	//		┣フレーム数
	//		┣イメージID
	//		┣画像表示位置
	//		┣計算状態(持続/代入/加算)
	//		┣[]ルート
	//		┣[]接触枠
	//		┣[]攻撃枠
	//		┣[]当り枠
	//		┣[]相殺枠
	//		┣[]エフェクト発生
	//
	//================================================================

	//計算状態(CalcState)
	enum CLC_ST
	{
		CLC_MAINTAIN,	//持続
		CLC_SUBSTITUDE,	//代入
		CLC_ADD,		//加算
	};

	//クラス
	class Script
	{
		UINT	m_frame;		//自身の該当フレーム数
		UINT	m_imageIndex;	//イメージID

		VEC2	m_pos;			//画像表示位置
		CLC_ST	m_CalcState;	//計算状態

		PV_RECT	m_pvCRect;		//接触枠リスト
		PV_RECT	m_pvARect;		//攻撃枠リスト
		PV_RECT	m_pvHRect;		//当り枠リスト
		PV_RECT	m_pvORect;		//相殺枠リスト

		V_UINT		m_vRouteID;		//ルートリスト
		PVP_EfGnrt	m_pvpEfGnrt;	//Efジェネレートリスト

	public:
		Script ();
		Script ( const Script & rhs ) = delete;
		~Script ();

		void Make ();
		void Rele ();

		//該当フレーム数
		void SetFrame ( UINT frame ) { m_frame = frame; }
		UINT GetFrame () const { return m_frame; }

		//イメージID
		void SetImageIndex ( UINT index ) { m_imageIndex = index; }
		UINT GetImageIndex () const { return m_imageIndex; }

		//画像表示位置
		void SetPos ( VEC2 pos ) { m_pos = pos; }
		VEC2 GetPos () const { return m_pos; }

#if 0
		//速度
		void SetVel ( VEC2 vel ) { m_vel = vel; }
		VEC2 GetVel () const { return m_vel; }

		//加速度
		void SetAcc ( VEC2 acc ) { m_acc = acc; }
		VEC2 GetAcc () const { return m_acc; }
#endif // 0

		//計算状態
		void SetCalcState ( CLC_ST clcSt ) { m_CalcState = clcSt; }
		CLC_ST GetCalcState () const { return m_CalcState; }

		//ルート
		void AddRouteID ( UINT i ) { m_vRouteID.push_back ( i ); }
		const V_UINT & GetvRouteID () const { return m_vRouteID; }

		//EfGnrtリスト
		PVP_EfGnrt GetpvpEfGnrt () const { return m_pvpEfGnrt; }

		//EfGnrtリストに追加
		void AddpEfGnrt ( P_EfGnrt pEfGnrt ) { m_pvpEfGnrt->push_back ( pEfGnrt ); }

		//接触枠, 攻撃枠, 当り枠, 相殺枠
		PV_RECT GetpvCRect () const { return m_pvCRect; }
		PV_RECT GetpvARect () const { return m_pvARect; }
		PV_RECT GetpvHRect () const { return m_pvHRect; }
		PV_RECT GetpvORect () const { return m_pvORect; }
		void AddCRect ( RECT crect ) { m_pvCRect->push_back ( crect ); }
		void AddARect ( RECT arect ) { m_pvARect->push_back ( arect ); }
		void AddHRect ( RECT hrect ) { m_pvHRect->push_back ( hrect ); }
		void AddORect ( RECT orect ) { m_pvORect->push_back ( orect ); }

		//値
		ScriptParam_Battle		m_prmBattle;	//戦闘パラメータ
		ScriptParam_Staging		m_prmStaging;	//演出パラメータ
	};


	using P_Script = shared_ptr < Script >;
	using VP_Script = vector < P_Script >;
	using PVP_Script = shared_ptr < VP_Script >;


}	//namespace GAME


