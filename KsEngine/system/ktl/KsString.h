/************************************************************************************************/
/** 
 * @file		KsString.h
 * @brief		�����񑀍�
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRING_H__
#define __KSSTRING_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
//#include "KsCore.h"

/*===============================================================================================*/
/*                                     << ��` >>                                                */
/*===============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsString
 * @brief		�����񑀍�
 * @author		Tsukasa Kato
 * @date		2004/03/30
 */
/************************************************************************************************/
class ksENGINE_API KsString
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsString();

		/**
		 * �R���X�g���N�^
		 * @param		string		������N���X�̎Q��
		 */
									KsString( const KsString& string );

		/**
		 * �R���X�g���N�^
		 * @param		pString		������̃|�C���^
		 */
									KsString( const KsSChar* pString );

		/**
		 * �R���X�g���N�^
		 * @param		pString		������̃|�C���^
		 */
									KsString( const KsWChar* pString );

		/**
		 * �f�X�g���N�^
		 */
									~KsString();

		/**
		 * ������̒������擾����
		 * @return					������̒���
		 */
		KsUInt32					length() const { return m_length; }

		/**
		 * ������̃o�b�t�@�T�C�Y���擾����
		 * @return					�o�b�t�@�T�C�Y
		 */
		KsUInt32					size() const { return m_size; }

		/**
		 * ������̃o�b�t�@�擾
		 * @return					������̐擪�|�C���^
		 */
		const KsChar*				c_str() const { return m_pString; }

		/**
		 * �󂩂ǂ������`�F�b�N����
		 * @retval		ksTRUE		��ł�
		 * @retval		ksFALSE		��łȂ�
		 */
		KsBool						empty() const { return ( NULL == m_pString ); }

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
		KsChar						operator []( KsUInt32 index )		{ return m_pString[ index ]; }
	
		/**
		 * �w��C���f�b�N�X�̕������擾����( operator )
		 * @param	index			�擾����C���f�b�N�X
		 * @return					����
		 */
		const KsChar				operator []( KsUInt32 index ) const { return m_pString[ index ]; }

		KsString&					operator=(const KsString& string );
		KsString&					operator=(const KsSChar* string );
		KsString&					operator=(const KsWChar* string );
		KsString&					operator=(const KsChar c );

		KsString&					operator+=(const KsString& string );
		KsString&					operator+=(const KsChar* string );
		KsString&					operator+=(const KsChar c );

		KsString					operator+(const KsString& string );
		KsString					operator+(const KsChar* pString );
		KsString					operator+(const KsChar c );

		KsBool						operator==( const KsChar* pString ) const { return ( 0 == ks_strcmp( m_pString, pString ) ); }
		KsBool						operator==( const KsString& string ) const { return ( 0 == ks_strcmp( m_pString, string.c_str() ) ); }
	
		KsBool						operator!=( const KsChar* pString ) const { return ks_strcmp( m_pString, pString ); }
		KsBool						operator!=( const KsString& string ) const { return ks_strcmp( m_pString, string.c_str() ); }

	private:
		KsChar*						m_pString;		/**< ������					*/
		KsUInt32					m_length;		/**< ������̒���				*/
		KsUInt32					m_size;			/**< ������o�b�t�@�̃T�C�Y		*/
};

/************************************************************************************************/
/*
 * ���C�h������(WCHAR*)���}���`�o�C�g������(char*)�ɕϊ�
 * @param	wStrW		�ϊ��O������
 * @param	pOut		�ϊ�������i�[�o�b�t�@
 */
/************************************************************************************************/
ksENGINE_API KsUInt32 ks_wcstombs( const KsWChar* wStrW, KsSChar* pOut, KsUInt32 len );

/************************************************************************************************/
/*
 * �}���`�o�C�g������(char*)�����C�h������(WCHAR*)�ɕϊ�
 * @param	wStrW		�ϊ��O������
 * @param	pOut		�ϊ�������i�[�o�b�t�@
 */
/************************************************************************************************/
ksENGINE_API KsUInt32 ks_mbstowcs( const KsSChar* sStr, KsWChar* pOut, KsUInt32 len );


#endif		/* __KSSTRING_H__ */

