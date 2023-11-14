//=================================================================================================
//
// �L�������N�g�@�w�b�_�t�@�C��
//		�L�����ɂ�����g���ė�����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../FtgMain/FtgConst.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//�N���X
	class CharaRect
	{
		//�����g(�X�N���v�g����L�����ʒu�������Z�����l)
		PV_RECT		m_pvCRect;	//�ڐG�g
		PV_RECT		m_pvARect;	//�U���g
		PV_RECT		m_pvHRect;	//����g
		PV_RECT		m_pvORect;	//���E�g

	public:
		CharaRect ();
		CharaRect ( const CharaRect & rhs ) = delete;
		~CharaRect ();

		//�g�ݒ�
		void ResetAllRect ();				//�S�����g�̃��Z�b�g

		void ResetCRect () { ZeroVecRect ( m_pvCRect ); }
		void ResetARect () { ZeroVecRect ( m_pvARect ); }
		void ResetHRect () { ZeroVecRect ( m_pvHRect ); }
		void ResetORect () { ZeroVecRect ( m_pvORect ); }

		//�g�z��擾 ( size == ExeChara::CONST_CHARA::NUM_RECT )
		PV_RECT GetpvCRect () { return m_pvCRect; }
		PV_RECT GetpvARect () { return m_pvARect; }
		PV_RECT GetpvHRect () { return m_pvHRect; }
		PV_RECT GetpvORect () { return m_pvORect; }

		//�X�N���v�g��������g�֐ݒu
		void SetpvRect ( PV_RECT pvRectActual, PV_RECT pvRectScript, bool dir, VEC2 pos );
		void SetCRect ( PV_RECT crect, bool dir, VEC2 pos );
		void SetARect ( PV_RECT arect, bool dir, VEC2 pos );
		void SetHRect ( PV_RECT hrect, bool dir, VEC2 pos );
		void SetORect ( PV_RECT orect, bool dir, VEC2 pos );

#if 0
		//�����g����\���g�֐ݒu
		void SetGrpRect ( PrmRect grpRect [], RECT rect [], float dispGameBaseX );
#endif // 0
		
	};

	using P_CharaRect = std::shared_ptr < CharaRect >;


}	//namespace GAME


