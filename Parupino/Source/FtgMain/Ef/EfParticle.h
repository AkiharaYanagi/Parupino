//=================================================================================================
//
//	EfParticle �w�b�_�t�@�C��
//		�ō����ɔ�������̉���\�ȗ��q
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/FtgConst.h"
#include "../G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�p�����[�^
	struct PrmEfParticle
	{
		VEC2	m_startPos;
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;	//[rad]

		bool	m_flag;

	public:
		PrmEfParticle ()
			: m_startPos ( 0, 0 ), m_pos ( 0, 0 )
			, m_startVel ( 0, 0 ), m_vel ( 0, 0 )
			, m_G ( 0, 0 ), m_angle ( 0 ), m_flag ( F )
		{}
	};

	//���q�G�t�F�N�g�N���X
	class EfParticle : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 300,
		};
		std::vector < PrmEfParticle >	m_vPrm;

	public:
		EfParticle ();
		EfParticle ( const EfParticle & rhs ) = delete;
		~EfParticle ();

		//���
		//1��30�@���@�S300���x

		//����(�ǉ�)

		//���Ԃɂ����

		//����ɂ����
		
		void Move ();
		void On ( VEC2 center );

		void Draw ();
	};

	using P_EfParticle = std::shared_ptr < EfParticle >;

}	//namespace GAME


