/************************************************************************************************/
/** 
 * @file		KsRenderSystemGL.h
 * @brief		GL
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEMPSP_H__
#define __KSRENDERSYSTEMPSP_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsRenderSystem.h"

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
		 * �R���X�g���N�^
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 */
											KsRenderSystemGL( HWND hWnd );

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
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil );

		/**
		 * �V�[���`��I��
		 */
		virtual void						endScene();

		/**
		 * �`��o�b�t�@�ƕ\���o�b�t�@�����ւ�
		 */
		virtual void						swapBuffer();

		/**
		 * �}�e���A�����Z�b�g����
		 * @param		pMaterial			�}�e���A��
		 */
		virtual void						setMaterial( KsMaterial* pMaterial ){}

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport			�r���[�|�[�g�ݒ�
		 */
		virtual void						setViewport( const KsViewport* pViewport ){}

		/**
		 * �g�����X�t�H�[������
		 * @param		state				�g�����X�t�H�[���̃��[�h
		 * @param		pMatrix				�ϊ��}�g���b�N�X
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix ){}

		/**
		 * �t�H�O���Z�b�g����
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density ){}


	private:
		/**
		 * �s�N�Z���t�H�[�}�b�g���Z�b�g����
		 * @retval		ksTRUE				����
		 * @retval		ksFALSE				���s
		 */
		KsBool								setupPixelFormat();

	private:
		KsBool								m_useStencilBuffer;		/**< �X�e���V���o�b�t�@���g�p���邩�ǂ���	*/
		HWND								m_hWnd;					/**< �E�C���h�E�̃n���h��					*/
		HDC									m_hDC;					/**< �f�o�C�X�R���e�L�X�g					*/
		HGLRC								m_hRC;					/**< �����_�����O�R���e�L�X�g				*/
};


#if 0
/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define stDISP_LIST_SIZE				( 0x80000 )		/**< �f�B�X�v���C���X�g�̃T�C�Y(512KB)	*/
#define stPROJ_MATRIX_STACK_SIZE		( 8 )			/**< �v���W�F�N�V�����s��̐�				*/
#define stVIEW_MATRIX_STACK_SIZE		( 32 )			/**< �r���[�s��̐�						*/
#define stWORLD_MATRIX_STACK_SIZE		( 8 )			/**< ���[���h�s��̐�						*/
#define stTEX_MATRIX_STACK_SIZE			( 4 )			/**< �e�N�X�`���s��̐�					*/

#define stRENDER_VIEWPORT_OFFSET_X		( 2048 )		/**< �r���[�|�[�g�����ʒu					*/
#define stRENDER_VIEWPORT_OFFSET_Y		( 2048 )		/**< �r���[�|�[�g�����ʒu					*/

#define stRENDER_CLEAR_COLOR			( 0x00000000 )	/**< �o�b�t�@�̃N���A����F				*/
#define stRENDER_CLEAR_DEPTH			( 0 )			/**< Z�o�b�t�@���N���A����l				*/
#define stRENDER_CLEAR_STENCIL			( 0 )			/**< �X�e���V���o�b�t�@���N���A����l		*/

/* �}�g���b�N�X�̃X�^�b�N�̃T�C�Y	*/
#define stMATRIX_STACK_SIZE	(	stPROJ_MATRIX_STACK_SIZE  + \
									stVIEW_MATRIX_STACK_SIZE  + \
									stWORLD_MATRIX_STACK_SIZE + \
									stTEX_MATRIX_STACK_SIZE )

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
class StRenderSystemPSP : public StRenderSystem
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											StRenderSystemPSP();
											
		/**
		 * �f�X�g���N�^
		 */
		virtual							~StRenderSystemPSP();

		/**
		 * ����������
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual StBool						initialize();

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual StBool						terminate();
		
		/**
		 * �V�[���`��J�n
		 */
		virtual void						beginScene();

		/**
		 * �V�[���`��I��
		 */
		virtual void						endScene();

		/**
		 * �`��o�b�t�@�ƕ\���o�b�t�@�����ւ�
		 */
		virtual void						swapBuffer();

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport			�r���[�|�[�g�ݒ�
		 */
		virtual void						setViewport( const StViewport* pViewport );

		/**
		 * �r���[�I�t�Z�b�g�l���Z�b�g����
		 * @param		offsetX				X���W�I�t�Z�b�g
		 * @param		offsetY				Y���W�I�t�Z�b�g
		 */
		virtual void						setViewOffset( StInt32 offsetX, StInt32 offsetY );

		/**
		 * �t�H�O���Z�b�g����
		 */
		virtual void						setFog( StReal zs, StReal ze, StUInt32 color );

		/*-------------------------------------<< �v���~�e�B�u�`��@�\�֌W >>--------------------------------------------------*/
		/**
		 * ���C����`��(2D)
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		color				�F
		 */
		virtual void						drawLine( StInt16 x0, StInt16 y0, StInt16 x1, StInt16 y1, StUInt32 color );

		/**
		 * �Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		color				�F
		 */
		virtual void						drawRect( StInt16 x, StInt16 y, StInt16 w, StInt16 h, StUInt32 color );

		/**
		 * �Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		tx					�e�N�X�`����X���W
		 * @param		ty					�e�N�X�`����Y���W
		 * @param		tw					�e�N�X�`���̕�
		 * @param		th					�e�N�X�`���̍���
		 * @param		color				�F
		 * @param		pTexture			�e�N�X�`��
		 */
		virtual void						drawRectEx( StInt16 x, StInt16 y, StInt16 w, StInt16 h, StUInt16 tx, StUInt16 ty, StUInt16 tw, StUInt16 th, StUInt32 color, StTexture* pTexture );

		/**
		 * �X�v���C�g�`��
		 * @param		pSpritePrim			�X�v���C�g�̃v���~�e�B�u(4�̒��_�z����킽���Ȃ��ƃo�O��)
		 */
		virtual void						drawSprite( ST_SPRITE_PRIM* pSpritePrim );

		/*------------------------------------------<< �e�N�X�`���֌W >>------------------------------------------------------*/
		/**
		 * �e�N�X�`���𐶐�����
		 * @param		pFileName			�t�@�C����
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		virtual StTexture*					createTexture( const StChar* pFileName, StUInt32 flags=0 );

		/**
		 * �C���[�W�f�[�^����e�N�X�`���𐶐�����
		 * @param		pImage				�C���[�W�f�[�^�̃|�C���^
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		virtual StTexture*					createTexture( StImage* pImage, StUInt32 flags=0 );

		/**
		 * �e�N�X�`�����Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		pTexture			�e�N�X�`��
		 */
		virtual void						setTexture(  StUInt32 stage, StTexture* pTexture );

		/**
		 * �e�N�X�`���X�e�[�g���Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		state				�Z�b�g����X�e�[�^�X�̎��
		 * @param		value				�Z�b�g����l
		 */
		virtual void						setTextureState( StUInt32 stage, stTEXTURE_STATE_TYPE state, StUInt32 value );

		/*-----------------------------------<< �}�e���A���֌W >>--------------------------------------------------*/
		/**
		 * �}�e���A�����Z�b�g����
		 * @param		pMaterial			�}�e���A��
		 */
		virtual void						setMaterial( StMaterial* pMaterial );

		/*-------------------------------------<< ���C�g�֌W >>--------------------------------------------------*/
		/**
		 * ���C�g��ǉ�����
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		pLight				���C�g���
		 * @note							���C�g��ݒu�ł��鐔�́A�ő�W�ł��B<br>
		 *									���C�g����菜�����Ƃ��͎�菜���������C�g�̃C���f�b�N�X�ƃ��C�g��NULL���Z�b�g���Ă��������B
		 */
		virtual void						setLight( StUInt32 index, const StLight* pLight );

		/**
		 * �w�胉�C�g��L���A�����ɂ���B
		 */
		virtual void						setLightEnable( StUInt32 index, StBool flag );

		/**
		 * ��{�I�ɐݒ��3D���[�h������������
		 */
		virtual void						auto2DMode();

		/**
		 * ��{�I�ɐݒ��3D���[�h������������
		 */
		virtual void						auto3DMode();

		/*-------------------------------------<< �����_�[�X�e�[�g�֌W >>--------------------------------------------------*/
		/**
		 * �����_�[�X�e�[�g
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		virtual void						setRenderState( stRENDER_STATE_TYPE state, StUInt32 value );

		/**
		 * �g�����X�t�H�[������
		 * @param		state				�g�����X�t�H�[���̃��[�h
		 * @param		pMatrix				�ϊ��}�g���b�N�X
		 */
		//virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix );

	private:
		void								setAlphaBlend( StBool value );
		void								setZTestEnable( StBool value );
		void								setFogEnable( StBool value );
		void								setZWriteEnable( StBool value );
		void								setAlphaTestEnable( StBool value );
		void								setLightEnable( StBool value );
		void								setShadeMode( stSHADE_MODE value );
		void								setCullMode( stCULL_MODE value );
		void								setBlendFunc( stBLEND_OP_MODE op, stBLEND_MODE src, stBLEND_MODE dst );

	private:
		KsTexture*							m_pCurrentTexture;
		//StUInt32							m_pixelFormat;
		//StInt32							m_width;
		//StInt32							m_height;
};
#endif


#endif		/* __STRENDERSYSTEMGL_H__ */

