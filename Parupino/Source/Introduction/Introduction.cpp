//=================================================================================================
//
//	イントロダクション
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Introduction.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//定数
	const size_t Introduction::SIZE_STR = 20;
	const size_t Introduction::DISP_H = 10;
	const size_t Introduction::PAD_HEAD = 3;
	const size_t Introduction::PAD_TAIL = 3;


	Introduction::Introduction ()
		: m_selectPos ( 0 )//, m_bWait ( F ), m_bHold ( F )
	{
		//Caption "Introduction"
		m_grpIntro = make_shared < GrpAcv > ();
		m_grpIntro->AddTexture ( _T ( "TitleMenu_Introduction.png" ) );
		m_grpIntro->SetPos ( VEC2 ( 400, 100 ) );
		AddpTask ( m_grpIntro );
		GRPLST_INSERT_MAIN ( m_grpIntro );


		//cursor
		m_grpCursor = make_shared < GrpAcv > ();
		m_grpCursor->AddTexture ( _T ( "title_cursor.png" ) );
		m_grpCursor->SetPos ( VEC2 ( 30.f, 100.f + m_selectPos * 40) );
		AddpTask ( m_grpCursor );
		GRPLST_INSERT_MAIN ( m_grpCursor );

		m_tmrCursorDown = make_shared < HoldTimer > ( 30 );
		AddpTask ( m_tmrCursorDown );
		m_tmrCursorUp = make_shared < HoldTimer > ( 30 );
		AddpTask ( m_tmrCursorUp );


		//Str
		mv_Str.resize ( SIZE_STR );
		
		TCHAR tch = '0';
		for ( UINT i = 0; i < SIZE_STR; ++ i )
		{
			P_GrpStr p = make_shared < GrpStr > ();
			mv_Str [ i ] = p;

			tstring tstr ( _T("a") );
			tstr [ 0 ] = tch;
			p->SetStr ( tstr.c_str () );
			++ tch;
			
			p->SetPos ( VEC2 ( 140.f, 100.f + i * 40 ) );
			AddpTask ( p );
			GRPLST_INSERT_MAIN ( p );
		}

		//dispPos
		m_dispPos = make_shared < GrpStr > ();
		m_dispPos->SetPos ( VEC2 ( 200, 800 ) );
		tostringstream tss;
		tss << m_selectPos;
		m_dispPos->SetStr ( tss.str().c_str() );
		AddpTask ( m_dispPos );
		GRPLST_INSERT_MAIN ( m_dispPos );
	}

	Introduction::~Introduction ()
	{
	}

	void Introduction::ParamInit ()
	{
	}

	P_GameScene Introduction::Transit ()
	{
		return shared_from_this ();
	}

	void Introduction::Move ()
	{
		const UINT N = SIZE_STR;
		const UINT H = DISP_H;
		const float base_y = 100.f;	//基準位置
		UINT cursorPos = 0;	//カーソル位置

		//----------------------------------------------------------
		//入力
		bool bDownInput = CFG_IS_KEY ( _P1_DOWN ) || CFG_IS_KEY ( _P2_DOWN );
		m_tmrCursorDown->Check ( bDownInput );
		bool bDown = m_tmrCursorDown->IsHold ();

		bool bUpInput = CFG_IS_KEY ( _P1_UP ) || CFG_IS_KEY ( _P2_UP );
		m_tmrCursorUp->Check ( bUpInput );
		bool bUp = m_tmrCursorUp->IsHold ();

#if 0
		//状態
		if ( T )
		{
			if ( m_bHold )
			{
				bDown = T;
			}
			else
			{
				//押しっぱなし タイマウェイト
				if ( m_tmrCursor->IsActive () )
				{
					if ( m_bWait )
					{
						if ( m_tmrCursor->IsLast () )
						{
							bDown = T;
							m_bHold = T;	//押しっぱなし
						}
					}
				}
				else
				{
					m_tmrCursor->Start ();	//計測開始
					bDown = T;				//初回のみ１ステップ入力
					m_bWait = T;
				}
			}
		}
		//離したとき
		else
		{
			bDown = F;
			m_bWait = F;
			m_bHold = F;
		}
#endif // 0

		//----------------------------------------------------------


		//選択
//		if ( CFG_PUSH_KEY ( _P1_DOWN ) || CFG_PUSH_KEY ( _P2_DOWN ) )
		if ( bDown )
		{
			//選択位置
			if ( m_selectPos == SIZE_STR - 1 ) { m_selectPos = 0; }
			else { ++ m_selectPos; }

			//文字列位置
			if ( m_selectPos < H - PAD_TAIL )
			{
				m_start_str_y = base_y;
			}

		}
//		if ( CFG_PUSH_KEY ( _P1_UP ) || CFG_PUSH_KEY ( _P2_UP ) )
		if ( bUp )
		{
			//選択位置
			if ( m_selectPos == 0 ) { m_selectPos = SIZE_STR - 1; }
			else { -- m_selectPos; }

			//文字列位置
		}


		//文字列
		UINT i = 0;
		for ( P_GrpStr p : mv_Str )
		{
			//------------------------------------------------------
			//表示 ON/OFF 範囲

			//------------------------------------------------------
			//文字列　位置

			p->SetPos ( 140.f, m_start_str_y + i * 40 );
			++ i;
			//------------------------------------------------------
		}

		//カーソル位置
		cursorPos = m_selectPos;
		m_grpCursor->SetPos ( VEC2 ( 30, 100.f + cursorPos * 40 ) );

#if 0
		//cursor表示 (表示高さ：１０)
		UINT dispPos = 0;
		//先頭から固定範囲
		if ( m_cursorPos < PAD_HEAD ) { dispPos = m_cursorPos; }
		//末尾から固定範囲
		else if ( SIZE_STR - 1 - PAD_TAIL <= m_cursorPos )
		{
			dispPos = m_cursorPos - ( SIZE_STR - DISP_H );
		}
		//中層
		else { dispPos = m_cursorPos; }

		m_grpCursor->SetPos ( VEC2 ( 50, 100.f + dispPos * 40 ) );


		//位置の数値を表示
		tostringstream tss;
		tss << m_cursorPos << _T("->") << dispPos;
		m_dispPos->SetStr ( tss.str ().c_str () );
		m_dispPos->Load ();



		//文字列を表示, 前 PAD_HEAD, 後 PAD_TAIL に固定
		UINT i = 0;
		const UINT N = SIZE_STR;
		const UINT H = DISP_H;
		UINT pos = m_cursorPos;

		for ( P_GrpStr p : mv_Str )
		{
			//------------------------------------------------------
			//表示 ON/OFF 範囲

			//先頭から固定範囲
			if ( pos < PAD_HEAD ) { p->SetValid ( i < (N - H) ); }
			//末尾から固定範囲
			else if ( SIZE_STR - PAD_TAIL < pos )
			{
				p->SetValid ( ( N - H ) <=  i );
			}
			//中層
			else
			{ 
				bool A = ( pos - PAD_HEAD ) <= i;
				bool B = i < ( pos - PAD_HEAD + H );
				p->SetValid ( A && B );
			}


			//------------------------------------------------------
			//文字列　位置

			float base_y = 100.f;	//基準位置
			float start_y = base_y;	//開始位置

			//先頭から固定範囲
			if ( pos < PAD_HEAD ) { start_y = base_y; }
			//末尾から固定範囲
			else if ( SIZE_STR - PAD_TAIL < pos )
			{
				start_y = base_y - ( SIZE_STR - DISP_H ) * 40.f;
			}
			//中層
			else { start_y = base_y - ( pos - PAD_HEAD ) * 40.f; }

			p->SetPos ( 140.f, start_y + i * 40 );
			++ i;
			//------------------------------------------------------
		}
#endif // 0


		Scene::Move ();
	}


}	//namespace GAME

