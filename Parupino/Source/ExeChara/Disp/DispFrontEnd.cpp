//=================================================================================================
//
// DispFrontEnd �\�[�X�t�@�C��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DispFrontEnd.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DispFrontEnd::DispFrontEnd ()
	{
		//�Q�[�W��

		//���C�t�Q�[�W
		m_gaugeLife.SetPosition ( LIFE_GAUGE_X, LIFE_GAUGE_Y, LIFE_GAUGE_W, LIFE_GAUGE_H );
		const _CLR c0L = LIFE_GAUGE_VALUE_CLR0;
		const _CLR c1L = LIFE_GAUGE_VALUE_CLR1;
		const _CLR c2L = LIFE_GAUGE_VALUE_CLR2;
		const _CLR c3L = LIFE_GAUGE_VALUE_CLR3;
		m_gaugeLife.SetColor_Value ( c0L, c1L, c2L, c3L );
		m_gaugeLife.SetColor_Frame ( LIFE_GAUGE_FRAME_CLR );
		m_gaugeLife.SetColor_Decrease ( LIFE_GAUGE_DECREASE_CLR );

		//�o�����X�Q�[�W
		m_gaugeBalance.SetPosition ( BALANCE_GAUGE_X, BALANCE_GAUGE_Y, BALANCE_GAUGE_W, BALANCE_GAUGE_H );
		const _CLR c0B = BALANCE_GAUGE_VALUE_CLR0;
		const _CLR c1B = BALANCE_GAUGE_VALUE_CLR1;
		const _CLR c2B = BALANCE_GAUGE_VALUE_CLR2;
		const _CLR c3B = BALANCE_GAUGE_VALUE_CLR3;
		m_gaugeBalance.SetColor_Value ( c0B, c1B, c2B, c3B );
		m_gaugeBalance.SetColor_Frame ( BALANCE_GAUGE_FRAME_CLR );
		m_gaugeBalance.SetColor_Decrease ( BALANCE_GAUGE_DECREASE_CLR );
		m_gaugeBalance.OffDecrease ();

		//�}�i�Q�[�W
		m_gaugeMana.SetPosition ( MANA_GAUGE_X, MANA_GAUGE_Y, MANA_GAUGE_W, MANA_GAUGE_H );
		const _CLR c0M = MANA_GAUGE_VALUE_CLR0;
		const _CLR c1M = MANA_GAUGE_VALUE_CLR1;
		const _CLR c2M = MANA_GAUGE_VALUE_CLR2;
		const _CLR c3M = MANA_GAUGE_VALUE_CLR3;
		m_gaugeMana.SetColor_Value ( c0M, c1M, c2M, c3M );
		m_gaugeMana.SetColor_Frame ( BALANCE_GAUGE_FRAME_CLR );
		m_gaugeMana.SetColor_Decrease ( BALANCE_GAUGE_DECREASE_CLR );
		m_gaugeMana.OffDecrease ();


#if 0
		//�v���C���[�\��
		m_grpPlayer1P.AddTexture ( _T ( "Player_1P.png" ) );
		m_grpPlayer1P.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayer1P );
		m_grpPlayer2P.AddTexture ( _T ( "Player_2P.png" ) );
		m_grpPlayer2P.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayer2P );
		m_grpPlayerCOM.AddTexture ( _T ( "Player_COM.png" ) );
		m_grpPlayerCOM.GetpMatrix ()->SetValid ( false );
		m_pGrpAry->InsertTask ( & m_grpPlayerCOM );

		//�q�b�g�X�g�b�v���ԕ\��
		m_gaugeHitStop.SetAllColor ( _CLR ( 0xffa0a0ff ) );
		m_pGrpAry->InsertTask ( & m_gaugeHitStop );

		//�̂����莞�ԕ\��
		m_gaugeLurch.SetAllColor ( _CLR ( 0xffa0ffa0 ) );
		m_pGrpAry->InsertTask ( & m_gaugeLurch );

		//�G�t�F�N�g
		m_grpHitEf.AddTexture ( _T ( "efHit.png" ) );
		m_pGrpAry->InsertTask ( & m_grpHitEf );

		m_grpAvoidEf.AddTexture ( _T ( "efAvoid.png" ) );
		m_pGrpAry->InsertTask ( & m_grpAvoidEf );

		m_grpPoisedEf.AddTexture ( _T ( "poised0.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised1.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised2.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised3.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised4.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised5.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised6.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised7.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised8.png" ) );
		m_grpPoisedEf.AddTexture ( _T ( "poised9.png" ) );
		AddTask ( & m_grpPoisedEf );
