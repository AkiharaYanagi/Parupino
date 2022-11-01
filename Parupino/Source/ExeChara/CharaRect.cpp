//=================================================================================================
//
// �G�O�[�L�����@�\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "CharaRect.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�R���X�g���N�^
	CharaRect::CharaRect ()
	{
		m_pvCRect = make_shared < V_RECT > ();
		m_pvHRect = make_shared < V_RECT > ();
		m_pvARect = make_shared < V_RECT > ();
		m_pvORect = make_shared < V_RECT > ();

		//���萔��������
		m_pvCRect->resize ( NUM_RECT );
		m_pvHRect->resize ( NUM_RECT );
		m_pvARect->resize ( NUM_RECT );
		m_pvORect->resize ( NUM_RECT );
		ResetAllRect ();
#if 0
		for ( UINT i = 0; i < NUM_RECT; ++ i )
		{
			RECT rect = { 0, 0, 0, 0 };
			m_pvCRect->push_back ( rect );
			m_pvARect->push_back ( rect );
			m_pvHRect->push_back ( rect );
			m_pvORect->push_back ( rect );
		}
#endif // 0
	}

	//�f�X�g���N�^
	CharaRect::~CharaRect ()
	{
	}


	//�S�����g�̃��Z�b�g
	void CharaRect::ResetAllRect ()
	{
		ZeroVecRect ( m_pvCRect );
		ZeroVecRect ( m_pvHRect );
		ZeroVecRect ( m_pvARect );
		ZeroVecRect ( m_pvORect );
	}

	//�g�ݒ�
	void CharaRect::SetpvRect ( PV_RECT pvRectActual, PV_RECT pvRectScript, bool dir, VEC2 pos )
	{
		for ( UINT i = 0; i < NUM_RECT; ++ i )
		{
			if ( i < pvRectScript->size () )
			{
				RECT r = pvRectScript->at ( i );
				RECT tempRect;
				if ( true == dir )	//����
				{
					tempRect.left	= (LONG)(pos.x + r.left);
					tempRect.top	= (LONG)(pos.y + r.top);
					tempRect.right	= (LONG)(pos.x + r.right);
					tempRect.bottom	= (LONG)(pos.y + r.bottom);
				}
				else if ( false == dir )
				{
					tempRect.left	= (LONG)(pos.x - r.right);	//right�Ɠ���
					tempRect.top	= (LONG)(pos.y + r.top);
					tempRect.right	= (LONG)(pos.x - r.left);	//left�Ɠ���
					tempRect.bottom	= (LONG)(pos.y + r.bottom);
				}
				CopyRect ( pvRectActual->at ( i ), tempRect );
			}
			else
			{
				ZeroRect ( pvRectActual->at ( i ) );
			}
		}
	}

	void CharaRect::SetCRect ( PV_RECT p, bool dir, VEC2 pos ) { SetpvRect ( m_pvCRect, p, dir, pos ); }
	void CharaRect::SetHRect ( PV_RECT p, bool dir, VEC2 pos ) { SetpvRect ( m_pvHRect, p, dir, pos ); }
	void CharaRect::SetARect ( PV_RECT p, bool dir, VEC2 pos ) { SetpvRect ( m_pvARect, p, dir, pos ); }
	void CharaRect::SetORect ( PV_RECT p, bool dir, VEC2 pos ) { SetpvRect ( m_pvORect, p, dir, pos ); }

	
#if 0
	//�����g����\���g�֐ݒu
	void CharaRect::SetGrpRect ( PrmRect grpRect [], RECT rect [], float dispGameBaseX )
	{
		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			float x = dispGameBaseX + rect[i].left;
			float y = (float)rect[i].top;
			float w = (float)( rect[i].right - rect[i].left );
			float h = (float)( rect[i].bottom - rect[i].top );
			grpRect[i].SetRect ( x, y, w, h );
		}
	}
#endif // 0


}	//namespace GAME

