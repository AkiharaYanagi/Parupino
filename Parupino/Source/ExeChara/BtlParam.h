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
//単純フラグboolに対する get;set;マクロ
#define GET(type,Getter,prm)		type Getter () const { return prm; }
#define SET(type,Setter,prm)		void Setter ( type t ){ prm = t; }
#define GT_ST(type,Getter,Setter,b)		GET(type,Getter,b) SET(type,Setter,b)


	class BtlParam : public TASK_VEC
	{
		//------------------------------------------------
		//パラメータ
		VEC2	m_posChara;		//キャラ位置
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
		bool	m_clang;		//打合発生フラグ
		bool	m_transit;		//スクリプト遷移したフレーム

//		UINT	m_lurch;		//のけぞり(キャンセル不可)時間追加
//		UINT	m_lurchTimer;

		bool	m_wait;			//入力を一時停止
		bool	m_stop;			//入力、スクリプト処理を一時停止
		P_Timer	m_TmrStop;		//全体ストップタイマ
		P_Timer	m_tmrHitstop;	//ヒットストップタイマー
		P_Timer	m_tmrDown;		//ダウンタイマー
		P_Timer	m_tmrEnd;		//終了状態タイマー
		UINT	m_blackOut;		//暗転
		UINT	m_scpStop;		//スクリプトからの停止

		//------------------------------------------------
		//ゲーム進行状態
		CHARA_STATE		m_charaState;


	public:
		BtlParam ();
		BtlParam ( const BtlParam & rhs ) = delete;
		~BtlParam ();

		void Init ();
		void InitPlayerID ( PLAYER_ID playerID );


		//--------------------------------------------------------------------
		//アクション終了時
		void EndAction ();

		//--------------------------------------------------------------------
		//各パラメータ
		GT_ST ( VEC2, GetPos, SetPos, m_posChara )			//キャラ位置
		GT_ST ( bool, GetDirRight, SetDirRight, m_dirRight )		//右正の向き

		//ぶつかり後、位置の修正
		void BackPt () { m_posChara = m_tempPt; }
		void BackPtX () { m_posChara.x = m_tempPt.x; }
		void BackMoveX ();
		void LookOther ();	//相手の方向を向く

		GT_ST ( int, GetLife, SetLife, m_life )			//ライフ
		GT_ST ( int, GetBalance, SetBalance, m_balance )	//バランス
		GT_ST ( int, GetPower, SetPower, m_power )		//実効攻撃値
		GT_ST ( int, GetDamage, SetDamage, m_damage )	//ダメージ（ライフ減少分）

		//--------------------------------------------------------------------
		//単純フラグ { get; set; }
		GT_ST ( bool, GetDamaged, SetDamaged, m_damaged )		//くらい
		GT_ST ( bool, GetHitEst, SetHitEst, m_hitEst )			//ヒット成立
		GT_ST ( bool, GetForcedChange, SetForcedChange, m_ForcedChange )		//強制変更
		GT_ST ( bool, GetClang, SetClang, m_clang )				//打合
		GT_ST ( bool, GetTrangit, SetTrangit, m_transit )			//スクリプト遷移
		GT_ST ( bool, GetFirstEf, SetFirstEf, m_FirstEf )		//エフェクト発生初回
		GT_ST ( bool, GetFirstSE, SetFirstSE, m_FirstSE )		//SE発生初回
		GT_ST ( bool, GetWait, SetWait, m_wait )				//SE発生初回

		//--------------------------------------------------------------------
		//タイマ
		P_Timer GetTmr_Stop () { return m_TmrStop; }
		P_Timer GetTmr_HitStop () { return m_tmrHitstop; }
		P_Timer GetTmr_Down () { return m_tmrDown; }
		P_Timer GetTmr_End () { return m_tmrEnd; }
		//--------------------------------------------------------------------
	};


}	//namespace GAME

