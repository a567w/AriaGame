/************************************************************************************************/
/** 
 * @file		KsFont.h
 * @brief		フォント描画
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSFONT_H__
#define __KSFONT_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/


/************************************************************************************************/
/**
 * @enum		ksSPRITE_SORT_MODE
 * @brief		スプライトフォントモード
 * @since		2003/10/25
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
enum ksSPRITE_SORT_MODE
{
	ksSPRITE_SORT_MODE_DEFERRED,
	ksSPRITE_SORT_MODE_IMMEDIATE,
	ksSPRITE_SORT_MODE_TEXTURE,
	ksSPRITE_SORT_MODE_BACKTOFRONT,
	ksSPRITE_SORT_MODE_FRONTTOBACK,
};

/************************************************************************************************/
/**
 * @enum		ksSPRITE_SORT_MODE
 * @brief		スプライトフォントモード
 * @since		2003/10/25
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
enum ksSPRITE_EFFECTS
{
	ksSPRITE_EFFECTS_NONE             = 0,
	ksSPRITE_EFFECTS_FLIPHORIZONTALLY = 1,
	ksSPRITE_EFFECTS_FLIPVERTICALLY   = 2,
	ksSPRITE_EFFECTS_FLIPBOTH         = ksSPRITE_EFFECTS_FLIPHORIZONTALLY | ksSPRITE_EFFECTS_FLIPVERTICALLY,
};

/************************************************************************************************/
/**
 * @struct		KsGlyph
 * @brief		スプライトフォントモード
 * @since		2003/10/25
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
struct KsGlyph
{
	KsUInt32		Character;
	KsRect			Subrect;
	KsReal			XOffset;
	KsReal			YOffset;
	KsReal			XAdvance;
};

/************************************************************************************************/
/**
 * @class		KsFont
 * @brief		フォント描画クラス
 * @since		2003/10/25
 * @author		Tsukasa Kato
 */
/************************************************************************************************/
class ksENGINE_API KsFont
{
	public:
		/**
		 * コンストラクタ
		 */
									KsFont();
		/**
		 * コンストラクタ
		 * @param	pFileName		ファイル名
		 */
									KsFont( const KsWChar* pFileName );

		/**
		 * コンストラクタ
		 * @param	pData			データ
		 * @param	dataSize		データサイズ
		 */
									KsFont( const KsByte* pData, KsUInt32 dataSize );

		/**
		 * デストラクタ
		 */
		virtual						~KsFont();

		/**
		 * 生成する
		 */
		void						create( const KsWChar* pFileName );

		/**
		 * 生成する
		 */
		void						create( KsBinaryReader* pReader );

		/**
		 * 破棄する
		 */
		void						destroy();

		/**
		 * 文字列描画
		 */
		void						drawString( const KsWChar*  pText, const KsVector2d& position, KsColor color = KsColor::WHITE, KsReal rotation = 0.0f, const KsVector2d& origin = KsVector2d::ZERO, KsReal scale = 1.0f, ksSPRITE_EFFECTS effects = ksSPRITE_EFFECTS_NONE, KsReal layerDepth = 0.0f );
		void						drawString( const KsSChar*  pText, const KsVector2d& position, KsColor color = KsColor::WHITE, KsReal rotation = 0.0f, const KsVector2d& origin = KsVector2d::ZERO, KsReal scale = 1.0f, ksSPRITE_EFFECTS effects = ksSPRITE_EFFECTS_NONE, KsReal layerDepth = 0.0f );
		void						drawString( const KsString& rText, const KsVector2d& position, KsColor color = KsColor::WHITE, KsReal rotation = 0.0f, const KsVector2d& origin = KsVector2d::ZERO, KsReal scale = 1.0f, ksSPRITE_EFFECTS effects = ksSPRITE_EFFECTS_NONE, KsReal layerDepth = 0.0f );

		void						drawString( const KsWChar*  pText, KsInt32 x, KsInt32 y );

		KsVector4d					measureString( const KsWChar* pText );
		KsBool						containsCharacter( KsWChar character );


		KsTexture*					getTexture() { return m_pTexture; }

	protected:

		template<typename TAction>
		void						forEachGlyph( const KsWChar* pText, TAction action );

		/**
		 * 
		 * @return					
		 */
		const KsGlyph*				findGlyph( KsWChar character );

		/**
		 * 
		 * @return					
		 */
		KsWChar						getDefaultCharacter() const;

		/**
		 * 
		 * @return					
		 */
		void						setDefaultCharacter( KsWChar character );

		/**
		 * ラインスペースを取得する
		 * @return					ラインスペース
		 */
		KsReal						getLineSpacing() const;

		/**
		 * ラインスペースをセットする
		 * @param	spacing			ラインスペース
		 */
		void						setLineSpacing( KsReal spacing );

		/**
		 * 
		 * @return					
		 */
		KsInt32						binarySearch( KsUInt32 key );

	protected:
		KsReal						m_lineSpacing;		/**< ラインスペース			*/
		KsTexture*					m_pTexture;			/**< フォントテクスチャ		*/
		const KsGlyph*				m_pDefaultGlyph;	/**< デフォルトグリフ			*/
		KsGlyph*					m_pGlyphs;			/**< グリフリスト				*/
		KsUInt32					m_numGlyph;			/**< グリフ数宇				*/
		KsGraphics*					m_pGraphics;		/**< グラッフィクスオブジェクト	*/
};


#endif		/* __KSFONT_H__ */
