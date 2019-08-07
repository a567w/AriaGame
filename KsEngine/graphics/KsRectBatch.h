/************************************************************************************************/
/** 
 * @file		KsRectBatch.h
 * @brief		�`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRECTBATCH_H__
#define __KSRECTBATCH_H__

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
 * @class		KsRectBatch
 * @brief		RECT �`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsRectBatch
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	count			�ő�v���~�e�B�u��
		 */
									KsRectBatch();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsRectBatch();

		/**
		 * �o�b�t�@�𐶐�����
		 * @param	count			�ő�v���~�e�B�u��
		 */
		virtual void				create( KsUInt32 count ) = 0;

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
		 * RECT �`�悷��
		 * @param		left		X���W
		 * @param		top			Y���W
		 * @param		width		��
		 * @param		height		����
		 */
		virtual void				draw( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height ) = 0;

		/**
		 * RECT �`�悷��
		 * @param		left		X���W
		 * @param		top			Y���W
		 * @param		width		��
		 * @param		height		����
		 */
		virtual void				draw( KsReal left, KsReal top, KsReal width, KsReal height ) = 0;

		/**
		 * �o�b�t�@���ꊇ�`�悷��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		virtual void				flush( KsRenderContext* pRenderContext ) = 0;
};



#endif		/* __KSRECTBATCH_H__ */



