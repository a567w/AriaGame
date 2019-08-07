/************************************************************************************************/
/** 
 * @file		KsXmlChar.h
 * @brief		Xml文字
 * @author		Tsukasa Kato
 * @date		2004/10/17
 * @since		2004/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSXMLREADER_H__
#define __KSXMLREADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/


/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/

enum KsXmlNodeType
{
	ksXmlNone					= 0,
	ksXmlElement				= 1,
	ksXmlAttribute				= 2,
	ksXmlText					= 3,
	ksXmlCDATA					= 4,
	ksXmlEntityReference		= 5,
	ksXmlEntity					= 6,
	ksXmlProcessingInstruction	= 7,
	ksXmlComment				= 8,
	ksXmlDocument				= 9,
	ksXmlDocumentType			= 10,
	ksXmlDocumentFragment		= 11,
	ksXmlNotation				= 12,
	ksXmlWhitespace				= 13,
	ksXmlSignificantWhitespace	= 14,
	ksXmlEndElement				= 15,
	ksXmlEndEntity				= 16,
	ksXmlDeclaration			= 17,
};

enum KsXmlReadState
{
	ksXmlInitial		= 0,
	ksXmlInteractive	= 1,
	ksXmlError			= 2,
	ksXmlEndOfFile		= 3,
	ksXmlClosed			= 4,
};

class ksENGINE_API KsXmlException
{
	public:
		KsXmlException( const std::string& strErrorName ) : m_str(strErrorName) {}	
		
		virtual std::string	getError() const { return m_str; }
		
		std::string				m_str;
};

#endif	/* __KSXMLREADER_H__ */

