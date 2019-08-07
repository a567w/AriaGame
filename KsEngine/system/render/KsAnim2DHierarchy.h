/************************************************************************************************/
/** 
 * @file		KsAnimKeyFrame.h
 * @brief		�{�[��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIM2DHIERARCHY_H__
#define __KSANIM2DHIERARCHY_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsCore.h"
#include "KsColor.h"
#include "KsVector.h"
#include "KsArray.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsAnim2DJoint;

#if 0

/************************************************************************************************/
/**
 * @class		KsAnim2DHierarchy
 * @brief		�K�w�\��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DHierarchy
{
		typedef KsArray< KsAnim2DJoint* >	KsAnim2DJointArray;

	public:
		/**
		 * �R���X�g���N�^
		 */
								KsAnim2DHierarchy();

		/**
		 * �f�X�g���N�^
		 */
		virtual				~KsAnim2DHierarchy();

		/**
		 * ���[�g�W���C���g�����擾����
		 * @return				���[�g�W���C���g��
		 */
		KsUInt32				getNumRootJoint() { return m_vpRootJoints.size(); }

		/**
		 * ���[�g�W���C���g���擾����
		 * @param	index		���[�g�W���C���g�C���f�b�N�X
		 * @return				�w��̃��[�g�W���C���g�̃|�C���^
		 */
		KsAnim2DJoint*			getRootJoint( KsUInt32 index=0 ) { return m_vpRootJoints[ index ]; }

		/**
		 * �W���C���g�����擾����
		 * @return				�W���C���g��
		 */
		KsUInt32				getNumJoint() { return m_vpJoints.size(); }

		/**
		 * �W���C���g���擾����
		 * @param	index		�C���f�b�N�X
		 * @return				�w��W���C���g�̃|�C���^
		 */
		KsAnim2DJoint*			getJoint( KsUInt32 index ) { return m_vpJoints[ index ]; }

		/** 
		 * �W���C���g����������
		 * @param	id			ID
		 * @return				�w��W���C���g�̃|�C���^
		 */
		KsAnim2DJoint*			findJoint( KsInt32 id );

		/**
		 * �q���̍X�V����
		 * @param	pJoint		�W���C���g
		 * @param	pParent		�e�W���C���g
		 */
		void					updateChild( KsAnim2DJoint* pJoint, const KsAnim2DJoint* pParent );

		/**
		 * �X�V����
		 * @param	pCtrlJoint	�R���g���[���W���C���g
		 */
		void					update( const KsAnim2DJoint* pCtrlJoint=NULL );

		/**
		 * �K�w��j������
		 */
		void					destroy();

	public:
		KsAnim2DJointArray		m_vpRootJoints;	/**< ���[�g�ɂȂ�W���C���g���X�g			*/
		KsAnim2DJointArray		m_vpJoints;		/**< �W���C���g���X�g(���ׂẴW���C���g)	*/
};

#endif

#endif /* __KSANIM2DHIERARCHY_H__ */

