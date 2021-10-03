//=================================================================================================
//
// DispChara �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DispChara.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const UINT DispChara::NUM_DISP_INPUT = 20;


	DispChara::DispChara ()
		: m_timer ( 0 ), m_vel ( 1.f )
	{
		//���C���O���t�B�b�N
		m_mainGraphic = make_shared < GrpApTx > ();
		GRPLST_INSERT ( m_mainGraphic );

		//�e
		m_grpShadow = make_shared < GrpAcv > ();
		m_grpShadow->AddTexture ( _T("shadow.png") );
		m_grpShadow->SetZ ( Z_SHADOW );
		GRPLST_INSERT ( m_grpShadow );

		//�Q�[�W
		m_gaugeFrameLife = make_shared < PrmRect > ();
		m_gaugeFrameLife->SetAllColor ( _CLR ( 0xff404040 ) );
		GRPLST_INSERT ( m_gaugeFrameLife );

		m_gaugeDecreaseLife = make_shared < PrmRect > ();
		m_gaugeDecreaseLife->SetAllColor ( _CLR ( 0xffff9090 ) );
		GRPLST_INSERT ( m_gaugeDecreaseLife );

		m_gaugeLife = make_shared < PrmRect > ();
		m_gaugeLife->SetAllColor ( _CLR ( 0xffa0f0d0 ) );
		m_gaugeLife->SetColor ( 0, _CLR ( 0xffd0f040 ) );
		m_gaugeLife->SetColor ( 2, _CLR ( 0xfff0f040 ) );
		GRPLST_INSERT ( m_gaugeLife );



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

		//---------------------------------------------------------------


		//�g�\��(DispRect)�̓|�C���^�łȂ����̂�ێ�

#if 0
		//�G�t�F�N�g�O���t�B�b�N
#if 0
		m_efGraphic = make_shared < GrpApTx > ();
		GRPLST_INSERT ( m_efGraphic );
#endif // 0

		//�v���C���[�\��
		m_grpPlayer1P.AddTexture ( _T("Player_1P.png") );
		m_grpPlayer1P.GetpMatrix()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayer1P );
		m_grpPlayer2P.AddTexture ( _T("Player_2P.png") );
		m_grpPlayer2P.GetpMatrix()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayer2P );
		m_grpPlayerCOM.AddTexture ( _T("Player_COM.png") );
		m_grpPlayerCOM.GetpMatrix()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayerCOM );

		//�q�b�g�X�g�b�v���ԕ\��
		m_gaugeHitStop.SetAllColor ( _CLR ( 0xffa0a0ff ) );
		m_pGrpAry->InsertTask ( & m_gaugeHitStop );

		//�̂����莞�ԕ\��
		m_gaugeLurch.SetAllColor ( _CLR ( 0xffa0ffa0 ) );
		m_pGrpAry->InsertTask ( & m_gaugeLurch );

		//�G�t�F�N�g
		m_grpHitEf.AddTexture ( _T("efHit.png") );
		m_pGrpAry->InsertTask ( & m_grpHitEf );

		m_grpAvoidEf.AddTexture ( _T("efAvoid.png") );
		m_pGrpAry->InsertTask ( & m_grpAvoidEf );

		m_grpPoisedEf.AddTexture ( _T("poised0.png") );
		m_grpPoisedEf.AddTexture ( _T("poised1.png") );
		m_grpPoisedEf.AddTexture ( _T("poised2.png") );
		m_grpPoisedEf.AddTexture ( _T("poised3.png") );
		m_grpPoisedEf.AddTexture ( _T("poised4.png") );
		m_grpPoisedEf.AddTexture ( _T("poised5.png") );
		m_grpPoisedEf.AddTexture ( _T("poised6.png") );
		m_grpPoisedEf.AddTexture ( _T("poised7.png") );
		m_grpPoisedEf.AddTexture ( _T("poised8.png") );
		m_grpPoisedEf.AddTexture ( _T("poised9.png") );
		AddTask ( & m_grpPoisedEf );
