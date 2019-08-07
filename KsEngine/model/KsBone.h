/************************************************************************************************/
/** 
 * @file		KsBone.h
 * @brief		ボーン関係
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSBONE_H__
#define __KSBONE_H__

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
 * @class		KsBone
 * @brief		モデルボーンクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsBone
{
		friend class KsModel;
	public:
		/**
		 * コンストラクタ
		 */
									KsBone();

		/**
		 * デストラクタ
		 */
		virtual						~KsBone();

		/**
		 * ボーン名を取得する
		 * @return					ボーン名
		 */
		const KsString&				getName() const { return m_name; }


		/**
		 * ボーンインデックスを取得する
		 * @return					ボーンインデックス
		 */
		KsInt32						getIndex() const { return m_index; }

		/**
		 * 親ボーンインデックスを取得する
		 * @return					親ボーンインデックス
		 */
		KsInt32						getParentIndex() const { return m_parent; }

		/**
		 * 親ボーンを取得する
		 * @return					親ボーン
		 */
		KsBone*						getParent() { return m_pParent; }


		/**
		 * 子供のボーンの数を取得する
		 * @return					子供の数
		 */
		KsUInt32					getNumChild() const { return m_vpChildren.size(); }

		/**
		 * 子供のボーンを取得する
		 * @return					子供のボーン
		 */
		KsBone*						getChild( KsInt32 index ) { return m_vpChildren[ index ]; }

		/**
		 *
		 */
		KsMatrix4x4&				getDefaultTransform() { return m_defaultTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getBoneTransform() { return m_boneTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getAnimationTransform() { return m_animationTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getInverseTransform() { return m_inverseTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getWorldTransform() { return m_worldTransform; }

		/**
		 *
		 */
		KsMatrix4x4&				getSkinTransform() { return m_skinTransform; }

		/**
		 * ボーンを描画する
		 */
		void						draw();

	public:
		KsInt32						m_index;				/// Bones コレクション内の、このボーンのインデックスを取得します。
		KsString					m_name;					/// このボーンの名前を取得します。
		KsInt32						m_parent;				/// 親ボーンのインデックス
		KsBone*						m_pParent;				/// このボーンの親を取得します。
		KsArray<KsBone*>			m_vpChildren;			/// このボーンの子であるボーンのコレクションを取得します。
		KsMatrix4x4					m_defaultTransform;		/// 親ボーンを基準としてこのボーンをトランスフォームするために使用される行列を取得または設定します。
		KsMatrix4x4					m_animationTransform;	/// 親ボーンを基準としてこのボーンをトランスフォームするために使用される行列を取得または設定します。
		KsMatrix4x4					m_inverseTransform;
		KsMatrix4x4					m_boneTransform;
		KsMatrix4x4					m_worldTransform;
		KsMatrix4x4					m_skinTransform;
};


#endif		/* __KSBONE_H__ */



