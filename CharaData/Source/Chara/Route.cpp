//=================================================================================================
//	Route �\�[�X�t�@�C��
//=================================================================================================
#include "Route.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Route::Route ()
	{
	}

	Route::~Route ()
	{
	}

	void Route::Clear ()
	{
		m_vIdBranch.clear ();
	}

	void Route::AddBranchID ( UINT branchId )
	{
		m_vIdBranch.push_back ( branchId );
	}

}	//namespace GAME
