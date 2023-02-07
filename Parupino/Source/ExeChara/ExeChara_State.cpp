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
		if ( m_btlPrm.GetTmr_Stop ()->IsActive () )
		{
			return;
		}

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

		//入力
		pExe->Input ();
		
		//スクリプト遷移
		pExe->TransitAction ();

		// 位置計算
		pExe->CalcPos ();

		//接触枠設定
		pExe->SetCollisionRect ();
	}

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
		pExe->UpdateGraphic ();
	}




}	//namespace GAME

