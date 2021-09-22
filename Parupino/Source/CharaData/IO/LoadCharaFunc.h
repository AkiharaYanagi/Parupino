//=================================================================================================
//
// LoadCharaFunc ヘッダファイル
//
//=================================================================================================
#pragma once
#include "IOCharaDefine.h"
#include "LoadCharaUtl.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//	LoadCharaで用いる関数群
	//------------------------------------------------------------
	class LoadCharaFunc
	{
		//	内部使用関数
		LoadCharaUtl	m_utl;

		//関数オブジェクト型を定義
		//	P_ElementからCharaの値を読み込む関数：戻値void, 引数 P_Element, Chara
		using FP_ElemToCharaParam = std::function < void ( const P_Element, Chara & ) > ;

		//エレメントが持つエレメント配列に各読込関数を実行する
		void ElemAry ( const P_Element pElem, Chara & ch, FP_ElemToCharaParam fp );

		//----------------------------------
		//エレメントポインタからイメージリストを読み込む
		//データ読込　一時変数
		UINT	m_nMainImage;		//メインイメージリストの個数
		UINT	m_nEfImage;		//Efイメージリストの個数

		//イメージ名
		vector < tstring > m_vMainImageName;
		vector < tstring > m_vEfImageName;

		//------------------------------------------------------------
		//エレメントポインタからアクションを読み込む
		V_STR	m_vActionName;
//		void _ElemToActionArray ( const P_Element pElem, Chara & ch );	//配列
//		void _ElemToAction ( const P_Element pElem, const P_Action & pAction );
		void _ElemToActionC ( const P_Element pElem, Chara & ch );

		//エレメントポインタからスクリプトを読み込む
		void _ElemToScript ( const P_Element pElem, const P_Script pScript, UINT frame );


		//エレメントポインタからコマンドを読み込む
		V_STR	m_vCommandName;
//		void _ElemToCommandArray ( const P_Element pElem, Chara & ch );	//配列
//		void _ElemToCommand ( const P_Element pElem, const P_Command & pCommand );
		void _ElemToCommand ( const P_Element pElem, Chara & ch );

		//エレメントポインタからブランチを読み込む
		V_STR	m_vBranchName;
//		void _ElemToBranchArray ( const P_Element pElem, Chara & ch );	//配列
//		void _ElemToBranch ( const P_Element pElem, const P_Branch & pBranch );
		void _ElemToBranch ( const P_Element pElem, Chara & ch );

		//エレメントポインタからルートを読み込む
		V_STR	m_vRouteName;
//		void _ElemToRouteArray ( const P_Element pElem, Chara & ch );	//配列
//		void _ElemToRoute ( const P_Element pElem, Chara & ch, const P_Route & pRoute );
		void _ElemToRoute ( const P_Element pElem, Chara & ch );


		//エレメントポインタからゲームキーコマンドを読み込む
		void _ElemToGameKeyCmd ( const P_Element pElem, _GameKeyCommand & gameKeyCmd );
		_GameKeyCommand::GAME_KEY_STATE StrToKeyState ( tstring str );

		//基本状態アクションID
		void _ElemToBasicActionID ( const P_Element pElem, Chara & ch );


		//エレメントポインタからエフェクトを読み込む
		V_STR	m_vEffectName;
//		void _ElemToEffectArray ( const P_Element pElem, Chara & ch );	//配列
//		void _ElemToEffect ( const P_Element pElem, const P_Effect & pEffect );
		void _ElemToEffect ( const P_Element pElem, Chara & ch );

		//エレメントポインタからEFジェネレートを読み込む
		void _ElemToEfGnrtArray ( const P_Element pElem, const P_Script & pScript );	//配列
		void _ElemToEfGnrt ( const P_Element pElem, const P_EfGnrt & pEfGnrt );


		//------------------------------------------------------------
		//枠読込
#if 0
		//引数：エレメントポインタ, スクリプトポインタ, 枠を設定するScript内の関数ポインタ
		void _LoadRect ( const P_Element pElem, P_Script pScript, void(Script::* const pFuncAddRect)( RECT ) );
#endif // 0
		//関数型を定義
		//	クラスScriptにおけるRectを設定する関数：戻値void, 引数RECT
		using FP_SetRect = std::function < void ( RECT ) >;

		//引数：エレメントポインタ, スクリプトポインタ, 枠を設定するScript内の関数オブジェクト
		void _LoadRect ( const P_Element pElem, P_Script pSrcipt, FP_SetRect fp_SetRect );
		//引数：エレメントポインタ, 枠を設定するScript内の関数オブジェクト
		void _LoadRect ( const P_Element pElem, FP_SetRect fp_SetRect );

		//枠の読込
		void _LoadRectAll ( const PVP_Element pvpElem, const P_Script & pScript );

		//------------------------------------------------------------
		//スクリプト内のルート (アクションとコマンドの読込後、indexから実効オブジェクトのポインタを取得して設定する)
		void _LoadRouteInScript ( Chara & ch );


	public:
		LoadCharaFunc () = default;
		LoadCharaFunc ( const LoadCharaUtl & rhs ) = delete;
		~LoadCharaFunc () = default;

		//Documentからキャラに変換する
		void _DocumentToChara ( const Document & document, Chara & ch );

		//イメージアーカイブ読込
		void _LoadImage ( ifstream& pIfstrm, PVP_TxBs pvpTexture );
	};


}	//namespace GAME


