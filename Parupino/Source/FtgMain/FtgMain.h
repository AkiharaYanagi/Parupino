//=================================================================================================
//
//	FtgMain �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "Fighting.h"
#include "Menu/PauseMenu.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class FtgMain : public Scene, public enable_shared_from_this < FtgMain >
	{
		//�퓬
		P_FTG			m_fighting;

		//�|�[�Y���j��
		P_PauseMenu		m_pauseMenu;

		//�J�ڐ�V�[��
		P_Scene			m_scene;
		P_GameScene		m_gameScene;

	public:
		FtgMain ();
		FtgMain ( const FtgMain & rhs ) = delete;
		~FtgMain ();

		void Load ();
		void ParamInit ();
		void Move ();

		P_GameScene Transit ();

		void Transit_Title ();
		void Resume_Fighting ();
	};

	using P_FtgMain = shared_ptr < FtgMain >;


}	//namespace GAME