#endif	//0
	}

	DispChara::~DispChara ()
	{
	}

	void DispChara::SetpChara ( const P_Chara pChara )
	{
		m_pChara = pChara;
		m_pvpMainTexture = pChara->GetpvpMainTexture ();
	}

	void DispChara::InitMainImage ( UINT indexTexture )
	{
		P_TxBs pTexture = m_pvpMainTexture->at ( indexTexture );
		m_mainGraphic->SetpTexture ( pTexture );
	}

	void DispChara::UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight )
	{
		//�ʒu
		VEC2 posScript = pScript->GetPos ();
		float fDir = dirRight ? (1.f) : (-1.f);		//����
		float bx = G_Ftg::inst()->GetPosMutualBase ().x;	//��ʒu
		float x = bx + ptChara.x + fDir * posScript.x;
		float y = 0	 + ptChara.y + 1.f * posScript.y; 
		VEC2 vecImg = VEC2 ( x, y );

		//�\���ɔ��f
		m_mainGraphic->SetPos ( vecImg );
		m_mainGraphic->SetScaling ( 1.f * fDir, 1.f );
		P_TxBs pTexture = m_pvpMainTexture->at ( pScript->GetImageIndex () );
		m_mainGraphic->SetpTexture ( pTexture );

		//�e
		VEC2 vecImgShadow = VEC2 ( bx, 0 ) + ptChara + VEC2 ( -128 + fDir * 12, 0 );
		vecImgShadow.y = -32.f + 1.f * PLAYER_BASE_Y;
		m_grpShadow->SetPos ( vecImgShadow );
	}

	void DispChara::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect.SetCharaRect ( pCharaRect );
	}


	void DispChara::InitDisp ( PLAYER_ID playerID )
	{ 
		float dispGameBaseX = G_BASE_POS ().x;

		//�����ʒu
		if ( PLAYER_ID_1 == playerID )
		{
#if 0
			if ( cpu )
			{
				m_grpPlayerCOM.GetpMatrix()->SetValid ( true );
				m_grpPlayerCOM.GetpMatrix()->SetPos ( VEC2 ( GRP_PLAYER1_X, GRP_PLAYER1_Y ) );
			}
			else
			{
				m_grpPlayer1P.GetpMatrix()->SetValid ( true );
				m_grpPlayer1P.GetpMatrix()->SetPos ( VEC2 ( GRP_PLAYER1_X, GRP_PLAYER1_Y ) );
			}
#endif // 0
			m_gaugeFrameLife->SetRect (		LIFE_GAUGE_X-2,	 LIFE_GAUGE_Y-2,		GAUGE_WIDTH+4, GAUGE_HEIGHT+4 );
			m_gaugeLife->SetRect (			LIFE_GAUGE_X,	 LIFE_GAUGE_Y,		GAUGE_WIDTH, GAUGE_HEIGHT );
			m_gaugeDecreaseLife->SetRect (	0, 0, 0, 0 );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
#if 0
			if ( cpu )
			{
				m_grpPlayerCOM.GetpMatrix()->SetValid ( true );
				m_grpPlayerCOM.GetpMatrix()->SetPos ( VEC2 ( GRP_PLAYER2_X, GRP_PLAYER2_Y ) );
			}
			else
			{
				m_grpPlayer2P.GetpMatrix()->SetValid ( true );
				m_grpPlayer2P.GetpMatrix()->SetPos ( VEC2 ( GRP_PLAYER2_X, GRP_PLAYER2_Y ) );
			}
#endif // 0
			m_gaugeFrameLife->SetRect (		WINDOW_WIDTH - GAUGE_WIDTH - LIFE_GAUGE_X-2,		LIFE_GAUGE_Y-2,	 GAUGE_WIDTH+4, GAUGE_HEIGHT+4 );
			m_gaugeLife->SetRect (			WINDOW_WIDTH - GAUGE_WIDTH - LIFE_GAUGE_X,		LIFE_GAUGE_Y,	 GAUGE_WIDTH, GAUGE_HEIGHT );
			m_gaugeDecreaseLife->SetRect (	0, 0, 0, 0 );
		}






#if 0
		//�q�b�g�X�g�b�v���ԕ\��
		m_gaugeHitStop.SetRect ( 0, 0, 0, 0 );

		//�̂����莞�ԕ\��
		m_gaugeLurch.SetRect ( 0, 0, 0, 0 );

		//�g������
		InitRect ();
#endif // 0
	}

