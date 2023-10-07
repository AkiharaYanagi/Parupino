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
	using P_FtgMain = shared_ptr < FtgMain >;

	class YesNo_Menu;
	using P_YesNo_Menu = shared_ptr < YesNo_Menu >;

	//===================================================
	//メニュ項目
	class YNM_Item_Yes : public MenuItem
	{
		P_FtgMain	mp_FtgMain;

	public:
		void Do ();	//決定　タイトルに戻る
		void SetpFtgMain ( P_FtgMain p ) { mp_FtgMain = p; }
	};
	using P_YNM_Item_Yes = shared_ptr < YNM_Item_Yes >;


	class YNM_Item_No : public MenuItem
	{
		P_YesNo_Menu		mp_parent;
	public: 
		void Do ();	//キャンセル 自メニュを閉じる
		void SetpParent ( P_YesNo_Menu p ) { mp_parent = p; }
	};
	using P_YNM_Item_No = shared_ptr < YNM_Item_No >;



	//===================================================
	//メニュ
	class YesNo_Menu : public Menu, public enable_shared_from_this < YesNo_Menu >
	{
		P_PrmRect		m_bg;
		P_MenuString	m_grpStr_yesno;
		P_GrpAcv		m_cursor;

		P_MenuString	m_grpStr_yes;
		P_MenuString	m_grpStr_no;

		//メニュ項目
		P_YNM_Item_Yes	m_yes;
		P_YNM_Item_No	m_no;

	public:
		YesNo_Menu ();
		YesNo_Menu ( const YesNo_Menu & rhs ) = delete;
		~YesNo_Menu ();

		void Load ();
		void Init ();
		void Move ();

		void On ();
		void Off ();

		void SetpParent ( P_FtgMain p );
	};

//	using P_YesNo_Menu = shared_ptr < YesNo_Menu >;



}	//namespace GAME

