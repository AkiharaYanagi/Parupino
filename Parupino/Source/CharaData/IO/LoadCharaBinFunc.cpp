//=================================================================================================
//
// LoadCharaFunc �\�[�X�t�@�C��
//
//=================================================================================================
#include "LoadCharaBinFunc.h"

//#include <codecvt>

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	LoadCharaBinFunc::LoadCharaBinFunc ()
	{
	}


	void LoadCharaBinFunc::LoadChara ( P_CH buf, UINT & pos, Chara & ch )
	{
		LoadCharaScript ( buf, pos, ch );
		LoadCharaImage ( buf, pos, ch );
	}

	void LoadCharaBinFunc::LoadCharaScript ( P_CH buf, UINT & pos, Chara & ch )
	{
		LoadBehavior ( buf, pos, ch );	//Behavior
		LoadGarnish ( buf, pos, ch );	//Garnish
		LoadCommand ( buf, pos, ch );	//Command
		LoadBranch ( buf, pos, ch );	//Branch
		LoadRoute ( buf, pos, ch );		//Route
	}

	void LoadCharaBinFunc::LoadCharaImage ( P_CH buf, UINT & pos, Chara & ch )
	{
		LoadImg ( buf, pos, ch.GetpvpMainTexture () );
		LoadImg ( buf, pos, ch.GetpvpEfTexture () );
	}


	void LoadCharaBinFunc::LoadBehavior ( P_CH buf, UINT & pos, Chara & ch )
	{
		//@afford �������R���g���[��
		//�擪�� ���A�N�V������, ���X�N���v�g�� ���L�q�A�K�v���ɊY�����̃A�h���X��Ԃ�

		//�A�N�V������ �� �������̊m��
		byte nAct = (byte)buf [ pos ++ ];

#if 0
		unique_ptr < Action [] > pi = make_unique < Action [] > ( nAct );

		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
//		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = make_shared < Action > (); }

		shared_ptr < P_Action [] > aryShared { new P_Action [ nAct ] , default_delete < P_Action [] > () };
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = aryShared [ i ]; }
#endif // 0
#if 0
		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
		shared_ptr < Action [] > aryShared = make_shared < Action [] > ( nAct );
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ].reset ( & aryShared [ i ] ); }
#endif // 0

		unique_ptr < P_Action [] > aryAct = make_unique < P_Action [] > ( nAct );
