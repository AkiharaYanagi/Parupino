//=================================================================================================
//
// LoadChara �\�[�X�t�@�C��
//
//=================================================================================================
#include "LoadChara.h"
//#include "Branch.h"	//Action��Command����������Chara.h�Ƃ͓Ɨ�

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	LoadChara
	//		�X�N���v�g�ƃC���[�W���X�g��ۑ������L�����f�[�^ ".dat"�t�@�C�� ����AChara��ǂݍ���
	//==================================================================================
	LoadChara::LoadChara ( const tstring & filename, Chara & chara ) 
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
	LoadChara::~LoadChara ()
	{
	}


	//------------------------------------------
	//	try�p���s�֐�
	//------------------------------------------
	void LoadChara::_Load ( const tstring & filename, Chara & chara )
	{


		DWORD startTime = ::timeGetTime ();




		//������
		chara.Reset ();

		//�g���q��.dat���ǂ����m�F
		const int NX = 4;	//�g���q�̕�����
		if ( 0 != filename.compare ( filename.size() - NX, NX, _T(".dat"), 0, NX ) )
		{
			throw _T("�g���q�G���[\n"); 
		}

		//------------------------------------------
		//@info  tifstream �ł͂Ȃ� ifstream
		//		�o�C�i���t�@�C���Ȃ̂�char�^�ň���
		//------------------------------------------

		//---------------------------------------------------------------------
		//�t�@�C���X�g���[���J�n
		ifstream ifstrm ( filename.c_str(), ios::binary );

		//�t�@�C�������݂��Ȃ��Ƃ��������Ȃ�
		if ( ifstrm.fail () ) { throw _T("�t�@�C�������݂��܂���B"); } 

		//�L�����f�[�^�`���̃o�[�W����[uint]
		UINT version = 0;	//�Ǎ��p
		ifstrm.read ( (char*)& version, sizeof ( UINT ) );
		if ( CHARA_VERSION != version ) { throw _T("�L�����A�[�J�C�u�̃o�[�W�������قȂ�܂��B"); } 

		//---------------------------------------------------------------------
		//�X�N���v�g���̃T�C�Y
		UINT scriptSize = 0;
		ifstrm.read ( (char*)& scriptSize, sizeof ( UINT ) );

		//�ꎞ�Ǎ�
		char* scriptBuf = new char [ scriptSize ];
		ifstrm.read ( scriptBuf, scriptSize );




		DWORD scriptRead_Time = ::timeGetTime ();





		//Document�𐶐�
		Document document ( scriptBuf, scriptSize );




		DWORD Document_Time = ::timeGetTime ();



		//�ꎞ�Ǎ��̔j��
		delete[] scriptBuf;

		//�L�����f�[�^�ɕϊ�
		m_func._DocumentToChara ( document, chara );




		DWORD DtoC_Time = ::timeGetTime ();



		//---------------------------------------------------------------------
		//�O���t�B�b�N�A�[�J�C�u�̓Ǎ�	(�X�N���v�g�̑�������EOF�܂�)

		//���C���C���[�W
		m_func._LoadImage ( ifstrm, chara.GetpvpMainTexture() );

		//Ef�C���[�W
		m_func._LoadImage ( ifstrm, chara.GetpvpEfTexture() );

		//---------------------------------------------------------------------
		//�t�@�C���X�g���[���I��
		ifstrm.close ();



		DWORD LoadImage_Time = ::timeGetTime ();

		DWORD t0 = scriptRead_Time - startTime;
		DWORD t1 = Document_Time - scriptRead_Time;
		DWORD t2 = DtoC_Time - Document_Time;
		DWORD t3 = LoadImage_Time - DtoC_Time;
//		DBGOUT_WND_F ( 6, _T ( "scriptRead_Time = %d, Document_Time = %d, DtoC_Time = %d, LoadImage_Time = %d" ), t0, t1, t2, t3 );
	}


}	//namespace GAME

