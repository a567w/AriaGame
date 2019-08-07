/************************************************************************************************/
/** 
 * @file		KsRenderSystem.h
 * @brief		�`��V�X�e��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERSYSTEM_H__
#define __KSRENDERSYSTEM_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsColor.h"
#include "KsLight.h"
#include "KsMaterial.h"
#include "KsViewport.h"
#if 0
#include "KsTexture.h"
#include "ksImage.h"
#include "KsMatrix.h"
#include "KsVertexBuffer.h"
#include "KsIndexBuffer.h"
#endif

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/
#define ksLIGHT_MAX						( 4 )		/**< ���C�g�̍ő吔					*/
#define ksRENDER_STATE_STACK_MAX		( 8 )		/**< �����_�[�X�e�[�g�X�^�b�N�ő吔	*/

/* �N���A�[�r�b�g */
#define ksCLEAR_FLAG_COLOR				( 1<<0 )	/**< �J���[�N���A�t���O				*/
#define ksCLEAR_FLAG_DEPTH				( 1<<1 )	/**< �[�x�o�b�t�@�N���A�t���O			*/
#define ksCLEAR_FLAG_STENCIL			( 1<<2 )	/**< �X�e���V���o�b�t�@�N���A�t���O	*/
#define ksCLEAR_FLAG_ACCUM				( 1<<3 )	/**< �A�L���[�����t�o�b�t�@			*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * �g�����X�t�H�[���̎��
 */
/************************************************************************************************/
typedef enum _ksTRANSFORM_STATE
{
	ksTRANSFORM_WORLD,				/**< ���[���h					*/
	ksTRANSFORM_VIEW,				/**< �r���[						*/
	ksTRANSFORM_PROJECTION,			/**< �v���W�F�N�V����				*/
	ksTRANSFORM_TEXTURE0,			/**< �e�N�X�`��0					*/
	ksTRANSFORM_TEXTURE1,			/**< �e�N�X�`��1					*/
	ksTRANSFORM_TEXTURE2,			/**< �e�N�X�`��2					*/
	ksTRANSFORM_TEXTURE3,			/**< �e�N�X�`��3					*/
	ksTRANSFORM_TEXTURE4,			/**< �e�N�X�`��4					*/
	ksTRANSFORM_TEXTURE5,			/**< �e�N�X�`��5					*/

}ksTRANSFORM_STATE;

/************************************************************************************************/
/**
 * �e�N�X�`���X�e�[�g
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_STATE_TYPE
{
	ksTEXTURE_STATE_COLOR_OP  = 0,			/**< �e�N�X�`���t�@���N�V����				*/
	ksTEXTURE_STATE_ADDRESSU  = 1,			/**< �e�N�X�`�����W u �����̃��b�v���[�h 	*/
	ksTEXTURE_STATE_ADDRESSV  = 2,			/**< �e�N�X�`�����W v �����̃��b�v���[�h	*/
	ksTEXTURE_STATE_MAGFILTER = 3,			/**< �g��t�B���^						*/
	ksTEXTURE_STATE_MINFILTER = 4,			/**< �k���t�B���^						*/
	ksTEXTURE_STATE_MIPFILTER = 5,			/**< �~�b�v�}�b�v�t�B���^					*/
	ksTEXTURE_STATE_FORCE32   = 0x7fffffff,	/**< �����I��32bit�ɂ���					*/

}ksTEXTURE_STATE_TYPE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_COLOR_OP_MODE
{
	ksTEXTURE_COLOR_OP_MODULATE = 0,
	ksTEXTURE_COLOR_OP_DECAL    = 1,
	ksTEXTURE_COLOR_OP_BLEND    = 2,
	ksTEXTURE_COLOR_OP_REPLACE  = 3,
	ksTEXTURE_COLOR_OP_ADD      = 4,
	ksTEXTURE_COLOR_OP_FORCE32  = 0x7fffffff,	/**< �����I��32bit�ɂ���					*/
}ksTEXTURE_COLOR_OP_MODE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_ADDRESS_MODE
{
	ksTEXTURE_ADDRESS_REPEAT  = 0,
	ksTEXTURE_ADDRESS_CLAMP   = 1,
	ksTEXTURE_ADDRESS_FORCE32 = 0x7fffffff,	/**< �����I��32bit�ɂ���		*/
}ksTEXTURE_ADDRESS_MODE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_FILTER
{
	ksTEXTURE_FILTER_NEAREST = 0,  
	ksTEXTURE_FILTER_LINEAR  = 1,
	ksTEXTURE_FILTER_FORCE32 = 0x7fffffff,	/**< �����I��32bit�ɂ���		*/
}ksTEXTURE_FILTER;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
typedef enum _ksTEXTURE_MIPMAP_FILTER
{
	ksTEXTURE_MIPMAP_FILTER_NEAREST = 0,
	ksTEXTURE_MIPMAP_FILTER_LINEAR  = 1,
	ksTEXTURE_MIPMAP_FILTER_FORCE32 = 0x7fffffff,	/**< �����I��32bit�ɂ���		*/

}ksTEXTURE_MIPMAP_FILTER;

