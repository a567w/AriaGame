/*************************************************************************************************/
/**
 * @file	KsSprite.h
 * @brief	スプライトクラス
 * @author	Tsukasa Kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/
#ifndef __KSSPRITE_H__
#define __KSSPRITE_H__

/*===============================================================================================*/
/*                                 << インクルード >>                                            */
/*===============================================================================================*/
#include "KsTask.h"

/*===============================================================================================*/
/*                                     << 定義 >>                                                */
/*===============================================================================================*/
#define ksSPRITE_FLAGS_FILP_X		( 1<< 1 )
#define ksSPRITE_FLAGS_FILP_Y		( 1<< 2 )
#define ksSPRITE_BLEND_ADD			( 1<< 3 )
#define ksSPRITE_BLEND_SUB			( 1<< 4 )
#define ksSPRITE_BLEND_ALPHA		( 1<< 5 )
#define ksSPRITE_CLIP_X			( 1<< 6 )
#define ksSPRITE_CLIP_Y			( 1<< 7 )
#define ksSPRITE_INVISIBLE			( 1<< 8 )	/**< 不可視									*/
#define ksSPRITE_DEFAULT_PRIORITY	( 64 )		/**< スプライトのデフォルト状態での優先順位	*/
#define ksSPRITE_TASK_ORDER		( 3 )		/**< スプライトタスクのオーダー				*/

#define ksSPRITE_WORK_MAX			( 1<<10 )	/**< スプライトワークエリア(最大1024スプライト)	*/

/*===============================================================================================*/
/*                                     << 宣言 >>                                                */
/*===============================================================================================*/
class KsTexture;
class KsVertexBuffer;

class KsRectReal
class KsSprite : public KsTask
{
	public:
								KsSprite();

		virtual				~KsSprite();

		/**
		 * 初期化処理(マネージャに登録されたときに登録)
		 * @param	pParam		パラメータ
		 */
		virtual void*			initialize( void* pParam );

		/**
		 * タスクの実行
		 * @param	pParam		パラメータ
		 */
		virtual void*			execute( void* pParam );

		/**
		 * 描画処理
		 * @param	pParam		パラメータ
		 */
		virtual void*			render( void* pParam );

		/**
		 * 後処理関数でメモリーから削除されるときに呼ばれる
		 * @param	pParam		パラメータ
		 */
		virtual void*			terminate( void* pParam );

	protected:
		KsUInt32				m_spriteFlags;		/**< 各種フラグ		*/
		KsVector2d				m_controlPoint;		/**< 基点			*/
		KsVector2d				m_scale;			/**< スケール		*/
		KsVector2d				m_trans;			/**< 平行移動		*/
		KsReal					m_angle;			/**< 回転値			*/
		KsReal					m_x;				/**< 画像の左		*/
		KsReal					m_y;				/**< 画像の上		*/
		KsReal					m_w;				/**< 画像の幅		*/
		KsReal					m_h;				/**< 画像の高さ		*/
		KsReal					m_clipX;			/**< クリッピングX	*/
		KsReal					m_clipY;			/**< クリッピングY	*/
		KsReal					m_clipW;			/**< クリッピングW	*/
		KsReal					m_clipH;			/**< クリッピングH	*/
		KsVector4d				m_ST;

};

/*************************************************************************************************/
/**
 * @class	KsSprite
 * @brief	スプライト
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 */
/*************************************************************************************************/
class KsSprite : public KsTask
{
		friend class KsSpriteWorkArea;
	public:
		KsUInt16						m_spriteFlags;		/**< スプライトフラグ		*/
		KsUInt8							m_useWork;			/**< ワークフラグ			*/
		KsUInt8							m_reserv;			/**< 空き					*/
		KsTexture*						m_pTexture;			/**< テクスチャ				*/
		KsReal							m_centerX;			/**< 中心X座標				*/
		KsReal							m_centerY;			/**< 中心Y座標				*/
		KsReal							m_scaleX;			/**< Xスケール値			*/
		KsReal							m_scaleY;			/**< Yスケール値			*/
		KsInt32							m_clipX;			/**< */
		KsInt32							m_clipY;
		KsInt32							m_clipW;
		KsInt32							m_clipH;
		KsReal							m_rotate;			/**< 回転量					*/
		KsVertexBuffer*					m_pVertex;			/**< 頂点データ				*/
		KsReal							m_x[ 4 ];			/**< セット座標保存用		*/
		KsReal							m_y[ 4 ];			/**< セット座標保存用		*/
		//KsMatrix						m_mat;				// 移動と回転はマトリックスを使ったほうがいいかも・・・
		//KsMatrix						m_ltm;				//

	public:
		/**
		 * コンストラクタ
		 */
										KsSprite();

		/**
		 * デストラクタ
		 */
		virtual						~KsSprite();

		/**
		 * スプライト生成
		 * @param		x				X座標
		 * @param		y				Y座標
		 * @param		w				幅
		 * @param		h				高さ
		 * @param		tx				テクスチャのX座標
		 * @param		ty				テクスチャのY座標
		 * @param		tw				テクスチャの幅
		 * @param		th				テクスチャの高さ
		 * @param		scaleX			Xのスケール値
		 * @param		scaleY			Yのスケール値
		 * @param		rotate			回転量
		 * @param		color			カラー
		 * @param		pTexture		使用テクスチャのポインタ(使用しないときは、NULLを設定)
		 */
		void							create( KsReal	x,	KsReal	 y,	KsReal	 w, KsReal	h,
												KsReal	tx,	KsReal	ty,	KsReal	tw,	KsReal	th,
												KsReal	scaleX, KsReal		scaleY,
												KsReal	rotate, KsUInt32	color,	KsTexture* pTexture );

