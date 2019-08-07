/************************************************************************************************/
/** 
 * @file		KsBufferManagerDX.h
 * @brief		バッファマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBUFFERMANAGERDX_H__
#define __KSBUFFERMANAGERDX_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsBufferManager.h"
#include "KsVertexBufferDX.h"
#include "KsIndexBufferDX.h"

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
class KsBufferManagerDX : public KsBufferManager
{
	public:
		/**
		 * コンストラクタ
		 */
										KsBufferManagerDX( IDirect3DDevice9* pDevice ) : m_pDevice( pDevice ) {}

		/**
		 * デストラクタ
		 */
		virtual						~KsBufferManagerDX(){}

		/**
		 * 頂点バッファを生成する
		 * @param		vertexSize		頂点サイズ
		 * @param		numVertex		頂点数
		 * @param		vertexFormat	頂点フォーマット
		 * @param		flags			フラグ
		 * @return						頂点バッファのポインタ
		 */
		virtual KsVertexBuffer*		createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags );

		/**
		 * インデックスバッファを生成する
		 * @param		numIndex		インデックス数
		 * @param		flags			フラグ
		 * @return						インデックスバッファのポインタ
		 */
		virtual KsIndexBuffer*			createIndexBuffer( KsUInt32 numIndex, KsUInt32 flags );

	protected:
		IDirect3DDevice9*				m_pDevice;		/**< デバイス	*/

};

#endif		/* __KSBUFFERMANAGERDX_H__ */