/************************************************************************************************/
/**
 * �����_�[�X�e�[�g
 */
/************************************************************************************************/
typedef enum _ksRENDER_STATE_TYPE
{
	ksRENDER_STATE_OP_BLEND          = 0,			/**< �u�����h���[�h										*/
	ksRENDER_STATE_SRC_BLEND         = 1,			/**< SRC�u�����f�B���O									*/
    ksRENDER_STATE_DST_BLEND         = 2,			/**< DEST�u�����f�B���O									*/
	ksRENDER_STATE_ALPHA_BLEND       = 3,			/**< �A���t�@�u�����h										*/
	ksRENDER_STATE_ALPHA_FUNC        = 4,			/**< �A���t�@�֐�										*/
	ksRENDER_STATE_ALPHA_REF         = 5,			/**< �A���t�@��l										*/
	ksRENDER_STATE_ALPHA_MASK        = 6,			/**< �A���t�@�}�X�N�l										*/

	ksRENDER_STATE_ZTEST_ENABLE      = 7,			/**< Z�o�b�t�@(ON,OFF)									*/
	ksRENDER_STATE_ZWRITE_ENABLE     = 8,			/**< Z���C�g(ON,OFF)										*/
	ksRENDER_STATE_ALPAHTEST_ENABLE  = 9,			/**< �A���t�@�e�X�g(ON,OFF)								*/
	ksRENDER_STATE_FOG_ENABLE        = 10,			/**< �t�H�O(ON,OFF)										*/
	ksRENDER_STATE_LIGHTING          = 11,			/**< ���C�e�B���O(ON,OFF)								*/
	ksRENDER_STATE_SHADE             = 12,			/**< �V�F�[�f�B���O										*/
	ksRENDER_STATE_CULL              = 13,			/**< �J�����O											*/

	ksRENDER_STATE_STENCIL_ENABLE    = 14,			/**< �X�e���V��(ON,OFF)									*/
	ksRENDER_STATE_STENCIL_FAIL      = 15,			/**< �X�e���V���e�X�g���s���̃I�y���[�V����				*/
	ksRENDER_STATE_STENCIL_ZFAIL     = 16,			/**< �X�e���V���e�X�g����Z�e�X�g�Ɏ��s���̃I�y���[�V����	*/
	ksRENDER_STATE_STENCIL_PASS      = 17,			/**< �X�e���V���e�X�g����Z�e�X�g�̐������̃I�y���[�V����	*/
	ksRENDER_STATE_STENCIL_FUNC      = 18,			/**< �X�e���V���t�@���N�V����								*/
	ksRENDER_STATE_STENCIL_REF       = 19,			/**< �X�e���V���̊�l									*/
	ksRENDER_STATE_STENCIL_MASK      = 20,			/**< �X�e���V���̃}�X�N�l									*/

	ksRENDER_STATE_COLOR_TEST_ENABLE = 21,			/**< �J���[�e�X�g(ON,OFF)								*/
	ksRENDER_STATE_COLOR_FUNC        = 22,			/**< �J���[�֐�											*/
	ksRENDER_STATE_COLOR_REF         = 23,			/**< �J���[��l										*/
	ksRENDER_STATE_COLOR_MASK        = 24,			/**< �J���[�}�X�N�l										*/
	ksRENDER_STATE_PIXEL_MASK        = 25,			/**< �s�N�Z���}�X�N										*/
	ksRENDER_STATE_LOGICAL_OP_ENABLE = 26,			/**< ���W�J���I�y���[�V����(ON,OFF)						*/
	ksRENDER_STATE_LOGICAL_OP_BLEND  = 27,			/**< ���W�J���I�y���[�V�������[�h							*/

	ksRENDER_STATE_FORCE32           = 0x7fffffff,	/**< �����I��32bit�ɂ���									*/

}ksRENDER_STATE_TYPE;


