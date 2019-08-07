/************************************************************************************************/
/** 
 * @file		KsColor.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSCOLOR_H__
#define __KSCOLOR_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsColorReal;

/************************************************************************************************/
/**
 * @class		KsColor
 * @brief		�J���[�N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsColor
{
	public:
		union{
			struct{
				KsByte					m_red;			/**< ���b�h		*/
				KsByte					m_green;		/**< �O���[��	*/
				KsByte					m_blue;			/**< �u���[		*/
				KsByte					m_alpha;		/**< �A���t�@	*/
			};
			KsByte						m_data[ 4 ];	/**< �f�[�^		*/
		};

		/**
		 * �R���X�g���N�^
		 */
										KsColor() : m_red( 0 ), m_green( 0 ), m_blue( 0 ), m_alpha( 0 ) {}

		/**
		 * �J���[���Z�b�g����
		 * @param	fArray				�f�[�^
		 */
										KsColor( const KsByte* fArray ) : m_red( fArray[ 0 ] ), m_green( fArray[ 1 ] ), m_blue( fArray[ 2 ] ), m_alpha( fArray[ 3 ] ) {}

		/**
		 * �J���[���Z�b�g����
		 * @param	red					���b�h
		 * @param	blue				�u���[
		 * @param	green				�O���[��
		 * @param	alpha				�A���t�@
		 */
										KsColor( KsByte red, KsByte green, KsByte blue, KsByte alpha ) : m_red( red ), m_green( green ), m_blue( blue ), m_alpha( alpha ) {}

		/**
		 * �J���[���Z�b�g����
		 * @param	pColor				�J���[
		 */
										KsColor( const KsColor* pColor ) : m_red( pColor->m_red ), m_green( pColor->m_green ), m_blue( pColor->m_blue ), m_alpha( pColor->m_alpha ) {}

		/**
		 * �J���[���Z�b�g����
		 * @param	refColor			�J���[
		 */
										KsColor( const KsColor& refColor ) : m_red( refColor.m_red ), m_green( refColor.m_green ), m_blue( refColor.m_blue ), m_alpha( refColor.m_alpha ) {}

		/**
		 * ���b�h���擾
		 * @return						���b�h
		 */
		KsByte							getRed() const { return m_red; }

		/**
		 * �O���[�����擾
		 * @return						�O���[��
		 */
		KsByte							getGreen() const { return m_green; }

		/**
		 * �u���[���擾
		 * @return						�u���[
		 */
		KsByte							getBlue() const { return m_blue; }

		/**
		 * �A���t�@���擾
		 * @return						�A���t�@
		 */
		KsByte							getAlpha() const { return m_alpha; }

		/**
		 * �f�[�^���擾
		 * @return						�f�[�^
		 */
		const KsByte*					getData() { return &m_data[ 0 ]; }
		
		/**
		 * ���b�h���Z�b�g����
		 * @param	red					���b�h
		 */
		void							setRed( KsByte red ) { m_red = red; }

		/**
		 * �O���[�����Z�b�g����
		 * @param	green				�O���[��
		 */
		void							setGreen( KsByte green ) { m_green = green; }

		/**
		 * �O���[�����Z�b�g����
		 * @param	blue				�u���[
		 */
		void							setBlue( KsByte blue ) { m_blue = blue; }

		/**
		 * �A���t�@���Z�b�g����
		 * @param	alpha				�A���t�@
		 */
		void							setAlpha( KsByte alpha ) { m_alpha = alpha; }
		
		/**
		 * �J���[���Z�b�g����
		 * @param	red					���b�h
		 * @param	blue				�u���[
		 * @param	green				�O���[��
		 * @param	alpha				�A���t�@
		 */
		void							set( KsByte red, KsByte green, KsByte blue, KsByte alpha ) { m_red = red; m_green = green; m_blue = blue; m_alpha = alpha; }

		/**
		 * �J���[���Z�b�g����
		 * @param	fArray				�f�[�^
		 */
		void							set( const KsByte* fArray ) { m_red = fArray[ 0 ]; m_green = fArray[ 1 ]; m_blue = fArray[ 2 ]; m_alpha = fArray[ 3 ]; }

		/**
		 * �J���[���Z�b�g����
		 * @param	pColor				�J���[
		 */
		void							set( const KsColor* pColor )  { m_red = pColor->getRed(); m_green = pColor->getGreen(); m_blue = pColor->getBlue(); m_alpha = pColor->getAlpha(); }

		/**
		 * �J���[���Z�b�g����
		 * @param	refColor			�J���[
		 */
		void							set( const KsColor& refColor )  { m_red = refColor.getRed(); m_green = refColor.getGreen(); m_blue = refColor.getBlue(); m_alpha = refColor.getAlpha(); }
		
		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
		KsByte*							operator [] ( KsInt32 index ) { return &m_data[ index ]; }

		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
		const KsByte*					operator [] ( KsInt32 index ) const { return &m_data[ index ]; }

		KsBool							operator == ( const KsColor& refColor ) const	{ return ( 0 == memcmp( this, &refColor, sizeof(KsColor) ) ); }
		KsBool							operator != ( const KsColor& refColor ) const	{ return ( 0 != memcmp( this, &refColor, sizeof(KsColor) ) ); }
		KsColor&						operator  = ( const KsColor& refColor )			{ memcpy( &m_data[ 0 ], &refColor, sizeof(KsColor) ); return ( *this ); }
		KsColor&						operator  = ( const KsColorReal& refColor );

		static const KsColor			RED;
		static const KsColor			GREEN;
		static const KsColor			BLUE;
		static const KsColor			WHITE;
		static const KsColor			BLACK;
};

#endif		/* __KSCOLOR_H__ */

