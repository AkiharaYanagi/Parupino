//=================================================================================================
//
// DispInput �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../CharaData/Chara.h"
#include "../../FtgMain/G_Ftg.h"
#include "../Input/CharaInput.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using VP_PRMRECT = vector < P_PrmRect >;
	using PVP_PRMRECT = shared_ptr < VP_PRMRECT >;
	using VPVP_PRMRECT = vector < PVP_PRMRECT >;

	class DispInput : public TASK_VEC
	{
		//�L�[���͕\����
		static const UINT NUM_DISP_INPUT;

		P_PrmRect		m_bg;

		VPVP_PRMRECT	m_vpvpRect;

		UINT			m_timer;
		float			m_vel;

	public:
		DispInput ();
		DispInput ( const DispInput & rhs ) = delete;
		~DispInput ();

		//���͍X�V
		void UpdateInput ( P_CharaInput pCharaInput );


	private:
		bool GetBoolInput ( P_CharaInput pCharaInput, int n, int i );
	};

}	//namespace GAME


