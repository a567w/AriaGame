/************************************************************************************************/
/** 
 * @file		KsTexture.h
 * @brief		�e�N�X�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERCOMMANDOBJECT_H__
#define __KSRENDERCOMMANDOBJECT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsType.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsTexture
 * @brief		�e�N�X�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
class ksENGINE_API KsRenderCommandObject
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsRenderCommandObject();

		/**
		 * �f�X�g���N�^
		 */
		virtual					~KsRenderCommandObject();

		virtual void				execute( KsRenderSystem* pRenderSystem );

	protected:
		KsUInt16					m_type;		/**< �R�}���h�^�C�v		*/
		KsUInt16					m_size;		/**< �R�}���h�T�C�Y		*/

};


#endif		/* __KSRENDERCOMMANDOBJECT_H__ */


