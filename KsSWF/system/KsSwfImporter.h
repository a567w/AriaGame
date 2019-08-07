/************************************************************************************************/
/** 
 * @file		KsSwfImporter.h
 * @brief		SWF�ǂݍ���
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFIMPORTER_H__
#define __KSSWFIMPORTER_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
//#include "KsTypeSwf.h"
//#include "KsSwfFileHeader.h"
//#include "KsSwfTag.h"
//#include "KsSwfMatrix.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSwfImporter
 * @brief		SWF�ǂݍ���
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		�Ȃ�
 */
/************************************************************************************************/
class ksSWF_API KsSwfImporter
{
	protected:
		KsFileObject*			m_pFile;		/**< �t�@�C���I�u�W�F�N�g	*/

	public:
		/**
		 * �R���X�g���N�^
		 */
								KsSwfImporter();

		/**
		 * �R���X�g���N�^
		 */
								KsSwfImporter( KsFileObject* pFile );
	    
		/**
		 * �f�X�g���N�^
		 */
								~KsSwfImporter();

		/**
		 * �t�@�C���w�b�_���擾����
		 */
		KsBool					readFileHeader( KsSwfFileHeader* pFileHeader );

		/**
		 * �^�O��ǂݍ���
		 */
		KsBool					readRecordHeader( KsSwfRecordHeader* pTag );

		/**
		 * Rect����ǂݍ���
		 */
		KsBool					readRect( KsSwfRect* pRect );

		/**
		 *
		 */
		KsBool					readMatrix( KsSwfMatrix* pMatrix );

		/**
		 *
		 */
		static KsBool			readRect( KsFileObject* pFile, KsSwfRect* pRect );
		static KsBool			readMatrix( KsFileObject* pFile, KsSwfMatrix* pMatrix );
};

ksSWF_API KsBool	KsLoadSwf( const KsChar* pFileName );

#endif	/* __KSSWFIMPORTER_H__ */


