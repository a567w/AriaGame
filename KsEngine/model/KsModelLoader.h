/************************************************************************************************/
/** 
 * @file		KsModelLoader.h
 * @brief		モデルローダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMODELLOADER_H__
#define __KSMODELLOADER_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsModelLoader
 * @brief		モデルローダー
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsModelLoader
{
	public:
		/**
		 * コンストラクタ
		 */
									KsModelLoader();

		/**
		 * デストラクタ
		 */
		virtual						~KsModelLoader();
};


#endif		/* __KSMODELLOADER_H__ */



