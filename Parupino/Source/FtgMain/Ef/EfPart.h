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
	class EfPart : public GrpAcv
	{
		enum NUM
		{
			SPARK_NUM = 30,
			SPARK_MAX = 300,
		};
		vector < PrmEfPart >	m_vPrm;	//�p�����[�^
		vector < UINT >			mv_Rnd;	//��ғ��I�u�W�F�N�g����

	public:
		EfPart ();
		EfPart ( const EfPart & rhs ) = delete;
		~EfPart ();
		
		void Move ();
		void On ( VEC2 center );
		void Draw ();

	private:
		//�����̃x�N�^��0����N-1�܂ł̗������i�[����
		void Rnd_0_N ( UINT N, vector < UINT > & vec );
	};

	using P_EfPart = shared_ptr < EfPart >;

}	//namespace GAME

