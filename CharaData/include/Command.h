//=================================================================================================
//
// Command �w�b�_�t�@�C��
//	�Q�[�����̓L�[�̔z������̑g�ݍ��킹�ŕێ�����
//	���ۂɓ��͂��ꂽ���̂̋L�^�ƁA�X�N���v�g����̏����ɗp����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define.h"
#include "_GameKeyCommand.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Command
	{
		tstring			m_name;			//���O
		V_GAME_KEY_CMD	m_vecGameKey;	//�L�[�z��
		UINT			m_limitTime;	//���͎�t����

	public:
		Command ();
		Command ( const Command & rhs ) = delete;	//�R�s�[�֎~
		~Command ();

		//��r
		bool Compare ( const V_GAME_KEY & vecGameKey, bool dirRight );

		//���O
		tstring GetName () const { return m_name; }
		void SetName ( tstring name ) { m_name.assign ( name ); }

		//�L�[�z��
		void AddGameKey ( _GameKeyCommand gkc ) { m_vecGameKey.push_back ( gkc ); }
		void SetaGameKey ( _GameKeyCommand gkca [], UINT size );

		//���͎�t����
		UINT GetLimitTime () const { return m_limitTime; }
		void SetLimitTime ( UINT limitTime ) { m_limitTime = limitTime; }
	};

	using WP_Command = std::weak_ptr < Command >;
	using P_Command = std::shared_ptr < Command >;
	using VP_Command = std::vector < P_Command >;

}	//namespace GAME


