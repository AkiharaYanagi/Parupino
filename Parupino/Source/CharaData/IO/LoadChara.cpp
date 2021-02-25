//=================================================================================================
//
// LoadChara �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "LoadChara.h"
#include "../../CharaData/Branch.h"	//Action��Command����������Chara.h�Ƃ͓Ɨ�

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

		//�L�����A�[�J�C�u�t�@�C���`���̃o�[�W����
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

		//Document�𐶐�
		Document document ( scriptBuf, scriptSize );

		//�ꎞ�Ǎ��̔j��
		delete[] scriptBuf;

		//�L�����f�[�^�ɕϊ�
		m_utl._DocumentToChara ( document, chara );

		//---------------------------------------------------------------------
		//�O���t�B�b�N�A�[�J�C�u�̓Ǎ�	(�X�N���v�g�̑�������EOF�܂�)

		//���C���C���[�W
		_LoadImage ( ifstrm, chara.GetpvpMainTexture() );

		//Ef�C���[�W
		_LoadImage ( ifstrm, chara.GetpvpEfTexture() );

		//---------------------------------------------------------------------
		//�t�@�C���X�g���[���I��
		ifstrm.close ();
	}

	//------------------------------------------------------------
	//�C���[�W�A�[�J�C�u�Ǎ�
	void LoadChara::_LoadImage ( ifstream & ifstrm, PVP_TxBs pvpTexture )
	{
		//�C���[�W�̌��Ń��[�v
		UINT size = pvpTexture->size ();
		for ( UINT i = 0; i < size; ++ i )
		{
			//�C���[�W�̌ʃT�C�Y��Ǎ�
			UINT imageSize = 0;
			ifstrm.read ( (char*)&imageSize, sizeof ( UINT ) );

			//�ꎞ�̈�̊m�ۂ���A�C���[�W�{�̂̓Ǎ�
			char* imageBuf = new char [ imageSize ];
			ifstrm.read ( imageBuf, imageSize );

			//��������̃f�[�^����Q�[���e�N�X�`���ɕϊ�
			P_TxMem pGameTexture = make_shared < TxMem > ( (LPCVOID)imageBuf, imageSize );

			//�ꎞ�̈�͉������
			delete[] imageBuf;

			//�L���������̃e�N�X�`�����X�g�ɉ�����
			(*pvpTexture) [ i ] = pGameTexture;
		}
	}


}	//namespace GAME

