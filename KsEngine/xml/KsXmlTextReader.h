/************************************************************************************************/
/** 
 * @file		KsString.h
 * @brief		文字列操作
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSXMLTEXTREADER_H__
#define __KSXMLTEXTREADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/
#define ksXML_TEXT_READER_BUFFER_SIZE		( 1024 * 1024 )
#define ksXML_ATTRIBUTE_WORK_SIZE			( 256 )

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsXmlAttribute
 * @brief		文字列操作
 * @author		Tsukasa Kato
 * @date		2004/03/30
 */
/************************************************************************************************/
class ksENGINE_API KsXmlAttribute
{
public:
	KsStringFixed			m_name;
	KsStringFixed			m_value;
};

/************************************************************************************************/
/**
 * @class		KsXmlAttributeWork
 * @brief		文字列操作
 * @author		Tsukasa Kato
 * @date		2004/03/30
 */
/************************************************************************************************/
class ksENGINE_API KsXmlAttributeWork
{
public:
	static KsXmlAttribute			m_work[ ksXML_ATTRIBUTE_WORK_SIZE ];
	static KsXmlAttribute*			m_stack[ ksXML_ATTRIBUTE_WORK_SIZE ];
	static KsInt32					m_index;
	static KsXmlAttribute*			allocAttribute();
	static void					freeAttribute( KsXmlAttribute* pAttribute );
	static void					create();
	static void					destory();
	static void					clear();
};

/************************************************************************************************/
/**
 * @class		KsXmlTextReader
 * @brief		文字列操作
 * @author		Tsukasa Kato
 * @date		2004/03/30
 */
/************************************************************************************************/
class ksENGINE_API KsXmlTextReader
{
	public:
		KsXmlTextReader();
		KsBool						create( const KsChar* pFileName );
		KsBool						create( KsFileObject& file );
		void						destroy();

		/**
		 * コンストラクタ
		 * @param	pFileName		ファイル名
		 */
									KsXmlTextReader( const KsChar* pFileName );

		/**
		 * コンストラクタ
		 * @param	pFileName		ファイル名
		 */
									KsXmlTextReader( KsFileObject& file );

		/**
		 * デストラクタ
		 */
		virtual					~KsXmlTextReader();

		/**
		 * タグ読み込み処理
		 * @retval	ksTRUE			読み込み
		 * @retval	ksFALSE			もう読み込むものはない
		 */
		KsBool						read();

		/**
		 * 次のアトリビュートに移動
		 * @retval	ksTRUE			読み込み
		 * @retval	ksFALSE			もう読み込むものはない
		 */
		KsBool						moveToNextAttribute();
		
		/**
		 * ノードのタイプを取得
		 */
		KsXmlNodeType				getNodeType() { return m_nodeType; }

		/**
		 * 名前
		 */
		const KsChar*				getName()	{ return m_pNameBuffer; }

		/**
		 *
		 */
		const KsChar*				getValue() { return m_pValueBuffer; }

	protected:
		KsInt32					readerPeek(){ return *m_pFileBuffer; }
		KsInt32					readerRead(){ return *m_pFileBuffer++; }

	private:
		KsFileBuffer				m_file;
		KsChar*						m_pFileBuffer;
		KsChar*						m_pNameBuffer;
		KsChar*						m_pValueBuffer;
		KsInt32					m_nameSize;
		KsInt32					m_valueSize;
		KsChar*						m_pAttributeNameBuffer;
		KsChar*						m_pAttributeValueBuffer;
		KsInt32					m_attributeNameSize;
		KsInt32					m_attributeValueSize;
		KsBool						m_hasPeek;
		KsBool						m_canSeek;
		KsInt32					m_peekChar;
		KsXmlReadState				m_readState;
		KsXmlNodeType				m_nodeType;
		KsArray<KsXmlAttribute*>	m_attributes;
		KsXmlAttribute*				m_pAttribute;
		KsInt32					m_attributeIndex;
		KsStringFixed				m_currentTag;
		void						close();
		KsInt32					readChar();
		KsInt32					peekChar();
		void						readTag();
		void						readStartTag();
		void						readEndTag();
		void						readProcessingInstruction();
		void						skipSpace();
		void						expect( KsInt32 expected );
		void						expect( const KsChar* expected );
	private:
		KsBool						readContent();
		void						readName();
		void						readAttributeName();
		void						readAttribute();
		void						readAttributes();
		void						clearAttributes();
	protected:
		void						readText();
		void						readDeclaration();
		void						readComment();
};


#endif /* __KSXMLTEXTREADER_H__ */


