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
#include "PauseMenu.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class FtgMain : public Scene
	{
		P_FTG			m_fighting;

		bool			m_menu;
		P_PauseMenu		m_pauseMenu;

	public:
		FtgMain ();
		FtgMain ( const FtgMain & rhs ) = delete;
		~FtgMain ();

		void ParamInit ();
		void Init ();
		void Move ();

		P_GameScene Transit ();
		void SetpParam ( P_Param && pParam );
	};


}	//namespace GAME


