//=================================================================================================
//
// LoadCharaUtl �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once
#include "Define.h"
#include "Document.h"

#include "IOCharaDefine.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//	LoadChara�ŗp����Utility�֐��Q
	//------------------------------------------------------------
	class LoadCharaUtl
	{
	public:
		LoadCharaUtl () = default;
		LoadCharaUtl ( const LoadCharaUtl & rhs ) = delete;
		~LoadCharaUtl () = default;


		//------------------------------------------------------------
		//�G�������g�|�C���^����index�Ԗڂ̃A�g���r���[�g��Value��UINT�ɒ����ĕԂ�
		UINT _ElemToUINT ( const P_Element pElem, UINT indexAttr );

		//���O�̕ۑ�
		void ElemToNameArray ( const P_Element pElem, V_STR & vec );

		//���O����C���f�b�N�X���擾
		UINT IndexOf ( const V_STR& vstr, tstring name ) const;

		//------------------------------------------------------------
		//�A�g���r���[�g�ϊ� (�������Attribute��GetValue()��p����)
		bool _AttrToBool ( const P_Attribute pAttr );
		UINT _AttrToUINT ( const P_Attribute pAttr );
		int  _AttrToInt ( const P_Attribute pAttr );
		float  _AttrToFloat ( const P_Attribute pAttr );
		VEC2 _AttrToVec2 ( const P_Attribute pa0, const P_Attribute pa1 );
		RECT _AttrToRect
		( 
			const P_Attribute pa0, const P_Attribute pa1,  
			const P_Attribute pa2, const P_Attribute pa3  
		);

		CLC_ST _AttrToCLC_ST ( const P_Attribute pAttr );
		ACTION_POSTURE _AttrToACTION_POSTURE ( const P_Attribute pAttr );

	};


}	//namespace GAME


