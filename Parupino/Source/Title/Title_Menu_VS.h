//=================================================================================================
//
//	タイトル メニュ ファイティング
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Title_Menu_State.h"
#include "Title_Cursor.h"
#include "Title_Explain.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==============================================================
	class Title;  using WP_Title_Intro = std::weak_ptr < Title >;
	class Scene;	using WP_Scnen = std::weak_ptr < Scene >;

	//==============================================================
	//State

	//VS State共通
	class TMS_VS_Common : public Title_Menu_State
	{
	protected:
		P_Title_Explain		m_expl;

		P_GrpStr	m_str;
		
		P_PrmRect	m_fade;
		UINT		m_wait;


	public:
		TMS_VS_Common ();

		void Load ();
		void Do ();
		virtual void Decide () {}

		void Off ();
		void On ();
	};
	using P_TMS_VS_Common = std::shared_ptr < TMS_VS_Common >;


	//--------------------------------------------------------------
	class TMS_TRAINING : public TMS_VS_Common
	{
	public:
		TMS_TRAINING ();
		TMS_TRAINING ( const TMS_TRAINING & rhs ) = delete;
		~TMS_TRAINING () = default;

		void Decide ();
	};
	using P_TMS_TRAINING = std::shared_ptr < TMS_TRAINING >;

	//--------------------------------------------------------------
	class TMS_1P_VS_2P : public TMS_VS_Common
	{
	public:
		TMS_1P_VS_2P ();
		TMS_1P_VS_2P ( const TMS_1P_VS_2P & rhs ) = delete;
		~TMS_1P_VS_2P () = default;

		void Decide ();
	};
	using P_TMS_1P_VS_2P = std::shared_ptr < TMS_1P_VS_2P >;

	//--------------------------------------------------------------
	class TMS_1P_VS_CPU : public TMS_VS_Common
	{
	public:
		TMS_1P_VS_CPU ();
		TMS_1P_VS_CPU ( const TMS_1P_VS_CPU & rhs ) = delete;
		~TMS_1P_VS_CPU () = default;

		void Decide ();
	};
	using P_TMS_1P_VS_CPU = std::shared_ptr < TMS_1P_VS_CPU >;

	//--------------------------------------------------------------
	class TMS_CPU_VS_CPU : public TMS_VS_Common
	{
	public:
		TMS_CPU_VS_CPU ();
		TMS_CPU_VS_CPU ( const TMS_CPU_VS_CPU & rhs ) = delete;
		~TMS_CPU_VS_CPU () = default;

		void Decide ();
	};
	using P_TMS_CPU_VS_CPU = std::shared_ptr < TMS_CPU_VS_CPU >;


	//==============================================================
	//メニュ　対戦選択
	class Title_Menu_VS : public Title_Menu_State
	{
		P_TMS_TRAINING			m_state_Training;
		P_TMS_1P_VS_2P			m_state_1P_VS_2P;
		P_TMS_1P_VS_CPU			m_state_1P_VS_CP;
		P_TMS_CPU_VS_CPU		m_state_CP_VS_CP;

		P_GrpAcv			m_grp;
		P_Title_Cursor		m_cursor;

		static const float		BASE_X;
		static const float		BASE_Y;
		static const float		PITCH_Y;
	public:
		Title_Menu_VS ();
		Title_Menu_VS ( const Title_Menu_VS & rhs ) = delete;
		~Title_Menu_VS ();

		void Load ();
		void Do ();
		void SetwpTitle ( WP_Title wp );
		void SetwpScene ( WP_Scene wp );
		void Off ();
		void On ();

	private:
		void SelectMenuItem ();
	};
	using P_Title_Menu_VS = std::shared_ptr < Title_Menu_VS >;


	//==============================================================

}	//namespace GAME

