//=================================================================================================
//
//	MutualChara_Demo �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "MutualChara_Demo.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MutualChara_Demo::MutualChara_Demo ()
	{
		//�L����
		m_exeChara1 = make_shared < ExeChara_Demo > ( PLAYER_ID_1 );
		m_exeChara2 = make_shared < ExeChara_Demo > ( PLAYER_ID_2 );

		AddpTask ( m_exeChara1 );
		AddpTask ( m_exeChara2 );
	}

	MutualChara_Demo::~MutualChara_Demo ()
	{
	}

	void MutualChara_Demo::ParamInit ( P_Param pParam )
	{
		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
	}


	void MutualChara_Demo::Start ()
	{
		m_exeChara1->Init ();
		m_exeChara2->Init ();
	}


	//��#########################################################
	//��
	//��	�X�N���v�g�̖��t���[������
	//��
	//��#########################################################
	void MutualChara_Demo::Conduct ()
	{
		//���X�N���v�g�O����(���́A�ړ��Ȃ�)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//���X�N���v�g�㏈��(�O���t�B�b�N�ʒu�Ȃ�)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//---------------------------------------------------
		//��ʕ\���̊�ʒu������
		VEC2 pos1p = m_exeChara1->GetPos ();
		VEC2 pos2p = m_exeChara2->GetPos ();
		G_Ftg::inst ()->CulcPosMutualBase ( pos1p, pos2p );
	}
	//��#########################################################


}	//namespace GAME

