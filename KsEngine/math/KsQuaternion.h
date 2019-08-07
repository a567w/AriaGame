/************************************************************************************************/
/** 
 * @file		KsQuaternion.h
 * @brief		�N�H�[�^�j�I������
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSQUATERNION_H__
#define __KSQUATERNION_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

class KsMatrix4x4;
class KsVector3d;

/************************************************************************************************/
/**
 *	�N�H�[�^�j�I��
 *	@class	Quaternion
 *	@brief	
 *	@autor	Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsQuaternion
{
	public:
		/**
		 * �}�g���b�N�X�̗v�f����
		 */
		KsReal							x, y, z, w;

		/**
		 * �R���X�g���N�^				 �P�ʍs��ŏ���������܂�
		 */
										KsQuaternion() : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 1.0f ) {}

		/**
		 * �R���X�g���N�^
		 * @param	farray				����������l, ���̔z��̏��� �v�f�����������܂�
		 */
										KsQuaternion( const KsReal* fArray ) : x( fArray[0] ), y( fArray[1] ), z( fArray[2] ), w( fArray[3] ) {}

		/**
		 * �R���X�g���N�^
		 * @param	farray				����������l, ���̔z��̏��� �v�f�����������܂�
		 */
										KsQuaternion( KsReal qx, KsReal qy, KsReal qz, KsReal qw ) : x( qx ), y( qy ), z( qz ), w( qw ) {}

										KsQuaternion( const KsMatrix3x3& refMatrix );

										KsQuaternion( const KsMatrix4x4& refMatrix );
		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
										operator KsReal* () { return &x; }

		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
										operator const KsReal* () const { return &x; }

		/**
		 *
		 */
		KsQuaternion&					operator = ( const KsQuaternion& refQuat );
		KsQuaternion&					operator = ( const KsMatrix4x4& refMatrix );

		KsQuaternion&					operator += ( const KsQuaternion& refQuat );
		KsQuaternion&					operator -= ( const KsQuaternion& refQuat );
		KsQuaternion&					operator *= ( const KsQuaternion& refQuat );
		KsQuaternion&					operator *= ( KsReal s );
		KsQuaternion&					operator /= ( KsReal s );
	
		KsQuaternion					operator ~ () const;
		KsQuaternion					operator + () const;
		KsQuaternion					operator - () const;
	
		KsQuaternion					operator + ( const KsQuaternion& refQuat ) const;
		KsQuaternion					operator - ( const KsQuaternion& refQuat ) const;
		KsQuaternion					operator * ( const KsQuaternion& refQuat ) const;
		KsQuaternion					operator * ( KsReal s ) const;
		KsQuaternion					operator / ( KsReal s ) const;

		KsBool							operator == ( const KsQuaternion& refQuat ) const;
		KsBool							operator != ( const KsQuaternion& refQuat ) const;


		friend KsQuaternion				operator * ( KsReal s, const KsQuaternion& v ) { return v * s; }

		//�t�s��
	

		KsReal							length() const;

		KsReal							length2() const;

		//Dot

		/**
		 * ���K������
		 */
		void							normalize();

		/**
		 * �t�N�H�[�^�j�I��
		 */
		void							inverse();

		KsMatrix4x4						convertToMatrix();

		void							convertToMatrix( KsMatrix4x4* pMatrix );

		void							fromAxisRotation( const KsVector3d& refAxis, KsReal angle );
		void							fromEulerAngles( KsReal angleX, KsReal angleY, KsReal angleZ );
		void							convertToAxisRotation( KsVector3d* pAxis, KsReal* pAngle );
		KsVector3d						convertToEuler();

		//void							slerp( const KsQuaternion* pDest, KsReal t );

		static const KsQuaternion		IDENTITY;
		
		static KsQuaternion				CreateFromYawPitchRoll( KsReal yaw, KsReal pitch, KsReal roll );
		static KsQuaternion				CreateFromAxisAngle( const KsVector3d& refAxis, KsReal angle );
		static KsQuaternion				CreateFromRotationMatrix( const KsMatrix4x4& refMatrix );
		static KsQuaternion				CreateFromRotationMatrix( const KsMatrix3x3& refMatrix );
		static KsQuaternion				Slerp( const KsQuaternion& refSrc, const KsQuaternion& refDest, KsReal t );
		static KsQuaternion				Lerp( const KsQuaternion& refSrc, const KsQuaternion& refDest, KsReal t );
		static KsQuaternion				Multiply( const KsQuaternion& refA, const KsQuaternion& refB );
};

extern void KsQuaternionSlerp( KsQuaternion* pOut, const KsQuaternion* pSrc, const KsQuaternion* pDest, KsReal t );
extern void KsQuaternionLerp( KsQuaternion* pOut, const KsQuaternion* pSrc, const KsQuaternion* pDest, KsReal t );

/*************************************************************************************************/
/**
 * ����x�N�g�����炠��x�N�g���ւ̃N�H�[�^�j�I�������߂�i�ŏ��ʃN�H�[�^�j�I���j
 * @param		pQuat		�N�H�[�^�j�I��
 * @param		pV0			�ϊ��O�̍s��
 * @param		pV1			�ϊ���̍s��
 * @note		�t�H�[�~���O�Ȃǂ̊O�ς��O�ɋ߂��Ƃ����������Ȃ邽�߂̑Ώ�
 */
/*************************************************************************************************/
extern void KsRotationArc( KsQuaternion& quat, const KsVector3d& refV0, const KsVector3d refV1 );

/*************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>--------------------------------*/
								#include "KsEngine/math/KsQuaternion.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/


#endif /* __KSQUATERNION_H__ */

