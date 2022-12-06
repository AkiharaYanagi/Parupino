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
	};

	using P_Param = shared_ptr < Param >;


}	//namespace GAME

