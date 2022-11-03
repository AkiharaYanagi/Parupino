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


	void LoadCharaBinFunc::LoadChara ( P_CH buf, UINT & pos, Chara & ch )
	{
	}

	void LoadCharaBinFunc::LoadBehavior ( P_CH buf, UINT & pos, Chara & ch )
	{
		//アクション個数
		byte nAct = (byte)buf [ pos ++ ];

		//メモリの確保
		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
		for ( UINT i = 0; i < nAct; ++ i )
		{
			aryAct [ i ] = make_shared < Action > ();
		}

		//実データ
		for ( UINT iAct = 0; iAct < nAct; ++ iAct )
		{
			//アクション名
			aryAct [ iAct ]->SetName ( LoadText ( buf, pos ) );

			aryAct [ iAct ]->SetNextID ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetCategory ( (ACTION_CATEGORY)buf [ pos ++ ] );
			aryAct [ iAct ]->SetPosture ( (ACTION_POSTURE)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitNum ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitPitch ( (UINT)buf [ pos ++ ] );

			//スクリプト個数
			byte nScp = (byte)buf [ pos ++ ];

			//メモリの確保
			unique_ptr < P_Script [] > aryScp = make_unique < P_Script [] > ( nScp );
			for ( UINT i = 0; i < nScp; ++ i )
			{
				aryScp [ i ] = make_shared < Script > ();
			}

			for ( UINT iScp = 0; iScp < nScp; ++ iScp )
			{
				UINT indexImage = (UINT)buf [ pos ++ ];

				aryScp [ iScp ]->SetImageIndex ( indexImage );
			}

		}
	}
	
	void LoadCharaBinFunc::LoadGarnish ( P_CH buf, UINT & pos, Chara & ch )
	{
	}

	void LoadCharaBinFunc::LoadCommand ( P_CH buf, UINT & pos, Chara & ch )
	{
		//コマンド個数
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
			byte nStrName = buf [ pos ++ ];	//Encoding.UTF8
			aryCmd [ i ]->SetName ( LoadText ( buf, pos ) );
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
		//ブランチ個数
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
			byte nStrName = buf [ pos ++ ];	//size	Encoding.UTF8
			aryBrc [ i ]->SetName ( LoadText ( buf, pos ) );
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
		//ルート個数
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
			byte nStrName = buf [ pos ++ ];	//size	Encoding.UTF8
//			aryRut [ i ]->SetName ( LoadText ( buf.get () + pos, nStrName ) );
			tstring tstr( LoadText ( buf, pos ) );
			aryRut [ i ]->SetName ( tstr );

			pos += nStrName;

			//ブランチID個数
#if 0
			byte nIdBrc = (byte)buf [ pos ++ ];
			unique_ptr < UINT[] > aryIdBrc = make_unique < UINT[] > ( nIdBrc );
			for ( UINT id = 0; id < nIdBrc; ++ id )
			{
				aryIdBrc [ id ] = (UINT) buf [ pos ++ ];
			}
#endif // 0
			UINT nIdBrc = 0;
			unique_ptr < UINT [] > aryIdBrc = LoadAryUint ( buf, pos, nIdBrc );
			aryRut [ i ]->SetaIdBranch ( ::move ( aryIdBrc ), nIdBrc );
		}

		ch.AddaRoute ( ::move ( aryRut ), nRut );
	}

	void LoadCharaBinFunc::LoadScript ( P_CH buf, UINT & pos, Script & scp )
	{
		//イメージインデックス
		byte b = buf [ pos ++ ];
		scp.SetImageIndex ( (UINT)b );

		//位置
		int pos_x = LoadInt ( buf, pos );
		int pos_y = LoadInt ( buf, pos );
		scp.SetPos ( VEC2 ( (float)pos_x, (float)pos_y ) );

		//ルートID
#if 0
		byte nIdRut = buf [ pos ++ ];
		unique_ptr < UINT [] > aryIdRut = make_unique < UINT [] > ( nIdRut );
		for ( UINT i = 0; i < nIdRut; ++ i )
		{
			aryIdRut [ i ] = (UINT)buf [ pos ++ ];
		}
#endif // 0
		UINT nIdRut = 0;
		unique_ptr < UINT [] > aryIdRut = LoadAryUint ( buf, pos, nIdRut );
		scp.SetRouteID ( ::move ( aryIdRut ), nIdRut );

		//枠
		LoadListRect ( buf, pos, scp.GetpvCRect () );
		LoadListRect ( buf, pos, scp.GetpvHRect () );
		LoadListRect ( buf, pos, scp.GetpvARect () );
		LoadListRect ( buf, pos, scp.GetpvORect () );

		//エフェクト生成
		byte nIdEfGnrt = buf [ pos ++ ];
		unique_ptr < EffectGenerate [] > aryEfGnrt = make_unique < EffectGenerate [] > ( nIdEfGnrt );
		for ( UINT i = 0; i < nIdEfGnrt; ++ i )
		{
			//エフェクトID
			aryEfGnrt [ i ].SetIndex ( (UINT)buf [ pos ++ ] );
			//位置
			int pos_x = LoadInt ( buf, pos );
			int pos_y = LoadInt ( buf, pos );
			aryEfGnrt [ i ].SetPos ( VEC2 ( (float)pos_x, (float)pos_y ) );
			//Z値
			int z_per100F = (int)buf [ pos ++ ];
			aryEfGnrt [ i ].SetZ ( z_per100F / 100.f );
			//生成
			aryEfGnrt [ i ].SetGnrt ( (bool)buf [ pos ++ ] );
			//ループ
			aryEfGnrt [ i ].SetLoop ( (bool)buf [ pos ++ ] );
			//位置同期
			aryEfGnrt [ i ].SetSync ( (bool)buf [ pos ++ ] );
		}

		//バトルパラメータ

		//ステージング(演出)パラメータ
	}

	//スクリプト・戦闘パラメータ
	void LoadCharaBinFunc::LoadScpPrm_Btl ( P_CH buf, UINT & pos, Script & scp )
	{
	}

	//スクリプト・演出パラメータ
	void LoadCharaBinFunc::LoadScpPrm_Stg ( P_CH buf, UINT & pos, Script & scp )
	{
	}



	//-----------------------------------------------------------------------
	tstring LoadCharaBinFunc::LoadText ( P_CH buf, UINT & pos )
	{
		//名前のサイズ
		byte length = buf [ pos ++ ];	//Encoding.UTF8

		//		unique_ptr < char [] > arypChar = make_unique < char [] > ( length + 1 );
//		memcpy_s ( arypChar.get(), length ,buf, length );
		
//		unique_ptr < TCHAR [] >  tbuf = make_unique < TCHAR [] > ( length + 1 );
//		size_t _PptNumOfCharConverted = 0;
//		errno_t err = ::mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get (), length + 1, arypChar.get (), _TRUNCATE );

		//UTF8 -> wstring
		string str ( buf.get() + pos, length );
		std::wstring_convert < std::codecvt_utf8_utf16 < wchar_t > > converter;
		tstring tstr = converter.from_bytes ( str );

		//位置を更新
		pos += length;

		//取得した名前を返す
		return tstr ;
	}

	int LoadCharaBinFunc::LoadInt ( P_CH buf, UINT & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (int)0x01234567
		int i = 0;
		rsize_t size = sizeof ( int );
		::memcpy_s ( &i, size, buf.get () + pos, size );
		return i;
	}

	RECT LoadCharaBinFunc::LoadRect ( P_CH buf, UINT & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (int)0x01234567
		RECT rect = { 0 };
		rsize_t size = sizeof ( RECT );
		::memcpy_s ( &rect, size, buf.get () + pos, size );
		return rect;
	}

	void LoadCharaBinFunc::LoadListRect ( P_CH buf, UINT & pos, PV_RECT pvRect )
	{
		UINT n = buf [ pos ++ ];
		pvRect->clear ();
		pvRect->resize ( n );
		for ( UINT i = 0; i < n; ++ i )
		{
			( *pvRect ) [ i ] = LoadRect ( buf, pos );
		}
	}

	L_UINT LoadCharaBinFunc::LoadAryUint ( P_CH buf, UINT & pos, UINT & refLength )
	{
		refLength = buf [ pos ++ ];

		unique_ptr < UINT [] > ary_uint = make_unique < UINT [] > ( refLength );
		for ( UINT i = 0; i < refLength; ++ i )
		{
			ary_uint [ i ] = (UINT)buf [ pos ++ ];
		}

		return ::move ( ary_uint );
	}

}	//namespace GAME

