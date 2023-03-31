//=================================================================================================
//
// DispGauge �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DispGauge.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DispGauge::DispGauge ()
		: m_playerID ( PLAYER_ID_1 )
		, m_base_x ( 0 ), m_base_y ( 0 ), m_base_w ( 0 ), m_base_h ( 0 )
		, m_d ( LIFE_MAX )
	{
		//�g
		m_Frame = make_shared < PrmRect > ();
		GRPLST_INSERT ( m_Frame );

		//������
		m_Decrease = make_shared < PrmRect > ();
		GRPLST_INSERT ( m_Decrease );

		//���ݒl
		m_Value = make_shared < PrmRect > ();
		GRPLST_INSERT ( m_Value );
	}

	DispGauge::~DispGauge ()
	{
	}

	void DispGauge::SetPosition ( float x, float y, float w, float h )
	{
		m_base_x = x;
		m_base_y = y;
		m_base_w = w;
		m_base_h = h;
	}

	void DispGauge::SetColor_Frame ( _CLR c )
	{
		m_Frame->SetAllColor ( c );
	}

	void DispGauge::SetColor_Decrease ( _CLR c )
	{
		m_Decrease->SetAllColor ( c );
	}

	void DispGauge::SetColor_Value ( _CLR c0, _CLR c1, _CLR c2, _CLR c3 )
	{
		m_Value->SetColorN ( 0, c0 );
		m_Value->SetColorN ( 1, c1 );
		m_Value->SetColorN ( 2, c2 );
		m_Value->SetColorN ( 3, c3 );
	}

	void DispGauge::LoadPlayer ( PLAYER_ID id )
	{
		m_playerID = id;

		float x = m_base_x;
		float y = m_base_y;
		float w = m_base_w;
		float h = m_base_h;

		//�����ʒu
		if ( PLAYER_ID_1 == m_playerID )
		{
			m_Frame->SetRect ( x - 2, y - 2, w + 4, h + 4 );
			m_Value->SetRect ( x, y, w, h );
			m_Decrease->SetRect ( 0, 0, 0, 0 );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			float p2_bx_l = GAME_WINDOW_WIDTH - x - w;
			m_Frame->SetRect ( p2_bx_l - 2, y - 2, w + 4, h + 4 );
			m_Value->SetRect ( p2_bx_l, y, w, h );
			m_Decrease->SetRect ( 0, 0, 0, 0 );
		}
	}

	void DispGauge::Init ()
	{
		m_d = LIFE_MAX;
		m_Decrease->SetRect ( 0, 0, 0, 0 );
	}

	void DispGauge::Update ( UINT value )
	{
		float x = m_base_x;
		float y = m_base_y;
		float w = m_base_w;
		float h = m_base_h;

		if ( value < m_d )
		{
			m_d -= 10;
		}

		if ( PLAYER_ID_1 == m_playerID )
		{
			m_Value->SetRect ( x, y, w, h );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			float p2_bx_l = GAME_WINDOW_WIDTH - x - w;
			m_Value->SetRect ( p2_bx_l, y, w, h );
		}
	}


}	//namespace GAME

