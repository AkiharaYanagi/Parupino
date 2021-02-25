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
		bool			m_demo;			//�f�����[�h���ǂ���
		bool			m_battleStart;	//�o�g������X�^�[�g
		bool			m_training;		//�g���[�j���O���[�h

		MUTCH_MODE		m_mutchMode;	//�ΐ���
//		PLAYER_MODE		m_mode1P;		//�PP�Q�[�����[�h
//		PLAYER_MODE		m_mode2P;		//�QP�Q�[�����[�h

		CHARA_NAME		m_charaName1p;	//�PP�L������
		CHARA_NAME		m_charaName2p;	//�QP�L������

	public:
		Param ();
		Param ( const Param & rhs );	//�R�s�[�\
		~Param ();

		//�f��
		void SetDemo ( bool b ) { m_demo = b; }
		bool GetDemo () const { return m_demo; }

		//�o�g������J�n
		void SetBattleStart ( bool b ) { m_battleStart = b; }
		bool GetBattleStart () const { return m_battleStart; }

		//�g���[�j���O���[�h
		void SetTraining ( bool b ) { m_training = b; }
		bool GetTraining () const { return m_training; }

		//�ΐ���
		MUTCH_MODE	GetMutchMode () const { return m_mutchMode; }
		void SetMutchMode ( MUTCH_MODE m ) { m_mutchMode = m; }
		void SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p );
		PLAYER_MODE GetMode ( PLAYER_ID id ) const;

		//�L������
		CHARA_NAME GetCharaName ( PLAYER_ID id ) const
		{ 
			return ( PLAYER_ID_1 == id ) ? m_charaName1p : m_charaName2p; 
		}
		void SetCharaName1p ( CHARA_NAME name ) { m_charaName1p = name; }
		CHARA_NAME GetCharaName1p () const { return m_charaName1p; }
		void SetCharaName2p ( CHARA_NAME name ) { m_charaName2p = name; }
		CHARA_NAME GetCharaName2p () const { return m_charaName2p; }

		void SetRandomChara ();
		void SetRandomChara2p ();
		 
	};

	using P_Param = shared_ptr < Param >;


}	//namespace GAME

