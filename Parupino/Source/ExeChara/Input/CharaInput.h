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

#if 0

		//ブランチリストをチェックして
		//コマンド条件が達成されていたら遷移先のアクションを返す
		//戻値：nullptr	不成立
		P_Action GetpTransitAction ( PVP_Branch pvpBranch, bool dirRight );

		//ブランチリストをチェックして
		//コマンド条件が達成されていたら遷移先のアクションIDを返す
		//戻値：enum { NO_COMPLETE (0xFFFFFFFF) } 不成立
		virtual UINT GetTransitID ( PVP_Branch pvpBranch, bool dirRight );
#endif // 0


		//ルートリストをチェックして各種ブランチのコマンドが達成されていたら
		//遷移先のアクションIDを返す
		//戻値：enum { NO_COMPLETE (0xFFFFFFFF) } 不成立
		virtual UINT GetTransitID ( Chara & ch, P_Script pScp, bool dirRight );


		//-----------------------------------------------------------------
		//スクリプトで指定しない直接入力の状態
	private:
		_GameKeyCommand gkc_lvr4;
		_GameKeyCommand gkc_lvr1;
		_GameKeyCommand gkc_lvr4E;
		_GameKeyCommand gkc_lvr2E;
	public:
		bool IsInput4 () const { return gkc_lvr4.CompareTarget ( m_vGameKey[0] ); }
		bool IsInput1 () const { return gkc_lvr1.CompareTarget ( m_vGameKey[0] ); }
		bool IsInput4E () const { return gkc_lvr4E.CompareTarget ( m_vGameKey[0] ); }
		bool IsInput2E () const { return gkc_lvr2E.CompareTarget ( m_vGameKey[0] ); }

		//後入力
//		bool IsInput4 () const { return m_vGameKey[0].IsKeyLvrCmd ( _GameKeyCommand::LVR_CMD_4 ); }

		//後下入力
//		bool IsInput1 () const { return m_vGameKey[0].IsKeyLvrCmd ( _GameKeyCommand::LVR_CMD_1 ); }

		//後要素の入力確認 : 右向き時4E、ただし入力保存時に向きは反映されている
//		bool IsInputBack () const { return m_vGameKey[0].IsKeyLvrCmd ( _GameKeyCommand::LVR_CMD_4E ); }

		//下要素の入力確認
//		bool IsInput2E () const { return m_vGameKey[0].IsKeyLvrCmd ( _GameKeyCommand::LVR_CMD_2E ); }
	};

	using P_CharaInput = shared_ptr < CharaInput >;


}	//namespace GAME


