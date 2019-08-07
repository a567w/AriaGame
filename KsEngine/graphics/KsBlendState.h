/************************************************************************************************/
/** 
 * @file		KsBlendState.h
 * @brief		DirectX�p�[�x�X�e���V���X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSDBLENDSTATE_H__
#define __KSDBLENDSTATE_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KS_BLEND
 * @brief		�u�����h�X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
typedef enum KS_BLEND
{	
	KS_BLEND_ZERO	= 1,
	KS_BLEND_ONE	= 2,
	KS_BLEND_SRC_COLOR	= 3,
	KS_BLEND_INV_SRC_COLOR	= 4,
	KS_BLEND_SRC_ALPHA	= 5,
	KS_BLEND_INV_SRC_ALPHA	= 6,
	KS_BLEND_DEST_ALPHA	= 7,
	KS_BLEND_INV_DEST_ALPHA	= 8,
	KS_BLEND_DEST_COLOR	= 9,
	KS_BLEND_INV_DEST_COLOR	= 10,
	KS_BLEND_SRC_ALPHA_SAT	= 11,
	KS_BLEND_BLEND_FACTOR	= 14,
	KS_BLEND_INV_BLEND_FACTOR	= 15,
	KS_BLEND_SRC1_COLOR	= 16,
	KS_BLEND_INV_SRC1_COLOR	= 17,
	KS_BLEND_SRC1_ALPHA	= 18,
	KS_BLEND_INV_SRC1_ALPHA	= 19

}KS_BLEND;

/************************************************************************************************/
/**
 * @class		KS_BLEND
 * @brief		�u�����h�X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
typedef enum KS_BLEND_OP
{
	KS_BLEND_OP_ADD	= 1,
	KS_BLEND_OP_SUBTRACT	= 2,
	KS_BLEND_OP_REV_SUBTRACT	= 3,
	KS_BLEND_OP_MIN	= 4,
	KS_BLEND_OP_MAX	= 5
}KS_BLEND_OP;

/************************************************************************************************/
/**
 * @class		KS_BLEND
 * @brief		�u�����h�X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
typedef enum KS_COLOR_WRITE_ENABLE
{
	KS_COLOR_WRITE_ENABLE_RED	= 1,
	KS_COLOR_WRITE_ENABLE_GREEN	= 2,
	KS_COLOR_WRITE_ENABLE_BLUE	= 4,
	KS_COLOR_WRITE_ENABLE_ALPHA	= 8,
	KS_COLOR_WRITE_ENABLE_ALL	= ( ( ( KS_COLOR_WRITE_ENABLE_RED | KS_COLOR_WRITE_ENABLE_GREEN )  | KS_COLOR_WRITE_ENABLE_BLUE )  | KS_COLOR_WRITE_ENABLE_ALPHA ) 
}KS_COLOR_WRITE_ENABLE;

/************************************************************************************************/
/**
 * @class		KS_BLEND
 * @brief		�u�����h�X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
typedef struct KS_RENDER_TARGET_BLEND_DESC
{
	KsBool							BlendEnable;
	KS_BLEND						SrcBlend;
	KS_BLEND						DestBlend;
	KS_BLEND_OP						BlendOp;
	KS_BLEND						SrcBlendAlpha;
	KS_BLEND						DestBlendAlpha;
	KS_BLEND_OP						BlendOpAlpha;
	KsUInt8							RenderTargetWriteMask;

}KS_RENDER_TARGET_BLEND_DESC;

/************************************************************************************************/
/**
 * @class		KS_BLEND
 * @brief		�u�����h�X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
typedef struct KS_BLEND_DESC
{
	KsBool							AlphaToCoverageEnable;
	KsBool							IndependentBlendEnable;
	KS_RENDER_TARGET_BLEND_DESC		RenderTarget[ 8 ];

}KS_BLEND_DESC;

/************************************************************************************************/
/**
 * @class		KsBlendState
 * @brief		�[�x�X�e���V���X�e�[�g
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		�Q�ƃJ�E���^��
 */
/************************************************************************************************/
class ksENGINE_API KsBlendState
{
	public:
		/**
		 * �R���X�g���N�^
		 */
										KsBlendState();

		/**
		 * �R���X�g���N�^
		 */
										KsBlendState( const KS_BLEND_DESC* pBlendStateDesc );

		/**
		 * �R���X�g���N�^
		 */
										KsBlendState( const KS_BLEND_DESC& refBlendStateDesc );

		/**
		 * �f�X�g���N�^
		 */
		virtual							~KsBlendState();

		/**
		 * �e�N�X�`���̔j��
		 */
		virtual void					destroy() = 0;

		/**
		 * ���\�[�X���擾����
		 * @return						 ���\�[�X
		 */
		virtual void*					getRenderResource() = 0;

	protected:
		KS_BLEND_DESC					m_blendStateDesc;

	public:
		static const KS_BLEND_DESC		DEFAULT;
		static const KS_BLEND_DESC		SPRITE;
		static const KS_BLEND_DESC		ACCUMULATE;
};

#endif		/* __KSDBLENDSTATE_H__ */

