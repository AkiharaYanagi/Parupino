//=================================================================================================
//
//	バトルパラメータ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
#include "../FtgMain/FtgConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class BtlParam : public TASK_VEC
	{
		//------------------------------------------------
		//パラメータ
		VEC2	m_ptChara;		//キャラ位置
		VEC2	m_tempPt;		//一時保存
		bool	m_dirRight;		//向き(右：正, 左：逆)
		VEC2	m_inertial;		//慣性
		VEC2	m_vel;	//速度
		VEC2	m_acc;	//加速度
		float	m_g;	//重力
		float	m_vg;	//重力

		int		m_life;			//ライフ
		int		m_balance;		//バランス
		int		m_power;		//実効攻撃値
		int		m_damage;		//ダメージ(ライフ減少分)

		bool	m_damaged;		//くらいフラグ
		bool	m_hitEst;		//攻撃成立フラグ
		bool	m_FirstEf;		//初回Efフラグ
		bool	m_FirstSE;		//初回SEフラグ

		bool	m_ForcedChange;	//強制変更

		P_Timer	m_tmrHitstop;	//ヒットストップタイマー
		P_Timer	m_tmrDown;		//ダウンタイマー
		P_Timer	m_tmrEnd;		//終了状態タイマー

		bool	m_clang;		//打合発生フラグ
		bool	m_transit;		//スクリプト遷移したフレーム

//		UINT	m_lurch;		//のけぞり(キャンセル不可)時間追加
//		UINT	m_lurchTimer;

		bool	m_wait;			//入力を一時停止
		bool	m_stop;			//入力、スクリプト処理を一時停止
		P_Timer	m_stopTimer;
		UINT	m_blackOut;		//暗転
		UINT	m_scpStop;		//スクリプトからの停止

		//------------------------------------------------
		//ゲーム進行状態
		CHARA_STATE		m_charaState;


	public:
		BtlParam ();
		BtlParam ( const BtlParam & rhs ) = delete;
		~BtlParam ();
	};


}	//namespace GAME

