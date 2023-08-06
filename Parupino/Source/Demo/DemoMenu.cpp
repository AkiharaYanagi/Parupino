//=================================================================================================
//
//	DemoMenu ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DemoMenu.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DemoMenu::DemoMenu ()
	{
		//背景
		m_BG = make_shared < PrmRect > ();
		m_BG->SetAllColor ( 0xa0000000 );
		m_BG->SetSize ( 1000, 600 );
		m_BG->SetPos ( ( GAME_WINDOW_WIDTH - 1000 ) * 0.5f, 200 );
		m_BG->SetZ ( 0.2f );
		AddpTask ( m_BG );

		//デモ表示
		OutlineFont::Inst ()->SetParam ( 80, 1, 3 );
		OutlineFont::Inst ()->SetFontFace ( _T ( "メイリオ" ) );
		m_strDemo = make_shared < Str > ();
		m_strDemo->SetStr ( _T ( "Demo" ) );
		m_strDemo->GetSize ();
		m_strDemo->SetPos ( VEC2 ( 500, 200 ) );
		AddpTask ( m_strDemo );


		//選択
		float x = 500;
		float z = 0.1f;

#if 0
		m_1p_vs_2p = make_shared < GrpAcv > ();
		m_1p_vs_2p->AddTexture ( _T ( "menu\\1P_VS_2P.png" ) );
		m_1p_vs_2p->SetPos ( VEC2 ( x, 300 ) );
		m_1p_vs_2p->SetZ ( z );
		AddpTask ( m_1p_vs_2p );

		m_1p_vs_cpu = make_shared < GrpAcv > ();
		m_1p_vs_cpu->AddTexture ( _T ( "menu\\1P_VS_CPU.png" ) );
		m_1p_vs_cpu->SetPos ( VEC2 ( x, 400 ) );
		m_1p_vs_cpu->SetZ ( z );
		AddpTask ( m_1p_vs_cpu );

		m_cpu_vs_2p = make_shared < GrpAcv > ();
		m_cpu_vs_2p->AddTexture ( _T ( "menu\\CPU_VS_2P.png" ) );
		m_cpu_vs_2p->SetPos ( VEC2 ( x, 500 ) );
		m_cpu_vs_2p->SetZ ( z );
		AddpTask ( m_cpu_vs_2p );

		m_cpu_vs_cpu = make_shared < GrpAcv > ();
		m_cpu_vs_cpu->AddTexture ( _T ( "menu\\CPU_VS_CPU.png" ) );
		m_cpu_vs_cpu->SetPos ( VEC2 ( x, 600 ) );
		m_cpu_vs_cpu->SetZ ( z );
		AddpTask ( m_cpu_vs_cpu );
#endif // 0



		m_menu_1v2 = make_shared < Menu_1v2 > ();
		mv_menu.push_back ( m_menu_1v2 );
		m_menu_1vc = make_shared < Menu_1vc > ();
		mv_menu.push_back ( m_menu_1vc );
		m_menu_cv2 = make_shared < Menu_cv2 > ();
		mv_menu.push_back ( m_menu_cv2 );
		m_menu_cvc = make_shared < Menu_cvc > ();
		mv_menu.push_back ( m_menu_cvc );

		int i = 0;
		for ( P_MenuItem p : mv_menu )
		{
			p->SetPos ( VEC2 ( x, 300.f + 100.f * i ++ ) );
			AddpTask ( p );
		}

		//最初の選択
		m_selectedItem = m_menu_1v2;



		//矢印
		m_arrow = make_shared < GrpAcv > ();
		m_arrow->AddTexture ( _T ( "menu\\arrow.png" ) );
		m_arrow->SetPos ( VEC2 ( x - 100, 300 ) );
		m_arrow->SetZ ( z );
		AddpTask ( m_arrow );
	}

	DemoMenu::~DemoMenu ()
	{
	}

	void DemoMenu::Init ()
	{
		TASK_VEC::Init ();
	}

	void DemoMenu::Move ()
	{
		if ( PUSH_KEY ( P1_DOWN ) )
		{
			float x = m_arrow->GetPos ().x;
			float y = m_arrow->GetPos ().y;

			m_arrow->SetPos ( x, y + 100 );
		}

		TASK_VEC::Move ();
	}


}	//namespace GAME

