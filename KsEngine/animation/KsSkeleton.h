/************************************************************************************************/
/** 
 * @file		KsSkeleton.h
 * @brief		�X�P���g���N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 * @version		1.0.0
 */
/************************************************************************************************/
#ifndef __KSSKELETON_H__
#define __KSSKELETON_H__

/*==============================================================================================*/
/*                                 << �C���N���[�h >>                                            */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << ��` >>                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*                                     << �錾 >>                                               */
/*==============================================================================================*/

/************************************************************************************************/
/**
 * @class		KsSkeleton
 * @brief		�X�P���g���N���X
 * @author		Tsukasa Kato
 * @date		----/--/--
 * @since		----/--/--
 */
/************************************************************************************************/
class ksENGINE_API KsSkeleton
{
	protected:
		KsString					m_boneName;			/**< �{�[����			*/
		KsInt32						m_boneIndex;		/**< �{�[���C���f�b�N�X	*/
		KsString					m_parentName;		/**< �e�{�[����			*/
		KsInt32						m_parentIndex;		/**< �e�{�[���C���f�b�N�X	*/
		KsArray<KsSkeleton*>		m_vpChildren;		/**< �q�X�P���g��		*/
		KsArray<KsBonePose*>		m_vpBonePose;		/**< �{�[���|�[�Y		*/

	public:
		/**
		 * �R���X�g���N�^
		 */
									KsSkeleton();

		/**
		 * �R���X�g���N�^
		 */
									KsSkeleton( KsModel* pModel );

		/**
		 * �f�X�g���N�^
		 */
		virtual						~KsSkeleton();

		/**
		 * �X�V����
		 * @param	gameTime			�X�V����
		 */
		virtual void				update( KsReal gameTime );

#if 0
		const KsString&				getBoneName() { return m_boneName };
		KsInt32						getBoneIndex() const { return m_boneIndex; }
		const KsString&				getParentName() { return m_parentName };
		KsInt32						getParentIndex;() const { return m_parentIndex;; }
		KsSkeleton*					getChild( KsInt32 index ) { return m_vpChildren[ index ]; }
		KsUInt32					getChildCount() const { return m_vpChildren.size(); }
		KsBonePose*					getBonePose() { return m_bonePose; }


		static void	bindBone( KsSkeleton* pSkeleton, KsBonePoseCollection* pBonePoseCollection )
		{
			if( -1 != pSkeleton->m_boneIndex )
			{
				pSkeleton->m_bonePose = bones[ pSkeleton->m_boneIndex ];
			}

			for( KsUInt32 i=0; i<pSkeleton->getChildCount; i++ )
			{
				bindBone( pSkeleton->getChild( i ), pBonePoseCollection );
			}
		}
#endif
};

#endif		/* __KSSKELETON_H__ */



