/************************************************************************************************/
/** 
 * @file		KsStringFixed.h
 * @brief		文字列操作
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSTRINGFIXED_H__
#define __KSSTRINGFIXED_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
//#include "system/KsCore.h"

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/
#define ksSTRING_LENGTH		( 512 )		/**< 最大の操作文字列数 */

/************************************************************************************************/
/**
 * @class		KsStringFixed
 * @brief		文字列操作(固定256バイト)
 * @author		Tsukasa Kato
 * @date		2004/03/30
 */
/************************************************************************************************/
class ksENGINE_API KsStringFixed
{
	public:
		/**
		 * コンストラクタ
		 */
									KsStringFixed() : m_length( 0 ) { m_string[ 0 ] = '\0'; }

		/**
		 * コンストラクタ
		 * @param		string		文字列クラスの参照
		 */
									KsStringFixed( const KsStringFixed& string );

		/**
		 * コンストラクタ
		 * @param		pString		文字列のポインタ
		 */
									KsStringFixed( const KsChar* pString );

		/**
		 * デストラクタ
		 */
									~KsStringFixed();

		/**
		 * 文字列の長さを取得する
		 * @return					文字列の長さ
		 */
		KsUInt32					length() const { return m_length; }

		/**
		 * 文字列のバッファ取得
		 * @return					文字列の先頭ポインタ
		 */
		const KsChar*				c_str() const { return m_string; }

		/**
		 * 空かどうかをチェックする
		 * @retval		ksTRUE		空です
		 * @retval		ksFALSE		空でない
		 */
		KsBool						empty() const { return ( !m_length ); }

		/**
		 * 指定範囲の文字を削除する
		 * @param		top			消す文字列の先頭
		 * @param		num			消す文字列の数
		 */
		void						erase( KsUInt32 top, KsUInt32 num );

		/**
		 * 文字列をクリア
		 */
		void						clear();

		/**
		 * 指定インデックスの文字を取得する( operator )
		 * @param	index			取得するインデックス
		 * @return					文字
		 */
		KsChar&						operator []( KsUInt32 index )		{ return m_string[ index ]; }
	
		/**
		 * 指定インデックスの文字を取得する( operator )
		 * @param	index			取得するインデックス
		 * @return					文字
		 */
		const KsChar&				operator []( KsUInt32 index ) const { return m_string[ index ]; }

		KsStringFixed&				operator=(const KsStringFixed& string );
		KsStringFixed&				operator=(const KsChar* string );
		KsStringFixed&				operator=(const KsChar c );

		KsStringFixed&				operator+=(const KsStringFixed& string );
		KsStringFixed&				operator+=(const KsChar* string );
		KsStringFixed&				operator+=(const KsChar c );

		KsStringFixed					operator+(const KsStringFixed& string );
		KsStringFixed					operator+(const KsChar* pString );
		KsStringFixed					operator+(const KsChar c );

		KsBool						operator==( const KsChar* pString ) const { return ( 0 == ks_strcmp( m_string, pString ) ); }
		KsBool						operator==( const KsStringFixed& string ) const { return ( 0 == ks_strcmp( m_string, string.c_str() ) ); }
	
		KsBool						operator!=( const KsChar* pString ) const { return ks_strcmp( m_string, pString ); }
		KsBool						operator!=( const KsStringFixed& string ) const { return ks_strcmp( m_string, string.c_str() ); }

	private:
		KsChar						m_string[ ksSTRING_LENGTH ];	/**< 文字列			*/
		KsUInt32					m_length;						/**< 文字列の長さ	*/
};


#endif		/* __KSSTRINGFIXED_H__ */

