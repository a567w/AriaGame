/************************************************************************************************/
/** 
 * @file		KsHash.h
 * @brief		ハッシュ
 * @author		Tsukasa Kato
 * @date		2008/02/06
 * @since		2008/02/06
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSHASH_H__
#define __KSHASH_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/
#define ksHASH_DEFAULT_SIZE		( 256 )		/**< デフォルトのハッシュサイズ	*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @class		KsHashNode
 * @brief		ハッシュノード
 * @date		2008/02/06
 * @since		2008/02/06
 * @version		1.0.0
 */
/************************************************************************************************/
template < typename T > class KsHashNode
{
	public:
		typedef KsHashNode< T >	KsHashNodeType;

	public:
		KsUInt32					m_key;			/**< ハッシュキー			*/
		KsString					m_string;		/**< 文字列					*/
		T							m_pData;		/**< データ					*/
		KsHashNodeType*				m_pNext;		/**< 次のノードのポインタ		*/
};

/************************************************************************************************/
/**
 *	@class		KsHashTable
 *	@brief		ハッシュテーブル
 *	@since		2005/10/25
 *	@author		tukasa kato
 */
/************************************************************************************************/
template < typename T > class KsHashTable
{
	public:
		typedef KsHashNode< T >			KsHashNodeType;

	protected:
		KsInt32							m_size;		/**< テーブルサイズ		*/
		KsHashNodeType**				m_pTbl;		/**< ハッシュテーブル		*/

	public:
		/**
		 * コンストラクタ
		 * @param	size		ハッシュサイズ
		 */
		KsHashTable( KsInt32 size=ksHASH_DEFAULT_SIZE )
		{
			m_size = size;
			m_pTbl = new KsHashNodeType* [ m_size ];

			for( KsInt32 i=0; i<m_size; i++ ){
				m_pTbl[ i ] = NULL;
			}
		}
	
		/**
		 * デストラクタ
		 */
		virtual							~KsHashTable()
		{
			clear();
			delete [] m_pTbl;
		}

		/**
		 * @param	size		ハッシュサイズ
		 */
		void							create( KsInt32 size=ksHASH_DEFAULT_SIZE )
		{
			destory();

			m_size = size;
			m_pTbl = new KsHashNodeType* [ m_size ];

			for( KsInt32 i=0; i<m_size; i++ ){
				m_pTbl[ i ] = NULL;
			}
		}

		/**
		 * 破棄処理
		 */
		void							destory()
		{
			clear();
			ksDELETEARRAY( m_pTbl );
			m_size = 0;
			m_pTbl = 0;
		}

		/**
		 * ハッシュノードを検索する
		 * @param	pString		検索文字
		 * @return				ハッシュノード
		 */
		KsHashNodeType*					find( const KsChar* pString )
		{
			KsChar*				pStr  = const_cast<KsChar*>(pString);
			KsUInt32			key   = KsCrc32( (KsUInt8*)pStr );
			KsUInt32			idx   = key % m_size;
			KsHashNodeType*		pNode = m_pTbl[ idx  ];

			while( pNode ){
				if( pNode->m_key == key ){
					if( pNode->m_string == pString ){
						return pNode;
					}
				}
				pNode = pNode->m_pNext;
			}

			return NULL;
		}

		/**
		 * ハッシュノードを検索する
		 * @param	pString		検索文字
		 * @return				ハッシュノード
		 */
		KsHashNodeType*					find( const KsString& refString )
		{
			KsChar*				pStr  = const_cast<KsChar*>(refString.c_str());
			KsUInt32			key   = KsCrc32( (KsUInt8*)pStr );
			KsUInt32			idx   = key % m_size;
			KsHashNodeType*		pNode = m_pTbl[ idx  ];

			while( pNode )
			{
				if( pNode->m_key == key )
				{
					if( pNode->m_string == refString )
					{
						return pNode;
					}
				}
				pNode = pNode->m_pNext;
			}

			return NULL;
		}

		/**
		 * ハッシュノードを検索する
		 * @param	key			検索キー
		 * @param	idx			検索インデックス
		 * @param	pString		検索文字
		 * @return				ハッシュノード
		 */
		KsHashNodeType*					find( KsUInt32 key, KsUInt32 idx, const KsChar* pString )
		{
			KsHashNodeType*		pNode = m_pTbl[ idx ];

			while( pNode ){
				if( pNode->m_key == key ){
					if( pNode->m_string == pString ){
						return pNode;
					}
				}
				pNode = pNode->m_pNext;
			}

			return NULL;
		}

		/**
		 * ハッシュノードを検索する
		 * @param	key			検索キー
		 * @param	idx			検索インデックス
		 * @param	pString		検索文字
		 * @return				ハッシュノード
		 */
		KsHashNodeType*					find( KsUInt32 key, KsUInt32 idx, const KsString& refString )
		{
			KsHashNodeType*		pNode = m_pTbl[ idx ];

			while( pNode ){
				if( pNode->m_key == key ){
					if( pNode->m_string == refString ){
						return pNode;
					}
				}
				pNode = pNode->m_pNext;
			}

			return NULL;
		}

		/**
		 * ノードを追加する
		 * @param	pString		検索文字
		 * @param	pData		データ
		 * @retval	ksTRUE		成功
		 * @retval	ksTRUE		失敗
		 */
		KsBool							add( const KsChar* pString, T pData )
		{
			KsChar*				pStr  = const_cast<KsChar*>(pString);
			KsUInt32			key   = KsCrc32( (KsUInt8*)pStr );
			KsUInt32			idx   = key % m_size;
			KsHashNodeType*		pNode = find( key, idx, pString );

			if( !pNode )
			{
				pNode = new KsHashNodeType();
				pNode->m_key    = key;
				pNode->m_string = pString;
				pNode->m_pData  = pData;
				pNode->m_pNext  = m_pTbl[ idx ];
				m_pTbl[ idx ]   = pNode;

				return ksTRUE;
			}
		
			/* 値を変える */

			return ksFALSE;
		}

		/**
		 * ノードを追加する
		 * @param	pString		検索文字
		 * @param	pData		データ
		 * @retval	ksTRUE		成功
		 * @retval	ksTRUE		失敗
		 */
		KsBool							add( const KsString& refString, T pData )
		{
			KsChar*				pStr  = const_cast<KsChar*>(refString.c_str());
			KsUInt32			key   = KsCrc32( (KsUInt8*)pStr );
			KsUInt32			idx   = key % m_size;
			KsHashNodeType*		pNode = find( key, idx, refString );

			if( !pNode )
			{
				pNode = new KsHashNodeType();
				pNode->m_key    = key;
				pNode->m_string = refString;
				pNode->m_pData  = pData;
				pNode->m_pNext  = m_pTbl[ idx ];
				m_pTbl[ idx ]   = pNode;

				return ksTRUE;
			}
		
			/* 値を変える */

			return ksFALSE;
		}

		/**
		 * 削除
		 * @param	pString		検索文字
		 * @return				データ
		 */
		T								destroy( const KsChar* pString )
		{
			KsChar*				pStr  = const_cast<KsChar*>(pString);
			KsUInt32			key   = KsCrc32( (KsUInt8*)pStr );
			KsUInt32			idx   = key % m_size;
			KsHashNodeType*		pNode = m_pTbl[ idx ];

			if( pNode )
			{
				/* 先頭だけチェック */
				if( key == pNode->m_key ){
					if( pNode->m_string == pString ){
						T					pData = pNode->m_pData;
						m_pTbl[ idx  ] = pNode->m_pNext;
						delete pNode;
						return pData;
					}
				}
			
				while( pNode->m_pNext )
				{
					if( key == pNode->m_pNext->m_key )
					{
						if( pNode->m_string == pString )
						{
							KsHashNodeType*		pTemp = pNode->m_pNext;
							T					pData = pTemp->m_pData;
							pNode->m_pNext = pTemp->m_pNext;
							delete pTemp;
							return pData;
						}
					}
					pNode = pNode->m_pNext;
				}
			}

			return NULL;
		}

		/**
		 * クリア
		 */
		void							clear()
		{
			for( KsInt32 i=0; i<m_size; i++ )
			{
				KsHashNodeType*		pNode = m_pTbl[ i ];
				KsHashNodeType*		pTemp;

				while( pNode )
				{
					pTemp = pNode;
					pNode = pNode->m_pNext;
					delete pTemp;
				}
			}
		}

		// これも固定メモリーを使ったほうがいいかも
		//KsMemoryFix						m_nodeWork;		/* 固定メモリ	*/
};


#endif		/* __KSHASH_H__	*/