/************************************************************************************************/
/**
 * �u�����h�̉��Z
 */
/************************************************************************************************/
typedef enum _ksBLEND_OP_MODE
{
    ksBLEND_OP_ADD         = 1,			/**< ���ʂ͓]�����ɓ]���悪���Z�����  ( ���� = �]���� + �]���� )		*/
    ksBLEND_OP_SUBTRACT    = 2,			/**< ���ʂ͓]��������]���悪���Z�����( ���� = �]���� - �]���� )		*/
    ksBLEND_OP_REVSUBTRACT = 3,			/**< ���ʂ͓]���悩��]���������Z�����( ���� = �]���� - �]���� )		*/
    ksBLEND_OP_MIN         = 4,			/**< ���ʂ͓]�����Ɠ]����̍ŏ��l�ł���( ���� = MIN(�]����, �]����) )	*/
    ksBLEND_OP_MAX         = 5,			/**< ���ʂ͓]�����Ɠ]����̍ő�l�ł���( ���� = MAX(�]����, �]����) )	*/
    ksBLEND_OP_FORCE_DWORD = 0x7fffffff,/**< �����I��32bit�ɂ���												*/

}ksBLEND_OP_MODE;

typedef enum _ksALPHA_FUNC_MODE
{
/*
SCEGU_NEVER   �S�Ẵs�N�Z����`�悵�Ȃ�  
SCEGU_ALWAYS   �S�Ẵs�N�Z����`�悷��  
SCEGU_EQUAL   �s�N�Z���̃A���t�@�l���Œ�l�̏ꍇ�� �s�N�Z����`�悷��  
SCEGU_NOTEQUAL   �s�N�Z���̃A���t�@�l���Œ�l�̏ꍇ�� �s�N�Z����`�悷��  
SCEGU_LESS   �s�N�Z���̃A���t�@�l���Œ�l�̏ꍇ�� �s�N�Z����`�悷��  
SCEGU_LEQUAL   �s�N�Z���̃A���t�@�l���Œ�l�̏ꍇ�� �s�N�Z����`�悷��  
SCEGU_GREATER   �s�N�Z���̃A���t�@�l���Œ�l�̏ꍇ�� �s�N�Z����`�悷��  
SCEGU_GEQUAL   �s�N�Z���̃A���t�@�l���Œ�l�̏ꍇ�� �s�N�Z����`�悷��  
*/
	ksALPHA_FUNC_FORCE_DWORD = 0x7fffffff,	/**< �����I��32bit�ɂ���		*/
}ksALPHA_FUNC_MODE;

/************************************************************************************************/
/**
 * �X�e���V������
 */
