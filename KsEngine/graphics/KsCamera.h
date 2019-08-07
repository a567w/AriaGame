/************************************************************************************************/
/** 
 * @file		KsCamera.h
 * @brief		�J����
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSCAMERA_H__
#define __KSCAMERA_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/
#include "KsCameraObject.h"
#include "KsColor.h"
#include "KsViewport.h"

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/
class KsRenderSystem;

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsCamera
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsCamera : public KsCameraObject
{
	public:
		/** 
		 * �v���W�F�N�V�����̃^�C�v
		 */
		enum ksPROJECTION_TYPE
		{
			ksORTHOGRAPHIC,		/**< ���ˉe		*/
			ksPERSPECTIVE,		/**< �����ˉe	*/
		};

		/** 
		 * ���W�n
		 */
		enum ksCOORDINATE_TYPE
		{
			ksCOORD_RIGHT,		/**< �E��n		*/
			ksCOORD_LEFT,		/**< ����n		*/
		};

	protected:
		/**
		 * �X�V�t���O
		 */
		enum ksCAMERA_UPDATE_FLAG
		{
			ksNONE_UPDATE       = ( 0 ),
			ksVIEWPORT_UPDATE   = ( 1 << 0 ),
			ksPROJECTION_UPDATE = ( 1 << 1 ),
			ksVIEWMATRIX_UPDATE = ( 1 << 2 ),
			ksFRUSUM_UPDATE     = ( 1 << 3 ),
			ksUPDATE_FORCE32    = ( 0x7fffffff ),
		};

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsCamera();

		/**
		 * �R���X�g���N�^
		 * @param	pRenderSystem	�`��V�X�e��
		 */
									KsCamera( KsRenderSystem* pRenderSystem );

		/** 
		 * �f�X�g���N�^
		 */
		virtual						~KsCamera();

		/**
		 * �J�����̃N���[������
		 * @return					�N���[�����ꂽ�J����
		 */
		//virtual KsCamera*			clone();

		/**
		 * ���W�n�̃^�C�v���Z�b�g����
		 * @param	type			���W�n�̃^�C�v
		 */
		void						setCoordinateType( ksCOORDINATE_TYPE type );

		/**
		 * �J�����̍X�V����
		 */
		virtual void				update();

		/**
		 * �`��J�n
		 */
		virtual void				beginRender();

		/**
		 * �`��I��
		 */
		virtual void				endRender();

		/**
		 * �����ˉe�s��𐶐�����
		 * @param		fovy		����p
		 * @param		aspect		�A�X�y�N�g��
		 * @param		zNear		�ߋ����l
		 * @param		zFar		�������l
		 */
		void						setPerspective( KsReal fovy, KsReal aspect, KsReal zNear, KsReal zFar );

		/**
		 * ���ˉe�s��𐶐�����
		 * @param		projMatrix	�v���W�F�N�V�����}�g���b�N�X�ۑ��p
		 * @param		left		���t�g
		 * @param		right		���C�g
		 * @param		bottom		�{�g��
		 * @param		top			�g�b�v
		 * @param		aspect		�A�X�y�N�g��
		 * @param		zNear		�ߋ����l
		 * @param		zFar		�������l
		 */
		void						setOrtho( KsReal left, KsReal right, KsReal bottom, KsReal top, KsReal zNear, KsReal zFar );

		/**
		 * �r���[�|�[�g�̃Z�b�g
		 * @param		x			X���W
		 * @param		y			X���W
		 * @param		w			��
		 * @param		h			����
 		 * @param		near		near�N���b�v�l
		 * @param		far			far�N���b�v�l
		 */
		void						setViewport( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsReal minZ, KsReal maxZ );

		/**
		 * �r���[�|�[�g�̃Z�b�g
		 * @param		viewport	�r���[�|�[�g
		 */
		void						setViewport( const KsViewport& viewport );

		/**
		 * �r���[�|�[�g�̂��擾
		 * @return					�r���[�|�[�g��
		 */
		const KsViewport&			getViewport() { return m_viewport; }

		/**
		 * �J�����`��
		 * @param	pFrustum		�t���X�^��(����)�`�F�b�N(NULL�Ȃ玩���̃t���X�^�����g�p����)
		 * @param	bForce			�����`��t���O
		 * @return					true if successful, false if error
		 */
