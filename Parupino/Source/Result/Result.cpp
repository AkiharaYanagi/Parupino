//=================================================================================================
//
//	Result ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Result.h"
#include "../Title_Intro/Title_Intro.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Result::Result ()
	{
		m_bg = make_shared < GrpAcv > ();
		m_bg->AddTexture ( _T ( "Result.png" ) );
		AddpTask ( m_bg );
		GRPLST_INSERT_MAIN ( m_bg );

		m_affinity = make_shared < GrpStr > ();
		m_affinity->SetStr ( _T ( "相性：" ) );
		m_affinity->SetPos ( VEC2 ( 500, 100 ) );
		AddpTask ( m_affinity );
		GRPLST_INSERT_MAIN ( m_affinity );

		m_strNAct1p = make_shared < GrpStr > ();
		m_strNAct1p->SetStr ( _T ( "1p : アクション移行回数：" ) );
		m_strNAct1p->SetPos ( VEC2 ( 100, 200 ) );
		AddpTask ( m_strNAct1p );
		GRPLST_INSERT_MAIN ( m_strNAct1p );

		m_strNAct2p = make_shared < GrpStr > ();
		m_strNAct2p->SetStr ( _T ( "2p : アクション移行回数：" ) );
		m_strNAct2p->SetPos ( VEC2 ( 100, 240 ) );
		AddpTask ( m_strNAct2p );
		GRPLST_INSERT_MAIN ( m_strNAct2p );

		m_win_lose_1p = MakeStr ( _T ( "win_lose_1p" ), VEC2 ( 100, 300 ) );
		m_win_lose_2p = MakeStr ( _T ( "win_lose_2p" ), VEC2 ( 700, 300 ) );
	}

	Result::~Result ()
	{
	}

	P_GrpStr Result::MakeStr ( LPCTSTR str, VEC2 pos )
	{
		P_GrpStr p = make_shared < GrpStr > ();
		p->SetStr ( str );
		p->SetPos ( pos );
		AddpTask ( p );
		GRPLST_INSERT_MAIN ( p );
		return p;
	}

	void Result::ParamInit ()
	{
#if 0
		int n1 = GetpParam ()->GetN_Act1p ();
		UP_TSTR upstr1 = Format::GetFormatStr ( _T ( "1p : アクション移行回数：%d" ), n1 );
		m_strNAct1p->SetStr ( upstr1.get () );

		int n2 = GetpParam ()->GetN_Act2p ();
		UP_TSTR upstr2 = Format::GetFormatStr ( _T ( "2p : アクション移行回数：%d" ), n2 );
		m_strNAct2p->SetStr ( upstr2.get () );
#endif // 0
		int n1 = GetpParam ()->GetN_Act1p ();
		m_strNAct1p->SetStrF ( _T ( "1p : アクション移行回数：%d" ), n1 );
		int n2 = GetpParam ()->GetN_Act2p ();
		m_strNAct2p->SetStrF ( _T ( "2p : アクション移行回数：%d" ), n2 );


		PLAYER_ID winner = GetpParam ()->GetWinner ();
		switch ( winner )
		{
		case PLAYER_ID_1:
			m_win_lose_1p->SetStr ( _T ( "Win" ) );
			m_win_lose_2p->SetStr ( _T ( "Lose" ) );
		break;
		case PLAYER_ID_2:
			m_win_lose_1p->SetStr ( _T ( "Lose" ) );
			m_win_lose_2p->SetStr ( _T ( "Win" ) );
		break;
		case _PLAYER_NUM:
			m_win_lose_1p->SetStr ( _T ( "Draw" ) );
			m_win_lose_2p->SetStr ( _T ( "Draw" ) );
		break;
		}
	}

	void Result::Load ()
	{
		//遷移先を自身に設定
		mwp_This = shared_from_this ();

		Scene::Load ();
	}

	void Result::Init ()
	{
		Scene::Init ();
	}

	void Result::Move ()
	{
		Scene::Move ();
	}

	P_GameScene Result::Transit ()
	{
		//===========================================================
		//戻る (ボタン0, ボタン1 両方受付)
		bool p12_b0 = CFG_PUSH_KEY ( _P1_BTN0 ) || CFG_PUSH_KEY ( _P2_BTN0 );
		bool p12_b1 = CFG_PUSH_KEY ( _P1_BTN1 ) || CFG_PUSH_KEY ( _P2_BTN1 );
		if ( p12_b0 || p12_b1 )
		{
			GRPLST_CLEAR ();
			mp_Transit = make_shared < Title_Intro > ();
			GRPLST_LOAD ();
		}
		//===========================================================

		//次遷移先を返す
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//通常時は自身を返す
//		return shared_from_this ();
//		return shared_from_this ();		//通常は自身を返す
		return mwp_This.lock ();
	}


}	//namespace GAME