/************************************************************************************************/
typedef enum _ksSTENCIL_OP_MODE
{
	ksSTENCIL_OP_KEEP    = 0,				/**< �������Ȃ�								*/
	ksSTENCIL_OP_ZERO    = 1,				/**< �X�e���V���l�� 0 �ɕύX����				*/
	ksSTENCIL_OP_REPLACE = 2,				/**< �X�e���V���l��ݒ�l�ɕύX����			*/
	ksSTENCIL_OP_INVERT  = 3,				/**< �X�e���V���l�𔽓]����					*/
	ksSTENCIL_OP_INCR    = 4,				/**< �X�e���V���l�� 1 ��������				*/
	ksSTENCIL_OP_DECR    = 5,				/**< �X�e���V���l�� 1 ��������				*/
	ksSTENCIL_OP_FORCE32 = 0x7fffffff,		/**< �����I��32bit�ɂ���						*/

}ksSTENCIL_OP_MODE;

/************************************************************************************************/
/**
 * �X�e���V��FUNC
 */
/************************************************************************************************/
typedef enum _ksSTENCIL_FUNC_MODE
{
	ksSTENCIL_FUNC_NEVER    = 0,			/**< �S�Ẵs�N�Z����`�悵�Ȃ�						*/
	ksSTENCIL_FUNC_ALWAYS   = 1,			/**< �S�Ẵs�N�Z����`�悷��							*/
	ksSTENCIL_FUNC_EQUAL    = 2,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_NOTEQUAL = 3,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_LESS     = 4,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_LEQUAL   = 5,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_GREATER  = 6,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_GEQUAL   = 7,			/**< �ݒ�l���X�e���V���l�̏ꍇ�Ƀs�N�Z����`�悷��		*/
	ksSTENCIL_FUNC_FORCE32  = 0x7fffffff,	/**< �����I��32bit�ɂ���								*/

}ksSTENCIL_FUNC_MODE;

/************************************************************************************************/
/**
 * �J���[FUNC
 */
/************************************************************************************************/
typedef enum _ksCOLOR_FUNC_MODE
{
	ksCOLOR_FUNC_NEVER    = 0,				/**< �S�Ẵs�N�Z����`�悵�Ȃ�						*/
	ksCOLOR_FUNC_ALWAYS   = 1,				/**< �S�Ẵs�N�Z����`�悷��							*/
	ksCOLOR_FUNC_EQUAL    = 2,				/**< �s�N�Z���J���[���Œ�l�̏ꍇ�Ƀs�N�Z����`�悷��	*/
	ksCOLOR_FUNC_NOTEQUAL = 3,				/**< �s�N�Z���J���[���Œ�l�̏ꍇ�Ƀs�N�Z����`�悷��	*/
	ksCOLOR_FUNC_FORCE32  = 0x7fffffff,		/**< �����I��32bit�ɂ���								*/

}ksCOLOR_FUNC_MODE;

/************************************************************************************************/
/**
 * �u�����h���[�h
 */
/************************************************************************************************/
typedef enum _ksBLEND_MODE
{
	ksBLEND_ZERO                = 1,			/**< �u�����f�B���O�W�� (0, 0, 0, 0)				*/
	ksBLEND_ONE                 = 2,			/**< �u�����f�B���O�W�� (1, 1, 1, 1)				*/
	ksBLEND_SRC_COLOR           = 3,			/**< �u�����f�B���O�W�� (Rs,Gs,Bs,As)				*/
	ksBLEND_DST_COLOR           = 4,			/**< �u�����f�B���O�W�� (Rd,Gd,Bd,Ad)				*/
	ksBLEND_ONE_MINUS_SRC_COLOR = 5,			/**< �u�����f�B���O�W�� (1-Rs,1-Gs,1-Bs,1-As)		*/
	ksBLEND_ONE_MINUS_DST_COLOR = 6,			/**< �u�����f�B���O�W�� (1-Rd,1-Gd,1-Bd,1-Ad)		*/
	ksBLEND_SRC_ALPHA           = 7,			/**< �u�����f�B���O�W�� (As, As, As, As)			*/
	ksBLEND_DST_ALPHA           = 8,			/**< �u�����f�B���O�W�� (Ad, Ad, Ad, Ad) �֎~		*/
	ksBLEND_ONE_MINUS_SRC_ALPHA = 9,			/**< �u�����f�B���O�W�� (1-As,1-As,1-As,1-As)		*/
	ksBLEND_ONE_MINUS_DST_ALPHA = 10,			/**< �u�����f�B���O�W�� (1-Ad,1-Ad,1-Ad,1-Ad)	�֎~	*/
	ksBLEND_FORCE32             = 0x7fffffff,	/**< �����I��32bit�ɂ���							*/

}ksBLEND_MODE;

