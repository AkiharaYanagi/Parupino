//=================================================================================================
//
// LoadCharaFunc �\�[�X�t�@�C��
//
//=================================================================================================
#include "LoadCharaFunc.h"
using namespace std;
using namespace std::placeholders;

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
using LCF = LoadCharaFunc;

	//========================================================
	//�h�L�������g����X�N���v�g�ɕϊ�����
	//========================================================
	void LoadCharaFunc::_DocumentToChara ( const Document & document, Chara & ch )
	{
		//���[�g���̑���p�ꎞ�G�������g�z��
		const PVP_Element pvpElemRt = document.Root()->GetpvpElement ();

		//---------------------------------------------------------------
		//���[�g -> �L����
		P_Element pElemChara = pvpElemRt->at ( 0 );
		PVP_Element pvpeCh = pElemChara->GetpvpElement ();

		//---------------------------------------------------------------
		//�o�[�W����
		P_Element pElemVer = pvpeCh->at ( ELEM_CHARA_VER );

		//---------------------------------------------------------------
		//���C���C���[�W���X�g�̃G�������g
		P_Element pElemMainImage = pvpeCh->at ( EL_MAIN_IMAGE_LIST );
		UINT sizeMainTexture = m_utl._ElemToUINT ( pElemMainImage, 0 );
		ch.GetpvpMainTexture()->resize ( sizeMainTexture );
		m_utl.ElemToNameArray ( pElemMainImage, m_vMainImageName );		//���O�̕ۑ�

		//Ef�C���[�W���X�g�̃G�������g
		P_Element pElemEfImage = pvpeCh->at ( EL_EF_IMAGE_LIST );
		UINT sizeEfTexture = m_utl._ElemToUINT ( pElemEfImage, 0 );
		ch.GetpvpEfTexture()->resize ( sizeEfTexture );
		m_utl.ElemToNameArray ( pElemEfImage, m_vEfImageName );		//���O�̕ۑ�

		//---------------------------------------------------------------
		//�A�N�V�����z��̃G�������g
		ElemAry ( pvpeCh->at ( EL_ACTION ), ch, bind ( & LCF::_ElemToActionC, this, _1, _2 ) );
		m_utl.ElemToNameArray ( pvpeCh->at ( EL_ACTION ), m_vActionName );

		//---------------------------------------------------------------
		//�G�t�F�N�g�z��̃G�������g
		ElemAry ( pvpeCh->at ( EL_EFFECT ), ch, bind ( & LCF::_ElemToEffect, this, _1, _2 ) );
		m_utl.ElemToNameArray ( pvpeCh->at ( EL_EFFECT ), m_vEffectName );

		//---------------------------------------------------------------
		//�R�}���h�z��̃G�������g
		ElemAry ( pvpeCh->at ( EL_COMMAND ), ch, bind ( & LCF::_ElemToCommand, this, _1, _2 ) );
		m_utl.ElemToNameArray ( pvpeCh->at ( EL_COMMAND ), m_vCommandName );

		//�u�����`�z��̃G�������g
		ElemAry ( pvpeCh->at ( EL_BRANCH ), ch, bind ( & LCF::_ElemToBranch, this, _1, _2 ) );
		m_utl.ElemToNameArray ( pvpeCh->at ( EL_BRANCH ), m_vBranchName );

		//���[�g�z��̃G�������g
		ElemAry ( pvpeCh->at ( EL_ROUTE ), ch, bind ( & LCF::_ElemToRoute, this, _1, _2 ) );
		m_utl.ElemToNameArray ( pvpeCh->at ( EL_ROUTE ), m_vRouteName );

		//---------------------------------------------------------------
		//�X�N���v�g���̃��[�g (�A�N�V�����ƃR�}���h�̓Ǎ���Aindex��������I�u�W�F�N�g�̃|�C���^���擾���Đݒ肷��)
		_LoadRouteInScript ( ch );
	}


	//-------------------------------------------------------------------
	//	�����g�p�֐�
	//-------------------------------------------------------------------

	//�G�������g�����q�G�������g�z��Ɋe�Ǎ��֐������s����
	void LoadCharaFunc::ElemAry ( P_Element pElem, Chara & ch, FP_ElemToCharaParam fp )
	{
		const PVP_Element pvpElem = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElem )
		{
			fp ( pe, ch );
		}
	}

	//�G�������g�|�C���^����A�N�V������ǂݍ��݁A�L�����ɒǉ�����
	void LoadCharaFunc::_ElemToActionC ( const P_Element pElem, Chara & ch )
	{
		P_Action pAction = make_shared < Action > ();	//����p�̐V�K�A�N�V����

		//---------------------------
		//attribute�z��|�C���^
		const PVP_Attribute pvpAttrAction = pElem->GetpvpAttribute ();

		//�A�N�V���� "���O"
		pAction->SetName ( pvpAttrAction->at ( ATTR_ACTION_NAME )->GetValue () );


		//UINT ���A�N�V����ID (�I�����ɂ����鎟�A�N�V�����̃��X�g���C���f�b�N�X)
		pAction->SetNextID (m_utl._AttrToUINT (pvpAttrAction->at (ATTR_ACTION_ID)));

		//tstring ���A�N�V������ (�I�����ɂ����鎟�A�N�V�����̖��O)
		pAction->SetNextName ( pvpAttrAction->at (ATTR_ACTION_ID)->GetValue () );


		//�A�N�V��������
		UINT indexCategory = m_utl._AttrToUINT ( (*pvpAttrAction)[ATTR_ACTION_CATEGORY] );
		ACTION_CATEGORY category = static_cast <ACTION_CATEGORY> (indexCategory);
		pAction->SetCategory ( category );

		//�A�N�V�����̐�
		ACTION_POSTURE ap = m_utl._AttrToACTION_POSTURE ( (*pvpAttrAction)[ATTR_ACTION_POSTURE] );
		pAction->SetPosture ( ap );

		//int ����o�����X�l
//		pAction->SetBalance ( _AttrToInt ( (*pvpAttrAction)[ATTR_ACTION_BALANCE] ) );

		//---------------------------

		//<Action>����Element
		//	<Script>�@...�s�萔
		const PVP_Element pvpElemScript = pElem->GetpvpElement ();
		UINT _frame = 0;
		for ( P_Element pe : *pvpElemScript )
		{
			P_Script pScript = make_shared < Script > ();		//�ݒ�p�X�N���v�g�𐶐�
			_ElemToScript ( pe, pScript, _frame ++ );		//�G�������g����X�N���v�g��Ǎ�
			pAction->AddpScript ( pScript );			//�A�N�V�����ɃX�N���v�g��ǉ�
		}

		//---------------------------

		ch.AddpAction ( pAction );			//�L�����ɃA�N�V������ǉ�
	}

	//�G�������g�|�C���^����G�t�F�N�g��ǂݍ��݁A�L�����ɒǉ�����
	void LoadCharaFunc::_ElemToEffect ( const P_Element pElem, Chara & ch )
	{
		P_Effect pEffect = make_shared < Effect > ();	//����p�̐V�K�G�t�F�N�g
		//---------------------------

		//attribute�z��|�C���^
		const PVP_Attribute pvpAttrAction = pElem->GetpvpAttribute ();

		//<Effect>����Element
		//	<Script>�@...�s�萔
		const PVP_Element pvpElemScript = pElem->GetpvpElement ();
		UINT _frame = 0;
		for ( P_Element pe : * pvpElemScript )
		{
			P_Script pScript = make_shared < Script > ();		//�ݒ�p�X�N���v�g�𐶐�
			_ElemToScript ( pe, pScript, _frame ++ );		//�G�������g����X�N���v�g��Ǎ�
			pEffect->AddpScript ( pScript );			//�G�t�F�N�g�ɃX�N���v�g��ǉ�
		}
		//---------------------------

		ch.AddpEffect ( pEffect );			//�L�����ɃG�t�F�N�g��ǉ�
	}

	void LoadCharaFunc::_ElemToScript ( const P_Element pElem, const P_Script pScript, UINT frame )
	{
		//-----------------------------------------------------------------------------
		//��Ɨp�A�g���r���[�g�z��|�C���^
		const PVP_Attribute pAttr = pElem->GetpvpAttribute ();

		//�t���[����
		pScript->SetFrame ( frame );

		//�O���[�v(�����ł͗p���Ȃ�)

		//�C���[�WID
//		//���O��ID�ɕϊ�
//		tstring tstrImageName = pAttr->at ( ATTR_SCRIPT_IMAGE_ID )->GetValue ();
//		pScript->SetImageIndex ( m_utl.IndexOf ( m_vMainImageName, tstrImageName ) );
		pScript->SetImageIndex ( m_utl._AttrToUINT ( pAttr->at ( ATTR_SCRIPT_IMAGE_ID ) ) );

		//Pos
		VEC2 pos = m_utl._AttrToVec2 ( pAttr->at ( ATTR_SCRIPT_POS_X ), pAttr->at ( ATTR_SCRIPT_POS_Y ) );
		pScript->SetPos ( pos );

		//Vel
		VEC2 vel = m_utl._AttrToVec2 ( pAttr->at ( ATTR_SCRIPT_VEL_X ), pAttr->at ( ATTR_SCRIPT_VEL_Y ) );
//		pScript->SetVel ( vel );
		pScript->m_prmBattle.Vel = vel;

		//Acc
		VEC2 acc = m_utl._AttrToVec2 ( pAttr->at ( ATTR_SCRIPT_ACC_X ), pAttr->at ( ATTR_SCRIPT_ACC_Y ) );
//		pScript->SetAcc ( acc );
		pScript->m_prmBattle.Acc = acc;

		//�v�Z���
		CLC_ST clcSt = m_utl._AttrToCLC_ST ( pAttr->at ( ATTR_SCRIPT_CLCST ) );
		pScript->m_prmBattle.CalcState = clcSt;

		//----------------------------------------------------
		//�p�����[�^

		//power
		int power = m_utl._AttrToInt ( pAttr->at ( ATTR_SCRIPT_POWER ) );
		pScript->m_prmBattle.Power = power;

		//blackout
		UINT blackout = m_utl._AttrToUINT ( pAttr->at ( ATTR_SCRIPT_BLACKOUT ) );
		pScript->m_prmStaging.BlackOut = blackout;

		//viberation
		UINT viberation = m_utl._AttrToUINT ( pAttr->at ( ATTR_SCRIPT_VIBRATION ) );
		pScript->m_prmStaging.Vibration = viberation;

		//stop
		UINT stop = m_utl._AttrToUINT ( pAttr->at ( ATTR_SCRIPT_STOP ) );
		pScript->m_prmStaging.Stop = stop;

		//-----------------------------------------------------------------------------
		//�X�N���v�g�����̃G�������g
		const PVP_Element pvpElemInScript = pElem->GetpvpElement ();

		//���[�g�z��̃G�������g
		P_Element pElemVecRoute = pvpElemInScript->at ( ELEM_SCRIPT_ROUTE );
		PVP_Element pvpElemRouteName = pElemVecRoute->GetpvpElement ();
		for ( P_Element pe : * pvpElemRouteName )
		{
			PVP_Attribute pa = pe->GetpvpAttribute ();
			UINT i = m_utl._AttrToUINT ( pa->at ( ATTR_SCRIPT_ROUTE_ID ) );
			pScript->AddRouteID ( i );
		}

		//EF�W�F�l���[�g�z��̃G�������g
		P_Element pElemVecEfGnrt = pvpElemInScript->at ( ELEM_SCRIPT_EFGNRT );
		_ElemToEfGnrtArray ( pElemVecEfGnrt, pScript );

		//�g�Ǎ�
		_LoadRectAll ( pvpElemInScript, pScript );
	}

	//�G�������g�|�C���^����R�}���h��ǂݍ���
	void LoadCharaFunc::_ElemToCommand ( const P_Element pElem, Chara & ch )
	{
		P_Command pCommand = make_shared < Command > ();	//����p�̐V�K�쐬
	
		//------------------------------------------------------------
		//�A�g���r���[�g�z��
		const PVP_Attribute pvpAttrCommand = pElem->GetpvpAttribute ();

		//Name
		const P_Attribute pAttrCommand = pvpAttrCommand->at ( ATTR_COMMAND_NAME );
		tstring strName = pAttrCommand->GetValue ();
		pCommand->SetName ( strName );

		//Limit
		UINT limitTime = m_utl._AttrToUINT ( pvpAttrCommand->at ( ATTR_COMMAND_LIMIT ) );
		pCommand->SetLimitTime ( limitTime );

		//------------------------------------------------------------
		//�G�������g

		//�qElement��_GameKey��s�萔�ێ�
		const PVP_Element pvpElemGameKey = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElemGameKey )
		{
			_GameKeyCommand gameKeyCmd;	//�R�s�[��
			_ElemToGameKeyCmd ( pe, gameKeyCmd );
			pCommand->AddGameKey ( gameKeyCmd );
		}
		//------------------------------------------------------------

		ch.AddpCommand ( pCommand );
	}

	//�G�������g�|�C���^����Q�[���L�[�R�}���h��ǂݍ���
	void LoadCharaFunc::_ElemToGameKeyCmd ( const P_Element pElem, _GameKeyCommand & gameKeyCmd )
	{
		//��Ɨp
		const PVP_Attribute pvpAttrGameKey = pElem->GetpvpAttribute ();

		//�ے�t���O
		gameKeyCmd.SetNot ( m_utl._AttrToBool ( pvpAttrGameKey->at ( ATTR_GAMEKEY_NOT ) ) );

		//�������ǂݍ����ENUM�ɕϊ�����
		int index = ATTR_GAMEKEY_LVR_ST;
		//�ELvr
		for ( UINT i = 0; i < (UINT)_GameKey::LVR_NUM; ++ i )
		{
			tstring strGameLvr = pvpAttrGameKey->at ( index + i )->GetValue ();
			gameKeyCmd.SetLvr ( i, StrToKeyState ( strGameLvr ) );
		}
		index += _GameKey::LVR_NUM;

		//�EBtn
		for ( UINT i = 0; i < (UINT)_GameKey::BTN_NUM; ++ i )
		{
			tstring strGameKey = pvpAttrGameKey->at ( index + i )->GetValue();
			gameKeyCmd.SetBtn ( i, StrToKeyState ( strGameKey ) );
		}
	}

	_GameKeyCommand::GAME_KEY_STATE LoadCharaFunc::StrToKeyState ( tstring str )
	{
		if ( 0 == str.compare ( _T ( "KEY_OFF" ) ) ){ return _GameKeyCommand::GAME_KEY_OFF; }
		else	if ( 0 == str.compare ( _T ( "KEY_ON" ) ) ) { return _GameKeyCommand::GAME_KEY_ON; }
		else	if ( 0 == str.compare ( _T ( "KEY_PUSH" ) ) ) { return _GameKeyCommand::GAME_KEY_PUSH; }
		else	if ( 0 == str.compare ( _T ( "KEY_RELE" ) ) ) { return _GameKeyCommand::GAME_KEY_RELE; }
		else	if ( 0 == str.compare ( _T ( "KEY_WILD" ) ) ) { return _GameKeyCommand::GAME_KEY_WILD; }
		else	if ( 0 == str.compare ( _T ( "KEY_IS" ) ) ) { return _GameKeyCommand::GAME_KEY_IS; }
		else	if ( 0 == str.compare ( _T ( "KEY_NIS" ) ) ) { return _GameKeyCommand::GAME_KEY_NIS; }
		return _GameKeyCommand::GAME_KEY_STATE ();
	}
	
	void LoadCharaFunc::_ElemToBranch ( const P_Element pElem, Chara & ch )
	{
		P_Branch pBranch = make_shared < Branch > ();	//����p�̐V�K�쐬

		//------------------------------------------------------------
		//�u�����`�̃A�g���r���[�g
		const PVP_Attribute pa = pElem->GetpvpAttribute ();

		//�������
		UINT indexCondition = m_utl._AttrToUINT ( pa->at ( ATTR_BRANCH_CONDITION ) );
		pBranch->SetCondition ( (BRANCH_CONDITION)indexCondition );

		//�����R�}���h�C���f�b�N�X
		UINT indexCommand = m_utl._AttrToUINT ( pa->at ( ATTR_BRANCH_COMMAND_ID ) );
		pBranch->SetIndexCommand ( indexCommand );

		//�J�ڐ�V�[�N�G���X�C���f�b�N�X
		UINT indexAction = m_utl._AttrToUINT ( pa->at ( ATTR_BRANCH_SEQUENCE_ID ) );
		pBranch->SetIndexSequence ( indexAction );

		//�J�ڐ�X�N���v�g�C���f�b�N�X
		UINT indexFrame = m_utl._AttrToUINT ( pa->at ( ATTR_BRANCH_FRAME_INDEX ) );
		pBranch->SetIndexFrame ( indexFrame );

		//------------------------------------------------------------
		ch.AddpBranch ( pBranch );			//�L�����ɒǉ�
	}

	void LoadCharaFunc::_ElemToRoute ( const P_Element pElem, Chara & ch )
	{
		P_Route pRoute = make_shared < Route > ();	//����p�̐V�K�쐬
		//------------------------------------------------------------
		//���[�g�̃G�������g
		P_Element pElemBlanchNameListNum = pElem->GetpvpElement ()->at ( 0 );
		const PVP_Element pvpElemBlanchNameList = pElemBlanchNameListNum->GetpvpElement ();
		for ( P_Element pe : * pvpElemBlanchNameList )
		{
			P_Attribute pa = pe->GetpvpAttribute ()->at ( ATTR_NAME_0 );
			UINT i = m_utl.IndexOf ( m_vBranchName, pa->GetValue () );
			pRoute->AddBranchID ( i );
		}
		//------------------------------------------------------------
		ch.AddpRoute ( pRoute );			//�L�����ɒǉ�
	}

	//�G�������g�|�C���^����EF�W�F�l���[�g��ǂݍ���
	void LoadCharaFunc::_ElemToEfGnrtArray ( const P_Element pElem, const P_Script & pScript )
	{
		//EF�W�F�l���[�g�z��̃G�������g�z��
		const PVP_Element pvpElemEfGnrt = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElemEfGnrt )
		{
			P_EfGnrt pEfGnrt = make_shared < EffectGenerate > ();			//����p�ɐV�K�쐬
			_ElemToEfGnrt ( pe, pEfGnrt );
			pScript->AddpEfGnrt ( pEfGnrt );			//�X�N���v�g�ɒǉ�
		}
	}

	void LoadCharaFunc::_ElemToEfGnrt ( const P_Element pElem, const P_EfGnrt & pEfGnrt )
	{
		///EF�W�F�l���[�g�̃A�g���r���[�g
		const PVP_Attribute pa = pElem->GetpvpAttribute();

		//�A�g���r���[�g��
		enum { NAME, INDEX, POS_X, POS_Y, POS_Z, GNRT, LOOP, SYNC, };

		//�w��Ef�C���f�b�N�X
		pEfGnrt->SetIndex ( m_utl._AttrToUINT ( pa->at ( INDEX ) ) );

		//�����ʒu
		pEfGnrt->SetPos ( m_utl._AttrToVec2 ( pa->at ( POS_X ), pa->at ( POS_Y ) ) );

		//z�ʒu
		pEfGnrt->SetZ ( m_utl._AttrToFloat ( pa->at ( POS_Z ) ) );

		//����
		pEfGnrt->SetGnrt ( m_utl._AttrToBool ( pa->at ( GNRT ) ) );

		//�J��
		pEfGnrt->SetLoop ( m_utl._AttrToBool ( pa->at ( LOOP ) ) );

		//����
		pEfGnrt->SetSync ( m_utl._AttrToBool ( pa->at ( SYNC ) ) );
	}

	
	//------------------------------------------------------------


	//�g�Ǎ�
