/************************************************************************************************/
/** 
 * @file		KsVector3d.h
 * @brief		3D�x�N�g������
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVECTOR3D_H__
#define __KSVECTOR3D_H__

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
class KsQuaternion;

/*************************************************************************************************/
/**
 * @class	KsVector3d
 * @brief	3D�x�N�g������N���X
 * @author	tsukasa katou
 */
/*************************************************************************************************/
class ksENGINE_API KsVector3d
{
	public:
		/**
		 * �x�N�g���� x, y, z ����
		 */
		KsReal							x, y, z;

		/**
		 * �R���X�g���N�^				�[���ŏ���������܂�
		 */
										KsVector3d() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}

		/**
		 * �R���X�g���N�^
		 * @param	val					����������l, ���̒l��x, y, z �����������܂�
		 */
										KsVector3d( KsReal val ) : x( val ), y( val ), z( val ) {}

		/**
		 * �R���X�g���N�^
		 * @param	farray				����������l, ���̔z��̏��� x, y, z �����������܂�
		 */
										KsVector3d( const KsReal* fArray ) : x( fArray[ 0 ] ), y( fArray[ 1 ] ), z( fArray[ 2 ] ) {}
	
		/**
		 * �R���X�g���N�^(copy)
		 * @param	refVector			�����̒l���R�s�[���ď��������܂�
		 */
										KsVector3d( const KsVector3d& refVector ) : x( refVector.x ), y( refVector.y ), z( refVector.z ) {}
		/**
		 * �R���X�g���N�^
		 * @param	xf					����������x�̒l
		 * @param	yf					����������y�̒l
		 * @param	zf					����������z�̒l
		 */
										KsVector3d( KsReal xf, KsReal yf, KsReal zf ) : x( xf ), y( yf ), z( zf ) {}

		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
										operator KsReal* () { return &x; }

		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
										operator const KsReal* () const { return &x; }

		/**
		 * �z����̒l��Ԃ�
		 * @param	num					�Ԃ��z��̃i���o�[
		 * @return						�z����̐擪�̎Q��
		 */
		KsReal&							operator[]( KsInt32 index );

		/**
		 * �z����̒l��Ԃ�
		 * @param	num					�Ԃ��z��̃i���o�[
		 * @return						�z����̐擪�̎Q��
		 */
		const KsReal&					operator[]( KsInt32 index ) const;

		/**
		 * �x�N�g����( = )���Z�q
		 * @param	rkVector			�l���R�s�[����x�N�g��
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		const KsVector3d&				operator = ( const KsVector3d& rkVector );
							
		/**
		 * �x�N�g����( += )���Z�q
		 * @param	rkVector			�l�𑫂��x�N�g��
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector3d&						operator += ( const KsVector3d& refVector );

		/**
		 * �x�N�g����( += )���Z�q
		 * @param	rkVector			�l�𑫂��x�N�g��
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector3d&						operator -= ( const KsVector3d& refVector );

		/**
		 * �x�N�g����( *= )���Z�q
		 * @param	s					�x�N�g���Ɋ|����l
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector3d&						operator *= ( KsReal s );

		/**
		 * �x�N�g����( /= )���Z�q
		 * @param	s					�x�N�g��������l
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector3d&						operator /= ( KsReal s );

		/**
		 * �x�N�g����( + )���Z�q
		 * @return						+ ���Z�q�̃x�N�g��
		 */
		KsVector3d						operator + () const;

		/**
		 * �x�N�g����( - )���Z�q
		 * @return						- ���Z�q�̃x�N�g��
		 */
		KsVector3d						operator - () const;

		/**
		 * �x�N�g����( + )���Z�q
		 * @param	refVector			�v�Z����x�N�g��
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector3d						operator + ( const KsVector3d& refVector ) const;

		/**
		 * �x�N�g����( - )���Z�q
		 * @param	refVector			�v�Z����x�N�g��
		 */
		KsVector3d						operator - ( const KsVector3d& refVector ) const;
	
		/**
		 * �x�N�g����( * )���Z�q
		 * @param						�|����l
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector3d						operator * ( KsReal s ) const;
	
		/**
		 * �x�N�g����( / )���Z�q
		 * @param	s					����l
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector3d						operator / ( KsReal s ) const;

		/**
		 * �x�N�g�������������𔻒肷��
		 * @param	refVector			���肷��x�N�g��
		 * @retval	ksTRUE				������
		 * @retval	ksFALSE				�������Ȃ�
		 */
		KsBool							operator == ( const KsVector3d& refVector ) const;
	
		/**
		 * �x�N�g�����������Ȃ����𔻒肷��
		 * @param	refVector			���肷��x�N�g��
		 * @retval	ksTRUE				�������Ȃ�
		 * @retval	ksFALSE				������
		 */
		KsBool							operator != ( const KsVector3d& refVector ) const;

		/**
		 * �e�������Z�b�g����
		 * @param	xf					x����
		 * @param	yf					y����
		 * @param	zf					z����
		 */
		void							set( KsReal xf, KsReal yf, KsReal zf );
	
		/**
		 * �e�������Z�b�g����
		 * @param	fArray				�����̐擪�̃|�C���^
		 */
		void							set( const KsReal* fArray );
	
		/**
		 * �w�肵�������̃x�N�g���ɕύX����
		 * @param	len					�ύX���钷��
		 */
		void							scaleTo( KsReal len );
	
		/**
		 * �O�Ń��Z�b�g����
		 */
		void							reset();
	
		/**
		 * �x�N�g���̒������擾����
		 */
		KsReal							length();
	
		/**
		 * �x�N�g���̒����̂Q����擾����
		 */
		KsReal							length2();
	
		/**
		 * ���K������
		 */
		void							normalize();
	
		/**
		 * ����
		 * @param	refVector			���ς���x�N�g��
		 * @return						���ό��ʂ̃X�J���[�l
		 */
		KsReal							dotProduct( const KsVector3d& refVector ) const;

		/**
		 * �O��
		 * @param	refVector			�O�ς���x�N�g��
		 * @return						�O�ό��ʂ̃x�N�g��
		 */
		KsVector3d						crossProduct( const KsVector3d& refVector );

		/**
		 * �[���x�N�g��
		 */
		static const KsVector3d			ZERO;

		/**
		 * 1.0f�ŏ��������ꂽ�x�N�g��
		 */
		static const KsVector3d			ONE;

		/**
		 * (0,1,0)�ŏ��������ꂽ�x�N�g��
		 */
		static const KsVector3d			UP;

		/**
		 * (1,0,0)�ŏ��������ꂽ�x�N�g��
		 */
		static const KsVector3d			V100;

		/**
		 * (0,1,0)�ŏ��������ꂽ�x�N�g��
		 */
		static const KsVector3d			V010;

		/**
		 * (0,0,1)�ŏ��������ꂽ�x�N�g��
		 */
		static const KsVector3d			V001;

		static KsReal					Dot( const KsVector3d& a, const KsVector3d& b );
		static KsVector3d				Cross( const KsVector3d& a, const KsVector3d& b );
		static KsVector3d				Lerp( const KsVector3d& a, const KsVector3d& b, KsReal t );
		static KsVector3d				Transform( const KsVector3d* pV, const KsQuaternion* pQuat );
		static KsVector3d				Transform( const KsVector3d* pV, const KsMatrix4x4* pMatrix );
		static KsVector3d				TransformNormal( const KsVector3d* pV, const KsMatrix4x4* pMatrix );
		static void						TransformArray( KsVector3d* pOut, KsUInt32 OutStride, const KsVector3d* pV, KsUInt32 VStride, const KsMatrix4x4* pM, KsUInt32 n );

};

/************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>---------------------------------*/
								#include "KsEngine/math/KsVector3d.inl"
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/


#endif /* __KSVECTOR3D_H__ */