//		vector < P_Action > aryAct ( nAct );
		for ( UINT i = 0; i < nAct; ++ i ) { aryAct [ i ] = make_shared < Action > (); }


		//���f�[�^
		for ( UINT iAct = 0; iAct < nAct; ++ iAct )
		{
			P_Action pAct = aryAct [ iAct ];


			TRACE_F ( _T ( "%d\n" ), iAct );


			//�A�N�V����
			aryAct [ iAct ]->SetName ( m_utl.LoadText ( buf, pos ) );
			aryAct [ iAct ]->SetNextID ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetCategory ( (ACTION_CATEGORY)buf [ pos ++ ] );
			aryAct [ iAct ]->SetPosture ( (ACTION_POSTURE)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitNum ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitPitch ( (UINT)buf [ pos ++ ] );
			aryAct [ iAct ]->SetBalance ( m_utl.LoadInt ( buf, pos ) );

			//�X�N���v�g�� �� �������̊m��
			byte nScp = (byte)buf [ pos ++ ];
			unique_ptr < P_Script [] > aryScp = make_unique < P_Script [] > ( nScp );
			for ( UINT i = 0; i < nScp; ++ i ) { aryScp [ i ] = make_shared < Script > (); }

			for ( UINT iScp = 0; iScp < nScp; ++ iScp )
			{
				aryScp [ iScp ]->SetFrame ( iScp );
				LoadScript ( buf, pos, (* aryScp [ iScp ]) );
			}

			aryAct [ iAct ]->AddaScript ( ::move (aryScp), nScp );
		}

//		ch.AddpAction ( aryAct, nAct );
		ch.AddpAction ( ::move ( aryAct ), nAct );
	}
	
	void LoadCharaBinFunc::LoadGarnish ( P_CH buf, UINT & pos, Chara & ch )
	{
		//�G�t�F�N�g�� �� �������̊m��
		byte nEfc = (byte)buf [ pos ++ ];

		vector < P_Effect > aryEfc( nEfc );
		for ( UINT i = 0; i < nEfc; ++ i ) { aryEfc [ i ] = make_shared < Effect > (); }

		//���f�[�^
		for ( UINT iEfc = 0; iEfc < nEfc; ++ iEfc )
		{
			//�G�t�F�N�g
			aryEfc [ iEfc ]->SetName ( m_utl.LoadText ( buf, pos ) );

			//�X�N���v�g�� �� �������̊m��
			byte nScp = (byte)buf [ pos ++ ];
			unique_ptr < P_Script [] > aryScp = make_unique < P_Script [] > ( nScp );
			for ( UINT i = 0; i < nScp; ++ i ) { aryScp [ i ] = make_shared < Script > (); }

			for ( UINT iScp = 0; iScp < nScp; ++ iScp )
			{
				aryScp [ iScp ]->SetFrame ( iScp );
				LoadScript ( buf, pos, ( * aryScp [ iScp ] ) );
			}
		}

		ch.AddpEffect ( aryEfc, nEfc );
	}

	void LoadCharaBinFunc::LoadCommand ( P_CH buf, UINT & pos, Chara & ch )
	{
		//�R�}���h�� �� �������̊m��
		byte nCmd = (byte)buf [ pos ++ ];
		unique_ptr < P_Command[] > aryCmd = make_unique < P_Command[] > ( nCmd );
		for ( UINT i = 0; i < nCmd; ++ i ) { aryCmd [ i ] = make_shared < Command > (); }

		//���f�[�^
		for ( UINT i = 0; i < nCmd; ++ i )
		{
			//�R�}���h��
			aryCmd [ i ]->SetName ( m_utl.LoadText ( buf, pos ) );

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
		//�u�����`�� �� �������̊m��
		byte nBrc = (byte)buf [ pos ++ ];
		unique_ptr < P_Branch [] > aryBrc = make_unique < P_Branch [] > ( nBrc );
		for ( UINT i = 0; i < nBrc; ++ i ) { aryBrc [ i ] = make_shared < Branch > (); }

		//���f�[�^
		for ( UINT i = 0; i < nBrc; ++ i )
		{
			//�u�����`��
			aryBrc [ i ]->SetName ( m_utl.LoadText ( buf, pos ) );

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
		//���[�g�� �� �������̊m��
		byte nRut = (byte)buf [ pos ++ ];
		unique_ptr < P_Route [] > aryRut = make_unique < P_Route [] > ( nRut );
		for ( UINT i = 0; i < nRut; ++ i ) { aryRut [ i ] = make_shared < Route > (); }

		//���f�[�^
		for ( UINT i = 0; i < nRut; ++ i )
		{
			P_Route pr = aryRut [ i ];

			//���[�g��
			aryRut [ i ]->SetName ( m_utl.LoadText ( buf, pos ) );

			//�u�����`ID��
			m_utl.LoadAryUint ( buf, pos, aryRut [ i ]->GetvIDBranch () );
		}

		ch.AddaRoute ( ::move ( aryRut ), nRut );
	}

	void LoadCharaBinFunc::LoadScript ( P_CH buf, UINT & pos, Script & scp )
	{
		//�C���[�W�C���f�b�N�X
		byte b = buf [ pos ++ ];
		scp.SetImageIndex ( (UINT)b );

		//�ʒu
		scp.SetPos ( m_utl.LoadVec2 ( buf, pos ) );

		// [] ���[�gID
		m_utl.LoadAryUint ( buf, pos, scp.GetvRouteID () );

		//�g
		m_utl.LoadListRect ( buf, pos, scp.GetpvCRect () );
		m_utl.LoadListRect ( buf, pos, scp.GetpvHRect () );
		m_utl.LoadListRect ( buf, pos, scp.GetpvARect () );
		m_utl.LoadListRect ( buf, pos, scp.GetpvORect () );

		// [] �G�t�F�N�g����
		byte nIdEfGnrt = buf [ pos ++ ];
		unique_ptr < EffectGenerate [] > aryEfGnrt = make_unique < EffectGenerate [] > ( nIdEfGnrt );
		for ( UINT i = 0; i < nIdEfGnrt; ++ i )
		{
			//�G�t�F�N�gID
			aryEfGnrt [ i ].SetIndex ( (UINT)buf [ pos ++ ] );
			//�ʒu
			int pos_x = m_utl.LoadInt ( buf, pos );
			int pos_y = m_utl.LoadInt ( buf, pos );
			aryEfGnrt [ i ].SetPos ( VEC2 ( (float)pos_x, (float)pos_y ) );
			//Z�l
			int z_per100F = (int)buf [ pos ++ ];
			aryEfGnrt [ i ].SetZ ( z_per100F / 100.f );
			//����
			aryEfGnrt [ i ].SetGnrt ( (bool)buf [ pos ++ ] );
			//���[�v
			aryEfGnrt [ i ].SetLoop ( (bool)buf [ pos ++ ] );
			//�ʒu����
			aryEfGnrt [ i ].SetSync ( (bool)buf [ pos ++ ] );
		}

		//�o�g���p�����[�^
		LoadScpPrm_Btl ( buf, pos, scp );

		//�X�e�[�W���O(���o)�p�����[�^
		LoadScpPrm_Stg ( buf, pos, scp );
	}


	//�X�N���v�g�E�퓬�p�����[�^
	void LoadCharaBinFunc::LoadScpPrm_Btl ( P_CH buf, UINT & pos, Script & scp )
	{
		scp.m_prmBattle.CalcState = (CLC_ST)m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Vel = m_utl.LoadVec2 ( buf, pos );
		scp.m_prmBattle.Acc = m_utl.LoadVec2 ( buf, pos );
		scp.m_prmBattle.Power = m_utl.LoadInt ( buf, pos );

		scp.m_prmBattle.Warp = m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Recoil_I = m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Recoil_E = m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Balance_I = m_utl.LoadInt ( buf, pos );
		scp.m_prmBattle.Balance_E = m_utl.LoadInt ( buf, pos );

		//test
		if ( 0 != scp.m_prmBattle.Balance_I )
		{
			int i = 0;
		}
	}


	//�X�N���v�g�E���o�p�����[�^
	void LoadCharaBinFunc::LoadScpPrm_Stg ( P_CH buf, UINT & pos, Script & scp )
	{
		scp.m_prmStaging.BlackOut		 = m_utl.LoadByte ( buf, pos );
		scp.m_prmStaging.Vibration		 = m_utl.LoadByte ( buf, pos );
		scp.m_prmStaging.Stop			 = m_utl.LoadByte ( buf, pos );

		scp.m_prmStaging.Radian			 = m_utl.LoadInt ( buf, pos );
		scp.m_prmStaging.AfterImage_N	 = m_utl.LoadByte ( buf, pos );
		scp.m_prmStaging.AfterImage_time = m_utl.LoadByte ( buf, pos ); ;
		scp.m_prmStaging.AfterImage_pitch = m_utl.LoadByte ( buf, pos ); ;
		scp.m_prmStaging.Vibration_S	 = m_utl.LoadByte ( buf, pos );;
		scp.m_prmStaging.Color			 = (_CLR)m_utl.LoadUInt ( buf, pos );;
		scp.m_prmStaging.Color_time		 = m_utl.LoadByte ( buf, pos );;
	}


	void LoadCharaBinFunc::LoadImg ( P_CH buf, UINT & pos, PVP_TxBs pvpTxBs )
	{
		//�����擾
		UINT nImg = (UINT)m_utl.LoadByte ( buf, pos );
		pvpTxBs->clear ();
		pvpTxBs->resize ( nImg );

		for ( UINT i = 0; i < nImg; ++ i )
		{
			//�T�C�Y���擾
			UINT size = m_utl.LoadUInt ( buf, pos );

			//��������̃f�[�^����Q�[���e�N�X�`���ɕϊ�
			P_TxMem pTx = make_shared < TxMem > ( (LPCVOID)(buf.get() + pos), size );
			pos += size;

			//�L���������̃e�N�X�`�����X�g�ɉ�����
			( *pvpTxBs ) [ i ] = pTx;
		}

	}


}	//namespace GAME

