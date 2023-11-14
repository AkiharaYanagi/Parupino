//=================================================================================================
//
//	DemoMenu �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "DemoMenuItem.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DemoMenu : public TASK_VEC
	{
		P_PrmRect		m_BG;			//�w�i
		P_Str			m_strDemo;		//�f���\��
		P_GrpAcv		m_arrow;		//�I����

		//�f�����ڕ\��
		P_GrpAcv		m_1p_vs_2p;
		P_GrpAcv		m_1p_vs_cpu;
		P_GrpAcv		m_cpu_vs_2p;
		P_GrpAcv		m_cpu_vs_cpu;

		//���ڃI�u�W�F�N�g
		P_Menu_1v2		m_menu_1v2;
		P_Menu_1vc		m_menu_1vc;
		P_Menu_cv2		m_menu_cv2;
		P_Menu_cvc		m_menu_cvc;

		//�I��
		VP_DemoMenuItem		mv_menu;
		VP_DemoMenuItem::const_iterator		m_itMenu;

	public:
		DemoMenu ();
		DemoMenu ( const DemoMenu & rhs ) = delete;
		~DemoMenu ();

		void Init ();
		void Move ();

		void ParamInit ( P_DemoMain pDemoMain );
	};

	using P_DemoMenu = std::shared_ptr < DemoMenu >;


}	//namespace GAME


