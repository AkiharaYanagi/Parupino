//=================================================================================================
//
//	Fighting �f��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "FtgConst.h"	
#include "MutualChara.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//param



	//------------------------------------------------


	//=====================================================
	//State
	class FtgDemo
	{
	public:
		FtgDemo ();
		FtgDemo ( const FtgDemo & rhs ) = delete;
		~FtgDemo ();
	};
	using P_FtgDemo = shared_ptr < FtgDemo >;
	//=====================================================


	//------------------------------------------------

	class FTG_DM_GetReady : public FtgDemo
	{

	};
	using P_FTG_DM_GetReady = shared_ptr < FTG_DM_GetReady >;


	//------------------------------------------------
	class FTG_DM_Attack : public FtgDemo
	{

	};
	using P_FTG_DM_Attack = shared_ptr < FTG_DM_Attack >;


	//------------------------------------------------
	class FTG_DM_Main : public FtgDemo
	{

	};
	using P_FTG_DM_Main = shared_ptr < FTG_DM_Main >;


	//------------------------------------------------
	class FTG_DM_Down : public FtgDemo
	{

	};
	using P_FTG_DM_Down = shared_ptr < FTG_DM_Down >;


	//------------------------------------------------
	class FTG_DM_Winner : public FtgDemo
	{

	};
	using P_FTG_DM_Winner = shared_ptr < FTG_DM_Winner >;



}	//namespace GAME


