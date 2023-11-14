//=================================================================================================
//
// LoadCharaBinUtl �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once
//#include "Game.h"
#include "Chara.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using P_CH = std::shared_ptr < char [] >;
	using L_UINT = unique_ptr < UINT [] >;

	//------------------------------------------------------------
	//	LoadCharaBin�ŗp����֐��Q
	//------------------------------------------------------------
	class LoadCharaBinUtl
	{
	public:
		LoadCharaBinUtl ();
		LoadCharaBinUtl ( const LoadCharaBinUtl & rhs ) = delete;
		~LoadCharaBinUtl () = default;

		//----
		tstring LoadText ( P_CH buf, UINT & pos );
		byte LoadByte ( P_CH buf, UINT & pos );
		int LoadInt ( P_CH buf, UINT & pos );
		UINT LoadUInt ( P_CH buf, UINT & pos );
		VEC2 LoadVec2 ( P_CH buf, UINT & pos );
		RECT LoadRect ( P_CH buf, UINT & pos );
		void LoadListRect ( P_CH buf, UINT & pos, PV_RECT pvRect );
		L_UINT LoadAryUint ( P_CH buf, UINT & pos, UINT & refLength );
		void LoadAryUint ( P_CH buf, UINT & pos, V_UINT & refAryUint );
	};


}	//namespace GAME


