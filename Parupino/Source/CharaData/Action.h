//=================================================================================================
//
//	Action ヘッダファイル
//		スクリプトの一連、固有の値を追加
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
#include "Sequence.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//==================================================================================
	//	◆アクション属性
	//		STAND, MOVE, DASH, ATTACK_L, ATTACK_M, ATTACK_H, CLANG, AVOID, DOTTY, DAMAGED, DEMO, OTHER
	//
	//==================================================================================

	//================================================================
	//	アクション		各フレームのスクリプトリストを持つ
	//		┣[]スクリプト
	//		┣次アクション
	//		┣消費バランス値
	//		┣アクション体勢
	//		┣アクション属性
	//================================================================
	
	class Action : public Sequence
	{
		tstring				m_name;			//名前
		ACTION_CATEGORY		m_category;		//アクション属性
		ACTION_POSTURE		m_posture;		//アクション体勢
		UINT				m_hitNum;		//ヒット数
		UINT				m_hitPitch;		//ヒット間隔
		int					m_balance;		//バランス値

	public:
		Action ();
		Action ( const Action & rhs ) = delete;
		~Action ();

		//名前
		void SetName ( tstring name ) { m_name.assign ( name ); }
		tstring GetName () const { return m_name; }
		bool IsName ( tstring name ) const { return m_name == name; }

		//アクション属性
		ACTION_CATEGORY GetCategory () const { return m_category; }
		void SetCategory ( ACTION_CATEGORY category ) { m_category = category; }

		//アクション体勢
		ACTION_POSTURE GetPosture () const { return m_posture; }
		void SetPosture ( ACTION_POSTURE posture ) { m_posture = posture; }

		//ヒット数
		UINT GetHitNum () const { return m_hitNum; }
		void SetHitNum ( UINT n ) { m_hitNum = n; }

		//ヒット間隔
		UINT GetHitPitch () const { return m_hitPitch; }
		void SetHitPitch ( UINT n ) { m_hitPitch = n; }

		//バランス値
		int GetBalance () { return m_balance; }
		void SetHitNum ( int i ) { m_balance = i; }
};

	using P_Action = shared_ptr < Action >;
	using VP_Action = vector < P_Action >;
	using PVP_Action = shared_ptr < VP_Action >;


}	//namespace GAME


