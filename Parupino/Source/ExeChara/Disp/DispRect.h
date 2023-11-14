//=================================================================================================
//
// DispRect �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../FtgMain/G_Ftg.h"
#include "../../GameMain/GameConst.h"
#include "../Rect/CharaRect.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using VP_PrmRect = std::vector < P_PrmRect >;
	using PVP_PrmRect = std::shared_ptr < VP_PrmRect >;

	class DispRect : public TASK_VEC
	{
		//�Q�Ǝ����g
		P_CharaRect		mp_CharaRect;

		//�\���g
		PVP_PrmRect		m_pvpGrpCRect;
		PVP_PrmRect		m_pvpGrpARect;
		PVP_PrmRect		m_pvpGrpHRect;
		PVP_PrmRect		m_pvpGrpORect;

	public:
		DispRect ();
		DispRect ( const DispRect & rhs ) = delete;
		~DispRect ();

		//�����g�ݒ�
		void SetCharaRect ( P_CharaRect pCharaRect );
	
		//�\���g�̏�����
		void InitRect ();

		//�X�V
		void Update ();

		//------------------
		//�\����ԂɕύX
		void OnRect ();

		//��\����ԂɕύX
		void OffRect ();

		//-------------------

		//�\���g�ݒ�
		void SetGrpRect ( PVP_PrmRect pvpGrpRect, PV_RECT pvRect );
		void SetCRect ( PV_RECT pvRect ) { SetGrpRect ( m_pvpGrpCRect, pvRect ); }
		void SetARect ( PV_RECT pvRect ) { SetGrpRect ( m_pvpGrpARect, pvRect ); }
		void SetHRect ( PV_RECT pvRect ) { SetGrpRect ( m_pvpGrpHRect, pvRect ); }
		void SetORect ( PV_RECT pvRect ) { SetGrpRect ( m_pvpGrpORect, pvRect ); }

	private:
		//�������p
		P_PrmRect Make ( DWORD clr );
	};

	using P_DispRect = std::shared_ptr < DispRect >;


}	//namespace GAME


