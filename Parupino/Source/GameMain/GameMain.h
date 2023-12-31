//=================================================================================================
//
// ゲームメイン　ヘッダ
//			ゲーム内容における主となる挙動を記述する。ヘッダのみ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameMainBase.h"

//ゲーム内容ヘッダファイルのインクルード
#include "Scene.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//ゲームメインクラス
	class GameMain	: public GameMainBase
	{
		//ゲームに用いるオブジェクトクラス
		std::shared_ptr < SceneManager >		m_pTask;

	public:
		GameMain()
		{
			Make ();				//タスク生成
			AddpTask ( m_pTask );	//タスクの追加
		}
		GameMain(const GameMain& rhs) = delete;
		~GameMain () {}

		//タスク生成
		void Make ()
		{
			m_pTask = make_shared < SceneManager > ();
		}
	};


}	//namespace GAME

