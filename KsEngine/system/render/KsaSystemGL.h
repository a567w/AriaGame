/************************************************************************************************/
/** 
 * @file		KsSystemGL.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSGL_H__
#define __KSRENDERSYSGL_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsSystem.h"
/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/


/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsRenderSystemGL
 * @brief		OpenGL�p�̕`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderSystemGL : public KsRenderSystem
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsRenderSystemGL();
											
		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsRenderSystemGL();

		/**
		 * ����������
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual KsBool						initialize( HWND hWnd );

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual KsBool						terminate();
		
		/**
		 * �V�[���`��J�n
		 */
		virtual void						beginScene();

		/**
		 * �V�[���`��I��
		 */
		virtual void						endScene();

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport			�r���[�|�[�g�ݒ�
		 */
		virtual void						setViewport( const KsViewport* pViewport );


		/**
		 * �g�����X�t�H�[������
		 * @param		state				�g�����X�t�H�[���̃��[�h
		 * @param		pMatrix				�ϊ��}�g���b�N�X
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix );

		/**
		 * �t�H�O���Z�b�g����
		 * @param		pFog				�t�H�O���Z�b�g����( NULL )���Z�b�g����ƃt�H�O�𖳌�
		 */
		//virtual void						setFog( const KsFog* pFog );

		/**
		 * �e�N�X�`�����Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		pTexture			�e�N�X�`��
		 */
		virtual void						setTexture(  KsUInt32 stage, KsTexture* pTexture );


		/**
		 * �}�e���A�����Z�b�g����
		 * @param		pMaterial			�}�e���A��
		 */
		virtual void						setMaterial( KsMaterial* pMaterial );

/*-------------------------------------<< ���C�g�֌W >>--------------------------------------------------*/
		/**
		 * ���C�g��ǉ�����
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		pLight				���C�g���
		 * @note							���C�g��ݒu�ł��鐔�́A�ő�W�ł��B<br>
		 *									���C�g����菜�����Ƃ��͎�菜���������C�g�̃C���f�b�N�X�ƃ��C�g��NULL���Z�b�g���Ă��������B
		 */
		virtual void						addLight( KsUInt32 index, const KsLight* pLight );

		/**
		 * �w��C���f�b�N�X�̃��C�g���擾����
		 * @param		index				�C���f�b�N�X
		 * @return							���C�g�̃|�C���^(�Z�b�g����Ă��Ȃ��Ƃ���NULL���Ԃ�)
		 */
		virtual KsLight*					getLight( KsUInt32 index );

		/**
		 * �w��C���f�b�N�X�̃��C�g���폜����
		 * @param		index				�C���f�b�N�X
		 * @return							�Z�b�g����Ă������C�g�̃|�C���^(�Ȃ��Ƃ��́ANULL���Ԃ�)
		 */
		virtual void						removeLight( KsUInt32 index );

		/**
		 * ���ׂẴ��C�g���폜����
		 */
		virtual void						removeAllLight();

		/**
		 * �w�胉�C�g��L���A�����ɂ���B
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag );
/*-------------------------------------<< �����_�[�X�e�[�g�֌W >>--------------------------------------------------*/

		/**
		 * �����_�[�X�e�[�g���X�^�b�N�Ƀv�b�V������
		 */
		virtual void						pushRenderState();

		/**
		 * �����_�[�X�e�[�g���X�^�b�N�Ƀ|�b�v����
		 */
		virtual void						popRenderState();

		/**
		 * �����_�[�X�e�[�g
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value );

/*-------------------------------------<< �v���~�e�B�u�`��@�\�֌W >>--------------------------------------------------*/
	protected:
		/**
		 * �s�N�Z���t�H�[�}�b�g���Z�b�g�A�b�v����
		 */
		KsBool								setupPixelFormat();

		/**
		 * OpenGL�̊g�����Z�b�g�A�b�v����
		 */
		//void								setupExtensions();

		/**
		 * �R�c�̃����_�[�X�e�[�g���[�h�f�t�H���g�ŃZ�b�g����
		 */
		//void								setRenderStates3D();

	protected:
		KsBool								m_useStencilBuffer;		/**< �X�e���V���o�b�t�@���g�p���邩�ǂ���	*/
		HWND								m_hWnd;					/**< �E�C���h�E�̃n���h��					*/
		HDC									m_hDC;					/**< �f�o�C�X�R���e�L�X�g					*/
		HGLRC								m_hRC;					/**< �����_�����O�R���e�L�X�g				*/
};

#endif		/* __KSRENDERSYSGL_H__ */