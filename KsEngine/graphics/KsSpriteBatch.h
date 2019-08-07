/************************************************************************************************/
/** 
 * @file		KsSpriteBatch.h
 * @brief		�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSPRITEBATCH_H__
#define __KSSPRITEBATCH_H__

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
 * @class		KsSpriteBatch
 * @brief		�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSpriteBatch
{
	public:
		/**
		 * �R���X�g���N�^
		 */
									KsSpriteBatch();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsSpriteBatch();

		/**
		 * �o�b�t�@�𐶐�����
		 * @param	count			�ő�v���~�e�B�u��
		 */
		virtual void				create( KsUInt32 workMax, KsUInt32 spriteMax ) = 0;

		/**
		 * �o�b�t�@��j������
		 */
		virtual void				destroy() = 0;

		/**
		 * �J���[���Z�b�g����
		 * @param	rectColor		�J���[�l
		 */
		virtual void				setColor( const KsColorReal& lineColor ) = 0;

		/**
		 * �J���[���Z�b�g����
		 * @param	r				R�l
		 * @param	g				G�l
		 * @param	b				B�l
		 * @param	a				A�l
		 */
		virtual void				setColor( KsReal r, KsReal g, KsReal b, KsReal a ) = 0;

		/**
		 * �J���[���Z�b�g����
		 * @param	index			�C���f�b�N�X
		 * @param	rectColor		�J���[�l
		 */
		virtual void				setColor( KsInt32 index, const KsColorReal& rectColor ) = 0;

		/**
		 * �J���[���Z�b�g����
		 * @param	index			�C���f�b�N�X
		 * @param	r				R�l
		 * @param	g				G�l
		 * @param	b				B�l
		 * @param	a				A�l
		 */
		virtual void				setColor( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a ) = 0;

		/**
		 * Sprite �`�悷��
		 * @param		pTexture	�e�N�X�`��
		 * @param		left		X���W
		 * @param		top			Y���W
		 * @param		width		��
		 * @param		height		����
		 * @param		tx			�e�N�X�`�� X���W
		 * @param		ty			�e�N�X�`�� Y���W
		 * @param		tw			�e�N�X�`�� ��
		 * @param		th			�e�N�X�`�� ����
		 */
		virtual void				draw( const KsTexture* pTexture, KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height, KsReal tx, KsReal ty, KsReal tw, KsReal th ) = 0;

		/**
		 * Sprite �`�悷��
		 * @param		pTexture	�e�N�X�`��
		 * @param		left		X���W
		 * @param		top			Y���W
		 * @param		width		��
		 * @param		height		����
		 * @param		tx			�e�N�X�`�� X���W
		 * @param		ty			�e�N�X�`�� Y���W
		 * @param		tw			�e�N�X�`�� ��
		 * @param		th			�e�N�X�`�� ����
		 */
		virtual void				draw( const KsTexture* pTexture, KsReal left, KsReal top, KsReal width, KsReal height, KsReal tx, KsReal ty, KsReal tw, KsReal th ) = 0;

		/**
		 * Sprite �`�悷��
		 * @param		pTexture	�e�N�X�`��
		 * @param		pVertices	�X�v���C�g�p���_�f�[�^
		 */
		virtual void				draw( const KsTexture* pTexture, const KS_VERTEX_SPRITE* pVertices ) = 0;

		/**
		 * �o�b�t�@���ꊇ�`�悷��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		virtual void				flush( KsRenderContext* pRenderContext ) = 0;
};


#endif		/* __KSSPRITEBATCH_H__ */



