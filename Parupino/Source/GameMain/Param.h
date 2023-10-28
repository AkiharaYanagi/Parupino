//=================================================================================================
//
// �p�����[�^�w�b�_
//		�Q�[�����ŃV�[���Ԃ��܂����l
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameConst.h"
#include "GameSettingFile.h"
#include "SceneCommon.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Param	: public GameParam
	{
		//�Q�[���ݒ� ( �O���t�@�C���Ǎ� )
		GameSettingFile		m_setting;

		//�����ݒ�
		MUTCH_MODE			m_mutchMode = MODE_PLAYER_PLAYER;

		//���U���g�p
		PLAYER_ID		m_winner;	//����
		int				m_n_act_1p;	//�A�N�V������
		int				m_n_act_2p;	//�A�N�V������

	public:
		Param ();
		Param ( const Param & rhs );	//�R�s�[�\
		~Param ();

		GameSettingFile GetGameSetting () const { return m_setting; }
		void SetSettingFile ( GameSettingFile stg ) { m_setting = stg; }

		void SetMutchMode ( MUTCH_MODE mode ) { m_mutchMode = mode; }
		void SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p );
		MUTCH_MODE GetMutchMode () const { return m_mutchMode; }

		PLAYER_MODE GetPlayerMode ( PLAYER_ID id ) const;

		void SetRandomChara ();


		//���U���g�p
		void SetWinner ( PLAYER_ID plr ) { m_winner = plr; }
		PLAYER_ID GetWinner ( PLAYER_ID plr ) const { return m_winner; }

		void SetN_Act1p ( int n ) { m_n_act_1p = n; }
		int GetN_Act1p () const { return m_n_act_1p; }

		void SetN_Act2p ( int n ) { m_n_act_2p = n; }
		int GetN_Act2p () const { return m_n_act_2p; }
	};

	using P_Param = shared_ptr < Param >;


}	//namespace GAME

