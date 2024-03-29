/************************************************************************************************/
/** 
 * @file		KsRenderTargetTexture.h
 * @brief		描画ターゲット
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSRENDERTARGETTEXTURE_H__
#define __KSRENDERTARGETTEXTURE_H__

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
 * @class		KsRenderTargetTexture
 * @brief		描画ターゲット
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class KsRenderTargetTexture : public KsRenderTarget
{
	public:
		/**
		 * コンストラクタ
		 */
									KsRenderTargetTexture( KsTexture* pTexture ) : m_pTexture( pTexture ){}

		/**
		 * コンストラクタ
		 */
									KsRenderTargetTexture()	: m_pTexture( 0 ){}

		/**
		 * デストラクタ
		 */
		virtual						~KsRenderTargetTexture(){ ksDESTROY( m_pTexture ); }

		/**
		 * ロックする
		 * @return					データのポインタ
		 */
		virtual void*				lock() = 0;

		/**
		 * ロックを解除する
		 */
		virtual void				unlock() = 0;
		/**
		 * テクスチャの破棄
		 */
		virtual void				destroy() = 0;

		/**
		 * テクスチャのポインタを取得
		 * @return					テクスチャのポインタ
		 */
		KsTexture*					getTexture() { return m_pTexture; }

	protected:
		KsTexture*					m_pTexture;		/**< テクスチャのポインタ	*/
};



#endif		/* __KSRENDERTARGETTEXTURE_H__ */



