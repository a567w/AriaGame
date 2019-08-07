/************************************************************************************************/
/** 
 * @file		KsVertexShaderDX11.h
 * @brief		頂点シェーダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSVERTEXSHADERDX11_H__
#define __KSVERTEXSHADERDX11_H__

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
 * @class		KsVertexShaderDX11
 * @brief		頂点シェーダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksDEVDX11_API KsVertexShaderDX11 : public KsVertexShader
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * コンストラクタ
		 */
									KsVertexShaderDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual						~KsVertexShaderDX11();

		/**
		 * ファイルから頂点シェーダーを生成する
		 * @param	pFileName		ファイル名
		 * @param	shaderModel		シェーダーモデル
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		virtual KsBool				createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel );

		/**
		 * データから頂点シェーダーを生成する
		 * @param	pData			データ
		 * @param	dataSize		データサイズ
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		virtual KsBool				createFromMemory( const void* pData, KsUInt32 dataSize );

		/**
		 * 破棄処理
		 */
		virtual void				destroy();
	
		/**
		 * バッファのポインタを取得する
		 * @return					バッファのポインタ
		 */
		virtual const void*			getBufferPointer();

		/**
		 * バッファのサイズを取得する
		 * @return					バッファのサイズ
		 */
		virtual KsUInt32			getBufferSize();

	private:
		KsRenderSystemDX11*			m_pRenderSystem;
		ID3D11VertexShader*			m_pVertexShader;	/**< 頂点シェーダーオブジェクト		*/
		ID3DBlob*					m_pBlob;			/**< シェーダーオブジェクト			*/
		const void*					m_pData;			/**< バッファ						*/
		KsUInt32					m_dataSize;			/**< バッファサイズ				*/

};


#endif		/* __KSVERTEXSHADERDX11_H__ */

