/************************************************************************************************/
/** 
 * @file		KsSpriteBatchDX11.h
 * @brief		描画(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSPRITEBATCHDX11_H__
#define __KSSPRITEBATCHDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsSpriteWork
 * @brief		描画(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsSpriteWork
{
	public:
		/**
		 * コンストラクタ
		 */
		KsSpriteWork();

		/**
		 * コンストラクタ
		 * @param	count			最大プリミティブ数
		 */
		KsSpriteWork( KsUInt32 spriteMax );

		/**
		 * デストラクタ
		 */
		~KsSpriteWork();

		/**
		 * バッファを生成する
		 * @param	count			最大プリミティブ数
		 */
		virtual void				create( KsUInt32 count );

		/**
		 * バッファを破棄する
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
 * @brief		描画(DX11用)
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsSpriteBatchDX11 : public KsSpriteBatch
{
	public:
		/**
		 * コンストラクタ
		 * @param	workMax			ワーク数
		 * @param	spriteMax		最大プリミティブ数
		 */
									KsSpriteBatchDX11( KsUInt32 workMax, KsUInt32 spriteMax );

		/**
		 * デストラクタ
		 */
		virtual						~KsSpriteBatchDX11();

		/**
		 * バッファを生成する
		 * @param	workMax			ワーク数
		 * @param	spriteMax		最大プリミティブ数
		 */
		virtual void				create( KsUInt32 workMax, KsUInt32 spriteMax );

		/**
		 * バッファを破棄する
		 */
		virtual void				destroy();

		/**
		 * カラーをセットする
		 * @param	rectColor		カラー値
		 */
		virtual void				setColor( const KsColorReal& lineColor );

		/**
		 * カラーをセットする
		 * @param	r				R値
		 * @param	g				G値
		 * @param	b				B値
		 * @param	a				A値
		 */
		virtual void				setColor( KsReal r, KsReal g, KsReal b, KsReal a );

		/**
		 * カラーをセットする
		 * @param	index			インデックス
		 * @param	rectColor		カラー値
		 */
		virtual void				setColor( KsInt32 index, const KsColorReal& rectColor );

		/**
		 * カラーをセットする
		 * @param	index			インデックス
		 * @param	r				R値
		 * @param	g				G値
		 * @param	b				B値
		 * @param	a				A値
		 */
		virtual void				setColor( KsInt32 index, KsReal r, KsReal g, KsReal b, KsReal a );

		/**
		 * Sprite 描画する
		 * @param		pTexture	テクスチャ
		 * @param		left		X座標
		 * @param		top			Y座標
		 * @param		width		幅
		 * @param		height		高さ
		 * @param		tx			テクスチャ X座標
		 * @param		ty			テクスチャ Y座標
		 * @param		tw			テクスチャ 幅
		 * @param		th			テクスチャ 高さ
		 */
		virtual void				draw( const KsTexture* pTexture, KsInt32 left, KsInt32 top, KsInt32 width, KsInt32 height, KsReal tx, KsReal ty, KsReal tw, KsReal th );

		/**
		 * Sprite 描画する
		 * @param		pTexture	テクスチャ
		 * @param		left		X座標
		 * @param		top			Y座標
		 * @param		width		幅
		 * @param		height		高さ
		 * @param		tx			テクスチャ X座標
		 * @param		ty			テクスチャ Y座標
		 * @param		tw			テクスチャ 幅
		 * @param		th			テクスチャ 高さ
		 */
		virtual void				draw( const KsTexture* pTexture, KsReal left, KsReal top, KsReal width, KsReal height, KsReal tx, KsReal ty, KsReal tw, KsReal th );

		/**
		 * Sprite 描画する
		 * @param		pTexture	テクスチャ
		 * @param		pVertices	スプライト用頂点データ
		 */
		virtual void				draw( const KsTexture* pTexture, const KS_VERTEX_SPRITE* pVertices );

		/**
		 * バッファを一括描画する
		 * @param	pRenderContext	描画コンテキスト
		 */
		virtual void				flush( KsRenderContext* pRenderContext );

	private:
		KsSpriteWork*				getSpriteWork( const KsChar* name, const KsTexture* pTexture );

	public:
		KsSpriteWork*				m_pSpriteWork;			/**< Spriteワーク			*/
		KsUInt32					m_spriteWorkMax;		/**< SpriteワークMax			*/
		KsUInt32					m_spriteStride;			/**< Sprite Stride			*/
		KsUInt32					m_spriteOffset;			/**< Sprite Offset			*/
		KsColorReal					m_spriteColor[ 4 ];		/**< Sprite描画の4頂点のカラー	*/
		KsVertexShader*				m_pSpriteVS;			/**< Sprite Vertex　Shader	*/
		KsPixelShader*				m_pSpritePS;			/**< Sprite Pixel　 Shader	*/
		KsInputLayout*				m_pSpriteIL;			/**< 頂点レイアウト			*/
		KsIndexBuffer*				m_pSpriteIB;			/**< インデックスバッファ		*/
		KsReal						m_spriteDepth;			/**< Sprite Depth			*/
		KsUInt32					m_textureCount;			/**< Texture Count			*/
		KsUInt32					m_textureMax;			/**< Texture Max			*/
		KsHashTable<KsSpriteWork*>	m_textureDict;			/**< Texture ディクショナリ	*/
};


#endif		/* __KSSPRITEBATCHDX11_H__ */



