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
//#include "DemoMain.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//循環参照のため前方宣言
	class DemoMain;
	using P_DemoMain = shared_ptr < DemoMain >;


	class MenuItem : public TASK_VEC
	{
	protected:
		P_DemoMain		m_demoMain;
		P_GrpAcv		m_grp;

	public:
		MenuItem ();
		MenuItem ( const MenuItem & rhs ) = delete;
		~MenuItem ();

		virtual void Do () {}

		void SetPos ( VEC2 v ) { m_grp->SetPos ( v ); }

		void SetpDemoMain ( P_DemoMain p ) { m_demoMain = p; }
	};

	using P_MenuItem = shared_ptr < MenuItem >;
	using VP_MenuItem = vector < P_MenuItem >;


	//-------------------------------------------
	class Menu_1v2 : public MenuItem { public: Menu_1v2 ();	void Do (); };
	class Menu_1vc : public MenuItem { public: Menu_1vc ();	void Do (); };
	class Menu_cv2 : public MenuItem { public: Menu_cv2 ();	void Do (); };
	class Menu_cvc : public MenuItem { public: Menu_cvc ();	void Do (); };

	using P_Menu_1v2 = shared_ptr < Menu_1v2 >;
	using P_Menu_1vc = shared_ptr < Menu_1vc >;
	using P_Menu_cv2 = shared_ptr < Menu_cv2 >;
	using P_Menu_cvc = shared_ptr < Menu_cvc >;


}	//namespace GAME


