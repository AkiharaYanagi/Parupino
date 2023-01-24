//=================================================================================================
//
//	MutualChara Demo �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "G_Ftg.h"
#include "FtgConst.h"	
#include "../GameMain/Param.h"
#include "../ExeChara/ExeChara_Demo.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class MutualChara_Demo : public TASK_VEC
	{
		//�L����
		P_ExeChara_Demo		m_exeChara1;
		P_ExeChara_Demo		m_exeChara2;

	public:
		MutualChara_Demo ();
		MutualChara_Demo ( const MutualChara_Demo & rhs ) = delete;
		~MutualChara_Demo ();

		//�p�����[�^�w��
		void ParamInit ( P_Param pParam );

		//�퓬�J�n�̏�����
		void Start ();

		//�X�N���v�g�̖��t���[������
		void Conduct ();
	};

	using P_MutualChara_Demo = shared_ptr < MutualChara_Demo >;


}	//namespace GAME


