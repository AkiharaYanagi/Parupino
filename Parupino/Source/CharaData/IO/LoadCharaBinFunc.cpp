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
	}


	void LoadCharaBinFunc::LoadChara ( P_CH buf, UINT & pos, Chara & ch )
	{
		LoadCharaScript ( buf, pos, ch );
		LoadCharaImage ( buf, pos, ch );
	}

	void LoadCharaBinFunc::LoadCharaScript ( P_CH buf, UINT & pos, Chara & ch )
	{
		LoadBehavior ( buf, pos, ch );	//Behavior
		LoadGarnish ( buf, pos, ch );	//Garnish
		LoadCommand ( buf, pos, ch );	//Command
		LoadBranch ( buf, pos, ch );	//Branch
		LoadRoute ( buf, pos, ch );		//Route
	}

	void LoadCharaBinFunc::LoadCharaImage ( P_CH buf, UINT & pos, Chara & ch )
	{
		LoadImg ( buf, pos, ch.GetpvpMainTexture () );
		LoadImg ( buf, pos, ch.GetpvpEfTexture () );
	}


	void LoadCharaBinFunc::LoadBehavior ( P_CH buf, UINT & pos, Chara & ch )
	{
		//@todo メモリコントローラ
		//先頭に 総アクション数, 総スクリプト数 を記述、必要時に該当分のアドレスを返す

		//アクション個数 と メモリの確保
		byte nAct = (byte)buf [ pos ++ ];

#if 0
		unique_ptr < Action [] > pi = make_unique < Action [] > ( nAct );

		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
//		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = make_shared < Action > (); }

		shared_ptr < P_Action [] > aryShared { new P_Action [ nAct ] , default_delete < P_Action [] > () };
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = aryShared [ i ]; }
#endif // 0
#if 0
		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
		shared_ptr < Action [] > aryShared = make_shared < Action [] > ( nAct );
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ].reset ( & aryShared [ i ] ); }
#endif // 0

		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
