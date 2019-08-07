/************************************************************************************************/
/** 
 * @file		KsFrame.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSFRAME_H__
#define __KSFRAME_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsVector.h"
#include "KsQuaternion.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * 
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsFrame
{
	public:
		typedef std::vector< KsFrame* >				KsFrameList;
		typedef std::vector< KsFrame* >::iterator		KsFrameListPtr;

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsFrame();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsFrame();

		KsVector3d						m_pivot;			/**< ��_				*/
		KsVector3d						m_pos;				/**< �ʒu				*/
		KsQuaternion					m_rot;				/**< ��]				*/
		KsVector3d						m_scale;			/**< �X�P�[��			*/

		KsVector3d						m_initPos;			/**< �ʒu				*/
		KsQuaternion					m_initRot;			/**< ��]				*/
		KsVector3d						m_initSscale;		/**< �X�P�[��			*/

		//KsFrame*						m_pParent;			/**< �e�̃|�C���^		*/
		//KsFrameList						m_childern;			/**< �q�̃|�C���^���X�g	*/
};



#endif		/* __KSFRAME_H__ */