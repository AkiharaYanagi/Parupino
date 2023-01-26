//=================================================================================================
//
// ExeChara_Demo　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara_Demo.h"
#include "..\CharaData\IO\LoadCharaBin.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//コンストラクタ
	ExeChara_Demo::ExeChara_Demo ( PLAYER_ID m_playerID )
		: m_pChara ( nullptr )
		, m_playerID ( m_playerID ), m_name ( CHARA_TEST )
		, m_actionID ( 0 ), m_frame ( 0 )
		, m_charaState ( CHST_START )
	{
		//キャラデータ生成
		m_pChara = make_shared < Chara > ();	//キャラデータ実体
	}

	//デストラクタ
	ExeChara_Demo::~ExeChara_Demo ()
	{
	}

	//------------------------
	//シーンパラメータ関連初期化
	void ExeChara_Demo::ParamInit ( P_Param pParam )
	{
		//ゲーム設定
		GameSettingFile stg = pParam->GetGameSetting ();

		//選択キャラ //入力モード
		if ( m_playerID == PLAYER_ID_1 )
		{
			m_name = stg.GetName1p ();
		}
		if ( m_playerID == PLAYER_ID_2 )
		{
			m_name = stg.GetName2p ();
		}
	}

	//------------------------
	//読込
	void ExeChara_Demo::Load ()
	{
		//名前からスクリプトファイルを指定してキャラのロード
		//※	D3DXのテクスチャを用いるためフォーカス変更時などに再設定(Reset())が必要
		tstring name ( _T ( "charaBin.dat" ) );

		//バイナリデータ読込
		LoadCharaBin loadCharaBin ( name, *m_pChara );

		//キャラ表示初期化
		m_dispChara.SetpChara ( m_pChara );
		m_dispChara.Load ();

		TASK_VEC::Load ();
	}

	//------------------------
	//初期化(複数回実行可能)
	void ExeChara_Demo::Init ()
	{
		//アクション・スクリプト初期化
//		m_actionID = 0;
		m_actionID = m_pChara->GetActionID ( _T("Start_Demo") );
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_frame = 0;
		m_pScript = m_pAction->GetpScript ( m_frame );

		//バトルパラメータ
		m_btlPrm.InitPlayerID ( m_playerID );
		m_btlPrm.Init ();

		//表示
		//@info Move()中のTransit()の後に遷移し、
		//		再度Move()は呼ばれずDraw()が呼ばれるため、ここで初期化が必要(Init()は呼ばれる)
		m_dispChara.UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );
		m_dispChara.InitDisp ( m_playerID );

		TASK_VEC::Init ();
	}

	//再設定
	void ExeChara_Demo::Reset ()
	{
		_Reset ();	//復旧時
	}

	//------------------------
	//復旧時の再設定
	void ExeChara_Demo::_Reset ()
	{
		//テクスチャメモリ確保関連は再設定
		Rele ();
		m_pChara = make_shared < Chara > ();
		Load ();
		m_dispChara.SetpChara ( m_pChara );

		//アクション・スクリプト再取得
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//メイン イメージ
		m_dispChara.UpdateMainImage ( m_pScript, GetPos (), GetDirRight () );
	}

	//==========================================================
	//MutualCharaから呼ばれる主な関数
	//==========================================================
	//	↓ 処理順番
	//	void ExeChara::PreScriptMove ();	//	スクリプト前処理
	//	void MutualChara::Collision ();		//	相互判定 (接触枠)
	//	void ExeChara::ScriptRectMove ();	//	ぶつかり後、判定枠を設定
	//	void MutualChara::Decision ();		//	相互判定 (攻撃枠、ヒット枠)
	//	void ExeChara::PostScriptMove ();	//	スクリプト後処理

	//■#########################################################
	//■
	//■		毎フレーム スクリプト前処理
	//■			位置や枠の設定
	//■
	//■#########################################################
	void ExeChara_Demo::PreScriptMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//一時停止のときは何もしない
		if ( m_btlPrm.GetTmr_Stop()->IsActive () )
		{ return; }

		// アクション移項
		TransitAction ();
	}



	//■###########################################################################
	//■
	//■		毎フレーム スクリプト後処理
	//■			自分・相手のスクリプト前処理→相互の判定、の後にそれぞれの処理をする
	//■			判定の結果表示(主にグラフィック関連)
	//■
	//■###########################################################################
	void ExeChara_Demo::PostScriptMove ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );
		
		//1[F]に一度行う処理
		AlwaysPostMove ();

		//一時停止のときは何もしない
		if ( m_btlPrm.GetStop () ) { return; }

		// グラフィック
		UpdateGraphic ();
	}

	//================================================
	//	内部関数
	//================================================

	//アクションの移項(直接指定)
	void ExeChara_Demo::TransitAction ( UINT actionID )
	{
		//遷移先チェック
		P_Action pact = m_pChara->GetpAction( actionID );
		P_Script pscr = pact->GetpScript ( 0 );

		m_actionID = actionID;		//遷移
		m_frame = 0;		//スクリプト初期化

		//一時アクションとスクリプトを再設定
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );
	}

	// アクション移項(条件:コマンド, アクション終了)
	void ExeChara_Demo::TransitAction ()
	{
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//現在アクションが最終フレーム ならば
		if ( m_pAction->IsOverScript ( m_frame ) )
		{
			//実効アクションm_pActionは次フレーム時のMove()でm_actionIDを使って取得される
			m_actionID = m_pAction->GetNextID ();
			//各種状態の終了
			m_btlPrm.EndAction ();
			m_frame = 0;
			//今回のフレーム中はm_pActionとm_pScriptを用い、
			//これ以降はm_actionIDとm_frameを用いない

			//m_frameは0から開始、Move()とDraw()で同一スクリプトを処理する
			//このフレームでスクリプトを処理するため、移行先アクションとスクリプトを保存
			m_pAction = m_pChara->GetpAction ( m_actionID );
			m_pScript = m_pAction->GetpScript ( m_frame );
		}
		else
		{
			//m_frameは0から開始、Move()とDraw()で同一スクリプトを処理する
			//このフレームでスクリプトを処理するため、移行先アクションとスクリプトを保存
			m_pAction = m_pChara->GetpAction ( m_actionID );
			m_pScript = m_pAction->GetpScript ( m_frame );

			//通常処理：スクリプトを１つ進める
			++ m_frame;
		}

		assert ( nullptr != m_pAction && nullptr != m_pScript );
	}



	//グラフィック更新
	void ExeChara_Demo::UpdateGraphic ()
	{
		//メインイメージ
		m_dispChara.UpdateMainImage ( m_pScript, m_btlPrm.GetPos (), m_btlPrm.GetDirRight () );
	}


	void ExeChara_Demo::AlwaysPostMove ()
	{
		m_btlPrm.Move ();	//タイマー稼働
	}


}	//namespace GAME

