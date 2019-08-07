/************************************************************************************************/
/** 
 * @file		KsVector2d.h
 * @brief		2D�x�N�g������
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSVECTOR2D_H__
#define __KSVECTOR2D_H__

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
 * @class	KsVector2d
 * @brief	2D�x�N�g������N���X
 * @author	tsukasa katou
 */
/*************************************************************************************************/
class ksENGINE_API KsVector2d
{
	public:
		/**
		 * �x�N�g���� x, y ����
		 */
		KsReal							x, y;

		/**
		 * �R���X�g���N�^				�[���ŏ���������܂�
		 */
										KsVector2d() : x( 0.0f ), y( 0.0f ) {}

		/**
		 * �R���X�g���N�^
		 * @param	val					����������l, ���̒l��x, y �����������܂�
		 */
										KsVector2d( KsReal val ) : x( val ), y( val ) {}

		/**
		 * �R���X�g���N�^
		 * @param	farray				����������l, ���̔z��̏��� x, y �����������܂�
		 */
										KsVector2d( const KsReal* fArray ) : x( fArray[ 0 ] ), y( fArray[ 1 ] ) {}
	
		/**
		 * �R���X�g���N�^(copy)
		 * @param	refVector			�����̒l���R�s�[���ď��������܂�
		 */
										KsVector2d( const KsVector2d& refVector ) : x( refVector.x ), y( refVector.y ) {}
		/**
		 * �R���X�g���N�^
		 * @param	xf					����������x�̒l
		 * @param	yf					����������y�̒l
		 */
										KsVector2d( KsReal xf, KsReal yf ) : x( xf ), y( yf ){}

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
		const KsVector2d&				operator = ( const KsVector2d& rkVector );
							
		/**
		 * �x�N�g����( += )���Z�q
		 * @param	rkVector			�l�𑫂��x�N�g��
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector2d&						operator += ( const KsVector2d& refVector );

		/**
		 * �x�N�g����( += )���Z�q
		 * @param	rkVector			�l�𑫂��x�N�g��
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector2d&						operator -= ( const KsVector2d& refVector );

		/**
		 * �x�N�g����( *= )���Z�q
		 * @param	s					�x�N�g���Ɋ|����l
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector2d&						operator *= ( KsReal s );

		/**
		 * �x�N�g����( /= )���Z�q
		 * @param	s					�x�N�g��������l
		 * @return						�������g�̃x�N�g���Q��( *this )
		 */
		KsVector2d&						operator /= ( KsReal s );

		/**
		 * �x�N�g����( + )���Z�q
		 * @return						+ ���Z�q�̃x�N�g��
		 */
		KsVector2d						operator + () const;

		/**
		 * �x�N�g����( - )���Z�q
		 * @return						- ���Z�q�̃x�N�g��
		 */
		KsVector2d						operator - () const;

		/**
		 * �x�N�g����( + )���Z�q
		 * @param	refVector			�v�Z����x�N�g��
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector2d						operator + ( const KsVector2d& refVector ) const;

		/**
		 * �x�N�g����( - )���Z�q
		 * @param	refVector			�v�Z����x�N�g��
		 */
		KsVector2d						operator - ( const KsVector2d& refVector ) const;
	
		/**
		 * �x�N�g����( * )���Z�q
		 * @param						�|����l
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector2d						operator * ( KsReal s ) const;
	
		/**
		 * �x�N�g����( / )���Z�q
		 * @param	s					����l
		 * @return						���ʂ̃x�N�g��
		 */
		KsVector2d						operator / ( KsReal s ) const;

		/**
		 * �x�N�g�������������𔻒肷��
		 * @param	refVector			���肷��x�N�g��
		 * @retval	ksTRUE				������
		 * @retval	ksFALSE				�������Ȃ�
		 */
		KsBool							operator == ( const KsVector2d& refVector ) const;
	
		/**
		 * �x�N�g�����������Ȃ����𔻒肷��
		 * @param	refVector			���肷��x�N�g��
		 * @retval	ksTRUE				�������Ȃ�
		 * @retval	ksFALSE				������
		 */
		KsBool							operator != ( const KsVector2d& refVector ) const;

		/**
		 * �e�������Z�b�g����
		 * @param	xf					x����
		 * @param	yf					y����
		 * @param	zf					z����
		 */
		void							set( KsReal xf, KsReal yf );
	
		/**
		 * �e�������Z�b�g����
		 * @param	fArray				�����̐擪�̃|�C���^
		 */
		void							set( const KsReal* fArray );
	
		/**
		 * �O�Ń��Z�b�g����
		 */
		void							reset();

		/**
		 * �w�肵�������̃x�N�g���ɕύX����
		 * @param	len					�ύX���钷��
		 */
		void							scaleTo( KsReal len );
	
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
		KsReal							dotProduct( const KsVector2d& refVector ) const;

		/**
		 * �[���x�N�g��
		 */
		static const KsVector2d		ZERO;

		/**
		 * 1.0f�ŏ��������ꂽ�x�N�g��
		 */
		static const KsVector2d		ONE;
};

/*************************************************************************************************/
/*---------------------------<< �C�����C�������w�b�_�[�t�@�C�� >>----------------------------------*/
							#include "KsEngine/math/KsVector2d.inl"
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/


#endif /* __KSVECTOR2D_H__ */

