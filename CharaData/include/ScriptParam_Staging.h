//=================================================================================================
//
//	ScriptParam_Staging �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define.h"
#include "DxDefine.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	struct ScriptParam_Staging
	{
	public:
		//���o(�S��)
		UINT	BlackOut;		//�Ó][F]
		UINT	Vibration;		//�U��[F](�S��)
		UINT	Stop;			//��~[F](�S��)

		//------
		//���o(��)
		int		Rotate;				//��][rad]
		VEC2	Rotate_center;		//��]���S(x,y)
		UINT	AfterImage_N;		//�c��[��]
		UINT	AfterImage_time;	//�c��[F] ����
		UINT	AfterImage_pitch;	//�c��[F] pitch
		UINT	Vibration_S;		//�U��[F](��)
		_CLR	Color;				//�F���ύX
		UINT	Color_time;			//�F���ύX[F] ����

		ScriptParam_Staging ();
		ScriptParam_Staging ( const ScriptParam_Staging & rhs ) = delete;
		~ScriptParam_Staging ();




		//---------------------------------------------------------
		//�Ó]
		UINT GetBlackOut () const { return BlackOut; }
		void SetBlackOut ( UINT blackout ) { BlackOut = blackout; }

		//�U��
		UINT GetVibration () const { return Vibration; }
		void SetVibration ( UINT viberation ) { Vibration = viberation; }

		//��~
		UINT GetStop () const { return Stop; }
		void SetStop ( UINT stop ) { Stop = stop; }

		//---------------------------------------------------------
		//��]
		int GetRadian () const { return Rotate; }
		void SetStop ( int rad ) { Rotate = rad; }

		//�c��[F] pitch
		int GetAfterImage_pitch () const { return AfterImage_pitch; }
		void SetAfterImage_pitch ( int pitch ) { AfterImage_pitch = pitch; }

		//�c��[��]
		int GetAfterImage_N () const { return AfterImage_N; }
		void SetAfterImage_N ( int n ) { AfterImage_N = n; }

		//�c��[F] ����
		int GetAfterImage_time () const { return AfterImage_time; }
		void SetAfterImage_time ( int time ) { AfterImage_time = time; }

		//�U��[F](��)
		int GetVibration_S () const { return Vibration_S; }
		void SetVibration_S ( int time ) { Vibration_S = time; }

		//�F��
		_CLR GetColor () const { return Color; }
		void SetColor ( _CLR clr ) { Color = clr; }

		//�F���ύX[F] ����
		int GetColor_time () const { return Color_time; }
		void SetColor_time ( int time ) { Color_time = time; }
	};


}	//namespace GAME


