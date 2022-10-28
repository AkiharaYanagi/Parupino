//=================================================================================================
//
// LoadChara �\�[�X�t�@�C��
//
//=================================================================================================
#include "LoadCharaBin.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	LoadChara
	//		�X�N���v�g�ƃC���[�W���X�g��ۑ������L�����f�[�^ ".dat"�t�@�C�� ����AChara��ǂݍ���
	//==================================================================================
	LoadCharaBin::LoadCharaBin ( const tstring & filename, Chara & chara )
	{
		try
		{
			_Load ( filename, chara );
		}
		catch ( LPCTSTR lpctstr )
		{
			TRACE_F ( lpctstr );
		}
		catch (...)
		{
			TRACE_F ( _T("Error LoadChara.\n") );
		}
	}

	//----------------------------------
	//	�f�X�g���N�^
	//----------------------------------
	LoadCharaBin::~LoadCharaBin ()
	{
	}


	//------------------------------------------
	//	try�p���s�֐�
	//------------------------------------------
	void LoadCharaBin::_Load ( const tstring & filename, Chara & chara )
	{
		//---------------------------------------------------------------------
		//�t�@�C���X�g���[���J�n
		ifstream ifstrm ( filename.c_str (), ios::binary );

		//�t�@�C�������݂��Ȃ��Ƃ��������Ȃ�
		if ( ifstrm.fail () ) { throw _T ( "�t�@�C�������݂��܂���B" ); }

		//�L�����A�[�J�C�u�t�@�C���`���̃o�[�W����
		byte version = 0;	//�Ǎ��p
		ifstrm.read ( (char*)& version, sizeof ( byte ) );
		if ( CHARA_VERSION != version ) { throw _T ( "�L�����A�[�J�C�u�̃o�[�W�������قȂ�܂��B" ); }

		//---------------------------------------------------------------------
		//�X�N���v�g���̃T�C�Y
		UINT scriptSize = 0;
		ifstrm.read ( (char*)& scriptSize, sizeof ( UINT ) );

		//�ꎞ�Ǎ�
		unique_ptr < char [] > scriptBuf = make_unique < char[] > ( scriptSize );
		ifstrm.read ( scriptBuf.get(), scriptSize );

		UINT pos = 0;

		//Chara Command
		byte nCmd = (byte)scriptBuf [ pos ++ ];

		for ( UINT i = 0; i < nCmd; ++ i )
		{
			Command cmd;

			//�R�}���h��
			char nStrName = scriptBuf [ pos ++ ];	//Encoding.ASCII
			string str ( scriptBuf.get() + pos, nStrName );
			unique_ptr < TCHAR[] >  tbuf = make_unique < TCHAR[] > ( nStrName + 1 );
			size_t _PptNumOfCharConverted = 0;
			errno_t err = ::mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get (), nStrName + 1, str.c_str (), _TRUNCATE );
			cmd.SetName ( tstring ( tbuf.get () ) );
			pos += nStrName;

			//��t����
			cmd.SetLimitTime ( (UINT)scriptBuf [ pos ++ ] );

			//�Q�[���L�[
			byte nGameKey = scriptBuf [ pos ++ ];

			unique_ptr < _GameKeyCommand [] > gkc = make_unique < _GameKeyCommand [] > ( nGameKey );
			for ( UINT iKey = 0; iKey < nGameKey; ++ iKey )
			{
				//�ے�
				bool bNot = (bool) scriptBuf [ pos ++ ];

				//���o�[ [ _GameKey::LVR_NUM = 8 ]
				KEY_ST lvr [ _GameKey::LVR_NUM ] = { _GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iLvr = 0; iLvr < _GameKey::LVR_NUM; ++ iLvr )
				{
					lvr [ iLvr ] = (KEY_ST) scriptBuf [ pos ++ ];
				}

				//�{�^�� [ _GameKey::BTN_NUM = 8 ]
				KEY_ST btn [ _GameKey::BTN_NUM ] = { _GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iBtn = 0; iBtn < _GameKey::BTN_NUM; ++ iBtn )
				{
					btn [ iBtn ] = (KEY_ST) scriptBuf [ pos ++ ];
				}

				gkc [ iKey ].SetNot ( bNot );
				gkc [ iKey ].SetaLvr ( lvr );
				gkc [ iKey ].SetaBtn ( btn );
			}

			cmd.SetaGameKey ( gkc.get (), nGameKey );
#if 0
#endif // 0
		}

		//---------------------------------------------------------------------
		//�t�@�C���X�g���[���I��
		ifstrm.close ();
	}


}	//namespace GAME

