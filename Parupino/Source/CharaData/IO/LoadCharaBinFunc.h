//=================================================================================================
//
// LoadCharaBinFunc �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once
#include "Game.h"
#include "../Chara.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using P_CH = shared_ptr < char [] >;

	//------------------------------------------------------------
	//	LoadCharaBin�ŗp����֐��Q
	//------------------------------------------------------------
	class LoadCharaBinFunc
	{
	public:
		LoadCharaBinFunc ();
		LoadCharaBinFunc ( const LoadCharaBinFunc & rhs ) = delete;
		~LoadCharaBinFunc () = default;


		void LoadCommand ( P_CH buf, UINT & pos, Chara & ch );
		void LoadBranch ( P_CH buf, UINT & pos, Chara & ch );
		void LoadRoute ( P_CH buf, UINT & pos, Chara & ch );

		tstring LoadText ( char* buf, UINT length );
	};


}	//namespace GAME


