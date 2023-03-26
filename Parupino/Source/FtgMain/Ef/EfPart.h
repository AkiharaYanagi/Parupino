//=================================================================================================
//
//	EfPart �w�b�_�t�@�C��
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
	struct PrmEfPart
	{
		VEC2	m_startPos;
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;	//[rad]

		bool	m_flag;

	public:
		PrmEfPart ()
			: m_startPos ( 0, 0 ), m_pos ( 0, 0 )
			, m_startVel ( 0, 0 ), m_vel ( 0, 0 )
			, m_G ( 0, 0 ), m_angle ( 0 ), m_flag ( F )
		{}
	};

	//���q�G�t�F�N�g�N���X
	class EfPart : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 300,
		};
		vector < PrmEfPart >	m_vPrm;

	public:
		EfPart ();
		EfPart ( const EfPart & rhs ) = delete;
		~EfPart ();
		
		void Move ();
		void On ( VEC2 center );
		void Draw ();
	};

	using P_EfPart = shared_ptr < EfPart >;

}	//namespace GAME


