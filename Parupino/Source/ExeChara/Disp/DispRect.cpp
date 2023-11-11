//=================================================================================================
//
// DispRect �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DispRect.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DispRect::DispRect () 
	{
		//�g�\����������
		m_pvpGrpCRect = make_shared < VP_PrmRect > ();
		m_pvpGrpARect = make_shared < VP_PrmRect > ();
		m_pvpGrpHRect = make_shared < VP_PrmRect > ();
		m_pvpGrpORect = make_shared < VP_PrmRect > ();

		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
#if 0
			P_PrmRect pCRect = make_shared < PrmRect > ();
			pCRect->SetAllColor ( RECT_COLOR_C );
			pCRect->SetZ ( Z_SYS );
			pCRect->Load ();
			m_pvpGrpCRect->push_back ( pCRect );
			AddpTask ( pCRect );
			GRPLST_INSERT_MAIN ( pCRect );

			P_PrmRect pARect = make_shared < PrmRect > ();
			pARect->SetAllColor ( RECT_COLOR_A );
			pARect->SetZ ( Z_SYS );
			pARect->Load ();
			pARect->Move ();
			m_pvpGrpARect->push_back ( pARect );
			AddpTask ( pARect );
			GRPLST_INSERT_MAIN ( pARect );

			P_PrmRect pHRect = make_shared < PrmRect > ();
			pHRect->SetAllColor ( RECT_COLOR_H );
			pHRect->SetZ ( Z_SYS );
			pHRect->Load ();
			pHRect->Move ();
			m_pvpGrpHRect->push_back ( pHRect );
			AddpTask ( pHRect );
			GRPLST_INSERT_MAIN ( pHRect );

			P_PrmRect pORect = make_shared < PrmRect > ();
			pORect->SetAllColor ( RECT_COLOR_O );
			pORect->SetZ ( Z_SYS );
			pORect->Load ();
			pORect->Move ();
			m_pvpGrpORect->push_back ( pORect );
			AddpTask ( pORect );
			GRPLST_INSERT_MAIN ( pORect );
#endif // 0
			m_pvpGrpCRect->push_back ( Make ( RECT_COLOR_C ) );
			m_pvpGrpARect->push_back ( Make ( RECT_COLOR_A ) );
			m_pvpGrpHRect->push_back ( Make ( RECT_COLOR_H ) );
			m_pvpGrpORect->push_back ( Make ( RECT_COLOR_O ) );

		}
		InitRect ();

		//----------------------------------------------------
		//@info		GRPLST�ɓ��I�ɒǉ�����Ƃ��͊��ɑS�̂�Load()����Ă���̂ŁA
		//			�����I��Load()���K�v
		//----------------------------------------------------

		OnRect ();
	}

	P_PrmRect DispRect::Make ( DWORD clr )
	{
		P_PrmRect p = make_shared < PrmRect > ();
		p->SetAllColor ( clr );
		p->SetSize ( VEC2 ( 0, 0 ) );
		p->SetZ ( Z_SYS );
		p->Load ();
		p->Move ();
		AddpTask ( p );
		GRPLST_INSERT_MAIN ( p );
		return p;
	}

	DispRect::~DispRect ()
	{
		//�I�����ɃO���t�B�b�N�^�X�N���O��
		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			GRPLST_REMOVE_MAIN ( (*m_pvpGrpCRect)[i] );
			GRPLST_REMOVE_MAIN ( (*m_pvpGrpARect)[i] );
			GRPLST_REMOVE_MAIN ( (*m_pvpGrpHRect)[i] );
			GRPLST_REMOVE_MAIN ( (*m_pvpGrpORect)[i] );
		}
		//���
		for ( UINT i = 0; i < NUM_RECT; ++i )
		{
			m_pvpGrpCRect->clear ();
			m_pvpGrpARect->clear ();
			m_pvpGrpHRect->clear ();
			m_pvpGrpORect->clear ();
		}
	}

	//�����g�ݒ�
	void DispRect::SetCharaRect ( P_CharaRect pCharaRect )
	{
		mp_CharaRect = pCharaRect;
	}

	//�X�V
	void DispRect::Update ()
	{
		SetCRect ( mp_CharaRect->GetpvCRect () );
		SetARect ( mp_CharaRect->GetpvARect () );
		SetHRect ( mp_CharaRect->GetpvHRect () );
		SetORect ( mp_CharaRect->GetpvORect () );
	}

	//�\���g�̏�����
	void DispRect::InitRect ()
	{
		for ( P_PrmRect p : * m_pvpGrpCRect ) { p->SetZero (); }
		for ( P_PrmRect p : * m_pvpGrpARect ) { p->SetZero (); }
		for ( P_PrmRect p : * m_pvpGrpHRect ) { p->SetZero (); }
		for ( P_PrmRect p : * m_pvpGrpORect ) { p->SetZero (); }
	}

	//�\��
	void DispRect::OnRect ()
	{
		for ( P_PrmRect p : * m_pvpGrpCRect ) { p->SetValid ( true ); }
		for ( P_PrmRect p : * m_pvpGrpARect ) { p->SetValid ( true ); }
		for ( P_PrmRect p : * m_pvpGrpHRect ) { p->SetValid ( true ); }
		for ( P_PrmRect p : * m_pvpGrpORect ) { p->SetValid ( true ); }
	}

	//��\��
	void DispRect::OffRect ()
	{
		for ( P_PrmRect p : * m_pvpGrpCRect ) { p->SetValid ( false ); }
		for ( P_PrmRect p : * m_pvpGrpARect ) { p->SetValid ( false ); }
		for ( P_PrmRect p : * m_pvpGrpHRect ) { p->SetValid ( false ); }
		for ( P_PrmRect p : * m_pvpGrpORect ) { p->SetValid ( false ); }
	}

	//�����g����\���g�֐ݒu
	void DispRect::SetGrpRect ( PVP_PrmRect pvpGrpRect, PV_RECT pvRect )
	{
		float bx = G_BASE_POS().x;	//��ʒu

		UINT i = 0;
		for ( P_PrmRect p : * pvpGrpRect )
		{
			RECT r = pvRect->at ( i );
			float x = bx + r.left;
			float y = (float)r.top;
			float w = (float)( r.right - r.left );
			float h = (float)( r.bottom - r.top );
			p->SetRect ( x, y, w, h );
			++ i;
		}
	}

}	//namespace GAME

