//=================================================================================================
//
//	EfSpark �w�b�_�t�@�C��
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
	struct PrmEfSpark
	{
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;
	public:
		PrmEfSpark () : m_angle ( 0 ) {}
	};

	//�ΉԃG�t�F�N�g�N���X
	class EfSpark : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 30,
		};
		std::vector < PrmEfSpark >		m_vPrm;

	public:
		EfSpark ();
		EfSpark ( const EfSpark & rhs ) = delete;
		~EfSpark ();

		void Move ();
		void On ( VEC2 center );
	};

	using P_EfSpark = std::shared_ptr < EfSpark >;

}	//namespace GAME


