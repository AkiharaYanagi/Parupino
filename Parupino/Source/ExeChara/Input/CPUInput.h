//=================================================================================================
//
// CPUInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaInput.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class ExeChara;
	using P_ExeChara = std::shared_ptr < ExeChara >;
	using WP_ExeChara = weak_ptr < ExeChara >;

	class CPUInput : public CharaInput
	{
		const UINT		m_vGameKeyNum;		//キー入力の保存フレーム数
		V_GAME_KEY		m_vGameKey;			//キー入力保存
		PLAYER_ID		m_playerID;			//プレイヤーID
		WP_ExeChara		m_pExeChara;		//自身の参照
		WP_ExeChara		m_pExeCharaOther;	//相手の参照

		//CPU行動種類
		enum CPU_ACT
		{
			CPU_NEUTRAL = 0,
			CPU_FRONT = 1,
			CPU_BACK = 2,
			CPU_FRONT_DASH = 3,
			CPU_BACK_DASH = 4,
			CPU_L = 5,
			CPU_M = 6,
			CPU_H = 7,
			CPU_AVOID = 8,
			CPU_POISED = 9,
			CPU_ACT_NUM = 10,
		};
		CPU_ACT		m_randomKeyNear	[ CENT ];		//近距離
		CPU_ACT		m_randomKeyMiddle [ CENT ];		//中距離
		CPU_ACT		m_randomKeyFar [ CENT ];		//遠距離

		bool		m_bAct;		//行動決定済
		CPU_ACT		m_act;
		UINT		m_timer;
		UINT		m_actTime;

		int m_testAct;

		//外部読込
		int			m_actNear[ CPU_ACT_NUM ];
		int			m_actMiddle[ CPU_ACT_NUM ];
		int			m_actFar[ CPU_ACT_NUM ];


	public:
		CPUInput ( WP_ExeChara p, WP_ExeChara pOther );
		CPUInput ( const CPUInput & rhs ) = delete;
		~CPUInput ();

		//設定
		void SetPlayer ( PLAYER_ID id ) { m_playerID = id; }
//		void SetpExeChara ( WP_ExeChara p ) { m_pExeChara = p; }
//		void SetpExeCharaOther ( WP_ExeChara p ) { m_pExeCharaOther = p; }

		//フレーム毎の更新
		void Update ( bool dirRight );

		//ブランチリストをチェックして
		//コマンド条件が達成されていたら遷移先のアクションIDを返す
		UINT GetTransitID ( PVP_Branch pvpBranch, bool dirRight );

		void SetCPU_Act ( int index, int act[], CPU_ACT cpu_act[] );

	};


}	//namespace GAME


