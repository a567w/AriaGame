/************************************************************************************************/
/** 
 * @file		KsLine3DBatchDX11.h
 * @brief		3D���C���`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSLINE3DBATCHDX11_H__
#define __KSLINE3DBATCHDX11_H__

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
 * @class		KsLine3DBatchDX11
 * @brief		Line3D �`��
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsLine3DBatchDX11 : public KsLine3DBatch
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	count			�ő�v���~�e�B�u��
		 */
									KsLine3DBatchDX11( KsUInt32 count );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsLine3DBatchDX11();

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
		 * ���C���`�悷��
		 * @param		start		X���W
		 * @param		end			Y���W
		 */
		virtual void				draw( const KsVector3d& start, const KsVector3d& end );

		/**
		 * �o�b�t�@���ꊇ�`�悷��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		virtual void				flush( KsRenderContext* pRenderContext );

	private:
		KsUInt32					m_lineCount;
		KsUInt32					m_lineMax;
		KsUInt32					m_lineIndex;
		KsUInt32					m_lineStride;
		KsUInt32					m_lineOffset;
		KsColorReal					m_lineColor;
		KS_VERTEX_LINE3D*			m_pLineVertices;
		KsVertexShader*				m_pLineVS;
		KsPixelShader*				m_pLinePS;
		KsVertexBuffer*				m_pLineVB;
		KsInputLayout*				m_pLineIL;
};



#endif		/* __KSLINE3DBATCHDX11_H__ */



