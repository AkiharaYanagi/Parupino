//=================================================================================================
//
//	MenuItem �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "MenuItem.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MenuItem::MenuItem ()
	{
		m_grp = make_shared < GrpAcv > ();
		m_grp->SetZ ( 0.1f );
	}

	MenuItem::~MenuItem ()
	{
	}


}	//namespace GAME
