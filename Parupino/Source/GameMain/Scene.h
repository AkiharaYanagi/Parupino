//=================================================================================================
//
// シーンヘッダ
//		ゲームシーンを用いた状態遷移
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameSettingFile.h"
#include "Param.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//ゲーム内定義のパラメータを扱う

	//ゲーム状態
	class Scene : public GameScene
	{
	public:
		Scene ();
		Scene ( const Scene & rhs ) = delete;
		~Scene ();

		void SetpParam ( P_Param&& pParam )
		{
			GameScene::SetpParam ( pParam ); 
		}
		P_Param GetpParam ()
		{
			P_GameParam pgp = GameScene::GetpParam (); 
			P_Param pp = dynamic_pointer_cast < Param > ( pgp );
			return pp; 
		}
	};

	using P_Scene = shared_ptr < Scene >;



	//ゲーム状態遷移管理
	class SceneManager	: public GameSceneManager
	{
//		shared_ptr < GameScene >	m_pScene;	//現在のシーン
		P_Param		m_pParam;	//シーン共通パラメータ

	public:
		SceneManager ();
		SceneManager ( const SceneManager& rhs ) = delete;
		~SceneManager ();

		//シーン共通パラメータ
		void SetpParam ( P_Param&& pParam ) { m_pParam = pParam; }
		P_Param GetpParam () { return m_pParam; }
	};


}	//namespace GAME

