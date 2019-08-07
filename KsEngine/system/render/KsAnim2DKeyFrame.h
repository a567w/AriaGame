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
#ifndef __KSANIM2DKEYFRAME_H__
#define __KSANIM2DKEYFRAME_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsCore.h"
#include "KsColor.h"
#include "KsVector.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsAnim2DKeyFrame
 * @brief		�A�j���[�V����
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DKeyFrame
{
	public:
		/**
		 * �R���X�g���N�^
		 */
								KsAnim2DKeyFrame();

		/**
		 * �f�X�g���N�^
		 */
		virtual				~KsAnim2DKeyFrame();

		/**
		 * �t���[���Đ����Ԃ��擾����
		 * @return				�t���[���Đ�����
		 */
		KsReal					getTime() const { return m_time; }

		/**
		 * �ʒu���W���擾����
		 * @return				�ʒu���W
		 */
		const KsVector2d		getPos()	{ return m_pos; }

		/**
		 * �X�P�[�����擾����
		 * @return				�X�P�[��
		 */
		const KsVector2d		getScale()	{ return m_scale; }

		/**
		 * �t���[���Đ����Ԃ��Z�b�g����
		 * @param	time		�t���[���Đ�����
		 */
		void					setTime( KsReal time )  { m_time = time; }

		/**
		 * �ʒu���W���Z�b�g����
		 * @param	pos		�ʒu���W
		 */
		void					setPos( const KsVector2d& pos )	{ m_pos = pos; }

		/**
		 * ��]�l���Z�b�g����
		 * @param	rot			��]�l
		 */
		void					setAngle( KsReal angle )	{ m_angle = angle; }

		/**
		 * �X�P�[���l���Z�b�g����
		 * @param	scale		�X�P�[���l
		 */
		void					setScale( const KsVector2d& scale )	{ m_scale = scale; }

	public:
		KsUInt32				m_flags;		/**< �t���O				*/
		KsReal					m_time;			/**< �t���[���Đ�����	*/
		KsVector2d				m_pos;			/**< �ʒu���W			*/
		KsVector2d				m_scale;		/**< �X�P�[��			*/
		KsReal					m_angle;		/**< ��]				*/
		KsColor					m_color;		/**< �J���[				*/
		KsVector4d				m_uv;			/**< �e�N�X�`�����W		*/
		//KsInt32				m_texId;
		//KsString				m_texName;
		//KsUserData*				m_pUserData;	/**< ���[�U�[�f�[�^		*/
};


#endif /* __KSANIM2DKEYFRAME_H__ */

