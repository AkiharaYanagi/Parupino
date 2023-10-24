//=================================================================================================
//
//	YesNo_Menu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Menu.h"
#include "PauseMenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class FtgMain;
	using WP_FtgMain = weak_ptr < FtgMain >;

	class YesNo_Menu;
	using WP_YesNo_Menu = weak_ptr < YesNo_Menu >;

	//===================================================
	//メニュ項目
	class YNM_Item_Yes : public Menu
	{
		WP_FtgMain	mwp_FtgMain;

	public:
		void Decide ();	//決定　タイトルに戻る
		void SetpFtgMain ( WP_FtgMain p ) { mwp_FtgMain = p; }
	};
	using P_YNM_Item_Yes = shared_ptr < YNM_Item_Yes >;


	class YNM_Item_No : public Menu
	{
	public: 
		void Decide ();	//キャンセル 自メニュを閉じる
	};
	using P_YNM_Item_No = shared_ptr < YNM_Item_No >;



	//===================================================
	//メニュ
	class YesNo_Menu : public Menu
	{
		P_PrmRect		m_bg;
		P_MenuString	m_grpStr_yesno;
		P_GrpAcv		m_cursor;

		P_MenuString	m_grpStr_yes;
		P_MenuString	m_grpStr_no;

		//メニュ項目
		P_YNM_Item_Yes	m_yes;
		P_YNM_Item_No	m_no;

		//開始後1[F]待つ
		bool			m_wait;

	public:
		YesNo_Menu ();
		YesNo_Menu ( const YesNo_Menu & rhs ) = delete;
		~YesNo_Menu ();

		void Load ();
		void Init ();
		void Move ();

		void On ();
		void Off ();

		void SetwpParent ( WP_FtgMain p );
	};

	using P_YesNo_Menu = shared_ptr < YesNo_Menu >;



}	//namespace GAME

