//=================================================================================================
//
// DispChara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispChara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DispChara::DispChara ()
	{
		m_mainImage = make_shared < DispMainImage > ();
		AddpTask ( m_mainImage );

		m_dispRect = make_shared < DispRect > ();
		AddpTask ( m_dispRect );

		m_frontEnd = make_shared < DispFrontEnd > ();
		AddpTask ( m_frontEnd );

		//影
		m_grpShadow = make_shared < GrpAcv > ();
		m_grpShadow->AddTexture ( _T("shadow.png") );
		m_grpShadow->SetZ ( Z_SHADOW );
		AddpTask ( m_grpShadow );
		GRPLST_INSERT_MAIN ( m_grpShadow );

#if 0
		m_test = make_shared < PrmRect > ();
		m_test->SetZ ( Z_SYS );
		AddpTask ( m_test );
		GRPLST_INSERT_MAIN ( m_test );
#endif // 0
		m_testAcv = make_shared < GrpAcv > ();
		m_testAcv->SetZ ( Z_SYS );
		AddpTask ( m_testAcv );
		GRPLST_INSERT_MAIN ( m_testAcv );
	}

	DispChara::~DispChara ()
	{
	}

	//プレイヤIDを設定
	void DispChara::LoadPlayer ( PLAYER_ID playerID )
	{ 
		m_frontEnd->LoadPlayer ( playerID );
		m_dispInput.LoadPlayer ( playerID );
	}

	//キャラデータを設定
	void DispChara::SetpChara ( const P_Chara pChara )
	{
		m_mainImage->SetpChara ( pChara );
	}

	//枠データを設定
	void DispChara::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect->SetCharaRect ( pCharaRect );
	}

	//毎フレームにおけるメインイメージの更新
	void DispChara::UpdateMainImage ( P_Script pScript, VEC2 posChara, bool dirRight )
	{
		//メイン
		m_mainImage->UpdateMainImage ( pScript, posChara, dirRight );

		//影
		float fDir = dirRight ? ( 1.f ) : ( -1.f );		//向き
		float bx = G_Ftg::inst ()->GetPosMutualBase ().x;	//基準位置
		VEC2 vecImgShadow = VEC2 ( bx, 0 ) + posChara + VEC2 ( -128 + fDir * 12, 0 );
		vecImgShadow.y = -32.f + 1.f * PLAYER_BASE_Y;
		m_grpShadow->SetPos ( vecImgShadow );

		//枠
		m_dispRect->Update ();
	}


	//ゲージ類更新
	void DispChara::UpdateGauge ( BtlParam btlPrm )
	{
		m_frontEnd->UpdateGauge ( btlPrm );
	}


}	//namespace GAME

