//=================================================================================================
//
//	FtgMain ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "Fighting.h"
#include "Menu/PauseMenu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class TestDraw : public PrmRect
	{ public: void Draw () { PrmRect::Draw (); } };

	class FtgMain : public Scene, public enable_shared_from_this < FtgMain >
	{
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//遷移可能な次のシーン

		//===========================================================

		//戦闘
		P_FTG			m_fighting;

		//ポーズメニュ
		P_PauseMenu		m_pauseMenu;

		//ロード中
//		P_PrmRect		m_rectLoad;
		shared_ptr < TestDraw >		m_rectLoad;
		UINT			m_wait;

		P_GrpStr		m_NowLoading;

	public:
		FtgMain ();
		FtgMain ( const FtgMain & rhs ) = delete;
		~FtgMain ();

		void Load ();
		void ParamInit ();
		void Move ();

		P_GameScene Transit ();

		void Transit_Title ();
		void Resume_Fighting ();
		void Transit_Result ();
	};

	using P_FtgMain = shared_ptr < FtgMain >;


}	//namespace GAME


