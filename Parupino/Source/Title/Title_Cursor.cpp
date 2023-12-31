//=================================================================================================
//
//	タイトル カーソル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_Cursor.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float Title_Cursor::OMEGA = D3DX_2PI / ( 1 * 60.f );	//[rad/F]


	Title_Cursor::Title_Cursor ()
	{
		AddTexture ( _T ( "title_cursor.png" ) );
		SetScalingCenter ( VEC2 ( 64.f, 32.f ) );
		SetScaling ( VEC2 ( 1.f, 1.f ) );

		m_count = 0;
		m_dir = 1.f;
	}

	Title_Cursor::~Title_Cursor ()
	{
	}

	void Title_Cursor::Move ()
	{
		float f = sinf ( OMEGA * m_count );
		SetScaling ( VEC2 ( 1.f * m_dir, f ) );

		++ m_count;
		if ( OMEGA * m_count > D3DX_2PI ) { m_count = 0; }

		GrpAcv::Move ();
	}


	void Title_Cursor::Off ()
	{
		SetValid ( F );
	}

	void Title_Cursor::On ()
	{
		SetValid ( T );
	}


}	//namespace GAME

