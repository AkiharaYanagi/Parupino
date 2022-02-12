//=================================================================================================
//
// CPUInput ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include <time.h>
#include "CPUInput.h"
#include "_GameKey.h"
#include "../../CharaData/Branch.h"
#include "../../CharaData/Action.h"
#include "../../ExeChara/ExeChara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//CPU_AIの外部ファイル化

	//※ 乱数配分 の部分のみを外部ファイルにする

	// テキストファイル
	//	[n%] [行動ID]
	//	[m%] [行動ID]
	//	……

	//先頭から読んで、確率(%)が100以上で打ち切り

	//近 [%][ID]
	//中 [%][ID]
	//遠 [%][ID]

	//３種類

	CPUInput::CPUInput ( WP_ExeChara p, WP_ExeChara pOther )
	: m_pExeChara ( p ), m_pExeCharaOther ( pOther )
	, m_vGameKeyNum ( CPU_INPUT_GAMEKEY_NUM ), m_playerID ( PLAYER_ID_1 )
	, m_bAct ( false ), m_act ( CPU_NEUTRAL ), m_actTime ( 0 ), m_timer ( 0 )
	, m_testAct ( 0 )
	{
		//ゲームキーを規定数だけ確保
		for ( UINT i = 0; i < CPU_INPUT_GAMEKEY_NUM; ++ i )
		{
			_GameKey gameKey;
			m_vGameKey.push_back ( gameKey );
		}

		//---------------------------------------------------------------------
		//	※ 乱数配分
		//
		for ( UINT i = 0; i < CENT; ++ i )
		{
			m_randomKeyNear[i] = CPU_NEUTRAL;
			if		( i < 2  ) { m_randomKeyNear[i] = CPU_FRONT; }
			else if ( i < 4  ) { m_randomKeyNear[i] = CPU_BACK;	}
			else if ( i < 6  ) { m_randomKeyNear[i] = CPU_FRONT_DASH; }
			else if ( i < 8  ) { m_randomKeyNear[i] = CPU_BACK_DASH;	}
			else if ( i < 40 ) { m_randomKeyNear[i] = CPU_L; }
			else if ( i < 55 ) { m_randomKeyNear[i] = CPU_M; }
			else if ( i < 70 ) { m_randomKeyNear[i] = CPU_H; }
			else if ( i < 99 ) { m_randomKeyNear[i] = CPU_AVOID; }

			m_randomKeyMiddle[i] = CPU_NEUTRAL;
			if		( i < 5  ) { m_randomKeyMiddle[i] = CPU_FRONT; }
			else if ( i < 10 ) { m_randomKeyMiddle[i] = CPU_BACK;	}
			else if ( i < 15 ) { m_randomKeyMiddle[i] = CPU_FRONT_DASH; }
			else if ( i < 20 ) { m_randomKeyMiddle[i] = CPU_BACK_DASH;	}
			else if ( i < 25 ) { m_randomKeyMiddle[i] = CPU_L; }
			else if ( i < 30 ) { m_randomKeyMiddle[i] = CPU_M; }
			else if ( i < 35 ) { m_randomKeyMiddle[i] = CPU_H; }
			else if ( i < 60 ) { m_randomKeyMiddle[i] = CPU_AVOID; }

			m_randomKeyFar[i] = CPU_NEUTRAL;
			if		( i < 15 ) { m_randomKeyFar[i] = CPU_FRONT; }
			else if ( i < 17 ) { m_randomKeyFar[i] = CPU_BACK;	}
			else if ( i < 25 ) { m_randomKeyFar[i] = CPU_FRONT_DASH; }
			else if ( i < 27 ) { m_randomKeyFar[i] = CPU_BACK_DASH;	}
			else if ( i < 30 ) { m_randomKeyFar[i] = CPU_L; }
			else if ( i < 33 ) { m_randomKeyFar[i] = CPU_M; }
			else if ( i < 38 ) { m_randomKeyFar[i] = CPU_H; }
			else if ( i < 40 ) { m_randomKeyFar[i] = CPU_AVOID; }
		}
		//
		//	※ 乱数配分 ここまで
		//---------------------------------------------------------------------

		//外部ファイル読込
		//エラー時はデフォルト値を使用して続行
		try
		{
			tifstream tifStrm ( _T("CPU_ACT.txt") );
			if ( ! tifStrm ) { throw; }
			if ( tifStrm.fail () ) { throw; }

			int* iBuf = nullptr;
			iBuf = new int[CPU_ACT_NUM * 3];
			UINT index = 0;

			//ファイル末尾まで読込
			while ( ! tifStrm.eof() )
			{
				//1行読込
				tstring tstr = _T("");
				tifStrm >> tstr;

				//1文字ずつ処理
				bool bComp = false;
				UINT i = 0;
				TCHAR tchNum[2] = { 0 };	//10進数2桁 (0～99)
				while ( tstr.size() != i )
				{
					TCHAR tch = tstr[i];

					// '['や改行は終了
					if ( '[' == tch || '\n' == tch ) { break; }

					tchNum [ i ] = tch;
					++i;
					if ( i == 2 ) { bComp = true; }
				}

				//完成時数値に変換
				if ( bComp )
				{
					iBuf[index] = ::_ttoi ( tchNum );
					++index;
					bComp = false;
				}
			}

			//保存
			for ( UINT i = 0; i < CPU_ACT_NUM; ++i )
			{
				m_actNear[i] = iBuf[ i ];
			}
			for ( UINT i = 0; i < CPU_ACT_NUM; ++i )
			{
				m_actMiddle[i] = iBuf[ CPU_ACT_NUM + i ];
			}
			for ( UINT i = 0; i < CPU_ACT_NUM; ++i )
			{
				m_actFar[i] = iBuf[ CPU_ACT_NUM * 2 + i];
			}

			for ( int i = 0; i < CENT; ++ i )
			{
#if	0
				m_randomKeyNear[i] = CPU_NEUTRAL;
				if		( i < m_actNear[1] ) { m_randomKeyNear[i] = CPU_FRONT; }
				else if ( i < m_actNear[2] ) { m_randomKeyNear[i] = CPU_BACK;	}
				else if ( i < m_actNear[3] ) { m_randomKeyNear[i] = CPU_FRONT_DASH; }
				else if ( i < m_actNear[4] ) { m_randomKeyNear[i] = CPU_BACK_DASH;	}
				else if ( i < m_actNear[5] ) { m_randomKeyNear[i] = CPU_L; }
				else if ( i < m_actNear[6] ) { m_randomKeyNear[i] = CPU_M; }
				else if ( i < m_actNear[7] ) { m_randomKeyNear[i] = CPU_H; }
				else if ( i < m_actNear[8] ) { m_randomKeyNear[i] = CPU_AVOID; }

				m_randomKeyMiddle[i] = CPU_NEUTRAL;
				if		( i < m_actMiddle[1] ) { m_randomKeyMiddle[i] = CPU_FRONT; }
				else if ( i < m_actMiddle[2] ) { m_randomKeyMiddle[i] = CPU_BACK;	}
				else if ( i < m_actMiddle[3] ) { m_randomKeyMiddle[i] = CPU_FRONT_DASH; }
				else if ( i < m_actMiddle[4] ) { m_randomKeyMiddle[i] = CPU_BACK_DASH;	}
				else if ( i < m_actMiddle[5] ) { m_randomKeyMiddle[i] = CPU_L; }
				else if ( i < m_actMiddle[6] ) { m_randomKeyMiddle[i] = CPU_M; }
				else if ( i < m_actMiddle[7] ) { m_randomKeyMiddle[i] = CPU_H; }
				else if ( i < m_actMiddle[8] ) { m_randomKeyMiddle[i] = CPU_AVOID; }

				m_randomKeyFar[i] = CPU_NEUTRAL;
				if		( i < m_actFar[1] ) { m_randomKeyFar[i] = CPU_FRONT; }
				else if ( i < m_actFar[2] ) { m_randomKeyFar[i] = CPU_BACK;	}
				else if ( i < m_actFar[3] ) { m_randomKeyFar[i] = CPU_FRONT_DASH; }
				else if ( i < m_actFar[4] ) { m_randomKeyFar[i] = CPU_BACK_DASH;	}
				else if ( i < m_actFar[5] ) { m_randomKeyFar[i] = CPU_L; }
				else if ( i < m_actFar[6] ) { m_randomKeyFar[i] = CPU_M; }
				else if ( i < m_actFar[7] ) { m_randomKeyFar[i] = CPU_H; }
				else if ( i < m_actFar[8] ) { m_randomKeyFar[i] = CPU_AVOID; }
#endif	//0
				SetCPU_Act ( i, m_actNear, &(m_randomKeyNear[i]) );
				SetCPU_Act ( i, m_actMiddle, &(m_randomKeyMiddle[i]) );
				SetCPU_Act ( i, m_actFar, &(m_randomKeyFar[i]) );
			}

			delete[] iBuf;
		}
		catch ( ... )
		{
			TRACE_F ( _T("CPU_ACT:読込エラー\n") );
		}

//		DBGOUT_WND->SetPos ( 0, 100, 400 );
//		DBGOUT_WND->SetPos ( 1, 400, 400 );
		srand ( (UINT) time ( nullptr ) );
	}

	CPUInput::~CPUInput ()
	{
	}

	//更新
	void CPUInput::Update ( bool dirRight )
	{
		//今回の入力をゲームキーに直して保存 (方向は右方向で、コマンド入力側で向きを反映している)
		_GameKey gameKey;

		VEC2 pos = m_pExeChara.lock()->GetPos ();
		VEC2 posOther = m_pExeCharaOther.lock()->GetPos ();

#if	0
		//バランス
		if ( m_pExeChara->GetBalance () < 200 )
		{
			if ( ::rand() % 2 == 0 )
			{
				m_actTime = 20;
				m_bAct = true;
				m_act = CPU_NEUTRAL;
			}
		}
#endif	//0

		//行動未決定ならば
		if ( ! m_bAct ) 
		{
			int r = ::rand() % 100;
#if	0
			m_testAct += 7;
			if  ( m_testAct > 99 ) { m_testAct -= 99; }
		
			int r = m_testAct;
#endif	//0
			//距離
			float distance = fabsf ( pos.x - posOther.x );
			if ( distance < 200 )
			{
//				DebugOutGameWindow::instance()->DebugOutf ( ( PLAYER_1 == m_playerID ) ? 0 : 1, _T("m_randomKeyNear") );
				m_act = m_randomKeyNear[r];
			}
			else if ( distance < 300 )
			{
//				DebugOutGameWindow::instance()->DebugOutf ( ( PLAYER_1 == m_playerID ) ? 0 : 1, _T("m_randomKeyMiddle") );
				m_act = m_randomKeyMiddle[r];
			}
			else 
			{
#if	0
				//バランス回復
				if ( m_pExeChara->GetBalance () < 200 )
				{
					if ( ::rand() % 10 == 0 )
					{
						m_act = CPU_POISED;
					}
				}
				else
#endif	//0
				{
//				DebugOutGameWindow::instance()->DebugOutf ( ( PLAYER_1 == m_playerID ) ? 0 : 1, _T("m_randomKeyFar") );
					m_act = m_randomKeyFar[r];
				}
			}
			
			
			switch ( m_act )
			{
			case CPU_FRONT:
				m_actTime = 20;
				break;
			case CPU_BACK:
				m_actTime = 20;
				break;
			case CPU_FRONT_DASH:
				m_actTime = 20;
				break;
			case CPU_BACK_DASH:
				m_actTime = 20;
				break;
			case CPU_L:
				break;
			case CPU_M:
				break;
			case CPU_H:
				break;
			case CPU_NEUTRAL:
				break;
			case CPU_AVOID:
				m_actTime = 20;
				break;
			case CPU_POISED:
				m_actTime = 20;
				break;
			default:
				break;
			};
			m_bAct = true;
		}
		//行動決定済
		else
		{
			switch ( m_act )
			{
			case CPU_FRONT:
				gameKey.SetLvr ( _GameKey::LVR_6, true );
				break;
			case CPU_BACK:
				gameKey.SetLvr ( _GameKey::LVR_4, true );
				break;
			case CPU_FRONT_DASH:
				switch ( m_timer )
				{
				case 0: gameKey.SetLvr ( _GameKey::LVR_6, true ); 	break;
				case 1:	gameKey.SetLvrOff (); break;
				default: 
					gameKey.SetLvr ( _GameKey::LVR_6, true );
					//ダッシュを維持しつつ攻撃をランダムで行う
					switch ( ::rand() % 10 )
					{
					case 0: gameKey.SetBtn ( _GameKey::BTN_0, true ); 	break;
					case 1: gameKey.SetBtn ( _GameKey::BTN_1, true ); 	break;
					case 2: gameKey.SetBtn ( _GameKey::BTN_2, true ); 	break;
					default: break;
					}

					break;
				}
				break;
			case CPU_BACK_DASH:
				switch ( m_timer )
				{
				case 0: gameKey.SetLvr ( _GameKey::LVR_4, true ); break;
				case 1:	gameKey.SetLvrOff (); break;
				default: gameKey.SetLvr ( _GameKey::LVR_4, true ); break;
				}
				break;
			case CPU_L:
				gameKey.SetBtn ( _GameKey::BTN_0, true );
				break;
			case CPU_M:
				gameKey.SetBtn ( _GameKey::BTN_1, true );
				break;
			case CPU_H:
				gameKey.SetBtn ( _GameKey::BTN_2, true );
				break;
			case CPU_AVOID:
//				gameKey.SetLvr ( _GameKey::DIR_2 );
				gameKey.SetBtn ( _GameKey::BTN_3, true );
				break;
			case CPU_POISED:
//				gameKey.SetLvr ( _GameKey::DIR_8 );
				gameKey.SetBtn ( _GameKey::BTN_3, true );
				break;
			case CPU_NEUTRAL:
				break;
			default:
				break;
			};
			if ( m_timer == m_actTime )
			{
				m_timer = 0;
				m_actTime = 0;
				m_bAct = false;
			}
			else
			{
				++m_timer;
			}
		}

		//ゲーム入力を更新しながら現在フレーム分を保存
		for ( int i = m_vGameKeyNum - 1; i >= 1; --i )
		{
			m_vGameKey[i] = m_vGameKey[i - 1];
		}
		m_vGameKey[0] = gameKey;
	}

	//ブランチリストをチェックして
	//コマンド条件が達成されていたら遷移先のアクションIDを返す
	UINT CPUInput::GetTransitID ( PVP_Branch pvpBranch, bool dirRight )
	{
		VP_Branch::iterator it = pvpBranch->begin ();
		VP_Branch::iterator it_end = pvpBranch->end ();
		for ( ; it != it_end; ++it )
		{
			P_Command pCommand = (*it)->GetpCommand().lock ();
			
			if ( pCommand->Compare ( m_vGameKey, dirRight ) )
			{
				return (*it)->GetIndexSequence ();
			}
		}
		return NO_COMPLETE;
	}

	void CPUInput::SetCPU_Act ( int index, int act[], CPU_ACT pCpu_act[] )
	{
		*pCpu_act = CPU_NEUTRAL;
		if		( index < act[1] ) { *pCpu_act = CPU_FRONT; }

//		if		( index < act[0] ) { *pCpu_act = CPU_NEUTRAL; }
//		else if	( index < act[1] ) { *pCpu_act = CPU_FRONT; }

		else if ( index < act[2] ) { *pCpu_act = CPU_BACK;	}
		else if ( index < act[3] ) { *pCpu_act = CPU_FRONT_DASH; }
		else if ( index < act[4] ) { *pCpu_act = CPU_BACK_DASH;	}
		else if ( index < act[5] ) { *pCpu_act = CPU_L; }
		else if ( index < act[6] ) { *pCpu_act = CPU_M; }
		else if ( index < act[7] ) { *pCpu_act = CPU_H; }
		else if ( index < act[8] ) { *pCpu_act = CPU_AVOID; }
		else if ( index < act[9] ) { *pCpu_act = CPU_POISED; }
	}


}	//namespace GAME

