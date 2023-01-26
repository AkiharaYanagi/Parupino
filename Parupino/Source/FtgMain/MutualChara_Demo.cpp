//=================================================================================================
//
//	MutualChara_Demo ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "MutualChara_Demo.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MutualChara_Demo::MutualChara_Demo ()
	{
		//キャラ
		m_exeChara1 = make_shared < ExeChara_Demo > ( PLAYER_ID_1 );
		m_exeChara2 = make_shared < ExeChara_Demo > ( PLAYER_ID_2 );

		AddpTask ( m_exeChara1 );
		AddpTask ( m_exeChara2 );
	}

	MutualChara_Demo::~MutualChara_Demo ()
	{
	}

	void MutualChara_Demo::ParamInit ( P_Param pParam )
	{
		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
	}


	void MutualChara_Demo::Start ()
	{
		m_exeChara1->Init ();
		m_exeChara2->Init ();
	}


	//■#########################################################
	//■
	//■	スクリプトの毎フレーム処理
	//■
	//■#########################################################
	void MutualChara_Demo::Conduct ()
	{
		//◆スクリプト前処理(入力、移動など)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//◆スクリプト後処理(グラフィック位置など)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//---------------------------------------------------
		//画面表示の基準位置を決定
		VEC2 pos1p = m_exeChara1->GetPos ();
		VEC2 pos2p = m_exeChara2->GetPos ();
		G_Ftg::inst ()->CulcPosMutualBase ( pos1p, pos2p );
	}
	//■#########################################################


}	//namespace GAME

