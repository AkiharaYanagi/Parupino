//=================================================================================================
//
//	デシジョン(判定)
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../ExeChara/ExeChara.h"
#include "Ef/EfClang.h"
#include "Ef/EfSpark.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Decision
	{
		//キャラエグゼ
		P_ExeChara		m_pExeChara1p;
		P_ExeChara		m_pExeChara2p;

		//共通エフェクト
		P_EfClang		m_efClang;
		P_EfSpark		m_efSpark;

		//ヒットストップ
		P_Timer	m_tmrHitstop;

		//---------------------------------
		//判定フラグ
		bool		m_bOffsetChara;		//キャラ同士相殺
		bool		m_Efhit1P;		//エフェクトのヒットチェック
		bool		m_Efhit2P;		//エフェクトのヒットチェック
		bool		m_hit1P;		//本体ヒットフラグ
		bool		m_hit2P;		//本体ヒットフラグ




	public:
		Decision ();
		Decision ( const Decision & rhs ) = delete;
		~Decision ();

		void SetpChara (P_ExeChara pExeChara1p, P_ExeChara pExeChara2p);
		void SetpCommonEf (P_EfClang pefClang, P_EfSpark efSpark);
		void SetpHitStop (P_Timer pHitstop);

		void Do ();


	private:
		//------------------------------------------------------
		//	内部関数
		//------------------------------------------------------
		//ダッシュ関連判定
		bool DashDecision ( P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center );

		//攻撃枠 同士判定　(中心付)
		bool DcsAtoA (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center);

		//相殺枠判定(中心付)
		bool DcsOffset (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center);

		//エフェクトの相殺枠判定
		void DcsOffsetEf (PLP_ExEf plpExEf1, PLP_ExEf plpExEf2, P_CharaRect pCharaRect2p);

		//エフェクトのヒット枠判定
		bool DcsHitEf (PLP_ExEf plpExEf1, PV_RECT pvHRect2, P_ExeChara pHitChara, int & refPower);


		//判定後にキャラに反映する
		void Propagate ();

	};


}	//namespace GAME