#endif	//0
	}

	DispFrontEnd::~DispFrontEnd ()
	{
	}

	void DispFrontEnd::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;
		
		m_gaugeLife.LoadPlayer ( playerID );
		m_gaugeBalance.LoadPlayer ( playerID );
		m_gaugeMana.LoadPlayer ( playerID );

#if 0
		//�q�b�g�X�g�b�v���ԕ\��
		m_gaugeHitStop.SetRect ( 0, 0, 0, 0 );

		//�̂����莞�ԕ\��
		m_gaugeLurch.SetRect ( 0, 0, 0, 0 );

		//�g������
		InitRect ();
#endif // 0
	}

	void DispFrontEnd::Init ()
	{
		m_gaugeLife.Init ();
		m_gaugeBalance.Init ();
		m_gaugeMana.Init ();
	}

	void DispFrontEnd::UpdateGauge ( BtlParam btlPrm )
	{
		m_gaugeLife.Update ( btlPrm.GetLife () );
		m_gaugeBalance.Update ( btlPrm.GetBalance () );
		m_gaugeMana.Update ( btlPrm.GetMana () );


		//�d�����ԕ\��
#if 0
		static bool b2 = true;
		if ( ::GetAsyncKeyState ( '2' ) & 0x0001 ) { b2 ^= 1; }
		if ( b2 )
		{
			//�q�b�g�X�g�b�v����
			m_dispChara.UpdateHitStop ( m_ptChara, m_dirRight, m_hitstop, m_hitstopTimer );

			//�̂����莞��
			m_dispChara.UpdateLurch ( m_ptChara, m_dirRight, m_lurch, m_lurchTimer );
		}
#endif // 0

	}

#if 0
	void DispChara::UpdateHitStop ( VEC2 ptChara, bool dirRight, UINT hitstop, UINT hitstopTimer )
	{
		//�̂�����t���[�����ԕ\��
		float fLurch = 10 * ( (float)hitstop - hitstopTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeHitStop.SetRect ( ( *m_pDispGameBase ).x + ptChara.x - ( dirRight ? 10 + 64 + 10 : 0 - 64 - 10 ), ptChara.y - fLurch, 10.f, fLurch );
	}

	void DispChara::UpdateLurch ( VEC2 ptChara, bool dirRight, UINT lurch, UINT lurchTimer )
	{
		//�̂�����t���[�����ԕ\��
		float fLurch = 10 * ( (float)lurch - lurchTimer );
		float x = ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 );
		float y = ptChara.y - fLurch;
		float w = 10.f;
		float h = fLurch;
		m_gaugeLurch.SetRect ( ( *m_pDispGameBase ).x + ptChara.x - ( dirRight ? 10 + 64 : 0 - 64 ), ptChara.y - fLurch, 10.f, fLurch );
	}
#endif	//0

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
		float dir = dirRight ? 1.f : -1.f;
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
		float dir = dirRight ? 1.f : -1.f;
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
		float dir = dirRight ? 1.f : -1.f;
		m_grpPoisedEf.SetStartScaling ( VEC2 ( dir * 1.f, 1.f ) );
		m_grpPoisedEf.SetTargetScaling ( VEC2 ( dir * 1.5f, 1.5f ) );
		m_grpPoisedEf.SetAcc ( VEC2 ( dir * 0.005f, 0.005f ) );
		m_grpPoisedEf.On ();
	}


#endif // 0


}	//namespace GAME

