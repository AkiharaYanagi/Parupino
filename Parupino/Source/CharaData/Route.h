//=================================================================================================
//	Route ヘッダファイル
//=================================================================================================
#pragma once
#include "Game.h"
#include "Branch.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================================
	//	ルート
	//		ブランチの集合
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


