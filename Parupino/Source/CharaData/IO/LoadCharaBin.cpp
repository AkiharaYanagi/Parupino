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
			TRACE_F ( _T("Error LoadCharaBin.\n") );
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
		const byte CHARA_VERSION = 110;
		if ( CHARA_VERSION != version ) { throw _T ( "キャラアーカイブのバージョンが異なります。" ); }

		//---------------------------------------------------------------------
		//スクリプト部のサイズ
		UINT scriptSize = 0;
		ifstrm.read ( (char*)& scriptSize, sizeof ( UINT ) );

		//一時読込
		P_CH scriptBuf = make_unique < char[] > ( scriptSize );
		ifstrm.read ( scriptBuf.get(), scriptSize );
		UINT pos = 0;	//メモリポインタ

		//Chara
		m_func.LoadChara ( scriptBuf, pos, chara );

		//---------------------------------------------------------------------
		//ファイルストリーム終了
		ifstrm.close ();
	}


}	//namespace GAME

