//=================================================================================================
//	Route �w�b�_�t�@�C��
//=================================================================================================
#pragma once
#include "Game.h"
#include "Branch.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================================
	//	���[�g
	//		�u�����`�̏W��
	//================================================================
	
	class Route
	{
		vector < UINT >		m_vIdBranch;

	public:
		Route ();
		Route ( const Route & rhs ) = delete;
		~Route ();

		void Clear ();

		void AddBranchID ( UINT branchId );

		const V_UINT & GetvIDBranch () const { return m_vIdBranch; }
};

	using P_Route = shared_ptr < Route >;
	using VP_Route = vector < P_Route >;
	using PVP_Route = shared_ptr < VP_Route >;


}	//namespace GAME

