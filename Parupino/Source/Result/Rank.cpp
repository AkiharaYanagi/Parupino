//=================================================================================================
//
//	Rank ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Rank.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Rank::Rank ()
	{
		m_rank = make_shared < GrpAcv > ();
		m_rank->AddTexture ( _T ( "RANK_AAA.png" ) );
		m_rank->AddTexture ( _T ( "RANK_AA.png" ) );
		m_rank->AddTexture ( _T ( "RANK_A.png" ) );
		m_rank->AddTexture ( _T ( "RANK_B.png" ) );
		m_rank->AddTexture ( _T ( "RANK_C.png" ) );
		m_rank->AddTexture ( _T ( "RANK_D.png" ) );
		m_rank->AddTexture ( _T ( "RANK_E.png" ) );
		m_rank->AddTexture ( _T ( "RANK_F.png" ) );
		m_rank->SetPos ( VEC2 ( 480, 100 ) );
		AddpTask ( m_rank );
		GRPLST_INSERT_MAIN ( m_rank );

		m_blink = 0;
		m_step = 0;
	}

	Rank::~Rank ()
	{
	}

	void Rank::SelectRank ( RANK rank )
	{
		m_rank->SetIndexTexture ( rank );
	}

	void Rank::Move ()
	{
//		UINT index = m_rank->GetpObject ( 0 )->GetIndexTexture ();
//		if ( RANK_F < ++ index ) { index = 0; }
//		m_rank->SetIndexTexture ( index );

#if 0
		if ( ++ m_step > 0 )
		{
			if ( m_blink == 0 )
			{
				m_rank->SetColor ( 0x80fffffful );
				m_blink = 1;
			}
			else
			{
				m_rank->SetColor ( 0xfffffffful );
				m_blink = 0;
			}
			m_step = 0;
		}
#endif // 0


		TASK_VEC::Move ();
	}


}	//namespace GAME

