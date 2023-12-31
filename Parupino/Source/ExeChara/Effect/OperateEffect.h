//=================================================================================================
//
// OperateEffect ヘッダファイル
//		Effectを０〜複数個で実行する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "ExeEffect.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class OperateEffect : public TASK_VEC
	{
		P_Chara			m_pChara;			//キャラ
		PLP_ExEf		m_plpExeEffect;		//エフェクトの実行リスト(GameMain中に動的に生成・解放する)

		PVP_TxBs		m_pvpEfTexture;		//エフェクトイメージのテクスチャリスト
		VP_Branch		m_vpBranch;			//エフェクトの分岐
		VP_Route		m_vpRoute;			//ルート

	public:
		OperateEffect ();
		OperateEffect ( const OperateEffect & rhs ) = delete;
		~OperateEffect ();

		void Rele ();

		//キャラポインタの設定
		void SetpChara ( P_Chara p );

		//エフェクトリスト取得
		PLP_ExEf GetplpExEf () { return m_plpExeEffect; }

		//-----------------------------
		//エフェクトリストに追加
		void AddListEffect ( P_Effect pEffect, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight );

		//オブジェクトからExeEfを取得
		P_ExEf GetpExEf ( P_Effect p ) const;

		//オブジェクトが実行中かどうか
		bool IsActive ( P_Effect p ) const { return GetpExEf ( p )->IsActive (); }

		//オブジェクトによる稼働開始
		void DriveEffect ( P_Effect p ) { GetpExEf ( p )->Drive (); }

		//オブジェクトによる稼働停止
		void StopEffect ( P_Effect p ) { GetpExEf ( p )->Stop (); }

		//---------------------------------------------------------------
		//エフェクトの動作
		void PreScriptMove ();
		void PostScriptMove ( VEC2 ptChara, bool dirRight );
		void SynchroScript ( VEC2 ptChara );

		//---------------------------------------------------------------
		//Rect
		void OnDispRect ();
		void OffDispRect ();
	};

	using P_OprEf = std::shared_ptr < OperateEffect >;


}	//namespace GAME


