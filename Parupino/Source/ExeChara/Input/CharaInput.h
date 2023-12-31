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
#include "Chara.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"

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

		//コマンドが完成したIDを優先順に保存したリスト
		std::vector < UINT >		m_vCompID;		

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

		//成立リストを生成する
		virtual void MakeTransitIDList ( Chara & ch, P_Script pScp, bool dirRight );

		//キーの保存
		void SetGameKey ( V_GAME_KEY & vKey );

		//優先リストの先頭を取得する
		UINT GetCompID ();

		//優先リストの参照を得る
		const std::vector < UINT > & GetvCompID () const { return m_vCompID; }

	};

	using P_CharaInput = std::shared_ptr < CharaInput >;


}	//namespace GAME


