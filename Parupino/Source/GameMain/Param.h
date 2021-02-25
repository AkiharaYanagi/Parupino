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
		bool			m_demo;			//デモモードかどうか
		bool			m_battleStart;	//バトルからスタート
		bool			m_training;		//トレーニングモード

		MUTCH_MODE		m_mutchMode;	//対戦種類
//		PLAYER_MODE		m_mode1P;		//１Pゲームモード
//		PLAYER_MODE		m_mode2P;		//２Pゲームモード

		CHARA_NAME		m_charaName1p;	//１Pキャラ名
		CHARA_NAME		m_charaName2p;	//２Pキャラ名

	public:
		Param ();
		Param ( const Param & rhs );	//コピー可能
		~Param ();

		//デモ
		void SetDemo ( bool b ) { m_demo = b; }
		bool GetDemo () const { return m_demo; }

		//バトルから開始
		void SetBattleStart ( bool b ) { m_battleStart = b; }
		bool GetBattleStart () const { return m_battleStart; }

		//トレーニングモード
		void SetTraining ( bool b ) { m_training = b; }
		bool GetTraining () const { return m_training; }

		//対戦種類
		MUTCH_MODE	GetMutchMode () const { return m_mutchMode; }
		void SetMutchMode ( MUTCH_MODE m ) { m_mutchMode = m; }
		void SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p );
		PLAYER_MODE GetMode ( PLAYER_ID id ) const;

		//キャラ名
		CHARA_NAME GetCharaName ( PLAYER_ID id ) const
		{ 
			return ( PLAYER_ID_1 == id ) ? m_charaName1p : m_charaName2p; 
		}
		void SetCharaName1p ( CHARA_NAME name ) { m_charaName1p = name; }
		CHARA_NAME GetCharaName1p () const { return m_charaName1p; }
		void SetCharaName2p ( CHARA_NAME name ) { m_charaName2p = name; }
		CHARA_NAME GetCharaName2p () const { return m_charaName2p; }

		void SetRandomChara ();
		void SetRandomChara2p ();
		 
	};

	using P_Param = shared_ptr < Param >;


}	//namespace GAME

