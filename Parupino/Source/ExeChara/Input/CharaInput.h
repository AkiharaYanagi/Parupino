//=================================================================================================
//
// CharaInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../CharaData/Chara.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class CharaInput
	{
		static const UINT	m_vGameKeyNum;	//キー入力の保存フレーム数
		V_GAME_KEY			m_vGameKey;		//キー入力保存
		PLAYER_ID			m_playerID;		//プレイヤーID
		bool				m_cpu;			//CPUフラグ

	public:
		CharaInput ();
		CharaInput ( const CharaInput& rhs ) = delete;		//コピー禁止
		virtual ~CharaInput ();

		//プレイヤーID
		void SetPlayer ( PLAYER_ID id ) { m_playerID = id; }

		//フレーム毎における入力の保存
		virtual void Update ( bool dirRight );

		//キー入力配列の参照
		const V_GAME_KEY & GetvGameKey () const { return m_vGameKey; }

		//ルートリストをチェックして各種ブランチのコマンドが達成されていたら
		//遷移先のアクションIDを返す
		//戻値：enum { NO_COMPLETE (0xFFFFFFFF) } 不成立
		virtual UINT GetTransitID ( Chara & ch, P_Script pScp, bool dirRight );

		//キーの保存
		void SetGameKey ( V_GAME_KEY & vKey );

	};

	using P_CharaInput = shared_ptr < CharaInput >;


}	//namespace GAME


