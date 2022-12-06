//=================================================================================================
//
// 設定ファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameSettingFile.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//コンストラクタ
	GameSettingFile::GameSettingFile ()
		: m_startMode ( START_BATTLE )
		, m_playerMode1p ( MODE_PLAYER ), m_playerMode2p ( MODE_PLAYER )
		, m_name1p ( CHARA_TEST ), m_name2p ( CHARA_TEST )
	{
	}

	//コピーコンストラクタ
	GameSettingFile::GameSettingFile ( const GameSettingFile & rhs )
	{
		m_startMode		= rhs.m_startMode;
		m_playerMode1p	= rhs.m_playerMode1p;
		m_playerMode2p	= rhs.m_playerMode2p;
		m_name1p		= rhs.m_name1p;
		m_name2p		= rhs.m_name2p;
	}

	void GameSettingFile::Load ()
	{
		try
		{
			//入力ストリームを生成
			ifstream ifstrm( _T("GameSettings.dat"), ios::in | ios::binary );
			
			//見つからないときデフォルトの値を設定して終了
			if ( ! ifstrm ) { SetDefault (); }

			byte tempName1p = 0;
			byte tempName2p = 0;
			ifstrm.read ( (char*)& tempName1p, sizeof ( byte ) );
			ifstrm.read ( (char*)& tempName2p, sizeof ( byte ) );
			m_name1p = (CHARA_NAME)tempName1p;
			m_name2p = (CHARA_NAME)tempName2p;

			//終了
			ifstrm.close ();
		}
		catch (...)
		{
			SetDefault ();
		}
	}

	GameSettingFile::~GameSettingFile ()
	{
	}
	
	void GameSettingFile::SetDefault ()
	{
		m_startMode = START_BATTLE;
		m_playerMode1p = MODE_PLAYER;
		m_playerMode2p = MODE_PLAYER;
		m_name1p = CHARA_TEST;
		m_name2p = CHARA_TEST;
	}


}	//namespace GAME

