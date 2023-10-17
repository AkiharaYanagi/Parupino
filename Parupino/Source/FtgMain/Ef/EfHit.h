//=================================================================================================
//
//	EfHit �w�b�_�t�@�C��
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
	//�q�b�g�G�t�F�N�g�N���X
	class EfHit : public GrpEf
	{
	public:
		EfHit ();
		EfHit ( const EfHit & rhs ) = delete;
		~EfHit ();

		void Move ();
		void On ( VEC2 center );
	};

	using P_EfHit = shared_ptr < EfHit >;

}	//namespace GAME

