//=================================================================================================
//
// LoadChara ソースファイル
//
//=================================================================================================
#include "LoadCharaBin.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	LoadChara
	//		スクリプトとイメージリストを保存したキャラデータ ".dat"ファイル から、Charaを読み込む
	//==================================================================================
	LoadCharaBin::LoadCharaBin ( const tstring & filename, Chara & chara )
	{
		try
		{
			_Load ( filename, chara );
		}
		catch ( LPCTSTR lpctstr )
		{
			TRACE_F ( lpctstr );
		}
		catch (...)
		{
			TRACE_F ( _T("Error LoadChara.\n") );
		}
	}

	//----------------------------------
	//	デストラクタ
	//----------------------------------
	LoadCharaBin::~LoadCharaBin ()
	{
	}


	//------------------------------------------
	//	try用実行関数
	//------------------------------------------
	void LoadCharaBin::_Load ( const tstring & filename, Chara & chara )
	{
		//---------------------------------------------------------------------
		//ファイルストリーム開始
		ifstream ifstrm ( filename.c_str (), ios::binary );

		//ファイルが存在しないとき何もしない
		if ( ifstrm.fail () ) { throw _T ( "ファイルが存在しません。" ); }

		//キャラアーカイブファイル形式のバージョン
		byte version = 0;	//読込用
		ifstrm.read ( (char*)& version, sizeof ( byte ) );
		if ( CHARA_VERSION != version ) { throw _T ( "キャラアーカイブのバージョンが異なります。" ); }

		//---------------------------------------------------------------------
		//スクリプト部のサイズ
		UINT scriptSize = 0;
		ifstrm.read ( (char*)& scriptSize, sizeof ( UINT ) );

		//一時読込
		unique_ptr < char [] > scriptBuf = make_unique < char[] > ( scriptSize );
		ifstrm.read ( scriptBuf.get(), scriptSize );

		UINT pos = 0;

		//Chara Command
		byte nCmd = (byte)scriptBuf [ pos ++ ];

		for ( UINT i = 0; i < nCmd; ++ i )
		{
			Command cmd;

			//コマンド名
			char nStrName = scriptBuf [ pos ++ ];	//Encoding.ASCII
			string str ( scriptBuf.get() + pos, nStrName );
			unique_ptr < TCHAR[] >  tbuf = make_unique < TCHAR[] > ( nStrName + 1 );
			size_t _PptNumOfCharConverted = 0;
			errno_t err = ::mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get (), nStrName + 1, str.c_str (), _TRUNCATE );
			cmd.SetName ( tstring ( tbuf.get () ) );
			pos += nStrName;

			//受付時間
			cmd.SetLimitTime ( (UINT)scriptBuf [ pos ++ ] );

			//ゲームキー
			byte nGameKey = scriptBuf [ pos ++ ];

			unique_ptr < _GameKeyCommand [] > gkc = make_unique < _GameKeyCommand [] > ( nGameKey );
			for ( UINT iKey = 0; iKey < nGameKey; ++ iKey )
			{
				//否定
				bool bNot = (bool) scriptBuf [ pos ++ ];

				//レバー [ _GameKey::LVR_NUM = 8 ]
				KEY_ST lvr [ _GameKey::LVR_NUM ] = { _GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iLvr = 0; iLvr < _GameKey::LVR_NUM; ++ iLvr )
				{
					lvr [ iLvr ] = (KEY_ST) scriptBuf [ pos ++ ];
				}

				//ボタン [ _GameKey::BTN_NUM = 8 ]
				KEY_ST btn [ _GameKey::BTN_NUM ] = { _GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iBtn = 0; iBtn < _GameKey::BTN_NUM; ++ iBtn )
				{
					btn [ iBtn ] = (KEY_ST) scriptBuf [ pos ++ ];
				}

				gkc [ iKey ].SetNot ( bNot );
				gkc [ iKey ].SetaLvr ( lvr );
				gkc [ iKey ].SetaBtn ( btn );
			}

			cmd.SetaGameKey ( gkc.get (), nGameKey );
#if 0
#endif // 0
		}

		//---------------------------------------------------------------------
		//ファイルストリーム終了
		ifstrm.close ();
	}


}	//namespace GAME

