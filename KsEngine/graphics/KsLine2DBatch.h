/************************************************************************************************/
/** 
 * @file		KsLine2DBatch.h
 * @brief		2D���C���`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSLINE2DBATCH_H__
#define __KSLINE2DBATCH_H__

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
 * @class		KsLine2DBatch
 * @brief		Line2D �`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsLine2DBatch
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	count			�ő�v���~�e�B�u��
		 */
									KsLine2DBatch();

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsLine2DBatch();

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
		 * ���C���`�悷��
		 * @param		start		X���W
		 * @param		end			Y���W
		 */
		virtual void				draw( const KsVector3d& start, const KsVector3d& end ) = 0;

		/**
		 * �o�b�t�@���ꊇ�`�悷��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		virtual void				flush( KsRenderContext* pRenderContext ) = 0;
};



#endif		/* __KSLINE2DBATCH_H__ */



