//=================================================================================================
//
//	DemoMenu ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "MenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DemoMenu : public TASK_VEC
	{
		//背景
		P_PrmRect		m_BG;

		//デモ表示
		P_Str			m_strDemo;

		P_GrpAcv		m_1p_vs_2p;
		P_GrpAcv		m_1p_vs_cpu;
		P_GrpAcv		m_cpu_vs_2p;
		P_GrpAcv		m_cpu_vs_cpu;


		P_MenuItem		m_selectedItem;
		VP_MenuItem		mv_menu;
		P_Menu_1v2		m_menu_1v2;
		P_Menu_1vc		m_menu_1vc;
		P_Menu_cv2		m_menu_cv2;
		P_Menu_cvc		m_menu_cvc;


		P_GrpAcv		m_arrow;

	public:
		DemoMenu ();
		DemoMenu ( const DemoMenu & rhs ) = delete;
		~DemoMenu ();

		void Init ();
		void Move ();
	};

	using P_DemoMenu = shared_ptr < DemoMenu >;


}	//namespace GAME


