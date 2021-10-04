//=================================================================================================
//
// CharaInput �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "CharaInput.h"
//#include "CharaData/Branch.h"
//#include "CharaData/Action.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//static����
	const UINT CharaInput::m_vGameKeyNum = 20;		//�L�[���͂̕ۑ��t���[����

	//�R���X�g���N�^
	CharaInput::CharaInput () : 
		m_playerID ( PLAYER_ID_1 )
	{
		for ( UINT i = 0; i < m_vGameKeyNum; ++i )
		{
			_GameKey gameKey;
			m_vGameKey.push_back ( gameKey );
		}

#if 0

		//�X�N���v�g�Ŏw�肵�Ȃ����ړ��͂̏��
		gkc_lvr4.SetLvr ( _GameKeyCommand::LVR_CMD_4, _GameKeyCommand::GAME_KEY_IS );
		gkc_lvr1.SetLvr ( _GameKeyCommand::LVR_CMD_1, _GameKeyCommand::GAME_KEY_IS );
		gkc_lvr4E.SetLvr ( _GameKeyCommand::LVR_CMD_4E, _GameKeyCommand::GAME_KEY_IS );
		gkc_lvr2E.SetLvr ( _GameKeyCommand::LVR_CMD_2E, _GameKeyCommand::GAME_KEY_IS );

#endif // 0
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

		//�{�^��
		bool bButton0 = false;
		bool bButton1 = false;
		bool bButton2 = false;
		bool bButton3 = false;
		if ( PLAYER_ID_1 == m_playerID )
		{
			bButton0 = IS_KEY ( P1_BUTTON1 );
			bButton1 = IS_KEY ( P1_BUTTON2 );
			bButton2 = IS_KEY ( P1_BUTTON3 );
			bButton3 = IS_KEY ( P1_BUTTON4 );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			bButton0 = IS_KEY ( P2_BUTTON1 );
			bButton1 = IS_KEY ( P2_BUTTON2 );
			bButton2 = IS_KEY ( P2_BUTTON3 );
			bButton3 = IS_KEY ( P2_BUTTON4 );
		}

//		if ( bButton0 )
		if ( bKey6 )
		{
			int i = 0;
		}

		gameKey.SetBtn ( 0, bButton0 );
		gameKey.SetBtn ( 1, bButton1 );
		gameKey.SetBtn ( 2, bButton2 );
		gameKey.SetBtn ( 3, bButton3 );


		//�O��̃L�[������ɂ��ۑ�����
		gameKey.ReservePrevious ( m_vGameKey[0] );


		//�Q�[�����͂��X�V���Ȃ��猻�݃t���[������ۑ�
		for ( int i = m_vGameKeyNum - 1; i >= 1; -- i )
		{
			m_vGameKey[i] = m_vGameKey[i - 1];
		}
		m_vGameKey[0] = gameKey;
	}

#if 0

	//�u�����`���X�g���`�F�b�N����
	//�R�}���h�������B������Ă�����J�ڐ�̃A�N�V������Ԃ�
	P_Action CharaInput::GetpTransitAction ( PVP_Branch pvpBranch, bool dirRight )
	{
		VP_Branch::iterator it = pvpBranch->begin ();
		VP_Branch::iterator it_end = pvpBranch->end ();
		for ( ; it != it_end; ++it )
		{
			if ( (*it)->GetpCommand().lock()->Compare ( m_vGameKey, dirRight ) )
			{
				return dynamic_pointer_cast < Action > ( (*it)->GetpSequence ().lock() );
			}
		}
		return nullptr;
	}

	//�u�����`���X�g���`�F�b�N����
	//�R�}���h�������B������Ă�����J�ڐ�̃A�N�V����ID��Ԃ�
	UINT CharaInput::GetTransitID ( PVP_Branch pvpBranch, bool dirRight )
	{
		VP_Branch::iterator it = pvpBranch->begin ();
		VP_Branch::iterator it_end = pvpBranch->end ();
		for ( ; it != it_end; ++it )
		{
			P_Command pCommand = (*it)->GetpCommand().lock();
			if ( pCommand->Compare ( m_vGameKey, dirRight ) )
			{
				return (*it)->GetIndexAction ();
			}
		}
		return NO_COMPLETE;
	}

#endif // 0


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
					return vpBranch[indexBranch]->GetIndexAction ();
				}
			}
		}
		//�s�����̂Ƃ�
		return NO_COMPLETE;
	}


}	//namespace GAME

