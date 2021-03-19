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
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;
	public:
		PrmEfParticle () : m_angle ( 0 ) {}
	};

	//�ΉԃG�t�F�N�g�N���X
	class EfParticle : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 30,
		};
		vector < PrmEfParticle >		m_vPrm;

	public:
		EfParticle ();
		EfParticle ( const EfParticle & rhs ) = delete;
		~EfParticle ();

		void Move ();
		void On ( VEC2 center );
	};

	using P_EEfParticle = shared_ptr < EfParticle >;

}	//namespace GAME


