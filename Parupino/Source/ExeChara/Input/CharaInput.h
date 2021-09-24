//=================================================================================================
//
// CharaInput �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../CharaData/Chara.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class CharaInput
	{
		static const UINT	m_vGameKeyNum;	//�L�[���͂̕ۑ��t���[����
		V_GAME_KEY			m_vGameKey;		//�L�[���͕ۑ�
		PLAYER_ID			m_playerID;		//�v���C���[ID
		bool				m_cpu;			//CPU�t���O

	public:
		CharaInput ();
		CharaInput ( const CharaInput& rhs ) = delete;		//�R�s�[�֎~
		virtual ~CharaInput ();

		//�v���C���[ID
		void SetPlayer ( PLAYER_ID id ) { m_playerID = id; }

		//�t���[�����ɂ�������͂̕ۑ�
		virtual void Update ( bool dirRight );

		//�L�[���͔z��̎Q��
		const V_GAME_KEY & GetvGameKey () const { return m_vGameKey; }

#if 0

		//�u�����`���X�g���`�F�b�N����
		//�R�}���h�������B������Ă�����J�ڐ�̃A�N�V������Ԃ�
		//�ߒl�Fnullptr	�s����
		P_Action GetpTransitAction ( PVP_Branch pvpBranch, bool dirRight );

		//�u�����`���X�g���`�F�b�N����
		//�R�}���h�������B������Ă�����J�ڐ�̃A�N�V����ID��Ԃ�
		//�ߒl�Fenum { NO_COMPLETE (0xFFFFFFFF) } �s����
		virtual UINT GetTransitID ( PVP_Branch pvpBranch, bool dirRight );
#endif // 0


		//���[�g���X�g���`�F�b�N���Ċe��u�����`�̃R�}���h���B������Ă�����
		//�J�ڐ�̃A�N�V����ID��Ԃ�
		//�ߒl�Fenum { NO_COMPLETE (0xFFFFFFFF) } �s����
		virtual UINT GetTransitID ( Chara & ch, P_Script pScp, bool dirRight );


		//-----------------------------------------------------------------
		//�X�N���v�g�Ŏw�肵�Ȃ����ړ��͂̏��
	private:
		_GameKeyCommand gkc_lvr4;
		_GameKeyCommand gkc_lvr1;
		_GameKeyCommand gkc_lvr4E;
		_GameKeyCommand gkc_lvr2E;
	public:
		bool IsInput4 () const { return gkc_lvr4.CompareTarget ( m_vGameKey[0] ); }
		bool IsInput1 () const { return gkc_lvr1.CompareTarget ( m_vGameKey[0] ); }
		bool IsInput4E () const { return gkc_lvr4E.CompareTarget ( m_vGameKey[0] ); }
		bool IsInput2E () const { return gkc_lvr2E.CompareTarget ( m_vGameKey[0] ); }

		//�����
//		bool IsInput4 () const { return m_vGameKey[0].IsKeyLvrCmd ( _GameKeyCommand::LVR_CMD_4 ); }

		//�㉺����
//		bool IsInput1 () const { return m_vGameKey[0].IsKeyLvrCmd ( _GameKeyCommand::LVR_CMD_1 ); }

		//��v�f�̓��͊m�F : �E������4E�A���������͕ۑ����Ɍ����͔��f����Ă���
//		bool IsInputBack () const { return m_vGameKey[0].IsKeyLvrCmd ( _GameKeyCommand::LVR_CMD_4E ); }

		//���v�f�̓��͊m�F
//		bool IsInput2E () const { return m_vGameKey[0].IsKeyLvrCmd ( _GameKeyCommand::LVR_CMD_2E ); }
	};

	using P_CharaInput = shared_ptr < CharaInput >;


}	//namespace GAME


