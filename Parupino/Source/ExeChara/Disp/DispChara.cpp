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

		m_dispInput = make_shared < DispInput > ();
		AddpTask ( m_dispInput );

		//影
		m_grpShadow = make_shared < GrpAcv > ();
		m_grpShadow->AddTexture ( _T("shadow.png") );
		m_grpShadow->SetZ ( Z_SHADOW );
		AddpTask ( m_grpShadow );
		GRPLST_INSERT_MAIN ( m_grpShadow );

		//プレイヤー表示
		m_grpPlayer1P = make_shared < GrpAcv > ();
		m_grpPlayer1P->AddTexture ( _T ( "Player_1P.png" ) );
		m_grpPlayer1P->SetValid ( F );
		m_grpPlayer1P->SetZ ( Z_SYS - 0.001f );
		AddpTask ( m_grpPlayer1P );
		GRPLST_INSERT_MAIN ( m_grpPlayer1P );

		m_grpPlayer2P = make_shared < GrpAcv > ();
		m_grpPlayer2P->AddTexture ( _T ( "Player_2P.png" ) );
		m_grpPlayer2P->SetValid ( F );
		m_grpPlayer2P->SetZ ( Z_SYS - 0.001f );
		AddpTask ( m_grpPlayer2P );
		GRPLST_INSERT_MAIN ( m_grpPlayer2P );

		m_grpPlayerCOM = make_shared < GrpAcv > ();
		m_grpPlayerCOM->AddTexture ( _T ( "Player_CPU.png" ) );
		m_grpPlayerCOM->SetValid ( F );
		m_grpPlayerCOM->SetZ ( Z_SYS - 0.001f );
		AddpTask ( m_grpPlayerCOM );
		GRPLST_INSERT_MAIN ( m_grpPlayerCOM );
	}

	DispChara::~DispChara ()
	{
	}

	//プレイヤIDを設定
	void DispChara::LoadPlayer ( PLAYER_ID playerID )
	{ 
		m_frontEnd->LoadPlayer ( playerID );
		m_dispInput->LoadPlayer ( playerID );

		if ( PLAYER_ID_1 == playerID )
		{
			m_grpPlayer1P->SetValid ( T );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_grpPlayer2P->SetValid ( T );
		}
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
		vecImgShadow.y = -32.f + 1.f * PLAYER_BASE_Y;	//y方向のみ指定
		m_grpShadow->SetPos ( vecImgShadow );

		//枠
		m_dispRect->Update ();

		//プレイヤー表示
		VEC2 vecImgPlayer = VEC2 ( bx, 0 ) + posChara + VEC2 ( -32.f , 0 );
		vecImgPlayer.y = 32.f + 1.f * PLAYER_BASE_Y;	//y方向のみ指定
		m_grpPlayer1P->SetPos ( vecImgPlayer );
		m_grpPlayer2P->SetPos ( vecImgPlayer );
		m_grpPlayerCOM->SetPos ( vecImgPlayer );
	}


	//ゲージ類更新
	void DispChara::UpdateGauge ( BtlParam btlPrm )
	{
		m_frontEnd->UpdateGauge ( btlPrm );
	}


}	//namespace GAME

