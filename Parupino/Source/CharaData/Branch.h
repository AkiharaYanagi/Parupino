//=================================================================================================
//
//	Branch ヘッダファイル
//		スクリプト遷移条件の入力コマンドと遷移先シークエンス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara_Const.h"
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class Sequence;
	using P_Sqc = shared_ptr < Sequence >;
	using WP_Sqc = weak_ptr < Sequence >;		//循環参照

	using VP_Sqc = vector < P_Sqc >;
	using PVP_Sqc = shared_ptr < VP_Sqc >;
	using WP_Command = weak_ptr < Command >;		//循環参照

	class Branch
	{
		tstring		m_name;				//名前
		BRANCH_CONDITION		m_condition;	//分岐条件
		UINT		m_indexCommand;		//条件コマンド配列添字
		WP_Command	m_pCommand;			//条件コマンドポインタ
		UINT		m_indexSequence;	//遷移先シークエンス添字
		WP_Sqc		m_pSequence;		//遷移先シークエンスポインタ
		UINT		m_indexFrame;		//遷移先スクリプト位置

	public:
		Branch ();
		Branch ( const Branch & rhs ) = delete;
		~Branch ();

		//名前
		tstring GetName () const { return m_name; }
		void SetName ( tstring name ) { m_name.assign ( name ); }

		//分岐条件
		void SetCondition ( BRANCH_CONDITION bc ) { m_condition = bc; }
		BRANCH_CONDITION GetCondition () const { return m_condition; }

		//条件コマンド配列添字
		void SetIndexCommand ( UINT index ) { m_indexCommand = index; }
		UINT GetIndexCommand () const { return m_indexCommand; }

		//条件コマンドポインタ
		void SetpCommand ( P_Command pCommand ) { m_pCommand = pCommand; }
		WP_Command GetpCommand () const { return m_pCommand; }

		//遷移先シークエンス配列添字
		void SetIndexSequence ( UINT index ) { m_indexSequence = index; }
		UINT GetIndexSequence () const { return m_indexSequence; }

		//遷移先シークエンスポインタ
		void SetpSequence ( P_Sqc pAction ) { m_pSequence = pAction; }
		WP_Sqc GetpSequence () const { return m_pSequence; }

		//遷移先スクリプト位置
		void SetIndexFrame ( UINT index ) { m_indexFrame = index; }
		UINT GetIndexFrame () const { return m_indexFrame; }
	};


	using P_Branch = shared_ptr < Branch >;
	using VP_Branch = vector < P_Branch >;
	using PVP_Branch = shared_ptr < VP_Branch >;


}	//namespace GAME


