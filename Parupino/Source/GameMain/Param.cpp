//=================================================================================================
//
// パラメータ
//		シーン間をまたぐ値
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Param.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Param::Param ()
		: m_demo ( F ), m_battleStart ( F )
		, m_training ( F ), m_mutchMode ( MODE_PLAYER_PLAYER )
//		, m_charaName1p ( CHARA_SONIA ), m_charaName2p ( CHARA_ORFLOAT )
		, m_charaName1p ( CHARA_TEST ), m_charaName2p ( CHARA_TEST )
	{
		//ゲーム設定ファイル開始
		GM_STG ()->Create ();

		//ゲーム設定ファイルから読み込んだ値を対応
		m_demo = GM_STG ()->GetDemo ();
		m_battleStart = GM_STG ()->GetStartBattle ();
		m_training = GM_STG ()->GetTraining ();

		PLAYER_MODE pm1 = GM_STG ()->GetbInput1pPlayer () ? MODE_PLAYER : MODE_CPU;
		PLAYER_MODE pm2 = GM_STG ()->GetbInput2pPlayer () ? MODE_PLAYER : MODE_CPU;
		SetMutchMode ( pm1, pm2 );

		m_charaName1p = GM_STG ()->GetName1p ();
		m_charaName2p = GM_STG ()->GetName2p ();
	}

	Param::Param ( const Param & rhs )
		: m_demo ( F ), m_battleStart ( F )
		, m_training ( F ), m_mutchMode ( MODE_PLAYER_PLAYER )
		, m_charaName1p ( CHARA_TEST ), m_charaName2p ( CHARA_TEST )
	{
		m_demo = rhs.m_demo;
		m_battleStart = rhs.m_battleStart;
		m_mutchMode = rhs.m_mutchMode;
		m_charaName1p = rhs.m_charaName1p;
		m_charaName2p = rhs.m_charaName2p;
	}

	Param::~Param ()
	{
	}

	void Param::SetRandomChara ()
	{
		m_charaName1p = (CHARA_NAME)(rand () % CHARA_NAME_NUM);
		m_charaName2p = (CHARA_NAME)(rand () % CHARA_NAME_NUM);
	}

	void Param::SetRandomChara2p ()
	{
		m_charaName2p = (CHARA_NAME)(rand () % CHARA_NAME_NUM);
	}

	void Param::SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p )
	{
		if ( MODE_PLAYER == mode1p )
		{
			if ( MODE_PLAYER == mode2p ) { m_mutchMode = MODE_PLAYER_PLAYER; }
			if ( MODE_CPU == mode2p ) { m_mutchMode = MODE_PLAYER_CPU; }
			if ( MODE_NETWORK == mode2p ) { m_mutchMode = MODE_PLAYER_NETWORK; }
		}
		else if ( MODE_CPU == mode1p )
		{
			if ( MODE_PLAYER == mode2p ) { m_mutchMode = MODE_CPU_PLAYER; }
			if ( MODE_CPU == mode2p ) { m_mutchMode = MODE_CPU_CPU; }
		}
	}

	PLAYER_MODE Param::GetMode ( PLAYER_ID id ) const
	{
		PLAYER_MODE pm = MODE_PLAYER;
		if ( id == PLAYER_ID_1 )
		{
			switch ( m_mutchMode )
			{
			case MODE_PLAYER_PLAYER:	pm = MODE_PLAYER;	break;
			case MODE_PLAYER_CPU:		pm = MODE_PLAYER; 	break;
			case MODE_CPU_PLAYER:		pm = MODE_CPU;	  	break;
			case MODE_CPU_CPU:			pm = MODE_CPU;	  	break;
			case MODE_PLAYER_NETWORK:	pm = MODE_PLAYER; 	break;
			default: break;
			}
		}
		if ( id == PLAYER_ID_2 )
		{
			switch ( m_mutchMode )
			{
			case MODE_PLAYER_PLAYER:	pm = MODE_PLAYER;	break;
			case MODE_PLAYER_CPU:		pm = MODE_CPU;	  	break;
			case MODE_CPU_PLAYER:		pm = MODE_PLAYER; 	break;
			case MODE_CPU_CPU:			pm = MODE_CPU;	  	break;
			case MODE_PLAYER_NETWORK:	pm = MODE_NETWORK; 	break;
			default: break;
			}
		}
		return pm;
	}

}	//namespace GAME

