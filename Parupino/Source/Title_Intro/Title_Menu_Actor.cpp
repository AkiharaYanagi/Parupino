//=================================================================================================
//
//	タイトル メニュ アクタ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title_Menu_Actor.h"
#include "Title.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//==============================================================
	//Actor

	Title_Menu_Actor::Title_Menu_Actor ()
	{
		m_start = make_shared < Title_Menu_Start > ();
		AddpTask ( m_start );

		m_vs = make_shared < Title_Menu_VS > ();
		AddpTask ( m_vs );
		m_vs->Off ();
	}

	Title_Menu_Actor::~Title_Menu_Actor ()
	{
	}


	void Title_Menu_Actor::Load ()
	{
		//アクタが管理するメニュを追加
		//shared_from_this () を含むのでコンストラクタで用いない
		Menu::SetpMenuItem ( m_vs );
		Menu::SetpMenuItem ( m_start );

		Menu::Load ();
	}

	void Title_Menu_Actor::SetwpTitle ( WP_Title wp )
	{
		m_vs->SetwpTitle ( wp );
		m_vs->SetwpParentScene ( wp );

		m_start->SetwpTitle ( wp );
		m_start->SetwpParentScene ( wp );
	}


	void Title_Menu_Actor::Move ()
	{
		Menu::Do ();

		TASK_VEC::Move ();
	}

	//VSメニュに移行
	void Title_Menu_Actor::Select_VS ()
	{
		m_start->Off ();
		Menu::Next ();
		m_vs->On ();
	}

	//タイトルの最初に戻る
	void Title_Menu_Actor::Return_Start ()
	{
		m_start->On ();
		Menu::Top ();
		m_vs->Off ();
	}

	//==============================================================


}	//namespace GAME

