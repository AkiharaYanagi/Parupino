//=================================================================================================
//
//	Chara �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Chara.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Chara::Chara ()
		: m_bsAction ()
	{
		Make ();
	}

	Chara::~Chara ()
	{
	}

	void Chara::Make ()
	{
		m_pvpTxMain = make_shared < VP_TxBs > ();
		m_pvpAction = make_shared < VP_Action > ();
		m_pvpTxEf = make_shared < VP_TxBs > ();
		m_pvpEf = make_shared < VP_Effect > ();
	}

	void Chara::Rele ()
	{
		for ( auto p : * m_pvpTxMain ) { p->Rele (); } m_pvpTxMain->clear (); m_pvpTxMain.reset ();
		for ( auto p : * m_pvpAction ) { p->Rele (); } m_pvpAction->clear (); m_pvpAction.reset ();
		for ( auto p : * m_pvpTxEf ) { p->Rele (); } m_pvpTxEf->clear (); m_pvpTxEf.reset ();
		for ( auto p : * m_pvpEf ) { p->Rele (); } m_pvpEf->clear (); m_pvpEf.reset ();
	}

	void Chara::Reset ()
	{
		Rele ();
		Make ();
	}

	void Chara::Clear ()
	{
//		m_vpCommand.clear ();
//		m_vpBranch.clear ();
//		m_vpRoute.clear ();
		//�萔�̂�
		//�ēǍ�����Chara����
	}

	UINT Chara::GetActionID ( tstring name ) const
	{
		UINT index = 0;
		for ( auto p : *m_pvpAction )
		{
			tstring actionName = p->GetName (); 
			if ( 0 == name.compare ( actionName ) )
			{
				return index;
			}
			++index;
		}
		return 0;
	}

}	//namespace GAME

