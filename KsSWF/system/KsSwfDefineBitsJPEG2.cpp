/************************************************************************************************/
/** 
 * @file		KsSwfDefineBitsJPEG2.cpp
 * @brief		SWF�R�}���h
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsSWF/KsSWFPreCompile.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/*
 * �R���X�g���N�^
 */
/************************************************************************************************/
KsSwfDefineBitsJPEG2::KsSwfDefineBitsJPEG2( KsFileObject* pFile, const KsSwfRecordHeader* tag )
	: KsSwfCommand( ksSWF_DEFINEBITSJPEG2 )
{
	m_characterID = pFile->readUInt16();
	m_size = tag->getSize() - 2;
	m_data = ksNew KsByte[ m_size ];

	pFile->read( m_data, m_size );
}

/************************************************************************************************/
/* 
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsSwfDefineBitsJPEG2::~KsSwfDefineBitsJPEG2()
{
	ksDELETEARRAY( m_data );
}

/************************************************************************************************/
/* 
 * �R�}���h���s
 */
/************************************************************************************************/
void KsSwfDefineBitsJPEG2::execute()
{
}
