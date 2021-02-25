//=================================================================================================
//
// DispMainImage ヘッダファイル
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

	class DispMainImage : public TASK_VEC
	{
	public:
		DispMainImage ();
		DispMainImage ( const DispMainImage & rhs ) = delete;
		~DispMainImage ();
	};


}	//namespace GAME


