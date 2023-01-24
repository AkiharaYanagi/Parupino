//=================================================================================================
//
// ExeChara_Demo　ヘッダファイル
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
#include "BtlParam.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class ExeChara_Demo;
	using P_ExeChara_Demo = shared_ptr < ExeChara_Demo >;
	using WP_ExeChara_Demo = weak_ptr < ExeChara_Demo >;

	//クラス
	class ExeChara_Demo : public TASK_VEC, public enable_shared_from_this < ExeChara_Demo >
	{
		//------------------------------------------------
		//基本データ
		P_Chara			m_pChara;		//キャラデータ
		PLAYER_ID		m_playerID;		//プレイヤーID
		CHARA_NAME		m_name;			//キャラ名

		//------------------------------------------------
		//パラメータ
		BtlParam		m_btlPrm;		//バトルパラメータ	

		//------------------------------------------------
		//表示
		DispChara		m_dispChara;	//キャラ全般表示

		//------------------------------------------------
		//スクリプト実行
		UINT			m_actionID;		//実効現在アクションID
		P_Action		m_pAction;		//実効アクションポインタ
		UINT			m_frame;		//実効内部フレーム(スクリプトID)
		P_Script		m_pScript;		//実効スクリプトポインタ

		//------------------------------------------------
		//ゲーム進行状態
		CHARA_STATE		m_charaState;

	public:
		ExeChara_Demo () = delete;
		ExeChara_Demo ( PLAYER_ID m_playerID );
		ExeChara_Demo ( const ExeChara_Demo & rhs ) = delete;
		~ExeChara_Demo ();

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
		void PostScriptMove ();			//	スクリプト後処理
		//------------------------------------------------------------

		//------------------------------------------------------------
		//パラメータ
		VEC2 GetPos () const { return m_btlPrm.GetPos (); }		//位置を取得
		bool GetDirRight () const { return m_btlPrm.GetDirRight (); }	//向きを取得
		void SetDirRight ( bool b ) { m_btlPrm.SetDirRight ( b ); }		//立ち状態で向きを設定

		void BackPt () { m_btlPrm.BackPt (); }
		void BackPtX () { m_btlPrm.BackPtX (); }

	//================================================
	//	内部関数
	//================================================
	private:
		//------------------------------------------------
		//PreScriptMove
		void TransitAction ();	// アクション移項
		void TransitAction ( UINT actionID );		//アクションの移項

		//PostScriptMove
		void AlwaysPostMove ();		// アクションとスクリプトによらない一定の処理
		void UpdateGraphic ();		//グラフィック更新

	};


}	//namespace GAME


