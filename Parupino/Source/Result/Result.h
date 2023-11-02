//=================================================================================================
//
//	Result ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//public 継承 enable_shared_from_this　＜ T >

	class Result : public Scene, public enable_shared_from_this < Result >
	{
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_GameScene		mwp_This;
		P_GameScene			mp_Transit;		//遷移可能な次のシーン

		//===========================================================
		P_GrpAcv		m_bg;

		P_GrpStr		m_affinity;		//相性(アフィニティ)

		P_GrpStr		m_strNAct1p;
		P_GrpStr		m_strNAct2p;

		P_GrpStr		m_win_lose_1p;
		P_GrpStr		m_win_lose_2p;

	public:
		Result ();
		Result ( const Result& rhs ) = delete;
		~Result ();

		void ParamInit ();
		void Load ();
		void Init ();
		void Move ();

		P_GameScene Transit ();

	private:

		P_GrpStr	MakeStr ( LPCTSTR str, VEC2 pos );
	};


}	//namespace GAME


