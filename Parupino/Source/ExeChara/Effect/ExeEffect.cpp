//=================================================================================================
//
// ExeEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//@Later	いずれEffectにEfGnrtを統合
	//------------------------------------------

	ExeEffect::ExeEffect ( P_Effect pEffect, PVP_TxBs pvpEfTexture, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight )
	 :	  m_dispEffect ( pvpEfTexture, pEfGnrt->GetZ() )
		, m_active ( true ), m_end ( false ), m_frame ( 0 )
		, m_ptEffect ( VEC2 ( 0, 0 ) ), m_dirRight ( dirRight )
		, m_vel ( VEC2 ( 0, 0 ) ), m_acc ( VEC2 ( 0, 0 ) )
		, m_pEffect ( pEffect ), m_pScript ( nullptr ) 
		, m_bDispRect ( true )
		, m_offset ( false ), m_hit ( false )
	{
		SetpEfGnrt ( pEfGnrt );
		m_pScript = m_pEffect->GetpScript ( 0 );

		//初期位置 (キャラ位置+エフェクト発生位置)
		m_ptEffect = ptChara + Dir ( m_ptGnrt );

		//枠
		m_charaRect = make_shared < CharaRect > ();

	}

	ExeEffect::~ExeEffect ()
	{
	}

	void ExeEffect::SetpEfGnrt ( P_EfGnrt p )
	{
		m_ptGnrt = p->GetPos ();
		m_gnrt = p->GetGnrt ();
		m_loop = p->GetLoop ();
		m_sync = p->GetSync ();
	}

	void ExeEffect::PreScriptMove ()
	{
		//スクリプトを取得
		m_pScript = m_pEffect->GetpScript ( m_frame );


		//---------------------------------------------------------------------
		//エフェクト終了条件
		//画面外のとき終了
		if ( m_ptEffect.x < 0 - 100 || GAME_WIDTH + 100 < m_ptEffect.x )
		{
			m_end = true;
		}

		//現在エフェクトが最終フレームならば
		if ( m_pEffect->IsEndScript ( m_frame ) )
		{
			if ( m_loop )
			{
				m_frame = 0;	//ループ
			}
			else
			{
				m_end = true;	//終了
			}
		}
		else
		{
			++ m_frame;	//続行
		}
		//---------------------------------------------------------------------
	}

	void ExeEffect::PostScriptMove ( VEC2 ptChara, bool dirRight )
	{
		//ゲーム位置計算 (表示位置はDispで計算する)
		//@info Exeでゲーム位置を計算し、Dispで画面位置補正を加算する

		//判定後ヒット時or相殺時
		if ( m_hit || m_offset )
		{
			m_end = true;
			return;
		}

		//エフェクト基準位置
		if ( m_sync )		//キャラ同期フラグで分岐
		{
			//エフェクト位置 = キャラ位置 + 発生位置
			m_ptEffect = ptChara + Dir ( m_ptGnrt );

			//向き
			m_dirRight = dirRight;
		}

		//速度計算
		m_ptEffect += Dir ( m_pScript->GetVel () );

//		DBGOUT_WND_F ( 0, _T ( "plpos = (%d,%d)" ), ptChara.x, ptChara.y );
//		DBGOUT_WND_F ( 1, _T ( "efpos = (%d,%d)" ), m_ptEffect.x, m_ptEffect.y );

		//枠設定
		m_charaRect->SetARect ( m_pScript->GetpvARect (), dirRight, m_ptEffect );

		//表示更新
		m_dispEffect.Update ( m_pScript, m_ptEffect, dirRight );

		//枠表示
		if ( m_bDispRect )
		{
			m_dispEffect.OnRect ();
			m_dispEffect.SetpCharaRect ( m_charaRect );
		}
		else
		{
			m_dispEffect.OffRect ();
		}

	}

	void ExeEffect::SynchroScript ( VEC2 ptChara )
	{
		m_ptEffect = ptChara;
	}


}	//namespace GAME

