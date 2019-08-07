/************************************************************************************************/
/** 
 * @file		KsStringFixed.h
 * @brief		�����񑀍�
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRINGFIXED_H__
#define __KSSTRINGFIXED_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
//#include "system/KsCore.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/
#define ksSTRING_LENGTH		( 512 )		/**< �ő�̑��앶���� */

/************************************************************************************************/
/**
 * @class		KsStringFixed
 * @brief		�����񑀍�(�Œ�256�o�C�g)
 * @author		Tsukasa Kato
 * @date		2004/03/30
 */
/************************************************************************************************/
class ksENGINE_API KsStringFixed
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsStringFixed() : m_length( 0 ) { m_string[ 0 ] = '\0'; }

		/**
		 * �R���X�g���N�^
		 * @param		string		������N���X�̎Q��
		 */
									KsStringFixed( const KsStringFixed& string );

		/**
		 * �R���X�g���N�^
		 * @param		pString		������̃|�C���^
		 */
									KsStringFixed( const KsChar* pString );

		/**
		 * �f�X�g���N�^
		 */
									~KsStringFixed();

		/**
		 * ������̒������擾����
		 * @return					������̒���
		 */
		KsUInt32					length() const { return m_length; }

		/**
		 * ������̃o�b�t�@�擾
		 * @return					������̐擪�|�C���^
		 */
		const KsChar*				c_str() const { return m_string; }

		/**
		 * �󂩂ǂ������`�F�b�N����
		 * @retval		ksTRUE		��ł�
		 * @retval		ksFALSE		��łȂ�
		 */
		KsBool						empty() const { return ( !m_length ); }

		/**
		 * �w��͈͂̕������폜����
		 * @param		top			����������̐擪
		 * @param		num			����������̐�
		 */
		void						erase( KsUInt32 top, KsUInt32 num );

		/**
		 * ��������N���A
		 */
		void						clear();

		/**
		 * �w��C���f�b�N�X�̕������擾����( operator )
		 * @param	index			�擾����C���f�b�N�X
		 * @return					����
		 */
		KsChar&						operator []( KsUInt32 index )		{ return m_string[ index ]; }
	
		/**
		 * �w��C���f�b�N�X�̕������擾����( operator )
		 * @param	index			�擾����C���f�b�N�X
		 * @return					����
		 */
		const KsChar&				operator []( KsUInt32 index ) const { return m_string[ index ]; }

		KsStringFixed&				operator=(const KsStringFixed& string );
		KsStringFixed&				operator=(const KsChar* string );
		KsStringFixed&				operator=(const KsChar c );

		KsStringFixed&				operator+=(const KsStringFixed& string );
		KsStringFixed&				operator+=(const KsChar* string );
		KsStringFixed&				operator+=(const KsChar c );

		KsStringFixed					operator+(const KsStringFixed& string );
		KsStringFixed					operator+(const KsChar* pString );
		KsStringFixed					operator+(const KsChar c );

		KsBool						operator==( const KsChar* pString ) const { return ( 0 == ks_strcmp( m_string, pString ) ); }
		KsBool						operator==( const KsStringFixed& string ) const { return ( 0 == ks_strcmp( m_string, string.c_str() ) ); }
	
		KsBool						operator!=( const KsChar* pString ) const { return ks_strcmp( m_string, pString ); }
		KsBool						operator!=( const KsStringFixed& string ) const { return ks_strcmp( m_string, string.c_str() ); }

	private:
		KsChar						m_string[ ksSTRING_LENGTH ];	/**< ������			*/
		KsUInt32					m_length;						/**< ������̒���	*/
};


#endif		/* __KSSTRINGFIXED_H__ */

