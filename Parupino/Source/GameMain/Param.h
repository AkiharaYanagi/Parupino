//=================================================================================================
//
// パラメータヘッダ
//		ゲーム内でシーン間をまたぐ値
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameConst.h"
#include "GameSettingFile.h"
#include "SceneCommon.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Param	: public GameParam
	{
		//ゲーム設定 ( 外部ファイル読込 )
		GameSettingFile		m_setting;

		//内部設定
		MUTCH_MODE			m_mutchMode = MODE_PLAYER_PLAYER;

		//リザルト用
		PLAYER_ID		m_winner;	//勝者
		int				m_n_act_1p;	//アクション回数
		int				m_n_act_2p;	//アクション回数

	public:
		Param ();
		Param ( const Param & rhs );	//コピー可能
		~Param ();

		GameSettingFile GetGameSetting () const { return m_setting; }
		void SetSettingFile ( GameSettingFile stg ) { m_setting = stg; }

		void SetMutchMode ( MUTCH_MODE mode ) { m_mutchMode = mode; }
		void SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p );
		MUTCH_MODE GetMutchMode () const { return m_mutchMode; }

		PLAYER_MODE GetPlayerMode ( PLAYER_ID id ) const;

		void SetRandomChara ();


		//リザルト用
		void SetWinner ( PLAYER_ID plr ) { m_winner = plr; }
		PLAYER_ID GetWinner ( PLAYER_ID plr ) const { return m_winner; }

		void SetN_Act1p ( int n ) { m_n_act_1p = n; }
		int GetN_Act1p () const { return m_n_act_1p; }

		void SetN_Act2p ( int n ) { m_n_act_2p = n; }
		int GetN_Act2p () const { return m_n_act_2p; }
	};

	using P_Param = shared_ptr < Param >;


}	//namespace GAME

