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
			TRACE_F ( _T("Error LoadCharaBin.\n") );
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
		const byte CHARA_VERSION = 110;
		if ( CHARA_VERSION != version ) { throw _T ( "�L�����A�[�J�C�u�̃o�[�W�������قȂ�܂��B" ); }

		//---------------------------------------------------------------------
		//�X�N���v�g���̃T�C�Y
		UINT scriptSize = 0;
		ifstrm.read ( (char*)& scriptSize, sizeof ( UINT ) );

		//�ꎞ�Ǎ�
		P_CH scriptBuf = make_unique < char[] > ( scriptSize );
		ifstrm.read ( scriptBuf.get(), scriptSize );
		UINT pos = 0;	//�������|�C���^

		//Chara
		m_func.LoadChara ( scriptBuf, pos, chara );

		//---------------------------------------------------------------------
		//�t�@�C���X�g���[���I��
		ifstrm.close ();
	}


}	//namespace GAME

