//=================================================================================================
//
//	タイトル メニュ アクタ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_MenuActor.h"
#include "Title_Intro.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//==============================================================
	//Actor

	Title_MenuActor::Title_MenuActor ()
	{
		m_start = make_shared < Title_Menu_Start > ();
		AddpTask ( m_start );

		m_vs = make_shared < Title_Menu_VS > ();
		AddpTask ( m_vs );
		m_vs->Off ();
	}

	Title_MenuActor::~Title_MenuActor ()
	{
	}


	void Title_MenuActor::Load ()
	{
		//shared_from_this () を含むのでコンストラクタで用いない
		Menu::SetpMenuItem ( m_start );
		Menu::SetpMenuItem ( m_vs );

		Menu::Load ();
	}

	void Title_MenuActor::SetwpTitle_Intro ( WP_Title_Intro p )
	{
		m_start->SetwpTitle_Intro ( p );
		m_vs->SetwpTitle_Intro ( p );
	}

	void Title_MenuActor::Move ()
	{
		Menu::Do ();

		TASK_VEC::Move ();
	}

	//VSメニュに移行
	void Title_MenuActor::Select_VS ()
	{
		m_start->Off ();
		Menu::Next ();
		m_vs->On ();
	}

	//タイトルの最初に戻る
	void Title_MenuActor::Return_Start ()
	{
		m_start->On ();
		Menu::Top ();
		m_vs->Off ();
	}

	//==============================================================


}	//namespace GAME

