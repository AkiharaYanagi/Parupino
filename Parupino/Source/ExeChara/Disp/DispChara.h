//=================================================================================================
//
// DispChara ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/G_Ftg.h"
#include "../../CharaData/Chara.h"
#include "DispMainImage.h"
#include "DispRect.h"
#include "../CharaRect.h"
#include "DispFrontEnd.h"
#include "DispInput.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispChara
	{
		DispMainImage	m_mainImage;	//メインイメージ
		DispRect		m_dispRect;		//枠
		P_GrpAcv		m_grpShadow;	//影
		DispFrontEnd	m_frontEnd;		//フロントエンド
		DispInput		m_dispInput;	//入力表示

	public:
		DispChara ();
		DispChara ( const DispChara & rhs ) = delete;
		~DispChara ();

		//キャラを設定する
		void SetpChara ( const P_Chara pChara );

		//メインイメージの更新
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );

		//表示枠設定
		void SetpCharaRect ( P_CharaRect pCharaRect );

		//枠表示ON
		void OnRect () { m_dispRect.OnRect (); }
		//枠表示OFF
		void OffRect () { m_dispRect.OffRect (); }

		//ゲージ類の表示部のみ初期化
		void LoadPlayer ( PLAYER_ID playerID );

		//ゲージ類更新
//		void UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance );
		void UpdateGauge ( BtlParam btlPrm );

		//入力更新
		void UpdateInput ( P_CharaInput p ) { m_dispInput.UpdateInput ( p ); }
	};

}	//namespace GAME


