//=================================================================================================
//
//	Script �w�b�_�t�@�C��
//		���t���[���ɏ�������l
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define.h"
#include "DxDefine.h"
#include "Rect.h"

#include "Chara_Const.h"
#include "Route.h"
#include "EffectGenerate.h"
#include "ScriptParam_Battle.h"
#include "ScriptParam_Staging.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================================
	//	���X�N���v�g		�L�����ɂ�����A�N�V�����̂P�t���[���̒l
	//		���t���[����
	//		���C���[�WID
	//		���摜�\���ʒu
	//		���v�Z���(����/���/���Z)
	//		��[]���[�g
	//		��[]�ڐG�g
	//		��[]�U���g
	//		��[]����g
	//		��[]���E�g
	//		��[]�G�t�F�N�g����
	//
	//================================================================

	//�N���X
	class Script
	{
		UINT	m_frame;		//���g�̊Y���t���[����
		UINT	m_imageIndex;	//�C���[�WID

		VEC2	m_pos;			//�摜�\���ʒu
//		CLC_ST	m_CalcState;	//�v�Z���

		PV_RECT	m_pvCRect;		//�ڐG�g���X�g
		PV_RECT	m_pvARect;		//�U���g���X�g
		PV_RECT	m_pvHRect;		//����g���X�g
		PV_RECT	m_pvORect;		//���E�g���X�g

		V_UINT		m_vRouteID;		//���[�g���X�g
		PVP_EfGnrt	m_pvpEfGnrt;	//Ef�W�F�l���[�g���X�g

	public:
		Script ();
		Script ( const Script & rhs ) = delete;
		~Script ();

		void Make ();
		void Rele ();

		//�Y���t���[����
		void SetFrame ( UINT frame ) { m_frame = frame; }
		UINT GetFrame () const { return m_frame; }

		//�C���[�WID
		void SetImageIndex ( UINT index ) { m_imageIndex = index; }
		UINT GetImageIndex () const { return m_imageIndex; }

		//�摜�\���ʒu
		void SetPos ( VEC2 pos ) { m_pos = pos; }
		VEC2 GetPos () const { return m_pos; }

#if 0
		//���x
		void SetVel ( VEC2 vel ) { m_vel = vel; }
		VEC2 GetVel () const { return m_vel; }

		//�����x
		void SetAcc ( VEC2 acc ) { m_acc = acc; }
		VEC2 GetAcc () const { return m_acc; }

		//�v�Z���
		void SetCalcState ( CLC_ST clcSt ) { m_CalcState = clcSt; }
		CLC_ST GetCalcState () const { return m_CalcState; }
#endif // 0

		//���[�g
		void AddRouteID ( UINT i ) { m_vRouteID.push_back ( i ); }
		void SetRouteID ( unique_ptr < UINT[] > up_aryUint, UINT size );
		const V_UINT & GetcvRouteID () const { return m_vRouteID; }
		V_UINT & GetvRouteID () { return m_vRouteID; }

		//EfGnrt���X�g
		PVP_EfGnrt GetpvpEfGnrt () const { return m_pvpEfGnrt; }

		//EfGnrt���X�g�ɒǉ�
		void AddpEfGnrt ( P_EfGnrt pEfGnrt ) { m_pvpEfGnrt->push_back ( pEfGnrt ); }

		//�ڐG�g, �U���g, ����g, ���E�g
		PV_RECT GetpvCRect () const { return m_pvCRect; }
		PV_RECT GetpvARect () const { return m_pvARect; }
		PV_RECT GetpvHRect () const { return m_pvHRect; }
		PV_RECT GetpvORect () const { return m_pvORect; }
		void AddCRect ( RECT crect ) { m_pvCRect->push_back ( crect ); }
		void AddARect ( RECT arect ) { m_pvARect->push_back ( arect ); }
		void AddHRect ( RECT hrect ) { m_pvHRect->push_back ( hrect ); }
		void AddORect ( RECT orect ) { m_pvORect->push_back ( orect ); }

		//�l
		ScriptParam_Battle		m_prmBattle;	//�퓬�p�����[�^
		ScriptParam_Staging		m_prmStaging;	//���o�p�����[�^
	};


	using P_Script = std::shared_ptr < Script >;
	using VP_Script = std::vector < P_Script >;
	using PVP_Script = std::shared_ptr < VP_Script >;


}	//namespace GAME


