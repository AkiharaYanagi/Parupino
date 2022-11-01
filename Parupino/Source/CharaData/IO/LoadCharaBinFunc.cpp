//=================================================================================================
//
// LoadCharaFunc �\�[�X�t�@�C��
//
//=================================================================================================
#include "LoadCharaBinFunc.h"

#include <codecvt>

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	LoadCharaBinFunc::LoadCharaBinFunc ()
	{
		::setlocale ( LC_ALL, "japanese" );
	}


	void LoadCharaBinFunc::LoadChara ( P_CH buf, UINT & pos, Chara & ch )
	{
	}

	void LoadCharaBinFunc::LoadBehavior ( P_CH buf, UINT & pos, Chara & ch )
	{
		//�A�N�V������
		byte nAct = (byte)buf [ pos ++ ];

		//�������̊m��
		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
		for ( UINT i = 0; i < nAct; ++ i )
		{
			aryAct [ i ] = make_shared < Action > ();
		}

		//���f�[�^
		for ( UINT iAct = 0; iAct < nAct; ++ iAct )
		{
			//�A�N�V������
			byte nStrName = buf [ pos ++ ];	//Encoding.UTF8
			aryAct [ iAct ]->SetName ( LoadText ( buf.get () + pos, nStrName ) );
			pos += nStrName;

			aryAct [ iAct ]->SetNextID ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetCategory ( (ACTION_CATEGORY)buf [ pos ++ ] );
			aryAct [ iAct ]->SetPosture ( (ACTION_POSTURE)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitNum ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitPitch ( (UINT)buf [ pos ++ ] );

			//�X�N���v�g��
			byte nScp = (byte)buf [ pos ++ ];

			//�������̊m��
			unique_ptr < P_Script [] > aryScp = make_unique < P_Script [] > ( nScp );
			for ( UINT i = 0; i < nScp; ++ i )
			{
				aryScp [ i ] = make_shared < Script > ();
			}

			for ( UINT iScp = 0; iScp < nScp; ++ iScp )
			{
				UINT indexImage = (UINT)buf [ pos ++ ];

				aryScp [ iScp ]->SetImageIndex ( indexImage );
			}

		}
	}
	
	void LoadCharaBinFunc::LoadGarnish ( P_CH buf, UINT & pos, Chara & ch )
	{
	}

	void LoadCharaBinFunc::LoadCommand ( P_CH buf, UINT & pos, Chara & ch )
	{
		//�R�}���h��
		byte nCmd = (byte)buf [ pos ++ ];
		
		//�������̊m��
		unique_ptr < P_Command[] > aryCmd = make_unique < P_Command[] > ( nCmd );
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			aryCmd [ i ] = make_shared < Command > ();
		}

		//���f�[�^
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			//�R�}���h��
			byte nStrName = buf [ pos ++ ];	//Encoding.UTF8
			aryCmd [ i ]->SetName ( LoadText ( buf.get() + pos, nStrName ) );
			pos += nStrName;

			//��t����
			aryCmd [ i ]->SetLimitTime ( (UINT)buf [ pos ++ ] );

			//�Q�[���L�[
			byte nGameKey = buf [ pos ++ ];
			unique_ptr < _GameKeyCommand [] > gkc = make_unique < _GameKeyCommand [] > ( nGameKey );
			for ( UINT iKey = 0; iKey < nGameKey; ++ iKey )
			{
				//�ے�
				bool bNot = (bool)buf [ pos ++ ];

				//���o�[ [ _GameKey::LVR_NUM = 8 ]
				KEY_ST lvr [ _GameKey::LVR_NUM ] = { _GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iLvr = 0; iLvr < _GameKey::LVR_NUM; ++ iLvr )
				{
					lvr [ iLvr ] = (KEY_ST)buf [ pos ++ ];
				}

				//�{�^�� [ _GameKey::BTN_NUM = 8 ]
				KEY_ST btn [ _GameKey::BTN_NUM ] = { _GameKeyCommand::GAME_KEY_WILD };
				for ( UINT iBtn = 0; iBtn < _GameKey::BTN_NUM; ++ iBtn )
				{
					btn [ iBtn ] = (KEY_ST)buf [ pos ++ ];
				}

				gkc [ iKey ].SetNot ( bNot );
				gkc [ iKey ].SetaLvr ( lvr );
				gkc [ iKey ].SetaBtn ( btn );
			}

			aryCmd [ i ]->SetaGameKey ( gkc.get (), nGameKey );
		}

		ch.AddaCommand ( ::move ( aryCmd ), nCmd );
	}


	void LoadCharaBinFunc::LoadBranch ( P_CH buf, UINT & pos, Chara & ch )
	{
		//�u�����`��
		byte nBrc = (byte)buf [ pos ++ ];

		//�������̊m��
		unique_ptr < P_Branch [] > aryBrc = make_unique < P_Branch [] > ( nBrc );
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			aryBrc [ i ] = make_shared < Branch > ();
		}

		//���f�[�^
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			//�u�����`��
			byte nStrName = buf [ pos ++ ];	//size	Encoding.UTF8
			aryBrc [ i ]->SetName ( LoadText ( buf.get () + pos, nStrName ) );
			pos += nStrName;

			//����
			aryBrc [ i ]->SetCondition ( (BRANCH_CONDITION)buf [ pos ++ ] );
			aryBrc [ i ]->SetIndexCommand ( (UINT)buf [ pos ++ ] );
			aryBrc [ i ]->SetIndexSequence ( (UINT)buf [ pos ++ ] );
			aryBrc [ i ]->SetIndexFrame ( (UINT)buf [ pos ++ ] );
		}

		ch.AddaBranch ( ::move ( aryBrc ), nBrc );
	}


	void LoadCharaBinFunc::LoadRoute ( P_CH buf, UINT & pos, Chara & ch )
	{
		//���[�g��
		byte nRut = (byte)buf [ pos ++ ];

		//�������̊m��
		unique_ptr < P_Route [] > aryRut = make_unique < P_Route [] > ( nRut );
		for ( UINT i = 0; i < nRut; ++ i )
		{
			aryRut [ i ] = make_shared < Route > ();
		}

		//���f�[�^
		for ( UINT i = 0; i < nRut; ++ i )
		{
			//���[�g��
			byte nStrName = buf [ pos ++ ];	//size	Encoding.UTF8
//			aryRut [ i ]->SetName ( LoadText ( buf.get () + pos, nStrName ) );
			tstring tstr( LoadText ( buf.get () + pos, nStrName ) );
			aryRut [ i ]->SetName ( tstr );

			pos += nStrName;

			//�u�����`ID��
			byte nIdBrc = (byte)buf [ pos ++ ];

			unique_ptr < UINT[] > aryIdBrc = make_unique < UINT[] > ( nIdBrc );

			for ( UINT id = 0; id < nIdBrc; ++ id )
			{
				aryIdBrc [ id ] = (UINT) buf [ pos ++ ];
			}

			aryRut [ i ]->SetaIdBranch ( ::move ( aryIdBrc ), nIdBrc );
		}

		ch.AddaRoute ( ::move ( aryRut ), nRut );
	}

	tstring LoadCharaBinFunc::LoadText ( char* buf, UINT length )
	{
//		unique_ptr < char [] > arypChar = make_unique < char [] > ( length + 1 );
//		memcpy_s ( arypChar.get(), length ,buf, length );
		
//		unique_ptr < TCHAR [] >  tbuf = make_unique < TCHAR [] > ( length + 1 );
//		size_t _PptNumOfCharConverted = 0;
//		errno_t err = ::mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get (), length + 1, arypChar.get (), _TRUNCATE );

		//UTF8 -> wstring
		string str ( buf, length );
		std::wstring_convert < std::codecvt_utf8_utf16 < wchar_t > > converter;
		tstring tstr = converter.from_bytes ( str );

		return tstr ;
	}

}	//namespace GAME

