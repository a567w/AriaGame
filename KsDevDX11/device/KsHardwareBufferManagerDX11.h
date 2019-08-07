/************************************************************************************************/
/** 
 * @file		KsHardwareBufferManagerDX11.h
 * @brief		バッファマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBUFFERMANAGERDX11_H__
#define __KSBUFFERMANAGERDX11_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsBufferManager
 * @brief		バッファマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksDEVDX11_API KsHardwareBufferManagerDX11 : public KsHardwareBufferManager
{
	public:
		/**
		 * コンストラクタ
		 * @param	pRenderSystem		描画システム
		 */
										KsHardwareBufferManagerDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual							~KsHardwareBufferManagerDX11();

		/**
		 * 頂点バッファを生成する
		 * @param		vertexSize		[in] 頂点サイズ
		 * @param		numVertex		[in] 頂点数
		 * @param		vertexFormat	[in] 頂点フォーマット
		 * @param		flags			[in] フラグ
		 * @return						頂点バッファのポインタ
		 */
		virtual KsVertexBuffer*			createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * 頂点バッファを生成する
		 * @param		vertexSize		[in] 頂点サイズ
		 * @param		numVertex		[in] 頂点数
		 * @param		vertexFormat	[in] 頂点フォーマット
		 * @param		flags			[in] フラグ
		 * @return						頂点バッファのポインタ
		 */
		virtual KsVertexBuffer*			createVertexBuffer( void* pData, KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * インデックスバッファを生成する
		 * @param	numIndex			[in] インデックスの数
		 * @param	indexFormat			[in] インデックスフォーマット
		 * @param	flags				[in] フラグ
		 * @return						インデックスバッファのポインタ
		 */
		virtual KsIndexBuffer*			createIndexBuffer( KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags );

		/**
		 * インデックスバッファを生成する
		 * @param	pData				[in] データ読み込み用のポインタ
		 * @param	size				[in] データサイズ
		 * @param	numIndex			[in] インデックスの数
		 * @param	indexFormat			[in] インデックスフォーマット
		 * @param	flags				[in] フラグ
		 * @return						インデックスバッファのポインタ
		 */
		virtual KsIndexBuffer*			createIndexBuffer( void* pData, KsUInt32 size, KsUInt32 numIndex, KsUInt32 indexFormat, KsUInt32 flags );

		/**
		 * 定数バッファを生成する
		 * @param	pData				[in] データ読み込み用のポインタ
		 * @param	size				[in] データサイズ
		 * @param	flags				[in] フラグ
		 * @return						定数バッファのポインタ
		 */
		virtual KsConstantBuffer*		createConstantBuffer( KsUInt32 size, KsUInt32 flags );

		/**
		 * 定数バッファを生成する
		 * @param	size				[in] バッファサイズ
		 * @param	flags				[in] フラグ
		 * @return						定数バッファのポインタ
		 */
		virtual KsConstantBuffer*		createConstantBuffer( void* pData, KsUInt32 size, KsUInt32 flags );

	protected:
		KsRenderSystemDX11*				m_RenderSystem;		/**< 描画システム	*/

};


#endif		/* __KSBUFFERMANAGERDX11_H__ */



