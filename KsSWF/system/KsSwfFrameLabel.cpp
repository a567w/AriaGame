/************************************************************************************************/
/** 
 * @file		KsSwfFrameLabel.cpp
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
KsSwfFrameLabel::KsSwfFrameLabel( KsFileObject* pFile )
	: KsSwfCommand( ksSWF_FRAMELABEL )
{
	m_name = pFile->readString();
}

/************************************************************************************************/
/* 
 * �f�X�g���N�^
 */
/************************************************************************************************/
KsSwfFrameLabel::~KsSwfFrameLabel()
{
}

/************************************************************************************************/
/* 
 * �R�}���h���s
 */
/************************************************************************************************/
void KsSwfFrameLabel::execute()
{
}
