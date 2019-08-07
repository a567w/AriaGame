/************************************************************************************************/
/**
 * @file		KsQueue.h
 * @brief		キュー
 * @author		Tsukasa Kato
 * @date		2008/02/06
 * @since		2008/02/06
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSQUEUE_H__
#define __KSQUEUE_H__

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
 * @class		KsQueue
 * @brief		キュー
 * @author		Tsukasa Kato
 * @date		2004/03/30
 * @version		1.0.0
 */
/************************************************************************************************/
template < typename T, KsInt32 max > class KsQueue
{
	public:
		typedef T					valueType;

	public:
		/**
		 * コンストラクタ
		 */
									KsQueue() : m_top( 0 ), m_end( 0 ), m_size( 0 ) {}
	
		/**
		 * デストラクタ
		 */
									~KsQueue() {}

		/**
 		 * スタックが空かどうかをチェックする
		 * @retval		ksTRUE			空です
		 * @retval		ksFALSE			空じゃない
		 */
		KsBool						empty() const { return ( m_size == 0 ); }

		/**
		 * データを格納します
		 * @param		T				格納するデータ
		 */
		void						push( const T& data )
		{
			if( m_size < max ){
				m_data[ m_end ] = data;
				if( ++m_end > max-1 ){
					m_end = 0;
				}
				m_size++;
			}	
		}
	
		/**
		 * データを取り出します
		 * @return						一つ前格納したデータ
		 */
		T&							pop() 
		{
			if( m_size > 0 ){
				KsInt32		top = m_top;
				if( ++m_top > max-1 ){
					m_top = 0;
				}
				m_size--;
				return m_data[ top ];
			}
			return m_data[ 0 ];
		}

		/**
		 * データを取り出します
		 * @return						一つ前格納したデータ
		 */
		const T&					pop() const 
		{
			if( m_size > 0 ){
				KsInt32		top = m_top;
				if( ++m_top > max-1 ){
					m_top = 0;
				}
				m_size--;
				return m_data[ top ];
			}
			return m_data[ 0 ];
		}

		/**
		 * データを取り出します
		 * @return						一つ前格納したデータ
		 */
		T&							top() { return m_data[ m_top ]; }

		/**
		 * データを取り出します
		 * @return						一つ前格納したデータ
		 */
		const T&					top() const { return m_data[ m_top ]; }

		/**
		 * データを取り出します
		 * @return						一つ前格納したデータ
		 */
		T&							end()
		{
			if( m_end ){
				return m_data[ m_end-1 ];
			}
			return m_data[ 0 ];
		}

		/**
		 * データを取り出します
		 * @return						一つ前格納したデータ
		 */
		const T&					end() const
		{
			if( m_end ){
				return m_data[ m_end-1 ];
			}
			return m_data[ 0 ];
		}

		/**
		 * 指定データを取得します。
		 * @param  		num				先頭からのデータ番号
		 * @return						データ
		 */
		T&							getData( KsInt32 num ) 
		{
			if( num < max ){
				KsInt32	index = m_top + num;
				if( index > max-1 ){
					index = 0;
				}
				return m_data[ index ];
			}
			return m_data[ 0 ];
		}

		/**
		 * 指定データを取得します。
		 * @param  		num				先頭からのデータ番号
		 * @return						データ
		 */
		const T&					getData( KsInt32 num ) const 
		{
			if( num < max ){
				KsInt32	index = m_top + num;
				if( index > max-1 ){
					index = 0;
				}
				return m_data[ index ];
			}
			return m_data[ 0 ];
		}
	
		/**
		 * 値を変える
		 * @param		index			書き換えるデータのインデックス
		 * @param		data			データ
		 */
		void						swap( KsInt32 index, const T& data )
		{
			m_data[ index ] = data;
		}

		/**
		 * クリアーする
		 */
		void						clear() { m_top = 0; m_end = 0; m_size = 0; }

		/**
		 * 現在格納されているデータの数を取得
		 * @return						格納されているデータの数
		 */
		KsInt32						size()	const { return m_size;	}
	
		/**
		 * 格納できるデータの数を取得
		 * @return						格納できるデータの数
		 */
		KsInt32						getMax()	const { return max;	}

	private:
		T							m_data[ max ];		/**< データ						*/
		KsInt32						m_top;				/**< キュー内データの先頭位置		*/
		KsInt32						m_end;				/**< キュー内データの最後位置		*/
		KsInt32						m_size;				/**< 格納されているデータの数		*/
};

#endif	/* __KSQUEUE_H__ */


