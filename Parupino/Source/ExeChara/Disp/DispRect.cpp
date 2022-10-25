//=================================================================================================
//
// DispRect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispRect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DispRect::DispRect () 
	{
		//枠表示を初期化
		m_pvpGrpCRect = make_shared < VP_PrmRect > ();
		m_pvpGrpARect = make_shared < VP_PrmRect > ();
		m_pvpGrpHRect = make_shared < VP_PrmRect > ();
		m_pvpGrpORect = make_shared < VP_PrmRect > ();

		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			P_PrmRect pCRect = make_shared < PrmRect > ();
			pCRect->SetAllColor ( RECT_COLOR_C );
//			pCRect->SetRect ( 100, 100, 200, 150 );
			pCRect->SetZ ( Z_SYS );
			pCRect->Load ();
			m_pvpGrpCRect->push_back ( pCRect );
			GRPLST_INSERT ( pCRect );

			P_PrmRect pARect = make_shared < PrmRect > ();
			pARect->SetAllColor ( RECT_COLOR_A );
			pARect->SetZ ( Z_SYS );
			pARect->Load ();
			pARect->Move ();
			m_pvpGrpARect->push_back ( pARect );
			GRPLST_INSERT ( pARect );

			P_PrmRect pHRect = make_shared < PrmRect > ();
			pHRect->SetAllColor ( RECT_COLOR_H );
			pHRect->SetZ ( Z_SYS );
			pHRect->Load ();
			pHRect->Move ();
			m_pvpGrpHRect->push_back ( pHRect );
			GRPLST_INSERT ( pHRect );

			P_PrmRect pORect = make_shared < PrmRect > ();
			pORect->SetAllColor ( RECT_COLOR_O );
			pORect->SetZ ( Z_SYS );
			pORect->Load ();
			pORect->Move ();
			m_pvpGrpORect->push_back ( pORect );
			GRPLST_INSERT ( pORect );
		}
		InitRect ();

		//----------------------------------------------------
		//@info		動的に追加するときは明示的にLoad()が必要
		//----------------------------------------------------
	}

	DispRect::~DispRect ()
	{
		//終了時にグラフィックタスクを外す
		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			GRPLST_ERASE ( (*m_pvpGrpCRect)[i] );
			GRPLST_ERASE ( (*m_pvpGrpARect)[i] );
			GRPLST_ERASE ( (*m_pvpGrpHRect)[i] );
			GRPLST_ERASE ( (*m_pvpGrpORect)[i] );
		}
		//解放
		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			m_pvpGrpCRect->clear ();
			m_pvpGrpARect->clear ();
			m_pvpGrpHRect->clear ();
			m_pvpGrpORect->clear ();
		}
	}

	//実効枠設定
	void DispRect::SetCharaRect ( P_CharaRect pCharaRect )
	{
		SetCRect ( pCharaRect->GetpvCRect () );
		SetARect ( pCharaRect->GetpvARect () );
		SetHRect ( pCharaRect->GetpvHRect () ); 
		SetORect ( pCharaRect->GetpvORect () );
	}

	//表示枠の初期化
	void DispRect::InitRect ()
	{
		for ( P_PrmRect p : * m_pvpGrpCRect ) { p->SetZero (); }
		for ( P_PrmRect p : * m_pvpGrpARect ) { p->SetZero (); }
		for ( P_PrmRect p : * m_pvpGrpHRect ) { p->SetZero (); }
		for ( P_PrmRect p : * m_pvpGrpORect ) { p->SetZero (); }
	}

	//表示
	void DispRect::OnRect ()
	{
		for ( P_PrmRect p : * m_pvpGrpCRect ) { p->SetValid ( true ); }
		for ( P_PrmRect p : * m_pvpGrpARect ) { p->SetValid ( true ); }
		for ( P_PrmRect p : * m_pvpGrpHRect ) { p->SetValid ( true ); }
		for ( P_PrmRect p : * m_pvpGrpORect ) { p->SetValid ( true ); }
	}

	//非表示
	void DispRect::OffRect ()
	{
		for ( P_PrmRect p : * m_pvpGrpCRect ) { p->SetValid ( false ); }
		for ( P_PrmRect p : * m_pvpGrpARect ) { p->SetValid ( false ); }
		for ( P_PrmRect p : * m_pvpGrpHRect ) { p->SetValid ( false ); }
		for ( P_PrmRect p : * m_pvpGrpORect ) { p->SetValid ( false ); }
	}

	//実効枠から表示枠へ設置
	void DispRect::SetGrpRect ( PVP_PrmRect pvpGrpRect, PV_RECT pvRect )
	{
		float bx = G_BASE_POS().x;	//基準位置

		UINT i = 0;
		for ( P_PrmRect p : * pvpGrpRect )
		{
			RECT r = pvRect->at ( i );
			float x = bx + r.left;
			float y = (float)r.top;
			float w = (float)( r.right - r.left );
			float h = (float)( r.bottom - r.top );
			p->SetRect ( x, y, w, h );
			++ i;
		}
	}

}	//namespace GAME

