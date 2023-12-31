//=================================================================================================
//
//	ExeChara ステート
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara_State.h"
#include "ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	void CHST_Greeting::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->SetAction ( _T ( "Start_Demo" ) );		//アクション・スクリプト初期化
	}

	void CHST_Greeting::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
//		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
//		pExe->SetCollisionRect ();	//接触枠設定
		pExe->EffectMove ();		//エフェクト生成と動作

	}

	void CHST_Greeting::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->MoveTimer ();		//タイマ稼働
//		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
	}


	//------------------------------------------------
	void CHST_GetReady::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->SetAction ( _T ( "Start_N" ) );		//アクション・スクリプト初期化
	}

	void CHST_GetReady::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
//		pExe->SetCollisionRect ();	//接触枠設定
		pExe->EffectMove ();		//エフェクト生成と動作
	}

	void CHST_GetReady::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->MoveTimer ();		//タイマ稼働
//		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
	}


	//------------------------------------------------
	void CHST_Main::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->Init ();
		pExe->SetAction ( _T ( "Stand" ) );		//アクション・スクリプト初期化
	}

	void CHST_Main::PreScriptMove ()
	{
#if 0
		//一時停止のときは何もしない
		if ( m_btlPrm.GetTmr_Stop ()->IsActive () ) { return; }

		// アクションとスクリプトによらない一定の処理
		//	入力など
		AlwaysMove ();

		// ヒットストップ時は入力の保存と表示関連の処理をして終了
		//Activeとの兼ね合いでタイマーのラストは有効　0～N-1まで
		if ( ! m_btlPrm.GetTmr_HitStop ()->IsLast () )
		{
			if ( m_btlPrm.GetTmr_HitStop ()->IsActive () ) { return; }
		}

		// アクション移項
		TransitAction ();

		// 位置計算
		m_btlPrm.CalcPos ( m_pScript );

		// 着地
		Landing ();

		//接触枠設定
		AdjustCRect ();
#endif // 0

		//一時参照
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		

		//ヒットストップ時は以降を飛ばす
		if ( pExe->IsHitStop () ) { return; }

		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
		pExe->OverEfPart ();		//EfPart重なり
		pExe->EffectMove ();		//エフェクト生成と動作
	}

	// AlwaysMove () アクションとスクリプトによらない一定の処理
#if 0
	void ExeChara::AlwaysMove ()
	{
		//ダメージ分のライフ表示減少
		int dmg = m_btlPrm.GetDamage ();
		if ( 0 < dmg ) { m_btlPrm.SetDamage ( dmg - 1 ); }

		//---------------------------------------------------
		//デモカウント
		//ダウン状態のとき
		if ( CHST_DOWN == m_charaState )
		{
			if ( ! m_btlPrm.GetTmr_Down ()->IsActive () )
			{
				m_charaState = CHST_DOWN_END;
			}
		}

		//勝利待機状態のとき
		if ( CHST_WIN_WAIT == m_charaState )
		{
#if 0
			//地上ニュートラルなら
			if ( IsBasicAction ( BA_STAND ) )
			{
				//勝利状態に移行
				m_actionID = m_pChara->GetBsAction ( BA_WIN );
				TransitAction ( m_actionID );
				m_tmrEnd->Start ();
				m_charaState = CHST_WIN;
}
#endif // 0
		}

		//勝利状態のとき
		if ( CHST_WIN == m_charaState )
		{
			//if ( ! m_tmrEnd->IsActive () )
			if ( ! m_btlPrm.GetTmr_End ()->IsActive () )
			{
				m_charaState = CHST_WIN_END;
			}
		}
		//---------------------------------------------------
		//SE
		if ( m_btlPrm.GetFirstEf () )
		{
			SOUND->Play ( SE_Hit );
			m_btlPrm.SetFirstEf ( F );
		}

		//---------------------------------------------------
		//入力
		Input ();
	}
#endif // 0

	void CHST_Main::RectMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->SetRect ();		//枠設定
	}

	void CHST_Main::PostScriptMove ()
	{
#if 0
		//1[F]に一度行う処理
		//AlwaysPostMove
		m_btlPrm.TimerMove ();	//タイマー稼働

		//一時停止のときは何もしない
		if ( m_btlPrm.GetStop () ) { return; }
#endif // 0

		//一時参照
		P_ExeChara pExe = GetwpExeChara ().lock ();

		pExe->MoveTimer ();		//タイマ稼働
		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
	}


}	//namespace GAME

