//=================================================================================================
//
//	EfPart �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "EfPart.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfPart::EfPart ()
	{
		AddTexture ( _T ( "Ef_Part.png" ) );
		SetValid ( T );
	}

	EfPart::~EfPart ()
	{
	}

	void EfPart::Move ()
	{
//		SetPos ( VEC2 ( GAME_WINDOW_WIDTH * 0.5f, GAME_WINDOW_HEIGHT * 0.5 ) );
		//SetPos ( 0,0 ) );
		VEC2 pos = GetRevised ();
		DBGOUT_WND_F ( 3, _T ( "y = %d" ), pos.y );

		if ( pos.y >= GROUND_Y )
		{
			SetColor ( 0xff8080ff );
			SetRevised ( VEC2 ( pos.x, pos.y - 500 ) );
		}
		else
		{
			SetRevised ( VEC2 ( pos.x, pos.y + 5 ) );
		}


		//���݃L�����N�^�ʒu�ɂ���ʕ␳�ʒu
		SetDispBase ( G_BASE_POS () );

		GrpEf::Move ();
	}

	void EfPart::On ( VEC2 center )
	{
		SetRevised ( center + VEC2 ( 0, -400 ) );
		GrpEf::On ();
	}

	void EfPart::Draw ()
	{
		GrpEf::Draw ();
	}


}
