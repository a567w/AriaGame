/************************************************************************************************/
/** 
 * @file		KsUserData.h
 * @brief		ユーザーデー管理
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSUSERDATA_H__
#define __KSUSERDATA_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

enum ksCHUNK_TYPE
{
	ksCHUNK_NONE,
	ksCHUNK_TOP,
	ksCHUNK_KMD,
	ksCHUNK_FORCE32 = 0x7fffffff,
};

class KsChunk
{
	public:
		KsChunk();


		~KsChunk();

	public:
		ksCHUNK_TYPE	m_chunkType;
		KsInt32			m_dataSize;
		KsInt32			m_nextChunk;
};

KsChunk::KsChunk()
	: m_chunkType( ksCHUNK_NONE )
	, m_dataSize( 0 )
	, m_nextChunk( 0 )
{
}

/************************************************************************************************/
/**
 * @class		KsUserData
 * @brief		ユーザーデータクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsUserData
{
		enum ksUSERDATA_ALLOC_TYPE
		{
			ksUSERDATA_ALLOC,
			ksUSERDATA_FREE,
		};

	public:
		/**
		 * コンストラクタ
		 */
								KsUserData();

		/**
		 * @param	size		確保するバッファのサイズ
		 */
								KsUserData( KsInt32 size );

		/*
		 * @param	pData		データ
		 * @param	size		サイズ
		 * @param	allocType	データの確保のタイプ
		 */
								KsUserData( KsByte* pData, KsInt32 size, KsBool allocType );

		/**
		 * デストラクタ
		 */
		virtual					~KsUserData();

		/*
		 * @param	size		確保するバッファのサイズ
		 */
		KsBool					create( KsInt32 size );

		/**
		 * @param	pData		データ
		 * @param	size		サイズ
		 * @param	allocType	データの確保のタイプ
		 */
		KsBool					create( KsByte* pData, KsInt32 size, KsBool allocType );

		/**
		 * 破棄する
		 */
		void					destroy();

		/**
		 * 指定チャンクへ移動する
		 * @param	chunk		チャンクタイプ
		 * @param	index		検索インデックス
		 * @return				チャンクデータのサイズ
		 * @return				データの位置
		 */
		KsInt32					findChunkSize( ksCHUNK_TYPE chunk, KsInt32 index=0 );

		/**
		 * 指定チャンクへ移動する
		 * @param	chunk		チャンクタイプ
		 * @param	index		検索インデックス
		 * @return				チャンクデータのサイズ
		 * @return				データの位置
		 */
		KsByte*					findChunk( ksCHUNK_TYPE chunk, KsInt32 index=0 );

		/**
		 * 指定チャンクからデータを読み込む
		 * @param	pBuffer		読み込みようバッファ
		 * @param	size		読み込みようバッファのサイズ
		 * @param	chunk		チャンクタイプ
		 * @param	index		検索インデックス
		 * @return				チャンクデータのサイズ
		 */
		KsInt32					read( KsByte* pBuffer, KsInt32 size, ksCHUNK_TYPE chunk, KsInt32 index=0 );

		/**
		 * 現在位置から指定サイズ読み込む
		 * @param	pBuffer		読み込みようバッファ
		 * @param	size		読み込みようバッファのサイズ
		 * @return				読み込んだサイズ
		 */
		KsInt32					read( KsByte* pBuffer, KsInt32 size );

		/**
		 * 指定チャンクから指定サイズ書き込む
		 * @param	pBuffer		書き込むデータ
		 * @param	size		書き込むデータサイズ
		 * @param	chunk		チャンクタイプ
		 * @param	index		検索インデックス
		 * @return				書き込んだサイズ
		 */
		KsInt32					write( KsByte* pBuffer, KsInt32 size, ksCHUNK_TYPE chunk, KsInt32 index=0 );

		/**
		 * 現在位置から指定サイズ書き込む
		 * @param	pBuffer		書き込むデータ
		 * @param	size		書き込むデータサイズ
		 * @return				書き込んだサイズ
		 */
		KsInt32					write( KsByte* pBuffer, KsInt32 size );

		/** 
		 * データのポインタ取得
		 * @param	pos			位置座標
		 * @return				データのポインタ
		 */
		KsByte*					getData( KsInt32 pos=0 ) { return &m_pData[ 0 ]; }

		/**
		 * サイズを取得する
		 * @return				ユーザーデータのサイズ
		 */
		KsInt32					getSize() const { return m_size; }

	protected:
		KsInt32					m_pos;			/**< 位置座標					*/
		KsByte*					m_pData;		/**< データ						*/
		KsInt32					m_size;			/**< バッファのサイズ				*/
		ksUSERDATA_ALLOC_TYPE	m_allocType;	/**< 自分で確保したデータかどうか	*/
};

#endif		/* __KSUSERDATA_H__ */



