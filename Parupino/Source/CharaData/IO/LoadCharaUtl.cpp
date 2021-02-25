//=================================================================================================
//
// LoadCharaUtl �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "LoadCharaUtl.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//========================================================
	//�h�L�������g����X�N���v�g�ɕϊ�����
	//========================================================
	void LoadCharaUtl::_DocumentToChara ( const Document & document, Chara & chara )
	{
		//���[�g���̑���p�ꎞ�G�������g�z��
		const PVP_Element pvpElemRt = document.Root()->GetpvpElement ();

		//---------------------------------------------------------------
		//�L����
		P_Element pElemChara = pvpElemRt->at ( 0 );
		PVP_Element pvpElemChara = pElemChara->GetpvpElement ();

		//---------------------------------------------------------------
		//�o�[�W����
		P_Element pElemVer = pvpElemChara->at ( ELEM_CHARA_VER );
//		UINT ver = _ElemToUINT ( pElemVer, 0 );

		//---------------------------------------------------------------
		//���C���C���[�W���X�g�̃G�������g
		P_Element pElemMainImage = pvpElemChara->at ( EL_MAIN_IMAGE_LIST );
		UINT sizeMainTexture = _ElemToUINT ( pElemMainImage, 0 );
		chara.GetpvpMainTexture()->resize ( sizeMainTexture );

		//Ef�C���[�W���X�g�̃G�������g
		P_Element pElemEfImage = pvpElemChara->at ( EL_EF_IMAGE_LIST );
		UINT sizeEfTexture = _ElemToUINT ( pElemEfImage, 0 );
		chara.GetpvpEfTexture()->resize ( sizeEfTexture );

		//---------------------------------------------------------------
		//�A�N�V�����z��̃G�������g
		P_Element pElemVecAction = pvpElemChara->at ( EL_ACTION );
		_ElemToActionArray ( pElemVecAction, chara );

		//---------------------------------------------------------------
		//�G�t�F�N�g�z��̃G�������g
		//---------------------------------------------------------------
		P_Element pElemVecEf = pvpElemChara->at ( EL_EFFECT );
		_ElemToEffectArray ( pElemVecEf, chara );

		//---------------------------------------------------------------
		//�R�}���h�z��̃G�������g
		P_Element pElemVecCommand = pvpElemChara->at ( EL_COMMAND );
		_ElemToCommandArray ( pElemVecCommand, chara );

		//---------------------------------------------------------------
		//�u�����` (�A�N�V�����ƃR�}���h�̓Ǎ���Aindex��������I�u�W�F�N�g�̃|�C���^���擾���Đݒ肷��)
		_LoadBranch ( chara );
	}



	//-------------------------------------------------------------------
	//	�����g�p�֐�
	//-------------------------------------------------------------------
	//�G�������g�|�C���^����index�Ԗڂ̃A�g���r���[�g��Value��UINT�ɒ����ĕԂ�
	UINT LoadCharaUtl::_ElemToUINT ( const P_Element pElem, UINT indexAttr )
	{
		UINT ui = 0;
		try
		{
			const PVP_Attribute pvpAttr = pElem->GetpvpAttribute();
			tistringstream tiss ( (*pvpAttr)[ indexAttr ]->GetValue() );
			tiss >> ui;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _ElemToUINT.\n") );
		}
		return ui;
	}

	//�G�������g�|�C���^����A�N�V�����z���ǂݍ���
	void LoadCharaUtl::_ElemToActionArray ( const P_Element pElem, Chara & chara )
	{
		const PVP_Element pvpElemAction = pElem->GetpvpElement();
		for ( P_Element pe : * pvpElemAction )
		{
			P_Action pAction = make_shared < Action > ();	//����p�̐V�K�A�N�V����
			_ElemToAction ( pe, pAction );		//�G�������g����A�N�V�����ɓǍ�
			chara.AddpAction ( pAction );			//�L�����ɃA�N�V������ǉ�
		}
	}

	//�G�������g�|�C���^����A�N�V������ǂݍ���
	void LoadCharaUtl::_ElemToAction ( const P_Element pElem, const P_Action & pAction )
	{
		//attribute�z��|�C���^
		const PVP_Attribute pvpAttrAction = pElem->GetpvpAttribute ();

		//�A�N�V���� "���O"
		pAction->SetName ( pvpAttrAction->at ( ATTR_ACTION_NAME )->GetValue() );

		//UINT ���A�N�V����ID (�I�����ɂ����鎟�A�N�V�����̃��X�g���C���f�b�N�X)
		pAction->SetNextID ( _AttrToUINT ( pvpAttrAction->at ( ATTR_ACTION_NEXT ) ) );

		//�A�N�V��������
		UINT indexCategory = _AttrToUINT ( (*pvpAttrAction)[ATTR_ACTION_CATEGORY] );
		ACTION_CATEGORY category = static_cast < ACTION_CATEGORY > ( indexCategory );
		pAction->SetCategory ( category );

		//�A�N�V�����̐�
		ACTION_POSTURE ap = _AttrToACTION_POSTURE ( (*pvpAttrAction)[ATTR_ACTION_POSTURE] );
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
	}

	//�G�������g�|�C���^����G�t�F�N�g�z���ǂݍ���
	void LoadCharaUtl::_ElemToEffectArray ( const P_Element pElem, Chara & chara )
	{
		const PVP_Element pvpElemEffect = pElem->GetpvpElement();
		for ( P_Element pe : * pvpElemEffect )
		{
			P_Effect pEffect = make_shared < Effect > ();	//����p�̐V�K�G�t�F�N�g
			_ElemToEffect ( pe, pEffect );		//�G�������g����G�t�F�N�g�ɓǍ�
			chara.AddpEffect ( pEffect );			//�L�����ɃG�t�F�N�g��ǉ�
		}
	}

	//�G�������g�|�C���^����G�t�F�N�g��ǂݍ���
	void LoadCharaUtl::_ElemToEffect ( const P_Element pElem, const P_Effect & pEffect )
	{
		//attribute�z��|�C���^
		const PVP_Attribute pvpAttrAction = pElem->GetpvpAttribute ();

		//---------------------------
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
	}


	void LoadCharaUtl::_ElemToScript ( const P_Element pElem, const P_Script pScript, UINT frame )
	{
		//-----------------------------------------------------------------------------
		//��Ɨp�A�g���r���[�g�z��|�C���^
		const PVP_Attribute p = pElem->GetpvpAttribute();

		//�t���[����
		pScript->SetFrame ( frame );

		//�O���[�v(�����ł͗p���Ȃ�)

		//�C���[�WID
		UINT imageID = _AttrToUINT ( p->at ( ATTR_SCRIPT_IMAGE_ID ) );
		pScript->SetImageIndex ( imageID );

		//Pos
		VEC2 pos = _AttrToVec2( p->at ( ATTR_SCRIPT_POS_X ), p->at ( ATTR_SCRIPT_POS_Y ) );
		pScript->SetPos ( pos );

		//Vel
		VEC2 vel = _AttrToVec2( p->at ( ATTR_SCRIPT_VEL_X ), p->at ( ATTR_SCRIPT_VEL_Y ) );
		pScript->SetVel ( vel );

		//Acc
		VEC2 acc = _AttrToVec2( p->at ( ATTR_SCRIPT_ACC_X ), p->at ( ATTR_SCRIPT_ACC_Y ) );
		pScript->SetAcc ( acc );

		//�v�Z���
		CLC_ST clcSt = _AttrToCLC_ST ( p->at ( ATTR_SCRIPT_CLCST ) );
		pScript->SetCalcState ( clcSt );

		//power
		int power = _AttrToInt ( p->at ( ATTR_SCRIPT_POWER ) );
		pScript->SetPower ( power );

		//-----------------------------------------------------------------------------
		//�X�N���v�g�����̃G�������g
		const PVP_Element pvpElemInScript = pElem->GetpvpElement ();

		//�u�����`�z��̃G�������g
		P_Element pElemVecBranch = pvpElemInScript->at ( ELEM_SCRIPT_BRANCH );
		_ElemToBranchArray ( pElemVecBranch, pScript );

		//EF�W�F�l���[�g�z��̃G�������g
		P_Element pElemVecEfGnrt = pvpElemInScript->at ( ELEM_SCRIPT_EFGNRT );
		_ElemToEfGnrtArray ( pElemVecEfGnrt, pScript );

		//�g�Ǎ�
		_LoadRectAll ( pvpElemInScript, pScript );
	}

	//�G�������g�|�C���^����R�}���h�z���ǂݍ���
	void LoadCharaUtl::_ElemToCommandArray ( const P_Element pElem, Chara & chara )
	{
		const PVP_Element pvpElemCommand = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElemCommand )
		{
			P_Command pCommand = make_shared < Command > ();	//����p�̐V�K�쐬
			_ElemToCommand ( pe, pCommand );			//�G�������g����R�}���h�ɓǍ�
			chara.AddpCommand ( pCommand );			//�L�����ɒǉ�
		}
	}

	//�G�������g�|�C���^����R�}���h��ǂݍ���
	void LoadCharaUtl::_ElemToCommand ( const P_Element pElem, const P_Command & pCommand )
	{
		//------------------------------------------------------------
		//�A�g���r���[�g�z��
		const PVP_Attribute pvpAttrCommand = pElem->GetpvpAttribute ();

		//Name
		const P_Attribute pAttrCommand = pvpAttrCommand->at ( ATTR_COMMAND_NAME );
		tstring strName = pAttrCommand->GetValue ();
		pCommand->SetName ( strName );

		//Limit
		UINT limitTime = _AttrToUINT ( pvpAttrCommand->at ( ATTR_COMMAND_LIMIT ) );
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
	}

	//�G�������g�|�C���^����Q�[���L�[�R�}���h��ǂݍ���
	void LoadCharaUtl::_ElemToGameKeyCmd ( const P_Element pElem, _GameKeyCommand & gameKeyCmd )
	{
		//��Ɨp
		const PVP_Attribute pvpAttrGameKey = pElem->GetpvpAttribute ();

		//�ے�t���O
		gameKeyCmd.SetNot ( _AttrToBool ( pvpAttrGameKey->at ( ATTR_GAMEKEY_NOT ) ) );

		//�������ǂݍ����ENUM�ɕϊ�����
		//�ELvr
		UINT idLvr = _AttrToUINT( pvpAttrGameKey->at ( ATTR_GAMEKEY_LVR_NUM ) );
		tstring strGameLvr = pvpAttrGameKey->at ( ATTR_GAMEKEY_LVR_NUM )->GetValue ();
		gameKeyCmd.SetLvr ( idLvr, StrToKeyState ( strGameLvr ) );

		//�EBtn
		for ( UINT i = 0; i < _GameKey::_BTN_NUM; ++ i )
		{
			tstring strGameKey = pvpAttrGameKey->at ( ATTR_GAMEKEY_BTN_ST + i )->GetValue();
			gameKeyCmd.SetBtn ( i, StrToKeyState ( strGameKey ) );
		}
	}

	_GameKeyCommand::GAME_KEY_STATE LoadCharaUtl::StrToKeyState ( tstring str )
	{
		return _GameKeyCommand::GAME_KEY_STATE ();
	}
	
	//�G�������g�|�C���^����u�����`��ǂݍ���
	void LoadCharaUtl::_ElemToBranchArray ( const P_Element pElem, const P_Script & pScript )
	{
		PVP_Element pvpElemBlanch = pElem->GetpvpElement ();
		for ( P_Element pe : * pvpElemBlanch )
		{
			P_Branch pBranch = make_shared < Branch > ();	//����p�ɐV�K�쐬
			_ElemToBranch ( pe, pBranch );
			pScript->AddpBranch ( pBranch );			//�X�N���v�g�ɒǉ�
		}
	}

	void LoadCharaUtl::_ElemToBranch ( const P_Element pElem, const P_Branch & pBranch )
	{
		//�u�����`�̃A�g���r���[�g
		const PVP_Attribute pa = pElem->GetpvpAttribute();
		UINT indexCommand = _AttrToUINT ( pa->at ( ATTR_BRANCH_COMMAND_INDEX ) );
		pBranch->SetIndexCommand ( indexCommand );		//�����R�}���h�C���f�b�N�X
		UINT indexAction = _AttrToUINT ( pa->at ( ATTR_BRANCH_ACTION_INDEX ) );
		pBranch->SetIndexAction ( indexAction );		//�J�ڐ�A�N�V�����C���f�b�N�X
		UINT indexFrame = _AttrToUINT ( pa->at ( ATTR_BRANCH_FRAME_INDEX ) );
		pBranch->SetIndexFrame ( indexFrame );		//�J�ڐ�X�N���v�g�C���f�b�N�X
	}
	
	//�G�������g�|�C���^����EF�W�F�l���[�g��ǂݍ���
	void LoadCharaUtl::_ElemToEfGnrtArray ( const P_Element pElem, const P_Script & pScript )
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

	void LoadCharaUtl::_ElemToEfGnrt ( const P_Element pElem, const P_EfGnrt & pEfGnrt )
	{
		///EF�W�F�l���[�g�̃A�g���r���[�g
		const PVP_Attribute pa = pElem->GetpvpAttribute();

		//�A�g���r���[�g��
		enum { NAME, INDEX, POS_X, POS_Y, POS_Z, GNRT, LOOP, SYNC, };

		//�w��Ef�C���f�b�N�X
		pEfGnrt->SetIndex ( _AttrToUINT ( pa->at ( INDEX ) ) );

		//�����ʒu
		pEfGnrt->SetPos ( _AttrToVec2 ( pa->at ( POS_X ), pa->at ( POS_Y ) ) );

		//z�ʒu
		pEfGnrt->SetZ ( _AttrToFloat ( pa->at ( POS_Z ) ) );

		//����
		pEfGnrt->SetGnrt ( _AttrToBool ( pa->at ( GNRT ) ) );

		//�J��
		pEfGnrt->SetLoop ( _AttrToBool ( pa->at ( LOOP ) ) );

		//����
		pEfGnrt->SetSync ( _AttrToBool ( pa->at ( SYNC ) ) );
	}

	
	//------------------------------------------------------------
	//(internal) �A�g���r���[�g�|�C���^����Value��bool�ɒ����ĕԂ�
	bool LoadCharaUtl::_AttrToBool ( const P_Attribute pAttr )
	{
		bool b = false;
		try
		{
			b = pAttr->GetValue().compare ( _T("True") ) == 0;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _AttrToBool.\n") );
		}
		return b;
	}

	//(internal) �A�g���r���[�g�|�C���^����Value��UINT�ɒ����ĕԂ�
	UINT LoadCharaUtl::_AttrToUINT ( const P_Attribute pAttr )
	{
		UINT ui = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> ui;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _AttrToUINT.\n") );
		}
		return ui;
	}

	//(internal) �A�g���r���[�g�|�C���^����Value��int�ɒ����ĕԂ�
	int LoadCharaUtl::_AttrToInt ( const P_Attribute pAttr )
	{
		int i = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> i;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _AttrToInt.\n") );
		}
		return i;
	}

	//(internal) �A�g���r���[�g�|�C���^����Value��float�ɒ����ĕԂ�
	float LoadCharaUtl::_AttrToFloat ( const P_Attribute pAttr )
	{
		float f = 0;
		try
		{
			tistringstream tiss ( pAttr->GetValue() );
			tiss >> f;
		}
		catch (...)
		{
			TRACE_F ( _T("Error _AttrToFloat.\n") );
		}
		return f;
	}

	//(internal) �A�g���r���[�g�|�C���^�Q����Value��VEC2�ɒ����ĕԂ�
	VEC2 LoadCharaUtl::_AttrToVec2 ( const P_Attribute pa0, const P_Attribute pa1 )
	{
		return VEC2 ( _AttrToFloat ( pa0 ), _AttrToFloat ( pa1 ) );
	}

	//(internal) �A�g���r���[�g�|�C���^�S����Value��RECT�ɒ����ĕԂ�
	//�����Fx, y, w, h
	RECT LoadCharaUtl::_AttrToRect ( const P_Attribute pa0, const P_Attribute pa1, const P_Attribute pa2, const P_Attribute pa3 )
	{
		//x0, y0, x1, y1�ɒ���
		int x = _AttrToInt ( pa0 );
		int y = _AttrToInt ( pa1 );
		int w = _AttrToInt ( pa2 );
		int h = _AttrToInt ( pa3 );

		RECT rect = { x, y, x + w, y + h };
		return rect;
	}

	//(internal) �A�g���r���[�g�|�C���^����Value��CLC_ST�ɒ����ĕԂ�
	CLC_ST LoadCharaUtl::_AttrToCLC_ST ( const P_Attribute pAttr )
	{
		CLC_ST clcSt = (CLC_ST)_AttrToInt ( pAttr );
#if 0
		tstring str = pAttr->GetValue ();
		if ( 0 == str.compare ( _T ( "CLC_MAINTAIN" ) ) ) { clcSt = CLC_MAINTAIN; }
		else if ( 0 == str.compare ( _T ( "CLC_SUBSTITUDE" ) ) ) { clcSt = CLC_SUBSTITUDE; }
		else if ( 0 == str.compare ( _T ( "CLC_ADD" ) ) ) { clcSt = CLC_ADD; }
#endif // 0
		return clcSt;
	}

	//(internal) �A�g���r���[�g�|�C���^����Value��ACTION_POSTURE�ɒ����ĕԂ�
	ACTION_POSTURE LoadCharaUtl::_AttrToACTION_POSTURE ( const P_Attribute pAttr )
	{
		ACTION_POSTURE ap = (ACTION_POSTURE)_AttrToInt ( pAttr );
#if 0
		tstring str = pAttr->GetValue ();
		if ( 0 == str.compare ( _T ( "AP_STAND" ) ) ) { ap = AP_STAND; }
		else if ( 0 == str.compare ( _T ( "AP_CROUCH" ) ) ) { ap = AP_CROUCH; }
		else if ( 0 == str.compare ( _T ( "AP_JUMP" ) ) ) { ap = AP_JUMP; }
#endif // 0
		return ap;
	}


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
	//�����F�G�������g�|�C���^, �X�N���v�g�|�C���^, �g��ݒ肷��Script���̊֐��|�C���^
	//�ݒ�p�֐���std::function�Ŏw��
	void LoadCharaUtl::_LoadRect ( const P_Element pElemRect, P_Script pScript, FP_SetRect fp_SetRect )
	{
		//�A�g���r���[�g�̓T�C�Y�̂�
		const PVP_Attribute pvpAttrVecRect = pElemRect->GetpvpAttribute ();
		UINT sizeRect = _AttrToUINT ( (*pvpAttrVecRect)[0] );

		//�G�������g
		const PVP_Element pvpElemRect = pElemRect->GetpvpElement ();

		//�g
		for ( UINT i = 0; i < sizeRect; ++i )
		{
			//�G�������g
			P_Element pElem = (*pvpElemRect)[i];

			//�A�g���r���[�g
			const PVP_Attribute pa = pElem->GetpvpAttribute();
			RECT rect = _AttrToRect ( (*pa)[0], (*pa)[1], (*pa)[2], (*pa)[3] );
			
			//FP_SetRect��pScript�Ɗ֘A�t���Ă���̂ł��̂܂܌Ăяo��
			fp_SetRect ( rect );
		}
	}

	//�����F�G�������g�|�C���^, �g��ݒ肷��Script���̊֐��|�C���^
	void LoadCharaUtl::_LoadRect ( const P_Element pElemRect, FP_SetRect fp_SetRect )
	{
		const PVP_Element pvpElemRect = pElemRect->GetpvpElement ();
		for ( P_Element pElem : * pvpElemRect )
		{
			const PVP_Attribute pa = pElem->GetpvpAttribute();
			RECT rect = _AttrToRect ( pa->at(0), pa->at(1), pa->at(2), pa->at(3) );
			fp_SetRect ( rect );	//FP_SetRect��pScript�Ɗ֘A�t���Ă���̂ł��̂܂܌Ăяo��
		}
	}

	void LoadCharaUtl::_LoadRectAll ( const PVP_Element pvpElem, const P_Script & pScript )
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
		FP_SetRect func_a = [ pScript ] ( RECT r ) { pScript->AddARect ( r ); };
		FP_SetRect func_c = [ pScript ] ( RECT r ) { pScript->AddCRect ( r ); };
		FP_SetRect func_h = [ pScript ] ( RECT r ) { pScript->AddHRect ( r ); };
		FP_SetRect func_o = [ pScript ] ( RECT r ) { pScript->AddORect ( r ); };

		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_CRECT ), pScript, func_c );
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_ARECT ), pScript, func_a );
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_HRECT ), pScript, func_h );
		_LoadRect ( pvpElem->at ( ELEM_SCRIPT_ORECT ), pScript, func_o );
	}

	//�u�����` (�A�N�V�����ƃR�}���h�̓Ǎ���Aindex��������I�u�W�F�N�g�̃|�C���^���擾���Đݒ肷��)
	void LoadCharaUtl::_LoadBranch ( Chara & chara )
	{
		PVP_Action pvpAction = chara.GetpvpAction ();
		for ( P_Action pAc : * pvpAction )
		{
			PVP_Script pvpScript = pAc->GetpvpScript ();
			for ( P_Script pSc : * pvpScript )
			{
				PVP_Branch pvpBranch = pSc->GetpvpBranch ();
				for ( P_Branch pBr : * pvpBranch )
				{
					pBr->SetpSequence ( chara.GetpAction ( pBr->GetIndexAction () ) );
					pBr->SetpCommand ( chara.GetpCommand ( pBr->GetIndexCommand () ) );
				}
			}
		}
	}

	//��{��ԃA�N�V����ID
	void LoadCharaUtl::_ElemToBasicActionID ( const P_Element pElem, Chara & chara )
	{
		//��{��ԃA�N�V����ID (name�͔�΂�)
		const PVP_Element pvpElemBasicAction = pElem->GetpvpElement ();
//		P_Element pElemBasicAction = pvpElemBasicAction->at ( 0 );
		for ( UINT i = 0; i < BASIC_ACTION_NUM; ++ i )
		{
			UINT n = _ElemToUINT ( pvpElemBasicAction->at ( i ), 0 );
			chara.SetBsAction ( static_cast < BASIC_ACTION > ( i ), n );
		}
	}

	//------------------------------------------------------------
	//�C���[�W�A�[�J�C�u�Ǎ�
	void LoadCharaUtl::_LoadImage ( ifstream* pIfstrm, PVP_TxBs pvpTexture, UINT numImage )
	{
		//�C���[�W�̌��Ń��[�v
		for ( UINT i = 0; i < numImage; ++ i )
		{
			//�C���[�W�̌ʃT�C�Y��Ǎ�
			UINT imageSize = 0;
			pIfstrm->read ( (char*)&imageSize, sizeof ( UINT ) );

			//�ꎞ�̈�̊m�ۂ���A�C���[�W�{�̂̓Ǎ�
			char* imageBuf = new char [ imageSize ];
			pIfstrm->read ( imageBuf, imageSize );

			//��������̃f�[�^����Q�[���e�N�X�`���ɕϊ�
			P_TxMem pGameTexture = make_shared < TxMem > ( (LPCVOID)imageBuf, imageSize );

			//�ꎞ�̈�͉������
			delete[] imageBuf;

			//�L���������̃e�N�X�`�����X�g�ɉ�����
			pvpTexture->push_back ( pGameTexture );
		}
	}


}	//namespace GAME

