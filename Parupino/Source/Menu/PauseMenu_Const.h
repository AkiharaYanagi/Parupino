//=================================================================================================
//
//	PauseMenu_Const
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------
	//メニュ 描画Z位置(後:1.f ～ 0.0f:前)

	//@info 大きい方が奥

#if 0
	constexpr float Z_BG		= 0.9f;		//背景
	constexpr float Z_SHADOW	= 0.8f;		//影
	constexpr float Z_EFB		= 0.7f;		//背面エフェクト
	constexpr float Z_CH		= 0.5f;		//キャラクタ(グラフィックのデフォルト位置)
	constexpr float Z_EFF		= 0.4f;		//前面エフェクト
	constexpr float Z_SYS		= 0.3f;		//バトルシステム表示
#endif // 0



#if 0
	constexpr float Z_MENU		= 0.2f;		//メニュ
#endif // 0

	constexpr float Z_MENU_BG		= Z_MENU - 0.01f;
	constexpr float Z_MENU_STR		= Z_MENU - 0.02f;
	constexpr float Z_MENU_YN_BG	= Z_MENU - 0.03f;
	constexpr float Z_MENU_YN_STR	= Z_MENU - 0.04f;
	constexpr float Z_MENU_KI_BG	= Z_MENU - 0.05f;
	constexpr float Z_MENU_KI_STR	= Z_MENU - 0.06f;


#if 0
	constexpr float Z_FADE		= 0.1f;		//フェード
#endif // 0

	//@info 小さい方が手前

	//--------------------------------------

}	//namespace GAME