//		vector < P_Action > aryAct ( nAct );
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = make_shared < Action > (); }


		//実データ
		for ( UINT iAct = 0; iAct < nAct; ++ iAct )
		{
			P_Action pAct = aryAct [ iAct ];


			TRACE_F ( _T ( "%d\n" ), iAct );


			//アクション
			aryAct [ iAct ]->SetName ( m_utl.LoadText ( buf, pos ) );
			aryAct [ iAct ]->SetNextID ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetCategory ( (ACTION_CATEGORY)buf [ pos ++ ] );
			aryAct [ iAct ]->SetPosture ( (ACTION_POSTURE)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitNum ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitPitch ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetBalance ( m_utl.LoadInt ( buf, pos ) );

			//スクリプト個数 と メモリの確保
			byte nScp = (byte)buf [ pos ++ ];
			unique_ptr < P_Script [] > aryScp = make_unique < P_Script [] > ( nScp );
			for ( UINT i = 0; i < nScp; ++ i ) { aryScp [ i ] = make_shared < Script > (); }

			for ( UINT iScp = 0; iScp < nScp; ++ iScp )
			{
				aryScp [ iScp ]->SetFrame ( iScp );
				LoadScript ( buf, pos, (* aryScp [ iScp ]) );
			}

			aryAct [ iAct ]->AddaScript ( ::move (aryScp), nScp );
		}

//		ch.AddpAction ( aryAct, nAct );
		ch.AddpAction ( ::move ( aryAct ), nAct );
	}
	
	void LoadCharaBinFunc::LoadGarnish ( P_CH buf, UINT & pos, Chara & ch )
	{
		//エフェクト個数 と メモリの確保
		byte nEfc = (byte)buf [ pos ++ ];

		vector < P_Effect > aryEfc( nEfc );
		for ( UINT i = 0; i < nEfc; ++ i ) { aryEfc [ i ] = make_shared < Effect > (); }

		//実データ
		for ( UINT iEfc = 0; iEfc < nEfc; ++ iEfc )
		{
			//エフェクト
			aryEfc [ iEfc ]->SetName ( m_utl.LoadText ( buf, pos ) );

			//スクリプト個数 と メモリの確保
			byte nScp = (byte)buf [ pos ++ ];
			unique_ptr < P_Script [] > aryScp = make_unique < P_Script [] > ( nScp );
			for ( UINT i = 0; i < nScp; ++ i ) { aryScp [ i ] = make_shared < Script > (); }

			for ( UINT iScp = 0; iScp < nScp; ++ iScp )
			{
				aryScp [ iScp ]->SetFrame ( iScp );
				LoadScript ( buf, pos, ( * aryScp [ iScp ] ) );
			}
		}

		ch.AddpEffect ( aryEfc, nEfc );
	}

	void LoadCharaBinFunc::LoadCommand ( P_CH buf, UINT & pos, Chara & ch )
	{
		//コマンド個数 と メモリの確保
		byte nCmd = (byte)buf [ pos ++ ];
		unique_ptr < P_Command[] > aryCmd = make_unique < P_Command[] > ( nCmd );
		for ( UINT i = 0; i < nCmd; ++ i ) { aryCmd [ i ] = make_shared < Command > (); }

		//実データ
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			//コマンド名
			aryCmd [ i ]->SetName ( m_utl.LoadText ( buf, pos ) );

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
		//ブランチ個数 と メモリの確保
		byte nBrc = (byte)buf [ pos ++ ];
		unique_ptr < P_Branch [] > aryBrc = make_unique < P_Branch [] > ( nBrc );
		for ( UINT i = 0; i < nBrc; ++ i ) { aryBrc [ i ] = make_shared < Branch > (); }

		//実データ
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			//ブランチ名
			aryBrc [ i ]->SetName ( m_utl.LoadText ( buf, pos ) );

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
		//ルート個数 と メモリの確保
		byte nRut = (byte)buf [ pos ++ ];
		unique_ptr < P_Route [] > aryRut = make_unique < P_Route [] > ( nRut );
		for ( UINT i = 0; i < nRut; ++ i ) { aryRut [ i ] = make_shared < Route > (); }

		//実データ
		for ( UINT i = 0; i < nRut; ++ i )
		{
			P_Route pr = aryRut [ i ];

			//ルート名
			aryRut [ i ]->SetName ( m_utl.LoadText ( buf, pos ) );

			//ブランチID個数
			m_utl.LoadAryUint ( buf, pos, aryRut [ i ]->GetvIDBranch () );
		}

		ch.AddaRoute ( ::move ( aryRut ), nRut );
	}

	void LoadCharaBinFunc::LoadScript ( P_CH buf, UINT & pos, Script & scp )
	{
		//イメージインデックス
		byte b = buf [ pos ++ ];
		scp.SetImageIndex ( (UINT)b );

		//位置
		scp.SetPos ( m_utl.LoadVec2 ( buf, pos ) );

		// [] ルートID
		m_utl.LoadAryUint ( buf, pos, scp.GetvRouteID () );

		//枠
		m_utl.LoadListRect ( buf, pos, scp.GetpvCRect () );
		m_utl.LoadListRect ( buf, pos, scp.GetpvHRect () );
		m_utl.LoadListRect ( buf, pos, scp.GetpvARect () );
		m_utl.LoadListRect ( buf, pos, scp.GetpvORect () );

		// [] エフェクト生成
		byte nIdEfGnrt = buf [ pos ++ ];
		unique_ptr < EffectGenerate [] > aryEfGnrt = make_unique < EffectGenerate [] > ( nIdEfGnrt );
		for ( UINT i = 0; i < nIdEfGnrt; ++ i )
		{


			TRACE_F ( _T ( "%d\n" ), i );


			//エフェクトID
			aryEfGnrt [ i ].SetIndex ( (UINT)buf [ pos ++ ] );
			//位置
			int pos_x = m_utl.LoadInt ( buf, pos );
			int pos_y = m_utl.LoadInt ( buf, pos );
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
		LoadScpPrm_Btl ( buf, pos, scp );

		//ステージング(演出)パラメータ
		LoadScpPrm_Stg ( buf, pos, scp );
	}


	//スクリプト・戦闘パラメータ
	void LoadCharaBinFunc::LoadScpPrm_Btl ( P_CH buf, UINT & pos, Script & scp )
	{
		scp.m_prmBattle.CalcState = (CLC_ST)m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Vel = m_utl.LoadVec2 ( buf, pos );
		scp.m_prmBattle.Acc = m_utl.LoadVec2 ( buf, pos );
		scp.m_prmBattle.Power = m_utl.LoadInt ( buf, pos );

		if ( 0 != scp.m_prmBattle.Power )
		{
			int i = 0;
		}

		scp.m_prmBattle.Warp = m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Recoil_I = m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Recoil_E = m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Balance_I = m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Balance_E = m_utl.LoadInt ( buf, pos );
	}


	//スクリプト・演出パラメータ
	void LoadCharaBinFunc::LoadScpPrm_Stg ( P_CH buf, UINT & pos, Script & scp )
	{
		scp.m_prmStaging.BlackOut		 = m_utl.LoadByte ( buf, pos );
		scp.m_prmStaging.Vibration		 = m_utl.LoadByte ( buf, pos );
		scp.m_prmStaging.Stop			 = m_utl.LoadByte ( buf, pos );

		scp.m_prmStaging.Radian			 = m_utl.LoadInt ( buf, pos );
		scp.m_prmStaging.AfterImage_N	 = m_utl.LoadByte ( buf, pos );
		scp.m_prmStaging.AfterImage_time = m_utl.LoadByte ( buf, pos ); ;
		scp.m_prmStaging.AfterImage_pitch = m_utl.LoadByte ( buf, pos ); ;
		scp.m_prmStaging.Vibration_S	 = m_utl.LoadByte ( buf, pos );;
		scp.m_prmStaging.Color			 = (_CLR)m_utl.LoadUInt ( buf, pos );;
		scp.m_prmStaging.Color_time		 = m_utl.LoadByte ( buf, pos );;
	}


	void LoadCharaBinFunc::LoadImg ( P_CH buf, UINT & pos, PVP_TxBs pvpTxBs )
	{
		//個数を取得
		UINT nImg = (UINT)m_utl.LoadByte ( buf, pos );
		pvpTxBs->clear ();
		pvpTxBs->resize ( nImg );

		for ( UINT i = 0; i < nImg; ++ i )
		{
			//サイズを取得
			UINT size = m_utl.LoadUInt ( buf, pos );

			//メモリ上のデータからゲームテクスチャに変換
			P_TxMem pTx = make_shared < TxMem > ( (LPCVOID)(buf.get() + pos), size );
			pos += size;

			//キャラ内部のテクスチャリストに加える
			( *pvpTxBs ) [ i ] = pTx;
		}

	}


}	//namespace GAME

