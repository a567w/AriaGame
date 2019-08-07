/************************************************************************************************/
/** 
 * @file		KsSwfTagType.h
 * @brief		SWFタグ
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFTAGTYPE_H__
#define __KSSWFTAGTYPE_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @enum		ksSWF_TAG_TYPE
 * @brief		SWFタグ
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
enum ksSWF_TAG_TYPE
{
	ksSWF_END					=  0,
	ksSWF_SHOWFRAME				=  1,
	ksSWF_DEFINESHAPE			=  2,
	/* 3 */
	ksSWF_PLACEOBJECT			=  4,
	ksSWF_REMOVEOBJECT			=  5,
	ksSWF_DEFINEBITS			=  6,
	ksSWF_DEFINEBUTTON			=  7,
	ksSWF_JPEGTABLES			=  8,
	ksSWF_SETBACKGROUNDCOLOR	=  9,

	ksSWF_DEFINEFONT			= 10,
	ksSWF_DEFINETEXT			= 11,
	ksSWF_DOACTION				= 12,
	ksSWF_DEFINEFONTINFO		= 13,
	ksSWF_DEFINESOUND			= 14,
	ksSWF_STARTSOUND			= 15,
	/* 16 */
	ksSWF_DEFINEBUTTONSOUND		= 17,
	ksSWF_SOUNDSTREAMHEAD		= 18,
	ksSWF_SOUNDSTREAMBLOCK		= 19,

	ksSWF_DEFINELOSSLESS		= 20,
	ksSWF_DEFINEBITSJPEG2		= 21,
	ksSWF_DEFINESHAPE2			= 22,
	ksSWF_DEFINEBUTTONCXFORM	= 23,
	ksSWF_PROTECT				= 24,
	/* 25 */
	ksSWF_PLACEOBJECT2			= 26,
	/* 27 */
	ksSWF_REMOVEOBJECT2			= 28,
	/* Sync Frmae 29 */
	/* 30 */
	/* Free All 31 */
	ksSWF_DEFINESHAPE3			= 32,
	ksSWF_DEFINETEXT2			= 33,
	ksSWF_DEFINEBUTTON2			= 34,
	ksSWF_DEFINEBITSJPEG3		= 35,
	ksSWF_DEFINELOSSLESS2		= 36,
	ksSWF_DEFINEEDITTEXT		= 37,
	/* 38 */
	ksSWF_DEFINESPRITE			= 39,
	/* Name Character 40 */
	ksSWF_PRODUCTIONINFO        = 41,
	/* DefineTextFormat 42 */
	ksSWF_FRAMELABEL			= 43,
	/* 44 */
	ksSWF_SOUNDSTREAMHEAD2		= 45,
	ksSWF_DEFINEMORPHSHAPE		= 46,
	/* GenerateFrame 47 */
	ksSWF_DEFINEFONT2			= 48,
	ksSWF_GENERATORCOMMAND      = 49,

	/* SWF Ver5.0 */
	// DefineCommandObject
	//Unknown encoding 	50 	Define 	?
	//CharacterSet
	//Unknown encoding 	51 	Define 	?
	//ExternalFont
	//Unknown encoding 	52 	Define 	?

	ksSWF_EXPORTASSETS			= 56,
	ksSWF_IMPORTASSETS			= 57,
	ksSWF_PROTECTDEBUG          = 58,
#if 0
	59	DoInitAction
	60	DefineVideoStream
	61	VideoFrame
	62	DefineFontInfo2
	63	DebugID
	64	EnableDebugger2
	65	ScriptLimits
	66	SetTabIndex
	67	-
	68	-
#endif
	ksSWF_FILEATTRIBUTES        = 69,
	ksSWF_PLACEOBJECT3          = 70,
	ksSWF_IMPORTASSETS2         = 71,
	ksSWF_DOABC                 = 72,
	ksSWF_DefineFontAlignZones  = 73,
	ksSWF_CSMTextSettings       = 74,
	ksSWF_DefineFont3           = 75,
	ksSWF_SymbolClass           = 76,
	ksSWF_METADATA              = 77,
	ksSWF_DefineScalingGrid		= 78,
	//-							  79,
	//-							  80,
	//-							  81,
	DoABC                       = 82,
	ksSWF_DEFINESHAPE4          = 83,
	DefineMorphShape2           = 84,
	//-							  85,
	ksSWF_DEFINESCENEANDFRAMELABELDATA= 86,
	DefineBinaryData            = 87,
	DefineFontName              = 88,
	StartSound2                 = 89,
	ksSWF_DEFINEBITSJPEG4       = 90,
	DefineFont4                 = 91,
};

#endif /* __KSSWFTAGTYPE_H__ */
