//=================================================================================================
//
// �ݒ�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameSettingFile.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	UP_GmStgFl	GameSettingFile::m_inst;

	GameSettingFile::GameSettingFile ()
	{
		try
		{
			//���̓X�g���[���𐶐�
			ifstream ifstrm( _T("GameSetting.dat"), ios::in );
			
			//������Ȃ��Ƃ��f�t�H���g�̒l��ݒ肵�ďI��
			if ( ! ifstrm ) { SetDefault (); }
			
			//�Ǎ�
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

			//�I��
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
		m_demo = false;				//�f�����[�h
		m_startBattle = false;		//�o�g������J�n
		m_training = false;		//�g���[�j���O���[�h
		m_input1pPlayer = true;
		m_input2pPlayer = true;
#if 0
		m_name1p = CHARA_SONIA;		//�I���L����
		m_name2p = CHARA_ORFLOAT;

		m_name1p = CHARA_TEST;		//�I���L����
		m_name2p = CHARA_TEST;
#endif // 0

		m_name1p = CHARA_RAKUNO;		//�I���L����
		m_name2p = CHARA_YUKINO;
	}


}	//namespace GAME

