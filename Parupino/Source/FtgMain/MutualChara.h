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
#include "Ef/EfClang.h"
#include "Ef/EfSpark.h"
#include "Ef/EfParticle.h"
#include "Decision.h"

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

		//粒子
		P_EEfParticle	m_efParticle;
	
		//開始ウェイト
		UINT	m_startTimer;
		UINT	m_startTime;
		P_Timer	m_tmrStartWait;

		//終了ウェイト
		UINT	m_endTimer;
		UINT	m_endTime;
		P_Timer	m_tmrEndWait;

		//暗転
		UINT	m_blackOut;

		//スクリプトからのストップ
		UINT	m_scpStop;

		//ヒットストップ
		P_Timer	m_tmrHitstop;

		//勝者
		WINNER	m_winner;


		//判定クラス
		Decision	m_decision;


	public:
		MutualChara ();
		MutualChara ( const MutualChara & rhs ) = delete;
		~MutualChara ();

		void ParamInit ( P_Param pParam );

		//戦闘開始の初期化
		void Start ();

		//スクリプトの毎フレーム処理
		void Conduct ();

		void Collision ();		//重なり判定
		void Decision ();		//攻撃判定

		void Grp ();			//グラフィック共通


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

		UINT GetBlackOut () const { return m_blackOut; };	//暗転
		void SetBlackOut ( UINT i ) { m_blackOut = i; };

		UINT GetScpStop () const { return m_scpStop; };	//停止
		void SetScpStop ( UINT i ) { m_scpStop = i; };

		void SetCharaState ( CHARA_STATE chst );

		//勝者
		WINNER GetWinner () const { return m_winner; }
		CHARA_NAME GetWinnerName () const;

	private:
		//------------------------------------------------------
		//	内部関数
		//------------------------------------------------------

		//枠表示切替
		void SwitchRect ();

		//CPU操作切替
		void SwithcCPU ();
	};

	using P_MutualChara = shared_ptr < MutualChara >;


}	//namespace GAME


