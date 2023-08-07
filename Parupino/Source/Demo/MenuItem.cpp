//=================================================================================================
//
//	MenuItem ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "MenuItem.h"
#include "DemoMain.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MenuItem::MenuItem ()
	{
		m_grp = make_shared < GrpAcv > ();
		m_grp->SetZ ( 0.1f );
	}

	MenuItem::~MenuItem ()
	{
	}

	//-------------------------------------------

	Menu_1v2::Menu_1v2 ()
	{
		m_grp->AddTexture ( _T ( "menu\\1P_VS_2P.png" ) );
//		m_grp->AddTexture ( _T ( "Demo_Attack.png" ) );
		GRPLST_INSERT ( m_grp );
	}

	void Menu_1v2::Do ()
	{
		m_demoMain->To_1v2 ();
	}

	Menu_1vc::Menu_1vc ()
	{
		m_grp->AddTexture ( _T ( "menu\\1P_VS_CPU.png" ) );
		GRPLST_INSERT ( m_grp );
	}

	void Menu_1vc::Do ()
	{
	}

	Menu_cv2::Menu_cv2 ()
	{
		m_grp->AddTexture ( _T ( "menu\\CPU_VS_2P.png" ) );
		GRPLST_INSERT ( m_grp );
	}

	void Menu_cv2::Do ()
	{

	}

	Menu_cvc::Menu_cvc ()
	{
		m_grp->AddTexture ( _T ( "menu\\CPU_VS_CPU.png" ) );
		GRPLST_INSERT ( m_grp );
	}

	void Menu_cvc::Do ()
	{

	}


}	//namespace GAME

