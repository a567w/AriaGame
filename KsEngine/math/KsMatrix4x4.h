/************************************************************************************************/
/** 
 * @file		KsMatrix4x4.h
 * @brief		�}�g���b�N�X����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMATRIX4X4_H__
#define __KSMATRIX4X4_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsEngine/math/KsVector.h"
#include "KsEngine/math/KsPlane.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsVector3d;
class KsQuaternion;

/*************************************************************************************************/
/**
 * @class	KsMatrix4x4
 * @brief	�}�g���b�N�X����N���X
 * @author	Tsukasa Kato
 * @date	----/--/--
 * @since	----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsMatrix4x4
{
	public:
		/**
		 * �}�g���b�N�X�̗v�f����
		 */
		union
		{
			struct
			{
				KsReal	m11, m12, m13, m14;
				KsReal	m21, m22, m23, m24;
				KsReal	m31, m32, m33, m34;
				KsReal	m41, m42, m43, m44;
			};
			KsReal		m[ 4 ][ 4 ];
			KsReal		data[ 16 ];
		};

		/**
		 * �R���X�g���N�^					�P�ʍs��ŏ���������܂�
		 */
										KsMatrix4x4() :  m11(1.0f), m12(0.0f), m13(0.0f), m14(0.0f),
														 m21(0.0f), m22(1.0f), m23(0.0f), m24(0.0f),
														 m31(0.0f), m32(0.0f), m33(1.0f), m34(0.0f),
														 m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f) {}
		/**
		 * �R���X�g���N�^
		 * @param	farray				����������l, ���̔z��̏��� �v�f�����������܂�
		 */
										KsMatrix4x4( const KsReal* fArray )
												:  m11( fArray[ 0] ), m12( fArray[ 1] ), m13( fArray[ 2] ), m14( fArray[ 3] ),
												   m21( fArray[ 4] ), m22( fArray[ 5] ), m23( fArray[ 6] ), m24( fArray[ 7] ),
												   m31( fArray[ 8] ), m32( fArray[ 9] ), m33( fArray[10] ), m34( fArray[11] ),
												   m41( fArray[12] ), m42( fArray[13] ), m43( fArray[14] ), m44( fArray[15] ) {}

		/**
		 * �R���X�g���N�^(copy)
		 * @param	refMatrix			�����̒l���R�s�[���ď��������܂�
		 */
										KsMatrix4x4( const KsMatrix4x4& refMatrix )
												:  m11( refMatrix.m11 ), m12( refMatrix.m12 ), m13( refMatrix.m13 ), m14( refMatrix.m14 ),
												   m21( refMatrix.m21 ), m22( refMatrix.m22 ), m23( refMatrix.m23 ), m24( refMatrix.m24 ),
												   m31( refMatrix.m31 ), m32( refMatrix.m32 ), m33( refMatrix.m33 ), m34( refMatrix.m34 ),
												   m41( refMatrix.m41 ), m42( refMatrix.m42 ), m43( refMatrix.m43 ), m44( refMatrix.m44 ) {}


		/**
		 * �R���X�g���N�^					���ꂼ��̈����ŗv�f�����������܂�
		 */								
										KsMatrix4x4(  KsReal me11, KsReal me12, KsReal me13, KsReal me14,
												   KsReal me21, KsReal me22, KsReal me23, KsReal me24,
												   KsReal me31, KsReal me32, KsReal me33, KsReal me34,
												   KsReal me41, KsReal me42, KsReal me43, KsReal me44 )
												 : m11( me11 ), m12( me12 ), m13( me13 ), m14( me14 ),
												   m21( me21 ), m22( me22 ), m23( me23 ), m24( me24 ),
												   m31( me31 ), m32( me32 ), m33( me33 ), m34( me34 ),
												   m41( me41 ), m42( me42 ), m43( me43 ), m44( me44 ) {}

		/**
		 * �R���X�g���N�^				 
		 */
										KsMatrix4x4( const KsQuaternion& refQuat );

		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
										operator KsReal* () { return &m[ 0 ][ 0 ]; }
	
		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
										operator const KsReal* () const { return &m[ 0 ][ 0 ]; }
	
		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
		KsReal*							operator [] ( KsInt32 index ) { return &m[ index ][ 0 ]; }

		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
		const KsReal*					operator [] ( KsInt32 index ) const { return &m[ index ][ 0 ]; }

		KsMatrix4x4&					operator = ( const KsMatrix4x4& refMatrix );
		KsMatrix4x4&					operator = ( const KsQuaternion& refMatrix );

		KsMatrix4x4&					operator *= ( const KsMatrix4x4& refMatrix );
		KsMatrix4x4&					operator += ( const KsMatrix4x4& refMatrix );
		KsMatrix4x4&					operator -= ( const KsMatrix4x4& refMatrix );
		KsMatrix4x4&					operator *= ( KsReal s );
		KsMatrix4x4&					operator /= ( KsReal s );

		//KsMatrix4x4					operator ~ () const;
		KsMatrix4x4						operator + () const;
		KsMatrix4x4						operator - () const;

		KsMatrix4x4						operator * ( const KsMatrix4x4& refMatrix ) const;
		KsMatrix4x4						operator + ( const KsMatrix4x4& refMatrix ) const;
		KsMatrix4x4						operator - ( const KsMatrix4x4& refMatrix ) const;

		KsMatrix4x4						operator * ( KsReal s ) const;
		KsMatrix4x4						operator / ( KsReal s ) const;

		KsBool							operator == ( const KsMatrix4x4& refMatrix ) const;
		KsBool							operator != ( const KsMatrix4x4& refMatrix ) const;

		friend KsMatrix4x4				operator * ( KsReal s, const KsMatrix4x4& refMatrix );
	
		/**
		 * �l���Z�b�g����
		 * @param	farray				����������l, ���̔z��̏��� �v�f�����������܂�
		 * @return						�l���Z�b�g���ꂽ�}�g���b�N�X
		 */
		const KsMatrix4x4&				set( const KsReal* fArray );

		/**
		 * �N�H�[�^�j�I������ϊ����Ēl���Z�b�g����
		 * @param	refQuat				�N�H�[�^�j�I��
		 * @return						�l���Z�b�g���ꂽ�}�g���b�N�X
		 */
		const KsMatrix4x4&				set( const KsQuaternion& refQuat );

		/**
		 * �f�^�~�i���g���擾����
		 * @return						�f�^�~�i���g
		 */
		KsReal							determinant() const;

		/**
		 * �]�u����
		 */
		void							transpose();

		/**
		 * ���s����擾����
		 * @return						���s��
		 */
		const KsReal					minor( KsInt32 x, KsInt32 y ) const;

		/**
		 * �����s����擾����
		 * @return						�����s��
		 */
		const KsMatrix4x4				adjoint() const;

		/**
		 * �t�s����擾����
		 * A^-1 = 1/|A| * ~A (�t�s��̌������g��)
		 * �f�^�~�i���g�͗]���q�W�J(|A| = ��(-1)^(i+j) * a_ij*|A_ij| )
		 * @return						�t�s��
		 */
		KsMatrix4x4						inverse() const;

		/*
		 * �N�H�[�^�j�I������Δ����s������
		 */
		void							partialDifferential( const KsQuaternion &q, const KsQuaternion &dq );

		void							setTranslate( KsReal x, KsReal y, KsReal z );
		void							setTranslate( const KsVector3d& v );
		void							setTranslate( const KsVector3d* v );
		void							setScaleX( KsReal sx );
		void							setScaleY( KsReal sy );
		void							setScaleZ( KsReal sz );
		void							setScale( KsReal scale );
		void							setScale( KsReal sx, KsReal sy, KsReal sz );
		void							setScale( const KsVector3d& refScale );
		void							setScale( const KsVector3d* pScale );
		void							setRotateX( KsReal angle );
		void							setRotateY( KsReal angle );
		void							setRotateZ( KsReal angle );

		void							setEulerZYX( KsReal eulerX, KsReal eulerY, KsReal eulerZ );

		KsVector3d						getTranslate();
		KsQuaternion					getRotate();
		KsVector3d						getScale();

		//�t�s��
	
		/**
		 * �P�ʍs��
		 */
		static const KsMatrix4x4		IDENTITY;

		static KsMatrix4x4				CreateScale( const KsVector3d& refScale );
		static KsMatrix4x4				CreateFromQuaternion( const KsQuaternion& refQuat );
		static KsMatrix4x4				CreateTranslation( const KsVector3d& refTranslate );

		static const KsMatrix4x4&		PerspectiveRH( KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar );

		/**
		 * �N�H�[�^�j�I������Δ����s������
		 */
		static KsMatrix4x4				CreatePartialDifferential( const KsQuaternion &q, const KsQuaternion &dq );
};

