/************************************************************************************************/
/** 
 * @file		KsJoint.h
 * @brief		�W���C���g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSJOINT_H__
#define __KSJOINT_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsVector.h"
#include "KsMatrix.h"
#include "KsQuaternion.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

#if 0
/************************************************************************************************/
/**
 * @class		KsJoint
 * @brief		�W���C���g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsJoint
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsJoint();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsJoint();

	public:
		KsSkeleton*						m_pSkeleton;		/**< �X�P���g���̃|�C���^		*/
		std::string						m_name;				/**< ���O					*/
		KsInt32						m_id;				/**< �{�[��ID				*/
		KsUInt32						m_target;			/**< �`��^�[�Q�b�g			*/
		KsUInt32						m_flags;			/**< �e��t���O				*/
		KsInt32						m_parent;			/**< �e��ID					*/
		KsJointIDList					m_children;			/**< �q����ID���X�g			*/
		KsUserData*						m_pUserData;		/**< ���[�U�[�f�[�^			*/

		KsVector3d						m_initPivot;		/**< �����̊�_				*/
		KsVector3d						m_initTranslate;	/**< �����̈ʒu				*/
		KsQuaternion					m_initRotate;		/**< �����̉�]				*/
		KsVector3d						m_initScale;		/**< �����̃X�P�[��			*/

		KsVector3d						m_pivot;			/**< ��_					*/
		KsVector3d						m_translate;		/**< �ʒu					*/
		KsQuaternion					m_rotate;			/**< ��]					*/
		KsVector3d						m_scale;			/**< �X�P�[��				*/

		KsMatrix4x4					m_localMatrix;		/**< ���[�J���}�g���b�N�X		*/
		KsMatrix4x4					m_worldMatrix;		/**< ���[���h�}�g���b�N�X		*/
		KsMatrix4x4					m_stackMatrix;		/**< �}�g���b�N�X�X�^�b�N		*/
		KsVector3d						m_stackScale;		/**< �X�P�[���X�^�b�N			*/
};


class KsSkeleton;
class KsJoint;

typedef std::vector< KsInt32 >	KsJointIDList;


#endif

#endif		/* __KSJOINT_H__ */



