//=================================================================================================
//
// LoadCharaUtl �w�b�_�t�@�C��
//	LoadChara�ŗp����Utility�֐��Q
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "IOCharaDefine.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class LoadCharaUtl
	{
		//------------------------------------------------------------
		//�G�������g�|�C���^����index�Ԗڂ̃A�g���r���[�g��Value��UINT�ɒ����ĕԂ�
		UINT _ElemToUINT ( const P_Element pElem, UINT indexAttr );

		//�G�������g�|�C���^����A�N�V������ǂݍ���
		void _ElemToActionArray ( const P_Element pElem, Chara & chara );	//�z��
		void _ElemToAction ( const P_Element pElem, const P_Action & pAction );

		//�G�������g�|�C���^����X�N���v�g��ǂݍ���
		void _ElemToScript ( const P_Element pElem, const P_Script pScript, UINT frame );

		//�G�������g�|�C���^����R�}���h��ǂݍ���
		void _ElemToCommandArray ( const P_Element pElem, Chara & chara );	//�z��
		void _ElemToCommand ( const P_Element pElem, const P_Command & pCommand );

		//�G�������g�|�C���^����Q�[���L�[�R�}���h��ǂݍ���
		void _ElemToGameKeyCmd ( const P_Element pElem, _GameKeyCommand & gameKeyCmd );
		_GameKeyCommand::GAME_KEY_STATE StrToKeyState ( tstring str );

		//��{��ԃA�N�V����ID
		void _ElemToBasicActionID ( const P_Element pElem, Chara & chara );

		//�G�������g�|�C���^����G�t�F�N�g��ǂݍ���
		void _ElemToEffectArray ( const P_Element pElem, Chara & chara );	//�z��
		void _ElemToEffect ( const P_Element pElem, const P_Effect & pEffect );


		//�G�������g�|�C���^����u�����`��ǂݍ���
		void _ElemToBranchArray ( const P_Element pElem, const P_Script & pScript );	//�z��
		void _ElemToBranch ( const P_Element pElem, const P_Branch & pBranch );

		//�G�������g�|�C���^����EF�W�F�l���[�g��ǂݍ���
		void _ElemToEfGnrtArray ( const P_Element pElem, const P_Script & pScript );	//�z��
		void _ElemToEfGnrt ( const P_Element pElem, const P_EfGnrt & pEfGnrt );

		//------------------------------------------------------------
		//�A�g���r���[�g�ϊ�
		bool _AttrToBool ( const P_Attribute pAttr );
		UINT _AttrToUINT ( const P_Attribute pAttr );
		int  _AttrToInt ( const P_Attribute pAttr );
		float  _AttrToFloat ( const P_Attribute pAttr );
		VEC2 _AttrToVec2 ( const P_Attribute pa0, const P_Attribute pa1 );
		RECT _AttrToRect
		( 
			const P_Attribute pa0, const P_Attribute pa1,  
			const P_Attribute pa2, const P_Attribute pa3  
		);
		CLC_ST _AttrToCLC_ST ( const P_Attribute pAttr );
		ACTION_POSTURE _AttrToACTION_POSTURE ( const P_Attribute pAttr );

		//------------------------------------------------------------
		//�g�Ǎ�
#if 0
		//�����F�G�������g�|�C���^, �X�N���v�g�|�C���^, �g��ݒ肷��Script���̊֐��|�C���^
		void _LoadRect ( const P_Element pElem, P_Script pScript, void(Script::* const pFuncAddRect)( RECT ) );
#endif // 0
		//�֐��^���`
		//	�N���XScript�ɂ�����Rect��ݒ肷��֐��F�ߒlvoid, ����RECT
		using FP_SetRect = std::function < void ( RECT ) >;

		//�����F�G�������g�|�C���^, �X�N���v�g�|�C���^, �g��ݒ肷��Script���̊֐��|�C���^
		void _LoadRect ( const P_Element pElem, P_Script pSrcipt, FP_SetRect fp_SetRect );
		//�����F�G�������g�|�C���^, �g��ݒ肷��Script���̊֐��|�C���^
		void _LoadRect ( const P_Element pElem, FP_SetRect fp_SetRect );

		//�g�̓Ǎ�
		void _LoadRectAll ( const PVP_Element pvpElem, const P_Script & pScript );

		//------------------------------------------------------------
		//�u�����` (�A�N�V�����ƃR�}���h�̓Ǎ���Aindex��������I�u�W�F�N�g�̃|�C���^���擾���Đݒ肷��)
		void _LoadBranch ( Chara & chara );

		//----------------------------------
		//�f�[�^�Ǎ��@�ꎞ�ϐ�
		UINT	m_nMainImage;		//���C���C���[�W���X�g�̌�
		UINT	m_nEfImage;		//Ef�C���[�W���X�g�̌�

		//�C���[�W�A�[�J�C�u�Ǎ�
		void _LoadImage ( ifstream* pIfstrm, PVP_TxBs pvpTexture, UINT numImage );

		//�R�}���h������

	public:
		LoadCharaUtl () = default;
		LoadCharaUtl ( const LoadCharaUtl & rhs ) = delete;
		~LoadCharaUtl () = default;

		//Document����L�����ɕϊ�����
		void _DocumentToChara ( const Document & document, Chara & chara );
	};


}	//namespace GAME


