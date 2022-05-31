//=================================================================================================
//
//	MutualChara �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "MutualChara.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MutualChara::MutualChara ()
		: m_startTimer ( 0 ), m_startTime ( 0 ), m_endTimer ( 0 ), m_endTime ( 0 )
		, m_tmrHitstop ( 0 ), m_blackOut ( 0 )
	{
		//�L����
		m_exeChara1 = make_shared < ExeChara > ( PLAYER_ID_1 );
		m_exeChara2 = make_shared < ExeChara > ( PLAYER_ID_2 );

		m_exeChara1->SetpOther ( m_exeChara2 );
		m_exeChara2->SetpOther ( m_exeChara1 );

		AddpTask ( m_exeChara1 );
		AddpTask ( m_exeChara2 );

		//�q�b�g�X�g�b�v�^�C�}�[
		m_tmrHitstop = make_shared < Timer > ();
		m_tmrHitstop->SetTargetTime ( HITSTOP_TIME );
		AddpTask ( m_tmrHitstop );

		//���ʃG�t�F�N�g
		m_efClang = make_shared < EfClang > ();
		GRPLST_INSERT ( m_efClang );
		m_efSpark = make_shared < EfSpark > ();
		GRPLST_INSERT ( m_efSpark );
//		m_testEf = make_shared < TestEf > ();
//		GRPLST_INSERT ( m_testEf );
	}

	MutualChara::~MutualChara ()
	{
	}

	void MutualChara::ParamInit ( P_Param pParam )
	{
		m_exeChara1->ParamInit ( pParam );
		m_exeChara2->ParamInit ( pParam );
	}

	//��#########################################################
	//��
	//��	�X�N���v�g�̖��t���[������
	//��
	//��#########################################################
	void MutualChara::Conduct ()
	{
		//---------------------------------------------------
		SwitchRect ();	//�g�\���ؑ�
		//---------------------------------------------------

		//�X�N���v�g�O����(���́A�ړ��Ȃ�)
		m_exeChara1->PreScriptMove ();
		m_exeChara2->PreScriptMove ();

		//���ݔ���(�Ԃ���g)
		Collision ();

		//�Ԃ����A�U���E�q�b�g����g��ݒ�
		m_exeChara1->ScriptRectMove ();
		m_exeChara2->ScriptRectMove ();

		//���ݔ���(�U���E�q�b�g�g)
		Decision ();

		//�X�N���v�g�㏈��(�O���t�B�b�N�ʒu�Ȃ�)
		m_exeChara1->PostScriptMove ();
		m_exeChara2->PostScriptMove ();

		//�O���t�B�b�N����
		Grp ();
	}


	//��================================
	//		���ݔ���(�Ԃ���g)
	//��================================
	void MutualChara::Collision ()
	{
		//���҂̐ڐG�g���擾
		P_CharaRect pCharaRect1p = m_exeChara1->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_exeChara2->GetpCharaRect ();
		PV_RECT pvRect1p = pCharaRect1p->GetpvCRect ();
		PV_RECT pvRect2p = pCharaRect2p->GetpvCRect ();

		//�ڐG����
		//�d�Ȃ��Ă���Ƃ�
		if ( OverlapAryRect ( pvRect1p, pvRect2p ) )
		{
			m_exeChara1->BackPtX ();	//�݂���x�����݈̂ʒu��߂�
			m_exeChara2->BackPtX ();

			//����ɏd�Ȃ��Ă���Ƃ�
			int i = 0;
			while ( OverlapAryRect ( pvRect1p, pvRect2p ) )
			{
				m_exeChara1->BackMoveX ();	//������
				m_exeChara2->BackMoveX ();

				m_exeChara1->AdjustCRect ();
				m_exeChara2->AdjustCRect ();

				pvRect1p = pCharaRect1p->GetpvCRect ();
				pvRect2p = pCharaRect2p->GetpvCRect ();

				if ( ++i > 10 ) { break; }
			}
		}

		//�U��
		m_exeChara1->LookOther ();
		m_exeChara2->LookOther ();

		//��������(��ʒ[���m)
		float p1x = m_exeChara1->GetPos ().x;
		float p2x = m_exeChara2->GetPos ().x;
		if ( p2x - p1x > WINDOW_WIDTH - FIELD_EDGE * 2 )
		{
			m_exeChara1->BackPtX ();	//�݂��Ɉʒu��߂�
			m_exeChara2->BackPtX ();
		}
	}

	//��================================
	//��		���ݔ���(�U���E�q�b�g�g)
	//��================================
	void MutualChara::Decision ()
	{
		//------------------------------------------------------
		//�q�b�g�X�g�b�v�͉������Ȃ�
		if ( m_tmrHitstop->IsActive () ) { return; }
#if 0
		//�ō����͉������Ȃ�
		if ( m_exeChara1.GetClang () || m_exeChara2.GetClang () ) { return;	}
#endif // 0

		//------------------------------------------------------
		//����p�ꎞ�ϐ�

		//���著�M�p
//		CLANG_DECISION_LR sendDecision = CD_OFF; 

		//�d�Ȃ蒆�S�ʒu
		VEC2 center = VEC2 ( 0, 0 );

		//�{�̑��E�t���O
		bool offset = false;

		//�{�̃q�b�g�t���O
		bool hit1P = false;
		bool hit2P = false;

		//�G�t�F�N�g�q�b�g�t���O
		bool Efhit1P = false;
		bool Efhit2P = false;

		//�g�Ǘ��̎擾
		P_CharaRect pCharaRect1p = m_exeChara1->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_exeChara2->GetpCharaRect ();

		//�U���g���擾
		PV_RECT pvARect1 = pCharaRect1p->GetpvARect ();
		PV_RECT pvARect2 = pCharaRect2p->GetpvARect ();

		//���E�g���擾
		PV_RECT pvORect1 = pCharaRect1p->GetpvORect ();
		PV_RECT pvORect2 = pCharaRect2p->GetpvORect ();

		//����g���擾
		PV_RECT pvHRect1 = pCharaRect1p->GetpvHRect ();
		PV_RECT pvHRect2 = pCharaRect2p->GetpvHRect ();

		//�G�t�F�N�g���X�g�̎擾
		PLP_ExEf plpExEf1 = m_exeChara1->GetplpExEf ();
		PLP_ExEf plpExEf2 = m_exeChara2->GetplpExEf ();

		//------------------------------------------------------
		//����


		//------------------------------------------------------
		//�_�b�V���Ԃ��蔻��
		//[D]:�_�b�V���ɂ�����U������[A]


		//[D]-><-[D] : ���ꑊ�E
		bool b = DcsAtoA ( pCharaRect1p, pCharaRect2p, center );


		//[D]->[A],[D]->[O] : �ʏ푊�E
		//[D]->[H] : �ʏ�q�b�g����݂��ɃX�N���v�g�ŃA�N�V�����ڍs



		//------------------------------------------------------
		//�ō��F�U������ƍU������A�܂��͍U������Ƒ��E���� (���E�Ƒ��E�͉������Ȃ�)

		//�G�t�F�N�g���X�g�̑��E�`�F�b�N
		DcsOffsetEf ( plpExEf1, plpExEf2, pCharaRect2p );		//p1����p2�ւ̃`�F�b�N
		DcsOffsetEf ( plpExEf2, plpExEf1, pCharaRect1p );		//p2����p1�ւ̃`�F�b�N

		//���C���L�������m�̑��E�`�F�b�N
		offset = DcsOffset ( pCharaRect1p, pCharaRect2p, center );


		//------------------------------------------------------
		//�G�t�F�N�g�̃q�b�g�`�F�b�N
		int powerEf1p;
		int powerEf2p;
		if ( DcsHitEf ( plpExEf1, pvHRect2, m_exeChara2, powerEf1p ) )
		{
			Efhit2P = true;	//p1����p2�ւ̃`�F�b�N
		}
		if ( DcsHitEf ( plpExEf2, pvHRect1, m_exeChara1, powerEf2p ) )
		{
			Efhit1P = true;	//p2����p1�ւ̃`�F�b�N
		}

		//���C���L�����̃q�b�g�`�F�b�N
		//���҂̔�����s���Ă��甽�f����(�Е������f����ƃq�b�g��Ԃ��Q�Ƃ��Ă��܂�����)
		if ( !offset )	//���E���Ă��Ȃ��Ƃ��̂�
		{	//or���Z
			hit2P |= OverlapAryRect ( pvARect1, pvHRect2 );	//�q�b�g����ƍU������(1P->2P)
			hit1P |= OverlapAryRect ( pvARect2, pvHRect1 );	//�q�b�g����ƍU������(2P->1P)
		}

	}

	//------------------------------------------------------
	//	���ʃO���t�B�b�N
	//------------------------------------------------------
	void MutualChara::Grp ()
	{
		//---------------------------------------------------
		//�Ó]
		UINT blackout1P = m_exeChara1->GetBlackOut ();
		UINT blackout2P = m_exeChara2->GetBlackOut ();
		if ( 0 < blackout1P )
		{
			m_blackOut = blackout1P;
			m_exeChara1->SetBlackOut ( 0 );
		}

		//---------------------------------------------------
		//�X�N���v�g����̒�~
		UINT scpStop1P = m_exeChara1->GetScpStop ();
		UINT scpStop2P = m_exeChara2->GetScpStop ();
		if ( 0 < scpStop1P )
		{
			m_scpStop = scpStop1P;
			m_exeChara1->SetScpStop ( 0 );

			m_exeChara1->SetStopTimer ( m_scpStop );
			m_exeChara2->SetStopTimer ( m_scpStop );
		}

		//---------------------------------------------------
		//��ʕ\���̊�ʒu������
		VEC2 pos1p = m_exeChara1->GetPos ();
		VEC2 pos2p = m_exeChara2->GetPos ();
		G_Ftg::inst ()->CulcPosMutualBase ( pos1p, pos2p );
	}

	//------------------------------------------------------
	//	�I������
	//------------------------------------------------------
	bool MutualChara::CheckZeroLife ()
	{
		//�I������
		bool finish1p = m_exeChara1->IsZeroLife ();
		bool finish2p = m_exeChara2->IsZeroLife ();
		return ( finish1p || finish2p );
	}

	bool MutualChara::CheckDown ()
	{
		//�_�E������
		bool down1p = m_exeChara1->IsDown ();
		bool down2p = m_exeChara2->IsDown ();
		return (down1p || down2p);
	}

	bool MutualChara::CheckDownEnd ()
	{
		//�_�E������
		bool downEnd1p = m_exeChara1->IsDownEnd ();
		bool downEnd2p = m_exeChara2->IsDownEnd ();
		return (downEnd1p || downEnd2p);
	}

	bool MutualChara::CheckWin ()
	{
		//������Ԕ���
		bool win1p = m_exeChara1->IsWin ();
		bool win2p = m_exeChara2->IsWin ();
		return (win1p || win2p);
	}

	bool MutualChara::CheckWinEnd ()
	{
		//������Ԕ���
		bool winEnd1p = m_exeChara1->IsWinEnd ();
		bool winEnd2p = m_exeChara2->IsWinEnd ();
		return (winEnd1p || winEnd2p);
	}

	bool MutualChara::CheckWinner ()
	{
		bool bRet = false;

		//���C�t�ŏ����҂����肷��
		int life1p = m_exeChara1->GetLife ();
		int life2p = m_exeChara2->GetLife ();

		//Double K.O.
		if ( life1p <= 0 && life2p <= 0 ) { m_winner = WINNER_DP; }
		//2P Win
		else if ( life1p <= 0 ) { m_winner = WINNER_2P; }
		//1P Win
		else if ( life2p <= 0 ) { m_winner = WINNER_1P; }
		//Draw
		else if ( life1p == life2p ) { m_winner = WINNER_DRAW; }

		switch ( m_winner )
		{
		case WINNER_1P: 
			m_exeChara1->SetCharaState ( CHST_WIN_END );
			m_exeChara2->SetCharaState ( CHST_DOWN_END );
			break;
		case WINNER_2P: 
			m_exeChara1->SetCharaState ( CHST_DOWN_END );
			m_exeChara2->SetCharaState ( CHST_WIN_END );
			break;
		case WINNER_DP: break;
		default: break;
		}

		return bRet;
	}

	CHARA_NAME MutualChara::GetWinnerName () const
	{
		switch ( m_winner )
		{
		case WINNER_1P: return m_exeChara1->GetCharaName (); break;
		case WINNER_2P: return m_exeChara2->GetCharaName (); break;
		case WINNER_DP: break;
		default: break;
		}
		return CHARA_NAME ();
	}


	void MutualChara::ForcedEnd ()
	{
		m_exeChara1->ForcedEnd ();
		m_exeChara2->ForcedEnd ();
	}

	//------------------------------------------------------
	//	�����֐�
	//------------------------------------------------------
	//�U���g ���m����@(���S�t)
	bool MutualChara::DcsAtoA (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//�U���g���擾
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvARect2 = pcr2->GetpvARect ();

		//------------------------------------------------------
		//�U������ƍU�����肪�d�Ȃ��Ă�����true
		if ( OverlapAryRect_Center (pvARect1, pvARect2, center) )
		{
			return true;
		}

		return false;
	}

	//���E�g����(���S�t)
	bool MutualChara::DcsOffset (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//�U���g���擾
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvARect2 = pcr2->GetpvARect ();

		//���E�g���擾
		PV_RECT pvORect1 = pcr1->GetpvORect ();
		PV_RECT pvORect2 = pcr2->GetpvORect ();

		//����g���擾
		PV_RECT pvHRect1 = pcr1->GetpvHRect ();
		PV_RECT pvHRect2 = pcr2->GetpvHRect ();

		//------------------------------------------------------
		//�ō��F�U������ƍU������A�܂��͍U������Ƒ��E���� (���E�Ƒ��E�͉������Ȃ�)
		if (OverlapAryRect_Center (pvARect1, pvARect2, center)
			|| OverlapAryRect_Center (pvORect1, pvARect2, center)
			|| OverlapAryRect_Center (pvARect1, pvORect2, center))
		{
			return true;
		}

		return false;
	}

	//�G�t�F�N�g�̑��E�g����
	void MutualChara::DcsOffsetEf ( PLP_ExEf plpExEf1, PLP_ExEf plpExEf2, P_CharaRect pCharaRect2p )
	{
		VEC2 centeref = VEC2 ( 0, 0 );

		//�G�t�F�N�g���X�g�̑��E�`�F�b�N
		for ( P_ExEf pexef1 : (*plpExEf1) )
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//Ef
			for ( P_ExEf pexef2 : (*plpExEf2) )
			{
				P_CharaRect pcref2 = pexef2->GetpCharaRect ();

				if ( DcsOffset ( pcref1, pcref2, centeref ) )
				{
					//���E�� �eEf�ɋL�^
					pexef1->SetOffset ( true );
				}
			}
			//Chara
			if ( DcsOffset ( pcref1, pCharaRect2p, centeref ) )
			{
				//Ef�ɑ��E��Ԃ�ݒ�
				pexef1->SetOffset ( true );
			}
		}

	}


	//�G�t�F�N�g�̃q�b�g�g����
	bool MutualChara::DcsHitEf ( PLP_ExEf plpExEf1, PV_RECT pvHRect2, P_ExeChara pHitChara, int & refPower )
	{
		bool ret = false;
		VEC2 centeref = VEC2 ( 0, 0 );

		//�G�t�F�N�g���X�g�̃q�b�g�`�F�b�N
		for ( P_ExEf pexef1 : (*plpExEf1) )
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//���E���͔�΂�
			if ( pexef1->GetOffset () ) { continue; }

			//�g�Ǘ��̎擾
			P_CharaRect pcr1pEf = pexef1->GetpCharaRect ();

			//�U���g���擾
			PV_RECT pvARect1 = pcr1pEf->GetpvARect ();

			//Chara
			if ( OverlapAryRect_Center ( pvARect1, pvHRect2, centeref ) )
			{
				//�U���l��ݒ�
				refPower = pexef1->GetpScript ()->GetPower ();

				//Ef�Ƀq�b�g��Ԃ�ݒ�
				pexef1->SetHit ( true );

				//Chara�Ƀq�b�g��Ԃ�ݒ�
				ret = true;
			}
		}

		return ret;
	}

	//�����ɃL�����ɔ��f����
	void MutualChara::Propagate ()
	{
		//------------------------------------------------------
		//���f

		//���E����
		if (offset)
		{
#if 0
			//�U����ނ̎擾
			Action::ACTION_CATEGORY ac1p = m_exeChara1.GetActionCategory ();
			Action::ACTION_CATEGORY ac2p = m_exeChara2.GetActionCategory ();

			//�U����ނ̑g����
			UINT x = 0;
			switch (ac1p)
			{
			case Action::ATTACK_L: x = 0; break;
			case Action::ATTACK_M: x = 1; break;
			case Action::ATTACK_H: x = 2; break;
			default: 0; break;	//���̑���"��"����
			}
			UINT y = 0;
			switch (ac2p)
			{
			case Action::ATTACK_L: y = 0; break;
			case Action::ATTACK_M: y = 1; break;
			case Action::ATTACK_H: y = 2; break;
			default: 0; break;	//���̑���"��"����
			}
			UINT lurch1p = LURCH[x][y];
			UINT lurch2p = LURCH[y][x];


			//[�c][��]
			const UINT c_indexDecision[3][3] =
			{
				//	{���, �㒆, �㋭}, 
				//	{����, ����, ����}, 
				//	{����, ����, ����}
	#if	0
					{ CD_EQUAL, CD_RIGHT, CD_RIGHT },
					{ CD_LEFT, CD_EQUAL, CD_RIGHT },
					{ CD_LEFT, CD_LEFT, CD_EQUAL }
	#endif	//0
					//�い��
					{ CD_EQUAL, CD_RIGHT, CD_LEFT },
					{ CD_LEFT, CD_EQUAL, CD_RIGHT },
					{ CD_RIGHT, CD_LEFT, CD_EQUAL }
			};

			//���菟���̕��͑ō��̂�����ɂȂ炸�A�q�b�g�X�g�b�v�̌�A�N�V�������s(�L�����Z���\)

			//ExeChara�ɒʒB
			const CLANG_DECISION_WL c_decision_wl[3] = { CD_DRAW, CD_WIN, CD_LOSE };

			m_exeChara1.OnClang (lurch1p, c_decision_wl[c_indexDecision[x][y]]);
			m_exeChara2.OnClang (lurch2p, c_decision_wl[c_indexDecision[y][x]]);


			//�ō�����
			const CLANG_DECISION_LR c_decision[3] = { CD_EQUAL, CD_LEFT, CD_RIGHT };

			//�ō����ʕ\�� (�ō����ʏ��������E�ɕϊ�)
			if (m_exeChara1.GetDirRight ())	//1P���E��(�����FLEFT)
			{
				sendDecision = c_decision[c_indexDecision[x][y]];
			}
			else
			{
				sendDecision = c_decision[c_indexDecision[y][x]];
			}
#endif // 0

			//�ō����̃G�t�F�N�g����
			m_efClang->On (center);
			m_efSpark->On (center);

			//SE
			SOUND->Play (SE_Clang);

			//�q�b�g�X�g�b�v�J�n
			m_tmrHitstop->Start ();
			m_exeChara1->OnClang (0, CD_DRAW);
			m_exeChara2->OnClang (0, CD_DRAW);
		}

		//------------------------------------------------------
		//Ef�q�b�g����
		if (Efhit2P)
		{
			m_exeChara1->OnEfHit ();		//�q�b�g���
			m_exeChara2->OnDamaged (powerEf1p);		//���炢��ԁE�_���[�W����
		}

		if (Efhit1P)
		{
			m_exeChara2->OnEfHit ();		//�q�b�g���
			m_exeChara1->OnDamaged (powerEf2p);		//���炢��ԁE�_���[�W����
		}

		//���C���q�b�g����
		if (hit2P)
		{
			int power1P = m_exeChara1->GetPower ();	//�U���l
			m_exeChara1->OnHit ();		//�q�b�g���
			m_exeChara2->OnDamaged (power1P);		//���炢��ԁE�_���[�W����
		}

		if (hit1P)
		{
			int power2P = m_exeChara2->GetPower ();	//�U���l
			m_exeChara2->OnHit ();		//�q�b�g���
			m_exeChara1->OnDamaged (power2P);		//���炢��ԁE�_���[�W����
		}
	}


	//------------------------------------------------------
	//�g�\���ؑ� ExeChara�ŌĂԂ�1P2P�łQ��Ă΂�Ă��܂�
	void MutualChara::SwitchRect ()
	{
		//static bool b1 = false;
		static bool b1 = true;
		if ( ::GetAsyncKeyState ( '1' ) & 0x0001 ) { b1 ^= true; }
		if ( b1 )
		{
			m_exeChara1->OnDispRect ();
			m_exeChara2->OnDispRect ();
		}
		else
		{
			m_exeChara1->OffDispRect ();
			m_exeChara2->OffDispRect ();
		}
	}

	//------------------------------------------------------
	//	ExeChara���ґ���
	//------------------------------------------------------
	void MutualChara::SetReady ()
	{
		//����
		m_exeChara1->SetCharaState ( CHST_START );
		m_exeChara2->SetCharaState ( CHST_START );
	}
	void MutualChara::SetMain ()
	{
		//�J�n
		m_exeChara1->SetMain ();
		m_exeChara2->SetMain ();
	}
	void MutualChara::Wait ( bool b )
	{
		//���͒�~
		m_exeChara1->SetWait ( b );
		m_exeChara2->SetWait ( b );
	}
	void MutualChara::Stop ( bool b )
	{
		//�ꎞ��~
		m_exeChara1->SetStop ( b );
		m_exeChara2->SetStop ( b );
	}
	void MutualChara::SetEndWait ()
	{
		//�I���ҋ@
		m_exeChara1->SetEndWait ();
		m_exeChara2->SetEndWait ();
	}
	void MutualChara::EndAct ()
	{
		//�I��
		m_exeChara1->OnEndAct ();
		m_exeChara2->OnEndAct ();
	}
	void MutualChara::SetCharaState ( CHARA_STATE chst )
	{
		//��Ԃ̐ݒ�
		m_exeChara1->SetCharaState ( chst );
		m_exeChara2->SetCharaState ( chst );
	}

}	//namespace GAME

