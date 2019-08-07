/************************************************************************************************/
/** 
 * @file		KsHierarchy.h
 * @brief		���g��(�K�w�\��)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSHIERARCHY_H__
#define __KSHIERARCHY_H__
#if 0
/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsJoint.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/


typedef std::vector< KsJoint* >	KsJointList;

/************************************************************************************************/
/**
 * @class		KsHierarchy
 * @brief		�K�w�\��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsHierarchy
{
	public:
		/**
		 * �R���X�g���N�^
		 */
		KsHierarchy(){}

		/**
		 * �f�X�g���N�^
		 */
		virtual								~KsHierarchy(){}

	public:
		KsJointList								m_pRootJointList;	/**< ���[�g�ɂȂ�W���C���g���X�g	*/
		KsJointList								m_pJointList;		/**< �W���C���g���X�g				*/
};

#endif

#endif		/* __KSHIERARCHY_H__ */



