//=================================================================================================
//
// CPUInput �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Branch.h"
#include "Action.h"
#include "CPUInput.h"
#include "_GameKey.h"
#include "../../ExeChara/ExeChara.h"

#include <array>


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
	, m_actNear { 0 }, m_actMiddle{ 0 }, m_actFar{ 0 }
	, m_randomKeyNear { CPU_NEUTRAL }, m_randomKeyMiddle{ CPU_NEUTRAL }, m_randomKeyFar{ CPU_NEUTRAL }
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
			else if ( i < 55 ) { m_randomKeyNear[i] = CPU_Ma; }
			else if ( i < 70 ) { m_randomKeyNear[i] = CPU_Mb; }
			else if ( i < 99 ) { m_randomKeyNear[i] = CPU_H; }

			m_randomKeyMiddle[i] = CPU_NEUTRAL;
			if		( i < 5  ) { m_randomKeyMiddle[i] = CPU_FRONT; }
			else if ( i < 10 ) { m_randomKeyMiddle[i] = CPU_BACK;	}
			else if ( i < 15 ) { m_randomKeyMiddle[i] = CPU_FRONT_DASH; }
			else if ( i < 20 ) { m_randomKeyMiddle[i] = CPU_BACK_DASH;	}
			else if ( i < 25 ) { m_randomKeyMiddle[i] = CPU_L; }
			else if ( i < 30 ) { m_randomKeyMiddle[i] = CPU_Ma; }
			else if ( i < 35 ) { m_randomKeyMiddle[i] = CPU_Mb; }
			else if ( i < 60 ) { m_randomKeyMiddle[i] = CPU_H; }

			m_randomKeyFar[i] = CPU_NEUTRAL;
			if		( i < 15 ) { m_randomKeyFar[i] = CPU_FRONT; }
			else if ( i < 17 ) { m_randomKeyFar[i] = CPU_BACK;	}
			else if ( i < 25 ) { m_randomKeyFar[i] = CPU_FRONT_DASH; }
			else if ( i < 27 ) { m_randomKeyFar[i] = CPU_BACK_DASH;	}
			else if ( i < 30 ) { m_randomKeyFar[i] = CPU_L; }
			else if ( i < 33 ) { m_randomKeyFar[i] = CPU_Ma; }
			else if ( i < 38 ) { m_randomKeyFar[i] = CPU_Mb; }
			else if ( i < 40 ) { m_randomKeyFar[i] = CPU_H; }
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

			std::array < int, CPU_ACT_NUM * 3 > iBuf = { 0 };
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
					if ( i == 2 ) { bComp = T; }
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
				SetCPU_Act ( i, m_actNear, m_randomKeyNear [ i ] );
				SetCPU_Act ( i, m_actMiddle, m_randomKeyMiddle [ i ] );
				SetCPU_Act ( i, m_actFar, m_randomKeyFar [ i ] );
			}
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
		//����̓��͂��Q�[���L�[�ɒ����ĕۑ�
		//  (�Q�[���L�[�ۑ��͉E�������ʂŁA�R�}���h���͑��Ō����𔽉f���Ă���)
		_GameKey gameKey;

		VEC2 pos = m_pExeChara.lock()->GetPos ();
		VEC2 posOther = m_pExeCharaOther.lock()->GetPos ();

		//�s��������Ȃ��
		if ( ! m_bAct ) 
		{
			int r = ::rand() % 100;

			//�����ʂōs�����擾
			float distance = fabsf ( pos.x - posOther.x );
			if ( distance < 200 )
			{
				m_act = m_randomKeyNear[r];
			}
			else if ( distance < 300 )
			{
				m_act = m_randomKeyMiddle[r];
			}
			else 
			{
				m_act = m_randomKeyFar[r];
			}
			
			//�s������
			switch ( m_act )
			{
			case CPU_NEUTRAL:					break;
			case CPU_FRONT:		m_actTime = 20;	break;
			case CPU_BACK:		m_actTime = 20;	break;
			case CPU_FRONT_DASH:m_actTime = 20; break;
			case CPU_BACK_DASH:	m_actTime = 20; break;
			case CPU_L:			m_actTime = 6;	break;
			case CPU_Ma:		m_actTime = 6;	break;
			case CPU_Mb:		m_actTime = 6;	break;
			case CPU_H:			m_actTime = 6;	break;
			case CPU_POISED:	m_actTime = 20;	break;
			default:							break;
			};
			m_bAct = T;
		}

		//�s�������
		if ( m_bAct )
		{
			switch ( m_act )
			{
			case CPU_FRONT: gameKey.SetLvr ( _GameKey::LVR_6, T );	break;
			case CPU_BACK: gameKey.SetLvr ( _GameKey::LVR_4, T );	break;
			case CPU_FRONT_DASH:
				switch ( m_timer )
				{
				case 0: gameKey.SetLvr ( _GameKey::LVR_6, T ); 	break;
				case 1:	gameKey.SetLvrOff (); break;
				default: 
					gameKey.SetLvr ( _GameKey::LVR_6, T );
					//�_�b�V�����ێ����U���������_���ōs��
					switch ( ::rand() % 10 )
					{
					case 0: gameKey.SetBtn ( _GameKey::BTN_0, T ); 	break;
					case 1: gameKey.SetBtn ( _GameKey::BTN_1, T ); 	break;
					case 2: gameKey.SetBtn ( _GameKey::BTN_2, T ); 	break;
					case 3: gameKey.SetBtn ( _GameKey::BTN_3, T ); 	break;
					default: break;
					}

					break;
				}
				break;
			case CPU_BACK_DASH:
				switch ( m_timer )
				{
				case 0: gameKey.SetLvr ( _GameKey::LVR_4, T ); break;
				case 1:	gameKey.SetLvrOff (); break;
				default: gameKey.SetLvr ( _GameKey::LVR_4, T ); break;
				}
				break;
			case CPU_L:	gameKey.SetBtn ( _GameKey::BTN_0, T );	break;
			case CPU_Ma:gameKey.SetBtn ( _GameKey::BTN_1, T );	break;
			case CPU_Mb:gameKey.SetBtn ( _GameKey::BTN_2, T );	break;
			case CPU_H: gameKey.SetBtn ( _GameKey::BTN_3, T );	break;
			case CPU_POISED: gameKey.SetBtn ( _GameKey::BTN_3, T );		break;
			case CPU_NEUTRAL:	break;
			default:	break;
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

		//�O��̃L�[������ɂ��ۑ�����
		gameKey.ReservePrevious ( m_vGameKey[ 0 ] );

		//�Q�[�����͂��X�V���Ȃ��猻�݃t���[������ۑ�
		for ( int i = m_vGameKeyNum - 1; i >= 1; --i )
		{
			m_vGameKey[i] = m_vGameKey[i - 1];
		}
		m_vGameKey[0] = gameKey;


		//�e�N���X�ɔ��f
		CharaInput::SetGameKey ( m_vGameKey );
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

	void CPUInput::SetCPU_Act ( int index, ARY_INT act, CPU_ACT& cpu_act )
	{
		cpu_act = CPU_NEUTRAL;
		if		( index < act[1] ) { cpu_act = CPU_FRONT; }
		else if ( index < act[2] ) { cpu_act = CPU_BACK;	}
		else if ( index < act[3] ) { cpu_act = CPU_FRONT_DASH; }
		else if ( index < act[4] ) { cpu_act = CPU_BACK_DASH;	}
		else if ( index < act[5] ) { cpu_act = CPU_L; }
		else if ( index < act[6] ) { cpu_act = CPU_Ma; }
		else if ( index < act[7] ) { cpu_act = CPU_Mb; }
		else if ( index < act[8] ) { cpu_act = CPU_H; }
		else if ( index < act[9] ) { cpu_act = CPU_POISED; }
	}


}	//namespace GAME

