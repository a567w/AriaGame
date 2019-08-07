/************************************************************************************************/
/** 
 * @file		KsVertexShader.h
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSVERTEXSHADER_H__
#define __KSVERTEXSHADER_H__

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
 * @class		KsVertexShader
 * @brief		頂点シェーダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		
 */
/************************************************************************************************/
class ksENGINE_API KsVertexShader : public KsShaderProgram
{
		friend class KsShaderManager;
	public:
		/**
		 * コンストラクタ
		 */
									KsVertexShader();

		/**
		 * デストラクタ
		 */
		virtual						~KsVertexShader();

		/**
		 * バッファのポインタを取得する
		 * @return					バッファのポインタ
		 */
		virtual const void*			getBufferPointer() = 0;

		/**
		 * バッファのサイズを取得する
		 * @return					バッファのサイズ
		 */
		virtual KsUInt32			getBufferSize() = 0;
};


#endif		/* __KSVERTEXSHADER_H__ */

