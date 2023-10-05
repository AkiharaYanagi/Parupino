//=================================================================================================
//
// ExeEffect �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "ExeEffect.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//@Later	������Effect��EfGnrt�𓝍�
	//------------------------------------------

	ExeEffect::ExeEffect ( P_Effect pEffect, P_Chara pChara, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight )
	 :	  m_active ( true ), m_end ( false ), m_frame ( 0 )
		, m_ptEffect ( VEC2 ( 0, 0 ) ), m_dirRight ( dirRight )
		, m_vel ( VEC2 ( 0, 0 ) ), m_acc ( VEC2 ( 0, 0 ) )
		, m_pEffect ( pEffect ), m_pScript ( nullptr ) 
		, m_bDispRect ( true )
		, m_offset ( false ), m_hit ( false )
	{
		SetpEfGnrt ( pEfGnrt );
		m_pScript = m_pEffect->GetpScript ( 0 );

		m_pChara = pChara;
		m_vpBranch = pChara->GetvpBranch ();
		m_vpRoute = pChara->GetvpRoute ();

		//�����ʒu (�L�����ʒu+�G�t�F�N�g�����ʒu)
		m_ptEffect = ptChara + Dir ( m_ptGnrt );

		//�g
		m_charaRect = make_shared < CharaRect > ();

		//�\��
		m_dispEffect = make_shared < DispEffect > ( pChara->GetpvpEfTexture (), pEfGnrt->GetZ () );
		AddpTask ( m_dispEffect );
	}

	ExeEffect::~ExeEffect ()
	{
	}

	void ExeEffect::SetpEfGnrt ( P_EfGnrt p )
	{
		m_ptGnrt = p->GetPos ();
		m_gnrt = p->GetGnrt ();
		m_loop = p->GetLoop ();
		m_sync = p->GetSync ();
	}

	void ExeEffect::PreScriptMove ()
	{
		//�X�N���v�g���擾
		m_pScript = m_pEffect->GetpScript ( m_frame );


		//---------------------------------------------------------------------
		//�G�t�F�N�g�I������
		//��ʊO�̂Ƃ��I��
		if ( m_ptEffect.x < 0 - 100 || GAME_WIDTH + 100 < m_ptEffect.x )
		{
			m_end = true;
		}


		//�G�t�F�N�g�ڍ��p
		UINT sqcID = 0;

		//���݃G�t�F�N�g���ŏI�t���[���Ȃ��
		if ( m_pEffect->IsEndScript ( m_frame ) )
		{
			bool bBranch = false;

			//�X�N���v�g�����������

			//���[�g�̃`�F�b�N
			V_UINT vec_RouteID = m_pScript->GetcvRouteID ();
			for ( UINT indexRoute : vec_RouteID )
			{
				//�u�����`�̃`�F�b�N
				V_UINT vBranchID = m_vpRoute[indexRoute]->GetcvIDBranch ();
				for ( UINT indexBranch : vBranchID )
				{
					//�I�����ȊO�͔�΂�
					if ( BRC_END == m_vpBranch[indexBranch]->GetCondition () )
					{
						//���V�[�N�G���XID
						sqcID = m_vpBranch[indexBranch]->GetIndexSequence ();
						bBranch = true;
					}
				}
			}
			
			if ( bBranch )
			{
				//@todo �V�[�N�G���X(�G�t�F�N�g)���ŃG�t�F�N�g�̈ڍ�
				m_pEffect = m_pChara->GetpEffect ( sqcID );
				m_frame = 0;



			}
			else
			{
				if ( m_loop )
				{
					m_frame = 0;	//���[�v
				}
				else
				{
					m_end = true;	//�I��
				}

			}

		}
		else
		{
			++ m_frame;	//���s
		}
		//---------------------------------------------------------------------
	}

	void ExeEffect::PostScriptMove ( VEC2 ptChara, bool dirRight )
	{
		//�Q�[���ʒu�v�Z (�\���ʒu��Disp�Ōv�Z����)
		//@info Exe�ŃQ�[���ʒu���v�Z���ADisp�ŉ�ʈʒu�␳�����Z����

		//�����q�b�g��or���E��
		if ( m_hit || m_offset )
		{
			m_end = true;
			return;
		}

		//�G�t�F�N�g��ʒu
		if ( m_sync )		//�L���������t���O�ŕ���
		{
			//�G�t�F�N�g�ʒu = �L�����ʒu + �����ʒu
			m_ptEffect = ptChara + Dir ( m_ptGnrt );

			//����
			m_dirRight = dirRight;
		}

		//���x�v�Z
		m_ptEffect += Dir ( m_pScript->m_prmBattle.Vel );

//		DBGOUT_WND_F ( 0, _T ( "plpos = (%d,%d)" ), ptChara.x, ptChara.y );
//		DBGOUT_WND_F ( 1, _T ( "efpos = (%d,%d)" ), m_ptEffect.x, m_ptEffect.y );

		//�g�ݒ�
		m_charaRect->SetARect ( m_pScript->GetpvARect (), dirRight, m_ptEffect );

		//�\���X�V
		m_dispEffect->Update ( m_pScript, m_ptEffect, dirRight );

		//�g�\��
		if ( m_bDispRect )
		{
			m_dispEffect->OnRect ();
			m_dispEffect->SetpCharaRect ( m_charaRect );
		}
		else
		{
			m_dispEffect->OffRect ();
		}

	}

	void ExeEffect::SynchroScript ( VEC2 ptChara )
	{
		m_ptEffect = ptChara;
	}


}	//namespace GAME