/*************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>--------------------------------*/
								#include "KsEngine/math/KsMatrix4x4.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/



/************************************************************************************************/
/**
 * �����ˉe�s��𐶐�����(�E��n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		fovy			����p
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
ksENGINE_API void KsMatrixPerspectiveRH( KsMatrix4x4& projMatrix, KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar );

/************************************************************************************************/
/**
 * ���ˉe�s��𐶐�����(�E��n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		left			���t�g
 * @param		right			���C�g
 * @param		bottom			�{�g��
 * @param		top				�g�b�v
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
ksENGINE_API void KsMatrixOrthoRH( KsMatrix4x4& projMatrix, KsReal left, KsReal right, KsReal bottom, KsReal top, KsReal zNear, KsReal zFar );

/************************************************************************************************/
/**
 * ���_��ݒ肷��(�E��n)
 * @param		viewMatrix		�r���[�}�g���b�N�X�ۑ��p
 * @param		eye				���_
 * @param		at				�����_
 * @param		up				�A�b�v�x�N�g��
 */
/************************************************************************************************/
ksENGINE_API void KsMatrixLookAtRH( KsMatrix4x4& viewMatrix, const KsVector3d& eye, const KsVector3d& at, const KsVector3d& up );

/************************************************************************************************/
/**
 * �����ˉe�s��𐶐�����(����n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		fovy			����p
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
ksENGINE_API void KsMatrixPerspectiveLH( KsMatrix4x4& projMatrix, KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar );

/************************************************************************************************/
/**
 * ���ˉe�s��𐶐�����(����n)
 * @param		projMatrix		�v���W�F�N�V�����}�g���b�N�X�ۑ��p
 * @param		left			���t�g
 * @param		right			���C�g
 * @param		bottom			�{�g��
 * @param		top				�g�b�v
 * @param		aspect			�A�X�y�N�g��
 * @param		zNear			�ߋ����l
 * @param		zFar			�������l
 */
