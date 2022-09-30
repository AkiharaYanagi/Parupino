//=================================================================================================
//
// エグゼキャラ　ヘッダファイル
//		キャラのデータを受けてゲーム上で実行（フレーム毎動作、描画）する
//		操作時の位置などを保存する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
#include "../GameMain/Param.h"
#include "../FtgMain/G_Ftg.h"
#include "../FtgMain/FtgConst.h"
#include "../CharaData/Chara.h"
#include "../CharaData/IO/LoadChara.h"
#include "Disp/DispChara.h"
#include "Disp/DispInput.h"
#include "Input/CharaInput.h"
#include "Input/PlayerInput.h"
#include "Input/CPUInput.h"
#include "Effect/OperateEffect.h"
#include "CharaRect.h"
#include "BtlParam.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class ExeChara;
	using P_ExeChara = shared_ptr < ExeChara >;
	using WP_ExeChara = weak_ptr < ExeChara >;

	//クラス
	class ExeChara : public TASK_VEC, public enable_shared_from_this < ExeChara >
	{
		//------------------------------------------------
		//基本データ
		P_Chara			m_pChara;		//キャラデータ
		PLAYER_ID		m_playerID;		//プレイヤーID
		CHARA_NAME		m_name;			//キャラ名
		WP_ExeChara		m_pOther;		//相手キャラ(循環参照なのでweak_ptr)
		PLAYER_MODE		m_playerMode;	//プレイヤーモード(人,CPU,ネットワーク)

		//------------------------------------------------
		//表示
		DispChara		m_dispChara;	//キャラ全般表示
		DispInput		m_dispInput;	//入力表示

		//------------------------------------------------
		//入力
		P_CharaInput	m_pCharaInput;	//入力

		//------------------------------------------------
		//スクリプト実行
		UINT			m_actionID;		//実効現在アクションID
		P_Action		m_pAction;		//実効アクションポインタ
		UINT			m_frame;		//実効内部フレーム(スクリプトID)
		P_Script		m_pScript;		//実効スクリプトポインタ

		//------------------------------------------------
		//枠
		P_CharaRect		m_charaRect;	//枠
		bool			m_bDispRect;	//枠表示

		//------------------------------------------------
		//パラメータ
		BtlParam		m_btlPrm;		//バトルパラメータ	

		//------------------------------------------------
		//エフェクト監理
		OperateEffect	m_oprtEf;

		//------------------------------------------------
		//ゲーム進行状態
		CHARA_STATE		m_charaState;

	public:
		ExeChara () = delete;
		ExeChara ( PLAYER_ID m_playerID );
		ExeChara ( const ExeChara & rhs ) = delete;
		~ExeChara ();

		void ParamInit ( P_Param pParam );
		void Load ();
		void Init ();
		void Reset ();
		void _Reset ();	//復旧時

		//------------------------------------------------------------
		//******************************
		// 毎フレーム スクリプト処理一連
		//******************************
		void PreScriptMove ();			//	スクリプト前処理
		//MutualChara::Collision ();	//	相互判定 (接触枠)
		void ScriptRectMove ();			//	ぶつかり後、判定枠を設定
		//MutualChara::Decision ();		//	相互判定 (攻撃枠、ヒット枠)
		void PostScriptMove ();			//	スクリプト後処理
		//------------------------------------------------------------

		//相手を設定
		void SetpOther ( WP_ExeChara p ) { m_pOther = p; /*m_cpuInput.SetpExeCharaOther ( p );*/ }

		//------------------------------------------------------------
		//パラメータ
		VEC2 GetPos () const { return m_btlPrm.GetPos (); }		//位置を取得
		bool GetDirRight () const { return m_btlPrm.GetDirRight (); }	//向きを取得
		void SetDirRight ( bool b ) { m_btlPrm.SetDirRight ( b ); }		//立ち状態で向きを設定

		void BackPt () { m_btlPrm.BackPt (); }
		void BackPtX () { m_btlPrm.BackPtX (); }
		void BackMoveX ();
		void LookOther ();	//相手の方向を向く

		//---------------------------------------------
		//ゲーム進行状態

		CHARA_STATE GetCharaState () const { return m_charaState; }
		void SetCharaState ( CHARA_STATE chst ) { m_charaState = chst; }

		//開始
		void SetMain () { m_charaState = CHST_MAIN; }

		//入力をする状態かどうか
		bool CanInput () const;

		//メイン状態かどうか
		bool IsMain () const;

		//ライフ０チェック
		bool IsZeroLife () const { return ( 0 >= m_btlPrm.GetLife () ); }

#if 0
		bool GetStart () const { return m_start; }		//開始状態取得
		void SetStart ( bool b ) { m_start = b; }
		bool GetEnd () const { return m_end; }			//終了状態取得
		void SetEndWait ( bool b ) { m_endWait = b; }
#endif // 0

		//------------------------------------------------
		//エフェクト

		//エフェクトリスト取得
		PLP_ExEf GetplpExEf () { return m_oprtEf.GetplpExEf (); }

		//---------------------------------------------
		//枠
		void AdjustCRect ();		//現在位置から接触枠を反映
		P_CharaRect GetpCharaRect () { return m_charaRect; }		//枠取得

		//---------------------------------------------
		//パラメータ取得

		//各値取得
		CHARA_NAME GetCharaName () const { return m_name; }
		int GetPower () const { return m_btlPrm.GetPower (); }		//攻撃値取得
		int GetLife () const { return m_btlPrm.GetLife (); }		//ライフ取得
		ACTION_POSTURE GetPosture () const { return m_pAction->GetPosture (); }

		//---------------------------------------------
		//外部からの状態変更

		//一時停止
		void SetWait ( bool b ) { m_btlPrm.SetWait ( b ); }	//入力を停止
		void SetStop ( bool b ) { m_btlPrm.SetStop ( b ); }	//描画更新を停止
		void SetStopTimer ( UINT i ) {
			m_btlPrm.GetTmr_Stop ()->SetTargetTime ( i );
			m_btlPrm.GetTmr_Stop ()->Start ();
		}

		//打合
		bool GetClang () const { return m_btlPrm.GetClang (); }
		void SetClang ( bool b ) { m_btlPrm.SetClang ( b ); }

		//引数：打合停止時間
		void OnClang ( UINT nLurch, CLANG_DECISION_WL clangDecision );

		//くらい発生
		bool IsDamaged () const { return m_btlPrm.GetDamaged (); }
		void SetDamaged ( bool b ) { m_btlPrm.SetDamaged ( b ); }
		void OnDamaged ( int damage );

		//ヒット発生
		bool IsHit () const { return m_btlPrm.GetHitEst (); }
		void SetHit ( bool b ) { m_btlPrm.SetHitEst ( b ); }
		void OnHit ();
		void OnEfHit ();

		//-------------------------------------------------
		//スクリプトからの変更
		//暗転
		UINT GetBlackOut () const { return m_btlPrm.GetBlackOut (); }
		void SetBlackOut ( UINT i ) { m_btlPrm.SetBlackOut ( i ); }

		//停止
		UINT GetScpStop () const { return m_btlPrm.GetScpStop (); }
		void SetScpStop ( UINT i ) { m_btlPrm.SetScpStop ( i ); }

		//-------------------------------------------------

		//終了待機
		void SetEndWait ();

		//終了演出
		void OnEndAct ();

		//ダウン状態
		bool IsDown () { return CHST_DOWN == m_charaState; }

		//ダウン終了状態
		bool IsDownEnd () { return CHST_DOWN_END == m_charaState; }

		//勝利状態
		bool IsWin () { return CHST_WIN == m_charaState; }

		//勝利終了状態
		bool IsWinEnd () { return CHST_WIN_END == m_charaState; }

		//強制終了状態
		void ForcedEnd ()
		{
			if ( m_btlPrm.GetLife () <= 0 )
			{
				m_charaState = CHST_DOWN_END;
//				m_actionID = m_pChara->GetBsAction ( BA_DOWN );
				TransitAction ( m_actionID );
			}
			else
			{
				m_charaState = CHST_WIN_END;
//				m_actionID = m_pChara->GetBsAction ( BA_WIN );
				TransitAction ( m_actionID );
			}
		}

		//Rect
		void OnDispRect () { m_bDispRect = true; }
		void OffDispRect () { m_bDispRect = false; }

		//外部からの状態確認
		bool IsNameAction ( tstring nameAction ) const { return m_pAction->IsName ( nameAction ); }

		//ダッシュ分岐
		void OnDashBranch ();


	//================================================
	//	内部関数
	//================================================
	private:
		//------------------------------------------------
		//Init
		void MakeEfOprt ();		//エフェクト処理の生成

		//PreScriptMove
		void AlwaysMove ();		// アクションとスクリプトによらない一定の処理

		void TransitAction ();	// アクション移項
		void TransitAction ( UINT actionID );		//アクションの移項
		void TransitAction_Condition_I ( BRANCH_CONDITION CONDITION, bool forced );	//条件をチェックして移行
		void TransitAction_Condition_E ( BRANCH_CONDITION CONDITION, bool forced );	//条件をチェックして移行
		UINT Check_TransitAction_Condition ( BRANCH_CONDITION CONDITION );	//アクション移行(条件チェック)

		//ぶつかり後、位置の修正
		void Landing ();	//着地

		//PostScriptMove
		void AlwaysPostMove ();		// アクションとスクリプトによらない一定の処理
		void CheckLife ();			//ライフ判定
		void UpdateGraphic ();		//グラフィック更新
		void EffectGenerate ();		//エフェクト生成
		void EffectMove ();
		void TurnDispRect ();		//枠表示切替

		//------------------------------------------------
		//アクション体勢
		bool Is_APStand () { return m_pAction->GetPosture () == AP_STAND; }
		bool IsJump () { return m_pAction->GetPosture () == AP_JUMP; }
		bool IsCrouch () { return m_pAction->GetPosture () == AP_CROUCH; }

		//------------------------------------------------
		//アクションカテゴリ

		//現在アクションカテゴリ取得
		ACTION_CATEGORY ActCtg () const { return m_pAction->GetCategory (); }
		bool IsActCtg ( ACTION_CATEGORY ac ) const { return ac == ActCtg (); }
		//各アクションかどうか
		bool IsAttacking () const
		{
			return
				m_pAction->GetCategory ()  == AC_ATTACK_L 
			||	m_pAction->GetCategory ()  == AC_ATTACK_M
			||	m_pAction->GetCategory ()  == AC_ATTACK_H; 
		}
		bool IsStand ()		{ return m_pAction->GetCategory ()  == AC_STAND; }
		bool IsMove ()		{ return m_pAction->GetCategory ()  == AC_MOVE; }
		bool IsDash ()		{ return m_pAction->GetCategory ()  == AC_DASH; }
		bool IsPoised ()	{ return m_pAction->GetCategory ()  == AC_POISED; }
		bool IsClang ()		{ return m_pAction->GetCategory ()  == AC_CLANG; }
		bool IsAvoid ()		{ return m_pAction->GetCategory ()  == AC_AVOID; }
		bool IsDotty ()		{ return m_pAction->GetCategory ()  == AC_DOTTY; }
		bool IsDamaged ()	{ return m_pAction->GetCategory ()  == AC_DAMAGED; }

#if 0
		//現在のアクションが基本アクションかどうか
		bool IsBasicAction ( BASIC_ACTION ba ) 
		{
			UINT id = m_pChara->GetBsAction ( ba ); 
			return id == m_actionID;
		}
#endif // 0

		//------------------------------------------------
#if 0
		//のけぞり時間
		void SetLurch ( UINT n ) { if ( 0 != n ) { m_lurch = n;  } }
		bool LurchTimer ();

#endif // 0

	};


}	//namespace GAME


