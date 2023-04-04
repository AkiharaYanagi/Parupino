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


		DWORD startTime = ::timeGetTime ();




		//---------------------------------------------------------------------
		//�t�@�C���X�g���[���J�n
		ifstream ifstrm ( filename.c_str (), ios::binary );

		//�t�@�C�������݂��Ȃ��Ƃ��������Ȃ�
		if ( ifstrm.fail () ) { throw _T ( "�t�@�C�������݂��܂���B" ); }

		//�L�����A�[�J�C�u�t�@�C���`���̃o�[�W����
		UINT version = 0;	//�Ǎ��p
		ifstrm.read ( (char*)& version, sizeof ( UINT ) );
		const UINT CHARA_VERSION = 110;
		if ( CHARA_VERSION != version ) { throw _T ( "�L�����A�[�J�C�u�̃o�[�W�������قȂ�܂��B" ); }

		//---------------------------------------------------------------------
		//�S�̂̃T�C�Y
		UINT scriptSize = 0;
		ifstrm.read ( (char*)& scriptSize, sizeof ( UINT ) );

		//�ꎞ�Ǎ�
		P_CH scriptBuf = make_unique < char [] > ( scriptSize );
		ifstrm.read ( scriptBuf.get (), scriptSize );
		UINT pos = 0;	//�������|�C���^



		DWORD scriptRead_Time = ::timeGetTime ();



		//------------------------------------------

		//�L�����Ǎ�

		//�X�N���v�g
		m_func.LoadCharaScript ( scriptBuf, pos, chara );



		DWORD LoadScript_Time = ::timeGetTime ();



		//�C���[�W
		m_func.LoadCharaImage ( scriptBuf, pos, chara );

		//---------------------------------------------------------------------
		//�t�@�C���X�g���[���I��
		ifstrm.close ();


		DWORD LoadImage_Time = ::timeGetTime ();


		DWORD t0 = scriptRead_Time - startTime;
		DWORD t2 = LoadScript_Time - scriptRead_Time;
		DWORD t3 = LoadImage_Time - LoadScript_Time;
//		DBGOUT_WND_F ( 6, _T ( "scriptRead_Time = %d, LoadScript_Time = %d, LoadImage_Time = %d" ), t0, t2, t3 );
	}


}	//namespace GAME

