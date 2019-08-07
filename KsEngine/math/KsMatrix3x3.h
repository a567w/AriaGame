/************************************************************************************************/
/** 
 * @file		KsMatrix3x3.h
 * @brief		�}�g���b�N�X����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMATRIX3X3_H__
#define __KSMATRIX3X3_H__

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
 * @class	KsMatrix3x3
 * @brief	�}�g���b�N�X����N���X
 * @author	Tsukasa Kato
 * @date	----/--/--
 * @since	----/--/--
 */
/*************************************************************************************************/
class ksENGINE_API KsMatrix3x3
{
	public:
		/**
		 * �}�g���b�N�X�̗v�f����
		 */
		union
		{
			struct
			{
				KsReal	m11, m12, m13;
				KsReal	m21, m22, m23;
				KsReal	m31, m32, m33;
			};
			KsReal		m[ 3 ][ 3 ];
			KsReal		data[ 9 ];
		};

		/**
		 * �R���X�g���N�^				�P�ʍs��ŏ���������܂�
		 */
										KsMatrix3x3() :  m11(1.0f), m12(0.0f), m13(0.0f),
														 m21(0.0f), m22(1.0f), m23(0.0f),
														 m31(0.0f), m32(0.0f), m33(1.0f){}
		/**
		 * �R���X�g���N�^
		 * @param	farray				����������l, ���̔z��̏��� �v�f�����������܂�
		 */
										KsMatrix3x3( const KsReal* fArray )
												:  m11( fArray[ 0] ), m12( fArray[ 1] ), m13( fArray[ 2] ),
												   m21( fArray[ 3] ), m22( fArray[ 4] ), m23( fArray[ 5] ),
												   m31( fArray[ 6] ), m32( fArray[ 7] ), m33( fArray[ 8] ) {}

		/**
		 * �R���X�g���N�^(copy)
		 * @param	refMatrix			�����̒l���R�s�[���ď��������܂�
		 */
										KsMatrix3x3( const KsMatrix3x3& refMatrix )
												:  m11( refMatrix.m11 ), m12( refMatrix.m12 ), m13( refMatrix.m13 ),
												   m21( refMatrix.m21 ), m22( refMatrix.m22 ), m23( refMatrix.m23 ),
												   m31( refMatrix.m31 ), m32( refMatrix.m32 ), m33( refMatrix.m33 ){}


		/**
		 * �R���X�g���N�^				���ꂼ��̈����ŗv�f�����������܂�
		 */								
										KsMatrix3x3( KsReal me11, KsReal me12, KsReal me13,
												     KsReal me21, KsReal me22, KsReal me23,
												     KsReal me31, KsReal me32, KsReal me33 )
												   : m11( me11 ), m12( me12 ), m13( me13 ),
												     m21( me21 ), m22( me22 ), m23( me23 ),
												     m31( me31 ), m32( me32 ), m33( me33 ) {}

		/**
		 * �R���X�g���N�^				 
		 */
										KsMatrix3x3( const KsQuaternion& refQuat );

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

		KsMatrix3x3&					operator = ( const KsMatrix3x3& refMatrix );
		KsMatrix3x3&					operator = ( const KsQuaternion& refMatrix );

		KsMatrix3x3&					operator *= ( const KsMatrix3x3& refMatrix );
		KsMatrix3x3&					operator += ( const KsMatrix3x3& refMatrix );
		KsMatrix3x3&					operator -= ( const KsMatrix3x3& refMatrix );
		KsMatrix3x3&					operator *= ( KsReal s );
		KsMatrix3x3&					operator /= ( KsReal s );

		//KsMatrix3x3					operator ~ () const;
		KsMatrix3x3						operator + () const;
		KsMatrix3x3						operator - () const;

		KsVector3d						operator * ( const KsVector3d&  refVector ) const;
		KsMatrix3x3						operator * ( const KsMatrix3x3& refMatrix ) const;
		KsMatrix3x3						operator + ( const KsMatrix3x3& refMatrix ) const;
		KsMatrix3x3						operator - ( const KsMatrix3x3& refMatrix ) const;

		KsMatrix3x3						operator * ( KsReal s ) const;
		KsMatrix3x3						operator / ( KsReal s ) const;

		KsBool							operator == ( const KsMatrix3x3& refMatrix ) const;
		KsBool							operator != ( const KsMatrix3x3& refMatrix ) const;

		friend KsMatrix3x3				operator * ( KsReal s, const KsMatrix3x3& refMatrix );
	
		/**
		 * �l���Z�b�g����
		 * @param	farray				����������l, ���̔z��̏��� �v�f�����������܂�
		 * @return						�l���Z�b�g���ꂽ�}�g���b�N�X
		 */
		const KsMatrix3x3&				set( const KsReal* fArray );

		/**
		 * �N�H�[�^�j�I������ϊ����Ēl���Z�b�g����
		 * @param	refQuat				�N�H�[�^�j�I��
		 * @return						�l���Z�b�g���ꂽ�}�g���b�N�X
		 */
		const KsMatrix3x3&				set( const KsQuaternion& refQuat );

		/**
		 * �f�^�~�i���g���擾����
		 * @return						�f�^�~�i���g
		 */
		KsReal							determinant() const;

		/**
		 * �t�s����擾����
		 * A^-1 = 1/|A| * ~A (�t�s��̌������g��)
		 * �f�^�~�i���g�͗]���q�W�J(|A| = ��(-1)^(i+j) * a_ij*|A_ij| )
		 * @return						�t�s��
		 */
		KsMatrix3x3						inverse();

		/**
		 * �]�u����
		 */
		void							transpose();


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

		KsQuaternion					getRotate() const;
		KsVector3d						getScale() const;

		//�t�s��
	
		/**
		 * �P�ʍs��
		 */
		static const KsMatrix3x3		IDENTITY;
};

/*************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>----------------------------------*/
						#include "KsEngine/math/KsMatrix3x3.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/

#endif /* __KSMATRIX3X3_H__ */


