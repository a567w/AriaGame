/************************************************************************************************/
/** 
 * @file		KsKeyFrame.h
 * @brief		�L�[�t���[���f�[�^
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSKEYFRAME_H__
#define __KSKEYFRAME_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsKeyFrame
 * @brief		�L�[�t���[���f�[�^
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsKeyFrame
{
	private:
		KsInt32						m_time;				/**< ����			*/
		KsVector3d					m_scale;			/**< �X�P�[���l		*/
		KsVector3d					m_translate;		/**< �ړ��l			*/
		KsQuaternion				m_rotation;			/**< ��]�l			*/
		KsMatrix4x4					m_transform;		/**< �ϊ��s��		*/
		KsBezier					m_bezierX;			/**< X���ړ����		*/
		KsBezier					m_bezierY;			/**< Y���ړ����		*/
		KsBezier					m_bezierZ;			/**< Z���ړ����		*/
		KsBezier					m_bezierAngle;		/**< ��]���		*/

	public:
		/**
		 * �R���X�g���N�^
		 */
		KsKeyFrame();

		/**
		 * �R���X�g���N�^
		 */
		KsKeyFrame( const KsVector3d& translate, KsInt32 time );

		/**
		 * �R���X�g���N�^
		 */
		KsKeyFrame( const KsQuaternion& rotation, KsInt32 time );

		/**
		 * �R���X�g���N�^
		 */
		KsKeyFrame( const KsVector3d& translate, const KsQuaternion& rotation, const KsVector3d& scale, KsInt32 time );

		/**
		 * �R���X�g���N�^
		 */
		KsKeyFrame( const KsVector3d& translate, const KsQuaternion& rotation, KsInt32 time );

		/**
		 * �R���X�g���N�^
		 */
		KsKeyFrame( const KsMatrix4x4& transform, KsInt32 time );

		/**
		 * �f�X�g���N�^
		 */
		~KsKeyFrame();

		void						setBezierX( KsReal val0, KsReal val1, KsReal val2, KsReal val3 );
		void						setBezierY( KsReal val0, KsReal val1, KsReal val2, KsReal val3 );
		void						setBezierZ( KsReal val0, KsReal val1, KsReal val2, KsReal val3 );
		void						setBezierAngle( KsReal val0, KsReal val1, KsReal val2, KsReal val3 );

		KsInt32						getTime() const { return m_time; }

		const KsVector3d&			getScale() { return m_scale; }

		const KsVector3d&			getTranslate() { return m_translate; }

		const KsQuaternion&			getRotation() { return m_rotation; }

		const KsBezier&				getBezierX() { return m_bezierX; }
		const KsBezier&				getBezierY() { return m_bezierY; }
		const KsBezier&				getBezierZ() { return m_bezierZ; }
		const KsBezier&				getBezierAngle() { return m_bezierAngle; }
};

#endif /* __KSKEYFRAME_H__ */

