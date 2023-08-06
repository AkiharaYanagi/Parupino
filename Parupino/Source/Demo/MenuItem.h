//=================================================================================================
//
//	MenuItem ヘッダファイル
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
	class MenuItem : public TASK_VEC
	{
	protected:
		P_GrpAcv		m_grp;

	public:
		MenuItem ();
		MenuItem ( const MenuItem & rhs ) = delete;
		~MenuItem ();

		virtual void Do () {}

		void SetPos ( VEC2 v ) { m_grp->SetPos ( v ); }
	};

	using P_MenuItem = shared_ptr < MenuItem >;
	using VP_MenuItem = vector < P_MenuItem >;


	//-------------------------------------------
	class Menu_1v2 : public MenuItem { public: Menu_1v2 ();	};
	class Menu_1vc : public MenuItem { public: Menu_1vc (); };
	class Menu_cv2 : public MenuItem { public: Menu_cv2 (); };
	class Menu_cvc : public MenuItem { public: Menu_cvc (); };

	using P_Menu_1v2 = shared_ptr < Menu_1v2 >;
	using P_Menu_1vc = shared_ptr < Menu_1vc >;
	using P_Menu_cv2 = shared_ptr < Menu_cv2 >;
	using P_Menu_cvc = shared_ptr < Menu_cvc >;


}	//namespace GAME


