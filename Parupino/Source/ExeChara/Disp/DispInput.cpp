//=================================================================================================
//
// DispInput �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DispInput.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const UINT DispInput::NUM_DISP_INPUT = 20;

	DispInput::DispInput ()
		: m_timer ( 0 ), m_vel ( 1.f )
	{
		//---------------------------------------------------------------
		//�L�[����
		//�w�i
		m_bg = make_shared < PrmRect > ();
		m_bg->SetRect ( 20, 200, 80, 10 * NUM_DISP_INPUT );
		m_bg->SetZ ( Z_SYS );
		m_bg->SetAllColor ( 0x8080c080 );
		GRPLST_INSERT ( m_bg );

		//��`�Ǘ� ( 8��� * 60[FPS] )
		//�c 60FPS
		for ( UINT n = 0; n < NUM_DISP_INPUT; ++ n )
		{
			PVP_PRMRECT pvpRect = make_shared < VP_PRMRECT > ();
			m_vpvpRect.push_back ( pvpRect );

			//�� 8���
			for ( UINT i = 0; i < INPUT_NUM; ++ i )
			{
				P_PrmRect pRect = make_shared < PrmRect > ();
				pvpRect->push_back ( pRect );
				pRect->SetRect ( 20.f + 20 * i, 10.f + 20 * n, 10.f, 10.f );
				pRect->SetZ ( Z_SYS - 0.01f );

				//�����l�����_��
				if ( 0 == rand () % 2 )
				{
					pRect->SetValid ( F );
				}

				GRPLST_INSERT ( pRect );
			}
		}
	}

	DispInput::~DispInput ()
	{
	}


	void DispInput::UpdateInput ( P_CharaInput pCharaInput )
	{
		//---------------------------------------------------------------
		//�L�[����
		++ m_timer;

		//1�}�X���ړ��������ɃV�t�g
		if ( 0 < m_timer )
		{
			bool b[INPUT_NUM] = { F };
			bool b_prev[INPUT_NUM] = { F };

			int n = 0;
			for ( PVP_PRMRECT pvpRect : m_vpvpRect )
			{
				int i = 0;
				for ( P_PrmRect pRect : (*pvpRect) )
				{
					b[i] = pRect->GetValid ();
					pRect->SetValid ( b_prev[i] );
					b_prev[i] = b[i];
					++ i;
				}
				++ n;
			}

			m_timer = 0;
		}

		//������
		V_GAME_KEY vKey = pCharaInput->GetvGameKey ();

		//�\���ʒu
		int n = 0;
		for ( PVP_PRMRECT pvpRect : m_vpvpRect )
		{
			int i = 0;
			for ( P_PrmRect pRect : (*pvpRect) )
			{
				(*m_vpvpRect[n])[i]->SetValid ( GetBoolInput ( pCharaInput, n, i ) );
				pRect->SetRect ( 20.f + 10 * i, 200.f + 10 * n + m_vel * m_timer, 10.f, 10.f );
				++ i;
			}
			++ n;
		}
		//---------------------------------------------------------------
	}

	//-------------------------------------
	//�������p
	bool DispInput::GetBoolInput ( P_CharaInput pCharaInput, int n, int i )
	{
		//������
		V_GAME_KEY vKey = pCharaInput->GetvGameKey ();

		bool ret = false;
		switch ( i )
		{
		case 0: ret = vKey[n].GetLvr ( _GameKey::LVR_4 ); break;
		case 1: ret = vKey[n].GetLvr ( _GameKey::LVR_8 ); break;
		case 2: ret = vKey[n].GetLvr ( _GameKey::LVR_6 ); break;
		case 3: ret = vKey[n].GetLvr ( _GameKey::LVR_2 ); break;
		case 4: ret = vKey[n].GetBtn ( _GameKey::BTN_0 ); break;
		case 5: ret = vKey[n].GetBtn ( _GameKey::BTN_1 ); break;
		case 6: ret = vKey[n].GetBtn ( _GameKey::BTN_2 ); break;
		case 7: ret = vKey[n].GetBtn ( _GameKey::BTN_3 ); break;
		default: break;
		}
		return ret;
	}


}	//namespace GAME

