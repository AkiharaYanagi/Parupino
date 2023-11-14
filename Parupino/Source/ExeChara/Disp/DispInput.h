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
#include "Chara.h"
#include "../../FtgMain/G_Ftg.h"
#include "../Input/CharaInput.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispInput : public TASK_VEC
	{
		//�L�[���͕\����
		static const UINT NUM_DISP_INPUT;	//�\���t���[����
		static const UINT BASE_Y;			//��ʒu
		static const UINT CHIP_W;			//1�̕�
		static const UINT CHIP_H;			//1�̍�

		P_PrmRect		m_bg;		//�w�i
		P_GrpAcv		m_index;	//���o

		P_GrpAcv		m_grp;		//���͕\��
		VP_Object		m_vpOb;

		UINT			m_timer;
		float			m_vel;
		float			m_base_x;

	public:
		DispInput ();
		DispInput ( const DispInput & rhs ) = delete;
		~DispInput ();

		void LoadPlayer ( PLAYER_ID playerID );

		//���͍X�V
		void UpdateInput ( P_CharaInput pCharaInput );


	private:
		bool GetBoolInput ( P_CharaInput pCharaInput, int n, int i );
	};

	using P_DispInput = std::shared_ptr < DispInput >;


}	//namespace GAME


