/************************************************************************************************/
/** 
 * @file		KsAnimation.h
 * @brief		アニメーションクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSANIMATION_H__
#define __KSANIMATION_H__

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
 * @class		KsAnimation
 * @brief		アニメーション
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnimation
{
	private:
		KsReal					m_duration;			/**< アニメーション時間					*/
		KsString				m_animationName;	/**< アニメーション名						*/
		KsAnimationChannel*		m_boneAnimations;	/**< ボーンアニメーションチャンネル		*/

	public:
		/**
		 * コンストラクタ
		 */
		KsAnimation();

		/**
		 * コンストラクタ
		 * @param	animationName		アニメーションの名前
		 * @param	pAnimationChannel	アニメーションチャンネル
		 */
		KsAnimation( const KsString& animationName, KsAnimationChannel* pAnimationChannel );

		/**
		 * デストラクタ
		 */
		virtual					~KsAnimation();

		/**
		 * アニメーションの経過時間を取得する
		 * @return				アニメーションの経過時間
		 */
		KsReal					getDuration() const { return m_duration; }

		/**
		 * アニメーション名前を取得する
		 * @return				アニメーションの名前
		 */
		const KsString&			getName() { return m_animationName; }

		/**
		 * アニメーションチャンネルを取得する
		 * @return				アニメーションチャンネル
		 */
		KsAnimationChannel*		getAnimationChannels() { return m_boneAnimations; }

		/**
		 * 影響ボーンの名前を取得する
		 * @param	index		インデックス
		 * @return				影響ボーンの名前
		 */
		const KsString&			getAffectedBone( KsUInt32 index ) { return m_boneAnimations->getAffectedBone( index );}

		/**
		 * 影響ボーンあるかどうかをチェックする
		 * @param	boneName	ボーンの名前
		 * @retval	ksTRUE		影響ボーンを持っている
		 * @retval	ksFALSE		影響ボーンを持ってない
		 */
		KsBool					hasAffectsBone( const KsString& boneName ) { return m_boneAnimations->hasAffectsBone( boneName ); }
};


#endif /* __KSANIMATION_H__ */

