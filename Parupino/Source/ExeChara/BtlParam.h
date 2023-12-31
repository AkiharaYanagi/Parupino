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
#include "Script.h"
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

	class BtlParam
	{
		//------------------------------------------------
		//パラメータ
		PLAYER_ID	m_playerID;			//プレイヤID
		VEC2	m_posChara;		//キャラ位置
		VEC2	m_tempPt;		//一時保存
		bool	m_dirRight;		//向き(右：正, 左：逆)
		VEC2	m_inertial;		//慣性
		VEC2	m_dashInertial;	//ダッシュ慣性
		VEC2	m_vel;	//速度
		VEC2	m_acc;	//加速度
		float	m_g;	//重力
		float	m_vg;	//重力(計算用)

		int		m_life;			//ライフ
		int		m_balance;		//バランス
		int		m_mana;			//マナ

		int		m_power;		//実効攻撃値
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

		VP_Timer	m_timers;	//タイマ監理

		P_Timer	m_tmrStop;		//全体ストップタイマ
		P_Timer	m_tmrHitstop;	//ヒットストップタイマ
		P_Timer	m_tmrDown;		//ダウンタイマ
		P_Timer	m_tmrEnd;		//終了状態タイマ
		UINT	m_blackOut;		//暗転
		UINT	m_scpStop;		//スクリプトからの停止

		//連続ヒット
		P_Timer	m_tmrHitPitch;		//ヒット間隔タイマ
		UINT	m_hitNum;			//同一アクション内ヒット数

		//Result用
		int		m_nActTransit;		//アクション移行回数

	public:
		BtlParam ();
		BtlParam ( const BtlParam & rhs );	// ※ コピー可能
		~BtlParam ();

		void LoadPlayerID ( PLAYER_ID playerID );
		void LoadTimer ();
		void Init ();
		void TimerMove ();

		//--------------------------------------------------------------------
		//モード別初期化
		//トレーニング初期化
		void TrainingInit ();

		//--------------------------------------------------------------------
		//アクション終了時
		void EndAction ();

		//位置計算
		void PosInit ();
		void CalcPos ( P_Script pScp );
		void BackPt () { m_posChara = m_tempPt; }
		void BackPtX () { m_posChara.x = m_tempPt.x; }

		//--------------------------------------------------------------------
		//各パラメータ
		GT_ST ( VEC2, GetPos, SetPos, m_posChara )			//キャラ位置
		GT_ST ( bool, GetDirRight, SetDirRight, m_dirRight )		//右正の向き
		GT_ST ( VEC2, GetInertial, SetInertial, m_inertial )			//慣性
		GT_ST ( VEC2, GetDashInertial, SetDashInertial, m_dashInertial )	//ダッシュ慣性
		GT_ST ( VEC2, GetVel, SetVel, m_vel )			//速度
		GT_ST ( VEC2, GetAcc, SetAcc, m_acc )			//加速度
		GT_ST ( float, GetG, SetG, m_g )			//重力
		GT_ST ( float, GetVg, SetVg, m_vg )			//重力(計算用)

		GT_ST ( int, GetLife, SetLife, m_life	)			//ライフ
		GT_ST ( int, GetBalance, SetBalance, m_balance )	//バランス
		GT_ST ( int, GetMana, SetMana, m_mana )				//マナ
		GT_ST ( int, GetPower, SetPower, m_power )			//実効攻撃値
		
		//--------------------------------------------------------------------
		//単純フラグ { get; set; }
		GT_ST ( bool, GetDamaged, SetDamaged, m_damaged )		//くらい
		GT_ST ( bool, GetHitEst, SetHitEst, m_hitEst )			//ヒット成立
		GT_ST ( bool, GetForcedChange, SetForcedChange, m_ForcedChange )		//強制変更
		GT_ST ( bool, GetClang, SetClang, m_clang )				//打合
		GT_ST ( bool, GetTrangit, SetTrangit, m_transit )		//スクリプト遷移
		GT_ST ( bool, GetFirstEf, SetFirstEf, m_FirstEf )		//エフェクト発生初回
		GT_ST ( bool, GetFirstSE, SetFirstSE, m_FirstSE )		//SE発生初回
		GT_ST ( bool, GetWait, SetWait, m_wait )				//待機(入力を停止)
		GT_ST ( bool, GetStop, SetStop, m_stop )				//停止(入力、スクリプト処理を停止)

		//--------------------------------------------------------------------
		GT_ST ( UINT, GetBlackOut, SetBlackOut, m_blackOut )	//暗転
		GT_ST ( UINT, GetScpStop, SetScpStop, m_scpStop )	//スクリプトからの停止
		GT_ST ( UINT, GetHitNum, SetHitNum, m_hitNum )		//同一アクション内ヒット数

		//--------------------------------------------------------------------
		GT_ST ( int, GetNActTrs, SetNActTrs, m_nActTransit )			//アクション移行回数

		//--------------------------------------------------------------------
		//タイマ
		P_Timer GetTmr_Stop () { return m_tmrStop; }
		P_Timer GetTmr_HitStop () { return m_tmrHitstop; }
		P_Timer GetTmr_HitPitch () { return m_tmrHitPitch; }
		P_Timer GetTmr_Down () { return m_tmrDown; }
		P_Timer GetTmr_End () { return m_tmrEnd; }
		//--------------------------------------------------------------------


		//====
		//増減用
		void AddLife ( int n );
		void AddBalance ( int n );
		void AddMana ( int n );

		void AddNActTrs ( int n ) { m_nActTransit += n; }

		//----
		//処理まとめ
		void OnHit ();	//ヒット時
		void HitPitchWaitStart ();	//ヒット間隔再スタート


	private:
		// 慣性の減少
		void DecreaseInertial ( float d, VEC2 & inertial );
	};


}	//namespace GAME