#if	0
	//�I�y���[�g�G�t�F�N�g�̍X�V
	void DispChara::UpdateOperateEffect ( float dispGameBaseX, VEC2 ptChara, bool dirRight )
	{
		//�G�t�F�N�g�����`��
		//�G�t�F�N�g�񓯊��`��
	}


	//�X�N���v�g����`�悷��
	void DispChara::UpdateEffectImage
	(
		Script* pScript,
		float dispGameBaseX, VEC2 ptChara, bool dirRight 
	)
	{
		GameTextureBase* pEfTexture = (*m_pvpEfTexture) [ pScript->GetImageIndex() ];
		VEC2 ptScriptPos = pScript->GetPos ();
		VEC2 vecEfImg = VEC2 ( 0, 0 );

		//����
		float fDir = dirRight ? (1.f) : (-1.f);
		float x = dispGameBaseX + ptChara.x + fDir * ptScriptPos.x;
		float y = 0 + ptChara.y + ptScriptPos.y; 
		vecEfImg = VEC2 ( x, y );

		m_efGraphic.GetpMatrix()->SetPos ( vecEfImg );
		m_efGraphic.GetpMatrix()->SetScaling ( 1.f * fDir, 1.f );
		m_efGraphic.SetpTexture ( pEfTexture );

	}
#endif	//0

#if 0
	void DispChara::UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT hitstop, UINT hitstopTimer )
	{
		//�̂�����t���[�����ԕ\��
		float fLurch = 10 * ( (float)hitstop - hitstopTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeHitStop.SetRect ( (*m_pDispGameBase).x + ptChara.x - ( dirRight ? 10 + 64 + 10: 0 - 64 - 10 ), ptChara.y - fLurch, 10.f, fLurch );
	}

	void DispChara::UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer )
	{
		//�̂�����t���[�����ԕ\��
		float fLurch = 10 * ( (float)lurch - lurchTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeLurch.SetRect ( (*m_pDispGameBase).x + ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 ), ptChara.y - fLurch, 10.f, fLurch );
	}
#endif	//0

	//�Q�[�W�X�V
	void DispChara::UpdateGauge ( PLAYER_ID playerID, int life, int damage, int balance )
	{
		const static float cfl = 1.f * GAUGE_WIDTH / LIFE_MAX;		//1���C�t������̕\������
		float wl = cfl * life;
		float wd = cfl * damage;

		const float lx = LIFE_GAUGE_X + GAUGE_WIDTH;

		const float lx2p = WINDOW_WIDTH - LIFE_GAUGE_X - GAUGE_WIDTH;

		if ( wl < 0 ) { wl = 0; }

		if ( PLAYER_ID_1 == playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx - wl - wd, LIFE_GAUGE_Y, wd, GAUGE_HEIGHT );
			m_gaugeLife->SetRect (		lx - wl, LIFE_GAUGE_Y,		wl, GAUGE_HEIGHT );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gaugeDecreaseLife->SetRect ( lx2p + wl, LIFE_GAUGE_Y, wd, GAUGE_HEIGHT );
			m_gaugeLife->SetRect (		lx2p, LIFE_GAUGE_Y, wl, GAUGE_HEIGHT );
		}

	}


	void DispChara::UpdateInput ( P_CharaInput pCharaInput )
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
#if 0
		(*m_vpvpRect[0])[0]->SetValid ( IS_KEY ( P1_LEFT ) );
		(*m_vpvpRect[0])[1]->SetValid ( IS_KEY ( P1_UP ) );
		(*m_vpvpRect[0])[2]->SetValid ( IS_KEY ( P1_RIGHT ) );
		(*m_vpvpRect[0])[3]->SetValid ( IS_KEY ( P1_DOWN ) );
		(*m_vpvpRect[0])[4]->SetValid ( IS_KEY ( P1_BUTTON1 ) );
		(*m_vpvpRect[0])[5]->SetValid ( IS_KEY ( P1_BUTTON2 ) );
		(*m_vpvpRect[0])[6]->SetValid ( IS_KEY ( P1_BUTTON3 ) );
		(*m_vpvpRect[0])[7]->SetValid ( IS_KEY ( P1_BUTTON4 ) );

		(*m_vpvpRect[0])[0]->SetValid ( vKey[0].GetLvr ( _GameKey::LVR_4 ) );
		(*m_vpvpRect[0])[1]->SetValid ( vKey[0].GetLvr ( _GameKey::LVR_8 ) );
		(*m_vpvpRect[0])[2]->SetValid ( vKey[0].GetLvr ( _GameKey::LVR_6 ) );
		(*m_vpvpRect[0])[3]->SetValid ( vKey[0].GetLvr ( _GameKey::LVR_2 ) );
		(*m_vpvpRect[0])[4]->SetValid ( vKey[0].GetBtn ( _GameKey::BTN_0 ) );
		(*m_vpvpRect[0])[5]->SetValid ( vKey[0].GetBtn ( _GameKey::BTN_1 ) );
		(*m_vpvpRect[0])[6]->SetValid ( vKey[0].GetBtn ( _GameKey::BTN_2 ) );
		(*m_vpvpRect[0])[7]->SetValid ( vKey[0].GetBtn ( _GameKey::BTN_3 ) );
