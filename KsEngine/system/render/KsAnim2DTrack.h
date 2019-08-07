/************************************************************************************************/
/** 
 * @file		KsAnimTrack.h
 * @brief		�{�[��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIM2DTRACK_H__
#define __KSANIM2DTRACK_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsArray.h"
#include "KsAnim2DKeyFrame.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsAnim2DObject;

/************************************************************************************************/
/**
 * @class		KsAnimTrack
 * @brief		�A�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DTrack
{
		typedef KsArray<KsAnim2DKeyFrame*> KsAnim2DKeyFrameArray;

	public:
		/**
		 * �L�[�t���[�������擾����
		 * @return				�L�[�t���[����
		 */
		KsInt32				getNumKeyFrame() const { return static_cast<KsInt32>( m_vKeyFrames.size() ); }

		/**
		 * �^�[�Q�b�g�W���C���g���擾����
		 * @return				�^�[�Q�b�g�W���C���g
		 */
		const KsAnim2DObject*	getTarget() { return m_pTarget; }

		/**
		 * �ő�g���b�N���Ԃ��擾����
		 * @return				�ő�g���b�N����
		 */
		KsReal					getMaxTime() const { return m_maxTime; }

		/**
		 * �w�莞�Ԃ̃L�[�t���[�����擾����
		 * @param	time		�w�莞�� ( in )
		 * @param	pParam		�p�����[�^ ( out ) [ 0.0f ... 1.0f ]
		 * @param	pKey1		�L�[�t���[��1( out )
		 * @param	pKey2		�L�[�t���[��2( out )
		 * @return				�w��L�[�t���[���̏��
		 */
		KsInt32				getKeyFrame( KsReal time, KsReal *pParam, KsAnim2DKeyFrame* pKey1, KsAnim2DKeyFrame* pKey2, KsBool bLoop=ksFALSE );

		/**
		 * �w��C���f�b�N�X�̃L�[�t���[�����擾����
		 * @return				�L�[�t���[��
		 */
		KsAnim2DKeyFrame*		getKeyFrame( KsInt32 index ) const { return m_vKeyFrames[ index ]; }

	public:
		KsAnim2DKeyFrameArray	m_vKeyFrames;	/**< �L�[�t���[�����X�g		*/
		KsAnim2DObject*			m_pTarget;		/**< �^�[�Q�b�g�W���C���g	*/
		KsReal					m_maxTime;		/**< �ő�g���b�N����		*/
};


#endif /* __KSANIM2DTRACK_H__ */

