/************************************************************************************************/
/** 
 * @file		KsSwfPlaceObject.h
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSWFPLACEOBJECT_H__
#define __KSSWFPLACEOBJECT_H__

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
 * @class		KsSwfPlaceObject
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class ksSWF_API KsSwfPlaceObject : public KsSwfCommand
{
	public:
		/**
		 * コンストラクタ
		 */
								KsSwfPlaceObject( KsFileObject* pFile );

		/**
		 * デストラクタ
		 */
		virtual					~KsSwfPlaceObject();

		/**
		 * コマンド実行
		 */
		virtual void			execute();

	private:
		KsUInt16				m_characterId;		/**< 配置するキャラクタの ID		*/
		KsUInt16				m_depth;			/**< キャラクタの深度				*/
		KsSwfMatrix				m_matrix;			/**< 変形行列データ				*/
		KsSwfCxform				m_cxf;				/**< 色変換データ				*/
};

/************************************************************************************************/
/**
 * @class		KsSwfPlaceObject2
 * @brief		SWFコマンド
 * @author		Tsukasa Kato
 * @date		2005/10/17
 * @since		2005/10/17
 * @version		1.0.0
 * @note		なし
 */
/************************************************************************************************/
class ksSWF_API KsSwfPlaceObject2 : public KsSwfCommand
{
	public:
		/**
		 * コンストラクタ
		 */
								KsSwfPlaceObject2( KsFileObject* pFile );

		/**
		 * デストラクタ
		 */
		virtual					~KsSwfPlaceObject2();

		/**
		 * コマンド実行
		 */
		virtual void			execute();

	private:
		KsUInt8					m_flags;			/**< 制御フラグ					*/
		KsUInt16				m_characterId;		/**< 配置するキャラクタの ID		*/
		KsUInt16				m_depth;			/**< キャラクタの深度				*/
		KsSwfMatrix				m_matrix;			/**< 変形行列データ				*/
		KsSwfCxform				m_cxf;				/**< 色変換データ				*/
		KsUInt16				m_ratio;			/**< 比率						*/
		KsString				m_name;				/**< キャラクタの名前				*/
		KsUInt16				m_clipDepth;		/**< Clip depth					*/
		KsUInt16				m_clipActions;		/**< クリップアクションデータ		*/
};

#endif	/* __KSSWFPLACEOBJECT_H__ */


