//=================================================================================================
//
//	Training_Menu_KeyInput
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Training_Menu_KI : public Menu
	{
		P_PrmRect		m_bg;
		P_GrpAcv		m_keyIndex;
		P_GrpAcv		m_selectRect;

	public:
		Training_Menu_KI ();
		Training_Menu_KI ( const Training_Menu_KI & rhs ) = delete;
		~Training_Menu_KI ();

		void Load ();
		void Off ();
		void On ();

		//Active == T のみ実行される
		void Active ();
	};


	using P_Training_Menu_KI = std::shared_ptr < Training_Menu_KI >;


}	//namespace GAME

