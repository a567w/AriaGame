/************************************************************************************************/
/** 
 * @file		KsPixelShaderDX11.h
 * @brief		ピクセルシェーダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSPIXELSHADERDX11_H__
#define __KSPIXELSHADERDX11_H__

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
 * @class		KsPixelShaderDX11
 * @brief		ピクセルシェーダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksDEVDX11_API KsPixelShaderDX11 : public KsPixelShader
{
		friend class KsRenderContextDX11;
	public:
		/**
		 * コンストラクタ
		 */
									KsPixelShaderDX11( KsRenderSystemDX11* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual						~KsPixelShaderDX11();

		/**
		 * ファイルからピクセルシェーダーを生成する
		 * @param	pFileName		ファイル名
		 * @param	pEntryPoint		エントリーポイント
		 * @param	shaderModel		シェーダーモデル
		 * @retval	ksTRUE			生成成功
		 * @retval	ksFALSE			生成失敗
		 */
		virtual KsBool				createFromFile( const KsChar* pFileName, const KsChar* pEntryPoint, ksSHADER_MODEL_TYPE shaderModel );

		/**
		 * データからピクセルシェーダーを生成する
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

	private:
		KsRenderSystemDX11*			m_pRenderSystem;
		ID3D11PixelShader*			m_pPixelShader;
};


#endif		/* __KSPIXELSHADERDX11_H__ */