#if 0
	//�֐��|�C���^
	void LoadCharaUtl::_LoadRect ( const P_Element pElemRect, P_Script pScript, void (Script::* const pFuncAddRect)(RECT) )
	{
		//�A�g���r���[�g�̓T�C�Y�̂�
		const PVP_Attribute pvecpAttrVecRect = pElemRect->GetpvpAttribute();
		UINT sizeRect = _AttrToUINT ( (*pvecpAttrVecRect)[0] );

		const PVP_Element pvecpElemRect = pElemRect->GetpvpElement();

		//�g
		for ( UINT i = 0; i < sizeRect; ++i )
		{
			//�G�������g
			P_Element pElem = (*pvecpElemRect)[i];

			//�A�g���r���[�g
			const PVP_Attribute pa = pElem->GetpvpAttribute();
			RECT rect = _AttrToRect ( (*pa)[0], (*pa)[1], (*pa)[2], (*pa)[3] );
			
			//�֐��|�C���^�Ŋe�g�ɐݒ�
			(pScript->*pFuncAddRect)( rect );
		}
	}
#endif // 0
	//�����F�G�������g�|�C���^, �X�N���v�g�|�C���^, �g��ݒ肷��Script���̊֐��I�u�W�F�N�g
	//�ݒ�p�֐���std::function�Ŏw��
	void LoadCharaFunc::_LoadRect ( const P_Element pElemRect, P_Script pScript, FP_SetRect fp_SetRect )
	{
		//�A�g���r���[�g�̓T�C�Y�̂�
		const PVP_Attribute pvpAttrVecRect = pElemRect->GetpvpAttribute ();
		UINT sizeRect = m_utl._AttrToUINT ( (*pvpAttrVecRect)[0] );

		//�G�������g
		const PVP_Element pvpElemRect = pElemRect->GetpvpElement ();

		//�g
		for ( UINT i = 0; i < sizeRect; ++i )
		{
			//�G�������g
			P_Element pElem = (*pvpElemRect)[i];

			//�A�g���r���[�g
			const PVP_Attribute pa = pElem->GetpvpAttribute();
			RECT rect = m_utl._AttrToRect ( (*pa)[0], (*pa)[1], (*pa)[2], (*pa)[3] );
			
			//FP_SetRect��pScript�Ɗ֘A�t���Ă���̂ł��̂܂܌Ăяo��
			fp_SetRect ( rect );
		}
	}

	//�����F�G�������g�|�C���^, �g��ݒ肷��Script���̊֐��I�u�W�F�N�g
	void LoadCharaFunc::_LoadRect ( const P_Element pElemRect, FP_SetRect fp_SetRect )
	{
		const PVP_Element pvpElemRect = pElemRect->GetpvpElement ();
		for ( P_Element pElem : * pvpElemRect )
		{
			const PVP_Attribute pa = pElem->GetpvpAttribute();
			RECT rect = m_utl._AttrToRect ( pa->at(0), pa->at(1), pa->at(2), pa->at(3) );
			fp_SetRect ( rect );	//FP_SetRect��pScript�Ɗ֘A�t���Ă���̂ł��̂܂܌Ăяo��
		}
	}

	void LoadCharaFunc::_LoadRectAll ( const PVP_Element pvpElem, const P_Script & pScript )
	{
#if 0
		//�֐��|�C���^�Ŏw�肷��
		_LoadRect ( (*cpvpElemInScript)[CRECT], pScript, &Script::AddCRect );
		_LoadRect ( (*cpvpElemInScript)[ARECT], pScript, &Script::AddARect );
		_LoadRect ( (*cpvpElemInScript)[HRECT], pScript, &Script::AddHRect );
		_LoadRect ( (*cpvpElemInScript)[ORECT], pScript, &Script::AddORect );
#endif // 0
#if 0
		//bind
		FP_SetRect func_c = std::bind ( & Script::AddCRect, pScript, std::placeholders::_1 );
		FP_SetRect func_a = std::bind ( & Script::AddARect, pScript, std::placeholders::_1 );
		FP_SetRect func_h = std::bind ( & Script::AddHRect, pScript, std::placeholders::_1 );
		FP_SetRect func_o = std::bind ( & Script::AddORect, pScript, std::placeholders::_1 );
#endif // 0

		//�����_��
		FP_SetRect func_c = [ & pScript ] ( RECT r ) { pScript->AddCRect ( r ); };
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_CRECT ), pScript, func_c );

		FP_SetRect func_a = [ & pScript ] ( RECT r ) { pScript->AddARect ( r ); };
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_ARECT ), pScript, func_a );

		FP_SetRect func_h = [ & pScript ] ( RECT r ) { pScript->AddHRect ( r ); };
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_HRECT ), pScript, func_h );

		FP_SetRect func_o = [ & pScript ] ( RECT r ) { pScript->AddORect ( r ); };
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_ORECT ), pScript, func_o );
	}


	//------------------------------------------------------------
	//�X�N���v�g�����[�g (�A�N�V�����ƃR�}���h�̓Ǎ���Aindex��������I�u�W�F�N�g�̃|�C���^���擾���Đݒ肷��)
	void LoadCharaFunc::_LoadRouteInScript ( Chara & ch )
	{
#if 0
		PVP_Action pvpAction = ch.GetpvpAction ();
		for ( P_Action pAc : * pvpAction )
		{
			PVP_Script pvpScript = pAc->GetpvpScript ();
			for ( P_Script pSc : * pvpScript )
			{
				PVP_Branch pvpBranch = pSc->GetpvpBranch ();
				for ( P_Branch pBr : * pvpBranch )
				{
					pBr->SetpSequence ( ch.GetpAction ( pBr->GetIndexAction () ) );
					pBr->SetpCommand ( ch.GetpCommand ( pBr->GetIndexCommand () ) );
				}
			}
		}
#endif // 0
	}

#if 0
	//��{��ԃA�N�V����ID
	void LoadCharaFunc::_ElemToBasicActionID ( const P_Element pElem, Chara & ch )
	{
		//��{��ԃA�N�V����ID (name�͔�΂�)
		const PVP_Element pvpElemBasicAction = pElem->GetpvpElement ();
//		P_Element pElemBasicAction = pvpElemBasicAction->at ( 0 );
		for ( UINT i = 0; i < BASIC_ACTION_NUM; ++ i )
		{
			UINT n = m_utl._ElemToUINT ( pvpElemBasicAction->at ( i ), 0 );
			ch.SetBsAction ( static_cast < BASIC_ACTION > ( i ), n );
		}
	}
#endif // 0

	//------------------------------------------------------------
	//�C���[�W�A�[�J�C�u�Ǎ�
	void LoadCharaFunc::_LoadImage ( ifstream & ifstrm, PVP_TxBs pvpTexture )
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

