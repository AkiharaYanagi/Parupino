//=================================================================================================
//
// CPUInput �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include <time.h>
#include "CPUInput.h"
#include "_GameKey.h"
#include "../../CharaData/Branch.h"
#include "../../CharaData/Action.h"
#include "../../ExeChara/ExeChara.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//CPU_AI�̊O���t�@�C����

	//�� �����z�� �̕����݂̂��O���t�@�C���ɂ���

	// �e�L�X�g�t�@�C��
	//	[n%] [�s��ID]
	//	[m%] [�s��ID]
	//	�c�c

	//�擪����ǂ�ŁA�m��(%)��100�ȏ�őł��؂�

	//�� [%][ID]
	//�� [%][ID]
	//�� [%][ID]

	//�R���

	CPUInput::CPUInput ( WP_ExeChara p, WP_ExeChara pOther )
	: m_pExeChara ( p ), m_pExeCharaOther ( pOther )
	, m_vGameKeyNum ( CPU_INPUT_GAMEKEY_NUM ), m_playerID ( PLAYER_ID_1 )
	, m_bAct ( false ), m_act ( CPU_NEUTRAL ), m_actTime ( 0 ), m_timer ( 0 )
	, m_testAct ( 0 )
	{
		//�Q�[���L�[���K�萔�����m��
		for ( UINT i = 0; i < CPU_INPUT_GAMEKEY_NUM; ++ i )
		{
			_GameKey gameKey;
			m_vGameKey.push_back ( gameKey );
		}

		//---------------------------------------------------------------------
		//	�� �����z��
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
		//	�� �����z�� �����܂�
		//---------------------------------------------------------------------

		//�O���t�@�C���Ǎ�
		//�G���[���̓f�t�H���g�l���g�p���đ��s
		try
		{
			tifstream tifStrm ( _T("CPU_ACT.txt") );
			if ( ! tifStrm ) { throw; }
			if ( tifStrm.fail () ) { throw; }

			int* iBuf = nullptr;
			iBuf = new int[CPU_ACT_NUM * 3];
			UINT index = 0;

			//�t�@�C�������܂œǍ�
			while ( ! tifStrm.eof() )
			{
				//1�s�Ǎ�
				tstring tstr = _T("");
				tifStrm >> tstr;

				//1����������
				bool bComp = false;
				UINT i = 0;
				TCHAR tchNum[2] = { 0 };	//10�i��2�� (0�`99)
				while ( tstr.size() != i )
				{
					TCHAR tch = tstr[i];

					// '['����s�͏I��
					if ( '[' == tch || '\n' == tch ) { break; }

					tchNum [ i ] = tch;
					++i;
					if ( i == 2 ) { bComp = true; }
				}

				//���������l�ɕϊ�
				if ( bComp )
				{
					iBuf[index] = ::_ttoi ( tchNum );
					++index;
					bComp = false;
				}
			}

			//�ۑ�
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
			TRACE_F ( _T("CPU_ACT:�Ǎ��G���[\n") );
		}

//		DBGOUT_WND->SetPos ( 0, 100, 400 );
//		DBGOUT_WND->SetPos ( 1, 400, 400 );
		srand ( (UINT) time ( nullptr ) );
	}

	CPUInput::~CPUInput ()
	{
	}

	//�X�V
	void CPUInput::Update ( bool dirRight )
	{
		//����̓��͂��Q�[���L�[�ɒ����ĕۑ� (�����͉E�����ŁA�R�}���h���͑��Ō����𔽉f���Ă���)
		_GameKey gameKey;

		VEC2 pos = m_pExeChara.lock()->GetPos ();
		VEC2 posOther = m_pExeCharaOther.lock()->GetPos ();

#if	0
		//�o�����X
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

		//�s��������Ȃ��
		if ( ! m_bAct ) 
		{
			int r = ::rand() % 100;
#if	0
			m_testAct += 7;
			if  ( m_testAct > 99 ) { m_testAct -= 99; }
		
			int r = m_testAct;
#endif	//0
			//����
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
				//�o�����X��
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
		//�s�������
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
					//�_�b�V�����ێ����U���������_���ōs��
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

		//�Q�[�����͂��X�V���Ȃ��猻�݃t���[������ۑ�
		for ( int i = m_vGameKeyNum - 1; i >= 1; --i )
		{
			m_vGameKey[i] = m_vGameKey[i - 1];
		}
		m_vGameKey[0] = gameKey;
	}

	//�u�����`���X�g���`�F�b�N����
	//�R�}���h�������B������Ă�����J�ڐ�̃A�N�V����ID��Ԃ�
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

