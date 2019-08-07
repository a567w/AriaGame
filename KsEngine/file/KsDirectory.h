/************************************************************************************************/
/**
 * @file	KsDirectoy.h
 * @brief	�f�B���N�g������
 * @author	tsukasa kato
 * @date	2004/03/30
 * @version	1.0.0
 */
/************************************************************************************************/
#ifndef __KSDIRECTORY_H__
#define __KSDIRECTORY_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class	KsDirectoy
 * @brief	�f�B���N�g���擾
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/************************************************************************************************/
class KsDirectory
{
	public:
		/**
		 * �R�[���o�b�N�֐�
		 * @param		fileName			�t�@�C����
		 * @param		pData				�f�[�^
		 */
		typedef void						(*KsDirectoryCB)( const KsChar* fileName, void* pData );

	public:
		/**
		 * �R���X�g���N�^
		 */
											KsDirectory();

		/**
		 * �R���X�g���N�^
		 * @param		directoryName		�f�B���N�g����
		 * @param		pParent				�e�f�B���N�g��
		 */
											KsDirectory( const KsString& directoryName, KsDirectory* pParent );

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsDirectory();

		/**
		 * �t���p�X���擾����
		 * @return							�t���p�X
		 */
		const KsString&						getFullPath() const { return m_fullPath; }

		/**
		 * ���̃f�B���N�g���̖��O���擾����
		 * @return							�f�B���N�g����
		 */
		const KsString&						getDirectoryName() const { return m_directoryName; }

		/**
		 * �e�̃f�B���N�g�����擾����
		 * @return							�e�̃f�B���N�g��(���݂��Ȃ��Ƃ���NULL��Ԃ�)
		 */
		KsDirectory*						getParentDirectory() { return m_pParent; }

		/**
		 * �f�B���N�g������͂���
		 * @param		directory			��͂���f�B���N�g��
		 */
		void								parseDirectory( const KsString& directory );

		/**
		 * �A�^�b�`����
		 * @param		directory			�A�^�b�`����f�B���N�g��
		 */
		void								attach( KsDirectory* pDirectory );

		/**
		 * �f�^�b�`����
		 * @param		directory			�f�^�b�`����f�B���N�g��
		 */
		void								detach( KsDirectory* pDirectory );
	
		/**
		 * �t�@�C�����X�g���擾����
		 * @param 
		 */
		const KsString&						getFile( KsInt32 index ) const { return m_fileList[ index ]; }

		/**
		 * 
		 * 
		 */
		const KsDirectory*					getDirectory( KsInt32 index ) const { return m_vpDirectories[ index ]; }

		KsUInt32							getNumFile()	const { return static_cast<KsUInt32>( m_fileList.size() ); }

		KsUInt32							getNumDirectory()	const { return static_cast<KsUInt32>( m_vpDirectories.size() ); }

		// �K�w�̐[��
		//void								allFileExecCB();

	protected:
		//KsArray< KsFile > �{���̓n�b�V���e�[�u�����g�p�����ق�������
		KsArray< KsString >					m_fileList;				/**< �t�@�C�����X�g		*/
		KsArray< KsDirectory* >				m_vpDirectories;		/**< �f�B���N�g�����X�g	*/
		KsString							m_fullPath;				/**< �t���p�X			*/
		KsString							m_directoryName;		/**< �f�B���N�g����		*/
		KsDirectory*						m_pParent;				/**< �e�f�B���N�g��		*/
};


#endif		/* __KSDIRECTORY_H__ */
