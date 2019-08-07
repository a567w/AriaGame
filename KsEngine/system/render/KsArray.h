/************************************************************************************************/
/** 
 * @file		KsArray.h
 * @brief		可変長配列(STLのvectorみたく)
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		0.1
 */
/************************************************************************************************/
#ifndef __KSARRAY_H__
#define __KSARRAY_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/
#include "KsType.h"

/************************************************************************************************/
/**
 *  可変長配列
 *	@class		KsArray
 *	@brief		配列
 *	@since		2003/10/25
 *	@author		tukasa kato
 */
/************************************************************************************************/
template <typename T> class KsArray
{
	public:
		/**
		 * コンストラクタ
		 */
									KsArray() : m_data( 0 ), m_allocSize( 0 ), m_size( 0 ) {}
		
		/**
		 * コンストラクタ
		 * @param	size			確保するサイズ
		 */
									KsArray( KsUInt32 size ) : m_data( 0 ), m_allocSize( 0 ), m_size( 0 ){ this->realloc( size ); }
					
		/**
		 * デストラクタ
		 */
									~KsArray(){ if( m_data ){ delete [] m_data; }	}

		/**
		 * 代入( operator )
		 * @param	other			代入する配列
		 */
		void						operator = ( const KsArray< T >& other )
		{
			if( m_data ){ delete [] m_data; }

			// サイズチェック
			if( other.allocSize == 0 )	{ m_data = 0; }
			else						{ m_data = new T[ other.allocSize ]; }

			// カウント
			m_size = other.m_size;
			
			// 確保サイズ
			allocSize = other.allocSize;

			for( KsUInt32 i=0; i<other.m_size; ++i ){ m_data[ i ] = other.m_data[ i ]; }
		}

		/**
		 * 配列内の要素を取得する( operator )
		 * @param	index			取得するインデックス
		 */
		T&							operator []( KsUInt32 index )		{ return m_data[ index ]; }
		
		/**
		 * 配列内の要素を取得する( operator )
		 * @param	index			取得するインデックス
		 */
		const T&					operator []( KsUInt32 index ) const { return m_data[ index ]; }

		/**
		 * 新しくメモリーを確保しなおす
		 * @param	size			新しく確保するサイズ
		 */
		void						realloc( KsUInt32 size )
		{
			T*	temp = m_data;
			
			m_data		= new T[ size ];
			m_allocSize = size;
			
			KsUInt32 end = m_size < size ? m_size : size;

			for( KsUInt32 i=0; i<end; ++i ){ m_data[ i ] = temp[ i ]; }

			if( m_allocSize < m_size ){ m_size = m_allocSize; }
			
			delete [] temp;
		}
		
		/**
		 * 配列に後ろから要素を追加する
		 * @param	data			追加する要素
		 */
		void						push_back( const T& data )
		{
			if( m_size + 1 > m_allocSize ){ this->realloc( m_size * 2 + 1 ); }

			m_data[ m_size++ ] = data;
		}
		
		/**
		 * 配列から削除する
		 * @param	index			消すデータのインデックス
		 */
		void						erase( KsUInt32 index )
		{
			// 指定インデックスのデータを消してデータを詰める
			for ( KsUInt32 i=index+1; i<m_size; ++i ){ m_data[ i-1 ] = m_data[ i ]; }

			--m_size;
		}

		/**
		 * 配列から削除する
		 * @param	index			消すデータのインデックス
		 * @param	count			指定インデックスから消す個数
		 */
		void						erase( KsUInt32 index, KsUInt32 count )
		{
			for( KsUInt32 i=(index + count); i<m_size; ++i ){
				m_data[ i-count ] = m_data[ i ];
			}

			m_size -= count;
		}
		
		/**
		 * 配列をクリアーする
		 */
		void						clear()
		{
			if( m_data ){ delete [] m_data; }
			m_data      = 0;
			m_allocSize = 0;
			m_size		= 0;
		}
		
		/**
		 * ポインタを取得する
		 * @return					配列のポインタ
		 */
		T*							pointer()				{ return m_data;			}
		
		/**
		 * 配列が空かどうかをチェックする
		 * @retval	ksTRUE			配列は空
		 * @retval	ksFALSE			空じゃない
		 */
		KsBool						empty()			const	{ return ( m_size == 0 );	}
		
		/**
		 * 確保するサイズ
		 * @return					確保されている配列の数
		 */
		KsUInt32					getAllocSize()	const	{ return m_allocSize;		}

		/**
		 * カウント数を取得する
		 * @return					使われている配列の数
		 */
		KsUInt32					size()			const	{ return m_size;			}

	private:
		T*							m_data;				/**< データを取得する			*/
		KsUInt32					m_allocSize;		/**< 確保サイズを取得する		*/
		KsUInt32					m_size;				/**< 配列の要素数を取得する	*/
};

#endif	/* __KSARRAY_H__ */
