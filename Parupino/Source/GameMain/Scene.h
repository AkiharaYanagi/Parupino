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
	//ゲーム内定義のパラメータ(Param)を共通で扱う

	//ゲーム場面
	class Scene : public GameScene, public enable_shared_from_this < Scene >
	{
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//遷移可能な次のシーン

		//===========================================================
		bool	m_bTransit;

	public:
		Scene ();
		Scene ( const Scene & rhs ) = delete;
		~Scene ();

		void Load ();
		P_GameScene Transit ();


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

		WP_GameScene GetwpGameScene () { return mwp_This; }

		//メニュ用
		void Transit_Title ();		//タイトルに戻る
//		void Resume_Fighting ();	//ゲームに戻る
	};

	using P_Scene = std::shared_ptr < Scene >;


#if 0
	//test
	class TestScene : public Scene, public enable_shared_from_this < TestScene >
	{
	public:
		void ParamInit () {}
		P_GameScene Transit () { return shared_from_this (); }
	};
#endif // 0



	//==================================================================
	//ゲーム状態遷移管理
	class SceneManager	: public GameSceneManager
	{
//		std::shared_ptr < GameScene >	m_pScene;	//現在のシーン
		P_Param		m_pParam;	//シーン共通パラメータ

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

