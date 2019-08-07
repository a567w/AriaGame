/************************************************************************************************/
/** 
 * @file		KsMesh.h
 * @brief		メッシュクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSMESH_H__
#define __KSMESH_H__

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
 * @class		KsMeshPart
 * @brief		メッシュパーツ
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsMesh
{
	private:
		KsString					m_name;				/// このメッシュの名前を取得します。
		KsBoundingSphere			m_boundingSphere;	/// このメッシュが含まれている BoundingSphere を取得します。
		KsMeshPartCollection		m_vpMeshParts;		/// このメッシュを構成する ModelMeshPart オブジェクトを取得します。メッシュの各パーツは、同じマテリアルを共有するプリミティブの集合で構成されています。
		//KsEffectCollection			m_vpEffects;		/// このメッシュに関連付けられているエフェクトのコレクションを取得します。
		//KsUserData*				m_pUserData;		/// ユーザーデータ

		//     このメッシュに関連付けられているエフェクトのコレクションを取得します。
		//ModelEffectCollection		Effects

		//     このメッシュの親ボーンを取得します。メッシュの親ボーンにはモデルで親メッシュに関連したメッシュを配置する方法を記述する変換行列が含まれます。
		//ModelBone					ParentBone

	public:
		/**
		 * コンストラクタ
		 */
									KsMesh();

		/**
		 * デストラクタ
		 */
		virtual						~KsMesh();

		/** 
		 * 描画処理
		 * @param	pRenderContext	描画コンテキスト
		 */
		virtual void				draw( KsRenderContext* pRenderContext, KsModelParameter* pParameter=NULL );

		//     現在の Effect 設定を使用して、このメッシュ内のすべての ModelMeshPart オブジェクトを描画します。
		KsMeshPart*					getMeshPart( KsUInt32 index ) { return m_vpMeshParts[ index ]; }
		KsUInt32					getMeshPartCount() const { return m_vpMeshParts.size(); }

	public:
		void						addMeshParts( KsMeshPart* pMeshPart ) { m_vpMeshParts.push_back( pMeshPart ); }
};

#endif		/* __KSMESH_H__ */



