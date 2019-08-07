/************************************************************************************************/
/** 
 * @file		KsShaderManagerHLSL.h
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSSHADERMANAGERHLSL_H__
#define __KSSHADERMANAGERHLSL_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsTypeD3D9.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderSystemDX;

/************************************************************************************************/
/**
 * @class		KsShaderManager
 * @brief		シェーダーマネージャー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		本当は、ハッシュテーブルなどを使用したほうがいいがあまりテクスチャマテリアルは、
 *				あまり、使わないはずなので線形で探索する。
 */
/************************************************************************************************/
class ksDEVD3D9_API KsShaderManagerHLSL : public KsShaderManager
{
	public:
		/**
		 * コンストラクタ
		 * @param	pRenderSystem		描画システム
		 */
										KsShaderManagerHLSL( KsRenderSystemDX* pRenderSystem );

		/**
		 * デストラクタ
		 */
		virtual						~KsShaderManagerHLSL();

		/**
		 * ファイルからシェーダーを生成
		 * @param	pName				シェーダー名
		 * @param	bCompiled			コンパイル済みかどうかのフラグ
		 * @return						シェーダーデータのポインタ
		 */
		virtual KsShader*				createFromFile( const KsChar* pName, KsBool _bCompiled );

		/**
		 * リソースからシェーダーを生成
		 * @param	pName				シェーダー名
		 * @param	bCompiled			コンパイル済みかどうかのフラグ
		 * @return						シェーダーデータのポインタ
		 */
		virtual KsShader*				createFromResource( const KsChar* pName, KsBool _bCompiled );

		virtual void					setVertexShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count );
		virtual void					setVertexShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count );
		virtual void					setVertexShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count );

		virtual void					setPixelShaderConstantB( KsUInt32 startRegister, const KsBool*  pConstantData, KsUInt32 count );
		virtual void					setPixelShaderConstantF( KsUInt32 startRegister, const KsReal*  pConstantData, KsUInt32 count );
		virtual void					setPixelShaderConstantI( KsUInt32 startRegister, const KsInt32* pConstantData, KsUInt32 count );

	private:
		D3DXHANDLE						m_handls[ ksSHADER_GLOBAL_DATA_MAX ];	/**< ハンドルリスト	*/
		KsRenderSystemDX*				m_pRenderSystem;						/**< 描画システム	*/
};

#endif		/* __KSSHADERMANAGERHLSL_H__ */

