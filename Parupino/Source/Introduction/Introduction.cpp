//=================================================================================================
//
//	イントロダクション
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Introduction.h"
#include "../GameMain/SoundConst.h"
#include "../Title/Title.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//定数
//	const size_t Introduction::SIZE_STR = 20;
	const size_t Introduction::DISP_H = 10;
	const size_t Introduction::PAD_HEAD = 3;
	const size_t Introduction::PAD_TAIL = 3;
	const float Introduction::BASE_STR_Y = 100.f;


	Introduction::Introduction ()
		: m_selectPos ( 0 ), m_start_str_y ( 0 ), m_cursorPos ( 0 )
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


		//File
		
		//@info Unicode使用時はロケールの指定を行う
		setlocale ( LC_ALL, "japanese" );
		std::locale::global ( std::locale ( "japanese" ) );

//		ifstream ifstrm ( _T("Introduction.txt" ), ifstream::ate );
		ifstream ifstrm ( _T("Introduction.txt" ), ifstream::beg );

#if 0
		size_t size = static_cast <size_t> ( ifstrm.tellg () );
		ifstrm.seekg ( 0, ifstream::beg );
//		ifstrm.unsetf ( ifstream::skipws );
#endif // 0
		
		string str;
		streampos sp = ifstrm.tellg ();
		ifstrm.seekg ( 10, ifstream::beg );
		sp = ifstrm.tellg ();
		ifstrm.seekg ( 0, ifstream::beg );
		sp = ifstrm.tellg ();

		ios::iostate st = ifstrm.rdstate ();


		//@info eofbitはエラー扱いなので、その後のseekg()が無効になっている
		//@info ifstrm.clear ();を使用してビットをクリアする


		//行数
		int nLine = 0;
		while ( std::getline ( ifstrm, str ) )
		{
			sp = ifstrm.tellg ();
			++ nLine;
		}
		
		st = ifstrm.rdstate ();

		ifstrm.clear ();
		
		ifstrm.seekg ( 0, ifstream::beg );
		sp = ifstrm.tellg ();

		ifstrm.seekg ( ifstream::beg );
		sp = ifstrm.tellg ();


		mv_Str.resize ( nLine );
		UINT indexLine = 0;


		sp = ifstrm.tellg ();
//		unique_ptr < char [] > buf = make_unique < char [] > ( size );
		ifstrm.seekg ( 0, ifstream::beg );
		sp = ifstrm.tellg ();

//		while ( ! ifstrm.eof() )
		while ( std::getline ( ifstrm, str ) )
		{
//			ifstrm >> str;
			//TRACE_CHF ( str.c_str () );
//			std::getline ( ifstrm, str );

			//multibyte文字からTCHAR(WCHAR)に変換
			size_t n = 0;
			size_t sizebuf = strlen ( str.c_str () ) + 1;
			unique_ptr < TCHAR [] > tbuf = make_unique < TCHAR [] > ( sizebuf );		//バッファを確保
			errno_t e = mbstowcs_s ( &n, tbuf.get (), sizebuf, str.c_str (), _TRUNCATE );

			tstring tstr ( tbuf.get() );
//			TRACE_F ( tstr.c_str () );


			//---------------------------------------------
			//STR
			P_GrpStr p = make_shared < GrpStr > ();
			mv_Str [ indexLine ++ ] = p;
			p->SetStr ( tstr.c_str () );
			p->SetPos ( 140.f, BASE_STR_Y + ( m_start_str_y + indexLine ) * 40.f );
			AddpTask ( p );
			GRPLST_INSERT_MAIN ( p );

		}
