/************************************************************************************************/
/** 
 * @file		KsIndexBufferDX.h
 * @brief		インデックスバッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSINDEXBUFFERDX_H__
#define __KSINDEXBUFFERDX_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsIndexBuffer.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsIndexBufferDX
 * @brief		インデックスバッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsIndexBufferDX : public KsIndexBuffer
{
	public:
		/**
		 * インデックスバッファを生成する
		 * @param	pDevice			デバイス
		 * @param	numIndex		インデックスの数
		 * @param	flags			フラグ
		 */
									KsIndexBufferDX( IDirect3DDevice9* pDevice, KsUInt32 numIndex, KsUInt32 flags=D3DPOOL_DEFAULT );

		/**
		 * デストラクタ
		 */
		virtual					~KsIndexBufferDX();

		/**
		 * インデックスバッファをロックする
		 * @param	startIndex		ロックする先頭のインデックス
		 * @param	numIndex		ロックするインデックスの数
		 * @param	flags			ロックフラグ
		 * @return					ロックしたバッファの先頭ポインタ
		 */
		virtual void*				lock( KsUInt32 startIndex, KsUInt32 numIndex, KsUInt32 flags );

		/**
		 * インデックスバッファのロックを解除する
		 */
		virtual void				unlock();

		/**
		 * インデックスバッファからの読み込み
		 * @param	pData			データ読み込み用のポインタ
		 * @param	startIndex		ロックする先頭のインデックス
		 * @param	numIndex		ロックするインデックスの数
		 */
		virtual void				read( void* pData, KsUInt32 startIndex, KsUInt32 numIndex );

		/**
		 * インデックスバッファへの書き込み
		 * @param	pData			書き込みデータのポインタ
		 * @param	startIndex		ロックする先頭のインデックス
		 * @param	numIndex		ロックするインデックスの数
		 */
		virtual void				write( void* pData, KsUInt32 startIndex, KsUInt32 numIndex );

		/**
		 * インデックスバッファバッファを取得
		 * @return					インデックスバッファのポインタ
		 */
		IDirect3DIndexBuffer9*		getIndexBuffer() { return m_pIndexBuffer; }

	private:
		IDirect3DIndexBuffer9*		m_pIndexBuffer;	/**< DirectXインデックスバッファ		*/
};

#endif		/* __KSINDEXBUFFERDX_H__ */


