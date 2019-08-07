/************************************************************************************************/
/** 
 * @file		KsMaterial.h
 * @brief		マテリアル
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMATERIAL_H__
#define __KSMATERIAL_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsTexture;

/************************************************************************************************/
/**
 * マテリアルクラス
 * @class		KsMaterial
 * @author		kato tukasa
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @note		(拡張する)使用するテクスチャのポインタを保持する必要がある
 *				flags で　どのテクスチャを使用するかを調べる std::vector< KsTexture* > m_pTextures;
 */
/************************************************************************************************/
class ksENGINE_API KsMaterial// : public KsRefCounter
{
	public:
		KsString						m_name;			/**< 名前							*/
		KsInt32							m_id;			/**< ID								*/
		KsColorReal						m_diffuse;		/**< ディフューズ色( 拡散光 )			*/
		KsColorReal						m_ambient;		/**< アンビエント色( 環境光 )			*/
		KsColorReal						m_specular;		/**< スペキュラ色( 鏡面光 )			*/
		KsColorReal						m_emissive;		/**< エミッション色					*/
		KsReal							m_power;		/**< スペキュラ ハイライトの鮮明		*/
		KsInt32							m_textureID;	/**< テクスチャID					*/
		KsTexture*						m_pTexture;		/**< テクスチャ						*/

		/**
		 * コンストラクタ
		 */
										KsMaterial() : m_id( 0 ), m_power( 0.0f ), m_textureID( -1 ), m_pTexture( 0 ) {}

		/**
		 * コンストラクタ( マテリアルをセットする )
		 * @param	pDiffuse			ディフューズ色
		 * @param	pAmbient			アンビエント色
		 * @param	pSpecular			スペキュラ色
		 * @param	pEmissive			エミッション色
		 * @param	power				スペキュラ ハイライトの鮮明
		 */
										KsMaterial( const KsColorReal* pDiffuse, const KsColorReal* pAmbient, const KsColorReal* pSpecular, const KsColorReal* pEmissive, KsReal power );

		/**
		 * コンストラクタ( マテリアルをセットする )
		 * @param	refDiffuse			ディフューズ色
		 * @param	refAmbient			アンビエント色
		 * @param	refSpecular			スペキュラ色
		 * @param	refEmissive			エミッション色
		 * @param	power				スペキュラ ハイライトの鮮明
		 */
										KsMaterial( const KsColorReal& refDiffuse, const KsColorReal& refAmbient, const KsColorReal& refSpecular, const KsColorReal& refEmissive, KsReal power );

		/**
		 * コピーコンストラクタ
		 * @param	refMaterial			マテリアル
		 */
										KsMaterial( const KsMaterial& refMaterial );

		/**
		 * コピーコンストラクタ
		 * @param	pMaterial			マテリアル
		 */
										KsMaterial( const KsMaterial* pMaterial );

		/**
		 * ディフューズ色を取得
		 * @return						ディフューズ色
		 */
		KsColorReal*					getDiffuse() { return &m_diffuse; }
		
		/**
		 * アンビエント色を取得
		 * @return						アンビエント色
		 */
		KsColorReal*					getAmbient() { return &m_ambient; }

		/**
		 * スペキュラ色を取得
		 * @return						スペキュラ色
		 */
		KsColorReal*					getSpecular() { return &m_specular; }
		
		/**
		 * エミッション色を取得
		 * @return						エミッション色
		 */
		KsColorReal*					getEmissive() { return &m_emissive; }

		/**
		 * スペキュラ ハイライトの鮮明を取得
		 * @return						スペキュラ ハイライトの鮮明
		 */
		KsReal							getPower() const { return m_power; }

		/**
		 * 使用しているテクスチャを取得する
		 * @return						使用しているテクスチャのポインタ
		 */
		KsTexture*						getTexture() { return m_pTexture; }

		/**
		 * テクスチャIDを取得する
		 * @return						テクスチャID
		 */
		KsInt32							getTextureID() const { return m_textureID; }
		
		/**
		 * ディフューズ色を取得
		 * @return						ディフューズ色
		 */
		void							setDiffuse( const KsColorReal& diffuse ) { m_diffuse = diffuse; }
		
		/**
		 * アンビエント色を取得
		 * @return						アンビエント色
		 */
		void							setAmbient( const KsColorReal& ambient ) { m_ambient = ambient; }

		/**
		 * スペキュラ色を取得
		 * @return						スペキュラ色
		 */
		void							setSpecular( const KsColorReal& specular ) { m_specular = specular; }
		
		/**
		 * エミッション色を取得
		 * @return						エミッション色
		 */
		void							setEmissive( const KsColorReal& emissive ) { m_emissive = emissive; }

		/**
		 * スペキュラ ハイライトの鮮明を取得
		 * @return						スペキュラ ハイライトの鮮明
		 */
		void							setPower( KsReal power ) { m_power = power; }

		/**
		 * 使用しているテクスチャを取得する
		 * @param	pTexture			使用しているテクスチャのポインタ
		 */
		void							setTexture( KsTexture* pTexture ) { m_pTexture = pTexture; }

		/**
		 * テクスチャIDを取得する
		 * @param	textureID			テクスチャID
		 */
		void							setTextureID( KsInt32 textureID ) { m_textureID = textureID; }

		/**
		 * マテリアルをセットする
		 * @param	refDiffuse			ディフューズ色
		 * @param	refAmbient			アンビエント色
		 * @param	refSpecular			スペキュラ色
		 * @param	refEmissive			エミッション色
		 * @param	power				スペキュラ ハイライトの鮮明
		 */
		void							set( const KsColorReal& refDiffuse, const KsColorReal& refDmbient, const KsColorReal& refSpecular, const KsColorReal& refEmissive, KsReal power );

		/**
		 * マテリアルをセットする
		 * @param	pDiffuse			ディフューズ色
		 * @param	pAmbient			アンビエント色
		 * @param	pSpecular			スペキュラ色
		 * @param	pEmissive			エミッション色
		 * @param	power				スペキュラ ハイライトの鮮明
		 */
		void							set( const KsColorReal* pDiffuse, const KsColorReal* pAmbient, const KsColorReal* pSpecular, const KsColorReal* pEmissive, KsReal power );

		/**
		 * マテリアルをセットする
		 * @param	refMaterial			マテリアル
		 */
		void							set( const KsMaterial& refMaterial );

		/**
		 * マテリアルをセットする
		 * @param	pMaterial			マテリアル
		 */
		void							set( const KsMaterial* pMaterial );

		KsBool							operator == ( const KsMaterial& refMaterial ) const	{ return ( 0 == memcmp( this, &refMaterial, sizeof(KsMaterial) ) ); }
		KsBool							operator != ( const KsMaterial& refMaterial ) const	{ return ( 0 != memcmp( this, &refMaterial, sizeof(KsMaterial) ) ); }
		const KsMaterial&				operator  = ( const KsMaterial& refMaterial )		{ memcpy( &m_diffuse, &refMaterial, sizeof(KsMaterial) ); return ( *this ); }
};

/************************************************************************************************/
/**
 * マテリアルリスト
 */
/************************************************************************************************/
typedef KsArray< KsMaterial* >		KsMaterialArray;


#endif		/* __KSMATERIAL_H__ */


