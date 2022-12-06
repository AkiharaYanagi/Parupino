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
	};

	using P_Param = shared_ptr < Param >;


}	//namespace GAME

