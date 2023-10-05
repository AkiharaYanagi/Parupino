//=================================================================================================
//
// OperateEffect �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "OperateEffect.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�R���X�g���N�^
	OperateEffect::OperateEffect ()
	{
		m_plpExeEffect = make_shared < LP_ExEf > ();
	}

	//�f�X�g���N�^
	OperateEffect::~OperateEffect ()
	{
		Rele ();
	}

	//���
	void OperateEffect::Rele ()
	{
		m_plpExeEffect->clear();
	}

	void OperateEffect::SetpChara ( P_Chara p )
	{
		m_pChara = p;
		m_pvpEfTexture = p->GetpvpEfTexture ();
		m_vpBranch = p->GetvpBranch ();
		m_vpRoute = p->GetvpRoute ();
	}

	//�G�t�F�N�g���X�g�ɐV�K�ǉ�
	void OperateEffect::AddListEffect ( P_Effect pEffect, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight )
	{
		P_ExEf pExeEffect = make_shared < ExeEffect > ( pEffect, m_pChara, pEfGnrt, ptChara, dirRight );
		m_plpExeEffect->push_back ( pExeEffect );
		AddpTask ( pExeEffect );	//�^�X�N���X�g
	}

	//�I�u�W�F�N�g����ExeEf���擾
	P_ExEf OperateEffect::GetpExEf ( P_Effect p ) const
	{
		//�G�t�F�N�g���s���X�g���猟��
		for ( P_ExEf pExEf : (* m_plpExeEffect) )
		{
			if ( pExEf->Compare ( p ) ) { return pExEf; }
		}
		return nullptr;
	}

	//�X�N���v�g�O����
	void OperateEffect::PreScriptMove ()
	{
		//����
		for ( auto p : (*m_plpExeEffect) ) { p->PreScriptMove (); }
	}


	//�X�N���v�g�㏈��
	void OperateEffect::PostScriptMove ( VEC2 ptChara, bool dirRight )
	{
		//list
		for ( auto p : (*m_plpExeEffect) )
		{
			p->PostScriptMove ( ptChara, dirRight );
		}

		//�I������
		LP_ExEf::iterator it = begin ( * m_plpExeEffect );
		while ( it != end ( * m_plpExeEffect ) )
		{
			//�������A��u�C���N�������g�̓R�s�[��n���C�e���[�^���󂳂Ȃ�
			if ( (*it)->IsEnd () ) 
			{ 
				EraseTask ( *it );	//�^�X�N���X�g
				(*it).reset (); 
				m_plpExeEffect->erase ( it ++ ); 
			}
			else { ++ it; }
		}
	}

	//�X�N���v�g����
	void OperateEffect::SynchroScript ( VEC2 ptChara )
	{
		//list
		for ( P_ExEf p : (*m_plpExeEffect) )
		{
			p->SynchroScript ( ptChara );
		}
	}

	//�g�\���ؑ�
	void OperateEffect::OnDispRect ()
	{
		for ( auto p : (*m_plpExeEffect) ) { p->OnDispRect (); }
	}

	void OperateEffect::OffDispRect ()
	{
		for ( auto p : (*m_plpExeEffect) ) { p->OffDispRect (); }
	}



}	//namespace GAME

