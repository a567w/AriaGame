/************************************************************************************************/
/** 
 * @file		KsAnimationChannel.h
 * @brief		アニメーションチャンネル
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSANIMATIONCHANNEL_H__
#define __KSANIMATIONCHANNEL_H__

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
 * @class		KsAnimationChannel
 * @brief		アニメーションチャンネルクラス
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsAnimationChannel
{
	private:
		KsHashTable<KsKeyFrameCollection*>		m_dict;
		KsArray<KsKeyFrameCollection*>			m_fames;
		KsUInt32								m_numCollection;
		KsArray<KsString>						m_affectedBones;
			
	public:
		/**
		 * コンストラクタ
		 */
		KsAnimationChannel();

		/**
		 * コンストラクタ
		 */
		KsAnimationChannel( KsKeyFrameCollection* pKeyFrameCollection, KsUInt32 numCollection );

		/**
		 * デストラクタ
		 */
		~KsAnimationChannel();

		void					addKeyFrameCollection( const KsString& boneName, KsKeyFrameCollection* pKeyFrameCollection )
		{
			m_dict.add( boneName, pKeyFrameCollection );
			m_fames.push_back( pKeyFrameCollection );
			++m_numCollection;
		}

		KsKeyFrameCollection*	getKeyFrameCollection( const KsString& boneName )
		{
			KsHashTable<KsKeyFrameCollection*>::KsHashNodeType*	pNode = m_dict.find( boneName );

			if( pNode )
			{
				return pNode->m_pData;
			}

			return NULL;
		}

		KsBool hasAffectsBone( const KsString& boneName )
		{
			return ( NULL != m_dict.find( boneName ) );
		}


		KsArray<KsString>&		getAffectedBones()
		{
			return m_affectedBones;
		}

		const KsString&			getAffectedBone( KsUInt32 index )
		{
			return m_affectedBones[ index ];
		}

		KsKeyFrameCollection*	getKeyFrameCollection( KsUInt32 index )
		{
			return m_fames[ index ];
		}

		KsUInt32				getNumCollection() const { return m_fames.size(); }
};


#endif /* __KSANIMATIONCHANNEL_H__ */

