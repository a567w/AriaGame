/************************************************************************************************/
/** 
 * @file		KsSpriteBatchDX11.h
 * @brief		�`��(DX11�p)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSPRITEBATCHDX11_H__
#define __KSSPRITEBATCHDX11_H__

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
 * @class		KsSpriteWork
 * @brief		�`��(DX11�p)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsSpriteWork
{
	public:
		/**
		 * �R���X�g���N�^
		 */
		KsSpriteWork();

		/**
		 * �R���X�g���N�^
		 * @param	count			�ő�v���~�e�B�u��
		 */
		KsSpriteWork( KsUInt32 spriteMax );

		/**
		 * �f�X�g���N�^
		 */
		~KsSpriteWork();

		/**
		 * �o�b�t�@�𐶐�����
		 * @param	count			�ő�v���~�e�B�u��
		 */
		virtual void				create( KsUInt32 count );

		/**
		 * �o�b�t�@��j������
		 */
		virtual void				destroy();

	public:
		KsUInt32					m_spriteCount;
		KsUInt32					m_spriteMax;
		KsUInt32					m_spriteIndex;
		KS_VERTEX_SPRITE*			m_pSpriteVertices;
		KsVertexBuffer*				m_pSpriteVB;
		const KsTexture*			m_pTexture;
		KsString					m_textureName;
};

/************************************************************************************************/
/**
 * @class		KsSpriteBatchDX11
 * @brief		�`��(DX11�p)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsSpriteBatchDX11 : public KsSpriteBatch
{
	public:
		/**
		 * �R���X�g���N�^
		 * @param	workMax			���[�N��
		 * @param	spriteMax		�ő�v���~�e�B�u��
		 */
									KsSpriteBatchDX11( KsUInt32 workMax, KsUInt32 spriteMax );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsSpriteBatchDX11();

		/**
		 * �o�b�t�@�𐶐�����
		 * @param	workMax			���[�N��
		 * @param	spriteMax		�ő�v���~�e�B�u��
		 */
		virtual void				create( KsUInt32 workMax, KsUInt32 spriteMax );

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
		virtual void				draw( const KsTexture* pTexture, KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height, KsReal tx, KsReal ty, KsReal tw, KsReal th );

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
		virtual void				draw( const KsTexture* pTexture, KsReal left, KsReal top, KsReal width, KsReal height, KsReal tx, KsReal ty, KsReal tw, KsReal th );

		/**
		 * Sprite �`�悷��
		 * @param		pTexture	�e�N�X�`��
		 * @param		pVertices	�X�v���C�g�p���_�f�[�^
		 */
		virtual void				draw( const KsTexture* pTexture, const KS_VERTEX_SPRITE* pVertices );

		/**
		 * �o�b�t�@���ꊇ�`�悷��
		 * @param	pRenderContext	�`��R���e�L�X�g
		 */
		virtual void				flush( KsRenderContext* pRenderContext );

	private:
		KsSpriteWork*				getSpriteWork( const KsChar* name, const KsTexture* pTexture );

	public:
		KsSpriteWork*				m_pSpriteWork;			/**< Sprite���[�N			*/
		KsUInt32					m_spriteWorkMax;		/**< Sprite���[�NMax			*/
		KsUInt32					m_spriteStride;			/**< Sprite Stride			*/
		KsUInt32					m_spriteOffset;			/**< Sprite Offset			*/
		KsColorReal					m_spriteColor[ 4 ];		/**< Sprite�`���4���_�̃J���[	*/
		KsVertexShader*				m_pSpriteVS;			/**< Sprite Vertex�@Shader	*/
		KsPixelShader*				m_pSpritePS;			/**< Sprite Pixel�@ Shader	*/
		KsInputLayout*				m_pSpriteIL;			/**< ���_���C�A�E�g			*/
		KsIndexBuffer*				m_pSpriteIB;			/**< �C���f�b�N�X�o�b�t�@		*/
		KsReal						m_spriteDepth;			/**< Sprite Depth			*/
		KsUInt32					m_textureCount;			/**< Texture Count			*/
		KsUInt32					m_textureMax;			/**< Texture Max			*/
		KsHashTable<KsSpriteWork*>	m_textureDict;			/**< Texture �f�B�N�V���i��	*/
};


#endif		/* __KSSPRITEBATCHDX11_H__ */



