/************************************************************************************************/
/** 
 * @file		KsAnimTrack.h
 * @brief		ボーン
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0
 */
/************************************************************************************************/
#ifndef __KSANIM2DTRACK_H__
#define __KSANIM2DTRACK_H__

/*==============================================================================================*/
/*                                 << インクルード >>                                           */
/*==============================================================================================*/
#include "KsArray.h"
#include "KsAnim2DKeyFrame.h"

/*==============================================================================================*/
/*                                     << 定義 >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << 宣言 >>                                               */
/*==============================================================================================*/
class KsAnim2DObject;

/************************************************************************************************/
/**
 * @class		KsAnimTrack
 * @brief		アニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnim2DTrack
{
		typedef KsArray<KsAnim2DKeyFrame*> KsAnim2DKeyFrameArray;

	public:
		/**
		 * キーフレーム数を取得する
		 * @return				キーフレーム数
		 */
		KsInt32				getNumKeyFrame() const { return static_cast<KsInt32>( m_vKeyFrames.size() ); }

		/**
		 * ターゲットジョイントを取得する
		 * @return				ターゲットジョイント
		 */
		const KsAnim2DObject*	getTarget() { return m_pTarget; }

		/**
		 * 最大トラック時間を取得する
		 * @return				最大トラック時間
		 */
		KsReal					getMaxTime() const { return m_maxTime; }

		/**
		 * 指定時間のキーフレームを取得する
		 * @param	time		指定時間 ( in )
		 * @param	pParam		パラメータ ( out ) [ 0.0f ... 1.0f ]
		 * @param	pKey1		キーフレーム1( out )
		 * @param	pKey2		キーフレーム2( out )
		 * @return				指定キーフレームの状態
		 */
		KsInt32				getKeyFrame( KsReal time, KsReal *pParam, KsAnim2DKeyFrame* pKey1, KsAnim2DKeyFrame* pKey2, KsBool bLoop=ksFALSE );

		/**
		 * 指定インデックスのキーフレームを取得する
		 * @return				キーフレーム
		 */
		KsAnim2DKeyFrame*		getKeyFrame( KsInt32 index ) const { return m_vKeyFrames[ index ]; }

	public:
		KsAnim2DKeyFrameArray	m_vKeyFrames;	/**< キーフレームリスト		*/
		KsAnim2DObject*			m_pTarget;		/**< ターゲットジョイント	*/
		KsReal					m_maxTime;		/**< 最大トラック時間		*/
};


#endif /* __KSANIM2DTRACK_H__ */

