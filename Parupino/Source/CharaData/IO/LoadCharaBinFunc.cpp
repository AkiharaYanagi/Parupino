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
		unique_ptr < P_Command[] > aryCmd = make_unique < P_Command[] > ( nCmd );
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			aryCmd [ i ] = make_shared < Command > ();
		}

		//実データ
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			//コマンド名
			char nStrName = buf [ pos ++ ];	//Encoding.UTF8
			aryCmd [ i ]->SetName ( LoadText ( buf.get() + pos, nStrName ) );
			pos += nStrName;

			//受付時間
			aryCmd [ i ]->SetLimitTime ( (UINT)buf [ pos ++ ] );

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

			aryCmd [ i ]->SetaGameKey ( gkc.get (), nGameKey );
		}

		ch.AddaCommand ( ::move ( aryCmd ), nCmd );
	}


	void LoadCharaBinFunc::LoadBranch ( P_CH buf, UINT & pos, Chara & ch )
	{
		//個数
		byte nBrc = (byte)buf [ pos ++ ];

		//メモリの確保
		unique_ptr < P_Branch [] > aryBrc = make_unique < P_Branch [] > ( nBrc );
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			aryBrc [ i ] = make_shared < Branch > ();
		}

		//実データ
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			//ブランチ名
			char nStrName = buf [ pos ++ ];	//size	Encoding.UTF8
			aryBrc [ i ]->SetName ( LoadText ( buf.get () + pos, nStrName ) );
			pos += nStrName;

			//条件
			aryBrc [ i ]->SetCondition ( (BRANCH_CONDITION)buf [ pos ++ ] );
			aryBrc [ i ]->SetIndexCommand ( (UINT)buf [ pos ++ ] );
			aryBrc [ i ]->SetIndexSequence ( (UINT)buf [ pos ++ ] );
			aryBrc [ i ]->SetIndexFrame ( (UINT)buf [ pos ++ ] );
		}

		ch.AddaBranch ( ::move ( aryBrc ), nBrc );
	}


	void LoadCharaBinFunc::LoadRoute ( P_CH buf, UINT & pos, Chara & ch )
	{
		//個数
		byte nRut = (byte)buf [ pos ++ ];

		//メモリの確保
		unique_ptr < P_Route [] > aryRut = make_unique < P_Route [] > ( nRut );
		for ( UINT i = 0; i < nRut; ++ i )
		{
			aryRut [ i ] = make_shared < Route > ();
		}

		//実データ
		for ( UINT i = 0; i < nRut; ++ i )
		{
			//ルート名
			char nStrName = buf [ pos ++ ];	//size	Encoding.UTF8
//			aryRut [ i ]->SetName ( LoadText ( buf.get () + pos, nStrName ) );
			tstring tstr( LoadText ( buf.get () + pos, nStrName ) );
			aryRut [ i ]->SetName ( tstr );

			pos += nStrName;

			//ブランチID個数
			byte nIdBrc = (byte)buf [ pos ++ ];

			unique_ptr < UINT[] > aryIdBrc = make_unique < UINT[] > ( nIdBrc );

			for ( UINT id = 0; id < nIdBrc; ++ id )
			{
				aryIdBrc [ id ] = (UINT) buf [ pos ++ ];
#if 0
#endif // 0
			}

			aryRut [ i ]->SetaIdBranch ( ::move ( aryIdBrc ), nIdBrc );
		}

		ch.AddaRoute ( ::move ( aryRut ), nRut );
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