#if 0
		ifstream ifstrm ( _T ( "Introduction.txt" ), ios::binary | ios::ate );
		size_t size = static_cast < size_t > ( ifstrm.tellg () );
		ifstrm.seekg ( ios::beg );
		unique_ptr < char [] > buf = make_unique < char [] > ( size );
		ifstrm.read ( buf.get (), size );
		unique_ptr < TCHAR [] > wbuf = make_unique < TCHAR [] > ( size );
		size_t n = 0;
		mbstowcs_s ( & n, wbuf.get(), size, buf.get(), _TRUNCATE );
		tstring tstr ( wbuf.get() );


		tifstream tfstrm ( _T ( "Introduction.txt" ) );
		tstring tstr;
		while ( ! tfstrm.eof () )
		{
			tfstrm >> tstr;
			TRACE_F ( tstr.c_str () );
		}



		HANDLE hFile = ::CreateFile ( _T("Introduction.txt"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
		DWORD SIZE = 0;
		DWORD n = 0;
		::GetFileSize ( hFile, & SIZE );
		unique_ptr < char [] > buf ( new char [ SIZE ] );
		::ReadFile ( hFile, buf.get (), sizeof ( char ), & n, NULL );

		unique_ptr < TCHAR [] > tbuf = make_unique < TCHAR [] > ( SIZE );		//バッファを確保
		size_t n1 = 0;
		mbstowcs_s ( & n1, tbuf.get (), (size_t)SIZE, buf.get (), _TRUNCATE );
#endif // 0



#if 0

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
			
			p->SetPos ( 140.f, BASE_STR_Y + (m_start_str_y + i) * 40.f );
			AddpTask ( p );
			GRPLST_INSERT_MAIN ( p );
		}

#endif // 0



		//dispPos
		m_grpDispPos = make_shared < GrpStr > ();
		m_grpDispPos->SetPos ( VEC2 ( 200, 800 ) );
		tostringstream tss;
		tss << m_selectPos;
		m_grpDispPos->SetStr ( tss.str().c_str() );
		AddpTask ( m_grpDispPos );
		GRPLST_INSERT_MAIN ( m_grpDispPos );


		//画像説明
		m_grpInput = make_shared < GrpAcv > ();
		m_grpInput->AddTexture ( _T("Intro_Input.png") );
		m_grpInput->Move ();
		AddpTask ( m_grpInput );
		GRPLST_INSERT_MAIN ( m_grpInput );

		m_wait = 0;

		m_waitSound = make_shared < Timer > ();
		AddpTask ( m_waitSound );
	}

	Introduction::~Introduction ()
	{
	}

	void Introduction::Load ()
	{
		//遷移先を自身に設定
//		mwp_This = shared_from_this ();

		//SOUND
		m_waitSound->SetTargetTime ( 5 );
		m_waitSound->Start ();

		Scene::Load ();
	}

	void Introduction::ParamInit ()
	{
	}

	P_GameScene Introduction::Transit ()
	{
		//開始後、1[F]は入力をチェックしない
		if ( m_wait == 0 )
		{
			m_wait = 1; return mwp_This.lock ();
		}

		if ( m_waitSound->IsLast () )
		{
			//SOUND
			SOUND->Play_Loop_BGM ( BGM_Intro );
			m_waitSound->Clear ();
		}

		//===========================================================
		//戻る
		if ( CFG_IS_KEY ( _P1_BTN1 ) || CFG_IS_KEY ( _P2_BTN1 ) )
		{
			//SOUND
			SOUND->Play_SE ( SE_Sys_Cancel );
			SOUND->Stop_BGM ( BGM_Intro );

			GRPLST_CLEAR ();
			mp_Transit = make_shared < Title > ();
			GRPLST_LOAD ();
		}

		//===========================================================

		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		return mwp_This.lock();
	}

	void Introduction::Move ()
	{
		//----------------------------------------------------------
		//選択
//		const UINT N = SIZE_STR;
		const UINT N = mv_Str.size ();
		const UINT H = DISP_H;

		//下入力
		bool bDownInput = CFG_IS_KEY ( _P1_DOWN ) || CFG_IS_KEY ( _P2_DOWN );
		m_tmrCursorDown->Check ( bDownInput );
		if ( m_tmrCursorDown->IsHold () )
		{
			//選択位置
			//ループ
//			if ( m_selectPos == N - 1 ) { m_selectPos = 0; }
//			else { ++ m_selectPos; }
			//ループ無し
			if ( m_selectPos == N - 1 ) { m_selectPos = N - 1; }
			else
			{
				++ m_selectPos;

				//スクロール条件位置
				UINT STR = H - PAD_TAIL;
				UINT END = N - PAD_TAIL;

				//カーソル位置
				if ( m_cursorPos < STR || END < m_selectPos )
				{
					++ m_cursorPos;
				}

				//文字列位置
				if ( STR < m_selectPos && m_selectPos < END )
				{
					-- m_start_str_y;
				}
#if 0
				//カーソル位置
				//表示範囲内は下に移動
				if ( m_cursorPos < DISP_H - PAD_TAIL )
				{
					++ m_cursorPos;
				}
				//データ対象末尾から固定範囲
				else if ( DISP_H - PAD_TAIL < m_selectPos )
				{
					if ( m_cursorPos == DISP_H - 1 ) { m_cursorPos = 0; }
					++ m_cursorPos;
				}
				//中層
				else
				{
					//位置固定
				}

			//文字列位置
			//先頭から固定範囲
			if ( m_cursorPos < DISP_H - PAD_TAIL + 1 )
			{
				m_start_str_y = 0;
			}
			//末尾から固定範囲
			else if ( DISP_H - PAD_TAIL < m_selectPos )
			{
				//位置固定
			}
			//中層
			else
			{
				-- m_start_str_y;
			}
#endif // 0
				//SOUND
				SOUND->Play_SE ( SE_Sys_Select );
			}
		}

		//上入力
		bool bUpInput = CFG_IS_KEY ( _P1_UP ) || CFG_IS_KEY ( _P2_UP );
		m_tmrCursorUp->Check ( bUpInput );
		if ( m_tmrCursorUp->IsHold () )
		{
			//選択位置
			//ループ
//			if ( m_selectPos == 0 ) { m_selectPos = SIZE_STR - 1; }
//			else { -- m_selectPos; }
			//ループ無し
			if ( m_selectPos == 0 ) { m_selectPos = 0; }
			else
			{
				-- m_selectPos; 

				//スクロール条件位置
				UINT STR = 0 + PAD_HEAD;
				UINT END = N - H + PAD_HEAD;

				//カーソル位置
				if ( m_selectPos < STR || STR < m_cursorPos )
				{
					-- m_cursorPos;
				}

				//文字列位置
				if ( STR < m_selectPos && m_selectPos < END )
				{
					++ m_start_str_y;
				}
			}

#if 0
			//文字列位置
			//文字列位置
			//先頭から固定範囲
			if ( m_selectPos < PAD_HEAD )
			{
				m_start_str_y = 0;
			}
			//末尾から固定範囲
			else if ( DISP_H - PAD_TAIL < m_selectPos )
			{
				++ m_start_str_y;
			}
			//中層
			else
			{
				m_start_str_y = 0;
			}
#endif // 0
			//SOUND
			SOUND->Play_SE ( SE_Sys_Select );
		}


		//----------------------------------------------------------
		//文字列
		UINT i = 0;
		for ( P_GrpStr p : mv_Str )
		{
			//------------------------------------------------------
			//表示 ON/OFF 範囲
			bool bDisp = ( 0 <= m_start_str_y + i ) && ( m_start_str_y + i < DISP_H );
			p->SetValid ( bDisp );

			//------------------------------------------------------
			//文字列　位置
			p->SetPos ( 140.f, BASE_STR_Y + (m_start_str_y + i) * 40.f );
			//------------------------------------------------------

			++ i;
		}

		//----------------------------------------------------------
		//カーソル位置
		m_grpCursor->SetPos ( VEC2 ( 30, BASE_STR_Y + m_cursorPos * 40.f ) );

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

		//位置の数値を表示
		tostringstream tss;
		tss << m_selectPos << ", " << m_start_str_y << ", " << m_cursorPos;
		m_grpDispPos->SetStr ( tss.str ().c_str () );
		m_grpDispPos->Load ();



		Scene::Move ();
	}


}	//namespace GAME

