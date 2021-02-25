//=================================================================================================
//
//	Title �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "TitleConst.h"
#include "TitleEf.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Title : public Scene
	{
		P_GrpAcv	m_bg;
		P_GrpAcv	m_logo;
		P_GrpAcv	m_menu;
		P_GrpBlink	m_cursor;
		P_GrpAcv	m_demo_mode;

		TitleEf		m_titleEf;

		P_Fade		m_fade;
		UINT		m_fadeOutTimer;

		UINT		m_timer;
		bool		m_blink;

		//�ΐ��� ( PLAYER / COM )
//		MUTCH_MODE		m_muchMode;
		TITLE_MENU		m_menuPos;
		bool CsrUp ();
		bool CsrDn ();
		void SelectTR ();
		void SelectPP ();
		void SelectPC ();
		void SelectCC ();
		void SetCrsY ( int y );
		MUTCH_MODE MENU_to_MODE ( TITLE_MENU tm, PLAYER_ID id );

		//�f�����[�h�\��
		UINT	m_demoTimer;
		enum DEMO_MODE
		{
			DM_TITLE_WAIT = 360,
		};
		void DemoOn ();
		void DemoOff ();

	public:
		Title ();
		Title ( const Title& rhs ) = delete;
		~Title ();

		void ParamInit ();
		void Load ();
		void Init ();
		void Move ();

		P_GameScene Transit ();
	};



}	//namespace GAME