/************************************************************************************************/
ksENGINE_API void KsMatrixOrthoLH( KsMatrix4x4& projMatrix, KsReal left, KsReal right, KsReal bottom, KsReal top, KsReal zNear, KsReal zFar );

/************************************************************************************************/
/**
 * ���_��ݒ肷��(����n)
 * @param		viewMatrix		�r���[�}�g���b�N�X�ۑ��p
 * @param		eye				���_
 * @param		at				�����_
 * @param		up				�A�b�v�x�N�g��
 */
/************************************************************************************************/
ksENGINE_API void KsMatrixLookAtLH( KsMatrix4x4& viewMatrix, const KsVector3d& eye, const KsVector3d& at, const KsVector3d& up );

/************************************************************************************************/
/**
 * ���C�g����e���ˉe����悤��,�W�I���g���𕽖ʂɎˉe����B
 * @param		matrix			�r���[�}�g���b�N�X�ۑ��p
 * @param		eye				���_
 * @param		at				�����_
 * @param		up				�A�b�v�x�N�g��
 * @note
 * <pre>
 * ���̊֐����Ԃ��s��́A���̌������g���Čv�Z����B 
 *	P = normalize(Plane);
 *	L = Light;
 *	d = dot(P, L)
 *
 *	P.a * L.x + d  P.a * L.y      P.a * L.z      P.a * L.w  
 *	P.b * L.x      P.b * L.y + d  P.b * L.z      P.b * L.w  
 *	P.c * L.x      P.c * L.y      P.c * L.z + d  P.c * L.w  
 *	P.d * L.x      P.d * L.y      P.d * L.z      P.d * L.w + d
 * </pre>
 */
/************************************************************************************************/
ksENGINE_API void KsMatrixShadow( KsMatrix4x4& shadowMatrix, const KsVector3d& light, const KsPlane& refPlane, KsReal point );

#endif /* __KSMATRIX4X4_H__ */


