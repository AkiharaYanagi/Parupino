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

		//���[�g���X�g���`�F�b�N���Ċe��u�����`�̃R�}���h���B������Ă�����
		//�J�ڐ�̃A�N�V����ID��Ԃ�
		//�ߒl�Fenum { NO_COMPLETE (0xFFFFFFFF) } �s����
		virtual UINT GetTransitID ( Chara & ch, P_Script pScp, bool dirRight );

		//�L�[�̕ۑ�
		void SetGameKey ( V_GAME_KEY & vKey );

	};

	using P_CharaInput = shared_ptr < CharaInput >;


}	//namespace GAME


