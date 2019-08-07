/************************************************************************************************/
/** 
 * @file		KsRectBatchDX11.h
 * @brief		�`��(DX11�p)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSRECTBATCHDX11_H__
#define __KSRECTBATCHDX11_H__

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
 * @class		KsRectBatchDX11
 * @brief		RECT �`��(DX11�p)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsRectBatchDX11 : public KsRectBatch
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	count			�ő�v���~�e�B�u��
		 */
									KsRectBatchDX11( KsUInt32 count );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsRectBatchDX11();

		/**
		 * �o�b�t�@�𐶐�����
		 * @param	count			�ő�v���~�e�B�u��
		 */
		virtual void				create( KsUInt32 count );

		/**
		 * �o�b�t�@��j������
		 */
		virtual void				destroy();

		/**
		 * �J���[���Z�b�g����
		 * @param	rectColor		�J���[�l
		 */
		virtual void				setColor( const KsColorReal& lineColor );

		/**
		 * �J���[���Z�b�g����
		 * @param	r				R�l
		 * @param	g				G�l
		 * @param	b				B�l
		 * @param	a				A�l
		 */
		virtual void				setColor( KsReal r, KsReal g, KsReal b, KsReal a );

		/**
		 * �J���[���Z�b�g����
		 * @param	index			�C���f�b�N�X
		 * @param	rectColor		�J���[�l
		 */
		virtual void				setColor( KsInt32 index, const KsColorReal& rectColor );

		/**
		 * �J���[���Z�b�g����
		 * @param	index			�C���f�b�N�X
		 * @param	r				R�l
		 * @param	g				G�l
		 * @param	b				B�l
		 * @param	a				A�l
		 */
		virtual void				setColor( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a );

		/**
		 * RECT �`�悷��
		 * @param		left		X���W
		 * @param		top			Y���W
		 * @param		width		��
		 * @param		height		����
		 */
		virtual void				draw( KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height );

		/**
		 * RECT �`�悷��
		 * @param		left		X���W
		 * @param		top			Y���W
		 * @param		width		��
		 * @param		height		����
		 */
		virtual void				draw( KsReal left, KsReal top, KsReal width, KsReal height );

		/**
		 * �o�b�t�@���ꊇ�`�悷��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		virtual void				flush( KsRenderContext* pRenderContext );

	private:
		KsUInt32					m_rectCount;		/**< �`�悷��Rect��			*/
		KsUInt32					m_rectMax;			/**< �`�悷��Rect�ő吔		*/
		KsUInt32					m_rectIndex;		/**< �`�悷��Rect�ő吔		*/
		KsUInt32					m_rectStride;		/**< Rect Stride			*/
		KsUInt32					m_rectOffset;		/**< Rect Offset			*/
		KsReal						m_rectDepth;		/**< Rect �[�x�l				*/
		KS_VERTEX_RECT*				m_pRectVertices;	/**< Rect���_				*/
		KsVertexShader*				m_pRectVS;			/**< Rect Vertex�@Shader		*/
		KsPixelShader*				m_pRectPS;			/**< Rect Pixel�@ Shader		*/
		KsInputLayout*				m_pRectIL;			/**< ���_���C�A�E�g			*/
		KsVertexBuffer*				m_pRectVB;			/**< ���_�o�b�t�@				*/
		KsIndexBuffer*				m_pRectIB;			/**< �C���f�b�N�X�o�b�t�@		*/
		KsColorReal					m_rectColor[ 4 ];	/**< Rect�`���4���_�̃J���[	*/
};



#endif		/* __KSRECTBATCHDX11_H__ */



