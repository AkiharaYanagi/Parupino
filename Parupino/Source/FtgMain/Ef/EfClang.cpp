//=================================================================================================
//
//	EfClang ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfClang.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfClang::EfClang ()
	{
		AddTexture ( _T ( "Ef_Clang.png" ) );
	}

	EfClang::~EfClang ()
	{
	}

	void EfClang::On ( VEC2 center )
	{
		SetpDispBase ( G_BASE_POS () );
		SetPos ( center );
		SetFadeOut ( 15 );
		SetValid ( true );
		GrpEf::On ();
	}
}