/************************************************************************************************/
/**
 * �V�F�[�f�B���O���[�h
 */
/************************************************************************************************/
typedef enum _ksSHADE_MODE
{
	ksSHADE_FLAT    = 1,				/**< �t���b�g�V�F�[�f�B���O		*/
	ksSHADE_GOURAUD = 2,				/**< �O�[���[�V�F�[�f�B���O		*/
	ksSHADE_FORCE32 = 0x7fffffff,		/**< �����I��32bit�ɂ���			*/

}ksSHADE_MODE;

/************************************************************************************************/
/**
 * �J�����O���[�h
 */
/************************************************************************************************/
typedef enum _ksCULL_MODE
{
	ksCULL_NONE    = 1,					/**< �w�ʂ̃J�����O�͂��Ȃ�		*/
	ksCULL_CW      = 2,					/**< �w�ʂ��E���ŃJ�����O����	*/
	ksCULL_CCW     = 3,					/**< �w�ʂ������ŃJ�����O����	*/
	ksCULL_FORCE32 = 0x7fffffff,		/**< �����I��32bit�ɂ���			*/

}ksCULL_MODE;

/************************************************************************************************/
/**
 * �J�����O���[�h
 */
/************************************************************************************************/
typedef enum _ksFOG_MODE
{
	ksFOG_NONE    = 0,					/**< �t�H�O�Ȃ�									*/
	ksFOG_EXP     = 1,					/**< �w���ŁA�t�H�O �G�t�F�N�g������				*/
	ksFOG_EXP2    = 2,					/**< �w���� 2 ��ŁA�t�H�O �G�t�F�N�g������		*/
	ksFOG_LINEAR  = 3,					/**< �n�_�ƏI�_�̊ԂŐ��`�Ƀt�H�O �G�t�F�N�g������	*/
	ksFOG_FORCE32 = 0x7fffffff,			/**< �����I��32bit�ɂ���							*/

}ksFOG_MODE;

/************************************************************************************************/
/**
 * �`��v���~�e�B�u�̃^�C�v
 */
/************************************************************************************************/
typedef enum _ksPRIMITIVE_TYPE
{
    ksPRIMITIVE_POINT_LIST     = 1,
    ksPRIMITIVE_LINE_LIST      = 2,
    ksPRIMITIVE_LINE_STRIP     = 3,
    ksPRIMITIVE_TRIANGLE_LIST  = 4,
    ksPRIMITIVE_TRIANGLE_STRIP = 5,
    ksPRIMITIVE_FORCE32        = 0x7fffffff,

}ksPRIMITIVE_TYPE;


/************************************************************************************************/
/**
 * �v���~�e�B�u�̎��
 */
/************************************************************************************************/
typedef enum _ksRENDER_PRIM_TYPE
{

}ksRENDER_PRIM_TYPE;

/************************************************************************************************/
/**
 *
 */
