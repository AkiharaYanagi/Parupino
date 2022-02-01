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
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	UP_GmStgFl	GameSettingFile::m_inst;

	GameSettingFile::GameSettingFile ()
	{
		try
		{
			//入力ストリームを生成
			ifstream ifstrm( _T("GameSetting.dat"), ios::in );
			
			//見つからないときデフォルトの値を設定して終了
			if ( ! ifstrm ) { SetDefault (); }
			
			//読込
			ifstrm.read ( (char*)& m_demo, sizeof ( bool ) );
			ifstrm.read ( (char*)& m_startBattle, sizeof ( bool ) );
			ifstrm.read ( (char*)& m_training, sizeof ( bool ) );
			ifstrm.read ( (char*)& m_input1pPlayer, sizeof ( bool ) );
			ifstrm.read ( (char*)& m_input2pPlayer, sizeof ( bool ) );
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
		}
	}

	GameSettingFile::~GameSettingFile ()
	{
	}
	
	void GameSettingFile::SetDefault ()
	{
		m_demo = false;				//デモモード
		m_startBattle = false;		//バトルから開始
		m_training = false;		//トレーニングモード
		m_input1pPlayer = true;
		m_input2pPlayer = true;
#if 0
		m_name1p = CHARA_SONIA;		//選択キャラ
		m_name2p = CHARA_ORFLOAT;

		m_name1p = CHARA_TEST;		//選択キャラ
		m_name2p = CHARA_TEST;
#endif // 0

		m_name1p = CHARA_RAKUNO;		//選択キャラ
		m_name2p = CHARA_YUKINO;
	}


}	//namespace GAME

