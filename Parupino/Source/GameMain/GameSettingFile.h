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
	class GameSettingFile
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using _GmStgFl = GameSettingFile;
		using _UP_GmStgFl = unique_ptr < _GmStgFl >;
		static _UP_GmStgFl	m_inst;		//シングルトンインスタンス
		GameSettingFile ();		//private コンストラクタで通常の実体化は禁止
	public:
		~GameSettingFile ();	//デストラクタはunique_ptrのためpublic
		static void Create () { if ( ! m_inst ) { m_inst = _UP_GmStgFl ( new _GmStgFl () ); } }
		static _UP_GmStgFl & Inst () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------

		//ゲーム内設定
		bool	m_demo;				//デモモード
		bool	m_startBattle;		//バトルから開始
		bool	m_training;			//トレーニングモード
		bool	m_input1pPlayer;	//入力(true:プレイヤー, false:CPU)
		bool	m_input2pPlayer;
		CHARA_NAME	m_name1p;		//選択キャラ
		CHARA_NAME	m_name2p;

		void	SetDefault ();

	public:

		//値の取得
		bool GetDemo () const { return m_demo; }
		bool GetStartBattle () const { return m_startBattle; }
		bool GetTraining () const { return m_training; }

		bool GetbInput1pPlayer () const { return m_input1pPlayer; }
		bool GetbInput2pPlayer () const { return m_input2pPlayer; }

		CHARA_NAME GetName1p () const { return m_name1p; }
		CHARA_NAME GetName2p () const { return m_name2p; }
	};

	using UP_GmStgFl = unique_ptr < GameSettingFile >;

//シングルトンアクセス用
#define GM_STG	GameSettingFile::Inst

}	//namespace GAME

