//=================================================================================================
//
//	MutualChara ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "G_Ftg.h"
#include "FtgConst.h"	
#include "../GameMain/Param.h"
#include "../ExeChara/ExeChara.h"
#include "EfClang.h"
#include "EfSpark.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class MutualChara : public TASK_VEC
	{
		//キャラ
		P_ExeChara		m_exeChara1;
		P_ExeChara		m_exeChara2;

		//共通エフェクト
		P_EfClang		m_efClang;
		P_EfSpark		m_efSpark;
	
		//開始ウェイト
		UINT	m_startTimer;
		UINT	m_startTime;
		P_Timer	m_tmrStartWait;

		//終了ウェイト
		UINT	m_endTimer;
		UINT	m_endTime;
		P_Timer	m_tmrEndWait;

		//ヒットストップ
		P_Timer	m_tmrHitstop;

		//勝者
		WINNER m_winner;

	public:
		MutualChara ();
		MutualChara ( const MutualChara & rhs ) = delete;
		~MutualChara ();

		void ParamInit ( P_Param pParam );

		//スクリプトの毎フレーム処理
		void Conduct ();

		void Collision ();		//重なり判定
		void Decision ();		//攻撃判定


		//状態変更
		void SetReady ();
		void SetMain ();
		void Wait ( bool b );
		void Stop ( bool b );
		void EndAct ();
		bool CheckZeroLife ();	//格闘終了判定
		bool CheckDown ();		//ダウン判定
		void SetEndWait ();
		bool CheckDownEnd ();	//ダウン状態終了判定
		bool CheckWin ();		//勝利状態判定
		bool CheckWinEnd ();	//勝利終了状態判定
		bool CheckWinner ();	//勝利側判定
		void ForcedEnd ();	//強制終了

		void SetCharaState ( CHARA_STATE chst );

		//勝者
		WINNER GetWinner () const { return m_winner; }
		CHARA_NAME GetWinnerName () const;

	private:
		//------------------------------------------------------
		//	内部関数
		//------------------------------------------------------

		//相殺枠判定(中心付)
		bool DcsOffset ( P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center );

		//エフェクトの相殺枠判定
		void DcsOffsetEf ( PLP_ExEf plpExEf1, PLP_ExEf plpExEf2, P_CharaRect pCharaRect2p );

		//エフェクトのヒット枠判定
		bool DcsHitEf ( PLP_ExEf plpExEf1, PV_RECT pvHRect2, P_ExeChara pHitChara, int & refPower );

		//枠表示切替
		void SwitchRect ();
	};

	using P_MutualChara = shared_ptr < MutualChara >;


}	//namespace GAME


