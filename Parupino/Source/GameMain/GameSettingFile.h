//=================================================================================================
//
// ゲーム設定ファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameConst.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
	//ゲーム内設定
	class GameSettingFile
	{
		START_MODE		m_startMode;	//開始指定

		PLAYER_MODE		m_playerMode1p;	//１P操作
		PLAYER_MODE		m_playerMode2p;	//２P操作

		CHARA_NAME		m_name1p;		//選択キャラ
		CHARA_NAME		m_name2p;

	public:
		GameSettingFile ();
		GameSettingFile ( const GameSettingFile & rhs );	//コピー可能
		~GameSettingFile ();

		//読込
		void Load ();

		//値の取得
		START_MODE GetStartMode () const { return m_startMode; }
		
		PLAYER_MODE GetPlayerMode1p () const { return m_playerMode1p; }
		PLAYER_MODE GetPlayerMode2p () const { return m_playerMode2p; }
		PLAYER_MODE GetPlayerMode ( PLAYER_ID pid ) const
		{
			if ( pid == PLAYER_ID_1 ) { return m_playerMode1p; }
			if ( pid == PLAYER_ID_2 ) { return m_playerMode2p; }
			return MODE_PLAYER;
		}
		void SetPlayerMode1p ( PLAYER_MODE mode ) { m_playerMode1p = mode; }
		void SetPlayerMode2p ( PLAYER_MODE mode ) { m_playerMode2p = mode; }

		CHARA_NAME GetName1p () const { return m_name1p; }
		CHARA_NAME GetName2p () const { return m_name2p; }
		CHARA_NAME GetName ( PLAYER_ID pid ) const
		{
			if ( pid == PLAYER_ID_1 ) { return m_name1p; }
			if ( pid == PLAYER_ID_2 ) { return m_name2p; }
			return CHARA_NAME_NUM;
		}

#if 0
		//切替
		void SetDemo ( bool b ) { m_startMode = b ? START_DEMO : START_TITLE; }
		void SetTraining ( bool b ) { m_startMode = b ? START_TRAINING : START_TITLE; }
#endif // 0

		//初期値
		void	SetDefault ();
	};

}	//namespace GAME