/************************************************************************************************/
class KsTextureState
{
	public:
		ksTEXTURE_COLOR_OP_MODE			m_colorOP;
		ksTEXTURE_ADDRESS_MODE			m_addressU;
		ksTEXTURE_ADDRESS_MODE			m_addressV;
		ksTEXTURE_FILTER				m_magFilter;
		ksTEXTURE_FILTER				m_minFilter;
		ksTEXTURE_MIPMAP_FILTER			m_mipMapFilter;
};

/************************************************************************************************/
/**
 * @class		KsRenderState
 * @brief		�����_�[�X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderState
{
	public:
		/* �������郌���_�[�X�e�[�g�̃r�b�g */
		//push ���ꂽ�Ƃ����ׂĂ̌���̂��ׂẴ����_�[�X�e�[�g��ۑ�����
		//pop  �̂Ƃ��͈Ⴄ���̂�����ύX����
		ksBLEND_OP_MODE					m_opBlend;
		ksBLEND_MODE					m_srcBlend;
		ksBLEND_MODE					m_dstBlend;
		
		KsBool							m_alphaBlend;
		ksALPHA_FUNC_MODE				m_alphaFunc;
		KsUInt32						m_alphaRef;
		KsUInt32						m_alphaMask;

		KsBool							m_zTest;
		KsBool							m_zWrite;
		KsBool							m_alphaTest;
		KsBool							m_fog;
		KsBool							m_lighting;
		ksSHADE_MODE					m_shadeMode;
		ksCULL_MODE						m_cullMode;

		KsBool							m_stencil;
		KsUInt32						m_stencilRef;
		KsUInt32						m_stencilMask;
		ksSTENCIL_OP_MODE				m_stencilOpFail;
		ksSTENCIL_OP_MODE				m_stencilOpZFail;
		ksSTENCIL_OP_MODE				m_stencilOpPass;
		ksSTENCIL_FUNC_MODE				m_stencilFunc;

		KsBool							m_colorTest;
		ksCOLOR_FUNC_MODE				m_colorFunc;
		KsUInt32						m_colorRef;
		KsUInt32						m_colorMask;

		KsUInt32						m_pixelMask;

		KsBool							m_logicalOp;
		//stLOGICAL_FUNC_MODE			m_logicalFunc;
		//KsUInt32						m_changeStateMask;	/**< �ύX���������_�[�X�e�[�g�̃}�X�N	*/

};

/************************************************************************************************/
/**
 * @class		KsRenderStateStack
 * @brief		�����_�[�X�e�[�g�X�^�b�N
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderStateStack
{
	public:
		/**
		 * �R���X�g���N�^
		 */
											KsRenderStateStack() : m_index( 0 ) {}

		/**
		 * �����_�[�X�e�[�g���v�b�V������
		 * @param		pState				�v�b�V�����郌���_�[�X�e�[�g
		 */
		KsBool								push( const KsRenderState* pState );

		/**
		 * �����_�[�X�e�[�g���|�b�v����
		 * @param		pState				�����_�[�X�e�[�g���擾���邽�߂̃|�C���^
		 */
		KsBool								pop( KsRenderState* pState );

		/**
		 * �X�^�b�N���N���A�[����
		 */
		void								clear();

	private:
		KsRenderState						m_stack[ ksRENDER_STATE_STACK_MAX ];	/**< �����_�[�X�e�[�g�X�^�b�N	*/
		KsInt32								m_index;								/**< ���݂̃X�^�b�N�̐[��		*/
};

