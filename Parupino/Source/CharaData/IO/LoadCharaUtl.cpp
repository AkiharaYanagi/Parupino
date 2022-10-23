//=================================================================================================
//
// LoadCharaUtl �\�[�X�t�@�C��
//
//=================================================================================================
#include "LoadCharaUtl.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------
	//	�����g�p�֐�
	//-------------------------------------------------------------------
	//�G�������g�|�C���^����index�Ԗڂ̃A�g���r���[�g��Value��UINT�ɒ����ĕԂ�
	UINT LoadCharaUtl::_ElemToUINT ( const P_Element pElem, UINT indexAttr )
	{
		UINT ui = 0;
		try
		{
			const PVP_Attribute pvpAttr = pElem->GetpvpAttribute();
			tistringstream tiss ( (*pvpAttr)[ indexAttr ]->GetValue() );
			tiss >> ui;
		}
		catch (...) { TRACE_F ( _T("Error _ElemToUINT.\n") ); }
		return ui;
	}
	
	//------------------------------------------------------------
	//���O�̕ۑ�
	void LoadCharaUtl::ElemToNameArray ( const P_Element pElem, V_STR & vec )
	{
		PVP_Element pvp_elem = pElem->GetpvpElement ();

#if 0
		for ( P_Element pe : * pvp_elem )
		{
			PVP_Attribute pvp_attr = pe->GetpvpAttribute ();
			vec.push_back ( (*pvp_attr)[0]->GetValue () );		//���O�̃A�g���r���[�g�͂O�̈ʒu
		}
#endif // 0

		//�v�f���𐔂��グ��Ƀ��T�C�Y�Ŋm�ۂ���
		vec.resize ( pvp_elem->size () );

		//�l�̑��
		UINT i = 0;
		for ( P_Element pe : * pvp_elem )
		{
			PVP_Attribute pvp_attr = pe->GetpvpAttribute ();
			vec[i] = ( *pvp_attr ) [ 0 ]->GetValue ();		//���O�̃A�g���r���[�g�͂O�̈ʒu
			++ i;
		}
	}

	UINT LoadCharaUtl::IndexOf ( const V_STR& vstr, tstring name ) const
	{
		UINT ret = 0;
		for ( tstring tstr : vstr )
		{
			if ( 0 == tstr.compare ( name ) ) { break; }
			++ ret;
		}
		return ret;
	}

	//------------------------------------------------------------
	//�A�g���r���[�g�|�C���^����Value��bool�ɒ����ĕԂ�
	bool LoadCharaUtl::_AttrToBool ( const P_Attribute pAttr )
	{
		bool b = false;
		try
		{
			b = pAttr->GetValue().compare ( _T("True") ) == 0;
		}
		catch (...) { TRACE_F ( _T("Error _AttrToBool.\n") ); }
		return b;
	}

	//�A�g���r���[�g�|�C���^����Value��UINT�ɒ����ĕԂ�
	UINT LoadCharaUtl::_AttrToUINT ( const P_Attribute pAttr )
	{
		UINT ui = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> ui;
		}
		catch (...){ TRACE_F ( _T("Error _AttrToUINT.\n") ); }
		return ui;
	}

	//�A�g���r���[�g�|�C���^����Value��int�ɒ����ĕԂ�
	int LoadCharaUtl::_AttrToInt ( const P_Attribute pAttr )
	{
		int i = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> i;
		}
		catch (...)	{	TRACE_F ( _T("Error _AttrToInt.\n") );	}
		return i;
	}

	//�A�g���r���[�g�|�C���^����Value��float�ɒ����ĕԂ�
	float LoadCharaUtl::_AttrToFloat ( const P_Attribute pAttr )
	{
		float f = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> f;
		}
		catch (...)	{	TRACE_F ( _T("Error _AttrToFloat.\n") );	}
		return f;
	}

	//�A�g���r���[�g�|�C���^�Q����Value��VEC2�ɒ����ĕԂ�
	VEC2 LoadCharaUtl::_AttrToVec2 ( const P_Attribute pa0, const P_Attribute pa1 )
	{
		return VEC2 ( _AttrToFloat ( pa0 ), _AttrToFloat ( pa1 ) );
	}

	//�A�g���r���[�g�|�C���^�S����Value��RECT�ɒ����ĕԂ�
	//�����Fx, y, w, h
	RECT LoadCharaUtl::_AttrToRect ( const P_Attribute pa0, const P_Attribute pa1, const P_Attribute pa2, const P_Attribute pa3 )
	{
		//x0, y0, x1, y1�ɒ���
		int x = _AttrToInt ( pa0 );
		int y = _AttrToInt ( pa1 );
		int w = _AttrToInt ( pa2 );
		int h = _AttrToInt ( pa3 );

		RECT rect = { x, y, x + w, y + h };
		return rect;
	}

	//�A�g���r���[�g�|�C���^����Value��CLC_ST�ɒ����ĕԂ�
	CLC_ST LoadCharaUtl::_AttrToCLC_ST ( const P_Attribute pAttr )
	{
		CLC_ST clcSt = (CLC_ST)_AttrToInt ( pAttr );
#if 0
		tstring str = pAttr->GetValue ();
		if ( 0 == str.compare ( _T ( "CLC_MAINTAIN" ) ) ) { clcSt = CLC_MAINTAIN; }
		else if ( 0 == str.compare ( _T ( "CLC_SUBSTITUDE" ) ) ) { clcSt = CLC_SUBSTITUDE; }
		else if ( 0 == str.compare ( _T ( "CLC_ADD" ) ) ) { clcSt = CLC_ADD; }
#endif // 0
		return clcSt;
	}

	//�A�g���r���[�g�|�C���^����Value��ACTION_POSTURE�ɒ����ĕԂ�
	ACTION_POSTURE LoadCharaUtl::_AttrToACTION_POSTURE ( const P_Attribute pAttr )
	{
		ACTION_POSTURE ap = (ACTION_POSTURE)_AttrToInt ( pAttr );
#if 0
		tstring str = pAttr->GetValue ();
		if ( 0 == str.compare ( _T ( "AP_STAND" ) ) ) { ap = AP_STAND; }
		else if ( 0 == str.compare ( _T ( "AP_CROUCH" ) ) ) { ap = AP_CROUCH; }
		else if ( 0 == str.compare ( _T ( "AP_JUMP" ) ) ) { ap = AP_JUMP; }
#endif // 0
		return ap;
	}





}	//namespace GAME

