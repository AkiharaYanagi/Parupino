//=================================================================================================
//
// EffectGenerate ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EffectGenerate.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EffectGenerate::EffectGenerate ()
		:	m_id ( 0 ),
			m_index ( 0 ), m_pos ( VEC2 ( 0, 0 ) ), m_z ( 0 ),
			m_gnrt ( false ), m_loop ( false ), m_sync ( true )
	{
	}

	EffectGenerate::EffectGenerate ( const EffectGenerate & rhs )
	{
		m_id = rhs.m_id;
		m_index = rhs.m_index;
		m_pos = rhs.m_pos;
		m_z = rhs.m_z;
		m_gnrt = rhs.m_gnrt;
		m_loop = rhs.m_loop;
		m_sync = rhs.m_sync;
	}

	EffectGenerate::~EffectGenerate ()
	{
	}


}	//namespace GAME

