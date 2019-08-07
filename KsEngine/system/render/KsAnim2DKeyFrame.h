/************************************************************************************************/
/** 
 * @file		KsAnimKeyFrame.h
 * @brief		ボーン
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIM2DKEYFRAME_H__
#define __KSANIM2DKEYFRAME_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsCore.h"
#include "KsColor.h"
#include "KsVector.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsAnim2DKeyFrame
 * @brief		アニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DKeyFrame
{
	public:
		/**
		 * コンストラクタ
		 */
								KsAnim2DKeyFrame();

		/**
		 * デストラクタ
		 */
		virtual				~KsAnim2DKeyFrame();

		/**
		 * フレーム再生時間を取得する
		 * @return				フレーム再生時間
		 */
		KsReal					getTime() const { return m_time; }

		/**
		 * 位置座標を取得する
		 * @return				位置座標
		 */
		const KsVector2d		getPos()	{ return m_pos; }

		/**
		 * スケールを取得する
		 * @return				スケール
		 */
		const KsVector2d		getScale()	{ return m_scale; }

		/**
		 * フレーム再生時間をセットする
		 * @param	time		フレーム再生時間
		 */
		void					setTime( KsReal time )  { m_time = time; }

		/**
		 * 位置座標をセットする
		 * @param	pos		位置座標
		 */
		void					setPos( const KsVector2d& pos )	{ m_pos = pos; }

		/**
		 * 回転値をセットする
		 * @param	rot			回転値
		 */
		void					setAngle( KsReal angle )	{ m_angle = angle; }

		/**
		 * スケール値をセットする
		 * @param	scale		スケール値
		 */
		void					setScale( const KsVector2d& scale )	{ m_scale = scale; }

	public:
		KsUInt32				m_flags;		/**< フラグ				*/
		KsReal					m_time;			/**< フレーム再生時間	*/
		KsVector2d				m_pos;			/**< 位置座標			*/
		KsVector2d				m_scale;		/**< スケール			*/
		KsReal					m_angle;		/**< 回転				*/
		KsColor					m_color;		/**< カラー				*/
		KsVector4d				m_uv;			/**< テクスチャ座標		*/
		//KsInt32				m_texId;
		//KsString				m_texName;
		//KsUserData*				m_pUserData;	/**< ユーザーデータ		*/
};


#endif /* __KSANIM2DKEYFRAME_H__ */

