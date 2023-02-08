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

		//ヒットストップ時は飛ばす
		if ( pExe->IsHitStop () )
		{
			return;
		}

		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
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
#if 0
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//一時停止のときは何もしない
		if ( m_btlPrm.GetStop () ) { return; }

		//相殺枠設定
		m_charaRect->SetORect ( m_pScript->GetpvORect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );

		//攻撃枠設定
		// ヒット時に後の攻撃枠を一時停止(多段防止)
		//攻撃成立時・打合時に同一アクション中のみ枠を消失させる
		if ( m_btlPrm.GetHitEst () || m_btlPrm.GetClang () )
		{
			m_charaRect->ResetARect ();
		}
		else
		{
			m_charaRect->SetARect ( m_pScript->GetpvARect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
		}

		//攻撃力設定
//		m_power = m_pScript->GetPower ();

		//当り枠設定
		m_charaRect->SetHRect ( m_pScript->GetpvHRect (), m_btlPrm.GetDirRight (), m_btlPrm.GetPos () );
#endif // 0

		//一時参照
		P_ExeChara pExe = GetwpExeChara ().lock ();

		//枠設定
		pExe->SetRect ();
	}

	void CHST_Main::PostScriptMove ()
	{
#if 0
		assert ( nullptr != m_pAction && nullptr != m_pScript );

		//1[F]に一度行う処理
		AlwaysPostMove ();

		//一時停止のときは何もしない
		if ( m_btlPrm.GetStop () ) { return; }

		//ライフ判定
		CheckLife ();

		// グラフィック
		UpdateGraphic ();
#endif // 0

		//一時参照
		P_ExeChara pExe = GetwpExeChara ().lock ();

		//ライフ判定
		pExe->MoveTimer ();

		//ライフ判定
		pExe->CheckLife ();

		//グラフィックの更新
		pExe->UpdateGraphic ();
	}

#if 0
	void ExeChara::AlwaysPostMove ()
	{
		m_btlPrm.TimerMove ();	//タイマー稼働
	}
#endif // 0




}	//namespace GAME

