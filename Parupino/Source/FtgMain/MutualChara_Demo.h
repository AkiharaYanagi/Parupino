//=================================================================================================
//
//	MutualChara Demo ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "G_Ftg.h"
#include "FtgConst.h"	
#include "../GameMain/Param.h"
#include "../ExeChara/ExeChara_Demo.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class MutualChara_Demo : public TASK_VEC
	{
		//キャラ
		P_ExeChara_Demo		m_exeChara1;
		P_ExeChara_Demo		m_exeChara2;

	public:
		MutualChara_Demo ();
		MutualChara_Demo ( const MutualChara_Demo & rhs ) = delete;
		~MutualChara_Demo ();

		//パラメータ指定
		void ParamInit ( P_Param pParam );

		//戦闘開始の初期化
		void Start ();

		//スクリプトの毎フレーム処理
		void Conduct ();
	};

	using P_MutualChara_Demo = shared_ptr < MutualChara_Demo >;


}	//namespace GAME