/************************************************************************************************/
/**
 * @class		KsRenderSystem
 * @brief		�x�[�X�`��V�X�e��
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
											KsRenderSystem();

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
		virtual void						beginScene( KsUInt32 flags, KsColor color, KsReal depth, KsUInt32 stencil ) = 0;

		/**
		 * �V�[���`��I��
		 */
		virtual void						endScene() = 0;

		/**
		 * �`��o�b�t�@�ƕ\���o�b�t�@�����ւ�
		 */
		virtual void						swapBuffer() = 0;

		/**
		 * �r���[�|�[�g���Z�b�g����
		 * @param		pViewport			�r���[�|�[�g�ݒ�
		 */
		virtual void						setViewport( const KsViewport* pViewport ) = 0;

		/**
		 * �t�H�O���Z�b�g����
		 */
		virtual void						setFog( ksFOG_MODE mode, KsColor color, KsReal start, KsReal end, KsReal density ) = 0;

		/*-------------------------------------<< �v���~�e�B�u�`��@�\�֌W >>--------------------------------------------------*/
		/**
		 * ���C����`��(2D)
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		color				�F
		 */
		//virtual void						drawLine( KsInt16 x0, KsInt16 y0, KsInt16 x1, KsInt16 y1, KsUInt32 color ) = 0;

		/**
		 * �Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		color				�F
		 */
		virtual void						drawRect( KsInt32 x, KsInt32 y, KsInt32 w, KsInt32 h, KsColor color ) = 0;

		/**
		 * �Z�`��`��
		 * @param		x					X���W
		 * @param		y					Y���W
		 * @param		w					��
		 * @param		h					����
		 * @param		u0					�e�N�X�`����X���W
		 * @param		v0					�e�N�X�`����Y���W
		 * @param		u1					�e�N�X�`���̕�
		 * @param		v1					�e�N�X�`���̍���
		 * @param		color				�F
		 * @param		pTexture			�e�N�X�`��
		 */
		//virtual void						drawRectEx( KsInt16 x, KsInt16 y, KsInt16 w, KsInt16 h, KsUInt16 tx, KsUInt16 ty, KsUInt16 tw, KsUInt16 th, KsUInt32 color, KsTexture* pTexture ) = 0;

		/**
		 * �X�v���C�g�`��
		 * @param		pSpritePrim			�X�v���C�g�̃v���~�e�B�u(4�̒��_�z����킽���Ȃ��ƃo�O��)
		 */
		//virtual void						drawSprite( KS_SPRITE_PRIM* pSpritePrim ) = 0;

		/**
		 *
		 */
		virtual void						drawPrimitive( ksPRIMITIVE_TYPE type, KsUInt32 vertexStart, KsUInt32 indexStart, KsUInt32 primitiveCount, KsVertexBuffer* pVertexBuffer, KsIndexBuffer* pIndexBuffer ) = 0;

		/*------------------------------------------<< �e�N�X�`���֌W >>------------------------------------------------------*/
		/**
		 * �e�N�X�`���𐶐�����
		 * @param		pFileName			�t�@�C����
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		//virtual KsTexture*					createTexture( const KsChar* pFileName, KsUInt32 flags=0 ) = 0;

		/**
		 * �C���[�W�f�[�^����e�N�X�`���𐶐�����
		 * @param		pImage				�C���[�W�f�[�^�̃|�C���^
		 * @param		flags				�����t���O
		 * @return							�e�N�X�`���̃|�C���^
		 */
		//virtual KsTexture*					createTexture( KsImage* pImage, KsUInt32 flags=0 ) = 0;

		/**
		 * �e�N�X�`�����Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		pTexture			�e�N�X�`��
		 */
		//virtual void						setTexture( KsUInt32 stage, KsTexture* pTexture ) = 0;

		/**
		 * �e�N�X�`���X�e�[�g���Z�b�g����
		 * @param		statge				�e�N�X�`���X�e�[�W
		 * @param		state				�Z�b�g����X�e�[�^�X�̎��
		 * @param		value				�Z�b�g����l
		 */
		//virtual void						setTextureState( KsUInt32 stage, ksTEXTURE_STATE_TYPE state, KsUInt32 value ) = 0;

		/*-----------------------------------<< �}�e���A���֌W >>--------------------------------------------------*/
		/**
		 * �}�e���A�����Z�b�g����
		 * @param		pMaterial			�}�e���A��
		 */
		virtual void						setMaterial( KsMaterial* pMaterial ) = 0;

		/*-------------------------------------<< ���C�g�֌W >>--------------------------------------------------*/
		/**
		 * ���C�g��ǉ�����
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		pLight				���C�g���
		 * @note							���C�g��ݒu�ł��鐔�́A�ő�W�ł��B<br>
		 *									���C�g����菜�����Ƃ��͎�菜���������C�g�̃C���f�b�N�X�ƃ��C�g��NULL���Z�b�g���Ă��������B
		 */
		virtual void						setLight( KsUInt32 index, const KsLight* pLight ) = 0;

		/**
		 * �w�胉�C�g��L���A�����ɂ���B
		 * @param		index				���C�g�̃C���f�b�N�X
		 * @param		flag				���C�g��ON OFF�̃t���O( ksTRUE: ON, ksFALSE: OFF )
		 */
		virtual void						setLightEnable( KsUInt32 index, KsBool flag ) = 0;

		/**
		 * �w��C���f�b�N�X�̃��C�g���擾����
		 * @param		index				�C���f�b�N�X
		 * @return							���C�g�̃|�C���^(�Z�b�g����Ă��Ȃ��Ƃ���NULL���Ԃ�)
		 */
		virtual KsLight*					getLight( KsUInt32 index );

		/**
		 * ��{�I�ɐݒ��3D���[�h������������
		 */
		//virtual void						auto2DMode() = 0;

		/**
		 * ��{�I�ɐݒ��3D���[�h������������
		 */
		virtual void						auto3DMode() = 0;

		/*-------------------------------------<< �����_�[�X�e�[�g�֌W >>--------------------------------------------------*/
		/**
		 * �����_�[�X�e�[�g���X�^�b�N�Ƀv�b�V������
		 */
		void								pushRenderState();

		/**
		 * �����_�[�X�e�[�g���X�^�b�N�Ƀ|�b�v����
		 */
		void								popRenderState();

		/**
		 * �����_�[�X�e�[�g
		 * @param		state				�X�e�[�g�̎��
		 * @param		value				�X�e�[�g�ɑΉ�����l
		 */
		//virtual void						setRenderState( ksRENDER_STATE_TYPE state, KsUInt32 value ) = 0;

		/**
		 * �g�����X�t�H�[������
		 * @param		state				�g�����X�t�H�[���̃��[�h
		 * @param		pMatrix				�ϊ��}�g���b�N�X
		 */
		virtual void						setTransform( ksTRANSFORM_STATE state, const KsMatrix* pMatrix ) = 0;

	protected:
		KsMatrix							m_viewMatrix;					/**< �r���[�}�g���b�N�X					*/
		KsMatrix							m_worldMatrix;					/**< ���[���h�}�g���b�N�X					*/
		KsMatrix							m_textureMatrix;				/**< �e�N�X�`���}�g���b�N�X				*/
		KsTextureState						m_textureState;					/**< ���݂̃e�N�X�`���X�e�[�g				*/
		KsRenderState						m_renderState;					/**< ���݂̃����_�[�X�e�[�g				*/
		KsRenderStateStack					m_renderStateStack;				/**< �����_�[�X�e�[�g�X�^�b�N				*/
		KsLight								m_pLights[ ksLIGHT_MAX ];		/**< ���C�g								*/
		KsUInt32							m_clearFlags;					/**< �N���A�t���O						*/
		KsColor								m_clearColor;					/**< �o�b�t�@�̃N���A�J���[�Z�b�g			*/
		KsInt32								m_clearDepth;					/**< Z�o�b�t�@�̃N���A�l�Z�b�g			*/
		KsInt32								m_clearStencil;					/**< �X�e���V���o�b�t�@�̃N���A�l�Z�b�g	*/
};

#endif		/* __KSRENDERSYSTEM_H__ */

