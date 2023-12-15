//=================================================================================================
//
//	Training ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "../FtgMain/Fighting.h"
#include "../FtgMain/Menu/PauseMenu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Training : public Scene, public enable_shared_from_this < Training >
	{
#if 0
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//遷移可能な次のシーン
		//===========================================================
#endif // 0

		//戦闘
		P_FTG			m_fighting;

		P_GrpAcv		m_training;		//トレーニング表示

		//ロード中
		P_PrmRect		m_rectLoad;
		UINT			m_wait;
		P_GrpStr		m_NowLoading;

		//ポーズメニュ
		P_PauseMenu		m_pauseMenu;

		static const float	BX;
		static const float	BY;

	public:
		Training ();
		Training ( const Training & rhs ) = delete;
		~Training ();

		void ParamInit ();
		void Load ();
		void Init ();
		void Move ();

		P_GameScene Transit ();

	private:
//		void Pause ();
	};


}	//namespace GAME


