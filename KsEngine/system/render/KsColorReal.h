/************************************************************************************************/
/** 
 * @file		KsColorReal.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSCOLORREAL_H__
#define __KSCOLORREAL_H__

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
class KsColor;

/************************************************************************************************/
/**
 * @class		KsColorReal
 * @brief		�J���[�N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsColorReal
{
	public:
		union{
			struct{
				KsReal					m_red;			/**< ���b�h		*/
				KsReal					m_green;		/**< �O���[��	*/
				KsReal					m_blue;			/**< �u���[		*/
				KsReal					m_alpha;		/**< �A���t�@	*/
			};
			KsReal						m_data[ 4 ];	/**< �f�[�^		*/
		};

		/**
		 * �R���X�g���N�^
		 */
										KsColorReal() : m_red( 0.0f ), m_green( 0.0f ), m_blue( 0.0f ), m_alpha( 1.0f ) {}

		/**
		 * �J���[���Z�b�g����
		 * @param	fArray				�f�[�^
		 */
										KsColorReal( const KsReal* fArray ) : m_red( fArray[ 0 ] ), m_green( fArray[ 1 ] ), m_blue( fArray[ 2 ] ), m_alpha( fArray[ 3 ] ) {}

		/**
		 * �J���[���Z�b�g����
		 * @param	red					���b�h
		 * @param	blue				�u���[
		 * @param	green				�O���[��
		 * @param	alpha				�A���t�@
		 */
										KsColorReal( KsReal red, KsReal green, KsReal blue, KsReal alpha ) : m_red( red ), m_green( green ), m_blue( blue ), m_alpha( alpha ) {}

		/**
		 * �J���[���Z�b�g����
		 * @param	pColor				�J���[
		 */
										KsColorReal( const KsColorReal* pColor ) : m_red( pColor->m_red ), m_green( pColor->m_green ), m_blue( pColor->m_blue ), m_alpha( pColor->m_alpha ) {}

		/**
		 * �J���[���Z�b�g����
		 * @param	refColor			�J���[
		 */
										KsColorReal( const KsColorReal& refColor ) : m_red( refColor.m_red ), m_green( refColor.m_green ), m_blue( refColor.m_blue ), m_alpha( refColor.m_alpha ) {}

		/**
		 * ���b�h���擾
		 * @return						���b�h
		 */
		KsReal							getRed() const { return m_red; }

		/**
		 * �O���[�����擾
		 * @return						�O���[��
		 */
		KsReal							getGreen() const { return m_green; }

		/**
		 * �u���[���擾
		 * @return						�u���[
		 */
		KsReal							getBlue() const { return m_blue; }

		/**
		 * �A���t�@���擾
		 * @return						�A���t�@
		 */
		KsReal							getAlpha() const { return m_alpha; }

		/**
		 * �f�[�^���擾
		 * @return						�f�[�^
		 */
		KsReal*							getData() { return &m_data[ 0 ]; }
		
		/**
		 * ���b�h���Z�b�g����
		 * @param	red					���b�h
		 */
		void							setRed( KsReal red ) { m_red = red; }

		/**
		 * �O���[�����Z�b�g����
		 * @param	green				�O���[��
		 */
		void							setGreen( KsReal green ) { m_green = green; }

		/**
		 * �O���[�����Z�b�g����
		 * @param	blue				�u���[
		 */
		void							setBlue( KsReal blue ) { m_blue = blue; }

		/**
		 * �A���t�@���Z�b�g����
		 * @param	alpha				�A���t�@
		 */
		void							setAlpha( KsReal alpha ) { m_alpha = alpha; }
		
		/**
		 * �J���[���Z�b�g����
		 * @param	red					���b�h
		 * @param	blue				�u���[
		 * @param	green				�O���[��
		 * @param	alpha				�A���t�@
		 */
		void							set( KsReal red, KsReal green, KsReal blue, KsReal alpha ) { m_red = red; m_green = green; m_blue = blue; m_alpha = alpha; }

		/**
		 * �J���[���Z�b�g����
		 * @param	fArray				�f�[�^
		 */
		void							set( const KsReal* fArray ) { m_red = fArray[ 0 ]; m_green = fArray[ 1 ]; m_blue = fArray[ 2 ]; m_alpha = fArray[ 3 ]; }

		/**
		 * �J���[���Z�b�g����
		 * @param	pColor				�J���[
		 */
		void							set( const KsColorReal* pColor )  { m_red = pColor->getRed(); m_green = pColor->getGreen(); m_blue = pColor->getBlue(); m_alpha = pColor->getAlpha(); }

		/**
		 * �J���[���Z�b�g����
		 * @param	refColor			�J���[
		 */
		void							set( const KsColorReal& refColor )  { m_red = refColor.getRed(); m_green = refColor.getGreen(); m_blue = refColor.getBlue(); m_alpha = refColor.getAlpha(); }
		
		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
		KsReal*							operator [] ( KsInt32 index ) { return &m_data[ index ]; }

		/**
		 * KsReal�̃|�C���^�ɕϊ����ĂŎ擾�ł���悤�ɂ���
		 */
		const KsReal*					operator [] ( KsInt32 index ) const { return &m_data[ index ]; }

		KsBool							operator == ( const KsColorReal& refColor ) const	{ return ( 0 == memcmp( this, &refColor, sizeof(KsColorReal) ) ); }
		KsBool							operator != ( const KsColorReal& refColor ) const	{ return ( 0 != memcmp( this, &refColor, sizeof(KsColorReal) ) ); }
		KsColorReal&					operator  = ( const KsColorReal& refColor )		{ memcpy( &m_data[ 0 ], &refColor, sizeof(KsColorReal) ); return ( *this ); }
		KsColorReal&					operator  = ( const KsColor& refColor );

		static const KsColorReal		RED;
		static const KsColorReal		GREEN;
		static const KsColorReal		BLUE;
		static const KsColorReal		WHITE;
		static const KsColorReal		BLACK;
};


#endif		/* __KSCOLORREAL_H__ */

