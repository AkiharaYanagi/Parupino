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
	using L_UINT = unique_ptr < UINT [] >;

	//------------------------------------------------------------
	//	LoadCharaBin�ŗp����֐��Q
	//------------------------------------------------------------
	class LoadCharaBinFunc
	{
	public:
		LoadCharaBinFunc ();
		LoadCharaBinFunc ( const LoadCharaBinFunc & rhs ) = delete;
		~LoadCharaBinFunc () = default;

		void LoadChara ( P_CH buf, UINT & pos, Chara & ch );

		void LoadBehavior ( P_CH buf, UINT & pos, Chara & ch );
		void LoadGarnish ( P_CH buf, UINT & pos, Chara & ch );

		void LoadCommand ( P_CH buf, UINT & pos, Chara & ch );
		void LoadBranch ( P_CH buf, UINT & pos, Chara & ch );
		void LoadRoute ( P_CH buf, UINT & pos, Chara & ch );

		void LoadScript ( P_CH buf, UINT & pos, Script & scp );
		void LoadScpPrm_Btl ( P_CH buf, UINT & pos, Script & scp );
		void LoadScpPrm_Stg ( P_CH buf, UINT & pos, Script & scp );

		//----
		tstring LoadText ( P_CH buf, UINT & pos );
		int LoadInt ( P_CH buf, UINT & pos );
		RECT LoadRect ( P_CH buf, UINT & pos );
		void LoadListRect ( P_CH buf, UINT & pos, PV_RECT pvRect );
		L_UINT LoadAryUint ( P_CH buf, UINT & pos, UINT & refLength );
	};


}	//namespace GAME


