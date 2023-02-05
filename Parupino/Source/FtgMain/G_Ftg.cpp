//=================================================================================================
//
//	G_Ftg �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	UP_G_Ftg	G_Ftg::m_inst;

	G_Ftg::G_Ftg ()
	:	  m_posMutualBase ( VEC2 ( 0, 0 ) )
	{
	}

	G_Ftg::~G_Ftg ()
	{
	}

	//�L�����ʒu�ɂ���ʕ\���̊�ʒu
	void G_Ftg:: CulcPosMutualBase ( VEC2 pos1p, VEC2 pos2p ) const
	{
		//�ߒl
		float posMutualBase = 0;

		//�ʒu
		float averagex = (pos1p.x + pos2p.x) * 0.5f;	//���S
		float window_center = GAME_WINDOW_WIDTH * 0.5f;
		float gw = GAME_WIDTH;

		//��ʒ[�\������

		//����
		if ( averagex < window_center )
		{
			posMutualBase = 0;
		}
		//�E��
		else if ( averagex > GAME_WIDTH - window_center )
		{
			posMutualBase = (float)GAME_WINDOW_WIDTH - GAME_WIDTH;
		}
		//����
		else
		{
			posMutualBase = window_center - averagex;
		}

		G_Ftg::inst()->SetPosMutualBase ( VEC2 ( posMutualBase, 0 ) );
	}




}	//namespace GAME