#endif // 0

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

	bool DispChara::GetBoolInput ( P_CharaInput pCharaInput, int n, int i )
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


#if 0

	//�q�b�g
	void DispChara::OnHit ( VEC2 ptChara, bool dirRight )
	{
		//�G�t�F�N�g�̐ݒ�
		m_grpHitEf.SetWait ( 15 );
		m_grpHitEf.SetFadeOut ( 15 );

		//�����ɂ��ʒu�̌v�Z
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( 0, -128 );
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara;
//		m_grpHitEf.GetpMatrix()->SetPos ( img_vec );
		m_grpHitEf.SetPos ( ptChara + VEC2 ( 0, -128 ) );

		//�����͖���X�V����
		float dir = dirRight ? 1.f: -1.f;
		m_grpHitEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpHitEf.SetTargetScaling ( VEC2 ( dir * 1.3f, 1.3f ) );
		m_grpHitEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpHitEf.On ();
	}

	//�A���H�C�h
	void DispChara::OnAvoid ( VEC2 ptChara, bool dirRight )
	{
		//�G�t�F�N�g�̐ݒ�
		m_grpAvoidEf.SetWait ( 15 );
		m_grpAvoidEf.SetFadeIn ( 15 );

		//�����ɂ��ʒu�̌v�Z
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( -128, -256 );
//		VEC2 img_vec = VEC2 ( dispGameBaseX, 0 ) + ptChara + VEC2 ( 0, -64 );
//		m_grpAvoidEf.GetpMatrix()->SetPos ( img_vec );
//		m_grpAvoidEf.SetPos ( img_vec );
		m_grpAvoidEf.SetPos ( ptChara + VEC2 ( 0, -64 ) );

		//�����͖���X�V����
		float dir = dirRight ? 1.f: -1.f;
		m_grpAvoidEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpAvoidEf.SetTargetScaling ( VEC2 ( dir * 1.3f, 1.3f ) );
		m_grpAvoidEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpAvoidEf.On ();
	}

	//�|�C�Y�h
	void DispChara::OnPoised ( VEC2 ptChara, bool dirRight )
	{
		//�G�t�F�N�g�̐ݒ�
		m_grpPoisedEf.SetWait ( 15 );
		m_grpPoisedEf.SetFadeIn ( 15 );

		//�ʒu�̌v�Z
		m_grpPoisedEf.SetPos ( ptChara + VEC2 ( 0, -96 ) );

		//�����͖���X�V����
		float dir = dirRight ? 1.f: -1.f;
		m_grpPoisedEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpPoisedEf.SetTargetScaling ( VEC2 ( dir * 1.5f, 1.5f ) );
		m_grpPoisedEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpPoisedEf.On ();
	}


#endif // 0


}	//namespace GAME

