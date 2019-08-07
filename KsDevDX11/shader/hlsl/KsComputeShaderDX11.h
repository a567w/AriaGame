/************************************************************************************************/
/** 
 * @file		KsComputeShaderDX11.h
 * @brief		コンピュートシェーダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSCOMPUTESHADERDX11_H__
#define __KSCOMPUTESHADERDX11_H__

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
 * @class		KsComputeShaderDX11
 * @brief		コンピュートシェーダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksDEVDX11_API KsComputeShaderDX11 : public KsComputeShader
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * コンストラクタ
		 */
									KsComputeShaderDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual						~KsComputeShaderDX11();

		/**
		 * ファイルから頂点シェーダーを生成する
		 * @param	pFileName		ファイル名
		 * @param	shaderModel		シェーダーモデル
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		virtual KsBool				createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel );

		/**
		 * データからコンピュートシェーダーを生成する
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
		ID3D11ComputeShader*		m_pComputeShader;	/**< コンピュートシェーダーオブジェクト	*/
		ID3DBlob*					m_pBlob;			/**< シェーダーオブジェクト				*/
		//KsShaderManagerDX11*		m_pShaderManager;	/**< シェーダーマネージャ				*/
};


#endif		/* __KSCOMPUTESHADERDX11_H__ */

