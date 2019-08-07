/************************************************************************************************/
/** 
 * @file		KsVector4d.h
 * @brief		4D�x�N�g������
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVECTOR4D_H__
#define __KSVECTOR4D_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/*************************************************************************************************/
/**
 * @class	KsVector4d
 * @brief	4D�x�N�g������N���X
 * @author	tsukasa katou
 */
/*************************************************************************************************/
class ksENGINE_API KsVector4d
{
	public:
		/**
		 * �x�N�g���� x, y, z, w ����
		 */
		KsReal							x, y, z, w;

		/**
		 * �R���X�g���N�^				�[���ŏ���������܂�
		 */
										KsVector4d() : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 0.0f ) {}

		/**
		 * �R���X�g���N�^
		 * @param	val					����������l, ���̒l��x, y, z, w �����������܂�
		 */
										KsVector4d( KsReal val ) : x( val ), y( val ), z( val ), w( val ) {}

		/**
		 * �R���X�g���N�^
		 * @param	farray				����������l, ���̔z��̏��� x, y, z, w �����������܂�
		 */
										KsVector4d( const KsReal* fArray ) : x( fArray[ 0 ] ), y( fArray[ 1 ] ), z( fArray[ 2 ] ), w( fArray[ 3 ] ) {}
	
		/**
		 * �R���X�g���N�^(copy)
		 * @param	refVector			�����̒l���R�s�[���ď��������܂�
		 */
										KsVector4d( const KsVector4d& refVector ) : x( refVector.x ), y( refVector.y ), z( refVector.z ), w( refVector.w ) {}
		/**
		 * �R���X�g���N�^
		 * @param	xf					����������x�̒l
		 * @param	yf					����������y�̒l
		 * @param	zf					����������z�̒l
		 * @param	wf					����������w�̒l
		 */
										KsVector4d( KsReal xf, KsReal yf, KsReal zf, KsReal wf ) : x( xf ), y( yf ), z( zf ), w( wf ) {}

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
		const KsVector4d&				operator = ( const KsVector4d& rkVector );
							
		/**
		 * �x�N�g����( += )���Z�q
		 * @param	rkVector			�l�𑫂��x�N�g��
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector4d&						operator += ( const KsVector4d& refVector );

		/**
		 * �x�N�g����( += )���Z�q
		 * @param	rkVector			�l�𑫂��x�N�g��
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector4d&						operator -= ( const KsVector4d& refVector );

		/**
		 * �x�N�g����( *= )���Z�q
		 * @param	s					�x�N�g���Ɋ|����l
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector4d&						operator *= ( KsReal s );

		/**
		 * �x�N�g����( /= )���Z�q
		 * @param	s					�x�N�g��������l
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector4d&						operator /= ( KsReal s );

		/**
		 * �x�N�g����( + )���Z�q
		 * @return						+ ���Z�q�̃x�N�g��
		 */
		KsVector4d						operator + () const;

		/**
		 * �x�N�g����( - )���Z�q
		 * @return						- ���Z�q�̃x�N�g��
		 */
		KsVector4d						operator - () const;

		/**
		 * �x�N�g����( + )���Z�q
		 * @param	refVector			�v�Z����x�N�g��
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector4d						operator + ( const KsVector4d& refVector ) const;

		/**
		 * �x�N�g����( - )���Z�q
		 * @param	refVector			�v�Z����x�N�g��
		 */
		KsVector4d						operator - ( const KsVector4d& refVector ) const;
	
		/**
		 * �x�N�g����( * )���Z�q
		 * @param						�|����l
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector4d						operator * ( KsReal s ) const;
	
		/**
		 * �x�N�g����( / )���Z�q
		 * @param	s					����l
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector4d						operator / ( KsReal s ) const;

		/**
		 * �x�N�g�������������𔻒肷��
		 * @param	refVector			���肷��x�N�g��
		 * @retval	ksTRUE				������
		 * @retval	ksFALSE				�������Ȃ�
		 */
		KsBool							operator == ( const KsVector4d& refVector ) const;
	
		/**
		 * �x�N�g�����������Ȃ����𔻒肷��
		 * @param	refVector			���肷��x�N�g��
		 * @retval	ksTRUE				�������Ȃ�
		 * @retval	ksFALSE				������
		 */
		KsBool							operator != ( const KsVector4d& refVector ) const;

		/**
		 * �e�������Z�b�g����
		 * @param	xf					x����
		 * @param	yf					y����
		 * @param	zf					z����
		 * @param	wf					w����
		 */
		void							set( KsReal xf, KsReal yf, KsReal zf, KsReal wf );
	
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
		KsReal							dotProduct( const KsVector4d& refVector ) const;

		/**
		 * �[���x�N�g��
		 */
		static const KsVector4d			ZERO;

		/**
		 * 1.0f�ŏ��������ꂽ�x�N�g��
		 */
		static const KsVector4d			ONE;

		/**
		 * �n�[�t�x�N�^�[
		 */
		static const KsVector4d			HALF;

		/**
		 * �ő�l
		 */
		static const KsVector4d			MAX;

		/**
		 * �ŏ��l
		 */
		static const KsVector4d			MIN;

		/**
		 * V1100
		 */
		static const KsVector4d			VECTOR_1100;

		/**
		 * �ŏ��� 2 �̃x�N�g���̐ς��A3 �Ԗڂ̃x�N�g���ɉ��Z���܂��B
		 */
		static KsVector4d				MultiplyAdd( const KsVector4d& V1, const KsVector4d& V2, const KsVector4d& V3 );

		/**
		 * 2 �̃x�N�g���̍ő�l���擾����
		 */
		static KsVector4d				Max( const KsVector4d& V1, const KsVector4d& V2 );

};

/*************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>----------------------------------*/
								#include "KsEngine/math/KsVector4d.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/


#endif /* __KSVECTOR4D_H__ */



