//=================================================================================================
//
//	Action ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Action.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Action::Action ()
		: m_cost ( 0 ), m_category ( AC_STAND), m_posture ( AP_STAND )
	{
	}

	Action::~Action ()
	{
	}


}	//namespace GAME