//		KsBool						render( KsFrustum* pFrustum = 0, KsBool bForce = ksFALSE );

		/**
		 * �J������Look-At���Z�b�g����
		 * @param	eye				���_�ʒu
		 * @param	target			�^�[�Q�b�g
		 * @param	up				up �x�N�g��
		 * @note					�J�����̍X�V��beginRender�̂Ƃ��܂���update���Ăяo���Ȃ��ƍX�V����܂���B
		 */
		void						lookAt( const KsVector3d& eye, const KsVector3d& target, const KsVector3d& up );

		/**
		 * �r���[�}�g���b�N�X���Z�b�g����
		 * @param	viewMatrix		�r���[�}�g���b�N�X
		 */
		void						setViewMatrix( const KsMatrix4x4& viewMatrix ) { m_viewMatrix = viewMatrix; m_updateFlag |= ksVIEWMATRIX_UPDATE; }

		/**
		 * ���̃J�����̃v���W�F�N�V�����}�g���b�N�X���擾
		 * @return					�v���W�F�N�V�����}�g���b�N�X
		 */
		const KsMatrix4x4&			getProjMatrix() { return m_projMatrix; }

		/**
		 * ���̃J�����̃v���W�F�N�V�����}�g���b�N�X�̋t�s����擾
		 * @return					�v���W�F�N�V�����}�g���b�N�X�̋t�s��
		 */
		KsMatrix4x4					getInverseProjMatrix() { return m_projMatrix.inverse(); }

		/**
		 * ���̃J�����̃r���[�}�g���b�N�X���擾
		 * @return					�r���[�}�g���b�N�X
		 */
		const KsMatrix4x4&			getViewMatrix() { return m_viewMatrix; }

		/**
		 * ���̃J�����̃r���[�}�g���b�N�X�̋t�s����擾
		 * @return					�r���[�}�g���b�N�X�̋t�s��
		 */
		KsMatrix4x4					getInverseViewMatrix() { return m_viewMatrix.inverse(); }

		/**
		 * ���̃J�����̃r���[�v���W�F�N�V�����}�g���b�N�X���擾
		 * @return					�r���[�v���W�F�N�V�����}�g���b�N�X
		 */
		const KsMatrix4x4&			getViewProjMatrix() { return m_viewProjMatrix; }

		/**
		 * ���̃J�����̃r���[�v���W�F�N�V�����}�g���b�N�X�̋t�s����擾
		 * @return					�r���[�v���W�F�N�V�����}�g���b�N�X�̋t�s��
		 */
		KsMatrix4x4					getInverseViewProjMatrix() { return m_viewProjMatrix.inverse(); }

		/**
		 * �����̃J�������A�N�e�B�u�J�����ɃZ�b�g����
		 */
		void						setActive() { s_pActiveCamera = this; }

		/**
		 * �A�N�e�B�u�J�������擾����
		 * @return					�A�N�e�B�u�J����
		 */
		static KsCamera*			getActive() { return s_pActiveCamera; }

		/**
		 * �A�X�y�N�g����擾����
		 * @return					�A�X�y�N�g��
		 */
		KsReal						getAspect() const { return m_aspect; }

		/**
		 * �v���W�F�N�V������Near���擾����
		 * @return					�v���W�F�N�V������Near
		 */
		KsReal						getNear() const { return m_zNear; }

		/**
		 * �v���W�F�N�V������Far���擾����
		 * @return					�v���W�F�N�V������Far
		 */
		KsReal						getFar() const { return m_zFar; }

	protected:
		KsUInt32					m_updateFlag;		/**< �J�����̍X�V���K�v���ǂ���			*/
		ksCOORDINATE_TYPE			m_coordinateType;	/**< ���W�n�̃^�C�v					*/
		ksPROJECTION_TYPE			m_projectionType;	/**< �v���W�F�N�V�����̃^�C�v			*/
		KsUInt32					m_clearFlags;		/**< �N���A�t���O						*/
		KsColor						m_clearColor;		/**< �N���A�[�J���[					*/
		KsReal						m_clearDepth;		/**< �N���A�[����[�x�l				*/
		KsUInt32					m_clearSstencil;	/**< �N���A�[����X�e���V���l			*/
		KsViewport					m_viewport;			/**< �r���[�|�[�g						*/
		KsReal						m_fovy;				/**< ����p							*/
		KsReal						m_aspect;			/**< �A�X�y�N�g��						*/
		KsReal						m_right;			/**< right(���ˉe�p)					*/
		KsReal						m_left;				/**< left(���ˉe�p)					*/
		KsReal						m_top;				/**< top(���ˉe�p)					*/
		KsReal						m_bottom;			/**< bottom(���ˉe�p)					*/
		KsReal						m_zNear;			/**< �v���W�F�N�V������Near			*/
		KsReal						m_zFar;				/**< �v���W�F�N�V������Far				*/
		KsMatrix4x4					m_projMatrix;		/**< �v���W�F�N�V�����}�g���b�N�X		*/
		KsMatrix4x4					m_viewMatrix;		/**< �r���[�}�g���b�N�X				*/
		KsMatrix4x4					m_viewProjMatrix;	/**< �r���[�v���W�F�N�V�����}�g���b�N�X	*/
		KsFrustum					m_frustum;			/**< �t���X�^��						*/
		KsRenderSystem*				m_pRenderSystem;	/**< �`��V�X�e���̃|�C���^				*/
		static KsCamera*			s_pActiveCamera;	/**< ���݂̃A�N�e�B�u�J����				*/
};


#endif		/* __KSCAMERA_H__ */

