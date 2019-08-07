/************************************************************************************************/
/** 
 * @file		KsBufferObject.h
 * @brief		バッファオブジェクト
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBUFFEROBJECT_H__
#define __KSBUFFEROBJECT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsRenderContext;

/************************************************************************************************/
/**
 * @struct		KS_BUFFER_DESC
 * @brief		バッファDECS
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
typedef struct KS_BUFFER_DESC
{
    KsUInt32		ByteWidth;
    KsUInt32		Usage;
    KsUInt32		BindFlags;
    KsUInt32		CPUAccessFlags;
    KsUInt32		MiscFlags;
    KsUInt32		StructureByteStride;

} KS_BUFFER_DESC;


/************************************************************************************************/
/**
 * @class		KsIndexBuffer
 * @brief		インデックスバッファ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsBufferObject : public KsRefCounter
{
	public:
		/**
		 * コンストラクタ
		 */
									KsBufferObject();

		/**
		 * デストラクタ
		 */
		virtual						~KsBufferObject();

		/**
		 * 破棄処理
		 */
		virtual void				destroy() = 0;

		/**
		 * リソースを取得する
		 * @return					 リソース
		 */
		virtual void*				getBufferResource() = 0;

		/**
		 * インデックスバッファをロックする
		 * @param	pContext		描画コンテキスト
		 * @param	flags			ロックフラグ
		 * @return					ロックしたバッファの先頭ポインタ
		 */
		virtual void*				lock( const KsRenderContext* pContext, KsUInt32 flags ) = 0;

		/**
		 * インデックスバッファのロックを解除する
		 * @param	pContext		描画コンテキスト
		 */
		virtual void				unlock( const KsRenderContext* pContext ) = 0;

		/**
		 * インデックスバッファからの読み込み
		 * @param	pContext		描画コンテキスト
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 */
		virtual void				read( const KsRenderContext* pContext, void* pData, KsUInt32 size ) = 0;

		/**
		 * インデックスバッファへの書き込み
		 * @param	pContext		描画コンテキスト
		 * @param	pData			データ読み込み用のポインタ
		 * @param	size			データサイズ
		 */
		virtual void				write( const KsRenderContext* pContext, void* pData, KsUInt32 size ) = 0;
};

#endif		/* __KSBUFFEROBJECT_H__ */



