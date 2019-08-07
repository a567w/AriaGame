/************************************************************************************************/
/** 
 * @file		KsSystem.h
 * @brief		�J���[
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYS_H__
#define __KSRENDERSYS_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsMaterial.h"
#include "KsMatrix.h"
#include "KsViewport.h"
//#include "KsFog.h"
#include "KsLight.h"

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksLIGHT_MAX		( 8 )		/**< ���C�g�̍ő吔		*/

enum ksTRANSFORM_STATE
{
	ksTRANSFORM_WORLD,
	ksTRANSFORM_VIEW,
	ksTRANSFORM_PROJECTION,
	//ksTRANSFORM_TEXTURE0,
	//ksTRANSFORM_TEXTURE1,
	//ksTRANSFORM_TEXTURE2,
	//ksTRANSFORM_TEXTURE3,
	//ksTRANSFORM_TEXTURE4,
	//ksTRANSFORM_TEXTURE5,
};

typedef enum _ksRENDER_STATE_TYPE
{

	ksRENDER_STATE_FORCE32 = 0x7fffffff,
}ksRENDER_STATE_TYPE;


typedef enum _ksRENDER_PRIM_TYPE
{

}ksRENDER_PRIM_TYPE;

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
class KsRenderSystem
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsRenderSystem(){}
											
		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsRenderSystem(){}

		/**
		 * ����������
		 * @param		hWnd				�E�C���h�E�̃n���h��
		 * @retval		ksTRUE				����������
		 * @retval		ksFALSE				���������s
		 */
		virtual KsBool						initialize( HWND hWnd ) = 0;

		/**
		 * �㏈��
		 * @retval		ksTRUE				�㏈������
		 * @retval		ksFALSE				�㏈�����s
		 */
		virtual KsBool						terminate() = 0;
		
		/**
		 * �V�[���`��J�n
		 */
		virtual void						beginScene() = 0;

		/**
		 * �V�[���`��I��
		 */
		virtual void						endScene() = 0;

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport			�r���[�|�[�g�ݒ�
		 */
		virtual void						setViewport( const KsViewport* pViewport ) = 0;


		/**
		 * �g�����X�t�H�[������
		 * @param		state				�g�����X�t�H�[���̃��[�h
		 * @param		pMatrix				�ϊ��}�g���b�N�X
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix ) = 0;

		/**
		 * �t�H�O���Z�b�g����
		 * @param		pFog				�t�H�O���Z�b�g����( NULL )���Z�b�g����ƃt�H�O�𖳌�
		 */
		//virtual void						setFog( const KsFog* pFog ) = 0;

		/**
		 * �e�N�X�`�����Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		pTexture			�e�N�X�`��
		 */
		virtual void						setTexture(  KsUInt32 stage, KsTexture* pTexture ) = 0;


		/**
		 * �}�e���A�����Z�b�g����
		 * @param		pMaterial			�}�e���A��
		 */
		virtual void						setMaterial( KsMaterial* pMaterial ) = 0;

#if 0
/*-------------------------------------<< ���C�g�֌W >>--------------------------------------------------*/
		/**
		 * ���C�g��ǉ�����
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		pLight				���C�g���
		 * @note							���C�g��ݒu�ł��鐔�́A�ő�W�ł��B<br>
		 *									���C�g����菜�����Ƃ��͎�菜���������C�g�̃C���f�b�N�X�ƃ��C�g��NULL���Z�b�g���Ă��������B
		 */
		virtual void						addLight( KsUInt32 index, const KsLight* pLight ) = 0;

		/**
		 * �w��C���f�b�N�X�̃��C�g���擾����
		 * @param		index				�C���f�b�N�X
		 * @return							���C�g�̃|�C���^(�Z�b�g����Ă��Ȃ��Ƃ���NULL���Ԃ�)
		 */
		virtual KsLight*					getLight( KsUInt32 index ) = 0;

		/**
		 * �w��C���f�b�N�X�̃��C�g���폜����
		 * @param		index				�C���f�b�N�X
		 * @return							�Z�b�g����Ă������C�g�̃|�C���^(�Ȃ��Ƃ��́ANULL���Ԃ�)
		 */
		virtual void						removeLight( KsUInt32 index ) = 0;

		/**
		 * ���ׂẴ��C�g���폜����
		 */
		virtual void						removeAllLight() = 0;

		/**
		 * �w�胉�C�g��L���A�����ɂ���B
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag ) = 0;
/*-------------------------------------<< �����_�[�X�e�[�g�֌W >>--------------------------------------------------*/

		/**
		 * �����_�[�X�e�[�g���X�^�b�N�Ƀv�b�V������
		 */
		virtual void						pushRenderState() = 0;

		/**
		 * �����_�[�X�e�[�g���X�^�b�N�Ƀ|�b�v����
		 */
		virtual void						popRenderState() = 0;

		/**
		 * �����_�[�X�e�[�g
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value ) = 0;

/*-------------------------------------<< �v���~�e�B�u�`��@�\�֌W >>--------------------------------------------------*/
#endif

		/**
		 * �`�揈��
		 * @param			pVetices
		 */
		//virtual void				drawIndexedPrimitive( ksPRIMITIVE_TYPE type, const KsVertex* pVertices, KsUInt32 numVertex, const KsUInt16* pIndeces, KsUInt32 primitiveCount );
		//virtual void				drawIndexedTriangleList( const KsVertex* pVertices, KsUInt32 numVertex, const KsUInt16* pIndeces, KsUInt32 primitiveCount );
		//virtual void				drawLine( const KsVector3d& start, const KsVector3d& end, KsColor color);

	protected:
		KsMatrix							m_viewMatrix;					/**< �r���[�}�g���b�N�X		*/
		KsMatrix							m_worldMatrix;					/**< ���[���h�}�g���b�N�X		*/
		KsMatrix							m_textureMatrix;				/**< �e�N�X�`���}�g���b�N�X	*/
		KsLight*							m_pLights[ ksLIGHT_MAX ];		/**< ���C�g					*/
		//KsFog								m_fog;							/**< �t�H�O					*/
		KsViewport							m_viewport;						/**< �r���[�|�[�g			*/
};








#if 0
    D3DPT_POINTLIST = 1,
    D3DPT_LINELIST = 2,
    D3DPT_LINESTRIP = 3,
    D3DPT_TRIANGLELIST = 4,
    D3DPT_TRIANGLESTRIP = 5,
    D3DPT_TRIANGLEFAN = 6,
    D3DPT_FORCE_DWORD = 0x7fffffff
D3DPT_POINTLIST
���_���X�̓_�̏W���Ƃ��ă����_�����O����B���̒l�́A�C���f�b�N�X�t���v���~�e�B�u�ł̓T�|�[�g����Ȃ��B

D3DPT_LINELIST
�X�̐����̃��X�g�Ƃ��Ē��_�������_�����O����B���̃v���~�e�B�u �^�C�v���g���Ăяo���́A���̌��� 2 ��菬�������A��̏ꍇ�͎��s����B 

D3DPT_LINESTRIP
�P��̃|�����C���Ƃ��Ē��_�������_�����O����B���̃v���~�e�B�u �^�C�v���g���Ăяo���́A���̌��� 2 ��菬�����ꍇ�͎��s����B 

D3DPT_TRIANGLELIST
�X�̎O�p�`�̘A���Ƃ��Ďw��̒��_�������_�����O����B�e 3 �̒��_�̃O���[�v�͌ʂɎO�p�`���`����B

�w�ʂ̃J�����O�́A���݂̃J�����O ���[�h �����_�����O �X�e�[�g�̉e�����󂯂�B


D3DPT_TRIANGLESTRIP
���_���O�p�`�X�g���b�v�Ƃ��ă����_�����O����B�w�ʃJ�����O �t���O�́A�����ԍ��̎O�p�`�Ŏ����I�ɔ��]����B 

D3DPT_TRIANGLEFAN
���_���O�p�`�t�@���Ƃ��ă����_�����O����B 

D3DPT_FORCE_DWORD
���̗񋓌^�������I�� 32 �r�b�g �T�C�Y�ɃR���p�C������B���̒l�͎g���Ă��Ȃ��B
	
		
		//virtual void				drawBox( const KsBox& box

		virtual void				draw3DLine(const core::vector3df& start, const core::vector3df& end, SColor color = SColor(255,255,255,255));

		//! Draws a 3d triangle.
		virtual void draw3DTriangle(const core::triangle3df& triangle,
			SColor color = SColor(255,255,255,255));

		//! Draws a 3d axis aligned box.
		virtual void draw3DBox(const core::aabbox3d<f32> box,
			SColor color = SColor(255,255,255,255));

		//! draws an 2d image
		virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos);

		//! draws an 2d image, using a color (if color is other then Color(255,255,255,255)) and the alpha channel of the texture if wanted.
		virtual void draw2DImage(video::ITexture* texture, const core::position2d<s32>& destPos, 
			const core::rect<s32>& sourceRect, const core::rect<s32>* clipRect = 0,
			SColor color=SColor(255,255,255,255), bool useAlphaChannelOfTexture=false);

		//! draw an 2d rectangle
		virtual void draw2DRectangle(SColor color, const core::rect<s32>& pos, const core::rect<s32>* clip = 0);

		//! Draws a 2d line. 
		virtual void draw2DLine(const core::position2d<s32>& start,
								const core::position2d<s32>& end, 
								SColor color=SColor(255,255,255,255));

void CVideoOpenGL::loadExtensions()
{
	KsReal	version = atof( (KsChar*)glGetString( GL_VERSION ) );

	if( version >= 1.2f ){
		
	}
	else{
		/* OpenGL�̃o�[�W�������Â� */
	}

	const GLubyte* t = glGetString(GL_EXTENSIONS);
	s32 len = (s32)strlen((const char*)t);
	c8 *str = new c8[len+1];
	c8* p = str;

	for (s32 i=0; i<len; ++i)
	{
		str[i] = (char)t[i];

		if (str[i] == ' ')
		{
			str[i] = 0;
			if (strstr(p, "GL_ARB_multitexture"))
			{
				MultiTextureExtension = true;
				break;
			}

			p = p + strlen(p) + 1;
		}
	}

	delete [] str;

	if (MultiTextureExtension)
	{
		glActiveTextureARB   = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");
		if (!glActiveTextureARB || !glClientActiveTextureARB)
		{
			MultiTextureExtension = false;
			os::Printer::log("Failed to load OpenGL's multitexture extension, proceeding without.", ELL_WARNING);
		}

		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &MaxTextureUnits);
	}

	if (MaxTextureUnits < 2)
	{
		MultiTextureExtension = false;
		os::Printer::log("Warning: OpenGL device only has one texture unit. Disabling multitexturing.", ELL_WARNING);
	}
}

#endif


#endif		/* __KSRENDERSYS_H__ */