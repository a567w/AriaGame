/************************************************************************************************/
/** 
 * @file		KsKeyFrame.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSKEYFRAME_H__
#define __KSKEYFRAME_H__

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
 * 
 * @class	
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsKeyFrame
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsKeyFrame() : m_time( 0.0f ) { m_scale.x = 1.0f; m_scale.y = 1.0f; m_scale.z = 1.0f; }

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsKeyFrame(){}

		KsReal							GetTime() const { return m_time; }
		const KsVector3d				GetPos()	{ return m_pos; }
		const KsQuaternion				GetRot()	{ return m_rot; }
		const KsVector3d				GetScale()	{ return m_scale; }

		void							SetTime( KsReal time ) const { m_time = time; }
		void							SetPos( const KsVector3d& pos )	{ m_pos = pos; }
		void							SetRot( const KsQuaternion& rot )	{ m_rot = rot; }
		void							SetScale( const KsVector3d& scale )	{ m_scale = scale; }

	protected:
		KsReal							m_time;		/**< ����		*/
		KsVector3d						m_pos;		/**< �ʒu		*/
		KsQuaternion					m_rot;		/**< ��]		*/
		KsVector3d						m_scale;	/**< �X�P�[��	*/
};

class KsAnim
{
	private:
		typedef std::vector< KsKeyFrame* >		KsKeyFrameList;

		/**
		 * �A�j���̕⊮�̎��
		 */
		enum ksANIM_INTERPOLATE_KIND
		{
			ksANIM_INTERPOLATE_LINEAR,		/**< �����⊮		*/
			ksANIM_INTERPOLATE_SPLINE,		/**< �X�v���C���⊮	*/
			// �G���~�[�g�⊮
		};

	public:
		/**
		 * �R���X�g���N�^
		 */
										KsAnim();

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsAnim();

		/**
		 * �L�[�t���[����ǉ�����
		 * @param		pFrame			�ǉ�����L�[�t���[��
		 */
		void							AddKeyFrame( const KsKeyFrame* pFrame );

		/**
		 * �X�V����
		 * @param		dt				�X�V����
		 * @note		���Ԃ�,[ 0.0f���1.0f ]�ŊǗ�����
		 */
		void							Update( KsReal dt );

	protected:
		KsInt32							m_id;				/**< ID									*/
		KsInt32							m_startKeyFrame;	/**< �J�n�L�[�t���[��					*/
		KsInt32							m_lastKeyFrame;		/**< �I���L�[�t���[��					*/
		KsInt32							m_nextKeyFrame;		/**< ���̃L�[�t���[��					*/
		KsReal							m_totalTime;		/**< �g�[�^������						*/
		KsReal							m_currentTime;		/**< ���݂̎���							*/
		KsReal							m_offsetTime;		/**< 0.0f����1.0f�̊Ԃɂ���܂ł̕␳�l	*/
		KsKeyFrameList					m_vKeyFrames;		/**< �L�[�t���[�����X�g					*/
};


#endif		/* __KSKEYFRAME_H__ */
