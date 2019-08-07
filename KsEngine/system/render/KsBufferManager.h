/************************************************************************************************/
/** 
 * @file		KsBufferManager.h
 * @brief		バッファマネージャ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBUFFERMANAGER_H__
#define __KSBUFFERMANAGER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"
#include "KsSingleton.h"
#include "KsVertexBuffer.h"
#include "KsIndexBuffer.h"

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
class KsBufferManager : public KsSingleton< KsBufferManager >
{
	public:
		/**
		 * コンストラクタ
		 */
										KsBufferManager(){}

		/**
		 * デストラクタ
		 */
		virtual						~KsBufferManager(){}

		/**
		 * 頂点バッファを生成する
		 * @param		vertexSize		頂点サイズ
		 * @param		numVertex		頂点数
		 * @param		vertexFormat	頂点フォーマット
		 * @param		flags			フラグ
		 * @return						頂点バッファのポインタ
		 */
		virtual KsVertexBuffer*		createVertexBuffer( KsUInt32 vertexSize, KsUInt32 numVertex, KsUInt32 vertexFormat, KsUInt32 flags ) = 0;

		/**
		 * インデックスバッファを生成する
		 * @param		numIndex		インデックス数
		 * @param		flags			フラグ
		 * @return						インデックスバッファのポインタ
		 */
		virtual KsIndexBuffer*			createIndexBuffer( KsUInt32 numIndex, KsUInt32 flags ) = 0;

		/**
		 * シングルトンの参照を取得
		 * @return						シングルトンの参照
		 */
		static KsBufferManager&			getInstance();
		
		/**
		 * シングルトンのポインタを取得
		 * @return						シングルトンのポインタ
		 */
		static KsBufferManager*			getInstancePtr();
};

#endif		/* __KSBUFFERMANAGER_H__ */



