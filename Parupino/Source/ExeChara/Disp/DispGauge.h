//=================================================================================================
//
// DispGauge �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "../../FtgMain/G_Ftg.h"
#include "../BtlParam.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispGauge : public TASK_VEC
	{
		PLAYER_ID	m_playerID;		//�v���C���\����

		float		m_base_x;		//��ʒux
		float		m_base_y;		//��ʒuy
		float		m_base_w;		//��ʒuw
		float		m_base_h;		//��ʒuh

		P_PrmRect	m_Value;		//�\��
		P_PrmRect	m_Frame;		//�g
		P_PrmRect	m_Decrease;		//�������\��
		float		m_d;		//�������l


	public:
		DispGauge ();
		DispGauge ( const DispGauge & rhs ) = delete;
		~DispGauge ();

		//��ʒu�ݒ�
		void SetPosition ( VEC2 xy, VEC2 wh ) { SetPosition ( xy.x, xy.y, wh.x, wh.y ); }
		void SetPosition ( float x, float y, float w, float h );

		//�J���[�̐ݒ�
		void SetColor_Frame ( _CLR c );
		void SetColor_Decrease ( _CLR c );
		void SetColor_Value ( _CLR c0, _CLR c1, _CLR c2, _CLR c3 );

		//�Q�[�W�ނ̕\�����̂ݏ�����
		void LoadPlayer ( PLAYER_ID id );

		//������
		void Init ();

		//�������\��
		void OffDecrease () { m_Decrease->SetValid ( F ); }

		//�l�̍X�V
		void Update ( UINT value );
	};

	using P_DispGauge = std::shared_ptr < DispGauge >;


}	//namespace GAME

