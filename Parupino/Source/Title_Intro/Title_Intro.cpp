//=================================================================================================
//
//	タイトル イントロ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_Intro.h"
#include "../Introduction/Introduction.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Title_Intro::Title_Intro ()
	{
		m_menuActor = make_shared < Title_MenuActor > ();
		AddpTask ( m_menuActor );
	}

	Title_Intro::~Title_Intro ()
	{
	}

	void Title_Intro::Load ()
	{
		//アクタに親ポインタを設定
		m_menuActor->SetwpTitle_Intro ( shared_from_this () );

		//遷移先を自身に設定
		m_pTransit = shared_from_this ();

		Scene::Load ();
	}

	void Title_Intro::ParamInit ()
	{
	}

	P_GameScene Title_Intro::Transit ()
	{
#if 0
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( _P1_BTN0 ) )
		{
			//共通グラフィック配列をクリア
			GRPLST_CLEAR ();

			P_GameScene p = make_shared < Introduction > ();
			GRPLST_LOAD ();
			return p;
		}
		return shared_from_this ();
#endif // 0
		return m_pTransit;
	}

	//シーン状態遷移
	void Title_Intro::Transit_Intro ()
	{
		GRPLST_CLEAR ();
		m_pTransit = make_shared < Introduction > ();
		GRPLST_LOAD ();
	}


}	//namespace GAME

