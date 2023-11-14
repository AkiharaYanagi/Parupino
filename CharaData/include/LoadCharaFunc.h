//=================================================================================================
//
// LoadCharaFunc �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once
#include <functional>

#include "IOCharaDefine.h"
#include "LoadCharaUtl.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//	LoadChara�ŗp����֐��Q
	//------------------------------------------------------------
	class LoadCharaFunc
	{
		//	�����g�p�֐�
		LoadCharaUtl	m_utl;

		//�֐��I�u�W�F�N�g�^���`
		//	P_Element����Chara�̒l��ǂݍ��ފ֐��F�ߒlvoid, ���� P_Element, Chara
		using FP_ElemToCharaParam = std::function < void ( const P_Element, Chara & ) > ;

		//�G�������g�����G�������g�z��Ɋe�Ǎ��֐������s����
		void ElemAry ( const P_Element pElem, Chara & ch, FP_ElemToCharaParam fp );

		//----------------------------------
		//�G�������g�|�C���^����C���[�W���X�g��ǂݍ���
		//�f�[�^�Ǎ��@�ꎞ�ϐ�
		UINT	m_nMainImage;		//���C���C���[�W���X�g�̌�
		UINT	m_nEfImage;		//Ef�C���[�W���X�g�̌�

		//�C���[�W��
		std::vector < tstring > m_vMainImageName;
		std::vector < tstring > m_vEfImageName;

		//------------------------------------------------------------
		//�A�N�V����
		V_STR	m_vActionName;
		void _ElemToActionC ( const P_Element pElem, Chara & ch );

		//�G�������g�|�C���^����G�t�F�N�g��ǂݍ���
		V_STR	m_vEffectName;
		void _ElemToEffect ( const P_Element pElem, Chara & ch );

		//�X�N���v�g
		void _ElemToScript ( const P_Element pElem, const P_Script pScript, UINT frame );

		//�R�}���h
		V_STR	m_vCommandName;
		void _ElemToCommand ( const P_Element pElem, Chara & ch );

		//�G�������g�|�C���^����Q�[���L�[�R�}���h��ǂݍ���
		void _ElemToGameKeyCmd ( const P_Element pElem, _GameKeyCommand & gameKeyCmd );
		_GameKeyCommand::GAME_KEY_STATE StrToKeyState ( tstring str );

		//�u�����`
		V_STR	m_vBranchName;
		void _ElemToBranch ( const P_Element pElem, Chara & ch );

		//���[�g
		V_STR	m_vRouteName;
		void _ElemToRoute ( const P_Element pElem, Chara & ch );

		//��{��ԃA�N�V����ID
		void _ElemToBasicActionID ( const P_Element pElem, Chara & ch );


		//------------------------------------------------------------
		//�g�Ǎ�
#if 0
		//�����F�G�������g�|�C���^, �X�N���v�g�|�C���^, �g��ݒ肷��Script���̊֐��|�C���^
		void _LoadRect ( const P_Element pElem, P_Script pScript, void(Script::* const pFuncAddRect)( RECT ) );
#endif // 0
		//�֐��^���`
		//	�N���XScript�ɂ�����Rect��ݒ肷��֐��F�ߒlvoid, ����RECT
		using FP_SetRect = std::function < void ( RECT ) >;

		//�����F�G�������g�|�C���^, �X�N���v�g�|�C���^, �g��ݒ肷��Script���̊֐��I�u�W�F�N�g
		void _LoadRect ( const P_Element pElem, P_Script pSrcipt, FP_SetRect fp_SetRect );
		//�����F�G�������g�|�C���^, �g��ݒ肷��Script���̊֐��I�u�W�F�N�g
		void _LoadRect ( const P_Element pElem, FP_SetRect fp_SetRect );

		//�g�̓Ǎ�
		void _LoadRectAll ( const PVP_Element pvpElem, const P_Script & pScript );

		//------------------------------------------------------------
		//�X�N���v�g���̃��[�g (�A�N�V�����ƃR�}���h�̓Ǎ���Aindex��������I�u�W�F�N�g�̃|�C���^���擾���Đݒ肷��)
		void _LoadRouteInScript ( Chara & ch );

		//�G�������g�|�C���^����EF�W�F�l���[�g��ǂݍ���
		void _ElemToEfGnrtArray ( const P_Element pElem, const P_Script & pScript );	//�z��
		void _ElemToEfGnrt ( const P_Element pElem, const P_EfGnrt & pEfGnrt );


	public:
		LoadCharaFunc () = default;
		LoadCharaFunc ( const LoadCharaFunc & rhs ) = delete;
		~LoadCharaFunc () = default;

		//Document����L�����ɕϊ�����
		void _DocumentToChara ( const Document & document, Chara & ch );

		//�C���[�W�A�[�J�C�u�Ǎ�
		void _LoadImage ( ifstream& pIfstrm, PVP_TxBs pvpTexture );
	};


}	//namespace GAME


