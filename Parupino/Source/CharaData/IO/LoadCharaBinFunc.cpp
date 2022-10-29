//=================================================================================================
//
// LoadCharaFunc ソースファイル
//
//=================================================================================================
#include "LoadCharaBinFunc.h"

#include <codecvt>

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	LoadCharaBinFunc::LoadCharaBinFunc ()
	{
		::setlocale ( LC_ALL, "japanese" );
	}
	
	void LoadCharaBinFunc::LoadCommand ( P_CH buf, UINT & pos, Chara & ch )
	{
		//個数
		byte nCmd = (byte)buf [ pos ++ ];
		
		//メモリの確保
		unique_ptr < P_Command[] > pCmd = make_unique < P_Command[] > ( nCmd );
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			pCmd [ i ] = make_shared < Command > ();
		}

		//実データ
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			//コマンド名
			char nStrName = buf [ pos ++ ];	//Encoding.UTF8
			pCmd [ i ]->SetName ( LoadText ( buf.get() + pos, nStrName ) );
#if 0
			string str ( buf.get () + pos, nStrName );
			unique_ptr < TCHAR [] >  tbuf = make_unique < TCHAR [] > ( nStrName + 1 );
			size_t _PptNumOfCharConverted = 0;
			errno_t err = ::mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get (), nStrName + 1, str.c_str (), _TRUNCATE );
			pCmd [ i ]->SetName ( tstring ( tbuf.get () ) );
			
			
			tstring tstr ( (wchar_t*)( buf.get () + pos ), nStrName );
			pCmd [ i ]->SetName ( tstr );
#endif // 0
			pos += nStrName;

			//受付時間
			pCmd [ i ]->SetLimitTime ( (UINT)buf [ pos ++ ] );

			//ゲームキー
			byte nGameKey = buf [ pos ++ ];
			unique_ptr < _GameKeyCommand [] > gkc = make_unique < _GameKeyCommand [] > ( nGameKey );
			for ( UINT iKey = 0; iKey < nGameKey; ++ iKey )
			{
				//否定
				bool bNot = (bool)buf [ pos ++ ];

				//レバー [ _GameKey::LVR_NUM = 8 ]
				KEY_ST lvr [ _GameKey::LVR_NUM ] = { _GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iLvr = 0; iLvr < _GameKey::LVR_NUM; ++ iLvr )
				{
					lvr [ iLvr ] = (KEY_ST)buf [ pos ++ ];
				}

				//ボタン [ _GameKey::BTN_NUM = 8 ]
				KEY_ST btn [ _GameKey::BTN_NUM ] = { _GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iBtn = 0; iBtn < _GameKey::BTN_NUM; ++ iBtn )
				{
					btn [ iBtn ] = (KEY_ST)buf [ pos ++ ];
				}

				gkc [ iKey ].SetNot ( bNot );
				gkc [ iKey ].SetaLvr ( lvr );
				gkc [ iKey ].SetaBtn ( btn );
			}

			pCmd [ i ]->SetaGameKey ( gkc.get (), nGameKey );
		}

		ch.AddaCommand ( ::move ( pCmd ), nCmd );
	}


	void LoadCharaBinFunc::LoadBranch ( P_CH buf, UINT & pos, Chara & ch )
	{
		//個数
		byte nBrc = (byte)buf [ pos ++ ];

		//メモリの確保
		unique_ptr < P_Branch [] > pBrc = make_unique < P_Branch [] > ( nBrc );
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			pBrc [ i ] = make_shared < Branch > ();
		}

		//実データ
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			//ブランチ名
			char nStrName = buf [ pos ++ ];	//Encoding.UTF8
			pBrc [ i ]->SetName ( LoadText ( buf.get () + pos, nStrName ) );
			pos += nStrName;

			//条件
			pBrc [ i ]->SetCondition ( (BRANCH_CONDITION)buf [ pos ++ ] );
			pBrc [ i ]->SetIndexCommand ( (UINT)buf [ pos ++ ] );
			pBrc [ i ]->SetIndexSequence ( (UINT)buf [ pos ++ ] );
			pBrc [ i ]->SetIndexFrame ( (UINT)buf [ pos ++ ] );
		}

		ch.AddaBranch ( ::move ( pBrc ), nBrc );
	}


	void LoadCharaBinFunc::LoadRoute ( P_CH buf, UINT & pos, Chara & ch )
	{

	}

	tstring LoadCharaBinFunc::LoadText ( char* buf, UINT length )
	{
//		unique_ptr < char [] > arypChar = make_unique < char [] > ( length + 1 );
//		memcpy_s ( arypChar.get(), length ,buf, length );
		
//		unique_ptr < TCHAR [] >  tbuf = make_unique < TCHAR [] > ( length + 1 );
//		size_t _PptNumOfCharConverted = 0;
//		errno_t err = ::mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get (), length + 1, arypChar.get (), _TRUNCATE );

		//UTF8 -> wstring
		string str ( buf, length );
		std::wstring_convert < std::codecvt_utf8_utf16 < wchar_t > > converter;
		tstring tstr = converter.from_bytes ( str );

		return tstr ;
	}

}	//namespace GAME

