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
		bool	m_bTransit;

	public:
		Scene ();
		Scene ( const Scene & rhs ) = delete;
		~Scene ();

		//共通パラメータ
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


		//遷移
		bool GetTransit () const { return m_bTransit; }
		void SetTransit ( bool b ) { m_bTransit = b; }
	};

	using P_Scene = shared_ptr < Scene >;


	//test
	class TestScene : public Scene, public enable_shared_from_this < TestScene >
	{
	public:
		void ParamInit () {}
		P_GameScene Transit () { return shared_from_this (); }
	};



	//==================================================================
	//ゲーム状態遷移管理
	class SceneManager	: public GameSceneManager
	{
//		shared_ptr < GameScene >	m_pScene;	//現在のシーン
		P_Param		m_pParam;	//シーン共通パラメータ

		P_FadeRect	m_fade;		//フェード

	public:
		SceneManager ();
		SceneManager ( const SceneManager& rhs ) = delete;
		~SceneManager ();

		void Move ();

		//シーン共通パラメータ
		void SetpParam ( P_Param&& pParam ) { m_pParam = pParam; }
		P_Param GetpParam () { return m_pParam; }
	};


}	//namespace GAME

