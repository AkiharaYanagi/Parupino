//=================================================================================================
//
//	Demo �w�b�_�t�@�C��
//		�^�C�g���ɑ���V�[���Ƃ��ăf����Ԃ��ė�����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgMain/FtgMain.h"	
#include "../GameMain/Scene.h"
#include "DemoMenu.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DemoMain : public Scene, public enable_shared_from_this < DemoMain >
	{
		//���j��
		P_DemoMenu	m_menu;

		//�퓬
		P_FTG		m_fighting;

		//�|�[�Y
		P_GrpAcv	m_pause;

		//�J�ڃV�[��
		P_GameScene		m_scene;

	public:
		DemoMain ();
		DemoMain ( const DemoMain & rhs ) = delete;
		~DemoMain ();

		void ParamInit ();

		P_GameScene Transit ();

		//�V�[���ύX
		void To_1v2 ();
		void To_1vC ();
		void To_Cv2 ();
		void To_CvC ();

	private:
		void Pause ();
	};


	using P_DemoMain = std::shared_ptr < DemoMain >;


}	//namespace GAME


