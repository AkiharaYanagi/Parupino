//=================================================================================================
//
// CharaInput �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "CharaInput.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//static����
	const UINT CharaInput::m_vGameKeyNum = 60;		//�L�[���͂̕ۑ��t���[����

	//�R���X�g���N�^
	CharaInput::CharaInput ()
		: m_playerID ( PLAYER_ID_1 )
	{
		for ( UINT i = 0; i < m_vGameKeyNum; ++i )
		{
			_GameKey gameKey;
			m_vGameKey.push_back ( gameKey );
		}
	}

	//�f�X�g���N�^
	CharaInput::~CharaInput ()
	{
	}

	//�X�V
	void CharaInput::Update ( bool dirRight )
	{
		//����̓��͂��Q�[���L�[�ɒ����ĕۑ�
		_GameKey gameKey;

		//�㉺�O��
		bool bKey8 = false;	//��
		bool bKey2 = false;	//��
		bool bKey4 = false;	//��(�E������)
		bool bKey6 = false;	//�O(�E������)

#if 0
		if ( PLAYER_ID_1 == m_playerID )
		{
			bKey8 = IS_KEY ( P1_UP );
			bKey2 = IS_KEY ( P1_DOWN );
			if ( dirRight )	//�E������
			{
				bKey4 = IS_KEY ( P1_LEFT );
				bKey6 = IS_KEY ( P1_RIGHT );
			}
			else	//��������
			{
				bKey4 = IS_KEY ( P1_RIGHT );
				bKey6 = IS_KEY ( P1_LEFT );
			}
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			bKey8 = IS_KEY ( P2_UP );
			bKey2 = IS_KEY ( P2_DOWN );
			if ( dirRight )	//�E������
			{
				bKey4 = IS_KEY ( P2_LEFT );
				bKey6 = IS_KEY ( P2_RIGHT );
			}
			else	//��������
			{
				bKey4 = IS_KEY ( P2_RIGHT );
				bKey6 = IS_KEY ( P2_LEFT );
			}
		}
#endif // 0
		if ( PLAYER_ID_1 == m_playerID )
		{
			bKey8 = CFG_IS_KEY ( _P1_UP );
			bKey2 = CFG_IS_KEY ( _P1_DOWN );
			if ( dirRight )	//�E������
			{
				bKey4 = CFG_IS_KEY ( _P1_LEFT );
				bKey6 = CFG_IS_KEY ( _P1_RIGHT );
			}
			else	//��������
			{
				bKey4 = CFG_IS_KEY ( _P1_RIGHT );
				bKey6 = CFG_IS_KEY ( _P1_LEFT );
			}
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			bKey8 = CFG_IS_KEY ( _P2_UP );
			bKey2 = CFG_IS_KEY ( _P2_DOWN );
			if ( dirRight )	//�E������
			{
				bKey4 = CFG_IS_KEY ( _P2_LEFT );
				bKey6 = CFG_IS_KEY ( _P2_RIGHT );
			}
			else	//��������
			{
				bKey4 = CFG_IS_KEY ( _P2_RIGHT );
				bKey6 = CFG_IS_KEY ( _P2_LEFT );
			}
		}

		//3�ȏ㓯�������͗D�揇�ŏ���

		// �R�}���h�w��ł�12369874��

		//�΂ߗD��
		if ( bKey4 && bKey2 )	{ gameKey.SetLvr ( _GameKey::LVR_1, true ); }
		if ( bKey2 )			{ gameKey.SetLvr ( _GameKey::LVR_2, true ); }
		if ( bKey6 && bKey2 )	{ gameKey.SetLvr ( _GameKey::LVR_3, true ); }
		if ( bKey6 )			{ gameKey.SetLvr ( _GameKey::LVR_6, true ); }
		if ( bKey8 && bKey6 )	{ gameKey.SetLvr ( _GameKey::LVR_9, true ); }
		if ( bKey8 )			{ gameKey.SetLvr ( _GameKey::LVR_8, true ); }
		if ( bKey8 && bKey4 )	{ gameKey.SetLvr ( _GameKey::LVR_7, true ); }
		if ( bKey4 )			{ gameKey.SetLvr ( _GameKey::LVR_4, true ); }


		//==============================================================================
		//�{�^��
		bool bButton0 = false; bool bButton1 = false; bool bButton2 = false; bool bButton3 = false;
		bool bButton4 = false; bool bButton5 = false; bool bButton6 = false; bool bButton7 = false;
#if 0
		if ( PLAYER_ID_1 == m_playerID )
		{
			bButton0 = IS_KEY ( P1_BTN1 );
			bButton1 = IS_KEY ( P1_BTN2 );
			bButton2 = IS_KEY ( P1_BTN3 );
			bButton3 = IS_KEY ( P1_BTN4 );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			bButton0 = IS_KEY ( P2_BTN1 );
			bButton1 = IS_KEY ( P2_BTN2 );
			bButton2 = IS_KEY ( P2_BTN3 );
			bButton3 = IS_KEY ( P2_BTN4 );
		}
#endif // 0
		if ( PLAYER_ID_1 == m_playerID )
		{
			bButton0 = CFG_IS_KEY ( _P1_BTN0 );
			bButton1 = CFG_IS_KEY ( _P1_BTN1 );
			bButton2 = CFG_IS_KEY ( _P1_BTN2 );
			bButton3 = CFG_IS_KEY ( _P1_BTN3 );
			bButton4 = CFG_IS_KEY ( _P1_BTN4 );
			bButton5 = CFG_IS_KEY ( _P1_BTN5 );
			bButton6 = CFG_IS_KEY ( _P1_BTN6 );
			bButton7 = CFG_IS_KEY ( _P1_BTN7 );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			bButton0 = CFG_IS_KEY ( _P2_BTN1 );
			bButton1 = CFG_IS_KEY ( _P2_BTN2 );
			bButton2 = CFG_IS_KEY ( _P2_BTN3 );
			bButton3 = CFG_IS_KEY ( _P2_BTN4 );
			bButton4 = CFG_IS_KEY ( _P2_BTN4 );
			bButton5 = CFG_IS_KEY ( _P2_BTN5 );
			bButton6 = CFG_IS_KEY ( _P2_BTN6 );
			bButton7 = CFG_IS_KEY ( _P2_BTN7 );
		}


		gameKey.SetBtn ( 0, bButton0 );
		gameKey.SetBtn ( 1, bButton1 );
		gameKey.SetBtn ( 2, bButton2 );
		gameKey.SetBtn ( 3, bButton3 );
		gameKey.SetBtn ( 4, bButton4 );
		gameKey.SetBtn ( 5, bButton5 );
		gameKey.SetBtn ( 6, bButton6 );
		gameKey.SetBtn ( 7, bButton7 );


		//�O��̃L�[������ɂ��ۑ�����
		gameKey.ReservePrevious ( m_vGameKey[0] );


		//�Q�[�����͂��X�V���Ȃ��猻�݃t���[������ۑ�
		for ( int i = m_vGameKeyNum - 1; i >= 1; -- i )
		{
			m_vGameKey[i] = m_vGameKey[i - 1];
		}
		m_vGameKey[0] = gameKey;
	}


	//------------------------------------------------------------------------------------
	//���[�g���X�g���`�F�b�N���Ċe��u�����`�̃R�}���h���B������Ă�����
	//�J�ڐ�̃A�N�V����ID��Ԃ�
	//�ߒl�Fenum { NO_COMPLETE (0xFFFFFFFF) } �s����
	UINT CharaInput::GetTransitID ( Chara & ch, P_Script pScp, bool dirRight )
	{
		//�L�����̎����[�g,�u�����`,�R�}���h�̎Q��
		const VP_Route vpRoute = ch.GetvpRoute ();
		const VP_Branch vpBranch = ch.GetvpBranch ();
		const VP_Command vpCommand = ch.GetvpCommand ();
		
		//�X�N���v�g�̎����[�g���X�g
		for ( UINT indexRoute : pScp->GetvRouteID () )
		{
			const V_UINT vBranchID = vpRoute[indexRoute]->GetvIDBranch ();

			//�Ώۂ̃u�����`���X�g
			for ( UINT indexBranch : vBranchID )
			{
				//�R�}���h����ȊO�͔�΂�
				if ( BRC_CMD != vpBranch[indexBranch]->GetCondition () ) { continue; }

				//�R�}���h�擾
				UINT indexCommand = vpBranch[indexBranch]->GetIndexCommand ();
				P_Command pCmd = vpCommand[indexCommand];

				//�ΏۃR�}���h���������Ă�����
				if ( pCmd->Compare ( m_vGameKey, dirRight ) )
				{
					//�J�ڐ�A�N�V����ID��Ԃ�
					return vpBranch[indexBranch]->GetIndexSequence ();
				}
			}
		}
		//�s�����̂Ƃ�
		return NO_COMPLETE;
	}


}	//namespace GAME