		/**
		 * スプライト生成
		 * @param		x				X座標
		 * @param		y				Y座標
		 * @param		w				幅
		 * @param		h				高さ
		 * @param		tx				テクスチャのX座標
		 * @param		ty				テクスチャのY座標
		 * @param		tw				テクスチャの幅
		 * @param		th				テクスチャの高さ
		 * @param		color			カラー
		 * @param		pTexture		使用テクスチャのポインタ(使用しないときは、NULLを設定)
		 */
		void							create( KsReal	 x,	KsReal	 y,	KsReal	 w, KsReal	h,
												KsReal	tx,	KsReal	ty,	KsReal	tw,	KsReal	th,
												KsUInt32	color,	KsTexture* pTexture );

		/**
		 * スプライト生成
		 * @param		x				スプライト表示のX座標(スプライトの中心を基点とする)
		 * @param		y				スプライト表示のY座標(スプライトの中心を基点とする)
		 * @param		tx				テクスチャのX座標
		 * @param		ty				テクスチャのY座標
		 * @param		w				幅
		 * @param		h				高さ
		 * @param		color			カラー
		 * @param		pTexture		使用テクスチャのポインタ(使用しないときは、NULLを設定)
		 */
		void							create( KsReal	 x,	KsReal	 y,
												KsReal	tx,	KsReal	ty,
												KsReal	 w,	KsReal	 h,
												KsUInt32	color,	KsTexture* pTexture );

		/**
		 * スプライトフラグをセットする
		 * @param		flags			各種フラグ
		 */
		void							setSpriteFlags( KsUInt32 flags );

		/**
		 * UV座標をセットします
		 * @param		tx				テクスチャのX座標
		 * @param		ty				テクスチャのY座標
		 * @param		tw				テクスチャの幅
		 * @param		th				テクスチャの高さ
		 */
		void							setUVWH( KsReal tx, KsReal ty, KsReal tw, KsReal th );

		/**
		 * 指定頂点の頂点カラーをセットする
		 * @param		index			インデックス
		 * @param		color			カラー
		 */
		void							setColor( KsUInt32 index, KsUInt32 color );

		/**
		 * すべての頂点カラーをセットする
		 * @param		color			カラー
		 */
		void							setColorAll( KsUInt32 color );


		/**
		 * スケール値をセットする
		 * @param		scaleX			スケールX
		 * @param		scaleX			スケールY
		 */
		void							setScale( KsReal scaleX, KsReal scaleY );

		/**
		 * テクスチャをセットする
		 * @param		pTexture		テクスチャ
		 */
		void							setTexture( KsTexture* pTexture );

		/**
		 * 位置座標をセットする
		 * @param		x				X座標
		 * @param		y				Y座標
		 */
		void							setTranslate( KsReal x, KsReal y );

		/**
		 * 回転角度セットする
		 * @param		rotate			回転角度
		 */
		void							setRotate( KsReal rotate );

		/**
		 * 今の状態から指定量回転させる
		 * @param		x				X方向の移動量
		 * @param		y				Y方向の移動量
		 */
		void							translate( KsReal x, KsReal y );

		/**
		 * 今の状態から指定量回転させる
		 * @param		rotate			回転量
		 */
		void							rotate( KsReal rotate );

		/**
		 * 初期化処理(マネージャに登録されたときに登録)
		 * @param		pParam			パラメータ
		 */
		virtual void*					initialize( void* pParam );

		/**
		 * タスクの実行
		 * @param		pParam			パラメータ
		 */
		virtual void*					execute( void* pParam );

		/**
		 * 描画処理
		 * @param		pParam			パラメータ
		 */
		virtual void*					render( void* pParam );

		/**
		 * 後処理関数でメモリーから削除されるときに呼ばれる
		 * @param		pParam			パラメータ
		 */
		virtual void*					terminate( void* pParam );

	protected:
		/**
		 * スタートアップ
		 */
		void							startup();

		/**
		 * パラメータをクリアーする
		 */
		void							clear();

		/**
		 * 頂点などを再セットしなおす
		 */
		void							reset();

		/**
		 * 頂点バッファを生成する
		 */
		void							createVertexBuffer();

		/**
		 * 頂点バッファを削除する
		 */
		void							destroyVertexBuffer();
};

class KsSpriteManager
{
	KsSpriteManager();
};

/*************************************************************************************************/
/**
 * @class	KsSpriteWorkArea
 * @brief	スプライトワークエリア
 * @author	tsukasa kato
 * @date	2003/11/30
 * @version	1.0.0
 * @note	もしワークが足りなくなったらnewで生成される
 */
/*************************************************************************************************/
class KsSpriteWorkArea
{
	public:
		/**
		 * 初期化
		 */
		static void					initialize();

		static void					terminate();

		/**
		 * スプライト生成
		 */
		static KsSprite*				createSprite();

		/**
		 * スプライト破棄
		 * @param		pSprite			スプライト
		 */
		static void					destroySpreite( KsSprite* pSprite );

	private:
		static KsSprite					m_spriteWork[ ksSPRITE_WORK_MAX ];	/**< スプライト用ワーク			*/
		static KsSprite*				m_spriteStack[ ksSPRITE_WORK_MAX ];	/**< 空きワークエリアスタック	*/
		static KsInt32					m_stackCount;						/**< スタックカウント			*/
};


inline void KsSpriteWorkAreaInitialize() { KsSpriteWorkArea::initialize(); }


#endif /* __KSSPRITE_H__ */



